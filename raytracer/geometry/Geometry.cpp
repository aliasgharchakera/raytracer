#include "Geometry.hpp"

Material* Geometry::get_material() const {
    return material_ptr;
}

void Geometry::set_material(Material* mPtr) {
    material_ptr = mPtr;
}
