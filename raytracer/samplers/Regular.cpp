#include "Regular.hpp"

// Constructors.
Regular::Regular(Camera *c_ptr, ViewPlane *v_ptr, int num) : Sampler(c_ptr, v_ptr), n(num) {}

// Copy constructor and assignment operator.
Regular::Regular(const Regular &other) : Sampler(other), n(other.n) {}

Regular &Regular::operator=(const Regular &other) {
  if (this == &other) {
    return *this;
  }

  Sampler::operator=(other);
  n = other.n;
  return *this;
}

// Shoot n^2 rays of weight 1/n^2 through n x n subpixels of the pixel.
std::vector<Ray> Regular::get_rays(int px, int py) const {
  std::vector<Ray> rays;
  Ray ray;

  // Calculate the width of each pixel in the x and y directions.
  float xwidth = (viewplane_ptr->bottom_right.x - viewplane_ptr->top_left.x) / viewplane_ptr->hres;
  float ywidth = (viewplane_ptr->bottom_right.y - viewplane_ptr->top_left.y) / viewplane_ptr->vres;

  // Calculate the width of each subpixel in the x and y directions.
  float xsubwidth = xwidth / n;
  float ysubwidth = ywidth / n;

  // Calculate the center of the pixel.
  float x = viewplane_ptr->top_left.x + xwidth * px + xwidth / 2;
  float y = viewplane_ptr->top_left.y + ywidth * py + ywidth / 2;
  float z = viewplane_ptr->top_left.z;

  // Set the ray weight.
  ray.w = 1.0 / (n * n);

  // Shoot n^2 rays through the subpixels.
  for (int i = 0; i < n; i++) {
    float xsub = x - xwidth / 2 + xsubwidth / 2 + xsubwidth * i;
    for (int j = 0; j < n; j++) {
      float ysub = y - ywidth / 2 + ysubwidth / 2 + ysubwidth * j;
			// Set the ray origin at the center of the subpixel.
      ray.o = Point3D(xsub, ysub, z);
      ray.d = camera_ptr->get_direction(Point3D(xsub, ysub, z));
      rays.push_back(ray);
    }
  }

  return rays;
}
