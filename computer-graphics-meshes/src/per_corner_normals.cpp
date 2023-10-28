#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);

  std::vector<std::vector<int>> VF;
  int num_vertices = V.rows();
  vertex_triangle_adjacency(F, num_vertices, VF);
  for (int i = 0; i < F.rows(); i++) {
      Eigen::RowVector3d x = V.row(F(i, 0));
      Eigen::RowVector3d y = V.row(F(i, 1));
      Eigen::RowVector3d z = V.row(F(i, 2));
      Eigen::RowVector3d face_normal = triangle_area_normal(x, y, z).normalized();
      for (int j = 0; j < F.cols(); j++) {
          Eigen::RowVector3d total_normal(0, 0, 0);
          for (int k = 0; k < VF[F(i, j)].size(); k++) {
              Eigen::RowVector3d a = V.row(F(VF[F(i, j)][k], 0));
              Eigen::RowVector3d b = V.row(F(VF[F(i, j)][k], 1));
              Eigen::RowVector3d c = V.row(F(VF[F(i, j)][k], 2));
              Eigen::RowVector3d curr_normal = triangle_area_normal(a, b, c).normalized();

              if (face_normal.dot(curr_normal) > cos(corner_threshold * M_PI / 180)) {
                  total_normal += curr_normal;
              }
          }
          // take the weighted average of all satisfied normals
          N.row(i * 3 + j) = total_normal.normalized();
      }
  }
}
