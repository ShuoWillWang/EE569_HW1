// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu


//******************************************************************************************************************
//Average, Median, Gaussian and Bilateral filter for P3_a
//******************************************************************************************************************



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>
#include <time.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedata1[100000000];
extern unsigned char Imagedataori[100000000];
extern unsigned char Imagedataex[100000000];
extern unsigned char Imagedataex1[100000000];
extern unsigned char Imagedatasin[100000000];
extern unsigned char Imagedatasin1[100000000];
extern unsigned char Imagedatasin2[100000000];
extern unsigned char Imagedatasin3[100000000];

extern double PSNR_m(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataori);

double abso(double a) // get the absolute value
{
	if (a >= 0)
		return a;
	else
		return -a;
}

double Mid(double * a) // get the middle value for 5 values
{
	double temp, tempa;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5 - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				tempa = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tempa ;
			}
		}
	}
	temp = a[2];
	return temp;
}

double Mid_5(double * a)// get the middle value for 9 values
{
	double temp, tempa;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9 - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				tempa = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tempa;
			}
		}
	}
	temp = a[4];
	return temp;
}

double Mid_7(double * a)// get the middle value for 13 values
{
	double temp, tempa;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 13 - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				tempa = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tempa;
			}
		}
	}
	temp = a[6];
	return temp;
}

double PSNR(int s, int Size1, int Size2, unsigned char *Imagedatasin, unsigned char *Imagedataori) // calculate the PSNR for a sequence
{
	s = s - 1;
	double sqavg, temp, psnr;
	sqavg = 0;
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			temp = (Imagedatasin[1 * ((Size1)* i + j) + 0] - Imagedataori[3 * ((Size1)* i + j) + s])*(Imagedatasin[1 * ((Size1)* i + j) + 0] - Imagedataori[3 * ((Size1)* i + j) + s]);
			sqavg = sqavg + temp;
		}
	}
	sqavg = sqavg / ((double)Size1 * (double)Size2);
	psnr = 10 * log10(255 * 255 / sqavg);
	return psnr;
}

void Seq(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedatasin)//get the gray scale picture
{
	unsigned char ***Imagedata3_a_temp = new unsigned char **[Size2];
	for (int i = 0; i<Size2; i++)
	{
		Imagedata3_a_temp[i] = new unsigned char *[Size1];
		for (int j = 0; j<Size1; j++)
		{
			Imagedata3_a_temp[i][j] = new unsigned char[1];
		}
	}
	int a;
	cout << "Input the sequence: ";
	cin >> a;

	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			if (a == 1)
			{
				Imagedata3_a_temp[i][j][0] = Imagedata[3 * (Size1 * i + j) + 0];
			}
			else
			{
				if (a == 2)
				{
					Imagedata3_a_temp[i][j][0] = Imagedata[3 * (Size1 * i + j) + 1];
				}
				else
				{
					Imagedata3_a_temp[i][j][0] = Imagedata[3 * (Size1 * i + j) + 2];
				}
			}
		}
	}
	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata3_a_temp[i][j][0];
		}
	}
}

void Ext(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataex)//extend the edge by 1 for color image
{
	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * i + j) + 0];
			Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * i + j) + 1];
			Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * i + j) + 2];
		}
	}
	for (int j = 0; j < Size1; j++)
	{
		Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[3 * (Size1 * 0 + j) + 0];
		Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 1] = Imagedata[3 * (Size1 * 0 + j) + 1];
		Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 2] = Imagedata[3 * (Size1 * 0 + j) + 2];
		Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 0];
		Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 1];
		Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 2];
	}
	for (int i = 0; i < (Size2 + 2); i++)
	{
		Imagedataex[3 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 0];
		Imagedataex[3 * ((Size1 + 2) * i + 0) + 1] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 1];
		Imagedataex[3 * ((Size1 + 2) * i + 0) + 2] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 2];
		Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 0];
		Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 1] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 1];
		Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 2] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 2];
	}
}

