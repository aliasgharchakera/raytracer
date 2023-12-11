#include "ShadeInfo.hpp"

// Constructors.
ShadeInfo::ShadeInfo(const World &wr) : hit(false), material_ptr(NULL), hit_point(), normal(), ray(), depth(0), t(0), w(&wr) {}

// Copy constructor.
ShadeInfo::ShadeInfo(const ShadeInfo &sr) : hit(sr.hit), material_ptr(sr.material_ptr), hit_point(sr.hit_point), normal(sr.normal), ray(sr.ray), depth(sr.depth), t(sr.t), w(sr.w) {}