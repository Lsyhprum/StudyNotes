# Bitmap 加载与缓存
## Bitmap 高效加载
BitmapFactory 提供了四类方法加载图片：**decodeFile**、**decodeResource**、**decodeStream** 与 **decodeByteArray**。其中 decodeFile 与 decodeResource 间接调用了 decodeStream。
Bitmap占用的内存为：**像素总数 * 每个像素占用的内存**。在Android中，Bitmap有四种像素类型：**ARGB_8888**、**ARGB_4444**、**ARGB_565**、**ALPHA_8**，他们每个像素占用的字节数分别为4、2、2、1。因此，一个 2000*1000 的 ARGB_8888 类型的Bitmap占用的内存为 2000*1000*4 = 8000000B = 8MB 。
通过 **BitmapFactory.Options** 设置 采样率（**inSampleSize**）加载缩小的图片可降低占用内存。
```java
 public static Bitmap decodeBitmapFromRes(Resources res , int resId, int req_width, int req_height){
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeResource(res, resId, options);
        options.inSampleSize = calculateSize(options, req_width, req_height);
        options.inJustDecodeBounds = false;
        return BitmapFactory.decodeResource(res, resId, options);
    }

    private static int calculateSize(BitmapFactory.Options options, int req_width , int req_height){
        final int width = options.outWidth;
        final int height = options.outHeight;
        int inSampleSize = 1;
        while (width >= req_width && height >= req_height){
            inSampleSize *= 2;
            req_height *= 2;
            req_width *= 2;
        }

        return inSampleSize;
    }
```
* **inJustDecodeBounds**设置为 true 时，BitmapFactory 只会加载图片尺寸信息。**尺寸信息与图片位置与运行设备有关。**否则将会获取原图尺寸，此时与图片位置与运行设备无关。

## Android 中的缓存策略
缓存策略主要包含添加、获取和删除。目前常用的缓存算法是 **LRU（Least Recently Used）**,即**近期最少使用**算法，当缓存满时，优先淘汰近期最少使用的缓存对象。
采用 LRU 算法的缓存有两种：**LruCache** 与 **DiskLruCache**。
### LruCache
LruCache 内部采用 **LinkedHashMap** 以强引用的方式存储外界的缓存对象。
* **强引用**：直接的对象引用。
* **软引用**：内存不足时此对象会被 GC 回收。
* **弱引用**：随时会被 GC 回收

自从 Android2.3 之后，Android 中的 GC 变得更加积极，导致使用软引用与弱引用做缓存的 Bitmap 非常容易被回收掉；另外，在Android3.0之前，Bitmap的数据是直接分配在 native memory 中，它的释放是不受 dalvik 控制的，因此更容易导致内存的溢出。
```java
int maxMemory = (int) ((Runtime.getRuntime().maxMemory())/8);//KB
int cacheSize = maxMemory / 8;
LruCache<String, Bitmap> memoryCache = new LruCache<String , Bitmap>(cacheSize){
    @Override
    protected int sizeOf(String key, Bitmap value) {
        return bitmap.getByteCount() / 1024;//KB
    }
};
```
**获取缓存对象**
```java
memoryCache.get(key);
```
**添加缓存对象**
```java
memoryCache.put(key, bitmap);
```

### DiskLruCache
**DiskLruCache** 用于实现设备缓存，通过缓存对象写入文件系统实现缓存效果。
通过 gradle 导入 DiskLruCache：
> compile 'com.jakewharton:disklrucache:2.0.2'

#### DiskLruCache 创建
**public static DiskLruCache open(File directory, int appVersion, int valueCount, long maxSize) throws IOException**
directory 为磁盘缓存在文件系统中的存储路径。如果希望卸载引用后保留缓存数据，则应选择 SD 卡上特定目录。若想删除缓存目录，则写入 SD 卡上的缓存目录：
> /sdcard/Android/data/< package_name >/cache 

**创建缓存子目录**
```java
// 优先使用外置存储，如果外置存储不存在，使用内置存储。
public static File getDiskCacheDir(Context context, String uniqueName) {
    // 如果MEDIA目录已经挂载或者外置存储是手机自带的，使用外置存储，否则使用内置存储
    final String cachePath =
            Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState()) ||
                    !Environment.isExternalStorageRemovable()
                    ? context.getExternalCacheDir().getPath() :
                    context.getCacheDir().getPath();

    return new File(cachePath + File.separator + uniqueName);
}
```
**创建**
```java
private static final long DISK_CACHE_SIZE = 1024*1024*10;//10MB

File diskCacheDir = FileUtil.getDiskCacheDir(this, "bitmap");
if(!diskCacheDir.exists()){
     diskCacheDir.mkdirs();
 }
 try {
     DiskLruCache diskLruCache = DiskLruCache.open(diskCacheDir , 1 ,1 , DISK_CACHE_SIZE);
 } catch (IOException e) {
     e.printStackTrace();
 }
```

#### DiskLruCache 缓存添加
DiskLruCache 的缓存添加通过 **Editor** 完成，表示一个缓存对象的编辑对象。一般采用 url 的 **md5** 值作为 key。

**提交写入操作：**
> commit()

**回退操作：**
> abort()
```java
 String key = AblumUtil.hashKeyFromUrl(url);
 try {
       DiskLruCache.Editor editor = diskLruCache.edit(key);
       if(editor != null){
           OutputStream os = editor.newOutputStream(DISK_CACHE_INDEX);
           if(downloadUrlToStream(url, os)){
              editor.commit();
           }else{
              editor.abort();
           }
           diskLruCache.flush();
       }
  } catch (IOException e) {
      e.printStackTrace();
  }
```


#### DiskLruCache 缓存查找
通过 DiskLruCache 的 get 方法获取 **Snapshot** 对象。通过 Snapshot 对象即可获取缓存的文件输入流。
由于获取缩放图片时，需要读取两次 **FileInputStream**，而两次 **decodeStream** 会影响文件流的位置，导致错误。因此需要通过 **BitmapFactory.decodeFileDescriptor** 加载缩放后的图片。
```java
Bitmap bitmap = null;
String key = AblumUtil.hashKeyFromUrl(url);
DiskLruCache.Snapshot snapshot = diskLruCache.get(key);
if(snapshot != null){
    FileInputStream fis = (FileInputStream) snapshot.getInputStream(0);
    FileDescriptor fd = fis.getFD();
    bitmap = decodeBitmapFromFileDescriptor(fd, req_width, req_height);
    if(bitmap != null){
        putBitmapToMemoryCache(key, bitmap);
    }
}
```
```java
public static Bitmap decodeBitmapFromFileDescriptor(FileDescriptor fd , int req_width, int req_height){
    BitmapFactory.Options options = new BitmapFactory.Options();
    options.inJustDecodeBounds = true;
    options.inSampleSize = calculateSize(options, req_width, req_height);
    BitmapFactory.decodeFileDescriptor(fd, null, options);
    options.inJustDecodeBounds = false;
    return BitmapFactory.decodeFileDescriptor(fd, null, options);
}
```
