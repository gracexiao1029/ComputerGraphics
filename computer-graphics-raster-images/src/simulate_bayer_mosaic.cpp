#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int i = 0;
  for (int x = 0; x < height; x++){
      for (int y = 0; y < width; y++){
          if (x%2 == 0){
              if (y%2 == 0){
                  bayer[i] = rgb[(x*width+y)*3+1]; //g 
                  i++;
              }
              else{
                  bayer[i] = rgb[(x*width+y)*3+2]; //b
                  i++;
              }
          }
          else{
              if (y%2 == 0){
                  bayer[i] = rgb[(x*width+y)*3]; //r
                  i++;
              }
              else{
                  bayer[i] = rgb[(x*width+y)*3+1]; //g
                  i++;
              }
          }
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
