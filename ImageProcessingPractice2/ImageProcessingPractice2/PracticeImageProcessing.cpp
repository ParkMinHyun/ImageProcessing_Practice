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
/*이동
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
*/

/*고주파 통과 필터링
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main() {
	int i, j, n, m;
	CvScalar tempValue;
	double filter[3][3] = { { -1./9.,-1./9., -1./9. },{ -1./9.,8./9.,-1./9.},{ -1./9.,-1./9.,-1./ 9. } };
	//double filter[3][3] = { {1. / 18.,1. / 18., 1. / 18.},{ 1. / 18., 1. / 18., 1. / 18.},{ 1. / 18., 1. / 18., 1. / 18. } };

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width+2, inputImage->height+2), 8, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), 8, 1);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			tempValue.val[0] = 0;
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue.val[0] += cvGet2D(tempImage, i + n, j + m).val[0] * filter[n][m];
				}
			}
			cvSet2D(outputImage, i, j, tempValue);
		}
	}

	for (i = 0; i < outputImage->height; i++) {
		for (j = 0; j < outputImage->width; j++) {
			tempValue.val[0] = cvGet2D(outputImage, i, j).val[0];
			if (tempValue.val[0] > 10) {
				cvSet2D(outputImage, i, j, cvScalar(tempValue.val[0]+100));
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

/*대칭
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputImage_1 = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);
	IplImage* outputImage_2 = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);
	IplImage* outputImage_3 = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);

	int i, j;

	for (i = 0; i < inputImage->height; i++) { // 좌우반전
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(outputImage_1, i, inputImage->width - j - 1, cvGet2D(inputImage, i, j));
			//cvSet2D(outputImage_1, inputImage->height - i - 1, j, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // 상하반전
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(outputImage_2, inputImage->height - i - 1, j, cvGet2D(inputImage, i, j));
		}
	}
	for (i = 0; i < inputImage->height; i++) { // 상하좌우반전
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(outputImage_3, inputImage->height - i - 1, inputImage->width - j - 1, cvGet2D(inputImage, i, j));
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image1", outputImage_1);
	cvShowImage("Output Image2", outputImage_2);
	cvShowImage("Output Image3", outputImage_3);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage_1);
	cvReleaseImage(&outputImage_2);
	cvReleaseImage(&outputImage_3);

	return 0;
}
*/
/*회전
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define DEGREE 90 // 회전 각도

IplImage *Rotation(IplImage *mainImage, IplImage *scaleDownImage);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputImage = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);


	outputImage = Rotation(inputImage, outputImage);

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage);

	return 0;
}

IplImage *Rotation(IplImage *inputImage, IplImage *outputImage) {

	int i, j, Center_y, Center_x, source_y, source_x;
	double Radian, cosR, sinR;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0; // degree 값을 radian으로 변경

	cosR = cos(Radian);
	sinR = sin(Radian);

	Center_y = inputImage->height / 2;
	Center_x = inputImage->width / 2;

	for (i = 0; i < inputImage->height; i++) { // 좌우반전
		for (j = 0; j < inputImage->width; j++) {
			source_x = (int)((j - Center_x)*cosR + (i - Center_y)*sinR + Center_x);
			source_y = (int)(-(j - Center_x)*sinR + (i - Center_y)*cosR + Center_y);

			if (source_x < 0 || source_y < 0 || source_y >= inputImage->height || source_x >= inputImage->width) {
				Value.val[0] = 0;
			}
			else Value = cvGet2D(inputImage, source_y, source_x);

			cvSet2D(outputImage, i, j, Value);
		}
	}
	return outputImage;
}
*/
/*팽창, 침식*/
/*
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define THRESHOLD 130

int main() {
	int i, j, n, m, dilationSum = 0, erosionSum = 0;

	CvScalar tempValue;
	//침식 마스크
	double erosionMask[3][3] = { { 255,255,255 },{ 255,255,255 },{ 255,255,255 } };
	//팽창 마스크
	double dilationMask[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *binaryImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), 8, 1);
	IplImage *erosionImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *dilationImage = cvCreateImage(cvGetSize(inputImage), 8, 1);

	//이진화
	for (i = 0; i < inputImage->height; i++) { // 인풋이미지 temp에 옮김
		for (j = 0; j < inputImage->width; j++) {
			tempValue = cvGet2D(inputImage, i, j);
			if (tempValue.val[0] > THRESHOLD)
				cvSet2D(binaryImage, i, j, cvScalar(255));
			else
				cvSet2D(binaryImage, i, j, cvScalar(0));
		}
	}

	//패딩만들기
	for (i = 0; i < binaryImage->height; i++) { // 인풋이미지 temp에 옮김
		for (j = 0; j < binaryImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
		}
	}

	//연산
	//패딩만들기
	for (i = 0; i < binaryImage->height; i++) { // 인풋이미지 temp에 옮김
		for (j = 0; j < binaryImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue = cvGet2D(tempImage, i + n, j + m);
					if (erosionMask[n][m] == tempValue.val[0])
						erosionSum += 1;
					if (dilationMask[n][m] == tempValue.val[0])
						dilationSum += 1;
				}
			}
			if (erosionSum == 9)
				cvSet2D(erosionImage, i, j, cvScalar(255));
			else
				cvSet2D(erosionImage, i, j, cvScalar(0));
			if (dilationSum == 9)
				cvSet2D(dilationImage, i, j, cvScalar(0));
			else
				cvSet2D(dilationImage, i, j, cvScalar(255));

			dilationSum = 0;
			erosionSum = 0;
		}
	}

	cvShowImage("binary Image", binaryImage);
	cvShowImage("Erosion Image", erosionImage);
	cvShowImage("Dilation Image", dilationImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&binaryImage);
	cvReleaseImage(&erosionImage);
	cvReleaseImage(&dilationImage);

	return 0;
}
*/
/*Open
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define THRESHOLD 130

IplImage *Erosion(IplImage *binaryImage) {
	int i, j, n, m, Erosion_Sum = 0;
	CvScalar tempValue;
	double Erosion_Mask[3][3] = { { 0,255,0 },{ 255,255,255 },{ 0,255,0 } };

	IplImage *tempImage = cvCreateImage(cvSize(binaryImage->width + 2, binaryImage->height + 2), 8, 1);
	IplImage *outputImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);

	cvSetZero(tempImage);

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
		}
	}

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue = cvGet2D(tempImage, i + n, j + m);
					if (Erosion_Mask[n][m] == 255 && Erosion_Mask[n][m] == tempValue.val[0])
						Erosion_Sum += 1;

				}
			}
			if (Erosion_Sum == 5)
				cvSet2D(outputImage, i, j, cvScalar(255));
			else {
				cvSet2D(outputImage, i, j, cvScalar(0));
			}
			Erosion_Sum = 0;
		}

	}
	cvReleaseImage(&tempImage);
	return outputImage;

}


IplImage *Dilation(IplImage *binaryImage) {
	int i, j, n, m, Dilation_Sum = 0;
	CvScalar tempValue;
	double Dilation_Mask[3][3] = { { 255,0,255 },{ 0,0,0 },{ 255,0,255 } };

	IplImage *tempImage = cvCreateImage(cvSize(binaryImage->width + 2, binaryImage->height + 2), 8, 1);
	IplImage *outputImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);

	cvSetZero(tempImage);

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
		}
	}

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue = cvGet2D(tempImage, i + n, j + m);
					if (Dilation_Mask[n][m] == 0 && Dilation_Mask[n][m] == tempValue.val[0])
						Dilation_Sum += 1;

				}
			}
			if (Dilation_Sum == 5)
				cvSet2D(outputImage, i, j, cvScalar(0));
			else {
				cvSet2D(outputImage, i, j, cvScalar(255));
			}
			Dilation_Sum = 0;
		}

	}
	cvReleaseImage(&tempImage);
	return outputImage;

}

IplImage *Open(IplImage *binaryImage) {
	IplImage *outImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);
	outImage = Erosion(outImage);
	outImage = Dilation(binaryImage);

	return outImage;
}

IplImage *gray2binaryImage(IplImage *grayImage, const int Threshold) {

	IplImage *tempImage = cvCreateImage(cvSize(grayImage->width, grayImage->height), 8, 1);
	IplImage *outImage = cvCreateImage(cvSize(grayImage->width, grayImage->height), 8, 1);
	CvScalar tempValue;
	int i, j;


	for (i = 0; i < grayImage->height; i++) {
		for (j = 0; j < grayImage->width; j++) {
			tempValue = cvGet2D(grayImage, i, j);
			if (tempValue.val[0] > THRESHOLD)
				cvSet2D(outImage, i, j, cvScalar(255));
			else
				cvSet2D(outImage, i, j, cvScalar(0));
		}
	}

	cvReleaseImage(&tempImage);

	return outImage;
}

int main() {
	int i, j, sum = 1;
	CvScalar erostempval, opentempval;

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *binaryImage;
	IplImage *OpenImage;
	IplImage *ErosionImage;
	IplImage *resultImage = cvCreateImage(cvGetSize(inputImage), 8, 1);

	cvSetZero(resultImage);
	binaryImage = gray2binaryImage(inputImage, THRESHOLD);

	ErosionImage = binaryImage;
	OpenImage = Open(ErosionImage);
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			erostempval = cvGet2D(ErosionImage, i, j);
			opentempval = cvGet2D(OpenImage, i, j);

			if (erostempval.val[0] != opentempval.val[0])
				cvSet2D(resultImage, i, j, cvScalar(255));
		}
	}


	cvShowImage("Input Image", inputImage);
	cvShowImage("Open Image", resultImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&resultImage);

	return 0;
}
*/
/*골격화*/
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>

