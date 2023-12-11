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

// Ray intersection. Set t and sinfo as per intersection with this object.
// REVIEW: Idk if this is correct.
bool Sphere::hit(const Ray &ray, float &t, ShadeInfo &sinfo) const {
  Vector3D oc = ray.o - c;
  double a = ray.d * ray.d;
  double b = 2.0 * oc * ray.d;
  double c = oc * oc - r * r;
  double discriminant = b * b - 4 * a * c;

  if (discriminant > 0) {
    double curr_t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (curr_t > kEpsilon) {
      t = curr_t;
      sinfo.hit_point = ray.o + curr_t * ray.d;
      sinfo.normal = (oc + curr_t * ray.d) / r;
      return true;
    }

    curr_t = (-b + sqrt(discriminant)) / (2.0 * a);
    if (curr_t > kEpsilon) {
      t = curr_t;
      sinfo.hit_point = ray.o + curr_t * ray.d;
      sinfo.normal = (oc + curr_t * ray.d) / r;
      return true;
    }
  }

  return false;
}

// Get bounding box.
BBox Sphere::getBBox() const {
  Point3D minPoint(c.x - r, c.y - r, c.z - r);
  Point3D maxPoint(c.x + r, c.y + r, c.z + r);
  return BBox(minPoint, maxPoint);
}