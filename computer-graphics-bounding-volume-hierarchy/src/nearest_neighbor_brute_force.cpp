#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
    double min_dist = std::numeric_limits<double>::infinity();
    I = -1;
    for (int i = 0; i < points.rows(); i++) {
        double curr_dist = (points.row(i) - query).squaredNorm();
        if (curr_dist < min_dist) {
            min_dist = curr_dist;
            I = i;
        }
    }
    sqrD = min_dist;
}
