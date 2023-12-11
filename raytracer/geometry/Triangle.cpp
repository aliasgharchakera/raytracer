#include "Triangle.hpp"

// Constructors.
Triangle::Triangle() : v0(Point3D()), v1(Point3D()), v2(Point3D()) {}

Triangle::Triangle(const Point3D &p0, const Point3D &p1, const Point3D &p2)
    : v0(p0), v1(p1), v2(p2) {}

// Copy constructor and assignment operator.
Triangle::Triangle(const Triangle &object)
    : Geometry(object), v0(object.v0), v1(object.v1), v2(object.v2) {}

Triangle &Triangle::operator=(const Triangle &rhs) {
  if (this == &rhs) {
    return *this;
  }

  Geometry::operator=(rhs);
  v0 = rhs.v0;
  v1 = rhs.v1;
  v2 = rhs.v2;

  return *this;
}

// String representation.
std::string Triangle::to_string() const {
  return "Triangle";
}

// TODO: Implement ray-triangle intersection algorithm
bool Triangle::hit(const Ray &ray, float &t, ShadeInfo &s) const {
  
}

BBox Triangle::getBBox() const {
  return BBox(min(min(v0, v1), v2), max(max(v0,v1), v2))
}
