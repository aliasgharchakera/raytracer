#include "Glossy.hpp"

// Constructors.
Glossy::Glossy() : ambient_color(0), diffuse_color(0), specular_color(0), ka(0), kd(0), ks(0), exp(0), gloss(0) {}

Glossy::Glossy(float c) : ambient_color(c), diffuse_color(c), specular_color(c), ka(0), kd(0), ks(0), exp(0), gloss(0) {}

Glossy::Glossy(float r, float g, float b) : ambient_color(r, g, b), diffuse_color(r, g, b), specular_color(r, g, b), ka(0), kd(0), ks(0), exp(0), gloss(0) {}

Glossy::Glossy(const RGBColor &c) : ambient_color(c), diffuse_color(c), specular_color(c), ka(0), kd(0), ks(0), exp(0), gloss(0) {}

// Copy constuctor and assignment operator.
Glossy::Glossy(const Glossy &other) : ambient_color(other.ambient_color), diffuse_color(other.diffuse_color), specular_color(other.specular_color), ka(other.ka), kd(other.kd), ks(other.ks), exp(other.exp), gloss(other.gloss) {}

Glossy &Glossy::operator=(const Glossy &other) {
  if (this == &other) {
    return *this;
  }

  ambient_color = other.ambient_color;
  diffuse_color = other.diffuse_color;
  specular_color = other.specular_color;
  ka = other.ka;
  kd = other.kd;
  ks = other.ks;
  exp = other.exp;
  gloss = other.gloss;

  return *this;
}

// Get/set ambient color.
RGBColor Glossy::get_ambient_color() const {
  return ambient_color;
}

void Glossy::set_ambient_color(const RGBColor &c) {
  ambient_color = c;
}

// Get/set diffuse color.
RGBColor Glossy::get_diffuse_color() const {
  return diffuse_color;
}

void Glossy::set_diffuse_color(const RGBColor &c) {
  diffuse_color = c;
}

// Get/set specular color.
RGBColor Glossy::get_specular_color() const {
  return specular_color;
}

void Glossy::set_specular_color(const RGBColor &c) {
  specular_color = c;
}

// Get/set diffuse coefficient.
float Glossy::get_kd() const {
  return kd;
}

void Glossy::set_kd(float k) {
  kd = k;
}

// Get/set ambient coefficient.
float Glossy::get_ka() const {
  return ka;
}

void Glossy::set_ka(float k) {
  ka = k;
}

// Get/set specular coefficient.
float Glossy::get_ks() const {
  return ks;
}

void Glossy::set_ks(float k) {
  ks = k;
}

// Get/set specular exponent.
float Glossy::get_exp() const {
  return exp;
}

void Glossy::set_exp(float e) {
  exp = e;
}

// Get/set gloss coefficient.
float Glossy::get_gloss() const {
  return gloss;
}

void Glossy::set_gloss(float g) {
  gloss = g;
}

RGBColor Glossy::shade(const ShadeInfo &sinfo) const {
  RGBColor shade = ambient_color * ka;
  for (const auto& light : sinfo.w->lights) {
    Vector3D lightDir = light->get_direction(sinfo);
    Ray shadowRay(sinfo.hit_point, lightDir);

    if (sinfo.w->is_shadowed(shadowRay, sinfo)) {
      shade *= 0.75; // Apply shadow factor
    } else {
      float nDotL = sinfo.normal * lightDir;
      Vector3D r = -lightDir + 2 * sinfo.normal * nDotL;
      float rDotV = r * -sinfo.ray.d;

      if (nDotL > 0.0) {
        shade += (diffuse_color * kd + specular_color * ks * pow(rDotV, exp)) * nDotL;
      }
    }
  }

  return shade;
}

// Get normal.
Vector3D Glossy::get_normal(const ShadeInfo &sinfo) const {
  return sinfo.normal;
}