#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    Eigen::Vector3d d = ray.direction;
    Eigen::Vector3d e = ray.origin;
    Eigen::Vector3d c = center;
    double r = radius;

    // check discriminant
    double disc = d.dot(e - c) * d.dot(e - c) - d.dot(d) * ((e - c).dot(e - c) - r * r);
    if (disc < 0) { // no roots
        return false;
    } else if (disc == 0) { // 1 intersection
        double min_dist = (-d.dot(e - c)) / (d.dot(d));
        if (min_dist < min_t) {
            return false;
        }
        t = min_dist;
        Eigen::Vector3d p = e + t * d;
        n = (p - c) / r;
        return true;
    } else { // 2 intersections
        double min_dist1 = (-d.dot(e - c) + sqrt(disc)) / (d.dot(d));
        double min_dist2 = (-d.dot(e - c) - sqrt(disc)) / (d.dot(d));
        if (min_dist1 < min_t && min_dist2 < min_t) {
            return false;
        } else if (min_dist1 < min_t) {
            t = min_dist2;
        } else if (min_dist2 < min_t) {
            t = min_dist1;
        } else {
            t = fmin(min_dist1, min_dist2);
        }
        Eigen::Vector3d p = e + t * d;
        n = (p - c) / r;
        return true;
    }
}