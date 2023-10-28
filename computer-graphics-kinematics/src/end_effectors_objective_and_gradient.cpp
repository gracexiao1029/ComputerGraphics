#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
    f = [&](const Eigen::VectorXd& A)->double
    {
        // f(xb) = norm(xb - xb0)^2
        Skeleton copy_s = copy_skeleton_at(skeleton, A);
        Eigen::VectorXd xb = transformed_tips(copy_s, b);
        return 0.5 * (xb - xb0).squaredNorm();
    };

    grad_f = [&](const Eigen::VectorXd& A)->Eigen::VectorXd
    {
        Eigen::VectorXd grad = Eigen::VectorXd::Zero(A.size());
        // grad = (dx(a)/d(a)).transpose * (xb - xb0)
        Skeleton copy_s = copy_skeleton_at(skeleton, A);
        Eigen::VectorXd xb = transformed_tips(copy_s, b);
        Eigen::MatrixXd J;
        kinematics_jacobian(copy_s, b, J);
        grad = J.transpose() * (xb - xb0);
        return grad;
    };

    proj_z = [&](Eigen::VectorXd& A)
    {
        for (int i = 0; i < skeleton.size(); i++) {
            for (int j = 0; j < 3; j++) {
                A[3 * i + j] = std::max(skeleton[i].xzx_min[j], std::min(skeleton[i].xzx_max[j], A[3 * i + j]));
            }
        }
        assert(skeleton.size() * 3 == A.size());
    };
}
