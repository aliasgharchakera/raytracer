
#include <iostream>
#include <math.h>
#include "../cameras/Perspective.hpp"
#include "../geometry/Sphere.hpp"
#include "../materials/Cosine.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"

#include "../acceleration/BVH.hpp"
#include "../geometry/Grid.hpp"

#include "../tracer/Basic.hpp"
#include "../tracer/Shadow.hpp"

inline int
rand_int(void)
{
  return (rand());
}

inline float
rand_float(void)
{
  return ((float)rand_int() * invRAND_MAX);
}

void World::build(void)
{
  // View plane  .
  vplane.top_left.x = -1;
  vplane.top_left.y = 1;
  vplane.top_left.z = 1;
  vplane.bottom_right.x = 1;
  vplane.bottom_right.y = -1;
  vplane.bottom_right.z = 1;

  // set resolution of screen here
  vplane.hres = 400;
  vplane.vres = 400;

  bg_color = white;

  // Camera and sampler.
  set_camera(new Perspective(0, 0, 40));
  sampler_ptr = new Jittered(camera_ptr, &vplane, 5);

  Grid *grid_ptr = new Grid;

  // set number of primitives here
  int n = 100000;
  int upper = 20;
  int lower = -20;

  float volume = 0.1 / n;
  float radius = std::pow(0.75 * volume / 3.14159, 0.333333);

  for (int i = 0; i < n; i++)
  {
    float a = ((float)rand() / (RAND_MAX));
    float b = ((float)rand() / (RAND_MAX));
    float c = ((float)rand() / (RAND_MAX));

    int x = (rand() % (upper - lower + 1)) + lower;
    int y = (rand() % (upper - lower + 1)) + lower;
    Sphere *sphere_ptr = new Sphere(Point3D(1.0 - 2.0 * rand_float(),
                                            1.0 - 2.0 * rand_float(),
                                            1.0 - 2.0 * rand_float()),
                                    radius);

    sphere_ptr->set_material(new Cosine(RGBColor(a, b, c)));
    grid_ptr->add_object(sphere_ptr);
  }

  grid_ptr->setup_cells();

  add_geometry(grid_ptr);
}
