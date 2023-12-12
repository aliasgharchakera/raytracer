
#include "Image.hpp"
#include <fstream>

// Constructors.
Image::Image(int hres, int vres) : hres(hres), vres(vres) {
  colors = new RGBColor*[hres];
  for (int i = 0; i < hres; i++) {
    colors[i] = new RGBColor[vres];
  }
}

Image::Image(const ViewPlane& vp) : Image(vp.hres, vp.vres) {}

// Destructor.
Image::~Image() {
  for (int i = 0; i < hres; i++) {
    delete[] colors[i];
  }
  delete[] colors;
}

// Set pixel color. Convert to integer values.
void Image::set_pixel(int x, int y, const RGBColor& color) {
  colors[x][y] = color;
}

// Write image to file in PPM format.
//REVIEW: check write_ppm
void Image::write_ppm(std::string path) const {
  std::ofstream file(path);
  if (file.is_open()) {
    file << "P3\n";
    file << hres << " " << vres << "\n";
    file << "255\n";
    for (int y = 0; y < vres; y++) {
      for (int x = 0; x < hres; x++) {
        const RGBColor& color = colors[x][y];
        file << static_cast<int>(color.r * 255) << " ";
        file << static_cast<int>(color.g * 255) << " ";
        file << static_cast<int>(color.b * 255) << " ";
      }
      file << "\n";
    }
    file.close();
  }
}
