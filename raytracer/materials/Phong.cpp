#include "Phong.hpp"

// Constructors.
Phong::Phong() : Material(), ambient_color(RGBColor(0)), diffuse_color(RGBColor(0)), specular_color(RGBColor(0)), ka(0), kd(0), ks(0), exp(0) {}

Phong::Phong(float c) : Material(), ambient_color(RGBColor(c)), diffuse_color(RGBColor(c)), specular_color(RGBColor(c)), ka(0), kd(0), ks(0), exp(0) {}

Phong::Phong(float r, float g, float b) : Material(), ambient_color(RGBColor(r, g, b)), diffuse_color(RGBColor(r, g, b)), specular_color(RGBColor(r, g, b)), ka(0), kd(0), ks(0), exp(0) {}

Phong::Phong(const RGBColor &c) : Material(), ambient_color(c), diffuse_color(c), specular_color(c), ka(0), kd(0), ks(0), exp(0) {}

// Copy constuctor and assignment operator.
Phong::Phong(const Phong &other) : Material(other), ambient_color(other.ambient_color), diffuse_color(other.diffuse_color), specular_color(other.specular_color), ka(other.ka), kd(other.kd), ks(other.ks), exp(other.exp) {}

Phong &Phong::operator=(const Phong &other) {
  if (this == &other) {
    return *this;
  }

  Material::operator=(other);

  ambient_color = other.ambient_color;
  diffuse_color = other.diffuse_color;
  specular_color = other.specular_color;
  ka = other.ka;
  kd = other.kd;
  ks = other.ks;
  exp = other.exp;

  return *this;
}

// Get/set ambient color.
RGBColor Phong::get_ambient_color() const {
  return ambient_color;
}

void Phong::set_ambient_color(const RGBColor &c) {
  ambient_color = c;
}

// Get/set diffuse color.
RGBColor Phong::get_diffuse_color() const {
  return diffuse_color;
}

void Phong::set_diffuse_color(const RGBColor &c) {
  diffuse_color = c;
}

// Get/set specular color.
RGBColor Phong::get_specular_color() const {
  return specular_color;
}

void Phong::set_specular_color(const RGBColor &c) {
  specular_color = c;
}

// Get/set diffuse coefficient.
float Phong::get_kd() const {
  return kd;
}

void Phong::set_kd(float k) {
  kd = k;
}

// Get/set ambient coefficient.
float Phong::get_ka() const {
  return ka;
}

void Phong::set_ka(float k) {
  ka = k;
}

// Get/set specular coefficient.
float Phong::get_ks() const {
  return ks;
}

void Phong::set_ks(float k) {
  ks = k;
}

// Get/set specular exponent.
float Phong::get_exp() const {
  return exp;
}

void Phong::set_exp(float e) {
  exp = e;
}

// shade function
RGBColor Phong::shade(const ShadeInfo &sinfo) const {
  // Get normal.
  Vector3D normal = sinfo.normal;

  // Get view direction.
  Vector3D view = -sinfo.ray.d;

  // Get ambient color.
  RGBColor ambient = ka * ambient_color * sinfo.w->ambient_ptr->get_color();

  // Get diffuse color.
  RGBColor diffuse = RGBColor(0);

  // Get specular color.
  RGBColor specular = RGBColor(0);

  // Get number of lights.
  int num_lights = sinfo.w->lights.size();

  // Loop through lights.
  for (int i = 0; i < num_lights; i++) {
    // Get light direction.
    Vector3D light_dir = sinfo.w->lights[i]->get_direction(sinfo);

    // Get dot product of light direction and normal.
    float dot = light_dir * normal;

    // If dot product is positive, add diffuse and specular.
    if (dot > 0) {
      // Add diffuse.
      diffuse += kd * diffuse_color * sinfo.w->lights[i]->get_color() * dot;

      // Add specular.
      Vector3D reflect = -light_dir + 2 * dot * normal;
      float spec_dot = reflect * view;
      if (spec_dot > 0) {
        specular += ks * specular_color * sinfo.w->lights[i]->get_color() * pow(spec_dot, exp);
      }
    }
  }

  // Return sum of ambient, diffuse, and specular.
  return ambient + diffuse + specular;
}

// Get normal.
Vector3D Phong::get_normal(const ShadeInfo &sinfo) const {
  return sinfo.normal;
}