#define THRESHOLD 130

IplImage *gray2binaryImage(IplImage *grayimage, int Threshold);
IplImage *Erosion(IplImage *binaryImage);
IplImage *Dilation(IplImage *binaryImage);
IplImage *Open(IplImage *binaryImage);

int main() {
	int i, j, sum = 1;
	CvScalar erostempval, opentempval;
	bool first = true;

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *binaryImage;
	IplImage *OpenImage;
	IplImage *ErosionImage;
	IplImage *Skeletonization = cvCreateImage(cvGetSize(inputImage), 8, 1);

	cvSetZero(Skeletonization);
	binaryImage = gray2binaryImage(inputImage, THRESHOLD);

	while (sum) {
		if (first == true) {
			ErosionImage = binaryImage;
			OpenImage = Open(ErosionImage);
			for (i = 0; i < inputImage->height; i++) {
				for (j = 0; j < inputImage->width; j++) {
					erostempval = cvGet2D(ErosionImage, i, j);
					opentempval = cvGet2D(OpenImage, i, j);

					if (erostempval.val[0] != opentempval.val[0])
						cvSet2D(Skeletonization, i, j, cvScalar(255));
				}
			}
			first = false;
		}
		else {
			ErosionImage = Erosion(ErosionImage);
			OpenImage = Open(ErosionImage);

			for (i = 0; i < inputImage->height; i++) {
				for (j = 0; j < inputImage->width; j++) {
					erostempval = cvGet2D(ErosionImage, i, j);
					opentempval = cvGet2D(OpenImage, i, j);

					if (erostempval.val[0] != opentempval.val[0])
						cvSet2D(Skeletonization, i, j, cvScalar(255));

				}
			}
		}
		sum = 0;
		for (i = 0; i < inputImage->height; i++) {
			for (j = 0; j < inputImage->width; j++) {

				sum += cvGet2D(OpenImage, i, j).val[0];
			}
			if (sum != 0)
				break;
		}
	}
	cvShowImage("Input Image", inputImage);
	cvShowImage("Skeletonization Image", Skeletonization);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&Skeletonization);

	return 0;
}


IplImage *Erosion(IplImage *binaryImage) {
	int i, j, n, m, Erosion_Sum = 0;
	CvScalar tempValue;
	double Erosion_Mask[3][3] = { { 0,255,0 },{ 255,255,255 },{ 0,255,0 } };

	IplImage *tempImage = cvCreateImage(cvSize(binaryImage->width + 2, binaryImage->height + 2), 8, 1);
	IplImage *outputImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);

	cvSetZero(tempImage);

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
		}
	}

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue = cvGet2D(tempImage, i + n, j + m);
					if (Erosion_Mask[n][m] == 255 && Erosion_Mask[n][m] == tempValue.val[0])
						Erosion_Sum += 1;

				}
			}
			if (Erosion_Sum == 5)
				cvSet2D(outputImage, i, j, cvScalar(255));
			else {
				cvSet2D(outputImage, i, j, cvScalar(0));
			}
			Erosion_Sum = 0;
		}

	}
	cvReleaseImage(&tempImage);
	return outputImage;

}


IplImage *Dilation(IplImage *binaryImage) {
	int i, j, n, m, Dilation_Sum = 0;
	CvScalar tempValue;
	double Dilation_Mask[3][3] = { { 255,0,255},{ 0,0,0 },{ 255,0,255 } };

	IplImage *tempImage = cvCreateImage(cvSize(binaryImage->width + 2, binaryImage->height + 2), 8, 1);
	IplImage *outputImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);

	cvSetZero(tempImage);

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
		}
	}

	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue = cvGet2D(tempImage, i + n, j + m);
					if (Dilation_Mask[n][m] == 0 && Dilation_Mask[n][m] == tempValue.val[0])
						Dilation_Sum += 1;

				}
			}
			if (Dilation_Sum == 5)
				cvSet2D(outputImage, i, j, cvScalar(0));
			else {
				cvSet2D(outputImage, i, j, cvScalar(255));
			}
			Dilation_Sum = 0;
		}

	}
	cvReleaseImage(&tempImage);
	return outputImage;

}

