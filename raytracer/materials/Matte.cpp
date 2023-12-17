#include "Matte.hpp"

// Constructors.
Matte::Matte(){}

Matte::Matte(const Matte &m) : Material(m) {
  kd= m.kd;
  cd = m.cd;
}

// Copy assignment operator.
Matte &Matte::operator=(const Matte &rhs) {
  if (this == &rhs) {
    return *this;
  }

  Material::operator=(rhs);

  if (ambient_brdf) {
    delete ambient_brdf;
    ambient_brdf = nullptr;
  }

  if (rhs.ambient_brdf) {
    ambient_brdf = new Lambertian(*rhs.ambient_brdf);
  }

  if (diffuse_brdf) {
    delete diffuse_brdf;
    diffuse_brdf = nullptr;
  }

  if (rhs.diffuse_brdf) {
    diffuse_brdf = new Lambertian(*rhs.diffuse_brdf);
  }

  return *this;
}

// Destructor.
Matte::~Matte() {
  if (ambient_brdf) {
    delete ambient_brdf;
    ambient_brdf = nullptr;
  }

  if (diffuse_brdf) {
    delete diffuse_brdf;
    diffuse_brdf = nullptr;
  }
}

// Set ka.
void Matte::set_ka(float k) {
  // ambient_brdf->set_kd(k);
  set_ka(k);
}

// Set kd.
void Matte::set_kd(float k) {
  // diffuse_brdf->set_kd(k);
  set_kd(k);
}

// Set cd.
void Matte::set_cd(const RGBColor c) {
  // ambient_brdf->set_cd(c);
  // diffuse_brdf->set_cd(c);
  set_cd(c);
}

// Set cd.
void Matte::set_cd(float r, float g, float b) {
  // ambient_brdf->set_cd(r, g, b);
  // diffuse_brdf->set_cd(r, g, b);
  set_cd(r, g, b);
}

// Set cd.
void Matte::set_cd(float c) {
  // ambient_brdf->set_cd(c);
  // diffuse_brdf->set_cd(c);
  set_cd(c);
}

// Shade function.
RGBColor Matte::shade(const ShadeInfo& sinfo) const {
  std::cout << "here";
  Vector3D wo = -sinfo.ray.d;
  RGBColor L = kd*cd;
  // Light* check2 = sinfo.w->ambient_ptr->L(sinfo);
  // std::cout << check2;
  // RGBColor L = ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_ptr->L(sinfo);
  // int num_lights = sinfo.w->lights.size();
  // int num_lights = 0;
  // for (int j = 0; j < num_lights; j++) {
  //   Vector3D wi = sinfo.w->lights[j]->get_direction(sinfo);
  //   float ndotwi = sinfo.normal * wi;
  //   if (ndotwi > 0.0) {
  //     bool in_shadow = false;
  //     // if (sinfo.w->lights[j]->casts_shadows()) {
  //     //   Ray shadow_ray(sinfo.hit_point, wi);
  //     //   in_shadow = sinfo.w->lights[j]->in_shadow(shadow_ray, sinfo);
  //     // }
  //     if (!in_shadow) {
  //       L += diffuse_brdf->f(sinfo, wo, wi) * sinfo.w->lights[j]->L(sinfo) * ndotwi;
  //     }      
  //   }
  // }
  return kd*cd;
}

// Get normal.
Vector3D Matte::get_normal(const ShadeInfo& sinfo) const {
  return sinfo.normal;
}