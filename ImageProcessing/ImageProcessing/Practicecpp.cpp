#include <opencv\cv.h>
#include <opencv\highgui.h>

int main()
{
	IplImage *image = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);

	cvShowImage("Test Viewer", image);

	cvWaitKey();
	cvDestroyWindow("Test Viewer");
	cvReleaseImage(&image);

	return 0;
}