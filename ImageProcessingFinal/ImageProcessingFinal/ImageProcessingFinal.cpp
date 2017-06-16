/*1번-FFT&RFFT*/
/*
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
	IplImage* inputImage = cvLoadImage("input_1.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* FFTSpectrum;
	IplImage* IFFTImage;
	double SNRValue;

	FFTSpectrum = FFT2d(inputImage); //Fast Fourier Transform
	SaveImage("FFT_122179 박민현.bmp", FFTSpectrum);
	IFFTImage = RFFT2d(FFTSpectrum); // Reverse 역방향 FFT
	SaveImage("IFFT_122179 박민현.bmp", IFFTImage);
	SNRValue = ReceiveSNRvalue(inputImage, IFFTImage);
	printf("SNRValue : %f\n", SNRValue);

	cvShowImage("Input Image", inputImage);
	cvShowImage("FFT Spectrum", FFTSpectrum);
	cvShowImage("RFFT Image", IFFTImage);

	cvWaitKey();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&FFTSpectrum);
	cvReleaseImage(&IFFTImage);

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
*/
//-------------------------------------------------------------------------------------------------
// 2번 - 회전, 축소, 합성
//-------------------------------------------------------------------------------------------------

#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define SUB_SAMPLING_RATE 2 // 축소 비율
#define DEGREE 45 // 회전 각도

void SaveImage(char *saveImageName, IplImage *saveImage);
IplImage * Reduction(IplImage *inputImage, IplImage *outputImage, IplImage *tempImage);
IplImage * Rotation(IplImage *rotationImage, IplImage *outputImage);
IplImage * TransSizeImageRotation(IplImage *inputImage);
IplImage * Mix(IplImage *inputImage, IplImage *rotationImage, IplImage *outputImage);

int main()
{
	IplImage *inputImage = cvLoadImage("input_2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *scaleDownImage = cvCreateImage(cvSize((inputImage->width + 1) / SUB_SAMPLING_RATE, (inputImage->height + 1) / SUB_SAMPLING_RATE), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width, inputImage->height + 1), 8, 1);
	IplImage *outputImage;
	IplImage *rotationImage;				// 90도 단위 회전 시 
	IplImage *sizeTransferRotationImage;	// 45도 등 크기에 벗어나는 회전 시
	IplImage *sumImage = cvCreateImage(cvSize(inputImage->width+1, inputImage->height+1), inputImage->depth, inputImage->nChannels);

	scaleDownImage = Reduction(inputImage, scaleDownImage, tempImage);
	outputImage = cvCreateImage(cvSize(scaleDownImage->width, scaleDownImage->height), scaleDownImage->depth, scaleDownImage->nChannels);
	rotationImage = Rotation(scaleDownImage, outputImage); 
	sizeTransferRotationImage = TransSizeImageRotation(scaleDownImage);
	sumImage = Mix(inputImage, sizeTransferRotationImage, sumImage); 

	SaveImage("SubSampling_122179 박민현.bmp", scaleDownImage);
	SaveImage("Rotation_122179 박민현.bmp", sizeTransferRotationImage);
	SaveImage("Combination_122179 박민현.bmp", sumImage);
	cvShowImage("Input Image", inputImage);
	cvShowImage("sub Sampling Image", scaleDownImage);
	cvShowImage("Rotation", sizeTransferRotationImage);
	cvShowImage("Sum Image", sumImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&scaleDownImage);
	cvReleaseImage(&sizeTransferRotationImage);
	cvReleaseImage(&sumImage);

	return 0;
}

void SaveImage(char *saveImageName, IplImage *saveImage) {
	cvSaveImage(saveImageName, saveImage);
}
IplImage * Mix(IplImage *inputImage, IplImage *scaleDownRotationImage, IplImage *outputImage) { // 원본이미지에 축소 회전한 이미지를 합성하는 함수
	int i, j, n, m;
	CvScalar pixelValue;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			pixelValue = cvGet2D(inputImage, i, j);
			cvSet2D(outputImage, i, j, pixelValue);
		}
	}

	for (i = 0; i < scaleDownRotationImage->height; i++) {
		for (j = 0; j < scaleDownRotationImage->width; j++) {
			pixelValue = cvGet2D(scaleDownRotationImage, i, j); // 축소 회전된 이미지 저장

			if (pixelValue.val[0] != 0) { // 검은색 부분은 지우고 가운데에 붙이기
				cvSet2D(outputImage, i + inputImage->height / 8 +10, j + inputImage->width / 8+10, pixelValue);
			}
		}
	}

	return outputImage;
}

