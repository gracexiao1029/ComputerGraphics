#include "copy_skeleton_at.h"
Skeleton copy_skeleton_at(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{
    Skeleton s_copy = skeleton;
    for (int i = 0; i < skeleton.size(); i++) {
        s_copy[i].xzx(0) = A[3 * i];
        s_copy[i].xzx(1) = A[3 * i + 1];
        s_copy[i].xzx(2) = A[3 * i + 2];
    }
    return s_copy;
}
