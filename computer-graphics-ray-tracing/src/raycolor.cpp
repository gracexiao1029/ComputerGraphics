#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
    const Ray& ray,
    const double min_t,
    const std::vector< std::shared_ptr<Object> >& objects,
    const std::vector< std::shared_ptr<Light> >& lights,
    const int num_recursive_calls,
    Eigen::Vector3d& rgb)
{
    rgb = Eigen::Vector3d(0, 0, 0);
    if (num_recursive_calls > 3) {
        return false;
    }
    else {
        int l_hit_id;
        double l_t;
        Eigen::Vector3d l_n;
        bool has_intersection = first_hit(ray, min_t, objects, l_hit_id, l_t, l_n);
        if (has_intersection) { // if the ray intersects with an object
            // check ray reflection
            Ray reflected_ray;
            reflected_ray.origin = ray.origin + l_t * ray.direction;
            reflected_ray.direction = reflect(ray.direction, l_n);

            // shift reflected colors using a recursive call
            Eigen::Vector3d new_color;
            if (raycolor(reflected_ray, 1.0e-6, objects, lights, num_recursive_calls + 1, new_color)) {
                Eigen::Vector3d mirror_coef = objects[l_hit_id]->material->km;
                rgb += (mirror_coef.array() * new_color.array()).matrix();
            }

            // shade the shadow
            rgb += blinn_phong_shading(ray, l_hit_id, l_t, l_n, objects, lights);
            return true;
        }
        return false;
    }
}