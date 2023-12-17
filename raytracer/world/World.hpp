#pragma once

/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/

#include <vector>
#include <cstring>

#include "../acceleration/Acceleration.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../geometry/Geometry.hpp"
#include "../geometry/Triangle.hpp"
#include "../cameras/Camera.hpp"
#include "../samplers/Sampler.hpp"
#include "../materials/Material.hpp"
#include "../lights/Light.hpp"

#include "ViewPlane.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;

class World {
public:
  ViewPlane vplane;
  RGBColor bg_color;
  std::vector<Geometry *> geometry;
  std::vector<Light *> lights;
  Camera *camera_ptr;
  Sampler *sampler_ptr;
  Light* ambient_ptr;
  Acceleration* acceleration_ptr;

public:
  // Constructors.
  World(); // initialize members.

  // Destructor.
  ~World(); // free memory.

  // Add to the scene.
  void add_geometry(Geometry *geom_ptr);
  void add_light(Light *light_ptr);
  void set_camera(Camera *c_ptr);
  void set_acceleration(Acceleration* acceleration_ptr);

  // Checks if the given ray is shadowed by any geometry in the scene.
  virtual bool is_shadowed(const Ray &ray, const ShadeInfo &sinfo) const;

  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build();

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  ShadeInfo hit_objects(const Ray &ray);

  // add object
  void add_object(const char *path, Material *mPtr);
};
