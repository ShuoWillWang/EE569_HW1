// EE 569 Homework #1
// date:	Feb. 3rd, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu
//****************************************************************************************
// Compiled on WINDOWS 10 with Visual C++
// solution for all Problem 1; all Problem2; Problem3 (a) and (b)
// for problem3 (c), this exe can merge the RGB gray images into one color image
// Application Name: 	Image_Processing_HW1.exe
// Use the DOS command to open the program and run it. 
// Recommend: 		Use the .bat file to run
//****************************************************************************************
Problem 1(a):	Mirroring, Resizing and Compositing
1) Mirror queation
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\dog.raw D:\EE569_Assignment\1\dog_mirror.raw 3 300 300
Solve which problems: 1
solve which part: a
Do which number of question: 1
Press any key to continue . . .
Press any key to continue . . .


2) Resizing
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\dog_mirror.raw D:\EE569_Assignment\1\dog_200x200.raw 3 300 300
Solve which problems: 1
solve which part: a
Do which number of question: 2
Input the width of the picture: 200
The height of the new picture is: 200
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\dog_mirror.raw D:\EE569_Assignment\1\dog_400x400.raw 3 300 300
Solve which problems: 1
solve which part: a
Do which number of question: 2
Input the width of the picture: 400
The height of the new picture is: 400
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\dog_mirror.raw D:\EE569_Assignment\1\dog_600x600.raw 3 300 300
Solve which problems: 1
solve which part: a
Do which number of question: 2
Input the width of the picture: 600
The height of the new picture is: 600
Press any key to continue . . .
Press any key to continue . . .


3) Compositing
Open method: {path_of_program_name path_of_input_background.raw path_of_output_image.raw BytesPerPixel Size1_background(Width) Size2_background(Height) path_of_input_plus_image.raw Size1_plus_image(Width) Size2_plus_image(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\beach.raw D:\EE569_Assignment\1\beach_dog.raw 3 1914 808 D:\EE569_Assignment\1\dog_mirror.raw 300 300
Solve which problems: 1
solve which part: a
Do which number of question: 3
input the R of delete color:120
input the G of delete color:120
input the complement of B of delete color:120 // the pixel value of B = 255 - complement of B
input the location to put the dog.
the first cordinates is: 1100
the second cordinates is: 400



Problem 1(b):	Color Space Transformation
1) CMY
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)} P.S. each running will output only one color channel image
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\parrot.raw D:\EE569_Assignment\1\parrot_C.raw 3 512 384
Solve which problems: 1
solve which part: b
Do which number of question: 1
Input the sequence you want to output: C, M or Y: C
the final output sequence is C
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\parrot.raw D:\EE569_Assignment\1\parrot_M.raw 3 512 384
Solve which problems: 1
solve which part: b
Do which number of question: 1
Input the sequence you want to output: C, M or Y: M
the final output sequence is M
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\parrot.raw D:\EE569_Assignment\1\parrot_Y.raw 3 512 384
Solve which problems: 1
solve which part: b
Do which number of question: 1
Input the sequence you want to output: C, M or Y: Y
the final output sequence is Y
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\building.raw D:\EE569_Assignment\1\building_C.raw 3 789 600
Solve which problems: 1
solve which part: b
Do which number of question: 1
Input the sequence you want to output: C, M or Y: C
the final output sequence is C
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\building.raw D:\EE569_Assignment\1\building_M.raw 3 789 600
Solve which problems: 1
solve which part: b
Do which number of question: 1
Input the sequence you want to output: C, M or Y: M
the final output sequence is M
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\building.raw D:\EE569_Assignment\1\building_Y.raw 3 789 600
Solve which problems: 1
solve which part: b
Do which number of question: 1
Input the sequence you want to output: C, M or Y: Y
the final output sequence is Y
Press any key to continue . . .
Press any key to continue . . .


