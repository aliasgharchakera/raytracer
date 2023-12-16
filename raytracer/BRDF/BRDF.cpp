#include "BRDF.hpp"

// Constructors.
BRDF::BRDF() : sampler_ptr(nullptr) {}

// copy constructor
BRDF::BRDF(const BRDF &brdf) {
  if (brdf.sampler_ptr) {
    sampler_ptr = brdf.sampler_ptr->clone();
  } else {
    sampler_ptr = nullptr;
  }
};

// assignment operator
BRDF &BRDF::operator=(const BRDF &rhs) {
  if (this == &rhs) {
    return *this;
  }

  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = nullptr;
  }

  if (rhs.sampler_ptr) {
    sampler_ptr = rhs.sampler_ptr->clone();
  }

  return *this;
}

// Destructor.
BRDF::~BRDF() {
  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = nullptr;
  }
}

// Set sampler.
void BRDF::set_sampler(Sampler *s_ptr) {
  sampler_ptr = s_ptr;
}

