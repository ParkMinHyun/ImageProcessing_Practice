/*2번
#include <opencv/cv.h>
#include <opencv/highgui.h>

void SaveImage(char *saveImageName, IplImage *saveImage);
IplImage *scaleDown(IplImage *sclaeDownImage, IplImage *tempImage);
IplImage *mix(IplImage *mainImage, IplImage *scaleDownImage);

int main() {
	IplImage* lena = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // 기존 이미지 로드
	IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_COLOR); // 합성할 이미지 로드
	IplImage* Rock = cvLoadImage("Rock2.jpg", CV_LOAD_IMAGE_COLOR); // 합성할 이미지 로드
	IplImage* scaleDownImage = cvCreateImage(cvSize(lena->width, lena->height), lena->depth, lena->nChannels); // 합성된 이미지 생성
	IplImage* mixImage = cvCreateImage(cvGetSize(lena), lena->depth, lena->nChannels); // 합성된 이미지 생성

	int i, j;
	CvScalar temp;

	scaleDownImage = scaleDown(Rock, scaleDownImage);
	//cvAdd(lena, scaleDownImage, mixImage, NULL);

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

IplImage *scaleDown(IplImage *sclaeDownImage, IplImage *tempImage) {
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
//
//IplImage *mix(IplImage *lenaImage, IplImage *scaleDownImage) {
//	int i, j; 
//	IplImage* mixImage = cvCreateImage(cvGetSize(lenaImage), lenaImage->depth, lenaImage->nChannels); // 합성된 이미지 생성
//	CvScalar pixelValue,temp;
//	
//	for (i = 0; i < scaleDownImage->height; i++) {
//		for (j = 0; j < scaleDownImage->width; j++) {
//
//			pixelValue = cvGet2D(scaleDownImage, i, j); // 합성할 이미지의 색 얻기
//			if (pixelValue.val[0] < 240) {
//				temp = cvGet2D(scaleDownImage, i, j); // 합성할 이미지 보다 어두우면 그 색을 설정
//				cvSet2D(mixImage, i, j, temp);
//			}
//			else {
//				temp = cvGet2D(lenaImage, i, j); // 그외는 원본 값
//				cvSet2D(mixImage, i, j, temp);
//			}
//		}
//	}
//	return mixImage;
//}

IplImage *mix(IplImage *mainImage, IplImage *scaleDownImage) {
	int i, j;
	IplImage* mixImage = cvCreateImage(cvGetSize(mainImage), mainImage->depth, mainImage->nChannels); // 합성된 이미지 생성
	CvScalar pixelValue, temp;
	

	for (i = 0; i < scaleDownImage->height; i++) {
		for (j = 0; j < scaleDownImage->width; j++) {

			pixelValue = cvGet2D(scaleDownImage, i, j); // 합성할 이미지의 색 얻기
			if (pixelValue.val[0] == 255) {
				temp = cvGet2D(mainImage, i, j); // 그외는 원본 값
				cvSet2D(mixImage, i, j, temp);
			}
			else {
				temp = cvGet2D(scaleDownImage, i, j); // 합성할 이미지 보다 어두우면 그 색을 설정
				cvSet2D(mixImage, i, j, temp);
			}

		}
	}
	return mixImage;
}
*/
//----------------------------------------------------------------------------------------------------------------------
// 골격화
//----------------------------------------------------------------------------------------------------------------------
#include <opencv\cv.h>
#include <opencv\highgui.h>

#define THRESHOLD 130

IplImage *gray2binaryImage(IplImage *grayimage, int Threshold);
IplImage *Erosion(IplImage *binaryImage);
IplImage *Dilation(IplImage *binaryImage);
IplImage *Open(IplImage *binaryImage);

IplImage *Skeletonization(IplImage *binaryImage, IplImage *inputImage, IplImage *SkeletonImage);

int main() {

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *SkeletonImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *binaryImage;

	cvSetZero(SkeletonImage);
	binaryImage = gray2binaryImage(inputImage, THRESHOLD);
	SkeletonImage = Skeletonization(binaryImage, inputImage, SkeletonImage);
	
	cvShowImage("Input Image", inputImage);
	cvShowImage("Skeletonization Image", SkeletonImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&SkeletonImage);

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

IplImage *Skeletonization(IplImage *binaryImage, IplImage *inputImage, IplImage *SkeletonImage) {
	int i, j, sum = 1;
	bool first = true;
	CvScalar erostempval, opentempval;

	IplImage *OpenImage;
	IplImage *ErosionImage;
	while (sum) {
		if (first == true) {
			ErosionImage = binaryImage;
			OpenImage = Open(ErosionImage);
			for (i = 0; i < inputImage->height; i++) {
				for (j = 0; j < inputImage->width; j++) {
					erostempval = cvGet2D(ErosionImage, i, j);
					opentempval = cvGet2D(OpenImage, i, j);

					if (erostempval.val[0] != opentempval.val[0])
						cvSet2D(SkeletonImage, i, j, cvScalar(255));
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
						cvSet2D(SkeletonImage, i, j, cvScalar(255));

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
	return SkeletonImage;
}
