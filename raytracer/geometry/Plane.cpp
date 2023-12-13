#include "Plane.hpp"

// Constructors.
Plane::Plane() : a(0, 0, 0), n(0, 1, 0) {}

Plane::Plane(const Point3D &pt, const Vector3D &n) : a(pt), n(n) {
  this->n.normalize();
}

// Copy constructor and assignment operator.
Plane::Plane(const Plane &object) : a(object.a), n(object.n) {}

Plane &Plane::operator=(const Plane &rhs) {
  if (this == &rhs) {
    return *this;
  }

  a = rhs.a;
  n = rhs.n;

  return *this;
}

// String representation.

std::string Plane::to_string() const {
  std::ostringstream oss;
  oss << "Plane(" << a.to_string() << ", " << n.to_string() << ")";
  return oss.str();
}

// Ray intersection. set t and sinfo as per intersection with this object.
bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const {
  float t_hit = (a - ray.o) * n / (ray.d * n); 
														
	if (t_hit > kEpsilon) {
		t = t_hit;
		s.normal = n;
		s.normal.normalize();
		s.hit_point = ray.o + t * ray.d;
		s.ray = ray;
		s.t = t;
    s.material_ptr = material_ptr;
    s.hit = true;
		
		return true;	
	}

	return false;
}

// Get bounding box.
BBox Plane::getBBox() const {
  return BBox();
}