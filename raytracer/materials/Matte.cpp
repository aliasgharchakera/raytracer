#include "Matte.hpp"

// Constructors.
Matte::Matte() : color(0, 0, 0), ka(0), kd(0) {}

Matte::Matte(float c) : color(c, c, c), ka(0), kd(0) {}

Matte::Matte(float r, float g, float b) : color(r, g, b), ka(0), kd(0) {}

Matte::Matte(const RGBColor &c) : color(c), ka(0), kd(0) {}

// Copy constuctor and assignment operator.
Matte::Matte(const Matte &other) : color(other.color), ka(other.ka), kd(other.kd) {}

Matte &Matte::operator=(const Matte &other) {
  if (this == &other) {
    return *this;
  }

  color = other.color;
  ka = other.ka;
  kd = other.kd;

  return *this;
}

// Set ambient coefficient.
void Matte::set_ka(float k) {
  ka = k;
}

// Set diffuse coefficient.
void Matte::set_kd(float k) {
  kd = k;
}
