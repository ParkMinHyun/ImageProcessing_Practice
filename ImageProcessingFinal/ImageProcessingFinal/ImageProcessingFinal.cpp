#include <opencv/cv.h>
#include <opencv/highgui.h>

void SaveImage(char *saveImageName, IplImage *saveImage);
IplImage *scaleDown(IplImage *lenaImage, IplImage *tempImage);
int main() {
	IplImage* lena = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // ���� �̹��� �ε�
	IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_COLOR); // �ռ��� �̹��� �ε�
	IplImage* scaleDownImage = cvCreateImage(cvSize(lena->width / 2, lena->height / 2), lena->depth, lena->nChannels); // �ռ��� �̹��� ����
	IplImage* mix = cvCreateImage(cvGetSize(lena), lena->depth, lena->nChannels); // �ռ��� �̹��� ����

	int i, j;
	CvScalar temp;
	
	scaleDownImage = scaleDown(lena, scaleDownImage);

	//SaveImage("foo.jpg", mix);

	cvNamedWindow("lena image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("scaleDown image", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("mix image", CV_WINDOW_AUTOSIZE);

	cvShowImage("lena image", lena);
	cvShowImage("scaleDown image", scaleDownImage);
	//cvShowImage("mix image", mix);

	cvWaitKey();

	cvDestroyWindow("lena image");
	cvDestroyWindow("scaleDown image");
	//cvDestroyWindow("mix image");

	cvReleaseImage(&lena);
	cvReleaseImage(&scaleDownImage);
	//cvReleaseImage(&mix);

	return 0;
}

void SaveImage(char *saveImageName, IplImage *saveImage) {
	cvSaveImage(saveImageName, saveImage);
}

IplImage *scaleDown(IplImage *lenaImage, IplImage *tempImage){
	int i, j;
	CvScalar pixelValue;

	for (i = 0; i < lenaImage->height; i++) {
		for (j = 0; j < lenaImage->width; j++) {

			if (i % 2 == 0 && j % 2 == 0) {
				pixelValue = cvGet2D(lenaImage, i, j); // �ռ��� �̹����� �� ���
				cvSet2D(tempImage, i / 2, j / 2, pixelValue);
			}

			//if (pixelValue.val[0] < 240) {
			//	temp = cvGet2D(heart, i, j); // �ռ��� �̹��� ���� ��ο�� �� ���� ����
			//	cvSet2D(mix, i, j, temp);
			//}
			//else {
			//	temp = cvGet2D(lena, i, j); // �׿ܴ� ���� ��
			//	cvSet2D(mix, i, j, temp);
			//}
		}
	}
	return tempImage;
}