#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
    double x_e = ray.origin[0];
    double y_e = ray.origin[1];
    double z_e = ray.origin[2];
    double x_d = ray.direction[0];
    double y_d = ray.direction[1];
    double z_d = ray.direction[2];
    double a_x = 1 / x_d;
    double a_y = 1 / y_d;
    double a_z = 1 / z_d;
    double x_min = box.min_corner[0];
    double y_min = box.min_corner[1];
    double z_min = box.min_corner[2];
    double x_max = box.max_corner[0];
    double y_max = box.max_corner[1];
    double z_max = box.max_corner[2];
    double t_xmin, t_xmax, t_ymin, t_ymax, t_zmin, t_zmax;

    if (a_x >= 0) {
        t_xmin = a_x * (x_min - x_e);
        t_xmax = a_x * (x_max - x_e);
    } else {
        t_xmin = a_x * (x_max - x_e);
        t_xmax = a_x * (x_min - x_e);
    }
    if (a_y >= 0) {
        t_ymin = a_y * (y_min - y_e);
        t_ymax = a_y * (y_max - y_e);
    }
    else {
        t_ymin = a_y * (y_max - y_e);
        t_ymax = a_y * (y_min - y_e);
    }
    if (a_z >= 0) {
        t_zmin = a_z * (z_min - z_e);
        t_zmax = a_z * (z_max - z_e);
    }
    else {
        t_zmin = a_z * (z_max - z_e);
        t_zmax = a_z * (z_min - z_e);
    }

    if (t_xmin > t_ymax || t_ymin > t_xmax || t_xmin > t_zmax || t_zmin > t_xmax || t_ymin > t_zmax || t_zmin > t_ymax) {
        return false;
    }

    double t_min = fmax(fmax(t_xmin, t_ymin), t_zmin);
    double t_max = fmin(fmin(t_xmax, t_ymax), t_zmax);
    if (t_max < min_t || t_min > max_t) {
        return false;
    }
    return true;
}
