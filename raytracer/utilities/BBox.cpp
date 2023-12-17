#include "BBox.hpp"
#include <algorithm>
#include "../utilities/Constants.hpp"

BBox::BBox(const Point3D& _most_negative,
                         const Point3D& _most_positive)
    : most_negative{Point3D(_most_negative)},
      most_positive{Point3D(_most_positive)} {
  // nothing else to do
}

BBox BBox::merge(const BBox& other) const {
  Point3D most_negative_ = min(most_negative, other.most_negative);
  Point3D most_positive_ = max(most_positive, other.most_positive);

  return BBox(most_negative_, most_positive_);
}

int BBox::max_axis() const {
  double x_length = most_positive.x - most_negative.x;
  double y_length = most_positive.y - most_negative.y;
  double z_length = most_positive.z - most_negative.z;

  if (x_length >= y_length && x_length >= z_length) {
    return X_AXIS;
  }

  if (y_length >= x_length && y_length >= z_length) {
    return Y_AXIS;
  }

  return Z_AXIS;
}

bool BBox::intersect(const Point3D& point) const {
  return ((min(most_negative, point) == most_negative) && (max(most_positive, point) == most_positive));
}

bool BBox::intersect(const BBox& other) const {
  bool overlapping_x =
      BBox::overlapping1D(most_negative.x, most_positive.x,
                                 other.most_negative.x, other.most_positive.x);
  bool overlapping_y =
      BBox::overlapping1D(most_negative.y, most_positive.y,
                                 other.most_negative.y, other.most_positive.y);
  bool overlapping_z =
      BBox::overlapping1D(most_negative.z, most_positive.z,
                                 other.most_negative.z, other.most_positive.z);

  return overlapping_x && overlapping_y && overlapping_z;
}

double BBox::volume() const {
  Vector3D offset = most_positive - most_negative;
  return offset.x * offset.y * offset.z;
}

bool BBox::hit(const Ray& ray) const {
  // modified slightly from code by Kevin Suffern
  double ox = ray.o.x;
  double oy = ray.o.y;
  double oz = ray.o.z;
  double dx = ray.d.x;
  double dy = ray.d.y;
  double dz = ray.d.z;

  double tx_min, ty_min, tz_min;
  double tx_max, ty_max, tz_max;

  double x0 = most_negative.x;
  double x1 = most_positive.x;
  double y0 = most_negative.y;
  double y1 = most_positive.y;
  double z0 = most_negative.z;
  double z1 = most_positive.z;

  double a = 1.0 / dx;
  if (a >= 0) {
    tx_min = (x0 - ox) * a;
    tx_max = (x1 - ox) * a;
  } else {
    tx_min = (x1 - ox) * a;
    tx_max = (x0 - ox) * a;
  }

  double b = 1.0 / dy;
  if (b >= 0) {
    ty_min = (y0 - oy) * b;
    ty_max = (y1 - oy) * b;
  } else {
    ty_min = (y1 - oy) * b;
    ty_max = (y0 - oy) * b;
  }

  double c = 1.0 / dz;
  if (c >= 0) {
    tz_min = (z0 - oz) * c;
    tz_max = (z1 - oz) * c;
  } else {
    tz_min = (z1 - oz) * c;
    tz_max = (z0 - oz) * c;
  }

  double t0, t1;

  // find largest entering t value
  if (tx_min > ty_min)
    t0 = tx_min;
  else
    t0 = ty_min;

  if (tz_min > t0) t0 = tz_min;

  // find smallest exiting t value
  if (tx_max < ty_max)
    t1 = tx_max;
  else
    t1 = ty_max;

  if (tz_max < t1) t1 = tz_max;

  return (t0 < t1 && t1 > kEpsilon);
}

bool BBox::overlapping1D(double min1, double max1, double min2,
                                double max2) {
  return (max1 >= min2 && max2 >= min1);
}