#pragma once

/**
  This file declares the Spot class which represents a spot light.
*/

#include "Light.hpp"

#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

class Spot : public Light {
protected:
  Point3D pos; // position of the light source.
  Vector3D dir; // direction of the light source.
  float cos_cutoff; // cosine of the cutoff angle.
  float exp; // exponent for the falloff.

public:
  // Constructors.
  Spot(); // set color to white (1, 1, 1), ls to 1, pos to (0, 0, 0), dir to (0, 0, -1), cos_cutoff to 0.5, and exp to 1.
  Spot(const RGBColor &c, float brightness, const Point3D &position, const Vector3D &direction, float cutoff, float exponent); // set color to c, ls to brightness, pos to position, dir to direction, cos_cutoff to cutoff, and exp to exponent.

  // Copy constructor and assignment operator.
  Spot(const Spot &spot) = default;
  Spot &operator=(const Spot &rhs) = default;

  // Destructor.
  virtual ~Spot() = default;

  // String representation.
  virtual std::string to_string() const override;

  // Returns the direction from the hit point to the light source.
  virtual Vector3D get_direction(const ShadeInfo &sinfo) const override;

  // Returns the radiance along the direction from the hit point to the light source.
  virtual RGBColor L(const ShadeInfo &sinfo) const override;

  // Returns the distance from the hit point to the light source.
  virtual float get_distance(const ShadeInfo &sinfo) const override;

  // Returns the shadow ray from the hit point to the light source.
  virtual Ray get_shadow_ray(const ShadeInfo &sinfo) const override;
};