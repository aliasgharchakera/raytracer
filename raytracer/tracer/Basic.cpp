#include "Basic.hpp"

// Constructors.
Basic::Basic(World *world_ptr) : Tracer(world_ptr) {}

// Trace ray.
RGBColor Basic::trace_ray(const Ray ray, const int depth) const {
  ShadeInfo sinfo(world_ptr->hit_objects(ray));
  if (sinfo.hit) 
    return ray.w * sinfo.material_ptr->shade(sinfo);
  
  else
    return world_ptr->bg_color;
}