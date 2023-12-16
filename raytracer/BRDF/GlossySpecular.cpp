#include "GlossySpecular.hpp"

// Constructors.
GlossySpecular::GlossySpecular() : BRDF(), ks(0), cs(0), exp(0) {}

// Destructor.
GlossySpecular::~GlossySpecular() = default;

// f function.
RGBColor GlossySpecular::f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const {
  RGBColor L;
  float ndotwi = sinfo.normal * wi;
  Vector3D r(-wi + 2.0 * sinfo.normal * ndotwi);
  float rdotwo = r * wo;

  if (rdotwo > 0.0) {
    L = ks * cs * pow(rdotwo, exp);
  }

  return L;
}

// Sample f function.
RGBColor GlossySpecular::sample_f(const ShadeInfo &sinfo, const Vector3D &wo, Vector3D &wi, float &pdf) const {
  float ndotwo = sinfo.normal * wo;
  Vector3D r = -wo + 2.0 * sinfo.normal * ndotwo;
  Vector3D w = r;
  Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
  u.normalize();
  Vector3D v = u ^ w;

  // FIXME: This is from the book??? Why is it here?
  Point3D sp = sampler_ptr->sample_hemisphere();
  wi = sp.x * u + sp.y * v + sp.z * w;

  if (sinfo.normal * wi < 0.0) {
    wi = -sp.x * u - sp.y * v + sp.z * w;
  }

  float phong_lobe = pow(r * wi, exp);
  pdf = phong_lobe * (sinfo.normal * wi);
  return ks * cs * phong_lobe;
}

// Rho function.
RGBColor GlossySpecular::rho(const ShadeInfo &sinfo, const Vector3D &wo) const {
  return black;
}

void GlossySpecular::set_ks(const float ks) {
  this->ks = ks;
}

void GlossySpecular::set_exp(const float exp) {
  this->exp = exp;
}

void GlossySpecular::set_cs(const RGBColor &c) {
  this->cs = c;
}

void GlossySpecular::set_cs(const float r, const float g, const float b) {
  this->cs = RGBColor(r, g, b);
}

void GlossySpecular::set_cs(const float c) {
  this->cs = RGBColor(c, c, c);
}

void GlossySpecular::set_sampler(Sampler *sp, const float exp) {
  this->sampler_ptr = sp;
  // FIXME: What is this???
  this->sampler_ptr->map_samples_to_hemisphere(exp);
}

void GlossySpecular::set_samples(const int num_samples, const float exp) {
  // FIXME: What is this???
  this->sampler_ptr = new MultiJittered(num_samples);
  this->sampler_ptr->map_samples_to_hemisphere(exp);
}
