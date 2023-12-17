#pragma once

#include "Material.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../world/World.hpp"

class Matte: public Material {	
	public:
			
		Matte(void);											

		Matte(const Matte& m);		

    // Matte(const RGBColor& c);						

		Matte& operator= (const Matte& rhs);							

		~Matte(void);											
		
		void set_ka(const float k);
		
		void set_kd(const float k);
		
		void set_cd(const RGBColor c);
		
		void set_cd(const float r, const float g, const float b);
		
		void set_cd(const float c);
				
		virtual RGBColor shade(const ShadeInfo& sr) const;

    virtual Vector3D get_normal(const ShadeInfo& sinfo) const;
		
	private:
		
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
};
