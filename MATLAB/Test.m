% EE 569 Homework #1
% date:		Feb. 3rd, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
%************************************************************************************************************************************
% solution for Problem3 (c)	Block matching and 3-D (BM3D) transform filter
% M-file name:              Test.m
% Usage                     Test
% Application Name: 		Image_Processing_HW1.exe
% Reference:                BM3D is an algorithm for attenuation of additive white Gaussian noise from 
%                           grayscale images. This algorithm reproduces the results from the article:
%
%                           [1] K. Dabov, A. Foi, V. Katkovnik, and K. Egiazarian, "Image Denoising 
%                               by Sparse 3D Transform-Domain Collaborative Filtering," 
%                               IEEE Transactions on Image Processing, vol. 16, no. 8, August, 2007.
%                               preprint at http://www.cs.tut.fi/~foi/GCF-BM3D.
% Referenced file:          BM3D.m and its attached files
%************************************************************************************************************************************
image_name1 = 'D:\EE569_Assignment\1\a34.png';%path of R sequence of origin image
image_name_n1 = 'D:\EE569_Assignment\1\a31.png';%path of R sequence of noisy image
y1 = im2double(imread(image_name1));
z1 = im2double(imread(image_name_n1));
[PSNR1, y_est1] = BM3D(y1, z1, 25, 'vn_old', 1);
imwrite(y_est1,'pepper_R.png');