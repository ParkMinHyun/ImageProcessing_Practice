/*1번-FFT&RFFT*/
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdlib.h>

typedef struct Complex {
	double Re; //Variables for real numbers 실수부
	double Im; //Variables for imaginary numbers 허수부
};

Complex **FFT; //Pointer to save FFT result

IplImage* FFT2d(IplImage* inpuImage);
void FFT1d(Complex *X, int N, int Log2N);
void Scrambling(Complex *X, int N, int Log2N);
void Butterfly(Complex *X, int N, int Log2N, int mode);
void SaveImage(char *saveImageName, IplImage *saveImage);
int ReverseBitOrder(int index, int Log2N);
double ReceiveSNRvalue(IplImage* originalImage, IplImage *outputImage);
IplImage* RFFT2d(IplImage* FFTSpectrum);
void RFFT1d(Complex *X, int N, int Log2N);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* FFTSpectrum;
	IplImage* RFFTImage;
	double SNRValue;

	FFTSpectrum = FFT2d(inputImage); //Fast Fourier Transform
	//SaveImage("FFTSPECTRUM.jpg", FFTSpectrum);
	RFFTImage = RFFT2d(FFTSpectrum); // Reverse 역방향 FFT
	//SaveImage("RFFTImage.jpg", RFFTImage);
	SNRValue = ReceiveSNRvalue(inputImage, RFFTImage);
	printf("SNRValue : %f\n", SNRValue);

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

	for (i = 0; i < inputImage->height; i++) {
		FFT[i] = new Complex[inputImage->width];
		temp[i] = new unsigned char[inputImage->width];
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
		{
			Data[j].Re = (double)inputImage->imageData[i*inputImage->widthStep + j];
			// copy one row of input, the real component value is the value of the image
			//입력의 한 행을 복사, 실수 성분 값은 영상의 값
			Data[j].Im = 0.0; //The complex component value is 0 복소 성분 값은 0
		}
		FFT1d(Data, inputImage->width, Log2N); //1D FFT 1차원 FFT

		for (j = 0; j < inputImage->width; j++) { //Save Results
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

	for (i = 0; i < inputImage->width; i++) {
		for (j = 0; j < inputImage->height; j++) {
			Data[j].Re = FFT[j][i].Re; //Copy a row of images 영상의 한 열을 복사
			Data[j].Im = FFT[j][i].Im;
		}

		FFT1d(Data, inputImage->height, Log2N); //1D FFT 1차원 FFT

		for (j = 0; j < inputImage->height; j++) { //Save Results
			FFT[j][i].Re = Data[j].Re;
			FFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
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
	for (i = 0; i < inputImage->height; i += inputImage->height / 2) {
		for (j = 0; j < inputImage->width; j += inputImage->width / 2) {
			for (row = 0; row < inputImage->height / 2; row++) {
				for (col = 0; col < inputImage->width / 2; col++) {
					tempScalar = cvGet2D(tempImage, i + row, j + col);
					temp[(inputImage->height / 2 - 1) - row + i][(inputImage->width / 2 - 1) - col + j] = (unsigned char)tempScalar.val[0];
				}
			}
		}
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
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

	for (i = 0; i < N; i++) {
		temp[i].Re = X[ReverseBitOrder(i, Log2N)].Re;
		temp[i].Im = X[ReverseBitOrder(i, Log2N)].Im;
	}

	for (i = 0; i < N; i++) {
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

	for (i = 0; i < Log2N; i++) {
		Value = pow(2., i + 1);

		if (mode == 1) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j * 2.0 * PI / Value);
				Y[j].Im = -sin(j * 2.0 * PI / Value);
			}
		}
		if (mode == 2) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = sin(j*2.0*PI / Value);
			}
		}

		start = 0;

		for (k = 0; k < N / (int)Value; k++) {
			for (j = start; j < start + (int)(Value / 2); j++) {
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
		for (i = 0; i < N; i++) {
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

	for (i = 0; i < Log2N; i++) {
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
	for (i = 0; i < FFTSpectrum->height; i++) {
		RFFT[i] = new Complex[FFTSpectrum->width];
	}

	for (i = 0; i < FFTSpectrum->height; i++) {
		for (j = 0; j < FFTSpectrum->width; j++) { //Copy one row 한 행을 복사
			Data[j].Re = FFT[i][j].Re;
			Data[j].Im = FFT[i][j].Im;
		}
		RFFT1d(Data, FFTSpectrum->width, Log2N); //1D RFFT

		for (j = 0; j < FFTSpectrum->width; j++) {
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

	for (i = 0; i < FFTSpectrum->width; i++) {
		for (j = 0; j < FFTSpectrum->height; j++) {
			Data[j].Re = RFFT[j][i].Re; //Copy one column 한 열을 복사
			Data[j].Im = RFFT[j][i].Im;
		}

		RFFT1d(Data, FFTSpectrum->width, Log2N); //1D RFFT

		for (j = 0; j < FFTSpectrum->width; j++) {//Save Results 결과 저장
			RFFT[j][i].Re = Data[j].Re;
			RFFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i < FFTSpectrum->width; i++) {
		for (j = 0; j < FFTSpectrum->height; j++) {
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

void SaveImage(char *saveImageName, IplImage *saveImage) {
	cvSaveImage(saveImageName, saveImage);
}

double ReceiveSNRvalue(IplImage* originalImage, IplImage *outputImage)
{
	double SNRValue;
	double *m_InputImage;
	double *m_SkeletonImage;
	double OrgSum, ErrSum, MeanErr, MeanOrg;
	int i, j;

	OrgSum = 0.0;
	ErrSum = 0.0;

	CvScalar originalImagePixel, outputImagePixel;
	int m_Size = originalImage->width * originalImage->height;

	for (int i = 0; i < originalImage->height; i++) {
		for (int j = 0; j < originalImage->width; j++) {
			originalImagePixel = cvGet2D(originalImage, i, j);
			outputImagePixel = cvGet2D(outputImage, i, j);
			ErrSum += ((double)originalImagePixel.val[0] - outputImagePixel.val[0]) *
				((double)originalImagePixel.val[0] - outputImagePixel.val[0]);
		}
	}
	MeanErr = ErrSum / m_Size;

	for (int i = 0; i < originalImage->height; i++) {
		for (int j = 0; j < originalImage->width; j++) {
			originalImagePixel = cvGet2D(originalImage, i, j);
			OrgSum += ((double)originalImagePixel.val[0]) * ((double)originalImagePixel.val[0]);
		}
	}
	MeanOrg = OrgSum / m_Size;

	SNRValue = (10 * (double)log10(MeanOrg / MeanErr));
	return SNRValue;
}

//-------------------------------------------------------------------------------------------------
// 2번 - 회전, 축소, 합성
//-------------------------------------------------------------------------------------------------
/*
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define SUB_SAMPLING_RATE 2 // ��� ����
#define DEGREE 45 // ȸ�� ����

void SaveImage(char *saveImageName, IplImage *saveImage);
void Swap(double *a, double *b); // ������ ��ȯ
void BubbleSort(double *A, int MAX); // ������ ����
IplImage *ScaleDown_Median(IplImage *scaleDownImage);
IplImage *ScaleDown_RGB(IplImage *sclaeDownImage, IplImage *tempImage);
IplImage *ScaleDown_Average(IplImage *scaleDownImage);
IplImage *Mix(IplImage *mainImage, IplImage *scaleDownImage);
IplImage *Rotation(IplImage *mainImage, IplImage *scaleDownImage);

int main() {
	//IplImage* lena = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//IplImage* Rock = cvLoadImage("Rock.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* lena = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage* heart = cvLoadImage("heart.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage* Rock = cvLoadImage("Rock.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage* human = cvLoadImage("human2.png", CV_LOAD_IMAGE_COLOR);
	IplImage* scaleDownImage = cvCreateImage(cvSize(lena->width, lena->height), lena->depth, lena->nChannels);
	IplImage* rotationImage = cvCreateImage(cvSize(lena->width, lena->height), lena->depth, lena->nChannels);
	IplImage* mixImage = cvCreateImage(cvGetSize(lena), lena->depth, lena->nChannels);

	int i, j;
	CvScalar temp;

	//scaleDownImage = ScaleDown_Median(Rock); // 미디언 축소
	//scaleDownImage = ScaleDown_Average(Rock);  // 평균 축소
	scaleDownImage = ScaleDown_RGB(human, scaleDownImage); // 단순 축소(RGB 가능)
	rotationImage = Rotation(scaleDownImage, rotationImage);
	mixImage = Mix(lena, rotationImage);

	//cvAdd(lena, rotationImage, mixImage, NULL);
	//SaveImage("mix.jpg", mix);

	cvNamedWindow("lena image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("scaleDown image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("rotation image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mix image", CV_WINDOW_AUTOSIZE);

	cvShowImage("lena image", lena);
	cvShowImage("scaleDown image", scaleDownImage);
	cvShowImage("rotation image", rotationImage);
	cvShowImage("mix image", mixImage);

	cvWaitKey();

	cvDestroyWindow("lena image");
	cvDestroyWindow("scaleDown image");
	cvDestroyWindow("rotation image");
	cvDestroyWindow("mix image");

	cvReleaseImage(&lena);
	cvReleaseImage(&scaleDownImage);
	cvReleaseImage(&rotationImage);
	cvReleaseImage((IplImage**)&mixImage);

	return 0;
}

void SaveImage(char *saveImageName, IplImage *saveImage) {
	cvSaveImage(saveImageName, saveImage);
}

void Swap(double *a, double *b) {
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(double *A, int MAX) {
	int i, j;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				Swap(&A[j], &A[j + 1]);
			}
		}
	}
}

IplImage *ScaleDown_RGB(IplImage *scaleDownImage, IplImage *tempImage) {
	int i, j;

	cvSetZero(tempImage);
	CvScalar pixelValue;

	for (i = 0; i < scaleDownImage->height; i++) {
		for (j = 0; j < scaleDownImage->width; j++) {

			if (i % 2 == 0 && j % 2 == 0) {
				pixelValue = cvGet2D(scaleDownImage, i, j);
				cvSet2D(tempImage, i / 2, j / 2, pixelValue);
			}

		}
	}
	return tempImage;
}
IplImage *ScaleDown_Average(IplImage *scaleDownImage) {
	int i, j, n, m, k, index = 0;
	double *Mask, *OutputValue, Sum = 0.0;
	CvScalar tempScalar;

	Mask = new double[SUB_SAMPLING_RATE * SUB_SAMPLING_RATE]; //마스크 크기

	IplImage *outputImage = cvCreateImage(cvSize((scaleDownImage->width + 1) / SUB_SAMPLING_RATE, (scaleDownImage->height + 1) / SUB_SAMPLING_RATE), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(scaleDownImage->width + 1, scaleDownImage->height + 1), 8, 1);

	OutputValue = new double[(scaleDownImage->width + 1) / SUB_SAMPLING_RATE * (scaleDownImage->height + 1) / SUB_SAMPLING_RATE];

	cvSetZero(tempImage);

	for (i = 0; i<scaleDownImage->height; i++)
	{
		for (j = 0; j<scaleDownImage->width; j++)
		{
			cvSet2D(tempImage, i, j, cvGet2D(scaleDownImage, i, j));
		}
	}


	for (i = 0; i<scaleDownImage->height; i = i + SUB_SAMPLING_RATE) {
		for (j = 0; j<scaleDownImage->width; j = j + SUB_SAMPLING_RATE) {
			for (n = 0; n<SUB_SAMPLING_RATE; n++) {
				for (m = 0; m<SUB_SAMPLING_RATE; m++)
				{
					tempScalar = cvGet2D(tempImage, i + n, j + m);
					Mask[n*SUB_SAMPLING_RATE + m] = tempScalar.val[0]; //마스크 크기의 화소값 배열 만듬
				}
			}
			for (k = 0; k<SUB_SAMPLING_RATE*SUB_SAMPLING_RATE; k++) { //배열 값들 합함
				Sum += Mask[k];
			}

			OutputValue[index++] = (Sum / (SUB_SAMPLING_RATE * SUB_SAMPLING_RATE)); //Sum값 마스크 크기로 나누어서 평균값 배열 만듬
			Sum = 0.0;
		}
	}

	for (i = 0; i<outputImage->height; i++) { //OutputValue 행렬 값들 outputImage에 입력
		for (j = 0; j<outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvScalar(OutputValue[i*outputImage->width + j]));
		}
	}
	return outputImage;
}
IplImage *ScaleDown_Median(IplImage *sclaeDownImage) {
	int i, j, n, m, k, index = 0;
	double *Mask, *Mask1, *Mask2, *OutputValue, *OutputValue1, *OutputValue2;
	CvScalar tempScalar;

	Mask = new double[SUB_SAMPLING_RATE * SUB_SAMPLING_RATE];

	IplImage *outputImage = cvCreateImage(cvSize((sclaeDownImage->width + 1) / SUB_SAMPLING_RATE, (sclaeDownImage->height + 1) / SUB_SAMPLING_RATE), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(sclaeDownImage->width + 1, sclaeDownImage->height + 1), 8, 1);

	OutputValue = new double[(sclaeDownImage->width + 1) / SUB_SAMPLING_RATE*(sclaeDownImage->height + 1) / SUB_SAMPLING_RATE];
	cvSetZero(tempImage);

	for (i = 0; i < sclaeDownImage->height; i++) {
		for (j = 0; j < sclaeDownImage->width; j++) {
			cvSet2D(tempImage, i, j, cvGet2D(sclaeDownImage, i, j));
		}
	}

	for (i = 0; i < sclaeDownImage->height; i = i + SUB_SAMPLING_RATE) {
		for (j = 0; j < sclaeDownImage->width; j = j + SUB_SAMPLING_RATE) {
			for (n = 0; n < SUB_SAMPLING_RATE; n++) {
				for (m = 0; m < SUB_SAMPLING_RATE; m++) {
					tempScalar = cvGet2D(tempImage, i + n, j + m);
					Mask[n*SUB_SAMPLING_RATE + m] = tempScalar.val[0];
				}
			}
			BubbleSort(Mask, SUB_SAMPLING_RATE * SUB_SAMPLING_RATE);
			OutputValue[index++] = Mask[(int)(SUB_SAMPLING_RATE * SUB_SAMPLING_RATE / 2)];
		}
	}

	for (i = 0; i < outputImage->height; i++) {
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvScalar(OutputValue[i*outputImage->width + j]));
		}
	}
	return outputImage;
}

IplImage *Rotation(IplImage *inputImage, IplImage *outputImage) {

	int i, j, Center_y, Center_x, source_y, source_x;
	double Radian, cosR, sinR;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0;

	cosR = cos(Radian);
	sinR = sin(Radian);

	Center_y = inputImage->height / 2;
	Center_x = inputImage->width / 2;

	for (i = 0; i < inputImage->height; i++) {
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

IplImage *Mix(IplImage *mainImage, IplImage *scaleDownImage) {
	int i, j;
	IplImage* mixImage = cvCreateImage(cvGetSize(mainImage), mainImage->depth, mainImage->nChannels);
	CvScalar pixelValue, temp;

	for (i = 0; i < scaleDownImage->height; i++) {
		for (j = 0; j < scaleDownImage->width; j++) {

			pixelValue = cvGet2D(scaleDownImage, i, j);
			if (pixelValue.val[0] != 0) {
				temp = cvGet2D(scaleDownImage, i, j);
				cvSet2D(mixImage, i, j, temp);
			}
			else {
				temp = cvGet2D(mainImage, i, j);
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
//#include <opencv\cv.h>
//#include <opencv\highgui.h>
//
//#define THRESHOLD 130
//
//IplImage *gray2binaryImage(IplImage *grayimage, int Threshold);
//IplImage *Erosion(IplImage *binaryImage);
//IplImage *Dilation(IplImage *binaryImage);
//IplImage *Open(IplImage *binaryImage);
//IplImage *Skeletonization(IplImage *binaryImage, IplImage *SkeletonImage);
//
//int main() {
//
//	IplImage *inputImage = cvLoadImage("rect2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	IplImage *SkeletonImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
//	IplImage *binaryImage;
//f
//	cvSetZero(SkeletonImage);
//	binaryImage = gray2binaryImage(inputImage, THRESHOLD);
//	SkeletonImage = Skeletonization(binaryImage, SkeletonImage);
//	
//	cvShowImage("Input Image", inputImage);
//	cvShowImage("Skeletonization Image", SkeletonImage);
//	cvWaitKey();
//
//	cvDestroyAllWindows();
//	cvReleaseImage(&inputImage);
//	cvReleaseImage(&SkeletonImage);
//
//	return 0;
//}
//
//IplImage *Skeletonization(IplImage *binaryImage, IplImage *SkeletonImage) {
//	int i, j, sum = 1;
//	bool first = true;
//	CvScalar erostempval, opentempval;
//
//	IplImage *OpenImage;
//	IplImage *ErosionImage;
//	while (sum) {
//		if (first == true) {
//			ErosionImage = binaryImage;
//			OpenImage = Open(ErosionImage);
//			for (i = 0; i < binaryImage->height; i++) {
//				for (j = 0; j < binaryImage->width; j++) {
//					erostempval = cvGet2D(ErosionImage, i, j);
//					opentempval = cvGet2D(OpenImage, i, j);
//
//					if (erostempval.val[0] != opentempval.val[0])
//						cvSet2D(SkeletonImage, i, j, cvScalar(255));
//				}
//			}
//			first = false;
//		}
//		else {
//			ErosionImage = Erosion(ErosionImage);
//			OpenImage = Open(ErosionImage);
//
//			for (i = 0; i < binaryImage->height; i++) {
//				for (j = 0; j < binaryImage->width; j++) {
//					erostempval = cvGet2D(ErosionImage, i, j);
//					opentempval = cvGet2D(OpenImage, i, j);
//
//					if (erostempval.val[0] != opentempval.val[0])
//						cvSet2D(SkeletonImage, i, j, cvScalar(255));
//
//				}
//			}
//		}
//
//		sum = 0;
//		for (i = 0; i < binaryImage->height; i++) {
//			for (j = 0; j < binaryImage->width; j++) {
//
//				sum += cvGet2D(OpenImage, i, j).val[0];
//			}
//			if (sum != 0)
//				break;
//		}
//	}
//	return SkeletonImage;
//}
//
//
//IplImage *Erosion(IplImage *binaryImage) {
//	int i, j, n, m, Erosion_Sum = 0;
//	CvScalar tempValue;
//	double Erosion_Mask[3][3] = { { 0,255,0 },{ 255,255,255 },{ 0,255,0 } };
//
//	IplImage *tempImage = cvCreateImage(cvSize(binaryImage->width + 2, binaryImage->height + 2), 8, 1);
//	IplImage *outputImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);
//
//	cvSetZero(tempImage);
//
//	for (i = 0; i < binaryImage->height; i++) {
//		for (j = 0; j < binaryImage->width; j++) {
//			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
//		}
//	}
//
//	for (i = 0; i < binaryImage->height; i++) {
//		for (j = 0; j < binaryImage->width; j++) {
//			for (n = 0; n < 3; n++) {
//				for (m = 0; m < 3; m++) {
//					tempValue = cvGet2D(tempImage, i + n, j + m);
//					if (Erosion_Mask[n][m] == 255 && Erosion_Mask[n][m] == tempValue.val[0])
//						Erosion_Sum += 1;
//
//				}
//			}
//			if (Erosion_Sum == 5)
//				cvSet2D(outputImage, i, j, cvScalar(255));
//			else {
//				cvSet2D(outputImage, i, j, cvScalar(0));
//			}
//			Erosion_Sum = 0;
//		}
//
//	}
//	cvReleaseImage(&tempImage);
//	return outputImage;
//
//}
//
//
//IplImage *Dilation(IplImage *binaryImage) {
//	int i, j, n, m, Dilation_Sum = 0;
//	CvScalar tempValue;
//	double Dilation_Mask[3][3] = { { 255,0,255 },{ 0,0,0 },{ 255,0,255 } };
//
//	IplImage *tempImage = cvCreateImage(cvSize(binaryImage->width + 2, binaryImage->height + 2), 8, 1);
//	IplImage *outputImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);
//
//	cvSetZero(tempImage);
//
//	for (i = 0; i < binaryImage->height; i++) {
//		for (j = 0; j < binaryImage->width; j++) {
//			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
//		}
//	}
//
//	for (i = 0; i < binaryImage->height; i++) {
//		for (j = 0; j < binaryImage->width; j++) {
//			for (n = 0; n < 3; n++) {
//				for (m = 0; m < 3; m++) {
//					tempValue = cvGet2D(tempImage, i + n, j + m);
//					if (Dilation_Mask[n][m] == 0 && Dilation_Mask[n][m] == tempValue.val[0])
//						Dilation_Sum += 1;
//
//				}
//			}
//			if (Dilation_Sum == 5)
//				cvSet2D(outputImage, i, j, cvScalar(0));
//			else {
//				cvSet2D(outputImage, i, j, cvScalar(255));
//			}
//			Dilation_Sum = 0;
//		}
//
//	}
//	cvReleaseImage(&tempImage);
//	return outputImage;
//
//}
//
//IplImage *Open(IplImage *binaryImage) {
//	IplImage *outImage = cvCreateImage(cvSize(binaryImage->width, binaryImage->height), 8, 1);
//	outImage = Erosion(binaryImage);
//	outImage = Dilation(outImage);
//
//	return outImage;
//}
//
//
//IplImage *gray2binaryImage(IplImage *grayImage, const int Threshold) {
//
//	IplImage *tempImage = cvCreateImage(cvSize(grayImage->width, grayImage->height), 8, 1);
//	IplImage *outImage = cvCreateImage(cvSize(grayImage->width, grayImage->height), 8, 1);
//	CvScalar tempValue;
//	int i, j;
//
//
//	for (i = 0; i < grayImage->height; i++) {
//		for (j = 0; j < grayImage->width; j++) {
//			tempValue = cvGet2D(grayImage, i, j);
//			if (tempValue.val[0] > THRESHOLD)
//				cvSet2D(outImage, i, j, cvScalar(255));
//			else
//				cvSet2D(outImage, i, j, cvScalar(0));
//		}
//	}
//
//	cvReleaseImage(&tempImage);
//
//	return outImage;
//}
