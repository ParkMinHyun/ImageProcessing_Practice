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
/*�̵�
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

/*������ ��� ���͸�
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

/*��Ī
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputImage_1 = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);
	IplImage* outputImage_2 = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);

	int i, j;

	for (i = 0; i < inputImage->height; i++) { // �¿����
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(outputImage_1, i, inputImage->width - j - 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) { // ���Ϲ���
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(outputImage_2, inputImage->height - i - 1, j, cvGet2D(inputImage, i, j));
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image1", outputImage_1);
	cvShowImage("Output Image2", outputImage_2);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage_1);
	cvReleaseImage(&outputImage_2);

	return 0;
}
*/
/*ȸ��
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define DEGREE 90 // ȸ�� ����

int main() {
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* outputImage = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);

	int i, j, Center_y, Center_x, source_y, source_x;
	double Radian, cosR, sinR;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0; // degree ���� radian���� ����

	cosR = cos(Radian);
	sinR = sin(Radian);

	Center_y = inputImage->height / 2;
	Center_x = inputImage->width / 2;

	for (i = 0; i < inputImage->height; i++) { // �¿����
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

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage);

	return 0;
}

/*��â, ħ��

#include <opencv/cv.h>
#include <opencv/highgui.h>

#define THRESHOLD 130

int main() {
	int i, j, n, m, dilationSum = 0, erosionSum = 0;

	CvScalar tempValue;
	//ħ�� ����ũ
	double erosionMask[3][3] = { { 255,255,255 },{ 255,255,255 },{ 255,255,255 } };
	//��â ����ũ
	double dilationMask[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *binaryImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), 8, 1);
	IplImage *erosionImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *dilationImage = cvCreateImage(cvGetSize(inputImage), 8, 1);

	//����ȭ
	for (i = 0; i < inputImage->height; i++) { // ��ǲ�̹��� temp�� �ű�
		for (j = 0; j < inputImage->width; j++) {
			tempValue = cvGet2D(inputImage, i, j);
			if (tempValue.val[0] > THRESHOLD)
				cvSet2D(binaryImage, i, j, cvScalar(255));
			else
				cvSet2D(binaryImage, i, j, cvScalar(0));
		}
	}

	//�е������
	for (i = 0; i < binaryImage->height; i++) { // ��ǲ�̹��� temp�� �ű�
		for (j = 0; j < binaryImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
		}
	}

	//����
	//�е������
	for (i = 0; i < binaryImage->height; i++) { // ��ǲ�̹��� temp�� �ű�
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

/*���ȭ*/
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