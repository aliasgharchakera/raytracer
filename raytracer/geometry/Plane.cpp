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

// FIXME: Somewhat corrected but still not working correctly
bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const {
  float denom = ray.d*(n);

  // Check if the ray is parallel to the plane.
  if (denom == 0) {
    return false;
  }

  float t_hit = (a - ray.o)*(n) / denom;

  // Check if the intersection is behind the ray origin or beyond the current hit point.
  if (t_hit < kEpsilon || t_hit >= t) {
    return false;
  }

  // Update the hit information.
  t = t_hit;
  s.hit_point = ray.o + t_hit * ray.d;
  s.normal = n;
  s.material_ptr = material_ptr;

  return true;
}

BBox Plane::getBBox() const {
  return BBox();
}