#include "Material.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

class Matte : public Material {

private:
  // Ambient color.
  RGBColor ambient_color;

  // Diffuse color.
  RGBColor diffuse_color;

  // Ambient coefficient.
  float ka;

  // Diffuse coefficient.
  float kd;

public:
  // Constructors.
  Matte();
  Matte(float c);
  Matte(float r, float g, float b);
  Matte(const RGBColor &c);

  // Copy constuctor and assignment operator.
  Matte(const Matte &other);
  Matte &operator=(const Matte &other);

  // Destructor.
  ~Matte() = default;

  // Get/set ambient color.
  RGBColor get_ambient_color() const;
  void set_ambient_color(const RGBColor &c);

  // Get/set diffuse color.
  RGBColor get_diffuse_color() const;
  void set_diffuse_color(const RGBColor &c);

  // Get/set diffuse coefficient.
  float get_kd() const;
  void set_kd(float k);

  // Get/set ambient coefficient.
  float get_ka() const;
  void set_ka(float k);

  // shade function
  virtual RGBColor shade(const ShadeInfo &sinfo) const override;

  // Get normal.
  virtual Vector3D get_normal(const ShadeInfo &sinfo) const override;
};