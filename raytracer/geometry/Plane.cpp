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


bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const {
  
  float t_point = (a - ray.o) * n / (ray.d * n);

  if (t_point > kEpsilon) {
    t = t_point;
    s.normal = n;
    s.normal.normalize();
    s.hit_point = ray.o + t * ray.d;
    s.ray = ray;
    s.t = t_point;
    return true;
  }

  return false;

}

BBox Plane::getBBox() const {
  return BBox();
}