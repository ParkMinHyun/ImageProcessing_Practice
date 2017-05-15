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
/* ���� ������׷� 
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
*/
/* Į�� ������׷� 
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

int main() {
	int i, j, value;
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage* histogram_R = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3); // Į�� �̹��� ������׷� ����
	IplImage* histogram_G = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	IplImage* histogram_B = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);

	CvScalar temp;

	double HIST_R[HISTOGRAM_SIZE], HIST_G[HISTOGRAM_SIZE], HIST_B[HISTOGRAM_SIZE];
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // ������׷� �迭 �ʱ�ȭ
		HIST_R[i] = LOW;
		HIST_G[i] = LOW;
		HIST_B[i] = LOW;
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // �󵵼� ����
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);

			HIST_R[(int)temp.val[2]]++; // R
			HIST_G[(int)temp.val[1]]++; // G
			HIST_B[(int)temp.val[0]]++; // B
		}
	}

	MAX = HIST_R[0]; // R������׷� �׸���
	MIN = HIST_R[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST_R[i] > MAX) MAX = HIST_R[i]; // ����ȭ�� ���� �ִ� �ּ� ���ϱ�
		if (HIST_R[i] < MIN) MIN = HIST_R[i];
	}

	DIF = MAX - MIN; // �ִ밪�� �ּҰ��� �󵵼� ����

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_R[i] - MIN) * HIGH / DIF); // ����ȭ
	}

	cvSet(histogram_R, cvScalar(255, 255, 255)); // ��� �������

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // ������׷��� ���� ���������� ���
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogram_R, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) { // ������׷��� �Ʒ��κ��� ���� ǥ��
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogram_R, i, j, cvScalar(0, 0, j));
		}
	}

	MAX = HIST_G[0]; // G������׷� �׸���
	MIN = HIST_G[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST_G[i] > MAX) MAX = HIST_G[i];
		if (HIST_G[i] < MIN) MIN = HIST_G[i];
	}

	DIF = MAX - MIN;

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_G[i] - MIN) * HIGH / DIF);
	}

	cvSet(histogram_G, cvScalar(255, 255, 255));

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogram_G, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogram_G, i, j, cvScalar(0, j, 0));
		}
	}

	MAX = HIST_B[0];
	MIN = HIST_B[0]; // B������׷� �׸���

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST_B[i] > MAX) MAX = HIST_B[i];
		if (HIST_B[i] < MIN) MIN = HIST_B[i];
	}

	DIF = MAX - MIN;

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_B[i] - MIN) * HIGH / DIF);
	}

	cvSet(histogram_B, cvScalar(255, 255, 255));

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogram_B, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogram_B, i, j, cvScalar(j, 0, 0));
		}
	}

	cvShowImage("input image", inputImage);
	cvShowImage("histogram_R", histogram_R);
	cvShowImage("histogram_G", histogram_G);
	cvShowImage("histogram_B", histogram_B);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&histogram_R);
	cvReleaseImage(&histogram_G);
	cvReleaseImage(&histogram_B);
	cvReleaseImage(&inputImage);

	return 0;
}
*/
/*������׷� �Լ�ȭ
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

void Show_histogram(IplImage* img, char* imgWindowName, char* histogramWindowName);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1);

	Show_histogram(inputImage, "imgWindowName", "histogramImage");

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&histogramImage);
	cvReleaseImage(&inputImage);

	return 0;
}

void Show_histogram(IplImage* img, char* imgWindowName, char* histogramWindowName) {
	int i, j, value;
	IplImage* inputImage = img;
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1); // ���� 256, ���� 276

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE]; // ������׷� �迭����
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // ������׷� �迭 0���� �ʱ�ȭ

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) { // �󵵼� ����
			temp = cvGet2D(inputImage, i, j);
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
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN) * HIGH / DIF);
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

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);
}
*/
/*������׷� ��Ȱȭ
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

void Show_histogram(IplImage* img, char* imgWindowName, char* histogramWindowName);

int main() {
	int i, j, value;
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* equalImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE];
	double sum_of_HIST[HISTOGRAM_SIZE];
	double SUM = 0.0;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // ������׷� �ʱ�ȭ

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) { // 1�ܰ� �� ��� ���� ���� �󵵼� ���
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // 2�ܰ� �� ��� �� �󵵼��� ������ ���
		SUM = SUM + HIST[i];
		sum_of_HIST[i] = SUM;
	}

	for (i = 0; i < inputImage->height; i++) { // ��� ������ ����� ������ �����ϰ� �������
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			cvSet2D(equalImage, i, j, cvScalar(sum_of_HIST[(int)temp.val[0]] * HIGH / (inputImage->height*inputImage->width))); // ���� �󵵼��� ����ȭ
		}
	}

	Show_histogram(inputImage, "input image", "input histogram");
	Show_histogram(equalImage, "Equal image", "Equal histogram");

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&equalImage);
	cvReleaseImage(&inputImage);

	return 0;
}

void Show_histogram(IplImage* img, char* imgWindowName, char* histogramWindowName) {
	int i, j, value;
	IplImage* inputImage = img;
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1);

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE]; // ������׷� �迭����
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // ������׷� �迭 0���� �ʱ�ȭ

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) { // �󵵼� ����
			temp = cvGet2D(inputImage, i, j);
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
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN) * HIGH / DIF);
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

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);
}
*/
/*�������� 1 - �ռ�
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main() {
	IplImage* moonsu = cvLoadImage("moonsu.jpg", CV_LOAD_IMAGE_COLOR); // ���� �̹��� �ε�
	IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_COLOR); // �ռ��� �̹��� �ε�
	IplImage* mix = cvCreateImage(cvGetSize(moonsu), moonsu->depth, moonsu->nChannels); // �ռ��� �̹��� ����

	int i, j;
	CvScalar pixelValue, temp;

	for (i = 0; i < moonsu->height; i++) {
		for (j = 0; j < moonsu->width; j++) {
			pixelValue = cvGet2D(heart, i, j); // �ռ��� �̹����� �� ���

			if (pixelValue.val[0] < 240) {
				temp = cvGet2D(heart, i, j); // �ռ��� �̹��� ���� ��ο�� �� ���� ����
				cvSet2D(mix, i, j, temp);
			}
			else {
				temp = cvGet2D(moonsu, i, j); // �׿ܴ� ���� ��
				cvSet2D(mix, i, j, temp);
			}
		}
	}

	cvNamedWindow("moonsu image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("heart image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mix image", CV_WINDOW_AUTOSIZE);

	cvShowImage("moonsu image", moonsu);
	cvShowImage("heart image", heart);
	cvShowImage("mix image", mix);

	cvWaitKey();

	cvDestroyWindow("moonsu image");
	cvDestroyWindow("heart image");
	cvDestroyWindow("mix image");

	cvReleaseImage(&moonsu);
	cvReleaseImage(&heart);
	cvReleaseImage(&mix);

	return 0;
}*/
/*������׷� ��ȭ
#include <opencv/cv.h>
#include <opencv/highgui.h> // opencv ���̺귯��

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256 // ���� �����

void Show_histogram(IplImage* img, char* imgWindowName, char* histogramWindowName); // �Լ�����

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // ��ǲ �̹��� �ε�
	IplImage* targetImage = cvLoadImage("lawn.jpg", CV_LOAD_IMAGE_GRAYSCALE); // Ÿ�� �̹��� �ε�
	IplImage* specImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels); // ��ȭ�� �̹��� ����

	int i, j, value;
	double in_SUM = 0.0;
	double tar_SUM = 0.0;

	CvScalar temp; // ��Į�� ����

	double inputHist[HISTOGRAM_SIZE]; // ��ǲ�̹��� �󵵼�
	int inputEqHist[HISTOGRAM_SIZE]; // ��ǲ�̹��� ��Ȱȭ
	double targetHist[HISTOGRAM_SIZE]; // Ÿ���̹��� �󵵼�
	int targetEqHist[HISTOGRAM_SIZE]; // Ÿ���̹��� ��Ȱȭ
	int RevHIST[HISTOGRAM_SIZE]; // ����Ȱȭ

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // ������׷� �ʱ�ȭ
		inputHist[i] = LOW;
		targetHist[i] = LOW;
	}

	for (i = 0; i < inputImage->height; i++) { // ��ǲ�̹��� ���� ���� �󵵼�
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			inputHist[value]++;
		}
	}

	for (i = 0; i < targetImage->height; i++) { // Ÿ���̹��� ���� ���� �󵵼�
		for (j = 0; j < targetImage->width; j++) {
			temp = cvGet2D(targetImage, i, j);
			value = (int)temp.val[0];
			targetHist[value]++;
		}
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // ��Ȱȭ
		in_SUM = in_SUM + inputHist[i]; // ��ǲ�̹��� �󵵼� ������
		inputEqHist[i] = (int)(in_SUM * HIGH / (inputImage->height * inputImage->width)); // ����ȭ�� ������
		tar_SUM = tar_SUM + targetHist[i]; // Ÿ���̹��� �󵵼� ������
		targetEqHist[i] = (int)(tar_SUM * HIGH / (targetImage->height * targetImage->width)); // ����ȭ�� ������ 
	}

	value = targetEqHist[0]; // ����Ȱȭ ���̺�
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			if (i == targetEqHist[j]) {
				value = j;
				break;
			}
		}
		RevHIST[i] = value;
	}

	for (i = 0; i < inputImage->height; i++) { // ��ȭ �Է� �̹����� �� �̹����� ������ �����ϸ鼭 Ÿ�� �̹����� ����� ������׷����� ����
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			cvSet2D(specImage, i, j, cvScalar(RevHIST[(int)temp.val[0]]));
		}
	}

	Show_histogram(inputImage, "input image", "input histogram");
	Show_histogram(targetImage, "target image", "target histogram");
	Show_histogram(specImage, "spec image", "spec histogram");

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&targetImage);
	cvReleaseImage(&inputImage);

	return 0;
}

void Show_histogram(IplImage* img, char* imgWindowName, char* histogramWindowName) {
	int i, j, value;
	IplImage* inputImage = img;
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1); // ���� 256, ���� 276

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE]; // ������׷� �迭����
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // ������׷� �迭 0���� �ʱ�ȭ

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) { // �󵵼� ����
			temp = cvGet2D(inputImage, i, j);
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
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN) * HIGH / DIF); // ����ȭ
	}

	cvSet(histogramImage, cvScalar(255)); // ����� ���

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage, HISTOGRAM_SIZE - j - 1, i, cvScalar(0)); // ������׷��� ���� ���������� ��� // �ؿ������� �׸���
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) { //�Ʒ� �κп� ������׷��� ���� ǥ��
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogramImage, i, j, cvScalar(j));
		}
	}

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);
}
*/
/*����
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* ResultImage = NULL;

	double BlurringMask[3][3] = { { 1 / 9.,1 / 9.,1 / 9. },{ 1 / 9.,1 / 9., 1 / 9. },{ 1 / 9.,1 / 9.,1 / 9. } };

	ResultImage = ConvolutionProcess(inputImage, BlurringMask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", ResultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&ResultImage);
}

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // ���ó���� 0�� ����, temp�̹��� ���������� ä��

	for (i = 0; i < inputImage->height; i++) { // temp �̹����� ��ǲ �̹��� ����
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // ������� ����
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // ����ũ�� �����ϸ鼭 Sum�� ����
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // ������� �ƿ�ǲ �̹����� ����
			Sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*����þ� ���͸�
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* ResultImage = NULL;

	double GaussianMask[3][3] = { { 1 / 16.,1 / 8.,1 / 16. },{ 1 / 8.,1 / 4.,1 / 8. },{ 1 / 16.,1 / 8.,1 / 16. } };

	ResultImage = ConvolutionProcess(inputImage, GaussianMask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", ResultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&ResultImage);
}

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // ���ó���� 0�� ����, temp�̹��� ���������� ä��

	for (i = 0; i < inputImage->height; i++) { // temp �̹����� ��ǲ �̹��� ����
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // ������� ����
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // ����ũ�� �����ϸ鼭 Sum�� ����
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // ������� �ƿ�ǲ �̹����� ����
			Sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*������ ��� ����
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* ResultImage = NULL;

	double HPF_Mask[3][3] = { { -1 / 9.,-1 / 9.,-1 / 9. },{ -1 / 9.,8 / 9.,-1 / 9. },{ -1 / 9.,-1 / 9.,-1 / 9. } };

	ResultImage = ConvolutionProcess(inputImage, HPF_Mask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image1", ResultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&ResultImage);
}

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // ���ó���� 0�� ����, temp�̹��� ���������� ä��

	for (i = 0; i < inputImage->height; i++) { // temp �̹����� ��ǲ �̹��� ����
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // ������� ����
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // ����ũ�� �����ϸ鼭 Sum�� ����
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // ������� �ƿ�ǲ �̹����� ����
			Sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*������ ��� ����
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define ALPHA 2

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* tempImage = NULL;
	IplImage* ResultImage_1 = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* ResultImage_2 = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	double LPF_Mask[3][3] = { { 1 / 9.,1 / 9.,1 / 9. },{ 1 / 9.,1 / 9.,1 / 9. },{ 1 / 9.,1 / 9.,1 / 9. } };
	int i, j;
	CvScalar inputPixel, tempPixel;

	tempImage = ConvolutionProcess(inputImage, LPF_Mask);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			inputPixel = cvGet2D(inputImage, i, j);
			tempPixel = cvGet2D(tempImage, i, j);

			cvSet2D(ResultImage_1, i, j, cvScalar(inputPixel.val[0] - tempPixel.val[0])); // Unsharp Masking = (�� ����) - (������ ��� ���͸� ��� ����)
			cvSet2D(ResultImage_2, i, j, cvScalar(ALPHA * inputPixel.val[0] - tempPixel.val[0])); // High-Boost = a (�� ����) - (������ ��� ���͸� ��� ����)
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image1", ResultImage_1);
	cvShowImage("Result Image2", ResultImage_2);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&ResultImage_1);
	cvReleaseImage(&ResultImage_2);
	cvReleaseImage(&inputImage);
}

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // ���ó���� 0�� ����, temp�̹��� ���������� ä��

	for (i = 0; i < inputImage->height; i++) { // temp �̹����� ��ǲ �̹��� ����
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // ������� ����
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // ����ũ�� �����ϸ鼭 Sum�� ����
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // ������� �ƿ�ǲ �̹����� ����
			Sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/

/*������ �̿� ȭ�Ұ� ������
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define ZOOM_RATE 2 // ���� Ȯ�� ����

int main() {
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputImage = cvCreateImage(cvSize(inputImage->width * ZOOM_RATE, inputImage->height * ZOOM_RATE), 8, 1);

	for (i = 0; i < outputImage->height; i++) {
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvGet2D(inputImage, i / ZOOM_RATE, j / ZOOM_RATE));
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage);

	return 0;
}
*/

