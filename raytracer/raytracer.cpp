#include <iostream>
#include <time.h>

#include "materials/Cosine.hpp"

#include "samplers/Sampler.hpp"

#include "utilities/Image.hpp"
#include "utilities/RGBColor.hpp"
#include "utilities/Ray.hpp"
#include "utilities/ShadeInfo.hpp"

#include "world/World.hpp"
#include "world/ViewPlane.hpp"

#include "acceleration/BVH.hpp"

int main(int argc, char **argv) {
  World world;
  clock_t start = clock();

  world.build();

  if (world.acceleration_ptr)
    std::cout << "Using acceleration structure.\n";
  else
    std::cout << "Without using acceleration structure.\n";

  Sampler *sampler = world.sampler_ptr;
  ViewPlane &viewplane = world.vplane;
  Image image(viewplane);

  clock_t end = clock();
  double elapsed = double(end - start)/CLOCKS_PER_SEC;
  std::cout << "Overhead time: " << elapsed << " seconds.\n";
  
  start = clock();
  std::vector<Ray> rays;
  for (int x = 0; x < viewplane.hres; x++) {   // across.
    for (int y = 0; y < viewplane.vres; y++) { // down.
      // Get rays for the pixel from the sampler. The pixel color is the
      // weighted sum of the shades for each ray.
      RGBColor pixel_color(0);
      rays = sampler->get_rays(x, y);
      for (const auto &ray : rays) {
        float weight = ray.w; // ray weight for the pixel.
        ShadeInfo sinfo = world.hit_objects(ray);
        // if (sinfo.hit) {
        //   pixel_color += weight * sinfo.material_ptr->shade(sinfo);
        // }
  	    // else {
        //   pixel_color += weight * world.bg_color;
        // }
        pixel_color += world.tracer_ptr->trace_ray(ray, 0);
      }
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
      // std::cout << pixel_color << "\n";
    }
  }
  end = clock();
  elapsed = double(end - start)/CLOCKS_PER_SEC;
  std::cout << "Raytracing time: " << elapsed << " seconds.\n";

  // Write image to file.
  image.write_ppm("scene.ppm");

  std::cout << "Wrote image.\n";
  
  return 0;
}
