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

Point3D BRDF::sample_hemisphere() const {
    std::uniform_real_distribution<double> unif(-1.0, 1.0);
    std::random_device rd;

    double x = unif(rd);
    double y = unif(rd);

    float cos_phi = cos(2.0 * PI * x);
    float sin_phi = sin(2.0 * PI * x);
    float cos_theta = pow((1.0 - y), 1.0 / (exp + 1.0));
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;

    return Point3D(pu, pv, pw);
}
