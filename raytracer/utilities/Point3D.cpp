#include "Point3D.hpp"

// Constructors.
Point3D::Point3D() : x(0), y(0), z(0) {}

Point3D::Point3D(float c) : x(c), y(c), z(c) {}

Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

// String representation.
std::string Point3D::to_string() const {
  return "Point3D(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// Arithmetic.
Point3D Point3D::operator-() const { return Point3D(-x, -y, -z); }

Vector3D Point3D::operator-(const Point3D &p) const { return Vector3D(x - p.x, y - p.y, z - p.z); }

Point3D Point3D::operator+(const Vector3D &v) const { return Point3D(x + v.x, y + v.y, z + v.z); }

Point3D Point3D::operator-(const Vector3D &v) const { return Point3D(x - v.x, y - v.y, z - v.z); }

Point3D Point3D::operator*(const float s) const { return Point3D(x * s, y * s, z * s); }

bool Point3D::operator==(const Point3D &p) const { return (x == p.x && y == p.y && z == p.z); }

float Point3D::operator[](int idx) const {
  if (idx == 0) {
    return x;
  } else if (idx == 1) {
    return y;
  } else {
    return z;
  }
}

// Distance between points.
float Point3D::d_squared(const Point3D &p) const {
  return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z);
}

float Point3D::distance(const Point3D &p) const { return sqrt(d_squared(p)); }

Point3D Point3D::interpolate(const Point3D& a, const Point3D& b,
                             const Point3D& c, const Point3D& x,
                             const Point3D& y) {
  return Point3D(x.x + (c.x - a.x) / (b.x - a.x) * (y.x - x.x),
                 x.y + (c.y - a.y) / (b.y - a.y) * (y.y - x.y),
                 x.z + (c.z - a.z) / (b.z - a.z) * (y.z - x.z));
}

// Scale pt by a factor, s.
Point3D operator*(const float a, const Point3D &pt) { return Point3D(a * pt.x, a * pt.y, a * pt.z); }

// Compare points.
Point3D min(const Point3D& a, const Point3D& b) {
  return Point3D(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point3D max(const Point3D& a, const Point3D& b) {
  return Point3D(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}