2) HSL
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)} P.S. each running will output only one color channel image
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\cat.raw D:\EE569_Assignment\1\cat_H.raw 3 600 398
Solve which problems: 1
solve which part: b
Do which number of question: 2
Input the sequence you want to output: H, L or S: H
the final output sequence is H
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\cat.raw D:\EE569_Assignment\1\cat_L.raw 3 600 398
Solve which problems: 1
solve which part: b
Do which number of question: 2
Input the sequence you want to output: H, L or S: L
the final output sequence is L
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\cat.raw D:\EE569_Assignment\1\cat_S.raw 3 600 398
Solve which problems: 1
solve which part: b
Do which number of question: 2
Input the sequence you want to output: H, L or S: S
the final output sequence is S
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\dolphin.raw D:\EE569_Assignment\1\dolphin_H.raw 3 640 480
Solve which problems: 1
solve which part: b
Do which number of question: 2
Input the sequence you want to output: H, L or S: H
the final output sequence is H
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\dolphin.raw D:\EE569_Assignment\1\dolphin_L.raw 3 640 480
Solve which problems: 1
solve which part: b
Do which number of question: 2
Input the sequence you want to output: H, L or S: L
the final output sequence is L
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\dolphin.raw D:\EE569_Assignment\1\dolphin_S.raw 3 640 480
Solve which problems: 1
solve which part: b
Do which number of question: 2
Input the sequence you want to output: H, L or S: S
the final output sequence is S
Press any key to continue . . .
Press any key to continue . . .


3) Sepia filter
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\beach.raw D:\EE569_Assignment\1\beach_Gray.raw 3 1914 808
Solve which problems: 1
solve which part: b
Do which number of question: 3 //(to get the gray image I)
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\beach.raw D:\EE569_Assignment\1\beach_Sepia.raw 3 1914 808
Solve which problems: 1
solve which part: b
Do which number of question: 4 //(to get the color image filted by Sepia filter)
Press any key to continue . . .
Press any key to continue . . .



Problem 1(c):	Layer Blending Mode Implementation
Open method: {path_of_program_name path_of_input_top.raw path_of_output_image.raw BytesPerPixel Size1_top(Width) Size2_top(Height) path_of_input_plus_image.raw Size1_bottom_image(Width) Size2_bottom_image(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\top_layer.raw D:\EE569_Assignment\1\top_bottom.raw 3 890 900 D:\EE569_Assignment\1\bottom_layer.raw
Solve which problems: 1
solve which part: c
Input the type: 3
Press any key to continue . . .
Press any key to continue . . .



Problem 2(a):	Histogram Enhancement for Grayscale Images
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_dark.raw D:\EE569_Assignment\1\tulip_dark_STF.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 1
5.82857 -26.9571	//gradient and interception
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_dark.raw D:\EE569_Assignment\1\tulip_dark_CDF.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 2
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_dark.raw D:\EE569_Assignment\1\tulip_dark_CDFB.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 3
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_bright.raw D:\EE569_Assignment\1\tulip_bright_STF.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 1
5.82857 -1140.21	//gradient and interception
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_bright.raw D:\EE569_Assignment\1\tulip_bright_CDF.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 2
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_bright.raw D:\EE569_Assignment\1\tulip_bright_CDFB.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 3
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_mix.raw D:\EE569_Assignment\1\tulip_mix_STF.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 1
0.931507        14.3219		//gradient and interception
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_mix.raw D:\EE569_Assignment\1\tulip_mix_CDF.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 2
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_mix.raw D:\EE569_Assignment\1\tulip_mix_CDFB.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 3
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\tulip_mix.raw D:\EE569_Assignment\1\tulip_mix_ATF.raw 1 400 366
Solve which problems: 2
solve which part: a
Use which method: 1) single transfer function; 2)cdf; 3) bucket fill cdf; 4)advanced transfer function: 4
43      231		//Fmax points
12      220		//Finx points
Press any key to continue . . .
5.05763 	3.16977		//gradient of two transfer functions
-38.9783        -503.954        //interception of two transfer functions
Press any key to continue . . .
Press any key to continue . . .



Problem 2(b):	Histogram Equalization for Color Images
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
1) method A // single transfer function
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\bedroom.raw D:\EE569_Assignment\1\bedroom_STF.raw 3 940 400
Solve which problems: 2
solve which part: b
Use which approach 1)single transfer function; 2) bucket fill cdf 3) change only the luminance (HSL): 1
1.74359 -61.6795	//gradient and interception
Press any key to continue . . .
Press any key to continue . . .