IplImage * Reduction(IplImage *inputImage, IplImage *outputImage, IplImage *tempImage) { // 축소 함수
	int i, j, n, m, k, index = 0;
	double *Mask, *OutputValue, Sum = 0.0;
	CvScalar tempScalar;

	Mask = new double[SUB_SAMPLING_RATE * SUB_SAMPLING_RATE];

	OutputValue = new double[(inputImage->width + 1) / SUB_SAMPLING_RATE * (inputImage->height + 1) / SUB_SAMPLING_RATE];

	cvSetZero(tempImage);

	for (i = 0; i < inputImage->height; i++)
	{
		for (j = 0; j < inputImage->width; j++)
		{
			cvSet2D(tempImage, i, j, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i = i + SUB_SAMPLING_RATE) {
		for (j = 0; j < inputImage->width; j = j + SUB_SAMPLING_RATE) {
			for (n = 0; n < SUB_SAMPLING_RATE; n++) {
				for (m = 0; m < SUB_SAMPLING_RATE; m++)
				{
					tempScalar = cvGet2D(tempImage, i + n, j + m);
					Mask[n*SUB_SAMPLING_RATE + m] = tempScalar.val[0];
				}
			}
			for (k = 0; k < SUB_SAMPLING_RATE*SUB_SAMPLING_RATE; k++) {
				Sum += Mask[k];
			}

			OutputValue[index++] = (Sum / (SUB_SAMPLING_RATE * SUB_SAMPLING_RATE));
			Sum = 0.0;
		}
	}

	for (i = 0; i < outputImage->height; i++) { 
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvScalar(OutputValue[i*outputImage->width + j]));
		}
	}

	return outputImage;
}

IplImage * Rotation(IplImage *inputImage, IplImage *outputImage) { // 회전 함수
	int i, j, Center_y, Center_x, source_y, source_x;
	double Radian, cosR, sinR;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0; // degree 값을 radian으로 변경

	cosR = cos(Radian);
	sinR = sin(Radian);

	Center_y = inputImage->height / 2; // 영상의 중심좌표
	Center_x = inputImage->width / 2;

	for (i = 0; i < inputImage->height; i++) { // 좌우반전
		for (j = 0; j < inputImage->width; j++) {
			source_x = (int)((j - Center_x)*cosR + (i - Center_y)*sinR + Center_x); // 회전 변환 행렬을 이용하여 새 좌표값 계산
			source_y = (int)(-(j - Center_x)*sinR + (i - Center_y)*cosR + Center_y);

			if (source_x < 0 || source_y < 0 || source_y >= inputImage->height || source_x >= inputImage->width) { // 좌표가 영상범위 넘어갔을때 0 처리
				Value.val[0] = 0;
			}
			else Value = cvGet2D(inputImage, source_y, source_x);

			cvSet2D(outputImage, i, j, Value);
		}
	}

	return outputImage;
}

IplImage * TransSizeImageRotation(IplImage *inputImage) { // 출력 크기 변환 회전
	int i, j, in_Center_y, in_Center_x, source_y, source_x, out_w, out_h, out_Center_y, out_Center_x;
	double Radian, cosR, sinR, Radian90;
	CvScalar Value;
	IplImage* outputImage;

	Radian = (double)DEGREE * PI / 180.0; // degree 값을 radian 값으로 변경
	Radian90 = (double)90 * PI / 180.0; // 90도를 radian 값으로 변경

	out_w = inputImage->height * cos(Radian90 - Radian) + inputImage->width * cos(Radian); // output 크기 계산
	out_h = inputImage->height * cos(Radian) + inputImage->width * cos(Radian90 - Radian);

	outputImage = cvCreateImage(cvSize(out_w, out_h), inputImage->depth, inputImage->nChannels);

	cosR = cos(Radian);
	sinR = sin(Radian);

	out_Center_y = out_h / 2;
	out_Center_x = out_w / 2;

	in_Center_y = inputImage->height / 2; 
	in_Center_x = inputImage->width / 2;

	for (i = 0; i < out_h; i++) {
		for (j = 0; j < out_w; j++) { 
			source_x = (int)((j - out_Center_x) * cosR + (i - out_Center_y)*sinR + in_Center_x);
			source_y = (int)(-(j - out_Center_x) * sinR + (i - out_Center_y)*cosR + in_Center_y);
			
			if (source_x < 0 || source_y < 0 || source_y >= inputImage->height || source_x >= inputImage->width) Value.val[0] = 0;
			else Value = cvGet2D(inputImage, source_y, source_x);

			cvSet2D(outputImage, i, j, Value);
		}
	}

	return outputImage;
}

