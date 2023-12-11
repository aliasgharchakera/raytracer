#include "Sphere.hpp"

// Constructors.
Sphere::Sphere() : c(0, 0, 0), r(1) {}

Sphere::Sphere(const Point3D &center, float radius) : c(center), r(radius) {}

// Copy constructor and assignment operator.
Sphere::Sphere(const Sphere &object) : c(object.c), r(object.r) {}

Sphere &Sphere::operator=(const Sphere &rhs) {
  if (this == &rhs) {
    return *this;
  }

  c = rhs.c;
  r = rhs.r;

  return *this;
}

// String representation.
std::string Sphere::to_string() const {
  std::ostringstream oss;
  oss << "Sphere(" << c.to_string() << ", " << r << ")";
  return oss.str();
}

// TODO: Implement this function.
bool Sphere::hit(const Ray &ray, float &tmin, ShadeInfo &sinfo) const {}

// TODO: Implement this function.
BBox Sphere::getBBox() const {}