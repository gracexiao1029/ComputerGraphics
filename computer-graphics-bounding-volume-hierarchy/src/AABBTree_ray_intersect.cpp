#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
    // ray hits root box
    if (ray_intersect_box(ray, this->box, min_t, max_t)) {
        std::shared_ptr<Object> left_subtree;
        std::shared_ptr<Object> right_subtree;
        double left_t, right_t;
        bool has_left_hit = false;
        bool has_right_hit = false;

        if (this->left != NULL) {
            if (this->left->ray_intersect(ray, min_t, max_t, left_t, left_subtree)) {
                has_left_hit = true;
                // if no left subtree, use the current left node instead
                if (left_subtree == NULL) {
                    left_subtree = this->left;
                }
            }
        }
        if (this->right != NULL) {
            if (this->right->ray_intersect(ray, min_t, max_t, right_t, right_subtree)) {
                has_right_hit = true;
                // if no right subtree, use the current right node instead
                if (right_subtree == NULL) {
                    right_subtree = this->right;
                }
            }
        }

        // if intersections return from both subtrees, find the closest one
        if (has_left_hit && has_right_hit) {
            if (left_t < right_t) {
                t = left_t;
                descendant = left_subtree;
            } else {
                t = right_t;
                descendant = right_subtree;
            }
            return true;
        } else if (has_left_hit) {
            t = left_t;
            descendant = left_subtree;
            return true;
        } else if (has_right_hit) {
            t = right_t;
            descendant = right_subtree;
            return true;
        } else { // no intersection
            return false;
        }
    }
    return false;
}

