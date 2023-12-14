#pragma once

/**
  This file declares the class Matte which represents a matte material.
*/

#include "Material.hpp"

#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"

class Matte : public Material {
protected:
  RGBColor color; // the color of the material.
  float ka;       // ambient coefficient.
  float kd;       // diffuse coefficient.

public:
  // Constructors.
  Matte();                          // set color to (0, 0, 0).
  Matte(float c);                   // set color to (c, c, c).
  Matte(float r, float g, float b); // set color to (r, g, b).
  Matte(const RGBColor &c);         // set color to c.

  // Copy constuctor and assignment operator.
  Matte(const Matte &other);
  Matte &operator=(const Matte &other);

  // Desctructor.
  virtual ~Matte() = default;

  // Set ambient coefficient.
  void set_ka(float k);

  // Set diffuse coefficient.
  void set_kd(float k);

  /* Returned shade is: color * (ka + kd * cos \theta).
     \theta is the angle between the normal at the hit pont and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
  */
  virtual RGBColor shade(const ShadeInfo &sinfo) const override;

  // Get normal.
  virtual Vector3D get_normal(const ShadeInfo &sinfo) const override;
};