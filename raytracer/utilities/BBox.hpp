#include "Point3D.hpp"
#include "Ray.hpp"
#include "Constants.hpp"

class BBox {
 public:
  Point3D most_negative;
  Point3D most_positive;

 public:
  BBox() = default;
  BBox(const Point3D& _most_negative, const Point3D& _most_positive);

  BBox merge(const BBox& other) const;

  int max_axis() const;

  bool intersect(const Point3D& other) const;

  bool intersect(const BBox& other) const;

  double volume() const;

  bool hit(const Ray& ray) const;

 protected:
  static bool overlapping1D(double min1, double max1, double min2, double max2);
};
