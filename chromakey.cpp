/*********************************************************************
 File:     chromakey.cpp

 Author: Minxuan Song

 Email address: minxuans@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold);



void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
  // Image data array
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  if (argc < 6) {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold " 
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }
	
  if (readRGBBMP(argv[1], inputImage)) {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage)) {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }
  
  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
  threshold = atof(argv[3]);

  // Call Method 1 Function
  method1(inputImage,chromaMask,threshold);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage)) {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }	

  // Call Method 2 Function
  method2(inputImage,chromaMask);


  // Produce the output by calling replace()
  replace(chromaMask,inputImage,bgrndImage,outputImage);


  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage)) {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }	

  return 0;
}



// Use user-provided threshold for chroma-key distance
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold)
{
  int sampleR = 0;
  int sampleG = 0;
  int sampleB = 0;
  for (int i = 0; i < 20; i ++)
  {
    sampleR = sampleR + inImage[i][i][0]; //take the top left corner
    sampleG = sampleG + inImage[i][i][1]; //using 2 for loops
    sampleB = sampleB + inImage[i][i][2];
  }
  sampleR = sampleR/20;
  sampleG = sampleG/20;
  sampleB = sampleB/20; // Taking the average

  for (int i = 0; i < 255 ; i ++)
  {
    for (int j = 0; j < 255; j ++)
    {
      for (int k = 0; k < 3; k ++)
      {
        if (k == 0) // now masking for RGB
        {
          if ((inImage[i][j][k] >= (sampleR - threshold))
          && (inImage[i][j][k] <= (sampleR + threshold)))
          {
            mask[i][k] = 0;
          }
          else
          {
            mask[i][j] = 1;
          }
        }
        if (k == 1)
        {
          if ((inImage[i][j][k] >= (sampleG - threshold))
          && (inImage[i][j][k] <= (sampleG + threshold)))
          {
            mask[i][k] = 0;
          }
          else
          {
            mask[i][j] = 1;
          }
        }
        if (k == 2)
        {
          if ((inImage[i][j][k] >= (sampleB - threshold))
          && (inImage[i][j][k] <= (sampleB + threshold)))
          {
            mask[i][k] = 0;
          }
          else
          {
            mask[i][j] = 1;
          }
        }
      }
    }
  }
}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE])  
{
  // take x=1,y=1,x=255 and y=255 (four lines on the background)
  // find the highest & the lowest, and the threshold is
  // (Hi-low)/2
  int sampleR = 0;
  int sampleG = 0;
  int sampleB = 0;
  int maxR = 0;
  int minR = 0;
  int maxG = 0;
  int minG = 0;
  int maxB = 0;
  int minB = 0; // temp values for calculation
  for (int i = 0; i < 20; i ++)
  {
    sampleR = sampleR + inImage[i][i][0]; //take the top left corner
    sampleG = sampleG + inImage[i][i][1];
    sampleB = sampleB + inImage[i][i][2];
    if (inImage[i][i][0] > maxR)
    {
      maxR = inImage[i][i][0];
    }
    if (inImage[i][i][0] < minR)
    {
      minR = inImage[i][i][0];
    }
    if (inImage[i][i][1] > maxG)
    {
      maxG = inImage[i][i][1];
    }
    if (inImage[i][i][1] < minG)
    {
      minG = inImage[i][i][1];
    }
    if (inImage[i][i][2] > maxB)
    {
      maxB = inImage[i][i][2];
    }
    if (inImage[i][i][2] < minB)
    {
      minB = inImage[i][i][2];
    }
  }
  sampleR = sampleR/20;
  sampleG = sampleG/20;
  sampleB = sampleB/20; // taking the average
  int largestDifferenceR = maxR - minR + 20; 
  // calculating the largest differences
  int largestDifferenceG = maxG - minG + 20; 
  // the differences brings out uncertainties in backgroud
  int largestDifferenceB = maxB - minB + 20; 
  // giving a 20 of extra range of 20

  for (int i = 0; i < 255 ; i ++)
  {
    for (int j = 0; j < 255; j ++)
    {
      for (int k = 0; k < 3; k ++)
      {
        if (k == 0)
        {
          if ((inImage[i][j][k] >= (sampleR - largestDifferenceR))
          && (inImage[i][j][k] <= (sampleR + largestDifferenceR)))
          {
            mask[i][k] = 0;
          }
          else
          {
            mask[i][j] = 1;
          }
        }
        if (k == 1)
        {
          if ((inImage[i][j][k] >= (sampleG - largestDifferenceG))
          && (inImage[i][j][k] <= (sampleG + largestDifferenceG)))
          {
            mask[i][k] = 0;
          }
          else
          {
            mask[i][j] = 1;
          }
        }
        if (k == 2)
        {
          if ((inImage[i][j][k] >= (sampleB - largestDifferenceB))
          && (inImage[i][j][k] <= (sampleB + largestDifferenceB)))
          {
            mask[i][k] = 0;
          }
          else
          {
            mask[i][j] = 1;
          }
        }
      }
    }
  }
}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image
  for (int i = 0; i < 255; i ++)
  {
    for (int j = 0; j < 255; j ++)
    {
      if (mask[i][j] == 0)
        // accoridng to the mask, do the operation
      {
        for (int k = 0; k < 3; k ++)
        {
          outImage[i][j][k] = bgImage[i][j][k];
        }
      }
      else
      {
        for (int k = 0; k < 3; k ++)
        {
          outImage[i][j][k] = inImage[i][j][k];
        }
      }
    }
  }

}
