#include "Perspective.hpp"

// Constructors.
Perspective::Perspective() : pos(0, 0, 0) {}

Perspective::Perspective(float c) : pos(c, c, c) {}

Perspective::Perspective(float x, float y, float z) : pos(x, y, z) {}

Perspective::Perspective(const Point3D &pt) : pos(pt) {}

// Copy constuctor and assignment operator.
Perspective::Perspective(const Perspective &camera) : pos(camera.pos) {}

Perspective &Perspective::operator=(const Perspective &other) {
  if (this == &other) {
    return *this;
  }

  pos = other.pos;

  return *this;
}

// REVIEW: review this function
Vector3D Perspective::get_direction(const Point3D &p) const {
    Vector3D v = p - pos;
    v.normalize();
    return v;
}