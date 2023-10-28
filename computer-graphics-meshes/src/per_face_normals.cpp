#include "per_face_normals.h"
#include "triangle_area_normal.h"

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
    N = Eigen::MatrixXd::Zero(F.rows(), 3);
    // loop through all faces, assign each corner the normal of the face normal
    for (int i = 0; i < F.rows(); i++) {
        Eigen::RowVector3d a = V.row(F(i, 0));
        Eigen::RowVector3d b = V.row(F(i, 1));
        Eigen::RowVector3d c = V.row(F(i, 2));
        N.row(i) = triangle_area_normal(a, b, c).normalized();
    }
}