void Ext1(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataex)//extend one edge for the gray image
{
	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[1 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * i + j) + 0];
		}
	}
	for (int j = 0; j < Size1; j++)
	{
		Imagedataex[1 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[1 * (Size1 * 0 + j) + 0];
		Imagedataex[1 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * (Size2 - 1) + j) + 0];
	}
	for (int i = 0; i < (Size2 + 2); i++)
	{
		Imagedataex[1 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[1 * ((Size1 + 2) * i + 1) + 0];
		Imagedataex[1 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = Imagedataex[1 * ((Size1 + 2) * i + Size2) + 0];
	}
}

void Cmp(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedataori)//get the noise histogram
{
	char b[4] = "RGB";
	int ***Imagedata3_a_1 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_1[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_1[i][j] = new int[BytesPerPixel];
		}
	}
	for (int s = 0; s < BytesPerPixel; s++)
	{
		int pepper_sault = 0;
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				float avg;
				avg = 0.125 * (Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j + 2)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s]);
				if (((Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] == 0) || (Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] == 255)) && (abso(avg - (float)Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s])>= 40))
				{
					pepper_sault++;
					Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = Imagedataori[BytesPerPixel * (Size1* i + j) + s];
				}
				Imagedata3_a_1[i][j][s] = (int)Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - (int)Imagedataori[BytesPerPixel * (Size1* i + j) + s];
			}
		}
		cout << "The number of pixels in "<< b[s] <<" sequence with impulse noise is " << pepper_sault << endl;
		cout << endl;
		long his[512] = { 0 };

		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				for (int num = -256; num<256; num++)
				{
					if (Imagedata3_a_1[i][j][s] == num)
					{
						his[num + 256] = his[num + 256] + 1;break;
					}
				}
			}
		}
		cout<<"The histogram of noise in "<< b[s] <<" sequence is ";
		for (int num = -256; num<256; num++)
			cout << his[num + 256] << '\t';
		cout << endl;
		cout << endl;
		double sum = 0, mean, Svar = 0, temp;
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				sum = sum + Imagedata3_a_1[i][j][s];
			}
		}
		mean = (double)sum / (double)Size1 / (double)Size2;
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				temp = (Imagedata[BytesPerPixel * (Size1 * i + j) + 0] - mean) * (Imagedata[BytesPerPixel * (Size1 * i + j) + 0] - mean);
				Svar = Svar + temp;
			}
		}
		Svar = sqrt(Svar / (double)Size1 / (double)Size2);
		cout << "The noise variation in "<< b[s] <<" is" << Svar << '\t' << "The noise mean in " << b[s] << " is" << mean << endl;
	}
}

void His(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex)//get the histogram of images
{
	for (int s = 0;s < 3;s++)
	{
		char b[4] = "RGB";
		int his[256] = { 0 };
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				for (int num = 0; num < 256; num++)
				{
					if (Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] == num)
					{
						his[num] = his[num] + 1;
						break;
					}
				}
			}
		}
		cout << "The histogram of noise in " << b[s] << " sequence is ";
		for (int num = 0; num < 256; num++)
		{
			cout << his[num] << '\t';
		}
		cout << endl;
	}
}

