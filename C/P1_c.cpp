// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Layer Blending Mode for P1_c
//*********************************************************


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedata1_c[100000000];

const int Screen = 1;
const int Multiply = 2;
const int Soft_Light = 3;
const int Darken = 4;

void P1_c(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3)
{
	FILE *file;
	unsigned char  ***Imagedata_3_1;

	Imagedata_3_1 = new unsigned char**[Size2];
	for(int i = 0;i<Size2;i++)
	{
		Imagedata_3_1[i] = new unsigned char*[Size1];
		for(int j = 0;j<Size1;j++)
		{
			Imagedata_3_1[i][j] = new unsigned char[BytesPerPixel];
		}
	}

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata1_c, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(a3, "rb"))) {
		cout << "Cannot open file: "<< a3 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	//Problem 3

	float temp1, temp2, temp3;
	float tempa1, tempa2, tempa3;
	float tempb1, tempb2, tempb3;
	int a;
	cout << "Input the type: ";
	cin >> a;

	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			if (a == Screen)//screen
			{
				tempa1 = (float)(Imagedata[3 * (Size1 * i + j) + 0]) / 255;
				tempa2 = (float)(Imagedata[3 * (Size1 * i + j) + 1]) / 255;
				tempa3 = (float)(Imagedata[3 * (Size1 * i + j) + 2]) / 255;
				tempb1 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 0]) / 255;
				tempb2 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 1]) / 255;
				tempb3 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 2]) / 255;
				temp1 = 1 - (1 - tempa1)*(1 - tempb1);
				temp2 = 1 - (1 - tempa2)*(1 - tempb2);
				temp3 = 1 - (1 - tempa3)*(1 - tempb3);
				Imagedata_3_1[i][j][0] = 255 * temp1;
				Imagedata_3_1[i][j][1] = 255 * temp2;
				Imagedata_3_1[i][j][2] = 255 * temp3;
			}
			if (a == Multiply)//multiply
			{
				tempa1 = (float)(Imagedata[3 * (Size1 * i + j) + 0]) / 255;
				tempa2 = (float)(Imagedata[3 * (Size1 * i + j) + 1]) / 255;
				tempa3 = (float)(Imagedata[3 * (Size1 * i + j) + 2]) / 255;
				tempb1 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 0]) / 255;
				tempb2 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 1]) / 255;
				tempb3 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 2]) / 255;
				temp1 = tempa1 * tempb1;
				temp2 = tempa2 * tempb2;
				temp3 = tempa3 * tempb3;
				Imagedata_3_1[i][j][0] = 255 * temp1;
				Imagedata_3_1[i][j][1] = 255 * temp2;
				Imagedata_3_1[i][j][2] = 255 * temp3;
			}
			if (a == Soft_Light)//soft light
			{
				tempa1 = (float)(Imagedata[3 * (Size1 * i + j) + 0]) / 255;
				tempa2 = (float)(Imagedata[3 * (Size1 * i + j) + 1]) / 255;
				tempa3 = (float)(Imagedata[3 * (Size1 * i + j) + 2]) / 255;
				tempb1 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 0]) / 255;
				tempb2 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 1]) / 255;
				tempb3 = (float)(Imagedata1_c[3 * (Size1 * i + j) + 2]) / 255;
				if (tempb1<0.5)
				{
					temp1 = 2 * tempa1*tempb1 + tempa1*tempa1*(1 - 2 * tempb1);
					Imagedata_3_1[i][j][0] = 255 * temp1;
				}
				else
				{
					temp1 = 2 * tempa1*(1 - tempb1) + sqrt(tempa1)*(2 * tempb1 - 1);
					Imagedata_3_1[i][j][0] = 255 * temp1;
				}
				if (tempb2<0.5)
				{
					temp2 = 2 * tempa2*tempb2 + tempa2*tempa2*(1 - 2 * tempb2);
					Imagedata_3_1[i][j][1] = 255 * temp2;
				}
				else
				{
					temp2 = 2 * tempa2*(1 - tempb2) + sqrt(tempa2)*(2 * tempb2 - 1);
					Imagedata_3_1[i][j][1] = 255 * temp2;
				}
				if (tempb3<0.5)
				{
					temp3 = 2 * tempa3*tempb3 + tempa3*tempa3*(1 - 2 * tempb3);
					Imagedata_3_1[i][j][2] = 255 * temp3;
				}
				else
				{
					temp3 = 2 * tempa3*(1 - tempb3) + sqrt(tempa3)*(2 * tempb3 - 1);
					Imagedata_3_1[i][j][2] = 255 * temp3;
				}
			}
			if (a == Darken)//Darken
			{
				Imagedata_3_1[i][j][0] = (Imagedata[3 * (Size1 * i + j) + 0]>Imagedata1_c[3 * (Size1 * i + j) + 0]) ? Imagedata[3 * (Size1 * i + j) + 0] : Imagedata1_c[3 * (Size1 * i + j) + 0];
				Imagedata_3_1[i][j][1] = (Imagedata[3 * (Size1 * i + j) + 1]>Imagedata1_c[3 * (Size1 * i + j) + 1]) ? Imagedata[3 * (Size1 * i + j) + 1] : Imagedata1_c[3 * (Size1 * i + j) + 1];
				Imagedata_3_1[i][j][2] = (Imagedata[3 * (Size1 * i + j) + 2]>Imagedata1_c[3 * (Size1 * i + j) + 2]) ? Imagedata[3 * (Size1 * i + j) + 2] : Imagedata1_c[3 * (Size1 * i + j) + 2];
			}
		}
	}

	for (int i = 0; i < Size2; i++)//save the image
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedata[3 * (Size1 * i + j) + 0] = Imagedata_3_1[i][j][0];
			Imagedata[3 * (Size1 * i + j) + 1] = Imagedata_3_1[i][j][1];
			Imagedata[3 * (Size1 * i + j) + 2] = Imagedata_3_1[i][j][2];
		}
	}

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	system("pause");
}
