#include "BRDF.hpp"

class PerfectSpecular: public BRDF 
{
	public:
	
		PerfectSpecular(void);
		
		~PerfectSpecular(void);
		
		virtual PerfectSpecular*
		clone(void) const;
		
		void
		set_kr(const float k);
		
		void
		set_cr(const RGBColor& c);
		
		void													
		set_cr(const float r, const float g, const float b);
		
		void													
		set_cr(const float c);
		
		virtual RGBColor
		f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		virtual RGBColor
		rho(const ShadeInfo& sr, const Vector3D& wo) const;
				
	private:
	
		float		kr;			// reflection coefficient
		RGBColor 	cr;			// the reflection colour
};