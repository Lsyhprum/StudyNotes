# 图像分析

## 离散傅里叶变换

## 积分图

## Canny 边缘检测

图像边缘是指像素灰度值突然发生变化的区域。函数的变化趋势可以用函数的导数描述，当函数值突然变大时，导数必然变大，否则导数较小。

![图像边缘]()

由于图像是离散的信号，需使用差分替代微分：

![差分]()

这种对 x 轴方向求导方式对应滤波器为：

![]()

但这种求导方式计算结果最接近两个像素中间位置，但该处不存在任何像素，因此想表示某个像素处的梯度，最接近的方式是求取前一个像素和后一个像素的差值：

改进求导方式在 x 轴方向滤波器：

45 度方向的梯度：

图像边缘有可能是由高像素值变为低像素值，也有可能是由低像素值变成高像素值，由以上滤波器得到正数值表示像素值由低变高，得到负数值表示像素值由高到低，这两种都是图像边缘，为显示这两种边缘信息，需将计算结果求取绝对值。

convertScalaAbs()

该函数可以求取矩阵中所有数据的绝对值

```cpp
void cv::convertScaleAbs(InputArray  src, OutputArray  dst, double  alpha = 1, double  beta = 0 )
```

* alpha: 缩放因子，默认为只求绝对值不缩放

* beta: 在原始数据上添加偏值





## Hough 变换

## 距离变换