2) method B // bucket filling cdf
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\bedroom.raw D:\EE569_Assignment\1\bedroom_CDFB.raw 3 940 400
Solve which problems: 2
solve which part: b
Use which approach 1)single transfer function; 2) bucket fill cdf 3) change only the luminance (HSL): 2
Press any key to continue . . .
Press any key to continue . . .

3) new method: change only the luminance (HSL) 
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\bedroom.raw D:\EE569_Assignment\1\bedroom_HSL.raw 3 940 400
Solve which problems: 2
solve which part: b
Use which approach 1)single transfer function; 2) bucket fill cdf 3) change only the luminance (HSL): 3
Use 1) cdf or 2) bucket filling cdf: 2
Press any key to continue . . .
Press any key to continue . . .



Problem 2(c):	Histogram Transform
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\forest_1.raw D:\EE569_Assignment\1\forest_1_CDFB.raw 3 960 600
Solve which problems: 2
solve which part: c
Use 1) cdf or 2) bucket filling cdf: 2
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\forest_2.raw D:\EE569_Assignment\1\forest_2_CDFB.raw 3 550 413
Solve which problems: 2
solve which part: c
Use 1) cdf or 2) bucket filling cdf: 2
Press any key to continue . . .
Press any key to continue . . .


Problem 3(a):	Mix noise in color image
Open method: {path_of_program_name path_of_noisy_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height) path_of_origin_image.raw}
1) Gaussian
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_G_3.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 4
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow, 3 or 5 or 7: 3
the PSNR of R for filtered image is: 27.5538
the PSNR of G for filtered image is: 29.3937
the PSNR of B for filtered image is: 25.1881
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_G_5.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 4
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow, 3 or 5 or 7: 5
the PSNR of R for filtered image is: 28.4039
the PSNR of G for filtered image is: 27.8946
the PSNR of B for filtered image is: 26.5404
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_G_7.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 4
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow, 3 or 5 or 7: 7
the PSNR of R for filtered image is: 28.3943
the PSNR of G for filtered image is: 27.3177
the PSNR of B for filtered image is: 26.7134
Press any key to continue . . .
Press any key to continue . . .


2) Average
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_A_3.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 3
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow, 3 or 5 or 7: 3
the PSNR of R for filtered image is: 27.483
the PSNR of G  for filtered image is: 28.995
the PSNR of B  for filtered image is: 25.1308
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_A_5.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 3
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow, 3 or 5 or 7: 5
the PSNR of R  for filtered image is: 27.8914
the PSNR of G  for filtered image is: 26.6049
the PSNR of B  for filtered image is: 26.3032
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_A_7.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 3
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow, 3 or 5 or 7: 7
the PSNR of R  for filtered image is: 27.1198
the PSNR of G  for filtered image is: 24.8736
the PSNR of B for filtered image is: 25.992
Press any key to continue . . .
Press any key to continue . . .


3) Median
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_M_3.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 5
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow , 3 or 5 or 7: 3
the PSNR of R for filtered image is: 24.645
the PSNR of G for filtered image is: 30.3267
the PSNR of B for filtered image is: 29.3284
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_M_5.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 5
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow , 3 or 5 or 7: 5
the PSNR of R for filtered image is: 26.418
the PSNR of G for filtered image is: 30.4527
the PSNR of B for filtered image is: 30.2457
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_M_7.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 5
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of the wimdow , 3 or 5 or 7: 7
the PSNR of R for filtered image is: 26.9948
the PSNR of G for filtered image is: 29.9181
the PSNR of B for filtered image is: 29.9899
Press any key to continue . . .
Press any key to continue . . .


