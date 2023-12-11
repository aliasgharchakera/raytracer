#include "ViewPlane.hpp"

// Constructors.
ViewPlane::ViewPlane() : top_left(Point3D(-320, 240, 0)), bottom_right(Point3D(320, -240, 0)), normal(Vector3D(0, 0, 1)), hres(640), vres(480) {}

// Get/set resolution.
int ViewPlane::get_hres() const {
  return hres;
}

void ViewPlane::set_hres(int res) {
  hres = res;
}

int ViewPlane::get_vres() const {
  return vres;
}

void ViewPlane::set_vres(int res) {
  vres = res;
}
