#include <vector>

#include "../geometry/Geometry.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Point3D.hpp"

class KDNode {
 public:
  KDNode* left;
  KDNode* right;
  std::vector<Geometry*> primitives;
  BBox bb;

 public:
  KDNode();

  explicit KDNode(std::vector<Geometry*> _primitives);

  KDNode(std::vector<Geometry*> _primitives, BBox _bb);

  void add_primitive(Geometry* primitive);

  void add_primitive(Geometry* primitive, BBox new_bb);

  std::vector<Geometry*> get_primitives() const;

  ~KDNode();

  static void build_kd_tree(KDNode* node);
};
