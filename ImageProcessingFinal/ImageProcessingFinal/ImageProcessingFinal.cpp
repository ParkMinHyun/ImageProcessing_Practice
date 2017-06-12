#include <opencv/cv.h>
#include <opencv/highgui.h>

void SaveImage(char *saveImageName, IplImage *saveImage);
IplImage *scaleDown(IplImage *sclaeDownImage, IplImage *tempImage);
IplImage *mix(IplImage *lenaImage, IplImage *scaleDownImage);

int main() {
	IplImage* lena = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // 기존 이미지 로드
	IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_COLOR); // 합성할 이미지 로드
	IplImage* scaleDownImage = cvCreateImage(cvSize(lena->width, lena->height), lena->depth, lena->nChannels); // 합성된 이미지 생성
	IplImage* mixImage = cvCreateImage(cvGetSize(lena), lena->depth, lena->nChannels); // 합성된 이미지 생성
	
	int i, j;
	CvScalar temp;
	
	scaleDownImage = scaleDown(heart, scaleDownImage);
	mixImage = mix(lena, scaleDownImage);
	//SaveImage("mix.jpg", mix);

	cvNamedWindow("lena image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("scaleDown image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mix image", CV_WINDOW_AUTOSIZE);

	cvShowImage("lena image", lena);
	cvShowImage("scaleDown image", scaleDownImage);
	cvShowImage("mix image", mixImage);

	cvWaitKey();

	cvDestroyWindow("lena image");
	cvDestroyWindow("scaleDown image");
	cvDestroyWindow("mix image");

	cvReleaseImage(&lena);
	cvReleaseImage(&scaleDownImage);
	cvReleaseImage(&mixImage);

	return 0;
}

void SaveImage(char *saveImageName, IplImage *saveImage) {
	cvSaveImage(saveImageName, saveImage);
}

IplImage *scaleDown(IplImage *sclaeDownImage, IplImage *tempImage){
	int i, j;
	CvScalar pixelValue;

	for (i = 0; i < sclaeDownImage->height; i++) {
		for (j = 0; j < sclaeDownImage->width; j++) {

			if (i % 2 == 0 && j % 2 == 0) {
				pixelValue = cvGet2D(sclaeDownImage, i, j); // 합성할 이미지의 색 얻기
				cvSet2D(tempImage, i / 2, j / 2, pixelValue);
			}

		}
	}
	return tempImage;
}

IplImage *mix(IplImage *lenaImage, IplImage *scaleDownImage) {
	int i, j; 
	IplImage* mixImage = cvCreateImage(cvGetSize(lenaImage), lenaImage->depth, lenaImage->nChannels); // 합성된 이미지 생성
	CvScalar pixelValue,temp;
	
	for (i = 0; i < scaleDownImage->height; i++) {
		for (j = 0; j < scaleDownImage->width; j++) {

			pixelValue = cvGet2D(scaleDownImage, i, j); // 합성할 이미지의 색 얻기
			if (pixelValue.val[0] < 240) {
				temp = cvGet2D(scaleDownImage, i, j); // 합성할 이미지 보다 어두우면 그 색을 설정
				cvSet2D(mixImage, i, j, temp);
			}
			else {
				temp = cvGet2D(lenaImage, i, j); // 그외는 원본 값
				cvSet2D(mixImage, i, j, temp);
			}
		}
	}
	return mixImage;
}