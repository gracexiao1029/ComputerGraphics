#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
    double Ax_min = A.min_corner[0];
    double Ay_min = A.min_corner[1];
    double Az_min = A.min_corner[2];
    double Ax_max = A.max_corner[0];
    double Ay_max = A.max_corner[1];
    double Az_max = A.max_corner[2];
    double Bx_min = B.min_corner[0];
    double By_min = B.min_corner[1];
    double Bz_min = B.min_corner[2];
    double Bx_max = B.max_corner[0];
    double By_max = B.max_corner[1];
    double Bz_max = B.max_corner[2];

    if (Ax_min > Bx_max || Ay_min > By_max || Az_min > Bz_max || Bx_min > Ax_max || By_min > Ay_max || Bz_min > Az_max) {
        return false;
    }
    return true;
}

