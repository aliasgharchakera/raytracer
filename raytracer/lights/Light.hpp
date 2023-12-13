#pragma once

/**
  This file declares the Light class which is an abstract class from which
  other concrete light objects will inherit.

*/

#include <iostream>

#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

class Light {
protected:
  RGBColor color; // light color.
  float ls;       // radiance scaling factor.

public:
  // Constructors.
  Light(); // set color to white (1, 1, 1) and ls to 1.
  Light(const RGBColor &c, float brightness); // set color to c and ls to brightness.

  // Copy constructor and assignment operator.
  Light(const Light &light) = default;
  Light &operator=(const Light &rhs) = default;

  // Destructor.
  virtual ~Light() = default;

  // String representation.
  virtual std::string to_string() const = 0;

  // Get/set color.
  RGBColor get_color() const;
  void set_color(const RGBColor &c);

  // Get/set radiance scaling factor.
  float get_ls() const;
  void set_ls(float brightness);

  // Returns the direction from the hit point to the light source.
  virtual Vector3D get_direction(const ShadeInfo &sinfo) const = 0;

  // Returns the radiance along the direction from the hit point to the light source.
  virtual RGBColor L(const ShadeInfo &sinfo) const = 0;

  // Returns the distance from the hit point to the light source.
  virtual float get_distance(const ShadeInfo &sinfo) const = 0;

  // Returns the shadow ray from the hit point to the light source.
  virtual Ray get_shadow_ray(const ShadeInfo &sinfo) const = 0;
};