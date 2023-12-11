#pragma once

#include "Plane.hpp"

// Constructors.
Plane::Plane() : a(0, 0, 0), n(0, 1, 0) {}

Plane::Plane(const Point3D &pt, const Vector3D &n) : a(pt), n(n) {
  this->n.normalize();
}

// Copy constructor and assignment operator.
Plane::Plane(const Plane &object) : a(object.a), n(object.n) {}

Plane &Plane::operator=(const Plane &rhs) {
  if (this == &rhs) {
    return *this;
  }

  a = rhs.a;
  n = rhs.n;

  return *this;
}

// String representation.

std::string Plane::to_string() const {
  std::ostringstream oss;
  oss << "Plane(" << a.to_string() << ", " << n.to_string() << ")";
  return oss.str();
}

// TODO: Implement this function.
bool Plane::hit(const Ray &ray, float &tmin, ShadeInfo &sinfo) const {}

// TODO: Implement this function.
BBox Plane::getBBox() const {}