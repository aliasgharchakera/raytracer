#pragma once

/**
   This file declares the Geometry class which is an abstract class from which
   other concrete geometric objects will inherit.

   Courtesy Kevin Suffern.
*/

#include <string>
#include <cmath>
#include <limits>
#include <sstream>
#include <math.h>

#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"

class BBox;
class Material;
class Ray;
class ShadeInfo;

class Geometry {
protected:
  Material *material_ptr; // this object's material.

public:
  // Constructors.
  Geometry(); // sets material_ptr to NULL.

  // Copy constructor and assignment operator.
  Geometry(const Geometry &object) = default;
  Geometry &operator=(const Geometry &rhs) = default;

  // Destructor.
  virtual ~Geometry() = default;
  
  // String representation.
  virtual std::string to_string() const = 0;

  // Get/set material.
  Material *get_material() const;
  void set_material(Material *mPtr); 

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, float &t, ShadeInfo &sinfo) const = 0;

  // Check if shadow ray hits the object.
  // HACK: This is a hack. We should be able to use the hit function to do this.
  virtual bool shadow_hit(const Ray &ray, float &tmin) const = 0;

  // Get bounding box.
  virtual BBox getBBox() const = 0;
};