IplImage *Open(IplImage *binaryImage) {
	IplImage *outImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);
	outImage = Erosion(binaryImage);
	outImage = Dilation(outImage);

	return outImage;
}


IplImage *gray2binaryImage(IplImage *grayImage, const int Threshold) {

	IplImage *tempImage = cvCreateImage(cvSize(grayImage->width, grayImage->height), 8, 1);
	IplImage *outImage = cvCreateImage(cvSize(grayImage->width, grayImage->height), 8, 1);
	CvScalar tempValue;
	int i, j;


	for (i = 0; i < grayImage->height; i++) {
		for (j = 0; j < grayImage->width; j++) {
			tempValue = cvGet2D(grayImage, i, j);
			if (tempValue.val[0] > THRESHOLD)
				cvSet2D(outImage, i, j, cvScalar(255));
			else
				cvSet2D(outImage, i, j, cvScalar(0));
		}
	}

	cvReleaseImage(&tempImage);

	return outImage;
}
*/

/*FFT & 역FFT
#include <opencv/cv.h>
#include <opencv/highgui.h>

struct Complex {
	double Re; //Variables for real numbers 실수부
	double Im; //Variables for imaginary numbers 허수부
};

Complex **FFT; //Pointer to save FFT result

IplImage* FFT2d(IplImage* inpuImage);
void FFT1d(Complex *X, int N, int Log2N);
void Scrambling(Complex *X, int N, int Log2N);
void Butterfly(Complex *X, int N, int Log2N, int mode);
int ReverseBitOrder(int index, int Log2N);

IplImage* RFFT2d(IplImage* FFTSpectrum);
void RFFT1d(Complex *X, int N, int Log2N);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* FFTSpectrum;
	IplImage* RFFTImage;

	FFTSpectrum = FFT2d(inputImage); //Fast Fourier Transform
	RFFTImage = RFFT2d(FFTSpectrum); // Reverse 역방향 FFT

	cvShowImage("Input Image", inputImage);
	cvShowImage("FFT Spectrum", FFTSpectrum);
	cvShowImage("RFFT Image", RFFTImage);

	cvWaitKey();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&FFTSpectrum);
	cvReleaseImage(&RFFTImage);

	return 0;
}

IplImage* FFT2d(IplImage* inputImage)
{
	int i, j, row, col, Log2N, Num;
	Complex * Data;

	unsigned char **temp;
	double Value, Absol;

	CvScalar tempScalar;

	IplImage* FFTSpectrum = cvCreateImage(cvGetSize(inputImage), 8, 1);

	Num = inputImage->width;
	Log2N = 0;

	while (Num >= 2) //image Width calculation  영상의 너비 계산
	{
		Num >>= 1;
		Log2N++;
	}

	IplImage* tempImage = cvCreateImage(cvGetSize(inputImage), 8, 1); //Assign storage location

	Data = new Complex[inputImage->width];

	FFT = new Complex *[inputImage->height];
	//Arrangement for storing frequency-domain transformed images
	//주파수 영역 변환 영상을 저장하기 위한 배열
	temp = new unsigned char *[inputImage->height];

	for (i = 0; i<inputImage->height; i++) {
		FFT[i] = new Complex[inputImage->width];
		temp[i] = new unsigned char[inputImage->width];
	}

	for (i = 0; i<inputImage->height; i++) {
		for (j = 0; j<inputImage->width; j++)
		{
			Data[j].Re = (double)inputImage->imageData[i*inputImage->widthStep + j];
			// copy one row of input, the real component value is the value of the image
			//입력의 한 행을 복사, 실수 성분 값은 영상의 값
			Data[j].Im = 0.0; //The complex component value is 0 복소 성분 값은 0
		}
		FFT1d(Data, inputImage->width, Log2N); //1D FFT 1차원 FFT

		for (j = 0; j<inputImage->width; j++) { //Save Results
			FFT[i][j].Re = Data[j].Re;
			FFT[i][j].Im = Data[j].Im;
		}
	}

	Num = inputImage->height;
	Log2N = 0;

	while (Num >= 2) //Image height calculation 영상의 높이 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[inputImage->height];

	for (i = 0; i<inputImage->width; i++) {
		for (j = 0; j<inputImage->height; j++) {
			Data[j].Re = FFT[j][i].Re; //Copy a row of images 영상의 한 열을 복사
			Data[j].Im = FFT[j][i].Im;
		}

		FFT1d(Data, inputImage->height, Log2N); //1D FFT 1차원 FFT

		for (j = 0; j<inputImage->height; j++) { //Save Results
			FFT[j][i].Re = Data[j].Re;
			FFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i<inputImage->height; i++) {
		for (j = 0; j<inputImage->width; j++) {
			Value = sqrt((FFT[i][j].Re * FFT[i][j].Re) + (FFT[i][j].Im * FFT[i][j].Im));
			Absol = 20 * log(Value);

			if (Absol > 255.0)
				Absol = 255.0;
			if (Absol < 0.0)
				Absol = 0.0;

			cvSet2D(tempImage, i, j, cvScalar(Absol));
		}
	}
	//shuffling process 셔플링 과정
	for (i = 0; i<inputImage->height; i += inputImage->height / 2) {
		for (j = 0; j<inputImage->width; j += inputImage->width / 2) {
			for (row = 0; row<inputImage->height / 2; row++) {
				for (col = 0; col<inputImage->width / 2; col++) {
					tempScalar = cvGet2D(tempImage, i + row, j + col);
					temp[(inputImage->height / 2 - 1) - row + i][(inputImage->width / 2 - 1) - col + j] = (unsigned char)tempScalar.val[0];
				}
			}
		}
	}

	for (i = 0; i<inputImage->height; i++) {
		for (j = 0; j<inputImage->width; j++) {
			cvSet2D(FFTSpectrum, i, j, cvScalar(temp[i][j]));
		}
	}

	delete[] Data, **temp;
	cvReleaseImage(&tempImage);

	return FFTSpectrum;
}

void FFT1d(Complex *X, int N, int Log2N)
{
	Scrambling(X, N, Log2N);
	Butterfly(X, N, Log2N, 1);
}

void Scrambling(Complex *X, int N, int Log2N)
{
	int i;
	Complex *temp;

	temp = new Complex[N];

	for (i = 0; i<N; i++) {
		temp[i].Re = X[ReverseBitOrder(i, Log2N)].Re;
		temp[i].Im = X[ReverseBitOrder(i, Log2N)].Im;
	}

	for (i = 0; i<N; i++) {
		X[i].Re = temp[i].Re;
		X[i].Im = temp[i].Im;
	}

	delete[] temp;
}

void Butterfly(Complex *X, int N, int Log2N, int mode)
{
	int i, j, k, m;
	int start;
	double Value;
	double PI = 3.14159265358979;

	Complex *Y, temp;

	Y = new Complex[N / 2];

	for (i = 0; i<Log2N; i++) {
		Value = pow(2., i + 1);

		if (mode == 1) {
			for (j = 0; j<(int)(Value / 2); j++) {
				Y[j].Re = cos(j * 2.0 * PI / Value);
				Y[j].Im = -sin(j * 2.0 * PI / Value);
			}
		}
		if (mode == 2) {
			for (j = 0; j<(int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = sin(j*2.0*PI / Value);
			}
		}

		start = 0;

		for (k = 0; k<N / (int)Value; k++) {
			for (j = start; j<start + (int)(Value / 2); j++) {
				m = j + (int)(Value / 2);
				temp.Re = Y[j - start].Re * X[m].Re - Y[j - start].Im * X[m].Im;
				temp.Im = Y[j - start].Im * X[m].Re + Y[j - start].Re * X[m].Im;

				X[m].Re = X[j].Re - temp.Re;
				X[m].Im = X[j].Im - temp.Im;

				X[j].Re = X[j].Re + temp.Re;
				X[j].Im = X[j].Im + temp.Im;
			}
			start = start + (int)Value;
		}
	}
	if (mode == 2) {
		for (i = 0; i<N; i++) {
			X[i].Re = X[i].Re / N;
			X[i].Im = X[i].Im / N;
		}
	}

	delete[] Y;
}

int ReverseBitOrder(int index, int Log2N)
{
	int i, X, Y;

	Y = 0;

	for (i = 0; i< Log2N; i++) {
		X = (index & (1 << i)) >> i;
		Y = (Y << 1) | X;
	}
	return Y;
}


IplImage* RFFT2d(IplImage* FFTSpectrum)
{
	Complex **RFFT;

	int i, j, Num, Log2N;
	Complex *Data;

	IplImage *outputImage = cvCreateImage(cvGetSize(FFTSpectrum), 8, 1);

	Num = FFTSpectrum->width;
	Log2N = 0;
	while (Num >= 2) //Calculating the width of a frequency-converted image
	{			//주파수 변환된 영상의 너비 계산
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[FFTSpectrum->height];
	RFFT = new Complex *[FFTSpectrum->height]; //Arrangement for an inversely transformed image
											   //역변환된 영상을 위한 배열
	for (i = 0; i<FFTSpectrum->height; i++) {
		RFFT[i] = new Complex[FFTSpectrum->width];
	}

	for (i = 0; i<FFTSpectrum->height; i++) {
		for (j = 0; j<FFTSpectrum->width; j++) { //Copy one row 한 행을 복사
			Data[j].Re = FFT[i][j].Re;
			Data[j].Im = FFT[i][j].Im;
		}
		RFFT1d(Data, FFTSpectrum->width, Log2N); //1D RFFT

		for (j = 0; j<FFTSpectrum->width; j++) {
			RFFT[i][j].Re = Data[j].Re; //Save Results 결과 저장
			RFFT[i][j].Im = Data[j].Im;
		}
	}

	Num = FFTSpectrum->height;
	Log2N = 0;
	while (Num >= 2) //Calculation of height of frequency converted image
	{			//주파수 변환된 영상의 높이 계산
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[FFTSpectrum->height];

	for (i = 0; i< FFTSpectrum->width; i++) {
		for (j = 0; j<FFTSpectrum->height; j++) {
			Data[j].Re = RFFT[j][i].Re; //Copy one column 한 열을 복사
			Data[j].Im = RFFT[j][i].Im;
		}

		RFFT1d(Data, FFTSpectrum->width, Log2N); //1D RFFT

		for (j = 0; j< FFTSpectrum->width; j++) {//Save Results 결과 저장
			RFFT[j][i].Re = Data[j].Re;
			RFFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i<FFTSpectrum->width; i++) {
		for (j = 0; j<FFTSpectrum->height; j++) {
			cvSet2D(outputImage, i, j, cvScalar((unsigned char)RFFT[i][j].Re));
		}
	}
	delete[] Data;

	return outputImage;
}
void RFFT1d(Complex *X, int N, int Log2N)
{
	Scrambling(X, N, Log2N);
	Butterfly(X, N, Log2N, 2);
}
*/