4) Cascade of multiple filters
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_M_M.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 6
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
the PSNR of R for filtered image is: 26.7131
the PSNR of G for filtered image is: 31.4283
the PSNR of B for filtered image is: 30.7314
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_M_G.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 7
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
the PSNR of R for filtered image is: 27.9158
the PSNR of G for filtered image is: 29.2039
the PSNR of B for filtered image is: 30.044
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_G_G.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 8
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
the PSNR of R for filtered image is: 28.308
the PSNR of G for filtered image is: 28.1347
the PSNR of B for filtered image is: 26.4627
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_M_G_G.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 9
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
the PSNR of R for filtered image is: 28.1705
the PSNR of G for filtered image is: 27.9072
the PSNR of B for filtered image is: 29.4459
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_G_M_M.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 10
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
the PSNR of R for filtered image is: 28.316
the PSNR of G for filtered image is: 29.3466
the PSNR of B for filtered image is: 25.8522
Press any key to continue . . .
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_M_M_B.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: a
the list of options:
1) show the gray picture for a specific channels:
2) justify if it has pepper and sault and show the histogram of the noise [-255 255) or histogram the image pixel values:
3) avg filter:
4) Gaussian filter:
5) Median filter:
6) Median + Median filters:
7) Median + Gaussian filters:
8) Gaussian + Gaussian filters:
9) Median + Gaussian + Gaussian filters:
10) Gaussian + Median + Median:
11) Median + Bilateral filter:
Choose the issue you want to solve: 11
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
the PSNR of R for filtered image is: 28.0852
the PSNR of G for filtered image is: 30.6886
the PSNR of B for filtered image is: 30.4469
The running time is 30.472
Press any key to continue . . .
Press any key to continue . . .



Problem 3(b):	Mix noise in color image
Open method: {path_of_program_name path_of_noisy_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height) path_of_origin_image.raw}
1) Pepper (take one as example)
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\pepper_noisy.raw D:\EE569_Assignment\1\pepper_filt_NLM_23_7_1.8_15_9_15.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw
Solve which problems: 3
solve which part: b
the PSNR of R for noisy image is: 20.3157
the PSNR of G for noisy image is: 28.2002
the PSNR of B for noisy image is: 17.4843
input the size of searching window (any positive odd int): 23
input the shape of calculation window (input 3 5 or 7): 7
input the Sigma Value of Gaussian kernel (a) (any positive number): 1.8
input the h Value of Filter (any positive number): 15
the PSNR of R for filtered image is: 29.2931

The running time of R is 32.447
input the h Value of Filter (any positive number): 9
the PSNR of G for filtered image is: 30.3752

The running time of G is 32.599
input the h Value of Filter (any positive number): 15
the PSNR of B for filtered image is: 28.3356

The running time of B is 40.895
Press any key to continue . . .
Press any key to continue . . .
2) Sailboat
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\sailboat_noisy.raw D:\EE569_Assignment\1\sailboat_filt_NLM_23_7_1.12_15_16_16.2.raw 3 512 512 D:\EE569_Assignment\1\sailboat.raw
Solve which problems: 3
solve which part: b
the PSNR of R for noisy image is: 20.2497
the PSNR of G for noisy image is: 20.7585
the PSNR of B for noisy image is: 20.7194
input the size of searching window (any positive odd int): 23
input the shape of calculation window (input 3 5 or 7): 7
input the Sigma Value of Gaussian kernel (a) (any positive number): 1.12
input the h Value of Filter (any positive number): 15
the PSNR of R for filtered image is: 27.3352

The running time of R is 32.873
input the h Value of Filter (any positive number): 16.2
the PSNR of G for filtered image is: 25.9818

The running time of G is 30.567
input the h Value of Filter (any positive number): 16.2
the PSNR of B for filtered image is: 26.3381

The running time of B is 30.504
176.276
Press any key to continue . . .
Press any key to continue . . .



Problem 3(c):	Block matching and 3-D (BM3D) transform filter
// Usage: even though we use the MATLAB to geal with the BM3D filter, we can use this code to merge the image because the output of image are gray scale image representing the R, G and B.
Open method: {path_of_program_name path_of_R_image.raw path_of_output_image.raw BytesPerPixel = 3 Size1(Width) Size2(Height) path_of_origin_image.raw path_of_G_image.raw path_of_B_image.raw}
D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW1\Debug\Image_Processing_HW1.exe D:\EE569_Assignment\1\MATLAB\pepper_R.raw D:\EE569_Assignment\1\MATLAB\a37.raw 3 512 512 D:\EE569_Assignment\1\pepper.raw D:\EE569_Assignment\1\MATLAB\pepper_G.raw D:\EE569_Assignment\1\MATLAB\pepper_B.raw
Solve which problems: 3
solve which part: c
Press any key to continue . . .
