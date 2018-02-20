// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//******************************************************************************************************************
//Gaussian image equalization for P2_c
//******************************************************************************************************************


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>

const double PI = 3.1415926;

using namespace std;

extern unsigned char Imagedata[100000000];

void P2_c(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2)
{
	FILE *file;
	unsigned char ***Imagedata1_1 = new unsigned char **[Size2];
	for (int i = 0; i<Size2; i++)
	{
		Imagedata1_1[i] = new unsigned char *[Size1];
		for (int j = 0; j<Size1; j++)
		{
			Imagedata1_1[i][j] = new unsigned char[BytesPerPixel];
		}
	}

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	int a;
	cout << "Use 1) cdf or 2) bucket filling cdf: ";
	cin >> a;


	for (int s = 0; s<BytesPerPixel; s++)
	{
		long his[256] = { 0 };
		double pdf[256], cdf[256];
		double pdf1[256], cdf1[256], cdf10[256];

		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				for (int num = 0; num<256; num++)
				{
					if (Imagedata[BytesPerPixel * (Size1 * i + j) + s] == num)
					{
						his[num] = his[num] + 1;break;
					}
				}
			}
		}

		double temp;
		double tempp;

		for (int num = 0; num<256; num++)
		{
			temp = (double)his[num] / Size2 / Size1;
			pdf[num] = temp;
			if (num == 0)
			{
				cdf[num] = pdf[num];
			}
			else
			{
				cdf[num] = temp + cdf[num - 1];
			}
		}

		for (int num = 0; num<256; num++)
		{
			tempp = (double)(num - 70)*(double)(num - 70) / ((double)(2 * 20 * 20));
			temp = 1 / (sqrt(2 * PI*(double)20 * (double)20))*(double)exp(-tempp); //Gaussian pdf function
			pdf1[num] = temp;
			if (num == 0)
			{
				cdf10[num] = pdf1[num];
			}
			else
			{
				cdf10[num] = temp + cdf10[num - 1];
			}
		}

		temp = cdf10[255];

		for (int num = 0; num<256; num++)
		{
			cdf1[num] = cdf10[num] / temp;// 
		}

		//for(int num = 0; num<256; num++)
		//{
		//	cout<<cdf[num]<<"  ";
		//}

		//cout << endl;

		if (a == 1)//cdf
		{
			double temp1, temp2, temp21, temp22;
			for (int num = 0; num<256; num++)
			{
				if (cdf1[num] >= 0.99)
				{
					temp1 = (double)num / 255; break;
				}
			}
			cout << temp1 << endl;
			for (int i = 0; i<Size2; i++)
			{
				for (int j = 0; j<Size1; j++)
				{
					for (int num = 0; num<256; num++)
					{
						if (Imagedata[BytesPerPixel * (Size1 * i + j) + s] == num)
						{
							temp2 = cdf[num]; break;
						}
					}
					if (temp2 >= 0.99)
					{
						temp2 = temp1;
					}
					else
					{
						for (int num = 0; num<255; num++)
						{
							temp21 = cdf1[num];
							temp22 = cdf1[num + 1];
							if ((temp2 >= temp21) && (temp2<temp22))
							{
								temp2 = (double)num / 255; break;//map the origin pixel to another new pixel
							}
						}
					}
					Imagedata1_1[i][j][s] = temp2 * 255;
				}
			}
		}
		else if (a == 2)//bucket fill cdf
		{
			long stand[256];
			double tt;
			for (int num = 0; num<256; num++)
			{
				tt = (double)Size1 * (double)Size2 * pdf1[num] / cdf10[255];
				stand[num] = tt + 1;//make the number of pixels for each pixel values
			}
			//long stand;
			//stand = (Size1 * Size2)/256 + 1;
			int i0 = 0;
			int n = 0;
			for (int num = 0; num<256; num++)
			{
				for (int i = 0; i<Size2; i++)
				{
					for (int j = 0; j<Size1; j++)
					{
						if (Imagedata[BytesPerPixel * (Size1 * i + j) + s] == num)
						{
							if (i0 < stand[n])//check if we fill each buckets
							{
								i0++;
							}
							else
							{
								n++;
								i0 = 1;
							}
							Imagedata1_1[i][j][s] = n;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			Imagedata[BytesPerPixel * (Size1 * i + j) + 0] = Imagedata1_1[i][j][0];
			Imagedata[BytesPerPixel * (Size1 * i + j) + 1] = Imagedata1_1[i][j][1];
			Imagedata[BytesPerPixel * (Size1 * i + j) + 2] = Imagedata1_1[i][j][2];
		}
	}

	long his1[256] = { 0 };
	for (int s = 0;s < BytesPerPixel;s++)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				for (int num = 0; num<256; num++)
				{
					if (Imagedata[BytesPerPixel * (Size1 * i + j) + s] == num)
					{
						his1[num] = his1[num] + 1;break;
					}
				}
			}
		}
		//for (int num = 0; num < 256; num++)
		//{
		//	cout << his1[num] << endl;//get the histogram
		//}
		//cout << endl;
		//cout << endl;
	}
	

	double sum = 0, mean, Svar = 0, temp;

	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			sum = sum + Imagedata[BytesPerPixel * (Size1 * i + j) + 0];
		}
	}
	mean = (double)sum / (double)Size1 / (double)Size2;//output the mean
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			temp = (Imagedata[BytesPerPixel * (Size1 * i + j) + 0] - mean) * (Imagedata[BytesPerPixel * (Size1 * i + j) + 0] - mean);
			Svar = Svar + temp;//output the variation
		}
	}
	Svar = sqrt(Svar / (double)Size1 / (double)Size2);
	//cout << Svar << '\t' << mean << endl;

	

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