void Avgfil(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin)//avg filter for 3x3
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double avg;
			double a1, a2, a3;
			a1 = 1;
			a2 = 1;
			a3 = 1;
			avg = (double)1 / (double)(4 * a1 + 4 * a2 + a3) * (a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j + 1)) + s] + a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j + 2)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j)) + s] + a3 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] + a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] + a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s]);
			Imagedata3_a_2[i][j][0] = avg;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Avgfil_5(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin)//avg filter for 5x5
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double avg;
			avg = 0.0;
			double a1, a2, a3;
			double index[25];
			for (int s1 = -2; s1 <= 2;s1++)
			{
				for (int s2 = -2; s2 <= 2;s2++)
				{
					index[5 * (s1 + 2) + s2 + 2] = Imagedataex[BytesPerPixel * ((Size1 + 4) * (i + 2 + s1)+(j + 2 + s2)) + s];
					//cout << index[5 * (s1 + 2) + s2 + 2] << "  ";
				}
				//cout << endl;
			}
			for (int s3 = 0; s3 < 25; s3++)
			{
				avg = avg + index[s3];
			}
			avg = avg / 25;
			
			Imagedata3_a_2[i][j][0] = avg;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Avgfil_7(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin)//avg filter for 7x7
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double avg;
			avg = 0.0;
			double a1, a2, a3;
			double index[49];
			for (int s1 = -3; s1 <= 3;s1++)
			{
				for (int s2 = -3; s2 <= 3;s2++)
				{
					index[7 * (s1 + 3) + s2 + 3] = Imagedataex[BytesPerPixel * ((Size1 + 6) * (i + 3 + s1) + (j + 3 + s2)) + s];
				}
			}
			for (int s3 = 0; s3 < 49; s3++)
			{
				avg = avg + index[s3];
			}
			avg = avg / 49;
			Imagedata3_a_2[i][j][0] = avg;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Gausfil(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin)//Gau filter for 3x3
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double avg;
			double a1, a2, a3;
			double Sig = 1.50;
			a1 = exp(-2 / (2 * Sig * Sig));//gaussian kernel
			a2 = exp(-1 / (2 * Sig * Sig));
			a3 = 1;
			avg = (double)1 / (double)(4 * a1 + 4 * a2 + a3) * (a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j + 1)) + s] + a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j + 2)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j)) + s] + a3 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] + a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j)) + s] + a2 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] + a1 * Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s]);
			Imagedata3_a_2[i][j][0] = avg;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Gausfil_5(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin)//Gau filter for 5x5
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double avg, sum;
			avg = 0.0;
			sum = 0.0;
			double a1, a2, a3;
			double Sig = 1.50;
			double index[25] = { 0 }, weight[25] = { 0 };
			for (int s1 = -2; s1 <= 2;s1++)//gaussian kernel
			{
				for (int s2 = -2; s2 <= 2;s2++)
				{
					weight[5 * (s1 + 2) + s2 + 2] = exp(-(double)(s1 * s1 + s2 * s2)/(2 * Sig * Sig));
					sum = sum + exp(-(double)(s1 * s1 + s2 * s2) / (2 * Sig * Sig));
				}
			}
			for (int s3 = 0; s3 < 25; s3++)
			{
				weight[s3] = weight[s3] / sum;
			}
			for (int s1 = -2; s1 <= 2;s1++)
			{
				for (int s2 = -2; s2 <= 2;s2++)
				{
					index[5 * (s1 + 2) + s2 + 2] = Imagedataex[BytesPerPixel * ((Size1 + 4) * (i + 2 - s1) + (j + 2 - s2)) + s];
				}
			}
			for (int s3 = 0; s3 < 25; s3++)
			{
				avg = avg + index[s3] * weight[s3];
			}
			Imagedata3_a_2[i][j][0] = avg;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Gausfil_7(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin)//Gau filter for 7x7
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double avg, sum;
			avg = 0.0;
			sum = 0.0;
			double a1, a2, a3;
			double Sig = 1.50;
			double index[49] = { 0 }, weight[49] = { 0 };
			for (int s1 = -3; s1 <= 3;s1++)
			{
				for (int s2 = -3; s2 <= 3;s2++)
				{
					weight[7 * (s1 + 3) + s2 + 3] = exp(-(double)(s1 * s1 + s2 * s2) / (2 * Sig * Sig));//Gaussian kernels
					sum = sum + exp(-(double)(s1 * s1 + s2 * s2) / (2 * Sig * Sig));
				}
			}
			for (int s3 = 0; s3 < 49; s3++)
			{
				weight[s3] = weight[s3] / sum;//Gaussian kernels
			}
			for (int s1 = -3; s1 <= 3;s1++)
			{
				for (int s2 = -3; s2 <= 3;s2++)
				{
					index[7 * (s1 + 3) + s2 + 3] = Imagedataex[BytesPerPixel * ((Size1 + 6) * (i + 3 + s1) + (j + 3 + s2)) + s];
				}
			}
			for (int s3 = 0; s3 < 49; s3++)
			{
				avg = avg + index[s3] * weight[s3];
			}
			Imagedata3_a_2[i][j][0] = avg;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Midfil(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex1, unsigned char *Imagedatasin1)//mid filter for 3x3 +
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double mid;
			double a[5];
			a[0] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 2) * (i)+(j + 1)) + s];
			a[1] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 2) * (i + 1)+(j)) + s];
			a[2] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 2) * (i + 1)+(j + 1)) + s];
			a[3] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 2) * (i + 1)+(j + 2)) + s];
			a[4] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 2) * (i + 2)+(j + 1)) + s];
			mid = Mid(a);//get the middle value for the 5 numbers
			Imagedata3_a_2[i][j][0] = mid;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin1[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Midfil_5(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex1, unsigned char *Imagedatasin1) //mid filter for 5x5 +
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double mid;
			double a[9];
			a[0] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i)+(j + 2)) + s];
			a[1] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 1) + (j + 2)) + s];
			a[2] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j)) + s];
			a[3] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s];
			a[4] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s];
			a[5] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s];
			a[6] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s];
			a[7] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
			a[8] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
			mid = Mid_5(a);// get the middle value for 9 numbers
			Imagedata3_a_2[i][j][0] = mid;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin1[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Midfil_7(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex1, unsigned char *Imagedatasin1) //mid filter for 7x7 +
{
	s = s - 1;
	int ***Imagedata3_a_2 = new int **[Size2];
	for (int i = 0; i<(Size2); i++)
	{
		Imagedata3_a_2[i] = new int *[Size1];
		for (int j = 0; j<(Size1); j++)
		{
			Imagedata3_a_2[i][j] = new int[1];
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double mid;
			double a[13];
			a[0] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i) + (j + 3)) + s];
			a[1] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 1) + (j + 3)) + s];
			a[2] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 2) + (j + 3)) + s];
			a[3] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 3) + (j)) + s];
			a[4] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 3) + (j + 1)) + s];
			a[5] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 3) + (j + 2)) + s];
			a[6] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 3) + (j + 3)) + s];
			a[7] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 3) + (j + 4)) + s];
			a[8] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 3) + (j + 5)) + s];
			a[9] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 3) + (j + 6)) + s];
			a[10] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 4) + (j + 3)) + s];
			a[11] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 5) + (j + 3)) + s];
			a[12] = (double)Imagedataex1[BytesPerPixel * ((Size1 + 6) * (i + 6) + (j + 3)) + s];
			mid = Mid_7(a);// get the middle value for 13 numbers
			Imagedata3_a_2[i][j][0] = mid;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatasin1[1 * (Size1 * i + j) + 0] = Imagedata3_a_2[i][j][0];
		}
	}
}

