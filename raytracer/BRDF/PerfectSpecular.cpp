#include "PerfectSpecular.hpp"

// Constructors.
PerfectSpecular::PerfectSpecular() : BRDF(), kr(0), cr(0) {}

PerfectSpecular::PerfectSpecular(const PerfectSpecular &other) : BRDF(other), kr(other.kr), cr(other.cr) {}

PerfectSpecular &PerfectSpecular::operator=(const PerfectSpecular &rhs) {
  if (this == &rhs) {
    return *this;
  }

  BRDF::operator=(rhs);

  kr = rhs.kr;
  cr = rhs.cr;

  return *this;
}

// Destructor.
PerfectSpecular::~PerfectSpecular() = default;

// f function.
RGBColor PerfectSpecular::f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const {
  return black;
}

// Sample f function.
RGBColor PerfectSpecular::sample_f(const ShadeInfo &sinfo,const Vector3D &wo, Vector3D &wi) const {
  float ndotwo = sinfo.normal * wo;
  wi = (-wo) + 2.0 * sinfo.normal * ndotwo;
  return kr * cr / (sinfo.normal * wi);
}

RGBColor PerfectSpecular::sample_f(const ShadeInfo &sinfo, const Vector3D &wo, Vector3D &wi, float &pdf) const {
  float ndotwo = sinfo.normal * wo;
  wi = -wo + 2.0 * sinfo.normal * ndotwo;
  pdf = sinfo.normal * wi;
  return kr * cr;
}

// Rho function.
RGBColor PerfectSpecular::rho(const ShadeInfo &sinfo, const Vector3D &wo) const {
  return black;
}

void PerfectSpecular::set_kr(const float k) {
  this->kr = k;
}

void PerfectSpecular::set_cr(const RGBColor &c) {
  this->cr = c;
}

void PerfectSpecular::set_cr(const float r, const float g, const float b) {
  this->cr = RGBColor(r, g, b);
}

void PerfectSpecular::set_cr(const float c) {
  this->cr = RGBColor(c, c, c);
}