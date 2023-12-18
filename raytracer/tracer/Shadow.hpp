#pragma once

/**
  This file declares the Shadow class which is a tracer that uses the basic
  raytracing algorithm.
*/

#include "Tracer.hpp"

#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

class World;

class Shadow : public Tracer {
public:
  // Constructors.
  Shadow(World *world_ptr); // set world_ptr member.

  // Copy constuctor and assignment operator.
  Shadow(const Shadow &other) = default;
  
  Shadow &operator=(const Shadow &other) = default;

  // Desctructor.
  ~Shadow() = default;

  // Trace ray.
  RGBColor trace_ray(const Ray ray, const int depth) const override;
};
