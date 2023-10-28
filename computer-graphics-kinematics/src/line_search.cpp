#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
    double sigma = max_step;
    Eigen::VectorXd curr_z = z - sigma * dz;
    proj_z(curr_z);

    for (int i = max_step / 2; i > 0; i /= 2) {
        if (f(curr_z) < f(z)) {
            break;
        }
        sigma = i;
        curr_z = z - sigma * dz;
        proj_z(curr_z);
    }

    return sigma;
}
