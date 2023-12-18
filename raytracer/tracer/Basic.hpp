#pragma once

/**
  This file declares the Basic class which is a tracer that uses the basic
  raytracing algorithm.
*/

#include "Tracer.hpp"

#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

class World;

class Basic : public Tracer {
public:
  // Constructors.
  Basic(World *world_ptr); // set world_ptr member.

  // Copy constuctor and assignment operator.
  Basic(const Basic &other) = default;
  
  Basic &operator=(const Basic &other) = default;

  // Desctructor.
  ~Basic() = default;

  // Trace ray.
  RGBColor trace_ray(const Ray ray, const int depth) const override;
};
