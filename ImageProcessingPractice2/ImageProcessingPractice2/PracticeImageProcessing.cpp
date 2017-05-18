/*���� ������ ���*/
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