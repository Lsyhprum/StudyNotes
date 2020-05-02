# OpenCV 初探

## 显示图片

```cpp
# include <opencv2/opencv.hpp>

using namespace cv;

int main() {
	Mat img = imread("h:\\lena.png");
	namedWindow("Example", WINDOW_AUTOSIZE);

	imshow("Example", img);

	waitKey(0);
	destroyWindow("Example");
	return 0;
}
```