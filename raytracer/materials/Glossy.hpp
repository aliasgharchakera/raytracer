#include "Material.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

class Glossy : public Material{
  private:
    // Ambient color.
    RGBColor ambient_color;

    // Diffuse color.
    RGBColor diffuse_color;

    // Specular color.
    RGBColor specular_color;

    // Ambient coefficient.
    float ka;

    // Diffuse coefficient.
    float kd;

    // Specular coefficient.
    float ks;

    // Specular exponent.
    float exp;

    // Glossy coefficient.
    float gloss;

  public:

    // Constructors.
    Glossy();
    Glossy(float c);
    Glossy(float r, float g, float b);
    Glossy(const RGBColor &c);

    // Copy constuctor and assignment operator.
    Glossy(const Glossy &other);
    Glossy &operator=(const Glossy &other);

    // Destructor.
    ~Glossy() = default;

    // Get/set ambient color.
    RGBColor get_ambient_color() const;
    void set_ambient_color(const RGBColor &c);

    // Get/set diffuse color.
    RGBColor get_diffuse_color() const;
    void set_diffuse_color(const RGBColor &c);

    // Get/set specular color.
    RGBColor get_specular_color() const;
    void set_specular_color(const RGBColor &c);

    // Get/set diffuse coefficient.
    float get_kd() const;
    void set_kd(float k);

    // Get/set ambient coefficient.
    float get_ka() const;
    void set_ka(float k);

    // Get/set specular coefficient.
    float get_ks() const;
    void set_ks(float k);

    // Get/set specular exponent.
    float get_exp() const;
    void set_exp(float e);

    // Get/set glossy coefficient.
    float get_gloss() const;
    void set_gloss(float g);

    // Shade function.
    virtual RGBColor shade(const ShadeInfo &sinfo) const override;

    // Get normal.
    virtual Vector3D get_normal(const ShadeInfo &sinfo) const override;
};