#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width * num_channels; j++){
      if (num_channels == 3){
        if (j % num_channels == 0){
          reflected[(i*width*num_channels+j)] = input[(i+1)*width*num_channels-j-3]; //r
          reflected[(i*width*num_channels+j+1)] = input[(i+1)*width*num_channels-j-2]; //g
          reflected[(i*width*num_channels+j+2)] = input[(i+1)*width*num_channels-j-1]; //b
        }
      }
      else if (num_channels == 1){
        reflected[(i*width*num_channels+j)] = input[(i+1)*width*num_channels-j-1]; //greyscale
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
