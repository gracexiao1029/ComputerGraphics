#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
    double min_dist = std::numeric_limits<double>::infinity();
    bool hasHit = false;

    for (int i = 0; i < objects.size(); i++) {
        double curr_t;
        Eigen::Vector3d curr_n;
        if (objects[i]->intersect(ray, min_t, curr_t, curr_n)) { // found intersection
            hasHit = true;
            // distance comparison
            if (min_dist > curr_t) {
                min_dist = curr_t;
                hit_id = i;
                n = curr_n;
            }
        }
    }
    
    if (!hasHit) {
        return false;
    }
    t = min_dist;
    return true;
}

