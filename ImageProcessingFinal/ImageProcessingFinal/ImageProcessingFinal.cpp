#include <opencv/cv.h>
#include <opencv/highgui.h>

int main() {
	IplImage* lena = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // ���� �̹��� �ε�
	IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_COLOR); // �ռ��� �̹��� �ε�
	IplImage* mix = cvCreateImage(cvGetSize(lena), lena->depth, lena->nChannels); // �ռ��� �̹��� ����

	int i, j;
	CvScalar pixelValue, temp;

	for (i = 0; i < lena->height; i++) {
		for (j = 0; j < lena->width; j++) {
			pixelValue = cvGet2D(heart, i, j); // �ռ��� �̹����� �� ���

			if (pixelValue.val[0] < 240) {
				temp = cvGet2D(heart, i, j); // �ռ��� �̹��� ���� ��ο�� �� ���� ����
				cvSet2D(mix, i, j, temp);
			}
			else {
				temp = cvGet2D(lena, i, j); // �׿ܴ� ���� ��
				cvSet2D(mix, i, j, temp);
			}
		}
	}

	cvNamedWindow("lena image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("heart image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mix image", CV_WINDOW_AUTOSIZE);

	cvShowImage("lena image", lena);
	cvShowImage("heart image", heart);
	cvShowImage("mix image", mix);

	cvWaitKey();

	cvDestroyWindow("lena image");
	cvDestroyWindow("heart image");
	cvDestroyWindow("mix image");

	cvReleaseImage(&lena);
	cvReleaseImage(&heart);
	cvReleaseImage(&mix);

	return 0;
}