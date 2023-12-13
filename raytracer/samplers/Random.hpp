#pragma once

/**
  This file declares the Random class which represents a random sampler.

	It shoots n rays of weight 1/n randomly through the pixel.
*/

#include "Sampler.hpp"

class Random : public Sampler {
protected:
	// add members to cache values to avoid recomputation in get_rays().
	int n; // number of rays to shoot through the pixel.

public:
	// Constructors.
	Random() = default;                      // initializes members to NULL.
	Random(Camera *c_ptr, ViewPlane *v_ptr, int num); // set members.
	
	// Copy constuctor and assignment operator.
	Random(const Random &camera);
	Random &operator=(const Random &other);
	
	// Desctructor.
	virtual ~Random() = default;
	
	// Shoot n rays of weight 1/n randomly through the pixel.
	std::vector<Ray> get_rays(int px, int py) const override;
};