//----------------------------------------------------------------------------------------------------------------------
// 골격화
//----------------------------------------------------------------------------------------------------------------------
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>

#define THRESHOLD 130

void SaveImage(char *saveImageName, IplImage *saveImage);
IplImage *gray2binaryImage(IplImage *grayimage, int Threshold);
IplImage *Erosion(IplImage *binaryImage);
IplImage *Dilation(IplImage *binaryImage);
IplImage *Open(IplImage *binaryImage);
IplImage *Skeletonization(IplImage *binaryImage, IplImage *SkeletonImage);
IplImage *FrameProcessing(IplImage *inputImage, IplImage *SkeletonImage);

int main() {

	IplImage *inputImage = cvLoadImage("input_3.png", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *skeletonImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *binaryImage;
	IplImage *frameProcessingImage;

	cvSetZero(skeletonImage);
	binaryImage = gray2binaryImage(inputImage, THRESHOLD);
	skeletonImage = Skeletonization(binaryImage, skeletonImage);
	frameProcessingImage = FrameProcessing(inputImage, skeletonImage);

	SaveImage("Skeletalization_122179 박민현.bmp", skeletonImage);
	SaveImage("SumImage_122179 박민현.bmp", frameProcessingImage);

	cvShowImage("Input Image", inputImage);
	cvShowImage("Skeletonization Image", skeletonImage);
	cvShowImage("FrameProcessingImage Image", frameProcessingImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&skeletonImage);
	cvReleaseImage(&frameProcessingImage);

	return 0;
}

IplImage *FrameProcessing(IplImage *inputImage, IplImage *SkeletonImage) {
	int i, j;
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	CvScalar inputValue, skeletonValue, outputValue, outputValue2;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			inputValue = cvGet2D(inputImage, i, j);
			skeletonValue = cvGet2D(SkeletonImage, i, j);

			if (skeletonValue.val[0] == 255) {
				outputValue.val[0] = 0;
			}
			else {
				outputValue.val[0] = inputValue.val[0] + skeletonValue.val[0] / 2;
			}
			cvSet2D(outputImage, i, j, outputValue);
		}
	}

	return outputImage;
}

IplImage *Skeletonization(IplImage *binaryImage, IplImage *SkeletonImage) {
	int i, j, sum = 1;
	bool first = true;
	CvScalar erostempval, opentempval;

	IplImage *OpenImage;
	IplImage *ErosionImage;
	while (sum) {
		if (first == true) {
			ErosionImage = binaryImage;
			OpenImage = Open(ErosionImage);
			for (i = 0; i < binaryImage->height; i++) {
				for (j = 0; j < binaryImage->width; j++) {
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

			for (i = 0; i < binaryImage->height; i++) {
				for (j = 0; j < binaryImage->width; j++) {
					erostempval = cvGet2D(ErosionImage, i, j);
					opentempval = cvGet2D(OpenImage, i, j);

					if (erostempval.val[0] != opentempval.val[0])
						cvSet2D(SkeletonImage, i, j, cvScalar(255));

				}
			}
		}

		sum = 0;
		for (i = 0; i < binaryImage->height; i++) {
			for (j = 0; j < binaryImage->width; j++) {

				sum += cvGet2D(OpenImage, i, j).val[0];
			}
			if (sum != 0)
				break;
		}
	}
	return SkeletonImage;
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
void SaveImage(char *saveImageName, IplImage *saveImage) {
	cvSaveImage(saveImageName, saveImage);
}*/