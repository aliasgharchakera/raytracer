#pragma once

/**
   This file declares the Regular class which represents a regular sampler.

   Courtesy Kevin Suffern.
*/

#include "Sampler.hpp"

class Regular : public Sampler {
protected:
  // add members to cache values to avoid recomputation in get_rays().
  int n; // number of rows and columns to divide the pixel into.

public:
    // Constructors.
    Regular() = default;                      // initializes members to NULL.
    Regular(Camera *c_ptr, ViewPlane *v_ptr, int num); // set members.
    
    // Copy constuctor and assignment operator.
    Regular(const Regular &camera);
    Regular &operator=(const Regular &other);
    
    // Desctructor.
    virtual ~Regular() = default;
    
    // Shoot n^2 rays of weight 1/n^2 through n x n subpixels of the pixel.
    std::vector<Ray> get_rays(int px, int py) const override;
};
