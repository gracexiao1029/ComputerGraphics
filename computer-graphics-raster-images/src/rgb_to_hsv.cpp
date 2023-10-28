#include "rgb_to_hsv.h"
#include <algorithm>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double max = std::max(std::max(r, g), b);
  double min = std::min(std::min(r, g), b);
  double delta = max - min;

  if (delta == 0.0){
    h = 0.0;
  }
  else if (max == r){
    h = ((g - b) / delta) * 60.0;
  }
  else if (max == g){
    h = ((b - r) / delta + 2.0) * 60.0;
  }
  else if (max == b){
    h = ((r - g) / delta + 4.0) * 60.0;
  }
  
  if (max == 0.0){
    s = 0.0;
  }
  else if (max != 0.0){
    s = delta / max;
  }

  if (h < 0.0){
    h += 360.0;
  }
  v = max;
  ////////////////////////////////////////////////////////////////////////////
}
