#include "Lambertian.hpp"

// Constructors.
Lambertian::Lambertian() : BRDF(), kd(0), cd(0) {}

Lambertian::Lambertian(const Lambertian& l) : BRDF(l), kd(l.kd), cd(l.cd) {}

Lambertian* Lambertian::clone() const {
    return new Lambertian(*this);
}

// f.
RGBColor Lambertian::f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const {
    return kd * cd * invPI;
}

// sample_f.
RGBColor Lambertian::sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const {
    // Generate random sample on hemisphere that is oriented along normal.
    return (kd * cd * invPI);
}

RGBColor Lambertian::sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi, float& pdf) const {
    // Generate random sample on hemisphere that is oriented along normal.
    Vector3D w = sinfo.normal;
    Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
    v.normalize();
    Vector3D u = v ^ w;

    Point3D sp = BRDF::sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;
    wi.normalize();

    pdf = sinfo.normal * wi * invPI;

    return (kd * cd * invPI);
}

// rho.
RGBColor Lambertian::rho(const ShadeInfo& sinfo, const Vector3D& wo) const {
    return (kd * cd);
}

// Setters.
void Lambertian::set_ka(const float k) {
    kd = k;
}

void Lambertian::set_kd(const float k) {
    kd = k;
}

void Lambertian::set_cd(const RGBColor& c) {
    cd = c;
}

void Lambertian::set_cd(const float r, const float g, const float b) {
    cd.r = r;
    cd.g = g;
    cd.b = b;
}

void Lambertian::set_cd(const float c) {
    cd.r = c;
    cd.g = c;
    cd.b = c;
}