
#include <stdio.h>
#include <stdlib.h>

// struct for rgb colours
typedef struct RGBColor {
	int R;
	int G;
	int B;
} RGB;

// struct for ycc colours
typedef struct YCCColor {
	int Y;
	int Cb;
	int Cr;

} YCC;

// print rgb struct
void printColorRGB(RGB rgb) {
	printf("R : %d | G : %d | B : %d\n", rgb.R, rgb.G, rgb.B);
}

// print ycc struct
void printColorYCC(YCC ycc) {
	printf("Y : %d | Cb : %d | Cr : %d\n", ycc.Y, ycc.Cb, ycc.Cr);
}

void convertRGBToYCC(RGB rgb, YCC *ycc) {
	
	ycc->Y  = 16.0f  + (65*rgb.R + 129*rgb.G + 25*rgb.B)/256.0f;
	ycc->Cb = 128.0f + (-38*rgb.R - 74*rgb.G + 112*rgb.B)/256.0f;
	ycc->Cr = 128.0f + (112*rgb.R - 94*rgb.G - 18*rgb.B)/256.0f;
	

}

int convertToFixedPoint(int i) {
	int result = i << 14;	
	return result;
}

int convertFloatToInt(float f) {
	int result = (f / 4) * 65536;
	return result;
}

int convertToInt(int f) {
	
	int result = f >> 14;
	return result;
}

void convertYCCToRGB(RGB *rgb, const YCC ycc) {
	
	const int tempY  = 19070 * (ycc.Y - 16);
	const int tempCr = (ycc.Cr - 128);
	const int tempCb = (ycc.Cb - 128);

	rgb->R = convertToInt(tempY + 26148 * tempCr);
	rgb->G = convertToInt(tempY - 13320 * tempCr - 6406 * tempCb);
	rgb->B = convertToInt(tempY + 33062 * tempCb);
	
}

int main(int argc, char** argv) {

	RGB rgb;
/*	rgb.R = 2.0f;
	rgb.G = 3.0f;
	rgb.B = 5.0f;
*/
	YCC ycc;
	ycc.Y  = 160;
	ycc.Cb = 104;
	ycc.Cr = 182;
/*
	printColorRGB(rgb);	
	printColorYCC(ycc);

	convertRGBToYCC(rgb, &ycc);
	printColorRGB(rgb);	
	printColorYCC(ycc);
*/


	
	
//	printColorRGB(rgb);
	//printColorYCC(ycc);
	convertYCCToRGB(&rgb, ycc);
	printColorRGB(rgb);
//	printColorYCC(ycc);

	//int temp = convertToFixedPoint(2);
//	printf("the result : %d \n", temp);
//	printf("the result : %d \n", convertToInt(temp));
	//printf("the result : %d \n", convertFloatToInt(1.164));
/*
	printf("result 2.018: %d\n", convertFloatToInt(2.018));
	printf("result 1.164: %d\n", convertFloatToInt(1.164));
	printf("result 1.596: %d\n", convertFloatToInt(1.596));
	printf("result 0.813: %d\n", convertFloatToInt(0.813));
	printf("result 0.391: %d\n", convertFloatToInt(0.391));
*/

	return 0;
}

