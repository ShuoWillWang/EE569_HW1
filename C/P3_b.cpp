// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//******************************************************************************************************************
//Non-Local Mean filter for P3_b
//******************************************************************************************************************


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
//#include <cmath>
#include <time.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedata1[100000000];
extern unsigned char Imagedataori[100000000];
extern unsigned char Imagedataex[100000000];
extern unsigned char Imagedatasin[100000000];
extern unsigned char Imagedatasin1[100000000];
extern unsigned char Imagedatasin2[100000000];
extern unsigned char Imagedatasin3[100000000];

const double PI = 3.1415926;

extern void Seq(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedatasin);
extern double abso(double a);
extern void Ext(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataex);
extern void Midfil(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedatasin);
double PSNR_m(int s, int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataori)
{
	double sqavg, temp, psnr;
	sqavg = 0;
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			temp = ((double)Imagedata[BytesPerPixel * ((Size1)* i + j) + s] - (double)Imagedataori[BytesPerPixel * ((Size1)* i + j) + s])*((double)Imagedata[BytesPerPixel * ((Size1)* i + j) + s] - (double)Imagedataori[BytesPerPixel * ((Size1)* i + j) + s]);
			sqavg = sqavg + temp;
		}
	}
	sqavg = sqavg / ((double)Size1 * (double)Size2);
	psnr = 10 * log10((double)255 * (double)255 / sqavg);
	return psnr;
}

