#pragma once

#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
#include "Acceleration.hpp"
#include "KDNode.hpp"

class KDTree : public Acceleration {
 protected:
  World* world_ptr;
  KDNode* root_node;

 public:
  // Constructor
  explicit KDTree(World* world);

  KDTree() = delete;

  // Copy constructor
  KDTree(const KDTree& rhs) = delete;

  // Destructor
  virtual ~KDTree();

  // Calculates what object a Ray hits
  virtual ShadeInfo hit_objects(const Ray& ray);
};
