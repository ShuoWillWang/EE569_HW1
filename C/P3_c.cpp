// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//******************************************************************************************************************
//merge R, G and B sequence for P3_c
//******************************************************************************************************************


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedataori[100000000];
extern unsigned char Imagedataex[100000000];
extern unsigned char Imagedatasin[100000000];
extern unsigned char Imagedatasin1[100000000];
extern unsigned char Imagedatasin2[100000000];
extern unsigned char Imagedatasin3[100000000];

extern double PSNR(int s, int Size1, int Size2, unsigned char *Imagedatasin, unsigned char *Imagedataori);
extern double PSNR_m(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataori);

void Merg(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedatasin1, unsigned char *Imagedatasin2, unsigned char *Imagedatasin3, unsigned char *Imagedata, unsigned char *Imagedataori)
{
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedata[BytesPerPixel * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
			Imagedata[BytesPerPixel * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
			Imagedata[BytesPerPixel * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
		}
	}
	for (int s = 0; s < BytesPerPixel; s++)
	{
		cout << PSNR_m(s, BytesPerPixel, Size1, Size2, Imagedata, Imagedataori) << endl;
	}
}

void P3_c(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3, char *a4, char *a5)
{
	FILE *file;

	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedatasin1, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(a3, "rb"))) {
		cout << "Cannot open file: " << a3 << endl;
		exit(1);
	}
	fread(Imagedataori, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	if (!(file = fopen(a4, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedatasin2, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(a5, "rb"))) {
		cout << "Cannot open file: " << a3 << endl;
		exit(1);
	}
	fread(Imagedatasin3, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	Merg(BytesPerPixel, Size1, Size2, Imagedatasin1, Imagedatasin2, Imagedatasin3, Imagedata, Imagedataori);

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2 * Size1 * BytesPerPixel, file);
	fclose(file);
	system("pause");
}
