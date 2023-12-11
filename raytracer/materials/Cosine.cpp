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

// TODO: Implement this function.
RGBColor Cosine::shade(const ShadeInfo &sinfo) const {}