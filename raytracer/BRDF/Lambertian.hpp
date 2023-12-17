#pragma once

#include "BRDF.hpp"

/**
  This file declares the Lambertian class which is a concrete BRDF class that implements
  the Lambertian BRDF.
*/

class Lambertian : public BRDF {
protected:
	float kd; // Diffuse reflection coefficient.
	RGBColor cd; // Diffuse color.

public:
  // Constructors.
	Lambertian();

	// Copy constructor and assignment operator.
	Lambertian(const Lambertian& lamb);

	Lambertian& operator=(const Lambertian& rhs);

	// Destructor.
	virtual ~Lambertian() = default;

	// f function.
	virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const;
  virtual RGBColor sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi) const;
	virtual RGBColor sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
	virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;
	
	// Setters.
	void set_ka(const float ka);

	void set_kd(const float kd);

	void set_cd(const RGBColor& c);

	void set_cd(const float r, const float g, const float b);
	
	void set_cd(const float c);
};
