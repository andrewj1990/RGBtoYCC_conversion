
#include <stdio.h>
#include <stdlib.h>

// struct for rgb colours
typedef struct RGBColor {
	float R;
	float G;
	float B;
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

int main(int argc, char** argv) {

	RGB rgb;
	rgb.R = 2.0f;
	rgb.G = 3.0f;
	rgb.B = 5.0f;

	YCC ycc;
	ycc.Y  = 3;
	ycc.Cb = 4;
	ycc.Cr = 1;

	printColorRGB(rgb);	
	printColorYCC(ycc);

	convertRGBToYCC(rgb, &ycc);
	printColorRGB(rgb);	
	printColorYCC(ycc);
		

	return 0;
}

