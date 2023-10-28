#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    Eigen::Vector3d A = std::get<0>(corners);
    Eigen::Vector3d B = std::get<1>(corners);
    Eigen::Vector3d C = std::get<2>(corners);
    Eigen::Vector3d D = ray.direction;
    Eigen::Vector3d E = ray.origin;
    Eigen::Vector3d AB = B - A;
    Eigen::Vector3d AC = C - A;

    double a = A[0] - B[0];
    double b = A[1] - B[1];
    double c = A[2] - B[2];
    double d = A[0] - C[0];
    double e = A[1] - C[1];
    double f = A[2] - C[2];
    double g = D[0];
    double h = D[1];
    double i = D[2];
    double j = A[0] - E[0];
    double k = A[1] - E[1];
    double l = A[2] - E[2];

    double M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
    double curr_t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
    if (curr_t < min_t) {
        return false;
    }
    double gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
    if (gamma < 0 || gamma > 1) {
        return false;
    }
    double beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;
    if (beta < 0 || beta > 1 - gamma) {
        return false;
    }
    t = curr_t;
    n = (AB.cross(AC)).normalized();
    return true;
}


