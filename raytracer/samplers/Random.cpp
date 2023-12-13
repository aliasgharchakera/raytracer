#include "Random.hpp"

// Constructors.
Random::Random(Camera *c_ptr, ViewPlane *v_ptr, int num) : Sampler(c_ptr, v_ptr), n(num) {}

// Copy constructor and assignment operator.
Random::Random(const Random &other) : Sampler(other), n(other.n) {}

Random &Random::operator=(const Random &other) {
  if (this == &other) {
    return *this;
  }

  Sampler::operator=(other);
  n = other.n;
  return *this;
}

// Shoot n rays of weight 1/n through the pixel.
std::vector<Ray> Random::get_rays(int px, int py) const {
    std::vector<Ray> rays;
    Ray ray;

    // Calculate the width of each pixel in the x and y directions.
    float xwidth = (viewplane_ptr->bottom_right.x - viewplane_ptr->top_left.x) / viewplane_ptr->hres;
    float ywidth = (viewplane_ptr->bottom_right.y - viewplane_ptr->top_left.y) / viewplane_ptr->vres;

    // Calculate the center of the pixel.
    float x = viewplane_ptr->top_left.x + xwidth * px + xwidth / 2;
    float y = viewplane_ptr->top_left.y + ywidth * py + ywidth / 2;
    float z = viewplane_ptr->top_left.z;

    // Set the ray weight.
    ray.w = 1.0 / n;

    // Shoot n rays through the pixel.
    for (int i = 0; i < n; i++) {
        // Set the ray origin randomly in the pixel ranging from (x - xwidth/2, y - ywidth/2, z) to (x + xwidth/2, y + ywidth/2, z).
        ray.o = Point3D(x + xwidth * (rand() / (RAND_MAX + 1.0) - 0.5), y + ywidth * (rand() / (RAND_MAX + 1.0) - 0.5), z);
        ray.d = camera_ptr->get_direction(ray.o);
        rays.push_back(ray);
    }

    return rays;
}