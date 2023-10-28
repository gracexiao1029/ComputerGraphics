#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include "point_box_squared_distance.h"

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{


    // reference: https://www.mygreatlearning.com/blog/priority-queue-in-cpp/#:~:text=Conclusion-,What%20is%20a%20Priority%20Queue%20in%20C%2B%2B%3F,elements%20are%20in%20decreasing%20order
    
    // implement a min-heap based on the pairs
    std::priority_queue<std::pair<double, std::shared_ptr<AABBTree>>, std::vector<std::pair<double, std::shared_ptr<AABBTree>>>, std::greater<std::pair<double, std::shared_ptr<AABBTree>>>> q;
    double min_dist = std::numeric_limits<double>::infinity();
    double root_sqrd = point_box_squared_distance(query, root->box);
    bool is_found = false;
    q.push(std::make_pair(root_sqrd, root));

    while (!q.empty()) {
        std::pair<double, std::shared_ptr<AABBTree>> top_pair = q.top();
        double curr_dist = top_pair.first;
        std::shared_ptr<AABBTree> curr_node = top_pair.second;
        q.pop();
        
        if (curr_dist < min_dist) {
            if (curr_node->num_leaves == 0) {
                double curr_sqrd;
                std::shared_ptr<Object> curr_desc;
                if (curr_node->point_squared_distance(query, min_sqrd, max_sqrd, curr_sqrd, curr_desc)) {
                    if (curr_sqrd < min_dist) {
                        min_dist = curr_sqrd;
                        descendant = curr_node;
                        is_found = true;
                    }
                }
            } else if (curr_node->num_leaves < 3) {
                double left_sqrd;
                double right_sqrd;
                std::shared_ptr<Object> left_desc;
                std::shared_ptr<Object> right_desc;
                bool left_sqrd_valid = curr_node->left && curr_node->left->point_squared_distance(query, min_sqrd, max_sqrd, left_sqrd, left_desc) && left_sqrd < min_dist;
                bool right_sqrd_valid = curr_node->right && curr_node->right->point_squared_distance(query, min_sqrd, max_sqrd, right_sqrd, right_desc) && right_sqrd < min_dist;
                
                if (left_sqrd_valid && right_sqrd_valid) { // if has two valid children, find the min child
                    if (left_sqrd < right_sqrd) {
                        min_dist = left_sqrd;
                        descendant = curr_node->left;
                        is_found = true;
                    } else {
                        min_dist = right_sqrd;
                        descendant = curr_node->right;
                        is_found = true;
                    }
                } else if (left_sqrd_valid) { // if only left child is valid
                    min_dist = left_sqrd;
                    descendant = curr_node->left;
                    is_found = true;
                } else if (right_sqrd_valid) { // if only right child is valid
                    min_dist = right_sqrd;
                    descendant = curr_node->right;
                    is_found = true;
                }
            } else {
                if (curr_node->left) {
                    double left_sqrd = point_box_squared_distance(query, curr_node->left->box);
                    q.push(std::make_pair(left_sqrd, std::static_pointer_cast<AABBTree>(curr_node->left)));
                }
                if (curr_node->right) {
                    double right_sqrd = point_box_squared_distance(query, curr_node->right->box);
                    q.push(std::make_pair(right_sqrd, std::static_pointer_cast<AABBTree>(curr_node->right)));
                }
            }
        }
    }

    sqrd = min_dist;
    if (is_found) {
        return true;
    }
    return false;
}
