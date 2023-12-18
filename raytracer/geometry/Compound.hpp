#include <iostream>
#include <vector>

#pragma once
#include "Geometry.hpp"

/**
   Courtesy Kevin Suffern.
*/

//-------------------------------------------------------------------------------- class Compound

class Compound : public Geometry
{
public:
	Compound(void);

	~Compound(void);

	virtual BBox
	getBBox(void) const;

	virtual void
	set_material(Material *material_ptr);

	virtual void
	add_object(Geometry *object_ptr);

	int
	get_num_objects(void);

	virtual bool
	hit(const Ray &ray, float &tmin, ShadeInfo &sinfo) const;

	virtual bool
	shadow_hit(const Ray &ray, float &t) const;

	virtual std::string to_string() const override;

  // Get center
  virtual Point3D getCenter() const override;

protected:
	std::vector<Geometry *> objects;

private:
	void
	delete_objects(void);
};

// ------------------------------------------------------------------------------- get_num_objects

inline int
Compound::get_num_objects(void)
{
	return (objects.size());
}
