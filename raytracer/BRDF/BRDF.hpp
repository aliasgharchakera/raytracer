#pragma once

/**
   This file declares the BRDF class which is an abstract class from which
   other concrete BRDFs will inherit.
*/

#include <sstream>

#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../samplers/Sampler.hpp"

class BRDF {
protected:
  Sampler *sampler_ptr;

public:
  // Constructors.
  BRDF(void);

  // Copy constructor and assignment operator.
  BRDF(const BRDF &brdf) = default;
  BRDF &operator=(const BRDF &rhs) = default;

  // Destructor.
  virtual ~BRDF() = default;

  // Set sampler.
  void set_sampler(Sampler *s_ptr);

  // f function.
  virtual RGBColor f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const = 0;

  // Sample f function.
  virtual RGBColor sample_f(const ShadeInfo &sinfo,const Vector3D &wo, Vector3D &wi) const = 0;
  virtual RGBColor sample_f(const ShadeInfo &sinfo,const Vector3D &wo, Vector3D &wi, float& pdf) const = 0;

  // Rho function.
  virtual RGBColor rho(const ShadeInfo &sinfo, const Vector3D &wo) const = 0;
};
