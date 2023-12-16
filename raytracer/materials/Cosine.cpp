#include "Cosine.hpp"

// Constructors.
Cosine::Cosine() : color(0, 0, 0) {}

Cosine::Cosine(float c) : color(c, c, c) {}

Cosine::Cosine(float r, float g, float b) : color(r, g, b) {}

Cosine::Cosine(const RGBColor &c) : color(c) {}

// Copy constuctor and assignment operator.
Cosine::Cosine(const Cosine &other) : color(other.color) {}

Cosine &Cosine::operator=(const Cosine &other) {
  if (this == &other) {
    return *this;
  }

  color = other.color;

  return *this;
}

RGBColor Cosine::shade(const ShadeInfo &sinfo) const {
  RGBColor shade = color * (sinfo.normal * -sinfo.ray.d);
  for (const auto& light : sinfo.w->lights) {
    Vector3D lightDir = light->get_direction(sinfo);
    Ray shadowRay(sinfo.hit_point, lightDir);

    if (sinfo.w->is_shadowed(shadowRay, sinfo)) {
      shade *= 0.75; // Apply shadow factor
    }
  }

  return shade;
}

// Get normal.
Vector3D Cosine::get_normal(const ShadeInfo &sinfo) const {
  return sinfo.normal;
}