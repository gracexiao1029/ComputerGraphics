#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
    std::list<std::pair<std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree>>> pairs_q;
    // if roots intersect
    if (box_box_intersect(rootA->box, rootB->box)) {
        pairs_q.push_back(std::make_pair(rootA, rootB));
    }

    while (!pairs_q.empty()) {
        std::pair<std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree>> front_pair = pairs_q.front();
        std::shared_ptr<AABBTree> curr_nodeA = front_pair.first;
        std::shared_ptr<AABBTree> curr_nodeB = front_pair.second;
        pairs_q.pop_front();
        
        if (curr_nodeA->num_leaves == 0 && curr_nodeB->num_leaves == 0) {
            leaf_pairs.push_back(std::make_pair(curr_nodeA, curr_nodeB));
        } else if (curr_nodeA->num_leaves < 3 && curr_nodeB->num_leaves < 3) {
            // node A left, node B left
            if (curr_nodeA->left && curr_nodeB->left) {
                std::shared_ptr<AABBTree> nodeA_left = std::static_pointer_cast<AABBTree>(curr_nodeA->left);
                std::shared_ptr<AABBTree> nodeB_left = std::static_pointer_cast<AABBTree>(curr_nodeB->left);
                leaf_pairs.push_back(std::make_pair(nodeA_left, nodeB_left));
            }
            // node A left, node B right
            if (curr_nodeA->left && curr_nodeB->right) {
                std::shared_ptr<AABBTree> nodeA_left = std::static_pointer_cast<AABBTree>(curr_nodeA->left);
                std::shared_ptr<AABBTree> nodeB_right = std::static_pointer_cast<AABBTree>(curr_nodeB->right);
                leaf_pairs.push_back(std::make_pair(nodeA_left, nodeB_right));
            }
            // node A right, node B left
            if (curr_nodeA->right && curr_nodeB->left) {
                std::shared_ptr<AABBTree> nodeA_right = std::static_pointer_cast<AABBTree>(curr_nodeA->right);
                std::shared_ptr<AABBTree> nodeB_left = std::static_pointer_cast<AABBTree>(curr_nodeB->left);
                leaf_pairs.push_back(std::make_pair(nodeA_right, nodeB_left));
            }
            // node A right, node B right
            if (curr_nodeA->right && curr_nodeB->right) {
                std::shared_ptr<AABBTree> nodeA_right = std::static_pointer_cast<AABBTree>(curr_nodeA->right);
                std::shared_ptr<AABBTree> nodeB_right = std::static_pointer_cast<AABBTree>(curr_nodeB->right);
                leaf_pairs.push_back(std::make_pair(nodeA_right, nodeB_right));
            }
        } else if (curr_nodeA->num_leaves < 3) {
            if (curr_nodeB->left && box_box_intersect(curr_nodeA->box, curr_nodeB->left->box)) {
                pairs_q.push_back(std::make_pair(curr_nodeA, std::static_pointer_cast<AABBTree>(curr_nodeB->left)));
            }
            if (curr_nodeB->right && box_box_intersect(curr_nodeA->box, curr_nodeB->right->box)) {
                pairs_q.push_back(std::make_pair(curr_nodeA, std::static_pointer_cast<AABBTree>(curr_nodeB->right)));
            }
        } else if (curr_nodeB->num_leaves < 3) {
            if (curr_nodeA->left && box_box_intersect(curr_nodeA->left->box, curr_nodeB->box)) {
                pairs_q.push_back(std::make_pair(std::static_pointer_cast<AABBTree>(curr_nodeA->left), curr_nodeB));
            }
            if (curr_nodeA->right && box_box_intersect(curr_nodeA->right->box, curr_nodeB->box)) {
                pairs_q.push_back(std::make_pair(std::static_pointer_cast<AABBTree>(curr_nodeA->right), curr_nodeB));
            }
        } else {
            // node A left, node B left
            if (curr_nodeA->left && curr_nodeB->left && box_box_intersect(curr_nodeA->left->box, curr_nodeB->left->box)) {
                std::shared_ptr<AABBTree> nodeA_left = std::static_pointer_cast<AABBTree>(curr_nodeA->left);
                std::shared_ptr<AABBTree> nodeB_left = std::static_pointer_cast<AABBTree>(curr_nodeB->left);
                pairs_q.push_back(std::make_pair(nodeA_left, nodeB_left));
            }
            // node A left, node B right
            if (curr_nodeA->left && curr_nodeB->right && box_box_intersect(curr_nodeA->left->box, curr_nodeB->right->box)) {
                std::shared_ptr<AABBTree> nodeA_left = std::static_pointer_cast<AABBTree>(curr_nodeA->left);
                std::shared_ptr<AABBTree> nodeB_right = std::static_pointer_cast<AABBTree>(curr_nodeB->right);
                pairs_q.push_back(std::make_pair(nodeA_left, nodeB_right));
            }
            // node A right, node B left
            if (curr_nodeA->right && curr_nodeB->left && box_box_intersect(curr_nodeA->right->box, curr_nodeB->left->box)) {
                std::shared_ptr<AABBTree> nodeA_right = std::static_pointer_cast<AABBTree>(curr_nodeA->right);
                std::shared_ptr<AABBTree> nodeB_left = std::static_pointer_cast<AABBTree>(curr_nodeB->left);
                pairs_q.push_back(std::make_pair(nodeA_right, nodeB_left));
            }
            // node A right, node B right
            if (curr_nodeA->right && curr_nodeB->right && box_box_intersect(curr_nodeA->right->box, curr_nodeB->right->box)) {
                std::shared_ptr<AABBTree> nodeA_right = std::static_pointer_cast<AABBTree>(curr_nodeA->right);
                std::shared_ptr<AABBTree> nodeB_right = std::static_pointer_cast<AABBTree>(curr_nodeB->right);
                pairs_q.push_back(std::make_pair(nodeA_right, nodeB_right));
            }
        }
    }
}
