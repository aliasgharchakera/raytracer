
/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/

#include "../cameras/Perspective.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../lights/Point.hpp"
#include "../lights/Ambient.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Phong.hpp"


#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"
#include "../samplers/Random.hpp"
#include "../samplers/Jittered.hpp"

#include "../utilities/Constants.hpp"

#include "../world/World.hpp"

#include "../acceleration/BVH.hpp"

#include "../tracer/Basic.hpp"
#include "../tracer/Shadow.hpp"

void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

  // Background color.  
  bg_color = black;
  
  // Camera and sampler.
  set_camera(new Perspective(0, 0, 20));
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

  Sphere* sphere_ptr = new Sphere(Point3D(-3, 2, 0), 5); 
  // sphere_ptr->set_material(sphere_matte_ptr);
  sphere_ptr->set_material(sphere_phong_ptr);
  add_geometry(sphere_ptr);
  
  // triangle
  Point3D a(2.5, -5, 1); 
  Point3D b(14, -1, 0); 
  Point3D c(8.5, 5, 0.5); 
  Triangle* triangle_ptr = new Triangle(a, b, c);
  triangle_ptr->set_material(new Cosine(blue));
  add_geometry(triangle_ptr);

  // plane
  Plane* plane_ptr = new Plane(Point3D(0,1,0), Vector3D(0, 10, 2)); 
  plane_ptr->set_material(new Cosine(green));  // green
  add_geometry(plane_ptr);

  // light
  Point* light_ptr = new Point(Point3D(-10, 10, 10));
  add_light(light_ptr);

  Point* light_ptr2 = new Point(Point3D(-10, 10, -10));
  add_light(light_ptr2);

  // Ambient light.
  ambient_ptr = new Ambient(white, 0.25);

  // add_object("monke.obj",sphere_phong_ptr);
  set_acceleration(new BVH(this));

  // set_tracer
  set_tracer(new Shadow(this));

  printf("Build My Hello World!\n");
}
