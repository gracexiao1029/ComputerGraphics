#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
    Eigen::VectorXd result = Eigen::VectorXd::Zero(3 * b.size());

    // find transformation matrices
    std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d>> T;
    forward_kinematics(skeleton, T);

    for (int i = 0; i < b.size(); i++) {
        // bone transformation
        Eigen::Affine3d T_b = T[b[i]];
        Eigen::Affine3d T_res = skeleton[b[i]].rest_T;
        Eigen::Vector4d composed_vec = T_b * T_res * Eigen::Vector4d(skeleton[b[i]].length, 0, 0, 1);
        for (int j = 0; j < 3; j++) {
            result[i * 3 + j] = composed_vec[j];
        }
    }
    return result;
}
