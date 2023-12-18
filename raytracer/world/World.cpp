#include "World.hpp"
#include <array>

// Constructors.
World::World() : vplane(ViewPlane()), bg_color(RGBColor()), geometry(), camera_ptr(NULL), sampler_ptr(NULL), ambient_ptr(new Ambient(white, 0.25)), acceleration_ptr(NULL), tracer_ptr(new Basic(this)) {}

// Destructor.
World::~World() {
  if (camera_ptr) {
    delete camera_ptr;
    camera_ptr = NULL;
  }

  if (sampler_ptr) {
    delete sampler_ptr;
    sampler_ptr = NULL;
  }

  for (auto g : geometry) {
    delete g;
    g = NULL;
  }

  if (acceleration_ptr) {
    delete acceleration_ptr;
    acceleration_ptr = NULL;
  }
}

// Add to the scene.
void World::add_geometry(Geometry *geom_ptr) {
  geometry.push_back(geom_ptr);
}

void World::add_light(Light *light_ptr) {
  lights.push_back(light_ptr);
}

void World::set_camera(Camera *c_ptr) {
  camera_ptr = c_ptr;
}

// set acceleration structure
void World::set_acceleration(Acceleration* acceleration_ptr){
  this->acceleration_ptr = acceleration_ptr;
}

// set tracer
void World::set_tracer(Tracer* tracer_ptr){
  this->tracer_ptr = tracer_ptr;
}

// Checks if the given ray is shadowed by any geometry in the scene.
bool World::is_shadowed(const Ray &ray, const ShadeInfo &sinfo) const {
  float t;
  int num_objects = geometry.size();

  for (int i = 0; i < num_objects; i++) {
    if (geometry[i]->shadow_hit(ray, t) && (t < sinfo.t)) {
      return true;
    }
  }

  return false;
}

// Returns appropriate shading information corresponding to intersection of
// the ray with the scene geometry.
ShadeInfo World::hit_objects(const Ray &ray) {

  if (acceleration_ptr != NULL)
    return acceleration_ptr->hit(ray);
  ShadeInfo sinfo(*this), sinfo_min(*this);
  float t;
  float tmin = std::numeric_limits<float>::max();
  int num_objects = geometry.size();

  for (int i = 0; i < num_objects; i++) {
    if (geometry[i]->hit(ray, t, sinfo) && (t < tmin)) {
      tmin = t;
      sinfo_min = sinfo;
    }
  }

  return sinfo_min;
}

// add an object file
void World::add_object(const char *path, Material *mPtr){
  std::vector<int> vertex_indices, normal_indices;
    std::vector<Point3D> vertices;
    std::vector<Vector3D> normals;

    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        std::cout << "Cannot open file " << path << "\n";
        return;
    }

    while (1)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v") == 0)
        {
            Point3D vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            Vector3D normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            std::string v1, v2, v3;
            int vertexIndex[3], normalIndex[3];
            fscanf(file, "%d/%*d/%d %d/%*d/%d %d/%*d/%d\n", &vertexIndex[0],
                   &normalIndex[0], &vertexIndex[1], &normalIndex[1],
                   &vertexIndex[2], &normalIndex[2]);
            vertex_indices.push_back(vertexIndex[0]);
            vertex_indices.push_back(vertexIndex[1]);
            vertex_indices.push_back(vertexIndex[2]);

            normal_indices.push_back(normalIndex[0]);
            normal_indices.push_back(normalIndex[1]);
            normal_indices.push_back(normalIndex[2]);
        }
    }

    // now we have four arrays 1) Vertices 2) Normals 3) Vertex Indices 4) Normal Indices
    // to get faces we need to iterate over vertex indices and normal indices and create triangles
    for (int i = 0; i < vertex_indices.size(); i += 3)
    {
        Triangle *triangle = new Triangle(vertices[vertex_indices[i] - 1],
                                          vertices[vertex_indices[i + 1] - 1],
                                          vertices[vertex_indices[i + 2] - 1]);
        triangle->set_material(mPtr);
        // triangle->set_normal(normals[normal_indices[i] - 1],
        //                      normals[normal_indices[i + 1] - 1],
        //                      normals[normal_indices[i + 2] - 1]);
        add_geometry(triangle);
    }
}

void World::add_mesh(std::string filename, Material* material_ptr, Point3D bottom, Point3D top) {

    happly::PLYData plyIn(filename);
    std::vector<std::array<double, 3>> vertices = plyIn.getVertexPositions();
    std::vector<std::vector<size_t>> faces = plyIn.getFaceIndices<size_t>();
    std::vector<Point3D> points;

    Point3D modelMin(vertices[0][0], vertices[0][1], vertices[0][2]);
    Point3D modelMax(vertices[0][0], vertices[0][1], vertices[0][2]);
    /*std::cout << "vertices stores " << int(vertices.size()) << " numbers.\n";
    std::cout << "vertices " << vPos[1][0] << " numbers.\n";
    std::cout << "fInd stores " << int(fInd.size()) << " numbers.\n";
    std::cout << "vertices " << int(fInd[0].size()) << " numbers.\n";
    std::cout << modelMin.to_string()<<endl;*/

    for (const auto& i : vertices) {
        //std::cout << "vertices " << int(point[0])<<int(point[1])<<int(point[2]) << " numbers.\n";
        Point3D obj(i[0], i[1], i[2]);
        points.push_back(obj);
        modelMin = min(modelMin, obj);
        modelMax = max(modelMax, obj);
    }

    for (auto& p: points) {
        p = Point3D::interpolate(modelMin, modelMax, p, bottom, top);
    }

    for (const auto& f : faces) {
      //std::cout << points[f[0]].to_string() << std::endl;

      Triangle* mesh_triangle = new Triangle(points[f[0]], points[f[1]], points[f[2]]);
      mesh_triangle->set_material(material_ptr);
      add_geometry(mesh_triangle);
    }
    //delete material_ptr;

}

