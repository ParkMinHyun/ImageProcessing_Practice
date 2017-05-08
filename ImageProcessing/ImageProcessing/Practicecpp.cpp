/*
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#define SUM_CONSTANT 50
#define SUB_CONSTANT 50
#define MUL_CONSTANT 5
#define DIV_CONSTANT 5

int main() {
	int i, j;

	IplImage* inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // �̹����ҷ�����, �ʱ��̹���
	IplImage* sumimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels); // ������� �̹�������
	IplImage* subimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);
	IplImage* mulimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);
	IplImage* divimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j); // �� ��ȯ
													//���� ����
			if (pixelValue.val[0] + SUM_CONSTANT >= 255) { // 255�� �ƽ���
				temp.val[0] = 255;
				cvSet2D(sumimage, i, j, temp); // �� ����
			}
			else {
				temp.val[0] = pixelValue.val[0] + SUM_CONSTANT;
				cvSet2D(sumimage, i, j, temp);
			}
			//���� ����
			if (pixelValue.val[0] - SUB_CONSTANT < 0) { // 0�� �ּҰ�
				temp.val[0] = 0;
				cvSet2D(subimage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] - SUB_CONSTANT;
				cvSet2D(subimage, i, j, temp);
			}
			//���� ����
			if (pixelValue.val[0] * MUL_CONSTANT >= 255) {
				temp.val[0] = 255;
				cvSet2D(mulimage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] * MUL_CONSTANT;
				cvSet2D(mulimage, i, j, temp);
			}
			//������ ����
			if (pixelValue.val[0] / DIV_CONSTANT < 0) {
				temp.val[0] = 0;
				cvSet2D(divimage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] / DIV_CONSTANT;
				cvSet2D(divimage, i, j, temp);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // â ����
	cvNamedWindow("sum image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sub image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mul image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("div image", CV_WINDOW_AUTOSIZE);

	cvShowImage("input image", inputimage); // â�� �̹��� ����
	cvShowImage("sum image", sumimage);
	cvShowImage("sub image", subimage);
	cvShowImage("mul image", mulimage);
	cvShowImage("div image", divimage);

	cvWaitKey(); // Ű ���� ���

	cvDestroyWindow("inputimage"); // â �μ���
	cvDestroyWindow("sumimage");
	cvDestroyWindow("subimage");
	cvDestroyWindow("mulimage");
	cvDestroyWindow("divimage");

	cvReleaseImage(&inputimage); // ������ ����
	cvReleaseImage(&sumimage);
	cvReleaseImage(&subimage);
	cvReleaseImage(&mulimage);
	cvReleaseImage(&divimage);

	return 0;
}
*/

/* ���� ����
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

int main() {
	int i, j;

	IplImage* inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++)
	{
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);
			temp.val[0] = 255 - pixelValue.val[0]; // ���� ����
			cvSet2D(outputimage, i, j, temp);
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvWaitKey();

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
*/

/*���� ����
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#define GAMMA_CONSTANT 0.85

int main() {
	int i, j;

	IplImage* inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++)
	{
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);
			temp.val[0] = pow(pixelValue.val[0], 1 / GAMMA_CONSTANT); // ���� ����

			if (temp.val[0] < 0) {
				temp.val[0] = 0;
				cvSet2D(outputimage, i, j, temp);
			}
			else if (temp.val[0] > 255) {
				temp.val[0] = 255;
				cvSet2D(outputimage, i, j, temp);
			}
			else {
				cvSet2D(outputimage, i, j, temp);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvWaitKey();

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
*/

/*����ȭ
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#define BINARY_THRESHOLD 130

int main() {
	int i, j;

	IplImage* inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++)
	{
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);

			if (pixelValue.val[0] >= BINARY_THRESHOLD) { // ����ȭ ��� ���� �̿��� ���� �ΰ��� �ִ� �������� ��ȯ
				temp.val[0] = 255;
				cvSet2D(outputimage, i, j, temp);
			}
			else {
				temp.val[0] = 0;
				cvSet2D(outputimage, i, j, temp);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvWaitKey();

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
*/

/*���� ����
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#define STRESS_START_POINT 100
#define STRESS_END_POINT 150

int main() {
	int i, j;

	IplImage* inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++)
	{
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);

			if (pixelValue.val[0] >= STRESS_START_POINT && pixelValue.val[0] <= STRESS_END_POINT) { // ���� ���� ��ȯ ���� ������ ȭ�Ҹ� ����
				temp.val[0] = 255;
				cvSet2D(outputimage, i, j, temp);
			}
			else {
				cvSet2D(outputimage, i, j, pixelValue);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvWaitKey();

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

int main() {
	int i, j, value;
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1); // ������׷� �̹��� ����

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE]; // ������׷� �迭����
	unsigned char scale_HIST[HISTOGRAM_SIZE]; // ������ �迭 ����
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // ������׷� �迭 0���� �ʱ�ȭ

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j); // �󵵼� ����
			value = (int)temp.val[0];
			HIST[value]++;
		}
	}

	MAX = HIST[0];
	MIN = HIST[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // ����ȭ�� ���� �ִ� �ּҰ� ���ϱ�
		if (HIST[i] > MAX) MAX = HIST[i];
		if (HIST[i] < MIN) MIN = HIST[i];
	}

	DIF = MAX - MIN; // �ִ밪�� �ּҰ��� ����

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN) * HIGH / DIF); // �⺻ ��� ��� ��Ʈ��Ī
	}

	cvSet(histogramImage, cvScalar(255)); // ����� ���

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage, HISTOGRAM_SIZE - j - 1, i, cvScalar(0)); // ������׷��� ���� ���������� ���
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) { //�Ʒ� �κп� ������׷��� ���� ǥ��
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogramImage, i, j, cvScalar(j));
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("histogramImage", histogramImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&histogramImage);
	cvReleaseImage(&inputImage);

	return 0;
}