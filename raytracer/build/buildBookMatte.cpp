#include "../cameras/Parallel.hpp"
#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../materials/Cosine.hpp"
#include "../samplers/Simple.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../lights/Ambient.hpp"
#include "../cameras/Perspective.hpp"
#include "../lights/Point.hpp"
#include "../materials/Matte.hpp"

void World::build(void) {
  vplane.set_hres(400);
  vplane.set_vres(400);
  bg_color = black;
  // tracer_ptr = new RayCast(this);
  Ambient* ambient_ptr = new Ambient;
  // ambient_ptr->scale_radiance(1.0); // default
  // set_ambient_light(ambient_ptr);
  set_camera(new Perspective(0,0,20));
  Point* light_ptr2 = new Point(Point3D(-10, 10, 10));
  add_light(light_ptr2);
  Matte* matte_ptr1 = new Matte;
  matte_ptr1->set_ka(0.25);
  matte_ptr1->set_kd(0.65);
  matte_ptr1->set_cd(1, 1, 0); // yellow
  Sphere* sphere_ptr1 = new Sphere(Point3D(10, -5, 0), 27);
  sphere_ptr1->set_material(matte_ptr1);
  add_geometry(sphere_ptr1);

}