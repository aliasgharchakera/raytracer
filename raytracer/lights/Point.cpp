#include "Point.hpp"

// Constructors.
Point::Point() : Light(), location(Point3D()) {}

Point::Point(const Point3D &loc) : Light(), location(loc) {}

Point::Point(const Point3D &loc, const RGBColor &c, float brightness) : Light(c, brightness), location(loc) {}

// String representation.
std::string Point::to_string() const {
  return "Point(" + location.to_string() + ")";
}

// Returns the direction from the hit point to the light source.
Vector3D Point::get_direction(const ShadeInfo &sinfo) const {
  Vector3D direction = location - sinfo.hit_point;
  float length = direction.length();
  if (length > 0.0f) {
    direction = direction / length;
  }
  return direction;
}

// Returns the radiance along the direction from the hit point to the light source.
RGBColor Point::L(const ShadeInfo &sinfo) const {
  return color * ls;
}

// Returns the distance from the hit point to the light source.
float Point::get_distance(const ShadeInfo &sinfo) const {
  return (location - sinfo.hit_point).length();
}

// Returns the shadow ray from the hit point to the light source.
Ray Point::get_shadow_ray(const ShadeInfo &sinfo) const {
  return Ray(sinfo.hit_point, get_direction(sinfo));
}