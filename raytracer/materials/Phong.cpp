#include "Phong.hpp"

// Constructors.
Phong::Phong() : color(RGBColor()), ka(0), kd(0), ks(0), exp(0) {}

Phong::Phong(float c) : color(c), ka(0), kd(0), ks(0), exp(0) {}

Phong::Phong(float r, float g, float b) : color(r, g, b), ka(0), kd(0), ks(0), exp(0) {}

Phong::Phong(const RGBColor &c) : color(c), ka(0), kd(0), ks(0), exp(0) {}

// Copy constuctor and assignment operator.
Phong::Phong(const Phong &other) : color(other.color), ka(other.ka), kd(other.kd), ks(other.ks), exp(other.exp) {}

Phong &Phong::operator=(const Phong &other) {
  if (this == &other) {
    return *this;
  }

  color = other.color;
  ka = other.ka;
  kd = other.kd;
  ks = other.ks;
  exp = other.exp;

  return *this;
}

// Set ambient coefficient.
void Phong::set_ka(float k) {
  ka = k;
}

// Set diffuse coefficient.
void Phong::set_kd(float k) {
  kd = k;
}

// Set specular coefficient.
void Phong::set_ks(float k) {
  ks = k;
}

// Set specular exponent.
void Phong::set_exp(float e) {
  exp = e;
}

/* Returned shade is: color * (ka + kd * cos \theta + ks * cos^n \alpha).
   \theta is the angle between the normal at the hit pont and the ray.
   \alpha is the angle between the reflection vector and the ray.
   Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
   cos^n \alpha = dot product of reflection vector and -ray.dir.
*/
RGBColor Phong::shade(const ShadeInfo &sinfo) const {
  // color * (ka + kd * cos \theta + ks * cos^n \alpha).
  // cos \theta: dot product of normal and -ray.dir.
  // cos^n \alpha = dot product of reflection vector and -ray.dir.
  Vector3D r = -sinfo.ray.d + 2 * (sinfo.normal * sinfo.ray.d) * sinfo.normal;
  float cos_alpha = r * -sinfo.ray.d;

  return color * (ka + kd * (sinfo.normal * -sinfo.ray.d) + ks * pow(cos_alpha, exp));
}