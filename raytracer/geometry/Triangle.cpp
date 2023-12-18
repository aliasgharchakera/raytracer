#include "Triangle.hpp"

// Constructors.
Triangle::Triangle() : v0(Point3D()), v1(Point3D()), v2(Point3D()) {}

Triangle::Triangle(const Point3D &p0, const Point3D &p1, const Point3D &p2)
    : v0(p0), v1(p1), v2(p2) {}

// Copy constructor and assignment operator.
Triangle::Triangle(const Triangle &object)
    : Geometry(object), v0(object.v0), v1(object.v1), v2(object.v2) {}

Triangle &Triangle::operator=(const Triangle &rhs) {
  if (this == &rhs) {
    return *this;
  }

  Geometry::operator=(rhs);
  v0 = rhs.v0;
  v1 = rhs.v1;
  v2 = rhs.v2;

  return *this;
}

// String representation.
std::string Triangle::to_string() const {
  return "Triangle";
}

// Ray intersection. Set t and sinfo as per intersection with this object.
bool Triangle::hit(const Ray &ray, float &t, ShadeInfo &s) const {
  
 	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x; 
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, u = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * u);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
	 	return (false);
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0 )
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * u;
	double curr_t = e3 * inv_denom;
	
	if (curr_t < kEpsilon)  
		return (false);
					
	t = curr_t;
	s.hit_point = ray.o + curr_t * ray.d;
	s.ray = ray;	
	Vector3D normal = (v1 - v0) ^ (v2 - v0);  
	normal.normalize();
	s.normal = normal;
	s.material_ptr = material_ptr;
	s.t = t;
	s.hit = true;
	
	return true;	
}

// Check if shadow ray hits the triangle.
bool Triangle::shadow_hit(const Ray &ray, float &tmin) const {
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x; 
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, u = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * u);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
		return false;
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0 )
		return false;
	
	if (beta + gamma > 1.0)
		return false;
			
	double e3 = a * p - b * r + d * u;
	double curr_t = e3 * inv_denom;
	
	if (curr_t < kEpsilon)  
		return false;
					
	tmin = curr_t;
	return true;
}

// Get bounding box.
BBox Triangle::getBBox() const {
  return BBox(min(min(v0, v1), v2), max(max(v0, v1), v2));
}

// Get center
Point3D Triangle::getCenter() const {
	Point3D centroid((v0.x + v1.x + v2.x)/3, (v0.y + v1.y + v2.y)/3, (v0.z + v1.z + v2.z)/3);
  return centroid;
}