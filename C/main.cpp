// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

// Compiled on WINDOWS 10 with Visual C++
// solution for all Problem 1; all Problem2; Problem3 (b) and (a)
// for problem3 (c), this exe can merge the RGB gray images into one color image
// Use the DOS command to open the program and run it by the README.txt

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

unsigned char Imagedata[100000000] = { 0 };
unsigned char Imagedata1_a_1[100000000] = { 0 };
unsigned char Imagedata1_a_2[100000000] = { 0 };
unsigned char Imagedatasin[100000000] = { 0 };
unsigned char Imagedatasin1[100000000] = { 0 };
unsigned char Imagedatasin2[100000000] = { 0 };
unsigned char Imagedatasin3[100000000] = { 0 };
unsigned char Imagedata1_c[100000000] = { 0 };
unsigned char Imagedata2_b[100000000] = { 0 };
unsigned char Imagedataex1[100000000] = { 0 };
unsigned char Imagedataex[100000000] = { 0 };
unsigned char Imagedataori[100000000] = { 0 };
unsigned char Imagedata1[100000000] = { 0 };
unsigned char Imagedataexavg[100000000] = { 0 };
unsigned char ImagedataPlus[100000000] = { 0 };

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	int BytesPerPixel;
	int Size1 = 256, Size2 = 256, Size3 = 300, Size4 = 300;
	int Problem;
	char Part;

	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size1 = 256] [Size2 = 256]" << endl;
		return 0;
	}

	cout << "Solve which problems: ";
	cin >> Problem;
	cout << "solve which part: ";
	cin >> Part;

	// Check if image is grayscale or color
	if (argc < 4) {
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5) {
			Size1 = atoi(argv[4]);
			Size2 = atoi(argv[5]);
		}
	}
	void P1_a(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, int question);
	void P1_a_3(int BytesPerPixel, int Size1, int Size2, int Size3, int Size4, char *a1, char *a2, char *a3);
	void P1_b(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2);
	void P1_c(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3);
	void P2_a(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, int a);
	void P2_b(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2);
	void P2_c(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2);
	void P3_a(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3);
	void P3_b(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3);
	void P3_c(int BytesPerPixel, int Size1, int Size2, char *a1, char *a2, char *a3, char *a4, char *a5);
	if (Problem == 1)
	{
		if ((Part == 'A') || (Part == 'a'))
		{
			int question = 1;
			cout << "Do which number of question: ";
			cin >> question;
			if (question == 1 || question == 2)
			{
				P1_a(BytesPerPixel, Size1, Size2, argv[1], argv[2], question);
			}
			else
			{
				if (argc < 9)
				{
					cout << "Not enough parameters." << endl;
					system("pause");
				}
				else
				{
					Size3 = atoi(argv[7]);
					Size4 = atoi(argv[8]);
					P1_a_3(BytesPerPixel, Size1, Size2, Size3, Size4, argv[1], argv[2], argv[6]);
				}
			}
		}
		else if ((Part == 'B') || (Part == 'b'))
		{
			P1_b(BytesPerPixel, Size1, Size2, argv[1], argv[2]);
		}
		else if ((Part == 'C') || (Part == 'c'))
		{
			if (argc < 7)
			{
				cout << "Error, Lack Back Picture." << endl;
				system("pause");
				return 0;
			}
			else
			{
				P1_c(BytesPerPixel, Size1, Size2, argv[1], argv[2], argv[6]);
			}
		}
	}
	else if (Problem == 2)
	{
		if ((Part == 'A') || (Part == 'a'))
		{
			int a;
			cout << "Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: ";
			cin >> a;
			P2_a(BytesPerPixel, Size1, Size2, argv[1], argv[2], a);
		}
		else if ((Part == 'B') || (Part == 'b'))
		{
			int a;
			cout << "Use which approach 1)single transfer function; 2) bucket fill cdf 3) change only the luminance (HSL): ";
			cin >> a;
			if (a == 1)
			{
				P2_a(BytesPerPixel, Size1, Size2, argv[1], argv[2], 1);
			}
			else if (a == 2)
			{
				P2_a(BytesPerPixel, Size1, Size2, argv[1], argv[2], 3);
			}
			else if (a == 3)
			{
				P2_b(BytesPerPixel, Size1, Size2, argv[1], argv[2]);
			}
		}
		else if ((Part == 'C') || (Part == 'c'))
		{
			P2_c(BytesPerPixel, Size1, Size2, argv[1], argv[2]);
		}
	}
	else if (Problem == 3)
	{
		if ((Part == 'A') || (Part == 'a'))
		{
			P3_a(BytesPerPixel, Size1, Size2, argv[1], argv[2], argv[6]);
		}
		else if ((Part == 'B') || (Part == 'b'))
		{
			P3_b(BytesPerPixel, Size1, Size2, argv[1], argv[2], argv[6]);
		}
		else if ((Part == 'C') || (Part == 'c'))
		{
			if (argc < 8)
			{
				cout << "Error, Lack Back Picture." << endl;
				system("pause");
				return 0;
			}
			else
			{
				P3_c(BytesPerPixel, Size1, Size2, argv[1], argv[2], argv[6], argv[7], argv[8]);
			}
		}
	}
	
	system("pause");
	return 0;
}