#include "BBox.hpp"

// Constructors.
BBox::BBox(const Point3D &p0, const Point3D &p1) : pmin(p0), pmax(p1) {}

// String representation.
std::string BBox::to_string() const {
  return "BBox(" + pmin.to_string() + ", " + pmax.to_string() + ")";
}

// Does ray hit bbox? If so, set entering and leaving t values for ray.
// REVIEW: Unsure if this is correct.
bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const {
  float t0 = ray.o.x;
  float t1 = ray.o.x + ray.d.x;
  float tmin = std::min(t0, t1);
  float tmax = std::max(t0, t1);
  float ty0 = ray.o.y;
  float ty1 = ray.o.y + ray.d.y;
  float tymin = std::min(ty0, ty1);
  float tymax = std::max(ty0, ty1);
  if ((tmin > tymax) || (tymin > tmax)) {
    return false;
  }
  if (tymin > tmin) {
    tmin = tymin;
  }
  if (tymax < tmax) {
    tmax = tymax;
  }
  float tz0 = ray.o.z;
  float tz1 = ray.o.z + ray.d.z;
  float tzmin = std::min(tz0, tz1);
  float tzmax = std::max(tz0, tz1);
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
void BBox::extend(Geometry *g) {
  extend(g->getBBox());
}

void BBox::extend(const BBox &b) {
  pmin.x = std::min(pmin.x, b.pmin.x);
  pmin.y = std::min(pmin.y, b.pmin.y);
  pmin.z = std::min(pmin.z, b.pmin.z);
  pmax.x = std::max(pmax.x, b.pmax.x);
  pmax.y = std::max(pmax.y, b.pmax.y);
  pmax.z = std::max(pmax.z, b.pmax.z);
}

// Does this BBox contain p? True even when p lies on a boundary.
bool BBox::contains(const Point3D &p) {
  return (p.x >= pmin.x && p.x <= pmax.x) &&
         (p.y >= pmin.y && p.y <= pmax.y) &&
         (p.z >= pmin.z && p.z <= pmax.z);
}

// Does this BBox overlap with g or b?
bool BBox::overlaps(Geometry *g) {
  return overlaps(g->getBBox());
}

bool BBox::overlaps(const BBox &b) {
  return (pmax.x >= b.pmin.x && pmin.x <= b.pmax.x) &&
         (pmax.y >= b.pmin.y && pmin.y <= b.pmax.y) &&
         (pmax.z >= b.pmin.z && pmin.z <= b.pmax.z);
}