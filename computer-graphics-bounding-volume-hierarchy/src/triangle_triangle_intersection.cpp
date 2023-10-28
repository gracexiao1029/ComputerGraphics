#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
#include "Ray.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
    Ray ray_A0A1 = Ray(A0, A1 - A0);
    Ray ray_A1A2 = Ray(A1, A2 - A1);
    Ray ray_A2A0 = Ray(A2, A0 - A2);
    Ray ray_B0B1 = Ray(B0, B1 - B0);
    Ray ray_B1B2 = Ray(B1, B2 - B1);
    Ray ray_B2B0 = Ray(B2, B0 - B2);
    double t1, t2, t3, t4, t5, t6;

    if (ray_intersect_triangle(ray_A0A1, B0, B1, B2, 0.0, 1.0, t1) ||
        ray_intersect_triangle(ray_A1A2, B0, B1, B2, 0.0, 1.0, t2) ||
        ray_intersect_triangle(ray_A2A0, B0, B1, B2, 0.0, 1.0, t3) ||
        ray_intersect_triangle(ray_B0B1, A0, A1, A2, 0.0, 1.0, t4) ||
        ray_intersect_triangle(ray_B1B2, A0, A1, A2, 0.0, 1.0, t5) ||
        ray_intersect_triangle(ray_B2B0, A0, A1, A2, 0.0, 1.0, t6)) {
        return true;
    }
    return false;
}
