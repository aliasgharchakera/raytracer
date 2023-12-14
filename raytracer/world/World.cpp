#include "World.hpp"

// Constructors.
World::World() : vplane(ViewPlane()), bg_color(RGBColor()), geometry(), camera_ptr(NULL), sampler_ptr(NULL) {}

// Destructor.
World::~World() {
  if (camera_ptr) {
    delete camera_ptr;
    camera_ptr = NULL;
  }

  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }

  for (auto g : geometry) {
    delete g;
    g = NULL;
  }
}

// Add to the scene.
void World::add_geometry(Geometry *geom_ptr) {
  geometry.push_back(geom_ptr);
}

void World::add_light(Light *light_ptr) {
  lights.push_back(light_ptr);
}

void World::set_camera(Camera *c_ptr) {
  camera_ptr = c_ptr;
}

// Checks if the given ray is shadowed by any geometry in the scene.
bool World::is_shadowed(const Ray &ray, const ShadeInfo &sinfo) const {
  float t;
  int num_objects = geometry.size();

  for (int i = 0; i < num_objects; i++) {
    if (geometry[i]->shadow_hit(ray, t) && (t < sinfo.t)) {
      return true;
    }
  }

  return false;
}

// Returns appropriate shading information corresponding to intersection of
// the ray with the scene geometry.
ShadeInfo World::hit_objects(const Ray &ray) {
  ShadeInfo sinfo(*this), sinfo_min(*this);
  float t;
  float tmin = std::numeric_limits<float>::max();
  int num_objects = geometry.size();

  for (int i = 0; i < num_objects; i++) {
    if (geometry[i]->hit(ray, t, sinfo) && (t < tmin)) {
      tmin = t;
      sinfo_min = sinfo;
    }
  }

  return sinfo_min;
}