#include "Matte.hpp"

// Constructors.
Matte::Matte() : Material(), ambient_color(RGBColor(0)), diffuse_color(RGBColor(0)), ka(0), kd(0) {}

Matte::Matte(float c) : Material(), ambient_color(RGBColor(c)), diffuse_color(RGBColor(c)), ka(0), kd(0) {}

Matte::Matte(float r, float g, float b) : Material(), ambient_color(RGBColor(r, g, b)), diffuse_color(RGBColor(r, g, b)), ka(0), kd(0) {}

Matte::Matte(const RGBColor &c) : Material(), ambient_color(c), diffuse_color(c), ka(0), kd(0) {}

// Copy constuctor and assignment operator.
Matte::Matte(const Matte &other) : Material(other), ambient_color(other.ambient_color), diffuse_color(other.diffuse_color), ka(other.ka), kd(other.kd) {}

Matte &Matte::operator=(const Matte &other) {
  if (this == &other) {
    return *this;
  }

  Material::operator=(other);

  ambient_color = other.ambient_color;
  diffuse_color = other.diffuse_color;
  ka = other.ka;
  kd = other.kd;

  return *this;
}

// Get/set ambient color.
RGBColor Matte::get_ambient_color() const {
  return ambient_color;
}

void Matte::set_ambient_color(const RGBColor &c) {
  ambient_color = c;
}

// Get/set diffuse color.
RGBColor Matte::get_diffuse_color() const {
  return diffuse_color;
}

void Matte::set_diffuse_color(const RGBColor &c) {
  diffuse_color = c;
}

// Get/set diffuse coefficient.
float Matte::get_kd() const {
  return kd;
}

void Matte::set_kd(float k) {
  kd = k;
}

// Get/set ambient coefficient.
float Matte::get_ka() const {
  return ka;
}

void Matte::set_ka(float k) {
  ka = k;
}

RGBColor Matte::shade(const ShadeInfo &sinfo) const {
  RGBColor shade = ambient_color * ka;
  for (const auto& light : sinfo.w->lights) {
    Vector3D lightDir = light->get_direction(sinfo);
    Ray shadowRay(sinfo.hit_point, lightDir);

    if (sinfo.w->is_shadowed(shadowRay, sinfo)) {
      shade *= 0.75; // Apply shadow factor
    } else {
      shade += diffuse_color * kd * (lightDir * sinfo.normal);
    }
  }

  return shade;
}

// Get normal.
Vector3D Matte::get_normal(const ShadeInfo &sinfo) const {
  return sinfo.normal;
}