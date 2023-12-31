#pragma once

/**
   This file declares the Simple class which represents a simple sampler.

   It shoots a single ray of weight 1 through a pixel.

   Courtesy Kevin Suffern.
*/

#include "Sampler.hpp"

class Simple : public Sampler {
protected:
  // add members to cache values to avoid recomputation in get_rays().
  // Cache values to avoid recomputation in get_rays().
  //HACK verify this
  // int cached_px;
  // int cached_py;
  // std::vector<Ray> cached_rays;

public:
  // Constructors.
  Simple() = default;                      // initializes members to NULL.
  Simple(Camera *c_ptr, ViewPlane *v_ptr); // set members.

  // Copy constuctor and assignment operator.
  Simple(const Simple &camera);
  Simple &operator=(const Simple &other);

  // Desctructor.
  virtual ~Simple() = default;

  // Shoot a ray of weight 1 through the center of the pixel.
  std::vector<Ray> get_rays(int px, int py) const override;
};
  
