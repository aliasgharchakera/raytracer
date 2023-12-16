#include "Light.hpp"

class Ambient : public Light {
public:
  // Constructors.
  Ambient(); // set color to white (1, 1, 1) and ls to 1.
  Ambient(const RGBColor &c, float brightness); // set color to c and ls to brightness.

  // Copy constructor and assignment operator.
  Ambient(const Ambient &ambient) = default;
  Ambient &operator=(const Ambient &rhs) = default;

  // Destructor.
  virtual ~Ambient() = default;

  // String representation.
  virtual std::string to_string() const;

  // Returns the direction from the hit point to the light source.
  virtual Vector3D get_direction(const ShadeInfo &sinfo) const;

  // Returns the radiance along the direction from the hit point to the light source.
  virtual RGBColor L(const ShadeInfo &sinfo) const;

  // Returns the distance from the hit point to the light source.
  virtual float get_distance(const ShadeInfo &sinfo) const;

  // Returns the shadow ray from the hit point to the light source.
  virtual Ray get_shadow_ray(const ShadeInfo &sinfo) const;
};