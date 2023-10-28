#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int i = 0;
  for (int col = width-1; col >= 0; col--){
    for (int row = 0; row < height; row++){
      if (num_channels == 3){
        rotated[i++] = input[(width*row+col)*num_channels]; //r
        rotated[i++] = input[(width*row+col)*num_channels+1]; //g
        rotated[i++] = input[(width*row+col)*num_channels+2]; //b
      }
      else if (num_channels == 1){
        rotated[i++] = input[(width*row+col)*num_channels];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
