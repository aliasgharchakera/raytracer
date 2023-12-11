#include "Ray.hpp"

// Constructors.
// REVIEW: Should we set origin and dir to (0, 0, 0) and w to 1?
Ray::Ray() : o(Point3D()), d((0.0, 0.0, 1.0)), w(1) {}

Ray::Ray(const Point3D &origin, const Vector3D &dir) : o(origin), d(dir), w(1) {}

// String representation.
std::string Ray::to_string() const {
  return "Ray(" + o.to_string() + ", " + d.to_string() + ", " + std::to_string(w) + ")";
}