// wavelet 변환
/*#include <opencv/cv.h>
#include <opencv/highgui.h>

double *DWT_1D(double *data, int len);
IplImage *DWT_2D(IplImage *inputImage, int iterations);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* DWTimg;

	DWTimg = DWT_2D(inputImage, 2);

	cvShowImage("Input Image", inputImage);
	cvShowImage("DWT image", DWTimg);

	cvWaitKey();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&DWTimg);

	return 0;
}

IplImage *DWT_2D(IplImage *inputImage, int iterations)
{
	IplImage *outImg = cvCreateImage(cvGetSize(inputImage), 8, 1);

	int rows = inputImage->height;
	int cols = inputImage->width;

	int i, j, k, levCols, levRows, lev;
	double*data;

	for (int i = 0; i < inputImage->height; i++)
		for (int j = 0; j < inputImage->width; j++) {
			cvSet2D(outImg, i, j, cvGet2D(inputImage, i, j));
		}

	for (k = 0; k < iterations; k++) {
		lev = 1 << k;
		levCols = cols / lev;
		levRows = rows / lev;

		data = new double[levCols];
		for (int i = 0; i < levRows; i++) {
			for (int j = 0; j < levRows; j++)
				data[j] = cvGet2D(outImg, i, j).val[0];
			data = DWT_1D(data, levCols);

			for (j = 0; j < levRows; j++)
				cvSet2D(outImg, i, j, cvScalar(data[j]));
		}
		data = new double[levRows];
		for (i = 0; i < levCols; i++) {
			for (j = 0; j < levRows; j++) {
				data[j] = cvGet2D(outImg, j, i).val[0];
			}
			data = DWT_1D(data, levCols);
			for (j = 0; j < levCols; j++) {
				cvSet2D(outImg, j, i, cvScalar(data[j]));
			}
		}

	}
	return outImg;
}

double *DWT_1D(double *data, int len) {
	double LPF[2] = { 0.50710678118655, 0.50710678118655 };
	double HPF[2] = { 0.70710678118655, -0.70710678118655 };

	double *temp = new double[len];
	int i;

	for (i = 0; i < len / 2; i++) {
		temp[i] = data[2 * i] * LPF[0] + data[2 * i + 1] * LPF[1];
		temp[len / 2 + i] = data[2 * i] * HPF[0] + data[2 * i + 1] * HPF[1];

	}
	return temp;
}*/


