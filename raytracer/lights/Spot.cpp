#include "Spot.hpp"

// Constructors.
Spot::Spot() : Light(), pos(Point3D()), dir(Vector3D(0, 0, -1)), cos_cutoff(0.5f), exp(1) {}

Spot::Spot(const RGBColor &c, float brightness, const Point3D &position, const Vector3D &direction, float cutoff, float exponent) : Light(c, brightness), pos(position), dir(direction), cos_cutoff(cutoff), exp(exponent) {}

// String representation.
std::string Spot::to_string() const {
  return "Spot(" + pos.to_string() + ", " + dir.to_string() + ", " + std::to_string(cos_cutoff) + ", " + std::to_string(exp) + ")";
}

// Returns the direction from the hit point to the light source.
Vector3D Spot::get_direction(const ShadeInfo &sinfo) const {
  Vector3D direction = pos - sinfo.hit_point;
  float length = direction.length();
  if (length > 0.0f) {
    direction = direction / length;
  }
  return direction;
}

// Returns the radiance along the direction from the hit point to the light source.
RGBColor Spot::L(const ShadeInfo &sinfo) const {
  float cos_angle = dir * (-get_direction(sinfo));
  if (cos_angle > cos_cutoff) {
    return color * ls * std::pow(cos_angle, exp);
  }
  return RGBColor(0, 0, 0);
}

// Returns the distance from the hit point to the light source.
float Spot::get_distance(const ShadeInfo &sinfo) const {
  return (pos - sinfo.hit_point).length();
}

// Returns the shadow ray from the hit point to the light source.
Ray Spot::get_shadow_ray(const ShadeInfo &sinfo) const {
  return Ray(sinfo.hit_point, get_direction(sinfo));
}