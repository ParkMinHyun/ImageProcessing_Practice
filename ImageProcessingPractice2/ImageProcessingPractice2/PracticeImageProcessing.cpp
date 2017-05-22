/*유사 연산자 기법
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* HomogenProcess(IplImage* inputImage);
double ABS(double x);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* ResultImage = NULL;

	ResultImage = HomogenProcess(inputImage);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", ResultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&ResultImage);
	cvReleaseImage(&inputImage);
}

double ABS(double x) { // 절대값 함수
	if (x >= 0) return x;
	else return -x;
}

IplImage* HomogenProcess(IplImage* inputImage) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Max = 0.0, temp;
	CvScalar tempScalar, ceterScalar;

	cvSetZero(tempinputImage); // 경계처리는 0을 삽입, temp이미지 검은색으로 채움

	for (i = 0; i < inputImage->height; i++) { // temp 이미지에 인풋 이미지 복사
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // 컨벌루션 연산
		for (j = 0; j < inputImage->width; j++) {
			ceterScalar = cvGet2D(tempinputImage, i + 1, j + 1);
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // 마스크와 연산하면서 Sum에 누적
					tempScalar = cvGet2D(tempinputImage, i + n, j + m); // 이웃값
					temp = ABS(ceterScalar.val[0] - tempScalar.val[0]); // 이웃 값들과의 차를 구한뒤 절대값
					if (Max < temp)
						Max = temp; // 최대값
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Max)); // 결과값을 아웃풋 이미지에 넣음
			Max = 0.0;
		}
	}
	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*라플라시안
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* LaplaImage_1 = NULL;
	IplImage* LaplaImage_2 = NULL;

	double LaplaMask_1[3][3] = { { 0.,-1.,-0. },{ -1.,4.,-1. },{ 0.,-1.,0. } }; // 라플라시안
	double LaplaMask_2[3][3] = { { -1.,-1.,-1. },{ -1.,8.,-1. },{ -1.,-1.,-1. } };

	LaplaImage_1 = ConvolutionProcess(inputImage, LaplaMask_1);
	LaplaImage_2 = ConvolutionProcess(inputImage, LaplaMask_2);

	cvShowImage("input Image", inputImage);
	cvShowImage("LaplaImage_1 Image", LaplaImage_1);
	cvShowImage("LaplaImage_2 Image", LaplaImage_2);

	cvWaitKey();
	cvDestroyAllWindows();

	cvReleaseImage(&LaplaImage_1);
	cvReleaseImage(&LaplaImage_2);
	cvReleaseImage(&inputImage);
}

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // 경계처리는 0을 삽입, temp이미지 검은색으로 채움

	for (i = 0; i < inputImage->height; i++) { // temp 이미지에 인풋 이미지 복사
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // 컨벌루션 연산
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // 마스크와 연산하면서 Sum에 누적
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // 결과값을 아웃풋 이미지에 넣음
			Sum = 0.0;
		}
	}
	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*Canny 에지 검출
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW_THRESHOLD 30 // HIGH를 LOW의 2~3배로 사용하는 것을 권장
#define HIGH_THRESHOLD 30 * 2.5

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* CannyEdgeImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	cvCanny(inputImage, CannyEdgeImage, LOW_THRESHOLD, HIGH_THRESHOLD); // 케니 함수

	cvShowImage("input Image", inputImage);
	cvShowImage("CannyEdge Image", CannyEdgeImage);

	cvWaitKey();
	cvDestroyAllWindows();

	cvReleaseImage(&CannyEdgeImage);
	cvReleaseImage(&inputImage);
}

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // 경계처리는 0을 삽입, temp이미지 검은색으로 채움

	for (i = 0; i < inputImage->height; i++) { // temp 이미지에 인풋 이미지 복사
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // 컨벌루션 연산
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // 마스크와 연산하면서 Sum에 누적
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // 결과값을 아웃풋 이미지에 넣음
			Sum = 0.0;
		}
	}
	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*로버츠 마스크
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* SumImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* RowImage = NULL;
	IplImage* ColImage = NULL;

	//double RowMask[3][3] = { {-1.,0.,0.},{0.,1.,0.},{0.,0.,0.} }; // 로버츠
	//double ColMask[3][3] = { {0.,0.,-1.},{0.,1.,0.},{0.,0.,0.} };
	//double freeRowMask[3][3] = { {-1.,-1.,-1.},{0.,0.,0.},{1.,1.,1.} }; // 프리윗
	//double freeColMask[3][3] = { {1.,0.,-1.},{1.,0.,-1.},{1.,0.,-1.} };
	double soRowMask[3][3] = { { -1.,-2.,-1 },{ 0.,0.,0. },{ 1.,2.,1. } }; // 소벨
	double soColMask[3][3] = { { 1.,0.,-1. },{ 2.,0.,-2. },{ 1.,0.,-1. } };

	int i, j;
	CvScalar horizontemp, vertical;

	//RowImage = ConvolutionProcess(inputImage, RowMask); // 로버츠
	//ColImage = ConvolutionProcess(inputImage, ColMask);
	//RowImage = ConvolutionProcess(inputImage, freeRowMask); // 프리윗
	//ColImage = ConvolutionProcess(inputImage, freeColMask);
	RowImage = ConvolutionProcess(inputImage, soRowMask); // 소벨
	ColImage = ConvolutionProcess(inputImage, soColMask);

	cvOr(RowImage, ColImage, SumImage); // 두개 이미지 합치는 함수

	cvShowImage("input Image", inputImage);
	cvShowImage("RowEdge Image", RowImage);
	cvShowImage("ColEdge Image", ColImage);
	cvShowImage("Sum Image", SumImage);

	cvWaitKey();
	cvDestroyAllWindows();

	cvReleaseImage(&RowImage);
	cvReleaseImage(&ColImage);
	cvReleaseImage(&SumImage);
	cvReleaseImage(&inputImage);
}

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // 경계처리는 0을 삽입, temp이미지 검은색으로 채움

	for (i = 0; i < inputImage->height; i++) { // temp 이미지에 인풋 이미지 복사
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // 컨벌루션 연산
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // 마스크와 연산하면서 Sum에 누적
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // 결과값을 아웃풋 이미지에 넣음
			Sum = 0.0;
		}
	}
	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*이동*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define H_POS 30
#define W_POS 130

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputImage = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);

	int i, j;

	cvSetZero(outputImage);

	for (i = 0; i < inputImage->height - H_POS; i++) {
		for (j = 0; j < inputImage->width - W_POS; j++) {
			cvSet2D(outputImage, i + H_POS, j + W_POS, cvGet2D(inputImage, i, j));
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