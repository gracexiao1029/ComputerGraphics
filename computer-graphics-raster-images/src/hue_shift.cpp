#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int i = 0;
  int j = 0;
  for (int x = 0; x < height; x++){
    for (int y = 0; y < width; y++){
      double r = (double)(rgb[i++]) / 255.0;
      double g = (double)(rgb[i++]) / 255.0;
      double b = (double)(rgb[i++]) / 255.0;
      double h, s, v;
      rgb_to_hsv(r, g, b, h, s, v);
      h += shift;
      while (h < 0){
        h += 360.0;
      }
      h = fmod(h, 360.0);
      hsv_to_rgb(h, s, v, r, g, b);
      shifted[j++] = (unsigned char)(r * 255.0);
      shifted[j++] = (unsigned char)(g * 255.0);
      shifted[j++] = (unsigned char)(b * 255.0);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
