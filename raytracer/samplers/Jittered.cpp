#include "Jittered.hpp"

// Constructors.
Jittered::Jittered(Camera *c_ptr, ViewPlane *v_ptr, int num) : Sampler(c_ptr, v_ptr), n(num) {}

// Copy constructor and assignment operator.
Jittered::Jittered(const Jittered &other) : Sampler(other), n(other.n) {}

Jittered &Jittered::operator=(const Jittered &other) {
  if (this == &other) {
    return *this;
  }

  Sampler::operator=(other);
  return *this;
}

// Shoot n^2 rays of weight 1/n^2 randomly through n x n subpixels of the pixel.
std::vector<Ray> Jittered::get_rays(int px, int py) const {
  std::vector<Ray> rays;
  Ray ray;

  // Calculate the width of each pixel in the x and y directions.
  float xwidth = (viewplane_ptr->bottom_right.x - viewplane_ptr->top_left.x) / viewplane_ptr->hres;
  float ywidth = (viewplane_ptr->bottom_right.y - viewplane_ptr->top_left.y) / viewplane_ptr->vres;

  // Calculate the width of each subpixel in the x and y directions.
  float subxwidth = xwidth / n;
  float subywidth = ywidth / n;

  // Calculate the center of the pixel.
  float x = viewplane_ptr->top_left.x + xwidth * px + xwidth / 2;
  float y = viewplane_ptr->top_left.y + ywidth * py + ywidth / 2;
  float z = viewplane_ptr->top_left.z;

  // Set the ray weight.
  ray.w = 1.0 / (n * n);

  // Shoot n^2 rays randomly through the subpixels.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { 
      // Set the ray origin randomly in the subpixel ranging from (x - xwidth/2, y - ywidth/2, z) to (x + xwidth/2, y + ywidth/2, z).
      ray.o = Point3D(x + xwidth * (rand() / (RAND_MAX + 1.0) - 0.5) + subxwidth * (rand() / (RAND_MAX + 1.0) - 0.5), y + ywidth * (rand() / (RAND_MAX + 1.0) - 0.5) + subywidth * (rand() / (RAND_MAX + 1.0) - 0.5), z);
      ray.d = camera_ptr->get_direction(ray.o);
      rays.push_back(ray);
    }
  }

  return rays;
}
