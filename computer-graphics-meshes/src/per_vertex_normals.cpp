#include "per_vertex_normals.h"
#include "triangle_area_normal.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  
  // for all vertices, compute the vertex normal
  for (int i = 0; i < V.rows(); i++) {
      Eigen::RowVector3d total_normal(0, 0, 0);
      for (int j = 0; j < F.rows(); j++) {
          // check if face is the neighbour of vertex (the vertex is one of the corners of face)
          if (F.row(j)[0] == i || F.row(j)[1] == i || F.row(j)[2] == i) {
              Eigen::RowVector3d a = V.row(F(j, 0));
              Eigen::RowVector3d b = V.row(F(j, 1));
              Eigen::RowVector3d c = V.row(F(j, 2));
              total_normal += triangle_area_normal(a, b, c).normalized();
          }
      }
      // take the weighted average of all neighbouring normals
      N.row(i) = total_normal.normalized();
  }
}
