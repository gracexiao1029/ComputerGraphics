#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
    double sqrt_d = 0;
    for (int i = 0; i < 3; i++) {
        sqrt_d += pow(fmax(fmax(box.min_corner[i] - query[i], 0), query[i] - box.max_corner[i]), 2);
    }
    return sqrt_d;
}
