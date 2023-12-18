
#include <iostream>
#include <vector>

#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"
#include "Compound.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"

/**
   Courtesy Kevin Suffern.
*/

// ----------------------------------------------------------------  default constructor

Compound::Compound(void)
	: Geometry()
{
}

std::string Compound::to_string() const
{
	return "Hello World";
}

// ---------------------------------------------------------------- destructor

Compound::~Compound(void)
{
	delete_objects();
}

// ---------------------------------------------------------------- add_object

void Compound::add_object(Geometry *object_ptr)
{
	objects.push_back(object_ptr);
}

//------------------------------------------------------------------ set_material
// sets the same material on all objects

void Compound::set_material(Material *material_ptr)
{
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}

//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty

void Compound::delete_objects(void)
{
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase(objects.begin(), objects.end());
}

//------------------------------------------------------------------ hit

bool Compound::hit(const Ray &ray, double &tmin, ShadeInfo &sinfo) const
{
	float t;
	Vector3D normal;
	Point3D local_hit_point;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects = objects.size();

for (int j = 0; j < num_objects; j++)
  if (objects[j]->hit(ray, t, sinfo) && (t < tmin))
  {
    hit = true;
    tmin = t;
    material_ptr = objects[j]->get_material(); // lhs is GeometricObject::material_ptr
    normal = sinfo.normal;
    local_hit_point = sinfo.hit_point;
  }

	if (hit)
	{
		sinfo.t = tmin;
		sinfo.normal = normal;
		sinfo.hit_point = local_hit_point;
	}

	return (hit);
}

bool Compound::shadow_hit(const Ray &ray, float &t) const
{
	return false;
}

BBox Compound::getBBox() const
{
	return BBox();
}

// Get center
Point3D Compound::getCenter() const
{
  return Point3D();
}