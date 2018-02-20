// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//******************************************************************************************************************
//Change only L of image for P2_b_3
//******************************************************************************************************************

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];

extern double maxi(double a, double b, double c);

extern double mini(double a, double b, double c);


void RGB2HSL(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata)
{
	unsigned char ***Imagedata2_2 = new unsigned char**[Size2];
	for (int i = 0;i<Size2;i++)
	{
		Imagedata2_2[i] = new unsigned char*[Size1];
		for (int j = 0;j<Size1;j++)
		{
			Imagedata2_2[i][j] = new unsigned char[BytesPerPixel];
		}
	}

	double temp, l;
	double R, G, B;
	double M, m, C;

	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			R = (double)Imagedata[3 * (Size1 * i + j) + 0] / 255;
			G = (double)Imagedata[3 * (Size1 * i + j) + 1] / 255;
			B = (double)Imagedata[3 * (Size1 * i + j) + 2] / 255;
			M = maxi(R, G, B);
			m = mini(R, G, B);
			C = M - m;
			if (C == 0)//get the H
			{
				Imagedata2_2[i][j][0] = 0;
			}
			else
			{
				if ((M == R) && (G >= B))
				{
					temp = (G - B) / C;
					Imagedata2_2[i][j][0] = 60 * (temp) * ((double)255 / 360);
				}
				else if ((M == R) && (G<B))
				{
					temp = (G - B) / C;
					Imagedata2_2[i][j][0] = (60 * (temp)+360) * ((double)255 / 360);
				}
				else if (M == G)
				{
					temp = (B - R) / C;
					Imagedata2_2[i][j][0] = (60 * (temp)+120) * ((double)255 / 360);
				}
				else if (M == B)
				{
					temp = (R - G) / C;
					Imagedata2_2[i][j][0] = (60 * (temp)+240) * ((double)255 / 360);
				}
			}
			temp = (M + m) / 2;//get the L
			Imagedata2_2[i][j][1] = temp * 255;
			l = (M + m) / 2;//get the S
			if (l == 0)
			{
				Imagedata2_2[i][j][2] = 0;
			}
			else if ((l>0) && (l<0.5))
			{
				temp = C / (M + m);
				Imagedata2_2[i][j][2] = temp * 255;
			}
			else
			{
				temp = C / (2 - M - m);
				Imagedata2_2[i][j][2] = temp * 255;
			}
		}
	}

	for (int i = 0; i<Size2; i++)//save the image
	{
		for (int j = 0; j<Size1; j++)
		{
			Imagedata[3 * (Size1 * i + j) + 0] = Imagedata2_2[i][j][0];
			Imagedata[3 * (Size1 * i + j) + 1] = Imagedata2_2[i][j][1];
			Imagedata[3 * (Size1 * i + j) + 2] = Imagedata2_2[i][j][2];
		}
	}
	delete[] Imagedata2_2;
}

void EQL(int Size1, int Size2, unsigned char *Imagedata)
{
	unsigned char ***Imagedata2_2 = new unsigned char**[Size2];
	for (int i = 0;i<Size2;i++)
	{
		Imagedata2_2[i] = new unsigned char*[Size1];
		for (int j = 0;j<Size1;j++)
		{
			Imagedata2_2[i][j] = new unsigned char[1];
		}
	}

	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedata2_2[i][j][0] = Imagedata[3 * (Size1 * i + j) + 1];
		}
	}

	int a;
	cout << "Use 1) cdf or 2) bucket filling cdf: ";
	cin >> a;

	long his[256] = { 0 };
	double pdf[256], cdf[256];

	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			for (int num = 0; num<256; num++)
			{
				if (Imagedata2_2[i][j][0] == num)
				{
					his[num] = his[num] + 1;//get the histogram
				}
			}
		}
	}

	double temp;
	int Fmin, Fmax;

	for (int num = 0; num<256; num++)//calculate the pdf and cdf
	{
		temp = (double)his[num] / (double)Size2 / (double)Size1;
		pdf[num] = temp;
		if (num == 0)
		{
			cdf[num] = pdf[num];
		}
		else
		{
			cdf[num] = temp + cdf[num - 1];
		}
		if (cdf[num] <= 0.1)
		{
			Fmin = num;
		}
		if (cdf[num] <= 0.9)
		{
			Fmax = num;
		}
	}

	if (a == 1)//cdf
	{
		double temp2;
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				for (int num = 0; num<256; num++)
				{
					if (Imagedata2_2[i][j][0] == num)
					{
						temp2 = cdf[num]; break;
					}
				}
				temp2 = 255 * temp2;
				Imagedata[3 * (Size1 * i + j) + 1] = temp2;
			}
		}
	}
	else if (a == 2)//bucket filling cdf
	{
		long stand;
		stand = (Size1 * Size2) / 256 + 1;
		int i0 = 0;
		int n = 0;
		for (int num = 0; num<256; num++)
		{
			for (int i = 0; i<Size2; i++)
			{
				for (int j = 0; j<Size1; j++)
				{
					if (Imagedata2_2[i][j][0] == num)
					{
						if (i0<stand)
						{
							i0++;
						}
						else
						{
							n++;
							i0 = 1;
						}
						Imagedata[3 * (Size1 * i + j) + 1] = n;
					}
				}
			}
		}
	}
	else
	{
		cout << "Invalid Choice" << endl;
	}
	delete[] Imagedata2_2;
}