void NLMean_fil(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedataex, unsigned char *Imagedata, unsigned char *Imagedataori)
{
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
				Imagedata[BytesPerPixel * ((Size1)* i + j) + 0] = Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 17)) + 0];
				Imagedata[BytesPerPixel * ((Size1)* i + j) + 1] = Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 17)) + 1];
				Imagedata[BytesPerPixel * ((Size1)* i + j) + 2] = Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 17)) + 2];
		}
	}
	//Sig1 = sqrt(Sig1);
	char seq[4] = "RGB";

	int Na;
	cout << "input the size of searching window (any positive odd int): ";
	cin >> Na;
	Na = (double)(Na - 1) / 2;
	char Shape;
	cout << "input the shape of calculation window (input 3 5 or 7): ";
	cin >> Shape;
	double Sig;
	cout << "input the Sigma Value of Gaussian kernel (a) (any positive number): ";
	cin >> Sig;
	for (int s = 0; s < BytesPerPixel; s++)
	{
		double Sig1;
		cout << "input the h Value of Filter (any positive number): ";
		cin >> Sig1;
		clock_t start, finish;
		double duration;
		start = clock();
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				if (Shape == '5')// vector is 5x5
				{
					double base[25] = { 0 };
					double Imagedata3_a_3temp[25] = { 0 };
					double sum1 = 0, sum2 = 0, temp = 0;
					double a1, a2, a3, a4, a5, a6;
					double a10, a20, a30, a40, a50, a60;
					a10 = 1 / (2 * PI * Sig * Sig);//Gaussian kernel
					a20 = 1 / (2 * PI * Sig * Sig) * exp(-(double)1 / (2 * Sig * Sig));
					a30 = 1 / (2 * PI * Sig * Sig) * exp(-(double)2 / (2 * Sig * Sig));
					a40 = 1 / (2 * PI * Sig * Sig) * exp(-(double)4 / (2 * Sig * Sig));
					a50 = 1 / (2 * PI * Sig * Sig) * exp(-(double)5 / (2 * Sig * Sig));
					a60 = 1 / (2 * PI * Sig * Sig) * exp(-(double)8 / (2 * Sig * Sig));
					double a00;
					a00 = a10 + 4 * a20 + 4 * a30 + 4 * a40 + 8 * a50 + 4 * a60;
					a1 = sqrt(a10 / a00);//
					a2 = sqrt(a20 / a00);//
					a3 = sqrt(a30 / a00);//
					a4 = sqrt(a40 / a00);//
					a5 = sqrt(a50 / a00);//
					a6 = sqrt(a60 / a00);//
					base[0] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 15)) + s];//the pixel in the central location vector of a searching window
					base[1] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 16)) + s];
					base[2] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 17)) + s];
					base[3] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 18)) + s];
					base[4] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 19)) + s];
					base[5] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 15)) + s];
					base[6] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 16)) + s];
					base[7] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 17)) + s];
					base[8] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 18)) + s];
					base[9] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 19)) + s];
					base[10] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 15)) + s];
					base[11] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 16)) + s];
					base[12] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 17)) + s];
					base[13] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 18)) + s];
					base[14] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 19)) + s];
					base[15] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 15)) + s];
					base[16] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 16)) + s];
					base[17] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 17)) + s];
					base[18] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 18)) + s];
					base[19] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 19)) + s];
					base[20] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 15)) + s];
					base[21] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 16)) + s];
					base[22] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 17)) + s];
					base[23] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 18)) + s];
					base[24] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 19)) + s];
					for (int i0 = i - Na + 2; i0 <= i + Na - 2; i0 = i0 + 1)//scan in the searching window
					{
						for (int j0 = j - Na + 2; j0 <= j + Na - 2; j0 = j0 + 1)
						{
							double avg;
							avg = Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17 - 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17)) + s]\
								+ Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17 + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17 - 1)) + s]\
								+ Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17 + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17 - 1)) + s]\
								+ Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17 + 1)) + s];
							avg = avg / 8;//do the average of the neighbour
							if (abso(i0 - i) <= 2 && abso(j0 - j) <= 2)//if the center point is in the central point vector or not, if so, skip it
							{

							}
							else
							{
								if ((Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] == 255 || Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] == 0) && (abso(avg - Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s]) > 40))
								//whether it is impulse noise or not, if there is impulse noise, skip it
								{

								}
								else
								{
									Imagedata3_a_3temp[0] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 15)) + s];
									Imagedata3_a_3temp[1] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 16)) + s];
									Imagedata3_a_3temp[2] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 17)) + s];
									Imagedata3_a_3temp[3] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 18)) + s];
									Imagedata3_a_3temp[4] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 19)) + s];
									Imagedata3_a_3temp[5] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 15)) + s];
									Imagedata3_a_3temp[6] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 16)) + s];
									Imagedata3_a_3temp[7] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 17)) + s];
									Imagedata3_a_3temp[8] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 18)) + s];
									Imagedata3_a_3temp[9] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 19)) + s];
									Imagedata3_a_3temp[10] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 15)) + s];
									Imagedata3_a_3temp[11] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 16)) + s];
									Imagedata3_a_3temp[12] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s];
									Imagedata3_a_3temp[13] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 18)) + s];
									Imagedata3_a_3temp[14] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 19)) + s];
									Imagedata3_a_3temp[15] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 15)) + s];
									Imagedata3_a_3temp[16] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 16)) + s];
									Imagedata3_a_3temp[17] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 17)) + s];
									Imagedata3_a_3temp[18] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 18)) + s];
									Imagedata3_a_3temp[19] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 19)) + s];
									Imagedata3_a_3temp[20] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 15)) + s];
									Imagedata3_a_3temp[21] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 16)) + s];
									Imagedata3_a_3temp[22] = a4 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 17)) + s];
									Imagedata3_a_3temp[23] = a5 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 18)) + s];
									Imagedata3_a_3temp[24] = a6 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 19)) + s];
									double tempa = 0.0, suma = 0.0;
									for (int q = 0; q < 25;q = q++)
									{
										tempa = (Imagedata3_a_3temp[q] - base[q])*(Imagedata3_a_3temp[q] - base[q]);
										suma = suma + tempa;
									}
									temp = exp(-(double)suma / (double)(2 * Sig1 * Sig1));//get the weight number
									sum1 = sum1 + (double)Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] * temp;
									sum2 = sum2 + temp;
								}
							}
						}
					}
					Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = (double)sum1 / (double)sum2;//get the pixel
				}
				else if (Shape == '7')
				{
					double base[49] = { 0 };
					double sum1, sum2, temp;
					sum1 = 0.0;
					sum2 = 0.0;
					temp = 0.0;
					double a1, a2, a3;
					double weight[49] = {0};
					double tempp;
					tempp = 0.0;
					for (int i1 = -3; i1 <= 3; i1++)
					{
						for (int j1 = -3; j1 <= 3; j1++)
						{
							weight[7 * (i1 + 3) + j1 + 3] = (double)1 / (double)(2 * PI * Sig * Sig)*exp(-(double)(i1 * i1 + j1 * j1) / (2 * Sig * Sig));
							tempp = tempp + weight[7 * (i1 + 3) + j1 + 3];
						}
					}
					
					for (int i2 = 0;i2 < 49;i2++)
					{
						weight[i2] = weight[i2] / tempp;
					}
					a1 = 1;//sqrt(exp(-(double)2 / (2 * Sig * Sig)) / sqrt(2 * PI));
					a2 = 1;//sqrt(exp(-(double)1 / (2 * Sig * Sig)) / sqrt(2 * PI));//exp(-(double)1 / (2 * Sig * Sig));//;
					a3 = 1;
					base[0] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 14) + (j + 14)) + s];
					base[1] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 14) + (j + 15)) + s];
					base[2] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 14) + (j + 16)) + s];
					base[3] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 14) + (j + 17)) + s];
					base[4] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 14) + (j + 18)) + s];
					base[5] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 14) + (j + 19)) + s];
					base[6] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 14) + (j + 20)) + s];
					base[7] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 14)) + s];
					base[8] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 15)) + s];
					base[9] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 16)) + s];
					base[10] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 17)) + s];
					base[11] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 18)) + s];
					base[12] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 19)) + s];
					base[13] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 15) + (j + 20)) + s];
					base[14] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 14)) + s];
					base[15] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 15)) + s];
					base[16] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 16)) + s];
					base[17] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 17)) + s];
					base[18] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 18)) + s];
					base[19] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 19)) + s];
					base[20] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 20)) + s];
					base[21] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 14)) + s];
					base[22] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 15)) + s];
					base[23] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 16)) + s];
					base[24] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 17)) + s];
					base[25] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 18)) + s];
					base[26] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 19)) + s];
					base[27] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 20)) + s];
					base[28] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 14)) + s];
					base[29] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 15)) + s];
					base[30] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 16)) + s];
					base[31] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 17)) + s];
					base[32] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 18)) + s];
					base[33] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 19)) + s];
					base[34] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 20)) + s];
					base[35] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 14)) + s];
					base[36] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 15)) + s];
					base[37] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 16)) + s];
					base[38] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 17)) + s];
					base[39] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 18)) + s];
					base[40] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 19)) + s];
					base[41] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 19) + (j + 20)) + s];
					base[42] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 20) + (j + 14)) + s];
					base[43] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 20) + (j + 15)) + s];
					base[44] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 20) + (j + 16)) + s];
					base[45] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 20) + (j + 17)) + s];
					base[46] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 20) + (j + 18)) + s];
					base[47] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 20) + (j + 19)) + s];
					base[48] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 20) + (j + 20)) + s];

					for (int i0 = i - Na + 3; i0 <= i + Na - 3; i0 = i0 + 1)
					{
						for (int j0 = j - Na + 3; j0 <= j + Na - 3; j0 = j0 + 1)
						{
							double avg;
							avg = Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17 - 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17)) + s]\
								 + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17 + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17 - 1)) + s]\
								 + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17 + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17 - 1)) + s]\
								 + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17 + 1)) + s];
							avg = avg / 8;
							if (abso(i0 - i) <= 3 && abso(j0 - j) <= 3)
							{

							}
							else
							{
								if ((Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] == 255 || Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] == 0) && (abso(avg - Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s]) > 40))//
								{

								}
								else
								{
									double Imagedata3_a_3temp[49] = { 0 };
									double tempa, suma;
									tempa = 0.0;
									suma = 0.0;
									Imagedata3_a_3temp[0] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 14) + (j0 + 14)) + s];
									Imagedata3_a_3temp[1] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 14) + (j0 + 15)) + s];
									Imagedata3_a_3temp[2] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 14) + (j0 + 16)) + s];
									Imagedata3_a_3temp[3] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 14) + (j0 + 17)) + s];
									Imagedata3_a_3temp[4] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 14) + (j0 + 18)) + s];
									Imagedata3_a_3temp[5] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 14) + (j0 + 19)) + s];
									Imagedata3_a_3temp[6] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 14) + (j0 + 20)) + s];
									Imagedata3_a_3temp[7] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 14)) + s];
									Imagedata3_a_3temp[8] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 15)) + s];
									Imagedata3_a_3temp[9] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 16)) + s];
									Imagedata3_a_3temp[10] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 17)) + s];
									Imagedata3_a_3temp[11] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 18)) + s];
									Imagedata3_a_3temp[12] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 19)) + s];
									Imagedata3_a_3temp[13] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 15) + (j0 + 20)) + s];
									Imagedata3_a_3temp[14] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 14)) + s];
									Imagedata3_a_3temp[15] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 15)) + s];
									Imagedata3_a_3temp[16] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 16)) + s];
									Imagedata3_a_3temp[17] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 17)) + s];
									Imagedata3_a_3temp[18] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 18)) + s];
									Imagedata3_a_3temp[19] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 19)) + s];
									Imagedata3_a_3temp[20] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 20)) + s];
									Imagedata3_a_3temp[21] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 14)) + s];
									Imagedata3_a_3temp[22] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 15)) + s];
									Imagedata3_a_3temp[23] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 16)) + s];
									Imagedata3_a_3temp[24] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s];
									Imagedata3_a_3temp[25] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 18)) + s];
									Imagedata3_a_3temp[26] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 19)) + s];
									Imagedata3_a_3temp[27] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 20)) + s];
									Imagedata3_a_3temp[28] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 14)) + s];
									Imagedata3_a_3temp[29] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 15)) + s];
									Imagedata3_a_3temp[30] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 16)) + s];
									Imagedata3_a_3temp[31] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 17)) + s];
									Imagedata3_a_3temp[32] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 18)) + s];
									Imagedata3_a_3temp[33] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 19)) + s];
									Imagedata3_a_3temp[34] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 20)) + s];
									Imagedata3_a_3temp[35] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 14)) + s];
									Imagedata3_a_3temp[36] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 15)) + s];
									Imagedata3_a_3temp[37] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 16)) + s];
									Imagedata3_a_3temp[38] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 17)) + s];
									Imagedata3_a_3temp[39] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 18)) + s];
									Imagedata3_a_3temp[40] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 19)) + s];
									Imagedata3_a_3temp[41] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 19) + (j0 + 20)) + s];
									Imagedata3_a_3temp[42] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 20) + (j0 + 14)) + s];
									Imagedata3_a_3temp[43] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 20) + (j0 + 15)) + s];
									Imagedata3_a_3temp[44] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 20) + (j0 + 16)) + s];
									Imagedata3_a_3temp[45] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 20) + (j0 + 17)) + s];
									Imagedata3_a_3temp[46] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 20) + (j0 + 18)) + s];
									Imagedata3_a_3temp[47] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 20) + (j0 + 19)) + s];
									Imagedata3_a_3temp[48] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 20) + (j0 + 20)) + s];
									//k++;
									for (int q = 0; q < 49;q = q++)
									{
										tempa = (Imagedata3_a_3temp[q] - base[q]) * (Imagedata3_a_3temp[q] - base[q]) * weight[q];/// 49;
										suma = suma + tempa;
									}
									//cout << suma << endl;
									temp = exp(-(double)suma / (double)(2 * Sig1 * Sig1));
									sum1 = sum1 + (double)Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] * temp;
									sum2 = sum2 + temp;
								}
							}
						}
					}
					Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = (unsigned char)((double)sum1 / (double)sum2);
					//cout << (double)sum1 / (double)sum2 <<'\t'<< Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] << endl;
				}
				else if (Shape == '3')
				{
					double base[9] = { 0 };
					double Imagedata3_a_3temp[9] = { 0 };
					double sum1 = 0, sum2 = 0, temp = 0;
					double a1, a2, a3;
					double a10, a20, a30;
					a10 = 1 / (2 * PI * Sig * Sig);
					a20 = 1 / (2 * PI * Sig * Sig) * exp(-(double)1 / (2 * Sig * Sig));//exp(-(double)1 / (2 * Sig * Sig));
					a30 = 1 / (2 * PI * Sig * Sig) * exp(-(double)2 / (2 * Sig * Sig));//exp(-(double)2 / (2 * Sig * Sig));
					double a00;
					a00 = a10 + 4 * a20 + 4 * a30;
					//cout << a00 << endl;
					//system("pause");
					a1 = sqrt(a10 / a00);//
					a2 = sqrt(a20 / a00);//
					a3 = sqrt(a30 / a00);//
					base[0] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 16)) + s];
					base[1] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 17)) + s];
					base[2] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 16) + (j + 18)) + s];
					base[3] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 16)) + s];
					base[4] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 17)) + s];
					base[5] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 17) + (j + 18)) + s];
					base[6] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 16)) + s];
					base[7] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 17)) + s];
					base[8] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i + 18) + (j + 18)) + s];
					for (int i0 = i - Na; i0 <= i + Na; i0 = i0 + 1)
					{
						for (int j0 = j - Na; j0 <= j + Na; j0 = j0 + 1)
						{
							double avg;
							avg = Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17 - 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17)) + s]\
								+ Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 - 1) + (j0 + 17 + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17 - 1)) + s]\
								+ Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17 + 1)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17 - 1)) + s]\
								+ Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17)) + s] + Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17 + 1) + (j0 + 17 + 1)) + s];
							avg = avg / 8;
							if (abso(i0 - i) <= 1 && abso(j0 - j) <= 1)
							{

							}
							else
							{
								if ((Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] == 255 || Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] == 0) && (abso(avg - Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s]) > 40))//
								{

								}
								else
								{
									Imagedata3_a_3temp[0] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 16)) + s];
									Imagedata3_a_3temp[1] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 17)) + s];
									Imagedata3_a_3temp[2] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 16) + (j0 + 18)) + s];
									Imagedata3_a_3temp[3] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 16)) + s];
									Imagedata3_a_3temp[4] = a1 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s];;
									Imagedata3_a_3temp[5] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 18)) + s];
									Imagedata3_a_3temp[6] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 16)) + s];
									Imagedata3_a_3temp[7] = a2 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 17)) + s];
									Imagedata3_a_3temp[8] = a3 * Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 18) + (j0 + 18)) + s];
									double tempa = 0.0, suma = 0.0;
									for (int q = 0; q < 9;q = q++)
									{
										tempa = (Imagedata3_a_3temp[q] - base[q])*(Imagedata3_a_3temp[q] - base[q]);/// 9;
										suma = suma + tempa;
									}
									temp = exp(-(double)suma / (double)(2 * Sig1 * Sig1));
									sum1 = sum1 + (double)Imagedataex[BytesPerPixel * ((Size1 + 34) * (i0 + 17) + (j0 + 17)) + s] * temp;
									sum2 = sum2 + temp;
								}
							}
						}
					}
				
					Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = (unsigned char)((double)sum1 / (double)sum2);
					//cout << (float)sum1 <<'\t'<< (float)sum2 << endl;
				}
			}
		}
		cout << "the PSNR of " << seq[s] << " for filtered image is: " << PSNR_m(s, BytesPerPixel, Size1, Size2, Imagedata, Imagedataori) << endl;
		cout << endl;

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "The running time of " << seq[s] << " is " <<duration << endl;
	}
}