/*�缱�� ȭ�� ������
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define ZOOM_RATE 2.0 // Ȯ�� ����

int main() {
	int i, j, i_H, i_W;
	double r_H, r_W, s_H, s_W;
	CvScalar C1, C2, C3, C4, newValue;

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize(inputImage->width * ZOOM_RATE, inputImage->height * ZOOM_RATE), 8, 1);

	for (i = 0; i < outputImage->height; i++) {
		for (j = 0; j < outputImage->width; j++) {
			r_H = i / ZOOM_RATE; // ���������� ���ÿ��󿡼� ��Ȯ�� ��ǥ
			r_W = j / ZOOM_RATE;

			i_H = (int)r_H; // �Ҽ��� ����
			i_W = (int)r_W;

			s_H = r_H - i_H; // �Ҽ��� ���� �� ����
			s_W = r_W - i_W;

			if (i_H >= (inputImage->height - 1) || i_W >= (inputImage->width - 1)) { // ���� ���� ���ó��
				cvSet2D(outputImage, i, j, cvScalar(0));
			}
			else { // �缱�� ������ ���
				C1 = cvGet2D(inputImage, i_H, i_W);
				C2 = cvGet2D(inputImage, i_H, i_W + 1);
				C3 = cvGet2D(inputImage, i_H + 1, i_W + 1);
				C4 = cvGet2D(inputImage, i_H + 1, i_W);
				newValue.val[0] = (C1.val[0] * (1 - s_W)*(1 - s_H) + C2.val[0] * s_W * (1 - s_H) * C3.val[0] * s_W * s_H + C4.val[0] * (1 - s_W) * s_H);
				cvSet2D(outputImage, i, j, newValue);
			}
		}
	}

	cvShowImage("Input Image", inputImage);
	cvShowImage("Output Image", outputImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage);

	return 0;
}
*/

