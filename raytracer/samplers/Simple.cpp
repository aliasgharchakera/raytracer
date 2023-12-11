#include "Simple.hpp"

// Constructors.
Simple::Simple() : Sampler() {}

Simple::Simple(Camera* c_ptr, ViewPlane* v_ptr) {
  camera_ptr = c_ptr;
  viewplane_ptr = v_ptr;
}

// Copy constructor and assignment operator.
Simple::Simple(const Simple& other) : Sampler(other) {}

Simple& Simple::operator=(const Simple& other) {
  if (this == &other) {
    return *this;
  }

  camera_ptr = other.camera_ptr;
  viewplane_ptr = other.viewplane_ptr;
  return *this;
}


// Shoot a ray of weight 1 through the center of the pixel.
std::vector<Ray> Simple::get_rays(int px, int py) const {
  std::vector<Ray> rays;
  Ray ray;

  // Calculate the width of each pixel in the x and y directions.
  float xwidth = (viewplane_ptr->bottom_right.x - viewplane_ptr->top_left.x) / viewplane_ptr->hres;
  float ywidth = (viewplane_ptr->bottom_right.y - viewplane_ptr->top_left.y) / viewplane_ptr->vres;

  // Calculate the center of the pixel.
  float x = viewplane_ptr->top_left.x + xwidth * px + xwidth / 2;
  float y = viewplane_ptr->top_left.y + ywidth * py + ywidth / 2;
  float z = viewplane_ptr->top_left.z;

  // Set the ray weight, origin, and direction.
  ray.w = 1.0;
  ray.o = Point3D(x, y, z);
  ray.d = camera_ptr->get_direction(Point3D(x, y, z));

  rays.push_back(ray);
  return rays;
}
