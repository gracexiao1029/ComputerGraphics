#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);

  for (int i = 0; i < num_vertices; i++) {
      for (int j = 0; j < F.rows(); j++) {
          if (F.row(j)[0] == i || F.row(j)[1] == i || F.row(j)[2] == i) {
              VF[i].push_back(j);
          }
      }
  }
}

