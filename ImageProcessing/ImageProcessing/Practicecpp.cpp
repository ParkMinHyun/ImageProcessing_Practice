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
/* 영상 히스토그램 
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
*/
/* 칼라 히스토그램 
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

int main() {
	int i, j, value;
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage* histogram_R = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3); // 칼라 이미지 히스토그램 생성
	IplImage* histogram_G = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	IplImage* histogram_B = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);

	CvScalar temp;

	double HIST_R[HISTOGRAM_SIZE], HIST_G[HISTOGRAM_SIZE], HIST_B[HISTOGRAM_SIZE];
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // 히스토그램 배열 초기화
		HIST_R[i] = LOW;
		HIST_G[i] = LOW;
		HIST_B[i] = LOW;
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // 빈도수 조사
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);

			HIST_R[(int)temp.val[2]]++; // R
			HIST_G[(int)temp.val[1]]++; // G
			HIST_B[(int)temp.val[0]]++; // B
		}
	}

	MAX = HIST_R[0]; // R히스토그램 그리기
	MIN = HIST_R[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST_R[i] > MAX) MAX = HIST_R[i]; // 정규화를 위한 최대 최소 구하기
		if (HIST_R[i] < MIN) MIN = HIST_R[i];
	}

	DIF = MAX - MIN; // 최대값과 최소값의 빈도수 차이

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_R[i] - MIN) * HIGH / DIF); // 정규화
	}

	cvSet(histogram_R, cvScalar(255, 255, 255)); // 배경 흰색으로

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // 히스토그램의 값은 검은색으로 출력
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogram_R, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) { // 히스토그램의 아래부분의 색을 표시
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogram_R, i, j, cvScalar(0, 0, j));
		}
	}

	MAX = HIST_G[0]; // G히스토그램 그리기
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
	MIN = HIST_B[0]; // B히스토그램 그리기

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
/*히스토그램 함수화
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
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1); // 가로 256, 세로 276

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE]; // 히스토그램 배열선언
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // 히스토그램 배열 0으로 초기화

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) { // 빈도수 조사
			temp = cvGet2D(inputImage, i, j);
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
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN) * HIGH / DIF);
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

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);
}
*/
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

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // 히스토그램 초기화

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) { // 1단계 각 명암 값에 대한 빈도수 계산
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) { // 2단계 각 명암 값 빈도수의 누적합 계산
		SUM = SUM + HIST[i];
		sum_of_HIST[i] = SUM;
	}

	for (i = 0; i < inputImage->height; i++) { // 명암 분포가 빈약한 영상을 균일하게 만들어줌
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			cvSet2D(equalImage, i, j, cvScalar(sum_of_HIST[(int)temp.val[0]] * HIGH / (inputImage->height*inputImage->width))); // 누적 빈도수를 정규화
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

	double HIST[HISTOGRAM_SIZE]; // 히스토그램 배열선언
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW; // 히스토그램 배열 0으로 초기화

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) { // 빈도수 조사
			temp = cvGet2D(inputImage, i, j);
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
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN) * HIGH / DIF);
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

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);
}