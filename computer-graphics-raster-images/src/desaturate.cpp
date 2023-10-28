#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
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
      s *= (1.0 - factor);
      hsv_to_rgb(h, s, v, r, g, b);
      desaturated[j++] = (unsigned char)(r * 255.0);
      desaturated[j++] = (unsigned char)(g * 255.0);
      desaturated[j++] = (unsigned char)(b * 255.0);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