/*�̵�� �� ����*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define SUB_SAMPLING_RATE 2 // ��� ����

void Swap(double *a, double *b); // ������ ��ȯ
void BubbleSort(double *A, int MAX); // ������ ����

int main() {
	int i, j, n, m, k, index = 0;
	double *Mask, *OutputValue;
	CvScalar tempScalar;

	Mask = new double[SUB_SAMPLING_RATE * SUB_SAMPLING_RATE]; // ����ũ ũ��

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize((inputImage->width + 1) / SUB_SAMPLING_RATE, (inputImage->height + 1) / SUB_SAMPLING_RATE), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + 1, inputImage->height + 1), 8, 1);

	OutputValue = new double[(inputImage->width + 1) / SUB_SAMPLING_RATE*(inputImage->height + 1) / SUB_SAMPLING_RATE];
	cvSetZero(tempImage);

	for (i = 0; i < inputImage->height; i++) { // ��ǲ�̹��� temp�� �ű�
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempImage, i, j, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i = i + SUB_SAMPLING_RATE) {
		for (j = 0; j < inputImage->width; j = j + SUB_SAMPLING_RATE) {
			for (n = 0; n < SUB_SAMPLING_RATE; n++) {
				for (m = 0; m < SUB_SAMPLING_RATE; m++) {
					tempScalar = cvGet2D(tempImage, i + n, j + m);
					Mask[n*SUB_SAMPLING_RATE + m] = tempScalar.val[0]; // ����ũ ������ ȭ�Ұ��� �迭 ����
				}
			}
			BubbleSort(Mask, SUB_SAMPLING_RATE * SUB_SAMPLING_RATE); // ����ũ �迭 ���� ����
			OutputValue[index++] = Mask[(int)(SUB_SAMPLING_RATE * SUB_SAMPLING_RATE / 2)]; // OutputValue ��Ŀ� �߰����� ���
		}
	}

	for (i = 0; i < outputImage->height; i++) { // OutputValue ��� ���� outputImage�� �Է�
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvScalar(OutputValue[i*outputImage->width + j]));
		}
	}
	cvShowImage("Input Image", inputImage);
	cvShowImage("Output Image", outputImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage);

	return 0;
}

void Swap(double *a, double *b) { // ������ ��ȯ
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(double *A, int MAX) { // ������ ����
	int i, j;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				Swap(&A[j], &A[j + 1]);
			}
		}
	}
}