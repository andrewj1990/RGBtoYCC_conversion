
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

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

void readFile(char* file_name)
{
	
	FILE* fp;
	fp = fopen(file_name, "r");
	if (fp == NULL) {
		perror("Error opening file\n");
		exit(1);
	}
	
	char c;
	while((c = fgetc(fp)) != EOF)
      		printf("%c", c);
 
	fclose(fp);

}

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
	
	const int tempY  = 19071 * (ycc.Y - 16);
	const int tempCr = (ycc.Cr - 128);
	const int tempCb = (ycc.Cb - 128);

	rgb->R = convertToInt(tempY + 26149 * tempCr);
	rgb->G = convertToInt(tempY - 13320 * tempCr - 6406 * tempCb);
	rgb->B = convertToInt(tempY + 33063 * tempCb);
	
}

void convertYCCToRGB2(int* r, int* g, int* b, int y, int cr, int cb) {
	
	const int tempY  = 19071 * (y - 16);
	const int tempCr = (cr - 128);
	const int tempCb = (cb - 128);

	if ((*r = convertToInt(tempY + 26149 * tempCr)) > 255) 
		*r = 255;
	if ((*g  = convertToInt(tempY - 13320 * tempCr - 6406 * tempCb)) > 255) 
		*g = 255;
	if (*g < 0)
		*g = 0;
	if ((*b = convertToInt(tempY + 33063 * tempCb)) > 255)
		*b = 255;
 	if (*b < 0)
		*b = 0;

}

int main(int argc, char** argv) 
{

	char c;
	FILE* fp;
	char* file_name = "output1.txt";

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		perror("Error opening file\n");
		exit(1);
	}

	int a, b, d;
	fscanf(fp, "%d %d %d", &a, &b, &d);

	int size = a*b;

 	int Y[size], Cb[size], Cr[size];
	
	int i;
	for (i = 0; i < size; i++) {
		fscanf(fp, "%d ", &Y[i]);
		//printf("%d ", Y[i]);
	}
	//printf("\n");

	for (i = 0; i < size; i++) {
		fscanf(fp, "%d ", &Cb[i]);
		//printf("%d ", Cb[i]);
	}
	//printf("\n");

	for (i = 0; i < size; i++) {
		fscanf(fp, "%d ", &Cr[i]);
		//printf("%d ", Cr[i]);
	}
	//printf("%d %d \n", size, d);
	//printf("\n");

	fclose(fp);

	int R[size];
	int G[size];
	int B[size];

	for (i = 0; i < size; ++i) {
		
		convertYCCToRGB2(&R[i], &G[i], &B[i], Y[i], Cr[i], Cb[i]);
	}

	for (i = 0; i < size; i++) {

		printf("YCC : ");
		printf("%d ", Y[i]);
		printf("%d ", Cb[i]);
		printf("%d ", Cr[i]);
		printf("\n");
		printf("RGB : ");
		printf("%d ", R[i]);
		printf("%d ", G[i]);
		printf("%d ", B[i]);
		printf("\n");
		printf("\n");
	}

	fp = fopen("rgb_out.txt", "w");
	if (fp == NULL) {
		perror("Error opening file\n");
		exit(1);
	}

	fprintf(fp, "%d %d %d ",a, b, d);
	for (i = 0; i < size; ++i) {
		fprintf(fp, "%d ", R[i]);	
	}
	for (i = 0; i < size; ++i) {
		fprintf(fp, "%d ", G[i]);	
	}
	for (i = 0; i < size; ++i) {
		fprintf(fp, "%d ", B[i]);	
	}
	
	fclose(fp);
/*
	RGB rgb;
	YCC ycc;

	int Y[SIZE];
	int Cb[SIZE];
	int Cr[SIZE];

	int R[SIZE] = {
		255, 0, 255, 0
	};
	int G[SIZE] = {
		0, 255, 0, 0
	};
	int B[SIZE] = {
		0, 0, 255, 255
	};

	int i = 0;
	for (i = 0; i < SIZE; ++i) {
		rgb.R  = R[i];	
		rgb.G  = G[i];	
		rgb.B  = B[i];	
		
		convertRGBToYCC(rgb, &ycc);
		
		Y[i] = ycc.Y;
		Cb[i] = ycc.Cb;
		Cr[i] = ycc.Cr;

		printColorYCC(ycc);	
		printColorRGB(rgb);
		printf("\n");
	}
	
	readFile("output1.txt");
*/	
	return 0;
}

