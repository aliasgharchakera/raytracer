#include "Sampler.hpp"

// Constructors.
Sampler::Sampler() : camera_ptr(NULL), viewplane_ptr(NULL) {}

Sampler::Sampler(Camera* c_ptr, ViewPlane* v_ptr) : camera_ptr(c_ptr), viewplane_ptr(v_ptr) {}

// Get rays corresponding to a pixel in the view plane. px and py are 0-based
std::vector<Ray> Sampler::get_rays(int px, int py) const {
  return std::vector<Ray>();
}