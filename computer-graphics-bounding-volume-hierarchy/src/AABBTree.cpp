#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
    int N = objects.size();
    if (N == 0) {
        this->left = NULL;
        this->right = NULL;
    } else if (N == 1) {
        this->left = objects[0];
        this->right = NULL;
        insert_box_into_box(objects[0]->box, this->box);
    } else if (N == 2) {
        this->left = objects[0];
        this->right = objects[1];
        insert_box_into_box(objects[0]->box, this->box);
        insert_box_into_box(objects[1]->box, this->box);
    } else {
        for (int i = 0; i < N; i++) {
            insert_box_into_box(objects[i]->box, this->box);
        }

        // find the longest axis
        double axis_x = this->box.max_corner[0] - this->box.min_corner[0];
        double axis_y = this->box.max_corner[1] - this->box.min_corner[1];
        double axis_z = this->box.max_corner[2] - this->box.min_corner[2];
        double longest_axis = fmax(fmax(axis_x, axis_y), axis_z);

        double m; // midpoint
        int axis_i;
        if (longest_axis == axis_x) {
            m = this->box.center()[0];
            axis_i = 0;
        } else if (longest_axis == axis_y) {
            m = this->box.center()[1];
            axis_i = 1;
        } else {
            m = this->box.center()[2];
            axis_i = 2;
        }

        std::vector<std::shared_ptr<Object>> left_node;
        std::vector<std::shared_ptr<Object>> right_node;
        // for each object, split it to left/right node based on its position comparing to the midpoint
        for (int i = 0; i < N; i++) {
            if (objects[i]->box.center()[axis_i] < m) {
                left_node.push_back(objects[i]);
            } else if (objects[i]->box.center()[axis_i] > m) {
                right_node.push_back(objects[i]);
            } else {
                if (left_node.size() < right_node.size()) {
                    left_node.push_back(objects[i]);
                }
                else {
                    right_node.push_back(objects[i]);
                }
            }
        }

        // check for empty child
        if (left_node.size() == 0) {
            std::shared_ptr<Object> back_right_node = right_node.back();
            left_node.push_back(back_right_node);
            right_node.pop_back();
        }
        if (right_node.size() == 0) {
            std::shared_ptr<Object> back_left_node = left_node.back();
            right_node.push_back(back_left_node);
            left_node.pop_back();
        }

        // assign the child nodes
        this->left = std::make_shared<AABBTree>(left_node, a_depth + 1);
        this->right = std::make_shared<AABBTree>(right_node, a_depth + 1);
    }
}
