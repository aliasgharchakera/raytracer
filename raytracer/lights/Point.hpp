#pragma once

/**
  This file declares the Point class which represents a point light source.
*/

#include "Light.hpp"

class Point : public Light {
protected:
  Point3D location; // location of the light source.

public:
  // Constructors.
  Point(); // set location to (0, 0, 0) and color to white (1, 1, 1).
  Point(const Point3D &loc); // set location to loc and color to white (1, 1, 1).
  Point(const Point3D &loc, const RGBColor &c, float brightness); // set location to loc, color to c, and ls to brightness.

  // Copy constructor and assignment operator.
  Point(const Point &light) = default;
  Point &operator=(const Point &rhs) = default;

  // Destructor.
  virtual ~Point() = default;

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