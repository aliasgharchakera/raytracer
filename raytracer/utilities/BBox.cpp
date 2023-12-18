#include "BBox.hpp"

// FIXME: Implement this class.
// Constructors.
// BBox::BBox() : pmin(Point3D()), pmax(Point3D()) {}

BBox::BBox(const Point3D& min, const Point3D& max) : pmin(min), pmax(max), delta(pmax-pmin) {}

// Copy constructor and assignment operator.
// BBox::BBox(const BBox &b) : pmin(b.pmin), pmax(b.pmax) {}

// BBox &BBox::operator=(const BBox &rhs) {
//   if (this == &rhs) {
//     return *this;
//   }

//   pmin = rhs.pmin;
//   pmax = rhs.pmax;

//   return *this;
// }

// String representation.
std::string BBox::to_string() const {
  std::ostringstream oss;
  oss << "BBox(" << pmin.to_string() << ", " << pmax.to_string() << ")";
  return oss.str();
}

// Does ray hit bbox? If so, set entering and leaving t values for ray.
bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const {
  float tmin = (pmin.x - ray.o.x) / ray.d.x;
  float tmax = (pmax.x - ray.o.x) / ray.d.x;

  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  float tymin = (pmin.y - ray.o.y) / ray.d.y;
  float tymax = (pmax.y - ray.o.y) / ray.d.y;

  if (tymin > tymax) {
    std::swap(tymin, tymax);
  }

  if ((tmin > tymax) || (tymin > tmax)) {
    return false;
  }

  if (tymin > tmin) {
    tmin = tymin;
  }

  if (tymax < tmax) {
    tmax = tymax;
  }

  float tzmin = (pmin.z - ray.o.z) / ray.d.z;
  float tzmax = (pmax.z - ray.o.z) / ray.d.z;

  if (tzmin > tzmax) {
    std::swap(tzmin, tzmax);
  }

  if ((tmin > tzmax) || (tzmin > tmax)) {
    return false;
  }

  if (tzmin > tmin) {
    tmin = tzmin;
  }

  if (tzmax < tmax) {
    tmax = tzmax;
  }

  t_enter = tmin;
  t_exit = tmax;

  return true;
}

// Extend this bbox, if necessary, to include g or b.
void BBox::extend(Geometry* g) {
  BBox b = g->getBBox();
  extend(b);
}

void BBox::extend(const BBox& b) {
  pmin.x = std::min(pmin.x, b.pmin.x);
  pmin.y = std::min(pmin.y, b.pmin.y);
  pmin.z = std::min(pmin.z, b.pmin.z);

  pmax.x = std::max(pmax.x, b.pmax.x);
  pmax.y = std::max(pmax.y, b.pmax.y);
  pmax.z = std::max(pmax.z, b.pmax.z);
}

// Extend this bbox, if necessary, to include p.
void BBox::extend(const Point3D& p) {
    this->pmin = min(pmin, p);
    this->pmax = max(pmax, p);
    delta = pmax - pmin;
}

// Does this BBox contain p? True even when p lies on a boundary.
bool BBox::contains(const Point3D& p) const {
  return (p.x >= pmin.x && p.x <= pmax.x &&
          p.y >= pmin.y && p.y <= pmax.y &&
          p.z >= pmin.z && p.z <= pmax.z);
}

// Does this BBox overlap with g or b?
bool BBox::overlaps(Geometry* g) {
  BBox b = g->getBBox();
  return overlaps(b);
}

bool BBox::overlaps(const BBox& b) {
  return (pmax.x >= b.pmin.x && pmin.x <= b.pmax.x &&
          pmax.y >= b.pmin.y && pmin.y <= b.pmax.y &&
          pmax.z >= b.pmin.z && pmin.z <= b.pmax.z);
}

// max dimension
int BBox::maxDimension() const {
  if (delta.x > delta.y && delta.x > delta.z) {
    return 0;
  } else if (delta.y > delta.z) {
    return 1;
  } else {
    return 2;
  }
}