#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      double r = (double)rgb[(i*width+j)*3];
      double g = (double)rgb[(i*width+j)*3+1];
      double b = (double)rgb[(i*width+j)*3+2];
      gray[i*width+j] = (unsigned char)(0.2126 * r + 0.7152 * g + 0.0722 * b);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

