#include "KDTree.hpp"
#include <stack>

#include "../utilities/BBox.hpp"

KDTree::KDTree(World* world)
    : world_ptr{world}, root_node{new KDNode(world->geometry)} {
  KDNode::build_kd_tree(root_node);
}

KDTree::~KDTree() { delete root_node; }

ShadeInfo KDTree::hit_objects(const Ray& ray) {
  float t;
  ShadeInfo sinfomin(*world_ptr);
  ShadeInfo sinfocur(*world_ptr);

  std::stack<KDNode*> frontier;
  frontier.push(root_node);

  KDNode* current = frontier.top();

  while (!frontier.empty()) {
    current = frontier.top();
    frontier.pop();

    if (current->bb.hit(ray)) {
      if (current->left == nullptr && current->right == nullptr) {
        for (auto g : current->primitives) {
          if (g->hit(ray, t, sinfocur) && (t < sinfomin.t)) {
            sinfomin = sinfocur;
          }
        }
      } else {
        frontier.push(current->left);
        frontier.push(current->right);
      }
    }
  }
}