void HSL2RGB(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata)
{
	unsigned char ***Imagedata2_2 = new unsigned char**[Size2];
	for (int i = 0;i<Size2;i++)
	{
		Imagedata2_2[i] = new unsigned char*[Size1];
		for (int j = 0;j<Size1;j++)
		{
			Imagedata2_2[i][j] = new unsigned char[BytesPerPixel];
		}
	}
	float H1, S1, L1;
	float p1, q1, hk;
	float t[3];
	float tempe[3];
	for (int i1 = 0; i1<Size2; i1++)
	{
		for (int j1 = 0; j1<Size1; j1++)
		{
			if (Imagedata[3 * (Size1 * i1 + j1) + 2] == 0)
			{
				Imagedata2_2[i1][j1][0] = Imagedata[3 * (Size1 * i1 + j1) + 1];
				Imagedata2_2[i1][j1][1] = Imagedata[3 * (Size1 * i1 + j1) + 1];
				Imagedata2_2[i1][j1][2] = Imagedata[3 * (Size1 * i1 + j1) + 1];
			}
			else
			{
				H1 = (double)Imagedata[3 * (Size1 * i1 + j1) + 0] * ((double)360 / 255);
				L1 = (double)Imagedata[3 * (Size1 * i1 + j1) + 1] / (double)255;
				S1 = (double)Imagedata[3 * (Size1 * i1 + j1) + 2] / (double)255;
				if (L1 < 0.5)
				{
					q1 = L1 * (double)(1 + S1);
				}
				else
				{
					q1 = L1 + S1 - (double)(L1 * S1);
				}
				p1 = 2 * L1 - q1;
				hk = H1 / (double)360;
				t[0] = hk + (double)1 / 3;
				t[1] = hk;
				t[2] = hk - (double)1 / 3;
				for (int s1 = 0; s1<3; s1++)
				{
					//while ((t[s1]<0) || (t[s1]>1))
					//{
						if (t[s1]<0)
						{
							t[s1] = t[s1] + 1;
						}
						if (t[s1]>1)
						{
							t[s1] = t[s1] - 1;
						}
					//}
				}
				for (int s1 = 0; s1<3; s1++)
				{
					if (t[s1]<(double)1 / 6)
					{
						tempe[s1] = p1 + ((q1 - p1) * (double)6 * t[s1]);
					}
					else if ((t[s1] >= (double)1 / 6) && (t[s1]<(double)1 / 2))
					{
						tempe[s1] = q1;
					}
					else if ((t[s1] >= (double)1 / 2) && (t[s1]<(double)2 / 3))
					{
						tempe[s1] = p1 + ((q1 - p1) * 6 * ((double)2 / 3 - t[s1]));
					}
					else
					{
						tempe[s1] = p1;
					}
				}
				Imagedata2_2[i1][j1][0] = 255 * tempe[0];
				Imagedata2_2[i1][j1][1] = 255 * tempe[1];
				Imagedata2_2[i1][j1][2] = 255 * tempe[2];
			}
		}
	}

	for (int i1 = 0; i1<Size2; i1++)
	{
		for (int j1 = 0; j1<Size1; j1++)
		{
			Imagedata[3 * (Size1 * i1 + j1) + 0] = Imagedata2_2[i1][j1][0];
			Imagedata[3 * (Size1 * i1 + j1) + 1] = Imagedata2_2[i1][j1][1];
			Imagedata[3 * (Size1 * i1 + j1) + 2] = Imagedata2_2[i1][j1][2];
		}
	}
}

void P2_b(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2)
{
	FILE *file;
	if (BytesPerPixel != 3)
	{
		cout << "Error Bytes Per Pixel" << endl;
		system("pause");
		return;
	}
	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	//RGB to HSL
	RGB2HSL(BytesPerPixel, Size1, Size2, Imagedata);

	//change L
	EQL(Size1, Size2, Imagedata);

	//HSL to RGB
	HSL2RGB(BytesPerPixel, Size1, Size2, Imagedata);

	

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