// wavelet ��ȯ
/*
#include <opencv/cv.h>
#include <opencv/highgui.h>

double *DWT_1D(double *data, int len);
IplImage *DWT_2D(IplImage *inputImage, int iterations);
double *IDWT_1D(double *data, int len);
IplImage *IDWT_2D(IplImage *inputImage, int iterations);
double **OnScale(double **img, int h, int w);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* DWTimg;
	IplImage* IDWTimg;

	DWTimg = DWT_2D(inputImage, 1);
	IDWTimg = IDWT_2D(DWTimg, 1);

	cvShowImage("Input Image", inputImage);
	cvShowImage("DWT image", DWTimg);
	cvShowImage("IDWT image", IDWTimg);

	cvWaitKey();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&DWTimg);
	cvReleaseImage(&IDWTimg);

	return 0;
}

IplImage *DWT_2D(IplImage *inputImage, int iterations)
{
	IplImage *outImg = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *tempImg = cvCreateImage(cvGetSize(inputImage), 8, 1);

	int rows = inputImage->height;
	int cols = inputImage->width;

	int i, j, k, levCols, levRows, lev;
	double*data;
	double**imgData;

	for (int i = 0; i < inputImage->height; i++) {
		for (int j = 0; j < inputImage->width; j++) {
			cvSet2D(outImg, i, j, cvGet2D(inputImage, i, j));
		}
	}
	imgData = new double *[inputImage->height];

	for (k = 0; k < iterations; k++) {
		lev = 1 << k;
		levCols = cols / lev;
		levRows = rows / lev;
		imgData = new double *[levRows];
		data = new double[levCols];

		for (int i = 0; i < levRows; i++) {
			for (int j = 0; j < levCols; j++)
				data[j] = cvGet2D(outImg, i, j).val[0];
			imgData[i] = DWT_1D(data, levCols);
		}

		data = new double[levRows];
		for (i = 0; i < levCols; i++) {
			for (j = 0; j < levRows; j++) {
				data[j] = imgData[j][i];
			}
			data = DWT_1D(data, levCols);
			for (j = 0; j < levCols; j++) {
				imgData[j][i] = data[j];
			}
		}

		imgData = OnScale(imgData, levRows, levCols);
		for (i = 0; i < levRows; i++)
			for (j = 0; j < levCols; j++) {
				cvSet2D(outImg, i, j, cvScalar(imgData[i][j]));
			}
	}
	return outImg;
}


double *DWT_1D(double *data, int len) {
	double LPF[2] = { 0.50710678118655, 0.50710678118655 };
	double HPF[2] = { 0.70710678118655, -0.70710678118655 };

	double *temp = new double[len];
	int i;

	for (i = 0; i < len / 2; i++) {
		temp[i] = data[2 * i] * LPF[0] + data[2 * i + 1] * LPF[1];
		temp[len / 2 + i] = data[2 * i] * HPF[0] + data[2 * i + 1] * HPF[1];

	}
	return temp;
}
double *IDWT_1D(double *data, int len) {
	double LPF[2] = { 0.70710678118655, 0.70710678118655 };
	double HPF[2] = { 0.70710678118655, -0.70710678118655 };

	double *sortData = new double[len];
	double *temp = new double[len];
	int i;

	for (i = 0; i < len / 2; i++) {
		sortData[i * 2] = data[i];
		sortData[i * 2 + 1] = data[len / 2 + i];
	}
	for (i = 0; i < len / 2; i++) {
		temp[2 * i] = sortData[2 * i] * LPF[0] + sortData[2 * i + 1] * LPF[1];
		temp[2 * i + 1] = sortData[2 * i] * HPF[0] + sortData[2 * i + 1] * HPF[1];
	}

	return temp;
}
IplImage *IDWT_2D(IplImage *inputImage, int iterations) {
	IplImage *outImg = cvCreateImage(cvGetSize(inputImage), 8, 1);

	int rows = inputImage->height;
	int cols = inputImage->width;

	int i, j, k, levCols, levRows, lev;
	double*data;

	for (int i = 0; i < inputImage->height; i++) {
		for (int j = 0; j < inputImage->width; j++) {
			cvSet2D(outImg, i, j, cvGet2D(inputImage, i, j));
		}
	}

	for (k = iterations; k > 0; k--) {
		lev = 1 << k - 1;

		levCols = cols / lev;
		levRows = rows / lev;
		data = new double[levCols];

		for (int i = 0; i < levRows; i++) {
			for (int j = 0; j < levCols; j++)
				data[j] = cvGet2D(outImg, i, j).val[0];

			data = IDWT_1D(data, levCols);

			for (int j = 0; j < levCols; j++)
				cvSet2D(outImg, i, j, cvScalar(data[j]));
		}

		data = new double[levRows];
		for (i = 0; i < levCols; i++) {
			for (j = 0; j < levRows; j++)
				data[j] = cvGet2D(outImg, j,i).val[0];

			data = IDWT_1D(data, levCols);
			for (j = 0; j < levCols; j++)
				cvSet2D(outImg, j, i, cvScalar(data[j]));
		}

	}
	return outImg;
}
double **OnScale(double **inputImage, int height, int width) {
	double max, min;
	int i, j;

	min = max = inputImage[0][0];
	for (i = 0; i < height / 2; i++) {
		for (j = 0; j < width / 2; j++) {
			if (inputImage[i][j] <= min) {
				min = inputImage[i][j];
			}
			if (inputImage[i][j] >= max) {
				max = inputImage[i][j];
			}
		}
	}

	max = max - min;
	for (i = 0; i < height / 2; i++) {
		for (j = 0; j < width / 2; j++) {
			inputImage[i][j] = (inputImage[i][j] - min) * 255 / max;
		}
	}

	min = max = inputImage[0][0];
	for (i = 0; i < height / 2; i++) {
		for (j = width / 2; j < width; j++) {
			if (inputImage[i][j] <= min) {
				min = inputImage[i][j];
			}
			if (inputImage[i][j] >= max) {
				max = inputImage[i][j];
			}
		}
	}

	max = max - min;
	for (i = 0; i < height; i++) {
		for (j = width / 2; j < width; j++) {
			inputImage[i][j] = (inputImage[i][j] - min) * 255 / max;
		}
	}


	min = max = inputImage[0][0];
	for (i = height / 2; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (inputImage[i][j] <= min) {
				min = inputImage[i][j];
			}
			if (inputImage[i][j] >= max) {
				max = inputImage[i][j];
			}
		}
	}

	max = max - min;
	for (i = height / 2; i < height; i++) {
		for (j = width / 2; j < width; j++) {
			inputImage[i][j] = (inputImage[i][j] - min) * 255 / max;
		}
	}



	min = max = inputImage[0][0];
	for (i = 0; i < height / 2; i++) {
		for (j = 0; j < width / 2; j++) {
			if (inputImage[i][j] <= min) {
				min = inputImage[i][j];
			}
			if (inputImage[i][j] >= max) {
				max = inputImage[i][j];
			}
		}
	}

	max = max - min;
	for (i = 0; i < height / 2; i++) {
		for (j = 0; j < width / 2; j++) {
			inputImage[i][j] = (inputImage[i][j] - min) * 255 / max;
		}
	}

	return inputImage;
}
*/


