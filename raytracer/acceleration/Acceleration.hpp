#pragma once

/**
  This file declares the Acceleration class which is an abstract class from which
  other concrete acceleration classes will inherit.
*/

#include <string>
#include <cmath>
#include <limits>
#include <sstream>
#include <math.h>

#include "../geometry/Geometry.hpp"

class Geometry;

class Acceleration {
protected:
  std::vector<Geometry *> objects; // objects to be accelerated.

public:
  // Constructors.
  Acceleration(); // sets objects to empty.

  // Copy constructor and assignment operator.
  Acceleration(const Acceleration &object) = default;
  Acceleration &operator=(const Acceleration &rhs) = default;

  // Destructor.
  virtual ~Acceleration() = default;

  // String representation.
  virtual std::string to_string() const = 0;

  // Add an object to the acceleration structure.
  virtual void add_object(Geometry *object_ptr) = 0;

  // Remove an object from the acceleration structure.
  virtual void remove_object(Geometry *object_ptr) = 0;

  // Get the number of objects in the acceleration structure.
  virtual int get_num_objects() const = 0;

  // Get the ith object in the acceleration structure.
  virtual Geometry *get_object(int i) const = 0;

  // Get the bounding box of the acceleration structure.
  virtual BBox getBBox() const = 0;

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, float &t, ShadeInfo &sinfo) const = 0;
};