void Bilateral_fil(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin)//bilateral filter
{
	s = s - 1;
	int k;
	
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double Imagedata3_a_3temp[576][3] = { 0 };
			double sum1 = 0, sum2 = 0, temp = 0;
			double Sig1 = 20.0, Sig2 = 13.0;
			k = 0;
			for (int i0 = i - 36; i0 < i + 36; i0 = i0 + 3)
			{
				for (int j0 = j - 36; j0 < j + 36; j0 = j0 + 3)//searching window
				{
					int abs;
					abs = abso((double)Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - (double)Imagedataex[BytesPerPixel * ((Size1 + 2) * (i0 + 1) + (j0 + 1)) + s]);
					if (i0 > 0 && j0 > 0 && i0 <= Size2 && j0 <= Size1 && abs <= 80 && k < 576)
					{
						Imagedata3_a_3temp[k][0] = Imagedataex[BytesPerPixel * ((Size1 + 2) * (i0 + 1) + (j0 + 1)) + s];
						Imagedata3_a_3temp[k][1] = i0 + 1;
						Imagedata3_a_3temp[k][2] = j0 + 1;
						k++;
					}
				}
			}
			for (int k0 = 0; k0 < k;k0++)//calculate the pixel
			{
				temp = exp(-(double)1 / (1 * Sig1 * Sig1) * ((i + 1 - Imagedata3_a_3temp[k0][1]) * (i + 1 - Imagedata3_a_3temp[k0][1]) + (j + 1 - Imagedata3_a_3temp[k0][2]) * (j + 1 - Imagedata3_a_3temp[k0][2])) - (float)1 / (1 * Sig2 * Sig2) * (((float)Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - Imagedata3_a_3temp[k0][0]) * ((double)Imagedataex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - Imagedata3_a_3temp[k0][0])));
				sum1 = sum1 + Imagedata3_a_3temp[k0][0] * temp;
				sum2 = sum2 + temp;
			}
			Imagedatasin[1 * ((Size1) * (i) + (j)) + 0] = (double)sum1 / (double)sum2;
			//cout << Imagedataex[BytesPerPixel * ((Size1 + 2) * (4 + 1) + (4 + 1)) + s] << endl;
		}
	}
	//cout << abso((float)Imagedataex[BytesPerPixel * ((Size1 + 2) * (2 + 1) + (3 + 1)) + s] - (float)Imagedataex[BytesPerPixel * ((Size1 + 2) * (4 + 1) + (5 + 1)) + s]) << endl;
}

