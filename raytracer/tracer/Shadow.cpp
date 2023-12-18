#include "Shadow.hpp"

// Constructors.
Shadow::Shadow(World *world_ptr) : Tracer(world_ptr) {}

// Trace ray.
RGBColor Shadow::trace_ray(const Ray ray, const int depth) const {
  ShadeInfo sinfo(world_ptr->hit_objects(ray));
  sinfo.enable_shadows = true;
  if (sinfo.hit) 
    return ray.w * sinfo.material_ptr->shade(sinfo);
  
  else
    return world_ptr->bg_color;
}