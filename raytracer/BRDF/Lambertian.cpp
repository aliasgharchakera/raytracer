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

// f function.
RGBColor Lambertian::f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const {
  return kd * cd * invPI;
}

// Sample f function.
//TODO implement this
RGBColor Lambertian::sample_f(const ShadeInfo &sinfo,const Vector3D &wo, Vector3D &wi, float& pdf) const {
  // Generate a random direction on the hemisphere.
  Vector3D w = sinfo.normal;
  Vector3D v = Vector3D(0.0034, 1.0, 0.0071) ^ (w);
  v.normalize();
  Vector3D u = v ^ (w);

  Point3D sp = sampler_ptr->sample_hemisphere();
  wi = u * sp.x + v * sp.y + w * sp.z;
  wi.normalize();

  // Calculate the PDF.
  pdf = sinfo.normal * wi * invPI;

  // Return the result of the Lambertian reflection model.
  return kd * cd * invPI;
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