void P3_a(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3)
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
	fread(Imagedataori, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	int choose;
	cout << "the list of options: " << endl;
	cout << "1) show the gray picture for a specific channels: " << endl;
	cout << "2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values: " << endl;
	cout << "3) avg filter: " << endl;
	cout << "4) Gaussian filter: " << endl;
	cout << "5) Median filter: " << endl;
	cout << "6) Median + Median filters: " << endl;
	cout << "7) Median + Gaussian filters: " << endl;
	cout << "8) Gaussian + Gaussian filters: " << endl;
	cout << "9) Median + Gaussian + Gaussian filters: " << endl;
	cout << "10) Gaussian + Median + Median: " << endl;
	cout << "11) Median + Bilateral filter: " << endl;
	cout << "Choose the issue you want to solve: ";
	cin >> choose;

	char seq[4] = "RGB";

	for (int s = 0; s < BytesPerPixel; s++)
	{
		cout << "the PSNR of "<< seq[s] << " for noisy image is: " << PSNR_m(s, BytesPerPixel, Size1, Size2, Imagedata, Imagedataori) << endl;//output the PSNR of origin image
	}
	if (choose == 1)//show the gray pic for diff channels
	{
		Seq(BytesPerPixel, Size1, Size2, Imagedata, Imagedatasin);
	}
	if (choose == 2)//justify if it has pepper and sault and show the histogram of the noise [-255 255)
	{
		int a;
		cout << "choose the kind of comparision. 1) hist of Gaussian noise and classification of impulse noise; 2) hist of the pixel in a original and noise image; ";
		cin >> a;
		if (a == 1)//hist of Gaussian noise and classification of impulse noise
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Cmp(BytesPerPixel, Size1, Size2, Imagedataex, Imagedataori);
		}
		else if (a == 2)//hist of original and noise image
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			His(BytesPerPixel, Size1, Size2, Imagedataex);
			system("pause");
			Ext(BytesPerPixel, Size1, Size2, Imagedataori, Imagedataex);
			His(BytesPerPixel, Size1, Size2, Imagedataex);
		}
	}
	if (choose == 3)//avg filter
	{
		int Na;
		cout << "input the size of the wimdow, 3 or 5 or 7: ";
		cin >> Na;
		if (Na == 3)// 3x3
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Avgfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Avgfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << "  for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Avgfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << "  for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		else if (Na == 5)// 5x5
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Avgfil_5(1, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << "  for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Avgfil_5(2, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << "  for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Avgfil_5(3, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << "  for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		else if (Na == 7)// 7x7
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Avgfil_7(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << "  for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Avgfil_7(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << "  for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Avgfil_7(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1) * i + j) + 0] = Imagedatasin1[1 * ((Size1) * i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1) * i + j) + 1] = Imagedatasin2[1 * ((Size1) * i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1) * i + j) + 2] = Imagedatasin3[1 * ((Size1) * i + j) + 0];

	}
	if (choose == 4)//Gaussian
	{
		int Na;
		cout << "input the size of the wimdow, 3 or 5 or 7: ";
		cin >> Na;
		if (Na == 3)//3x3
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Gausfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << " for filtered image is: " <<  PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Gausfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Gausfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		else if (Na == 5)//5x5
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Gausfil_5(1, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Gausfil_5(2, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Gausfil_5(3, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		else if (Na == 7)//7x7
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Gausfil_7(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << " for filtered image is: " <<  PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Gausfil_7(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Gausfil_7(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	}
	if (choose == 5)//Middle
	{
		int Na;
		cout << "input the size of the wimdow , 3 or 5 or 7: ";
		cin >> Na;
		if (Na == 3)//5 points
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Midfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Midfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Midfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		else if (Na == 5)// 9 points
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Midfil_5(1, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Midfil_5(2, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Midfil_5(3, BytesPerPixel, Size1, Size2, Imagedata1, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		else if (Na == 7)// 13 points
		{
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Midfil_7(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);
			cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Midfil_7(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
			cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
			Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
			Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata1);
			Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata1, Imagedataex);
			Midfil_7(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);
			cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		}
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	}
	if (choose == 6)//Middle + Middle
	{
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	}
	if (choose == 8)//Gaussian + Gaussian
	{
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Gausfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Gausfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Gausfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	}
	if (choose == 7)//Middle + Gaussian
	{
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		cout << "the PSNR of " << seq[0] << " for filtered image is: " <<  PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	}
	if (choose == 9)//Middle + Gaussian + Gaussian 
	{
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Gausfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	}
	if (choose == 10)//Gaussian + Middle + Middle 
	{
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Gausfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Gausfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Gausfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	}

	if (choose == 11)//Middle + Bilateral filter
	{
		clock_t start, finish;
		double duration;
		start = clock();
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		Ext1(1, Size1, Size2, Imagedatasin1, Imagedataex);
		Bilateral_fil(1, 1, Size1, Size2, Imagedataex, Imagedatasin1);
		cout << "the PSNR of " << seq[0] << " for filtered image is: " << PSNR(1, Size1, Size2, Imagedatasin1, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
		Ext1(1, Size1, Size2, Imagedatasin2, Imagedataex);
		Bilateral_fil(1, 1, Size1, Size2, Imagedataex, Imagedatasin2);
		cout << "the PSNR of " << seq[1] << " for filtered image is: " << PSNR(2, Size1, Size2, Imagedatasin2, Imagedataori) << endl;
		Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
		Midfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);//from color to specific gray sequence
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Midfil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		Ext1(1, Size1, Size2, Imagedatasin3, Imagedataex);
		Bilateral_fil(1, 1, Size1, Size2, Imagedataex, Imagedatasin3);
		cout << "the PSNR of " << seq[2] << " for filtered image is: " << PSNR(3, Size1, Size2, Imagedatasin3, Imagedataori) << endl;
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
		for (int i = 0; i < Size2; i++)
			for (int j = 0; j < Size1; j++)
				Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "The running time is " << duration << endl;
	}
	if (choose == 1)
	{
		if (!(file = fopen(a2, "wb"))) {
			cout << "Cannot open file: " << a2 << endl;
			exit(1);
		}
		fwrite(Imagedatasin, sizeof(unsigned char), Size2 * Size1 * 1, file);
		fclose(file);
		system("pause");
	}
	else
	{
		if (!(file = fopen(a2, "wb"))) {
			cout << "Cannot open file: " << a2 << endl;
			exit(1);
		}
		fwrite(Imagedata, sizeof(unsigned char), Size2 * Size1 * 3, file);
		fclose(file);
		system("pause");
	}
	
}
