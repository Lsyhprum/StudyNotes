# 滤波与卷积

## 预备知识

* **滤波/核**：滤波器/核指由一副图像 I(x, y) 根据像素点 x, y 附近的区域计算得到一副新图像 I'(x, y) 的算法。线性滤波算法满足叠加原理。

* **锚点**：锚点定义了核与源图像的对齐关系

## 阙值

## 平滑

### 均值滤波器

均值滤波器内所有像素值具有相同权重，该滤波器将减小像素值之间的差距，使图像细节模糊。滤波器越大，效果越明显。该滤波器形式如下：

![blur]()

OpenCV blur() 函数：

```cpp
void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )
```

* src: 输入图片
* dst: 输出图片
* ksize: 核大小
* acchor: 锚点，默认为(-1,-1)，即内核中心
* borderType：判断图像边界模式

代码实现：

```cpp
img.convertTo(img, CV_32FC1);   // 需转化为 float, 否则 uchar 卷积后导致数据溢出，高光处产生错误

Mat kernel = Mat::ones(10, 10, CV_32FC1);

Mat blur_mat = Mat(img.rows - kernel.rows + 1, img.cols - kernel.cols + 1, CV_32FC1);

for (int i = 0; i < blur_mat.rows; i++) {
    for (int j = 0; j < blur_mat.cols; j++) {
        int sum = 0;
        for (int m = 0; m < kernel.rows; m++) {
            for (int n = 0; n < kernel.cols; n++) {
                sum += img.at<float>(i + m, j + n) * kernel.at<float>(m, n);
            }
        } 
        blur_mat.at<float>(i, j) = sum / (kernel.cols * kernel.rows);
    }
}
blur_mat.convertTo(blur_mat, CV_8UC1);
imshow("blur", blur_mat);
```

### 方框滤波

### 中值滤波


### 高斯滤波

### 双边滤波

## 导数和梯度

### 索贝尔导数

Sobel 算子可以实现任意阶导数和混合偏导数。其求取边缘的思想原理与求边缘思想一致，此外 Sobel 算子还结合了高斯平滑滤波的思想，将边缘检测滤波器尺寸由 ksize*1 改进为 ksize*ksize，比普通方法更明显。

Sobel 边缘检测算子提取图像边缘主要分为三个步骤：

* 提取 X 方向边缘，X 方向一阶 Sobel 边缘检测算子：

* 提取 Y 方向边缘，Y 方向一阶 Sobel 边缘检测算子：

* 综合两个方向的边缘信息得到整幅图像边缘。

    * 求两张图像对应像素值的绝对值之和

    * 求两张图像对应像素值的平方和

OpenCV Sobel()

```cpp
void cv::Sobel(InputArray  src, OutputArray  dst, int  ddepth, int  dx, int  dy, int  ksize = 3, double  scale = 1, double  delta = 0, int  borderType = BORDER_DEFAULT)
```

* ddepth: 输出图像的数量类型（深度）

* dx: X 方向的差分阶数

* dy: Y 方向的差分阶数

* ksize: Sobel 边缘算子的尺寸，必须是 1，3，5，7

* scale: 缩放因子

* delta: 偏值

* borderType: 像素外推法选择标志

## 图像形态学

### 膨胀与腐蚀

膨胀与腐蚀是形态学最基础的变换，他们在消除噪声、元素分割和连接等方面得到了应用。

膨胀是一种卷积操作，它将目标像素的值替换为卷积核覆盖区域的局部最大值。腐蚀是与之相反的操作。

### 开操作与闭操作

### 形态学梯度

### 顶帽和黑帽

## 任意线性滤波器做卷积