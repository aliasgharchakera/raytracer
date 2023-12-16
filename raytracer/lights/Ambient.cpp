#include "Ambient.hpp"

// Constructors.
Ambient::Ambient() : Light() {}

Ambient::Ambient(const RGBColor &c, float brightness) : Light(c, brightness) {}

// String representation.
std::string Ambient::to_string() const {
  return "Ambient()";
}

// Returns the direction from the hit point to the light source.
Vector3D Ambient::get_direction(const ShadeInfo &sinfo) const {
  return Vector3D(0.0);
}

// Returns the radiance along the direction from the hit point to the light source.
RGBColor Ambient::L(const ShadeInfo &sinfo) const {
  return color * ls;
}

// Returns the distance from the hit point to the light source.
float Ambient::get_distance(const ShadeInfo &sinfo) const {
  return 0.0f;
}

// Returns the shadow ray from the hit point to the light source.
Ray Ambient::get_shadow_ray(const ShadeInfo &sinfo) const {
  return Ray();
}