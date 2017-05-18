/*유사 연산자 기법*/
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