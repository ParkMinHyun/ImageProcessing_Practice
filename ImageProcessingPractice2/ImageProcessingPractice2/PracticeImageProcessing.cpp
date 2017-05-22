/*���� ������ ���
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

double ABS(double x) { // ���밪 �Լ�
	if (x >= 0) return x;
	else return -x;
}

IplImage* HomogenProcess(IplImage* inputImage) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Max = 0.0, temp;
	CvScalar tempScalar, ceterScalar;

	cvSetZero(tempinputImage); // ���ó���� 0�� ����, temp�̹��� ���������� ä��

	for (i = 0; i < inputImage->height; i++) { // temp �̹����� ��ǲ �̹��� ����
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // ������� ����
		for (j = 0; j < inputImage->width; j++) {
			ceterScalar = cvGet2D(tempinputImage, i + 1, j + 1);
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // ����ũ�� �����ϸ鼭 Sum�� ����
					tempScalar = cvGet2D(tempinputImage, i + n, j + m); // �̿���
					temp = ABS(ceterScalar.val[0] - tempScalar.val[0]); // �̿� ������� ���� ���ѵ� ���밪
					if (Max < temp)
						Max = temp; // �ִ밪
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Max)); // ������� �ƿ�ǲ �̹����� ����
			Max = 0.0;
		}
	}
	cvReleaseImage(&tempinputImage);

	return outputImage;
}
*/
/*���ö�þ�
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* LaplaImage_1 = NULL;
	IplImage* LaplaImage_2 = NULL;

	double LaplaMask_1[3][3] = { { 0.,-1.,-0. },{ -1.,4.,-1. },{ 0.,-1.,0. } }; // ���ö�þ�
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
/*Canny ���� ����
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW_THRESHOLD 30 // HIGH�� LOW�� 2~3��� ����ϴ� ���� ����
#define HIGH_THRESHOLD 30 * 2.5

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* CannyEdgeImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	cvCanny(inputImage, CannyEdgeImage, LOW_THRESHOLD, HIGH_THRESHOLD); // �ɴ� �Լ�

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
/*�ι��� ����ũ
#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* SumImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* RowImage = NULL;
	IplImage* ColImage = NULL;

	//double RowMask[3][3] = { {-1.,0.,0.},{0.,1.,0.},{0.,0.,0.} }; // �ι���
	//double ColMask[3][3] = { {0.,0.,-1.},{0.,1.,0.},{0.,0.,0.} };
	//double freeRowMask[3][3] = { {-1.,-1.,-1.},{0.,0.,0.},{1.,1.,1.} }; // ������
	//double freeColMask[3][3] = { {1.,0.,-1.},{1.,0.,-1.},{1.,0.,-1.} };
	double soRowMask[3][3] = { { -1.,-2.,-1 },{ 0.,0.,0. },{ 1.,2.,1. } }; // �Һ�
	double soColMask[3][3] = { { 1.,0.,-1. },{ 2.,0.,-2. },{ 1.,0.,-1. } };

	int i, j;
	CvScalar horizontemp, vertical;

	//RowImage = ConvolutionProcess(inputImage, RowMask); // �ι���
	//ColImage = ConvolutionProcess(inputImage, ColMask);
	//RowImage = ConvolutionProcess(inputImage, freeRowMask); // ������
	//ColImage = ConvolutionProcess(inputImage, freeColMask);
	RowImage = ConvolutionProcess(inputImage, soRowMask); // �Һ�
	ColImage = ConvolutionProcess(inputImage, soColMask);

	cvOr(RowImage, ColImage, SumImage); // �ΰ� �̹��� ��ġ�� �Լ�

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
/*�̵�*/
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