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

	IplImage* inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // 이미지불러오기, 초기이미지
	IplImage* sumimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels); // 산술연산 이미지생성
	IplImage* subimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);
	IplImage* mulimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);
	IplImage* divimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j); // 색 반환
													//덧셈 연산
			if (pixelValue.val[0] + SUM_CONSTANT >= 255) { // 255가 맥스값
				temp.val[0] = 255;
				cvSet2D(sumimage, i, j, temp); // 색 설정
			}
			else {
				temp.val[0] = pixelValue.val[0] + SUM_CONSTANT;
				cvSet2D(sumimage, i, j, temp);
			}
			//뺄셈 연산
			if (pixelValue.val[0] - SUB_CONSTANT < 0) { // 0이 최소값
				temp.val[0] = 0;
				cvSet2D(subimage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] - SUB_CONSTANT;
				cvSet2D(subimage, i, j, temp);
			}
			//곱셈 연산
			if (pixelValue.val[0] * MUL_CONSTANT >= 255) {
				temp.val[0] = 255;
				cvSet2D(mulimage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] * MUL_CONSTANT;
				cvSet2D(mulimage, i, j, temp);
			}
			//나눗셈 연산
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

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // 창 생성
	cvNamedWindow("sum image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sub image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mul image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("div image", CV_WINDOW_AUTOSIZE);

	cvShowImage("input image", inputimage); // 창과 이미지 연결
	cvShowImage("sum image", sumimage);
	cvShowImage("sub image", subimage);
	cvShowImage("mul image", mulimage);
	cvShowImage("div image", divimage);

	cvWaitKey(); // 키 엽력 대기

	cvDestroyWindow("inputimage"); // 창 부수기
	cvDestroyWindow("sumimage");
	cvDestroyWindow("subimage");
	cvDestroyWindow("mulimage");
	cvDestroyWindow("divimage");

	cvReleaseImage(&inputimage); // 포인터 해제
	cvReleaseImage(&sumimage);
	cvReleaseImage(&subimage);
	cvReleaseImage(&mulimage);
	cvReleaseImage(&divimage);

	return 0;
}
*/

/* 영상 반전
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
			temp.val[0] = 255 - pixelValue.val[0]; // 영상 반전
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

/*감마 보정
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
			temp.val[0] = pow(pixelValue.val[0], 1 / GAMMA_CONSTANT); // 감마 보정

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

/*이진화
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

			if (pixelValue.val[0] >= BINARY_THRESHOLD) { // 이진화 경계 값을 이용해 값이 두개만 있는 영상으로 변환
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

/*범위 강조
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

			if (pixelValue.val[0] >= STRESS_START_POINT && pixelValue.val[0] <= STRESS_END_POINT) { // 범위 강조 변환 일정 범위의 화소만 강조
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
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1); // 히스토그램 이미지 생성

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE]; // 히스토그램 배열선언
	unsigned char scale_HIST[HISTOGRAM_SIZE]; // 누적합 배열 선언
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // 히스토그램 배열 0으로 초기화

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j); // 빈도수 조사
			value = (int)temp.val[0];
			HIST[value]++;
		}
	}

	MAX = HIST[0];
	MIN = HIST[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // 정규화를 위한 최대 최소값 구하기
		if (HIST[i] > MAX) MAX = HIST[i];
		if (HIST[i] < MIN) MIN = HIST[i];
	}

	DIF = MAX - MIN; // 최대값과 최소값의 차이

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN) * HIGH / DIF); // 기본 명암 대비 스트레칭
	}

	cvSet(histogramImage, cvScalar(255)); // 배경은 흰색

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage, HISTOGRAM_SIZE - j - 1, i, cvScalar(0)); // 히스토그램의 값은 검은색으로 출력
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) { //아래 부분에 히스토그램의 색을 표시
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