#include <opencv/cv.h>
#include <opencv/highgui.h>

//상수 정의
#define FilterTap	2
//분해 레벨 고정
#define Level		1

//영상의 세로, 가로, 전체 크기
#define m_Height 512
#define m_Width  512
#define m_Size   m_Height*m_Width

//임시 입출력 변수
double **m_tempInput;
double **m_tempOutput;

//필터 변수
double *m_FilterH0;
double *m_FilterH1;
double *m_FilterG0;
double *m_FilterG1;

double *m_Recon;

//입력, 출력, 변환 영상 버퍼
unsigned char *m_InputImage;
unsigned char *m_OutputImage;
unsigned char **m_ArrangeImage;

//함수 선언
double* OnDownSampling(double *m_Target, int size);
double* OnUpSampling(double *m_Target, int size);
double* OnConvolution(double *m_Target, double *m_Filter, int size, int mode);

void	OnFilterGen(double *m_H0, double *m_H1, double *m_G0, double *m_G1);
void	OnWaveletEncode();
void	OnWaveletDecode();

double** OnScale(double **m_Target, int height, int width);
double** OnMem2DAllocDouble(int height, int width);

unsigned char** OnMem2DAllocUnsigned(int height, int width);

int main()
{
	/* 변수 선언 */
	int i, j, k = 0;
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *waveletImage = cvCreateImage(cvSize((inputImage->height), (inputImage->width)), 8, 1);
	IplImage *outputImage = cvCreateImage(cvSize((inputImage->height), (inputImage->width)), 8, 1);

	m_InputImage = new unsigned char[m_Size];
	m_OutputImage = new unsigned char[m_Size];

	for (i = 0; i<m_Size; i++)
	{
		m_InputImage[i] = (unsigned char)inputImage->imageData[i];
	}

	OnWaveletEncode();
	OnWaveletDecode();

	for (i = 0; i<m_Height; i++) {
		for (j = 0; j<m_Width; j++) {
			waveletImage->imageData[k++] = (char)m_ArrangeImage[i][j];
		}
	}
	for (i = 0; i<m_Size; i++) {
		outputImage->imageData[i] = (char)m_OutputImage[i];
	}

	cvShowImage("Input Image", inputImage);
	cvShowImage("Wavelet Image", waveletImage);
	cvShowImage("OutPutImage", outputImage);

	cvSaveImage("Input Image.jpg", inputImage);
	cvSaveImage("Wavelet Image.jpg", waveletImage);
	cvSaveImage("OutPutImage.jpg", outputImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&waveletImage);
	cvReleaseImage(&outputImage);
	cvReleaseImage(&inputImage);

	return 0;
}
//다운 샘플링 함수
double* OnDownSampling(double *m_Target, int size)
{
	/* 변수 선언 */
	int i;
	double *m_temp;

	m_temp = new double[size / 2];

	/* 다운 샘플링 처리 */
	for (i = 0; i < size / 2; i++)
	{
		m_temp[i] = m_Target[2 * i];
	}

	return m_temp;
}
//업 샘플링 함수
double* OnUpSampling(double *m_Target, int size)
{
	/* 변수 선언 */
	int i;
	double *m_temp;

	m_temp = new double[size * 2];

	/* 업 샘플링 처리 */
	for (i = 0; i < size * 2; i++)
		m_temp[i] = 0.0;

	for (i = 0; i < size; i++)
		m_temp[2 * i] = m_Target[i];

	return m_temp;
}
//1차원 컨벌루션 함수
double* OnConvolution(double *m_Target, double *m_Filter, int size, int mode)
{
	/* 변수 선언 */
	int i, j;
	double *m_temp, *m_tempConv;
	double m_sum = 0.0;

	/* 컨벌루션 결과 출력 배열 */
	m_temp = new double[size + FilterTap - 1];
	m_tempConv = new double[size];

	/* 컨벌루션을 위한 초기화 과정 */
	switch (mode)
	{
	case 1:	// mode가 1일때
		for (i = 0; i < size; i++)
			m_temp[i] = m_Target[i];

		for (i = 0; i < FilterTap - 1; i++)
			m_temp[size + 1] = m_Target[i];

		break;

	case 2:	// mode가 2일때
		for (i = 0; i < FilterTap - 1; i++)
			m_temp[i] = m_Target[size - FilterTap + i + 1];

		for (i = FilterTap - 1; i < size + FilterTap - 1; i++)
			m_temp[i] = m_Target[i - FilterTap + 1];

		break;
	}

	/* 컨벌루션 연산 */
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < FilterTap; j++)
		{
			m_sum += (m_temp[j + i] * m_Filter[FilterTap - j - 1]);
		}
		m_tempConv[i] = m_sum;
		m_sum = 0.0;
	}

	return m_tempConv;	//연산 결과 return
}
//필터 생성 함수
void OnFilterGen(double *m_H0, double *m_H1, double *m_G0, double *m_G1)
{
	int i;
	/* 각각의 필터계수값을 초기화 */
	switch (FilterTap)
	{
	case 2:
		m_H0[0] = 0.70710678118655;
		m_H0[1] = 0.70710678118655;
		break;
	case 4:
		m_H0[0] = -0.12940952255092;
		m_H0[1] = 0.22414386804186;
		m_H0[2] = 0.83651630373747;
		m_H0[3] = 0.48296291314469;
		break;
	case 6:
		m_H0[0] = 0.03522629188210;
		m_H0[1] = -0.08544127388224;
		m_H0[2] = -0.13501102001039;
		m_H0[3] = 0.45987750211933;
		m_H0[4] = 0.80689150931334;
		m_H0[5] = 0.33267055295096;
		break;
	case 8:
		m_H0[0] = -0.01059740178500;
		m_H0[1] = 0.03288301166698;
		m_H0[2] = 0.03084138183599;
		m_H0[3] = -0.18703481171888;
		m_H0[4] = -0.02798376941698;
		m_H0[5] = 0.63088076792959;
		m_H0[6] = 0.71484657055254;
		m_H0[7] = 0.23037781330886;
		break;
	default:
		printf("Wrong Filter");
		return;
	}

	/* H0 필터계수를 이용해, H1, G0, G1 필터 계수 생성*/
	for (i = 0; i < FilterTap; i++)
		m_H1[i] = pow((double)-1, i + 1) * m_H0[FilterTap - i - 1];

	for (i = 0; i < FilterTap; i++)
		m_G0[i] = m_H0[FilterTap - i - 1];

	for (i = 0; i < FilterTap; i++)
		m_G1[i] = pow((double)-1, i) * m_H0[i];
}

