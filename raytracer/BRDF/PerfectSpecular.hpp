#include "BRDF.hpp"

/**
  This file declares the PerfectSpecular class which is a concrete BRDF class that implements
	the PerfectSpecular BRDF.
*/

class PerfectSpecular : public BRDF {
private:
	float kr; // reflection coefficient
	RGBColor cr; // the reflection colour

public:
	// Constructors.
	PerfectSpecular(void);

	// Destructor.
	~PerfectSpecular(void);

	// Setters.
	void set_kr(const float k);
	void set_cr(const RGBColor& c);
	void set_cr(const float r, const float g, const float b);
	void set_cr(const float c);

	// f function.
	virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const;
	virtual RGBColor sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi) const;
	virtual RGBColor sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
	virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;
};