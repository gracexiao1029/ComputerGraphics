#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    if (ray.direction.dot(normal) == 0) { // no intersection, line parallel to plane  
        return false;
    }
    double min_dist = (point - ray.origin).dot(normal) / (ray.direction.dot(normal));
    if (min_dist < min_t) {
        return false;
    }
    t = min_dist;
    n = normal;
    return true;
}