void P3_b(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3)
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

	clock_t start, finish;
	double duration;
	start = clock();

	char seq[4] = "RGB";

	for (int s = 0; s < BytesPerPixel; s++)
	{
		cout << "the PSNR of " << seq[s] << " for noisy image is: " << PSNR_m(s, BytesPerPixel, Size1, Size2, Imagedata, Imagedataori) << endl;//output the PSNR of origin image
	}

	//Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
	//Midfil(1, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin1);
	//Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
	//Midfil(2, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin2);
	//Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
	//Midfil(3, BytesPerPixel, Size1, Size2, Imagedataex, Imagedatasin3);
	//for (int i = 0; i < Size2; i++)
	//	for (int j = 0; j < Size1; j++)
	//		Imagedata[3 * ((Size1)* i + j) + 0] = Imagedatasin1[1 * ((Size1)* i + j) + 0];
	//for (int i = 0; i < Size2; i++)
	//	for (int j = 0; j < Size1; j++)
	//		Imagedata[3 * ((Size1)* i + j) + 1] = Imagedatasin2[1 * ((Size1)* i + j) + 0];
	//for (int i = 0; i < Size2; i++)
	//	for (int j = 0; j < Size1; j++)
	//		Imagedata[3 * ((Size1)* i + j) + 2] = Imagedatasin3[1 * ((Size1)* i + j) + 0];
	Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);//extend the edge for 17 times
	Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedata, Imagedataex);
	Ext(BytesPerPixel, Size1 + 6, Size2 + 6, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 8, Size2 + 8, Imagedata, Imagedataex);
	Ext(BytesPerPixel, Size1 + 10, Size2 + 10, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 12, Size2 + 12, Imagedata, Imagedataex);
	Ext(BytesPerPixel, Size1 + 14, Size2 + 14, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 16, Size2 + 16, Imagedata, Imagedataex);
	Ext(BytesPerPixel, Size1 + 18, Size2 + 18, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 20, Size2 + 20, Imagedata, Imagedataex);
	Ext(BytesPerPixel, Size1 + 22, Size2 + 22, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 24, Size2 + 24, Imagedata, Imagedataex);
	Ext(BytesPerPixel, Size1 + 26, Size2 + 26, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 28, Size2 + 28, Imagedata, Imagedataex);
	Ext(BytesPerPixel, Size1 + 30, Size2 + 30, Imagedataex, Imagedata);
	Ext(BytesPerPixel, Size1 + 32, Size2 + 32, Imagedata, Imagedataex);
	NLMean_fil(BytesPerPixel, Size1, Size2, Imagedataex, Imagedata, Imagedataori);
	//Seq(BytesPerPixel, Size1, Size2, Imagedata, Imagedatasin);
	//Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
	//NLMean_fil(BytesPerPixel, Size1, Size2, Imagedataex, Imagedata, Imagedataori);
	//Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataex);
	//NLMean_fil(BytesPerPixel, Size1, Size2, Imagedataex, Imagedata, Imagedataori);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << duration << endl;

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	//	fwrite(Imagedataex, sizeof(unsigned char), (Size2 + 2) * (Size1 + 2) * 1, file);
	fwrite(Imagedata, sizeof(unsigned char), Size1 * Size2 * BytesPerPixel, file);
	fclose(file);
	system("pause");
}
