#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double c = v * s;
  double hp = h / 60.0;
  double x = c * (1.0 - fabs(fmod(hp, 2.0) - 1.0));
  double m = v - c;

  double rp, gp, bp;
  if (0.0 <= hp && hp < 1.0) {
      rp = c;
      gp = x;
      bp = 0.0;
  } else if (1.0 <= hp && hp < 2.0) {
      rp = x;
      gp = c;
      bp = 0.0;
  } else if (2.0 <= hp && hp < 3.0) {
      rp = 0.0;
      gp = c;
      bp = x;
  } else if (3.0 <= hp && hp < 4.0) {
      rp = 0.0;
      gp = x;
      bp = c;
  } else if (4.0 <= hp && hp < 5.0) {
      rp = x;
      gp = 0.0;
      bp = c;
  } else if (5.0 <= hp && hp < 6.0) {
      rp = c;
      gp = 0.0;
      bp = x;
  } else {
      rp = 0.0;
      gp = 0.0;
      bp = 0.0;
  }

  r = rp + m;
  g = gp + m;
  b = bp + m;
  ////////////////////////////////////////////////////////////////////////////
}
