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
bool Sphere::hit(const Ray &ray, float &t, ShadeInfo &s) const {
  double a = ray.d*(ray.d);
  double b = 2 * ray.d*(ray.o - c);
  double d = (ray.o - c)*(ray.o - c) - r * r;

  double discriminant = b * b - 4 * a * d;

  if (discriminant < 0) {
    return false;
  }

  double t0 = (-b - sqrt(discriminant)) / (2 * a);
  double t1 = (-b + sqrt(discriminant)) / (2 * a);

  if (t0 > t1) {
    std::swap(t0, t1);
  }
  // Checking first intersection
  if (t0 < kEpsilon) {
    t0 = t1;
    // Checking second intersection
    if (t0 < kEpsilon) {
      return false;
    }
  }

  t = t0;
  s.hit = true;
  s.hit_point = ray.o + t * ray.d;
  s.normal = (s.hit_point - c) / r;
  s.normal.normalize();
  s.ray = ray;
  s.t = t;
  s.material_ptr = material_ptr;

  return true;

}

// Get bounding box.
BBox Sphere::getBBox() const {
  Point3D minPoint(c.x - r, c.y - r, c.z - r);
  Point3D maxPoint(c.x + r, c.y + r, c.z + r);
  return BBox(minPoint, maxPoint);
}