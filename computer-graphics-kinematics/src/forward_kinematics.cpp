#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d>> & T)
{
    // recursive function
    std::function<Eigen::Affine3d(const Skeleton&, int)> calculate_transformation = [&](const Skeleton& skeleton, int i) {
        if (skeleton[i].parent_index == -1) {
            return Eigen::Affine3d::Identity();
        }

        Eigen::Affine3d T_pi = calculate_transformation(skeleton, skeleton[i].parent_index);
        Eigen::Affine3d T_res = skeleton[i].rest_T;
        Eigen::Affine3d R_i = euler_angles_to_transform(skeleton[i].xzx);
        return T_pi * T_res * R_i * T_res.inverse();
    };

    T.resize(skeleton.size(), Eigen::Affine3d::Identity());
    for (int i = 1; i < skeleton.size(); i++) {
        T[i] = calculate_transformation(skeleton, i);
    }
}
