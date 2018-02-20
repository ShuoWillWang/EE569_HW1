// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//CMY, HSL and Sepia filter for P1_b
//*********************************************************


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedatasin[100000000];

double maxi(double a, double b, double c) // maximum value of three number
{
	double x, x1;
	if (a>b)
	{
		x = a;
	}
	else
	{
		x = b;
	}
	if (x>c)
	{
		x1 = x;
	}
	else
	{
		x1 = c;
	}
	return x1;
}

double mini(double a, double b, double c) // minimum of three number
{
	double x, x1;
	if (a<b)
	{
		x = a;
	}
	else
	{
		x = b;
	}
	if (x<c)
	{
		x1 = x;
	}
	else
	{
		x1 = c;
	}
	return x1;
}

void P1_b(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2)
{
	FILE *file;
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	int question;
	cout << "Do which number of question: ";
	cin >> question;

	if (question == 1)//CMY
	{
		unsigned char ***Imagedata2_1_temp = new unsigned char **[Size2];
		for (int i = 0; i<Size2; i++)
		{
			Imagedata2_1_temp[i] = new unsigned char *[Size1];
			for (int j = 0; j<Size1; j++)
			{
				Imagedata2_1_temp[i][j] = new unsigned char[1];
			}
		}
		char a;
		cout << "Input the sequence you want to output: C, M or Y: ";
		cin >> a;

		float temp;

		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				if (a == 'C' || a == 'c')//get the C sequence
				{
					temp = Imagedata[3 * (Size1 * i + j) + 0];
					temp = temp / 255;
					temp = 1 - temp;
					Imagedata2_1_temp[i][j][0] = 255 * temp;
				}
				else
				{
					if (a == 'M' || a == 'm')//get the M channel
					{
						temp = Imagedata[3 * (Size1 * i + j) + 1];
						temp = temp / 255;
						temp = 1 - temp;
						Imagedata2_1_temp[i][j][0] = 255 * temp;
					}
					else if (a == 'Y' || a == 'y')//get the Y channel
					{
						temp = Imagedata[3 * (Size1 * i + j) + 2];
						temp = temp / 255;
						temp = 1 - temp;
						Imagedata2_1_temp[i][j][0] = 255 * temp;
					}
				}
			}
		}
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata2_1_temp[i][j][0];//save the gray image
			}
		}
		cout << "the final output sequence is " << a << endl;
	}
	else if (question == 2)//HSl
	{
		unsigned char ***Imagedata2_2_temp = new unsigned char **[Size2];
		for (int i = 0; i<Size2; i++)
		{
			Imagedata2_2_temp[i] = new unsigned char *[Size1];
			for (int j = 0; j<Size1; j++)
			{
				Imagedata2_2_temp[i][j] = new unsigned char[1];
			}
		}
		double temp, l;
		double R, G, B;
		char a;
		cout << "Input the sequence you want to output: H, L or S: ";
		cin >> a;
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
				if (a == 'H' || a == 'h')//calculate the H
				{
					if (C == 0)
					{
						Imagedata2_2_temp[i][j][0] = 0;
					}
					else
					{
						if ((M == R) && (G >= B))
						{
							temp = (G - B) / C;
							Imagedata2_2_temp[i][j][0] = 60 * (temp) * ((double)255 / 360);
						}
						else if ((M == R) && (G<B))
						{
							temp = (G - B) / C;
							Imagedata2_2_temp[i][j][0] = (60 * (temp) + 360) * ((double)255 / 360);
						}
						else if (M == G)
						{
							temp = (B - R) / C;
							Imagedata2_2_temp[i][j][0] = (60 * (temp)+120) * ((double)255 / 360);
						}
						else if (M == B)
						{
							temp = (R - G) / C;
							Imagedata2_2_temp[i][j][0] = (60 * (temp)+240) * ((double)255 / 360);
						}
					}
				}
				else if (a == 'L' || a == 'l')//calculate the L
				{
					temp = (M + m) / 2;
					Imagedata2_2_temp[i][j][0] = temp * 255;
				}
				else if (a == 'S' || a == 's')//calculate the S
				{
					l = (M + m) / 2;
					if (l == 0)
					{
						Imagedata2_2_temp[i][j][0] = 0;
					}
					else if ((l>0) && (l<0.5))
					{
						temp = C / (2 * l);
						Imagedata2_2_temp[i][j][0] = temp * 255;
					}
					else
					{
						temp = C / (2 - 2 * l);
						Imagedata2_2_temp[i][j][0] = temp * 255;
					}
				}
			}
		}
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata2_2_temp[i][j][0];//save the gray image
			}
		}
		cout << "the final output sequence is " << a << endl;
	}
	else if (question == 3)//Problem 2_3_a the first part of the Spiea filter (gray iamge)
	{
		unsigned char ***Imagedata2_3_temp = new unsigned char **[Size2];
		for (int i = 0; i<Size2; i++)
		{
			Imagedata2_3_temp[i] = new unsigned char *[Size1];
			for (int j = 0; j<Size1; j++)
			{
				Imagedata2_3_temp[i][j] = new unsigned char[1];
			}
		}
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedata2_3_temp[i][j][0] = 0.21*Imagedata[3 * (Size1 * i + j) + 0] + 0.72*Imagedata[3 * (Size1 * i + j) + 1] + 0.07*Imagedata[3 * (Size1 * i + j) + 2];
			}
		}
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedatasin[1 * (Size1 * i + j) + 0] = Imagedata2_3_temp[i][j][0];
			}
		}
	}
	else if (question == 4)//Problem 2_3_b second part of the Spiea filter (color iamge)
	{
		unsigned char ***Imagedata2_4 = new unsigned char **[Size2];
		for (int i = 0; i<Size2; i++)
		{
			Imagedata2_4[i] = new unsigned char *[Size1];
			for (int j = 0; j<Size1; j++)
			{
				Imagedata2_4[i][j] = new unsigned char[BytesPerPixel];
			}
		}
		float temp1, temp2, temp3;
		float temp01, temp02, temp03;

		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				temp1 = (float)Imagedata[3 * (Size1 * i + j) + 0];
				temp2 = (float)Imagedata[3 * (Size1 * i + j) + 1];
				temp3 = (float)Imagedata[3 * (Size1 * i + j) + 2];
				temp01 = (0.393 + 0.769 + 0.189) * (0.21 * temp1 + 0.72 * temp2 + 0.07 * temp3);
				if (temp01 >= 255)
				{
					Imagedata2_4[i][j][0] = 255;
				}
				else
				{
					Imagedata2_4[i][j][0] = temp01;
				}
				temp02 = (0.349 + 0.686 + 0.168) * (0.21 * temp1 + 0.72 * temp2 + 0.07 * temp3);
				if (temp02 >= 255)
				{
					Imagedata2_4[i][j][1] = 255;
				}
				else
				{
					Imagedata2_4[i][j][1] = temp02;
				}
				temp03 = (0.272 + 0.534 + 0.131) * (0.21 * temp1 + 0.72 * temp2 + 0.07 * temp3);
				if (temp03 >= 255)
				{
					Imagedata2_4[i][j][2] = 255;
				}
				else
				{
					Imagedata2_4[i][j][2] = temp03;
				}
			}
		}
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedata[3 * (Size1 * i + j) + 0] = Imagedata2_4[i][j][0];
				Imagedata[3 * (Size1 * i + j) + 1] = Imagedata2_4[i][j][1];
				Imagedata[3 * (Size1 * i + j) + 2] = Imagedata2_4[i][j][2];
			}
		}
	}
	if (question == 5)//CMY color
	{
		unsigned char ***Imagedata2_5 = new unsigned char **[Size2];
		for (int i = 0; i<Size2; i++)
		{
			Imagedata2_5[i] = new unsigned char *[Size1];
			for (int j = 0; j<Size1; j++)
			{
				Imagedata2_5[i][j] = new unsigned char[BytesPerPixel];
			}
		}

		float temp;

		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				temp = Imagedata[3 * (Size1 * i + j) + 0];
				temp = temp / 255;
				temp = 1 - temp;
				Imagedata2_5[i][j][0] = 255 * temp;
				temp = Imagedata[3 * (Size1 * i + j) + 1];
				temp = temp / 255;
				temp = 1 - temp;
				Imagedata2_5[i][j][1] = 255 * temp;
				temp = Imagedata[3 * (Size1 * i + j) + 2];
				temp = temp / 255;
				temp = 1 - temp;
				Imagedata2_5[i][j][2] = 255 * temp;
			}
		}
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedata[3 * (Size1 * i + j) + 0] = Imagedata2_5[i][j][0];
				Imagedata[3 * (Size1 * i + j) + 1] = Imagedata2_5[i][j][1];
				Imagedata[3 * (Size1 * i + j) + 2] = Imagedata2_5[i][j][2];
			}
		}
	}
	if (question == 6)//HSL color
	{
		unsigned char ***Imagedata2_6 = new unsigned char **[Size2];
		for (int i = 0; i<Size2; i++)
		{
			Imagedata2_6[i] = new unsigned char *[Size1];
			for (int j = 0; j<Size1; j++)
			{
				Imagedata2_6[i][j] = new unsigned char[BytesPerPixel];
			}
		}
		float temp, l;
		float R, G, B;
		float M, m, C;

		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				R = (float)Imagedata[3 * (Size1 * i + j) + 0] / 255;
				G = (float)Imagedata[3 * (Size1 * i + j) + 1] / 255;
				B = (float)Imagedata[3 * (Size1 * i + j) + 2] / 255;
				M = maxi(R, G, B);
				m = mini(R, G, B);
				C = M - m;
				if (C == 0)
				{
					Imagedata2_6[i][j][0] = 0;
				}
				else
				{
					if ((M == R) && (G >= B))
					{
						temp = (G - B) / C;
						Imagedata2_6[i][j][0] = 60 * (temp) / 360 * 255;
					}
					else if ((M == R) && (G<B))
					{
						temp = (G - B) / C;
						Imagedata2_6[i][j][0] = (60 * (temp)+360) / 360 * 255;
					}
					else if (M == G)
					{
						temp = (B - R) / C;
						Imagedata2_6[i][j][0] = (60 * (temp)+120) / 360 * 255;
					}
					else if (M == B)
					{
						temp = (R - G) / C;
						Imagedata2_6[i][j][0] = (60 * (temp)+240) / 360 * 255;
					}
				}
				temp = (M + m) / 2;
				Imagedata2_6[i][j][1] = temp * 255;
				l = (M + m) / 2;
				if (l == 0)
				{
					Imagedata2_6[i][j][2] = 0;
				}
				else if ((l>0) && (l<0.5))
				{
					temp = C / (2 * l);
					Imagedata2_6[i][j][2] = temp * 255;
				}
				else
				{
					temp = C / (2 - 2 * l);
					Imagedata2_6[i][j][2] = temp * 255;
				}
			}
		}
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j<Size1; j++)
			{
				Imagedata[3 * (Size1 * i + j) + 0] = Imagedata2_6[i][j][0];
				Imagedata[3 * (Size1 * i + j) + 1] = Imagedata2_6[i][j][1];
				Imagedata[3 * (Size1 * i + j) + 2] = Imagedata2_6[i][j][2];
			}
		}
	}


	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix
	if ((question == 4) || (question == 5) || (question == 6))
	{
		if (!(file = fopen(a2, "wb"))) {
			cout << "Cannot open file: " << a2 << endl;
			exit(1);
		}
		fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
		fclose(file);
	}
	else
	{
		if (!(file = fopen(a2, "wb"))) {
			cout << "Cannot open file: " << a2 << endl;
			exit(1);
		}
		fwrite(Imagedatasin, sizeof(unsigned char), Size2*Size1 * 1, file);
		fclose(file);
	}
	system("pause");
}
