#include "Simple.hpp"

// Constructors.
Simple::Simple() : Sampler() {}

Simple::Simple(Camera* c_ptr, ViewPlane* v_ptr) : Sampler(c_ptr, v_ptr) {}

// Copy constructor and assignment operator.
Simple::Simple(const Simple& other) : Sampler(other) {}

Simple& Simple::operator=(const Simple& other) {
  if (this == &other) {
    return *this;
  }

  Sampler::operator=(other);
  return *this;
}

//REVIEW check this function
// Shoot a ray of weight 1 through the center of the pixel.
std::vector<Ray> Simple::get_rays(int px, int py) const {
  std::vector<Ray> rays;

  // Calculate the center of the pixel.
  Point2D pixel_center = view_plane_ptr->get_pixel_center(px, py);

  // Shoot a ray through the center of the pixel.
  Ray ray = camera_ptr->get_ray(pixel_center.x, pixel_center.y);
  ray.weight = 1.0;

  rays.push_back(ray);
  return rays;
}
