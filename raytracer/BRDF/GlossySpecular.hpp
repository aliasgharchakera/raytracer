#include "BRDF.hpp"

/**
  This file declares the GlossySpecular class which is a concrete BRDF class that implements
	the GlossySpecular BRDF.
*/

class GlossySpecular : public BRDF {
protected:
	float ks;
	RGBColor cs; // specular color
	float exp; // specular exponent
	Sampler* sampler; // for use in sample_f

public:
	// Constructors.
	GlossySpecular(void);

	// Destructor.
	~GlossySpecular(void);
	
	// f function.
	virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const;
	
	virtual RGBColor sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
	
	virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;
	
	// Setters.
	void set_ks(const float ks);
	
	void set_exp(const float exp);
	
	void set_cs(const RGBColor& c);
	
	void set_cs(const float r, const float g, const float b);
	
	void set_cs(const float c);
	
	void set_sampler(Sampler* sp, const float exp); // any type of sampling
	
	void set_samples(const int num_samples, const float exp); // multi jittered sampling
};