//2차원 메모리 할당 함수
unsigned char** OnMem2DAllocUnsigned(int height, int width)
{
	// unsigned char 형태의 2차원 배열 할당
	int i, j;
	unsigned char **temp;

	temp = new unsigned char *[height];
	/* unsigned char 형태의 2차원 배열 할당 */
	for (i = 0; i < height; i++)
		temp[i] = new unsigned char[width];
	/* unsigned char 형태의 2차원 배열 초기화 */
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			temp[i][j] = 0;

	return temp;	//초기화된 2차원 배열 return
}
//2차원 메모리 할당 함수
double** OnMem2DAllocDouble(int height, int width)
{
	// double 형태의 2차원 배열 할당
	int i, j;
	double **temp;

	temp = new double *[height];
	/* double 형태의 2차원 배열 할당 */
	for (i = 0; i < height; i++)
		temp[i] = new double[width];
	/* double 형태의 2차원 배열 초기화 */
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			temp[i][j] = 0;

	return temp;	//초기화된 2차원 배열 return
}
//정규화 함수
double** OnScale(double **m_Target, int height, int width)
{
	// 필터링 된 값을 0~ 255 사이의 값으로 정규화
	int i, j;
	double min, max;
	double **temp;

	temp = OnMem2DAllocDouble(height, width);

	min = max = m_Target[0][0];

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			/* 최소값일 경우 */
			if (m_Target[i][j] <= min)
			{
				min = m_Target[i][j];
			}
			/* 최대값일 경우 */
			if (m_Target[i][j] >= max)
			{
				max = m_Target[i][j];
			}
		}
	}

	max = max - min;
	/* 정규화 처리 */
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			temp[i][j] = (m_Target[i][j] - min) * (255. / max);
		}
	}

	return temp;	//정교화된 값을 return
}

