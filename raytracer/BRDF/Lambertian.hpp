#include "BRDF.hpp"

class Lambertian: public BRDF 
{
	public:
	
		Lambertian(void);
		
		Lambertian(const Lambertian& lamb);
		
		Lambertian& 
		operator= (const Lambertian& rhs);
		
		virtual
		~Lambertian(void);
		
		virtual Lambertian*
		clone(void) const;
		
		virtual RGBColor
		f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor												
		sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		virtual RGBColor
		rho(const ShadeInfo& sr, const Vector3D& wo) const;
			
		void
		set_ka(const float ka);	
				
		void
		set_kd(const float kd);
		
		void
		set_cd(const RGBColor& c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void													
		set_cd(const float c);
					
	private:
	
		float		kd;
		RGBColor 	cd;
};
