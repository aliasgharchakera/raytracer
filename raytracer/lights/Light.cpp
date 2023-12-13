#include "Light.hpp"

// Constructors.
Light::Light() : color(RGBColor(1)), ls(1) {}

Light::Light(const RGBColor &c, float brightness) : color(c), ls(brightness) {}

// Get/set color.
RGBColor Light::get_color() const {
  return color;
}

void Light::set_color(const RGBColor &c) {
  color = c;
}

// Get/set radiance scaling factor.
float Light::get_ls() const {
  return ls;
}

void Light::set_ls(float brightness) {
  ls = brightness;
}