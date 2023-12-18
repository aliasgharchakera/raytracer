#pragma once

/**
  This file declares the Tracer class which is an abstract class for all the
  tracers used.
*/

#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

class World;

class Tracer {
protected:
  World *world_ptr;

public:
  // Constructors.
  Tracer(World *world_ptr); // set world_ptr member.

  // Copy constuctor and assignment operator.
  Tracer(const Tracer &other) = default;
  Tracer &operator=(const Tracer &other) = default;

  // Desctructor.
  virtual ~Tracer() = default;

  // Trace ray.
  virtual RGBColor trace_ray(const Ray ray, const int depth) const = 0;
};