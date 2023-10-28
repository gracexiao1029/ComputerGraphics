#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int i = 0;
  for (int x = 0; x < height; x++){
    for (int y = 0; y < width; y++){
      int num_r = 0, num_g = 0, num_b = 0;
      double sum_r = 0, sum_g = 0, sum_b = 0;

      //iterate over a patch of size 9
      for (int offset1 = -1; offset1 < 2; offset1++){
        for (int offset2 = -1; offset2 < 2; offset2++){
          int px = x + offset1;
          int py = y + offset2;
          if (px >= 0 && px < height && py >= 0 && py < width){
            if(px % 2 == 0){
              if(py % 2 == 0){
                sum_g += bayer[px*width+py];
                num_g++;
              }
              else{
                sum_b += bayer[px*width+py];
                num_b++;
              }
            }
            else{
              if(py % 2 == 0){
                sum_r += bayer[px*width+py];
                num_r++;
              }
              else{
                sum_g += bayer[px*width+py];
                num_g++;
              }
            }
          }
        }
      }

      if (x % 2 == 0){
        if (y % 2 == 0){
          rgb[i++] = (unsigned char)(sum_r/num_r);
          rgb[i++] = bayer[x*width+y];
          rgb[i++] = (unsigned char)(sum_b/num_b);
        }
        else{
          rgb[i++] = (unsigned char)(sum_r/num_r);
          rgb[i++] = (unsigned char)(sum_g/num_g);
          rgb[i++] = bayer[x*width+y];
        }
      }
      else{
        if (y % 2 == 0){
          rgb[i++] = bayer[x*width+y];
          rgb[i++] = (unsigned char)(sum_g/num_g);
          rgb[i++] = (unsigned char)(sum_b/num_b);
        }
        else{
          rgb[i++] = (unsigned char)(sum_r/num_r);
          rgb[i++] = bayer[x*width+y];
          rgb[i++] = (unsigned char)(sum_b/num_b);
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
