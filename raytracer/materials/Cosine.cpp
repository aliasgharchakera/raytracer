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

Cosine* Cosine::clone() const {
    return (new Cosine(*this));
}

RGBColor Cosine::shade(const ShadeInfo &sinfo) const {
  // color * cos \theta (cos \theta: dot product of normal and -ray.dir) 
  return color * (sinfo.normal * -sinfo.ray.d);
}

// Get normal.
Vector3D Cosine::get_normal(const ShadeInfo &sinfo) const {
  return sinfo.normal;
}