#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
    double closest_t = std::numeric_limits<double>::infinity();
    bool is_valid = false;
    for (int i = 0; i < F.rows(); i++) {
        double curr_t;
        bool has_hit = ray_intersect_triangle(ray, V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)), min_t, max_t, curr_t);
        if (has_hit) {
            if (curr_t < closest_t) {
                closest_t = curr_t;
                hit_f = i;
                is_valid = true;
            }
        }
    }

    if (is_valid) {
        hit_t = closest_t;
        return true;
    }
    return false;
}
