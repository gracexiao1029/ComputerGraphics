#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
    J = Eigen::MatrixXd::Zero(b.size() * 3, skeleton.size() * 3);
    Eigen::VectorXd tips = transformed_tips(skeleton, b);
    const double epsilon = 1.0e-7;

    for (int i = 0; i < skeleton.size(); i++) {
        for (int j = 0; j < 3; j++) {
            Skeleton copy_s = skeleton;
            copy_s[i].xzx[j] += epsilon;
            Eigen::VectorXd copy_tips = transformed_tips(copy_s, b);

            for (int k = 0; k < J.rows(); k++) {
                J(k, i * 3 + j) = (copy_tips - tips)[k] / epsilon;
            }
        }
    }
}
