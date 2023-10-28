#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
    // L = ka * Ia + sum[kd * Ii * max(0, n.li) + ks * Ii * max(0, n.hi)^p]
    const double i_a = 0.1;
    Eigen::Vector3d ambient = (objects[hit_id]->material->ka.array()) * i_a; // ka * Ia
    Eigen::Vector3d result = ambient;
    for (int i = 0; i < lights.size(); i++) {
        std::shared_ptr<Light> light = lights[i];
        Eigen::Vector3d l_d;
        double max_t;
        light->direction(ray.origin + t * ray.direction, l_d, max_t);
        Ray shadow_ray;
        shadow_ray.origin = ray.origin + t * ray.direction;
        shadow_ray.direction = l_d;

        int l_hit_id;
        double l_t;
        Eigen::Vector3d l_n;
        double min_t = 1.0e-6;
        bool has_intersection = first_hit(shadow_ray, min_t, objects, l_hit_id, l_t, l_n);
        if (!has_intersection || l_t >= max_t) {
            // h = (v + l)/(v + l).norm()
            Eigen::Vector3d h = (-ray.direction.normalized() + l_d.normalized()).normalized();
            Eigen::Vector3d diff_coef = objects[hit_id]->material->kd;
            Eigen::Vector3d spec_coef = objects[hit_id]->material->ks;
            Eigen::Vector3d Ii = light->I;
            double phong = objects[hit_id]->material->phong_exponent;

            result += ((diff_coef.array() * Ii.array()).matrix() * fmax(0, n.dot(l_d)) +
                (spec_coef.array() * Ii.array()).matrix() * pow(fmax(0, n.dot(h)), phong));
        }
    }
    return result;
}
