// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Mirror and resizing for P1_a_1 and P1_a_2
//*********************************************************


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedata1_a_1[100000000];
extern unsigned char Imagedata1_a_2[100000000];

void P1_a(int BytesPerPixel = 3, int Size1 = 256, int Size2 = 256, char *a1 = "0", char *a2 = "0", int question = 1)
{
	FILE *file;

	// Allocate image data array

	unsigned char ImagedataPlus[300][300][3];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	int Sizea, Sizeb;
	if (question == 2)
	{
		cout << "Input the width of the picture: ";
		cin >> Sizea;
		Sizeb = (float)Size2 / (float)Size1 * (float)Sizea;
		cout << "The height of the new picture is: " << Sizeb << endl;
	}

	if (question == 1)//Problem 1_a_1
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedata1_a_1[3 * (Size1 * i + j) + 0] = Imagedata[3 * (Size1 * i + Size1 - 1 - j) + 0];//mirror the pixel value in R channel
				Imagedata1_a_1[3 * (Size1 * i + j) + 1] = Imagedata[3 * (Size1 * i + Size1 - 1 - j) + 1];//mirror the pixel value in G channel
				Imagedata1_a_1[3 * (Size1 * i + j) + 2] = Imagedata[3 * (Size1 * i + Size1 - 1 - j) + 2];//mirror the pixel value in B channel
			}
		}
		for (int i = 0; i<Size2; i++)//save the image
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedata[3 * (Size1 * i + j) + 0] = Imagedata1_a_1[3 * (Size1 * i + j) + 0];
				Imagedata[3 * (Size1 * i + j) + 1] = Imagedata1_a_1[3 * (Size1 * i + j) + 1];
				Imagedata[3 * (Size1 * i + j) + 2] = Imagedata1_a_1[3 * (Size1 * i + j) + 2];
			}
		}
	}
	else if (question == 2)//Problem 1_a_2
	{
		float r1;
		r1 = (float)Size1 / Sizea;//the ratio between new and origin image
		float i0, j0;
		float dx, dy;
		int i1, j1;
		int i11, j11;
		float temp;
		//cout<<r1<<endl;
		for (int i = 0; i<Sizeb; i++)//linear implementation
		{
			for (int j = 0; j<Sizea; j++)
			{
				i1 = r1*(float)(i); j1 = r1*(float)(j);//connection between cordinates
				i0 = r1*(float)(i); j0 = r1*(float)(j);
				//cout<<i1<<"  "<<j1<<" "<<i0<<"  "<<j0<<endl;
				dx = (i0 - i1); dy = (j0 - j1);
				i11 = i1 + 1; j11 = j1 + 1;
				temp = (1 - dx)*(1 - dy)*(float)Imagedata[3 * (Size1 * i1 + j1) + 0] + (dx)*(1 - dy)*(float)Imagedata[3 * (Size1 * i11 + j1) + 0] + (1 - dx)*(dy)*(float)Imagedata[3 * (Size1 * i1 + j11) + 0] + (dx)*(dy)*(float)Imagedata[3 * (Size1 * i11 + j11) + 0];
				Imagedata1_a_2[3 * (Sizea * i + j) + 0] = temp;
				temp = (1 - dx)*(1 - dy)*(float)Imagedata[3 * (Size1 * i1 + j1) + 1] + (dx)*(1 - dy)*(float)Imagedata[3 * (Size1 * i11 + j1) + 1] + (1 - dx)*(dy)*(float)Imagedata[3 * (Size1 * i1 + j11) + 1] + (dx)*(dy)*(float)Imagedata[3 * (Size1 * i11 + j11) + 1];
				Imagedata1_a_2[3 * (Sizea * i + j) + 1] = temp;
				temp = (1 - dx)*(1 - dy)*(float)Imagedata[3 * (Size1 * i1 + j1) + 2] + (dx)*(1 - dy)*(float)Imagedata[3 * (Size1 * i11 + j1) + 2] + (1 - dx)*(dy)*(float)Imagedata[3 * (Size1 * i1 + j11) + 2] + (dx)*(dy)*(float)Imagedata[3 * (Size1 * i11 + j11) + 2];
				Imagedata1_a_2[3 * (Sizea * i + j) + 2] = temp;
				//cout<<Imagedata1_2[i][j][0]<<"  "<<Imagedata1_2[i][j][1]<<"  "<<Imagedata1_2[i][j][2]<<endl;
				//cout<<i<<'\t'<<j<<'\t'<<endl;
			}
		}
	}
	

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (question == 2)
	{
		if (!(file = fopen(a2, "wb"))) {
			cout << "Cannot open file: " << a2 << endl;
			exit(1);
		}
		fwrite(Imagedata1_a_2, sizeof(unsigned char), Sizeb*Sizea*BytesPerPixel, file);
		fclose(file);
	}
	else
	{
		if (!(file = fopen(a2, "wb"))) {
			cout << "Cannot open file: " << a2 << endl;
			exit(1);
		}
		fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
		fclose(file);
	}
	system("pause");
}
