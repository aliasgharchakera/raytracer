#pragma once

/**
  This file declares the Sampler class which represents a sampler.

  It shoots n^2 rays of weight 1/n^2 randomly through n x n subpixels of the pixel.
*/

#include "Sampler.hpp"

class Jittered : public Sampler {
protected:
	// add members to cache values to avoid recomputation in get_rays().
	int n; // number of rows and columns to divide the pixel into.

public:
	// Constructors.
	Jittered() = default;                      // initializes members to NULL.
	Jittered(Camera *c_ptr, ViewPlane *v_ptr, int num); // set members.
	
	// Copy constuctor and assignment operator.
	Jittered(const Jittered &camera);
	Jittered &operator=(const Jittered &other);
	
	// Desctructor.
	virtual ~Jittered() = default;
	
	// Shoot n^2 rays of weight 1/n^2 randomly through n x n subpixels of the pixel.
	std::vector<Ray> get_rays(int px, int py) const override;
};