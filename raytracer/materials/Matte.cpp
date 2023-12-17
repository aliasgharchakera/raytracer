#include "Matte.hpp"

// Constructors.
Matte::Matte() : ambient_brdf(new Lambertian()), diffuse_brdf(new Lambertian()) {}

// TODO replace the clones in these files
Matte::Matte(const Matte &m) : Material(m) {
  if (m.ambient_brdf) {
    ambient_brdf = new Lambertian(*m.ambient_brdf);
  } else {
    ambient_brdf = nullptr;
  }

  if (m.diffuse_brdf) {
    diffuse_brdf = new Lambertian(*m.diffuse_brdf);
  } else {
    diffuse_brdf = nullptr;
  }
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
  ambient_brdf->set_kd(k);
}

// Set kd.
void Matte::set_kd(float k) {
  diffuse_brdf->set_kd(k);
}

// Set cd.
void Matte::set_cd(const RGBColor c) {
  ambient_brdf->set_cd(c);
  diffuse_brdf->set_cd(c);
}

// Set cd.
void Matte::set_cd(float r, float g, float b) {
  ambient_brdf->set_cd(r, g, b);
  diffuse_brdf->set_cd(r, g, b);
}

// Set cd.
void Matte::set_cd(float c) {
  ambient_brdf->set_cd(c);
  diffuse_brdf->set_cd(c);
}

// Shade function.
RGBColor Matte::shade(const ShadeInfo& sinfo) const {
  Vector3D wo = -sinfo.ray.d;
  RGBColor L = ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_ptr->L(sinfo);
  int num_lights = sinfo.w->lights.size();

  for (int i = 0; i < num_lights; i++) {
    Vector3D wi = sinfo.w->lights[i]->get_direction(sinfo);
    float ndotwi = sinfo.normal * wi;

    if (ndotwi > 0.0) {
      bool in_shadow = false;

      // TODO make this cast shadows
      // if (sinfo.w->lights[i]->casts_shadows()) {
      //   Ray shadow_ray(sinfo.hit_point, wi);
      //   in_shadow = sinfo.w->is_shadowed(shadow_ray, sinfo);
      // }

      if (!in_shadow) {
        L += diffuse_brdf->f(sinfo, wo, wi) * sinfo.w->lights[i]->L(sinfo) * ndotwi;
      }
    }
  }

  return L;
}

// Get normal.
Vector3D Matte::get_normal(const ShadeInfo& sinfo) const {
  return sinfo.normal;
}