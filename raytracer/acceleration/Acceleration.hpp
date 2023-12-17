#pragma once

#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

class World;

class Acceleration {
 protected:
  World* world;

 public:
  // Constructor
  explicit Acceleration(World* _world);

  Acceleration() = default;

  // Remove copy constructor
  Acceleration(const Acceleration& rhs) = delete;

  // Destructor
  virtual ~Acceleration() = default;

  // Calculates what object a Ray hits
  virtual ShadeInfo hit_objects(const Ray& ray) = 0;

};
