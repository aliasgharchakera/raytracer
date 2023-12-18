
/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/

#include "../cameras/Perspective.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../geometry/Grid.hpp"

#include "../lights/Point.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Phong.hpp"

#include "../tracer/Basic.hpp"
#include "../tracer/Shadow.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"
#include "../samplers/Random.hpp"
#include "../samplers/Jittered.hpp"

#include "../utilities/Constants.hpp"

#include "../world/World.hpp"

void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -1;
  vplane.top_left.y = 2;
  vplane.top_left.z = 2;
  vplane.bottom_right.x = 1;
  vplane.bottom_right.y = -2;
  vplane.bottom_right.z = 2;
  vplane.hres = 400;
  vplane.vres = 400;

  // Background color.  
  bg_color = black;
  
  // Camera and sampler.
  set_camera(new Perspective(0, 0, 10));
  sampler_ptr = new Jittered(camera_ptr, &vplane, 5);
	
  // sphere
  Matte* sphere_matte_ptr = new Matte(red);
  sphere_matte_ptr->set_ka(0.25);
  sphere_matte_ptr->set_kd(0.65);
  // sphere_matte_ptr->set_cd(1, 0, 0);
  // sphere_matte_ptr->set_cd(1, 1, 0);
  // sphere_matte_ptr->set_ka(0.1);
  // sphere_matte_ptr->set_kd(0.1);

  // phong sphere
  Phong* sphere_phong_ptr = new Phong(red);
  sphere_phong_ptr->set_ka(0.25);
  sphere_phong_ptr->set_kd(0.75);
  sphere_phong_ptr->set_ks(0.9);
  sphere_phong_ptr->set_exp(10);

  // light
  Point* light_ptr = new Point(Point3D(0, 0, 15));
  add_light(light_ptr);

  // Point* light_ptr2 = new Point(Point3D(-10, 10, -10));
  // add_light(light_ptr2);

  Grid* grid_ptr = new Grid;

	// add_mesh("3dmodels/finalskull.ply", sphere_phong_ptr, Point3D(-80.0, -60, -10), Point3D(-45, 0, 5), grid_ptr);

  add_object("3dmodels/babar_azam.obj", sphere_phong_ptr, grid_ptr);
  grid_ptr->setup_cells();
  add_geometry(grid_ptr);

  set_tracer(new Shadow(this));

  printf("My Hello World!\n");
}
