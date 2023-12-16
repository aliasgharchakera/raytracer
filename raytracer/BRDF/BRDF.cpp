#include "BRDF.hpp"

// Constructors.
BRDF::BRDF() : sampler_ptr(nullptr) {}

// copy constructor
BRDF::BRDF(const BRDF &brdf) {
  if (brdf.sampler_ptr) {
    sampler_ptr = new Sampler(*brdf.sampler_ptr);
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
    sampler_ptr = new Sampler(*rhs.sampler_ptr);
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