//역방향 웨이블렛 변환 함수 (코드작성)
void OnWaveletDecode()
{
	int i, j, k;
	int width, height;
	double *tempLL, *tempLH, *tempHL, *tempHH, *tempL, *tempH;
	double **L, **H;
	double *Up1, *Up2, *Up3, *Up4;
	double *Conv1, *Conv2, *Conv3, *Conv4;
	double **R;

	width = m_Width / (int)(pow((double)2, Level));
	height = m_Height / (int)(pow((double)2, Level));

	m_Recon = new double[m_Width * m_Height];

	//분해 레벨이 상수이므로 k 초기값 고정
	for (k = Level; k>0; k--) {
		if (width >    m_Width || height >m_Height) { // 분해 종료
			return;
		}

		tempLL = new double[height];
		tempLH = new double[height];
		tempHL = new double[height];
		tempHH = new double[height];
		L = OnMem2DAllocDouble(height * 2, width);
		H = OnMem2DAllocDouble(height * 2, width);

		tempL = new double[width];
		tempH = new double[width];

		R = OnMem2DAllocDouble(height * 2, width * 2);

		for (i = 0; i<width; i++) {
			for (j = 0; j<height; j++) {
				// 정렬 영상에서 처리하려는 열을 분리
				tempLL[j] = m_tempOutput[j][i];
				tempLH[j] = m_tempOutput[j + height][i];
				tempHL[j] = m_tempOutput[j][i + width];
				tempHH[j] = m_tempOutput[j + height][i + width];
			}

			Up1 = OnUpSampling(tempLL, height); // 업 샘플링
			Up2 = OnUpSampling(tempLH, height);
			Up3 = OnUpSampling(tempHL, height);
			Up4 = OnUpSampling(tempHH, height);

			Conv1 = OnConvolution(Up1, m_FilterG0, height * 2, 2);
			// 컨벌루션 연산
			Conv2 = OnConvolution(Up2, m_FilterG1, height * 2, 2);
			Conv3 = OnConvolution(Up3, m_FilterG0, height * 2, 2);
			Conv4 = OnConvolution(Up4, m_FilterG1, height * 2, 2);
			for (j = 0; j<height * 2; j++) {
				L[j][i] = Conv1[j] + Conv2[j];
				H[j][i] = Conv3[j] + Conv4[j];
			}
		}
		for (i = 0; i<height * 2; i++) {
			for (j = 0; j<width; j++) {
				tempL[j] = L[i][j]; // 횡 데이터 분리
				tempH[j] = H[i][j];
			}

			Up1 = OnUpSampling(tempL, width); // 업 샘플링
			Up2 = OnUpSampling(tempH, width);

			Conv1 = OnConvolution(Up1, m_FilterG0, width * 2, 2);
			// 컨벌루션 연산
			Conv2 = OnConvolution(Up2, m_FilterG1, width * 2, 2);
			for (j = 0; j<width * 2; j++) {
				R[i][j] = Conv1[j] + Conv2[j];
			}
		}

		for (i = 0; i<height * 2; i++) {
			for (j = 0; j<width * 2; j++) {
				m_tempOutput[i][j] = R[i][j];
				// 복원 데이터를 다시 정렬
			}
		}
		height = height * 2; // 영상의 크기를 두 배 확장
		width = width * 2;
	}

	for (i = 0; i< m_Height; i++) {
		for (j = 0; j< m_Width; j++) {
			m_Recon[i*   m_Width + j] = R[i][j];
			m_OutputImage[i*   m_Width + j]
				= (unsigned char)R[i][j];
			// 최종 복원된 결과를 출력
		}
	}

	//UpdateAllViews(NULL); MFC 전용 함수이므로 사용하지 않는다.

	delete[] tempLL, tempLH, tempHL, tempHH, tempL, tempH;
	// 메모리 해제
	delete[] Up1, Up2, Up3, Up4;
	delete[] Conv1, Conv2, Conv3, Conv4;

	for (i = 0; i< m_Height; i++) { // 메모리 해제
		delete[] L[i];
		delete[] H[i];
		delete[] R[i];
	}

	delete L, H, R;
}
//순방향 웨이블렛 함수 (코드작성)
void OnWaveletEncode()
{
	// Wavelet encode 함수 분해 레벨이 변수가 아니라 상수로 포팅 되었음에 주의
	if (Level <= 0 || (pow((double)2, Level + 3) > (double)m_Width) || (pow((double)2, Level + 3) > (double)m_Height)) {
		return;
		// 최대 분해 레벨이 512*512이면 6레벨로 제한
	}

	int i, j, k, width, height;
	double *m_Conv1, *m_Conv2, *m_Conv3, *m_Conv4;
	// Convolution을 위한 버퍼
	double *m_Down1, *m_Down2, *m_Down3, *m_Down4;
	// 다운 샘플링을 위한 버퍼
	double *m_Hor, *m_Ver1, *m_Ver2;
	double **m_L, **m_H, **m_LL, **m_LH, **m_HL, **m_HH, **m_SLL, **m_SLH, **m_SHL, **m_SHH;

	m_tempInput = OnMem2DAllocDouble(m_Height, m_Width);
	m_tempOutput = OnMem2DAllocDouble(m_Height, m_Width);
	m_ArrangeImage = OnMem2DAllocUnsigned(m_Height, m_Width);

	for (i = 0; i< m_Height; i++) {
		for (j = 0; j< m_Width; j++) {
			m_tempInput[i][j]
				= (double)m_InputImage[i*   m_Width + j];
			// 1차원 입력을 2차원 배열로 변환
		}
	}
	//OnFilterTapGen(); // FilterTap이 고정 상수이므로 주석처리

	m_FilterH0 = new double[FilterTap]; // 필터 계수를 위한 배열
	m_FilterH1 = new double[FilterTap]; // 필터 계수를 위한 배열
	m_FilterG0 = new double[FilterTap]; // 필터 계수를 위한 배열
	m_FilterG1 = new double[FilterTap]; // 필터 계수를 위한 배열

	OnFilterGen(m_FilterH0, m_FilterH1, m_FilterG0, m_FilterG1);
	// 필터 계수 생성

	width = m_Width;
	height = m_Height;

	for (k = 0; k<Level; k++) {
		m_L = OnMem2DAllocDouble(height, width / 2); //
		m_H = OnMem2DAllocDouble(height, width / 2); //
		m_LL = OnMem2DAllocDouble(height / 2, width / 2);
		// LL 저장을 위한 배열
		m_LH = OnMem2DAllocDouble(height / 2, width / 2);
		// LH 저장을 위한 배열
		m_HL = OnMem2DAllocDouble(height / 2, width / 2);
		// HL 저장을 위한 배열
		m_HH = OnMem2DAllocDouble(height / 2, width / 2);
		// HH 저장을 위한 배열

		m_Hor = new double[width]; // 횡 입력을 위한 배열
		for (i = 0; i<height; i++) {
			for (j = 0; j<width; j++) {
				m_Hor[j] = m_tempInput[i][j];
				// 입력 배열을 1차원 배열에 할당
			}

			m_Conv1 = OnConvolution(m_Hor, m_FilterH0, width, 1);
			// Convolution 처리
			m_Conv2 = OnConvolution(m_Hor, m_FilterH1, width, 1);
			// Convolution 처리
			m_Down1 = OnDownSampling(m_Conv1, width); // 다운 샘플링
			m_Down2 = OnDownSampling(m_Conv2, width); // 다운 샘플링

			for (j = 0; j<width / 2; j++) {// 다운 샘플링 결과를 저장
				m_L[i][j] = m_Down1[j];
				m_H[i][j] = m_Down2[j];
			}
		}

		m_Ver1 = new double[height];

		m_Ver2 = new double[height];
		for (i = 0; i<width / 2; i++) {
			for (j = 0; j<height; j++) {
				m_Ver1[j] = m_L[j][i]; // 열 방향으로 1차원 배열에 할당
				m_Ver2[j] = m_H[j][i];
			}

			m_Conv1 = OnConvolution(m_Ver1, m_FilterH0, height, 1);
			// Convolution 처리
			m_Conv2
				= OnConvolution(m_Ver1, m_FilterH1, height, 1);
			m_Conv3
				= OnConvolution(m_Ver2, m_FilterH0, height, 1);
			m_Conv4
				= OnConvolution(m_Ver2, m_FilterH1, height, 1);

			m_Down1 = OnDownSampling(m_Conv1, height); // 다운 샘플링
			m_Down2 = OnDownSampling(m_Conv2, height);
			m_Down3 = OnDownSampling(m_Conv3, height);
			m_Down4 = OnDownSampling(m_Conv4, height);

			for (j = 0; j<height / 2; j++) {
				m_LL[j][i] = m_Down1[j]; // 결과 저장
				m_LH[j][i] = m_Down2[j];
				m_HL[j][i] = m_Down3[j];
				m_HH[j][i] = m_Down4[j];
			}
		}
		m_SLL = OnScale(m_LL, height / 2, width / 2); // 처리 결과를 정규화
		m_SLH = OnScale(m_LH, height / 2, width / 2);
		m_SHL = OnScale(m_HL, height / 2, width / 2);
		m_SHH = OnScale(m_HH, height / 2, width / 2);

		for (i = 0; i<height / 2; i++) {
			for (j = 0; j<width / 2; j++) {
				m_tempOutput[i][j] = m_LL[i][j];
				m_tempOutput[i][j + (width / 2)] = m_HL[i][j];
				m_tempOutput[i + (height / 2)][j] = m_LH[i][j];
				m_tempOutput[i + (height / 2)][j + (width / 2)] =
					m_HH[i][j];
				// 처리 결과를 정렬
				m_ArrangeImage[i][j]
					= (unsigned char)m_SLL[i][j];
				m_ArrangeImage[i][j + (width / 2)]
					= (unsigned char)m_SHL[i][j];
				m_ArrangeImage[i + (height / 2)][j]
					= (unsigned char)m_SLH[i][j];
				m_ArrangeImage[i + (height / 2)][j + (width / 2)]
					= (unsigned char)m_SHH[i][j];
				// 정규화 과정을 거친 정렬 영상
			}
		}
		width = width / 2;
		// 분해를 계속하기 위해 영상의 가로축 크기를 반으로 줄임
		height = height / 2;
		// 분해를 계속하기 위해 영상의 세로축 크기를 반으로 줄임
		m_tempInput = OnMem2DAllocDouble(height, width);

		for (i = 0; i<height; i++) {
			for (j = 0; j<width; j++) {
				m_tempInput[i][j] = m_LL[i][j];
				// LL 값을 새로운 입력으로 할당
			}
		}
	}

	delete[] m_Conv1, m_Conv2, m_Conv3, m_Conv4;
	delete[] m_Down1, m_Down2, m_Down3, m_Down4;
	delete[] m_Hor, m_Ver1, m_Ver2;
	for (i = 0; i<height; i++) { // 메모리 해제
		delete[] m_LL[i];
		delete[] m_LH[i];
		delete[] m_HL[i];
		delete[] m_HH[i];
		delete[] m_SLL[i];
		delete[] m_SLH[i];
		delete[] m_SHL[i];
		delete[] m_SHH[i];
		delete[] m_L[i];
		delete[] m_H[i];
	}
	delete m_L, m_H, m_LL, m_LH, m_HL, m_HH, m_SLL, m_SLH,
		m_SHL, m_SHH;
}