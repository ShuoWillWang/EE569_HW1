// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Merging for P1_a_3
//*********************************************************



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedata1_a_1[100000000];
extern unsigned char Imagedata1_a_2[100000000];
extern unsigned char ImagedataPlus[100000000];

void P1_a_3(int BytesPerPixel = 3, int Size1 = 256, int Size2 = 256, int Size3 = 300, int Size4 = 300, char *a1 = "0", char *a2 = "0", char *a3 = "0")
{
	FILE *file;
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(a3, "rb"))) {
		cout << "Cannot open file: " << a3 << endl;
		exit(1);
	}
	fread(ImagedataPlus, sizeof(unsigned char), Size3*Size4*BytesPerPixel, file);
	fclose(file);
	int x1, x2, x3;
	cout << "input the R of delete color:";
	cin >> x1;
	cout << "input the G of delete color:";
	cin >> x2;
	cout << "input the complement of B of delete color:";
	cin >> x3;
	int i1, j1;
	int m1, n1;
	cout << "input the location to put the dog." << endl;//the location is the point in the top left corner of the dog image
	cout << "the first cordinates is: ";
	cin >> m1;
	cout << "the second cordinates is: ";
	cin >> n1;
	if (m1 >= 0 && m1 < Size1 - Size3 && n1 >= 0 && n1 < Size2 - Size4)
	{

	}
	else
	{
		cout << "invalid location!!!" << endl;
		return;
	}
	unsigned char ***Imagedata1_3 = new unsigned char **[Size2];
	for (int i = 0; i<Size2; i++)
	{
		Imagedata1_3[i] = new unsigned char *[Size1];
		for (int j = 0; j<Size1; j++)
		{
			Imagedata1_3[i][j] = new unsigned char[BytesPerPixel];
		}
	}
	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			Imagedata1_3[i][j][0] = Imagedata[3 * (Size1 * i + j) + 0];//save the background image
			Imagedata1_3[i][j][1] = Imagedata[3 * (Size1 * i + j) + 1];
			Imagedata1_3[i][j][2] = Imagedata[3 * (Size1 * i + j) + 2];
		}
	}
	for (int j = 0; j<Size3; j++)
	{
		for (int i = 0; i<Size3; i++)
		{
			if ((ImagedataPlus[BytesPerPixel * (Size3 * i + j) + 0] <= x1) && (ImagedataPlus[BytesPerPixel * (Size3 * i + j) + 1] <= x2) && (ImagedataPlus[BytesPerPixel * (Size3 * i + j) + 2] >= 255 - x3))
			{
				//filter the image pixel which is the background of the dog image
			}
			else
			{
				j1 = j + m1;
				i1 = i + n1;
				Imagedata1_3[i1][j1][0] = ImagedataPlus[BytesPerPixel * (Size3 * i + j) + 0];//add the dog into the image
				Imagedata1_3[i1][j1][1] = ImagedataPlus[BytesPerPixel * (Size3 * i + j) + 1];
				Imagedata1_3[i1][j1][2] = ImagedataPlus[BytesPerPixel * (Size3 * i + j) + 2];
			}
		}
	}
	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			Imagedata[3 * (Size1 * i + j) + 0] = Imagedata1_3[i][j][0];//save the image into the global array
			Imagedata[3 * (Size1 * i + j) + 1] = Imagedata1_3[i][j][1];
			Imagedata[3 * (Size1 * i + j) + 2] = Imagedata1_3[i][j][2];
		}
	}
	delete[] Imagedata1_3;
	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	system("pause");
}
