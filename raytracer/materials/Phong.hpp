#pragma once

/**
   This file declares the class Phong which represents a Phong material.
*/

#include "Material.hpp"

#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../BRDF/GlossySpecular.hpp"
#include "../world/World.hpp"

class Phong : public Material {
protected:
  RGBColor color; // the color of the material.
  float ka;       // ambient coefficient.
  float kd;       // diffuse coefficient.
  float ks;       // specular coefficient.
  float exp;      // specular exponent.
  Lambertian* ambient_brdf;
  Lambertian* diffuse_brdf;
  GlossySpecular* specular_brdf;

public:
  // Constructors.
  Phong();                          // set color to (0, 0, 0).
  Phong(float c);                   // set color to (c, c, c).
  Phong(float r, float g, float b); // set color to (r, g, b).
  Phong(const RGBColor &c);         // set color to c.

  // Copy constuctor and assignment operator.
  Phong(const Phong &other);
  Phong &operator=(const Phong &other);

  // Desctructor.
  ~Phong() = default;

  // Set ambient coefficient.
  void set_ka(float k);

  // Set diffuse coefficient.
  void set_kd(float k);

  // Set specular coefficient.
  void set_ks(float k);

  // Set specular exponent.
  void set_exp(float e);

  /* Returned shade is: color * (ka + kd * cos \theta + ks * cos^n \alpha).
     \theta is the angle between the normal at the hit pont and the ray.
     \alpha is the angle between the reflection vector and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
     cos^n \alpha = dot product of reflection vector and -ray.dir.
  */
  RGBColor shade(const ShadeInfo &sinfo) const override;

  // Get normal.
  Vector3D get_normal(const ShadeInfo &sinfo) const override;
};