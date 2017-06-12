#include <opencv/cv.h>
#include <opencv/highgui.h>

int main() {
	IplImage* lena = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // 기존 이미지 로드
	IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_COLOR); // 합성할 이미지 로드
	IplImage* mix = cvCreateImage(cvGetSize(lena), lena->depth, lena->nChannels); // 합성된 이미지 생성

	int i, j;
	CvScalar pixelValue, temp;

	for (i = 0; i < lena->height; i++) {
		for (j = 0; j < lena->width; j++) {
			pixelValue = cvGet2D(heart, i, j); // 합성할 이미지의 색 얻기

			if (pixelValue.val[0] < 240) {
				temp = cvGet2D(heart, i, j); // 합성할 이미지 보다 어두우면 그 색을 설정
				cvSet2D(mix, i, j, temp);
			}
			else {
				temp = cvGet2D(lena, i, j); // 그외는 원본 값
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