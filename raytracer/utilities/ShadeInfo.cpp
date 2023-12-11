#include "ShadeInfo.hpp"

// Constructors.
ShadeInfo::ShadeInfo(const World &wr) : hit(false), material_ptr(NULL), hit_point(), normal(), ray(), depth(0), t(0), w(&wr) {}