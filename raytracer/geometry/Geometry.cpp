#include "Geometry.hpp"

// Constructors.
Geometry::Geometry() : material_ptr(NULL) {}

// Get/set material.
Material* Geometry::get_material() const {
    return material_ptr;
}

void Geometry::set_material(Material* mPtr) {
    material_ptr = mPtr;
}

// Add object
void Geometry::add_object(Geometry* object_ptr) {
    // Do nothing.
}