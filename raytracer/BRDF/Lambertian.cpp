#include "Lambertian.hpp"

// Constructors.
Lambertian::Lambertian() : BRDF(), kd(0), cd(0) {}

Lambertian::Lambertian(const Lambertian &other) : BRDF(other), kd(other.kd), cd(other.cd) {}

Lambertian &Lambertian::operator=(const Lambertian &rhs) {
  if (this == &rhs) {
    return *this;
  }

  BRDF::operator=(rhs);

  kd = rhs.kd;
  cd = rhs.cd;

  return *this;
}

// Destructor.
Lambertian::~Lambertian() = default;

// f function.
RGBColor Lambertian::f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const {
  return kd * cd * invPI;
}

// Sample f function.
//TODO implement this
RGBColor Lambertian::sample_f(const ShadeInfo &sinfo,const Vector3D &wo, Vector3D &wi, float& pdf) const {
  return black;
}


// Rho function.
RGBColor Lambertian::rho(const ShadeInfo &sinfo, const Vector3D &wo) const {
  return kd * cd;
}

void Lambertian::set_ka(const float ka) {
  this->kd = ka;
}

void Lambertian::set_kd(const float kd) {
  this->kd = kd;
}

void Lambertian::set_cd(const RGBColor &c) {
  this->cd = c;
}

void Lambertian::set_cd(const float r, const float g, const float b) {
  this->cd = RGBColor(r, g, b);
}

void Lambertian::set_cd(const float c) {
  this->cd = RGBColor(c, c, c);
}

Lambertian* Lambertian::clone(void) const {
  return new Lambertian(*this);
}

