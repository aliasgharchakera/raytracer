#include "Parallel.hpp"

// Constructors.
Parallel::Parallel() : dir(0, 0, -1) {}

Parallel::Parallel(float c) : dir(c, c, c) {}

Parallel::Parallel(float x, float y, float z) : dir(x, y, z) {}

Parallel::Parallel(const Vector3D &d) : dir(d) {}

// Copy constuctor and assignment operator.
Parallel::Parallel(const Parallel &camera) : dir(camera.dir) {}

Parallel &Parallel::operator=(const Parallel &other) {
  if (this == &other) {
    return *this;
  }

  dir = other.dir;

  return *this;
}

// TODO: Implement this function.
Vector3D Parallel::get_direction(const Point3D &p) const { return dir; }