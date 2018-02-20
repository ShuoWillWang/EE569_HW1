// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//******************************************************************************************************************
//Transfer function, CDF, bucket filling CDF and advanced transfer function for P2_a, P2_b_1 and P2_b_2
//******************************************************************************************************************



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];

void P2_a(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, int a)
{
	FILE *file;

	unsigned char  ***Imagedata2_a;
	Imagedata2_a = new unsigned char**[Size2];
	for (int i = 0;i<Size2;i++)
	{
		Imagedata2_a[i] = new unsigned char*[Size1];
		for (int j = 0;j<Size1;j++)
		{
			Imagedata2_a[i][j] = new unsigned char[BytesPerPixel];
		}
	}

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	//Problem 2_1_1

	for (int s = 0; s<BytesPerPixel; s++)
	{
		long his[256] = { 0 };
		
		double pdf[256], cdf[256];

		for (int i = 0; i<Size2; i++)//get the histogram
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
		int Fmin, Fmax;

		for (int num = 0; num<256; num++)//get the pdf and cdf
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
			if (cdf[num] <= 0.1)
			{
				Fmin = num; // get the minimum value with 0.1 Prob. for transter function
			}
			if (cdf[num] <= 0.9)
			{
				Fmax = num; // get the maximum value with 0.1 Prob. for transter function
			}
		}

		if (a == 1)//single transfer function
		{
			double k, l;
			k = ((double)(255 * 0.9) - (double)(255 * 0.1)) / (Fmax - Fmin); //get the gradient of the transfer function
			l = (double)(255 * 0.9) - k * Fmax;//get the intercept of the transfer function

			cout << k << '\t' << l << endl;

			double temp1;

			for (int i = 0; i<Size2; i++)
			{
				for (int j = 0; j<Size1; j++)
				{
					temp1 = k * (double)Imagedata[BytesPerPixel * (Size1 * i + j) + s] + l;//get the new pixel
					//while((temp1<0)||(temp1>255))
					//{
					//	if(temp1<0)
					//	{
					//		temp1 = -temp1;
					//	}
					//	else if(temp1>255)
					//	{
					//		temp1 = 255 - (temp1 - 255);
					//	}
					//}
					//Imagedata2_a[i][j][s] = temp1;
					if (temp1<0)
					{
						temp1 = 0;
					}
					else if (temp1>255)
					{
						temp1 = 255;
					}
					Imagedata2_a[i][j][s] = temp1;
				}
			}
			//int temp1a;
			//for (int i = 0; i<Size2; i++)
			//{
			//	for (int j = 0; j<Size1; j++)
			//	{
			//		temp1a = Imagedata2_a[i][j][0];
			//		cout << temp1a << "  ";
			//	}
			//	cout << endl;
			//}
		}
		else if (a == 2)//cdf
		{
			double temp2;
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
					temp2 = 255 * temp2;//get the new pixel
					Imagedata2_a[i][j][s] = temp2;
				}
			}
		}
		else if (a == 4)//advanced transfer function
		{
			int Fma[10] = {0};//save the points for making each transfer function in each part
			int Fmi[10] = {0};
			int ind = 1;
			Fmi[0] = Fmin;
			for (int num = Fmin; num < 256; num++)
			{
				if (num > Fmin && pdf[num] == 0)
				{
					Fma[0] = num; 
					ind = 0;break;
				}
			}
			int k = 0;

			for (int num = Fma[0]; num < 256; num++)
			{
				if (cdf[num] - cdf[Fma[k]] >= 0.05 && ind == 0)
				{
					k++;
					Fmi[k] = num;
					ind = 1;
				}
				else if (ind == 1 && pdf[num] == 0)
				{
					ind = 0;
					Fma[k] = num;
				}
				else if (num == Fmax)
				{
					ind = 0;
					Fma[k] = num;break;
				}
			}
			double kc[10], l[10];//the gradient and intercept for all transfer function
			for (int k0 = 0; k0 <= k; k0++)
			{
				cout << Fma[k0] << '\t';
			}
			cout << endl;
			for (int k0 = 0; k0 <= k; k0++)
			{
				cout << Fmi[k0] << '\t';
			}
			cout << endl;
			system("pause");
			for (int k0 = 0; k0 <= k; k0++)
			{
				kc[k0] = ((double)(255 * cdf[Fma[k0]]) - (double)(255 * cdf[Fmi[k0]])) / (Fma[k0] - Fmi[k0]);
				l[k0] = (double)(255 * cdf[Fma[k0]]) - kc[k0] * Fma[k0];
			}
			double temp1;

			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					for (int k0 = 0; k0 <= k; k0++)
					{
						if (Imagedata[BytesPerPixel * (Size1 * i + j) + s] <= Fma[k0])
						{
							temp1 = kc[k0] * (double)Imagedata[BytesPerPixel * (Size1 * i + j) + s] + l[k0]; break;//get the new pixel value
						}
						else
						{
							temp1 = kc[k] * (double)Imagedata[BytesPerPixel * (Size1 * i + j) + s] + l[k]; break;
						}
					}
					if (temp1<0)
					{
						temp1 = 0;
					}
					else if (temp1>255)
					{
						temp1 = 255;
					}
					Imagedata2_a[i][j][s] = temp1;
				}
			}
			for (int k0 = 0; k0 <= k; k0++)
			{
				cout << kc[k0] << '\t';
			}
			cout << endl;
			for (int k0 = 0; k0 <= k; k0++)
			{
				cout << l[k0] << '\t';
			}
		}
		else if (a == 3)//bucket fill cdf
		{
			long stand;
			stand = (Size1 * Size2) / 256; // the number of pixels for each pixel value
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
							if (i0<stand)
							{
								i0++; //detect if we should change to another pixel value
							}
							else
							{
								n++;
								i0 = 1;
							}
							if (n >= 255)
							{
								Imagedata2_a[i][j][s] = 255;
							}
							else
							{
								Imagedata2_a[i][j][s] = n;
							}
						}
					}
				}
			}
		}
		//for (int num = 0; num < 256; num++)//output the pdf and cdf of the origin image
		//{
		//	cout << pdf[num] << endl;
		//}
		//cout << endl;
		//for (int num = 0; num < 256; num++)
		//{
		//	cout << cdf[num] << endl;
		//}
	}

	//int his1[256] = { 0 };
	//for (int i = 0; i<Size2; i++)
	//{
	//	for (int j = 0; j<Size1; j++)
	//	{
	//		for (int num = 0; num<256; num++)
	//		{
	//			if (Imagedata2_a[i][j][0] == num)
	//			{
	//				his1[num] = his1[num] + 1;break;
	//			}
	//		}
	//	}
	//}

	//for (int num = 0; num<256; num++)
	//{
	//	cout << his1[num] << "  ";
	//}
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedata[BytesPerPixel * (Size1 * i + j) + s] = Imagedata2_a[i][j][s];
			}
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
