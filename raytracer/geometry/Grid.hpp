#pragma once
#include "Compound.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"

//---------------------------------------------------------------------- class Grid

class Grid : public Compound
{
public:
	Grid(void);

	Grid(const Grid &rg);

	Grid &
	operator=(const Grid &rhs);

	virtual ~Grid(void);

	virtual BBox
	getBBox(void);

	virtual bool
	hit(const Ray &ray, float &tmin, ShadeInfo &sinfo) const;

	void
	setup_cells(void);

	void
	reverse_mesh_normals(void);

private:
	std::vector<Geometry *> cells; // grid of cells
	int nx, ny, nz;				   // number of cells in the x, y, and z directions
	BBox bbox;					   // bounding box

	Point3D
	find_min_bounds(void);

	Point3D
	find_max_bounds(void);

	void
	read_ply_file(char *file_name, const int triangle_type);

	void
	compute_mesh_normals(void);
};
