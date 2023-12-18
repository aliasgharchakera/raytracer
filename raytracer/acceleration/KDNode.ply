#include "KDNode.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

KDNode::KDNode()
    : left{NULL}, right{NULL}, primitives{std::vector<Geometry*>()} {
  // nothing else to do
}

//REVIEW the getBBox here returns nothing
KDNode::KDNode(std::vector<Geometry*> _primitives)
    : primitives{_primitives}, bb{BBox()} {
  // compute overall bounding box
  for (Geometry* primitive : primitives) {
    bb = bb.merge(primitive->getBBox());
  }
}

KDNode::KDNode(std::vector<Geometry*> _primitives, BBox _bb)
    : primitives{_primitives}, bb{_bb} {
  // nothing else to do
}

void KDNode::add_primitive(Geometry* primitive) {
  add_primitive(primitive, bb.merge(primitive->getBBox()));
}

void KDNode::add_primitive(Geometry* primitive, BBox new_bb) {
  primitives.push_back(primitive);
  bb = new_bb;
}

void KDNode::build_kd_tree(KDNode* node) {
  // based on http://www.flipcode.com/archives/
  // Raytracing_Topics_Techniques-Part_7_Kd-Trees_and_More_Speed.shtml

  BBox current_bb = node->bb;

  // this should eventually split smarter than just half of the longest axis,
  // but for now it will have to do
  int splitaxis = current_bb.max_axis();
  Vector3D lengths = current_bb.most_positive - current_bb.most_negative;

  double axislength;
  if (splitaxis == 0) {
    axislength = lengths.x;
  } else if (splitaxis == 1) {
    axislength = lengths.y;
  } else {  // z axis
    axislength = lengths.z;
  }

  // condition to stop splitting
  if (node->primitives.size() < 3 || axislength < 0.01) {
    return;
  }

  // offset from current_bb.most_negative, along splitaxis
  double splitoffset = axislength / 2;

  // compute midpoints for bounding box, where each half will be a new node

  Point3D midpoint_1 = current_bb.most_negative;
  Point3D midpoint_2 = current_bb.most_positive;

  //TODO check these values
  if (splitaxis == 0) {
    midpoint_1.x += splitoffset;
    midpoint_2.x -= splitoffset;
  } else if (splitaxis == 1) {
    midpoint_1.y += splitoffset;
    midpoint_2.y -= splitoffset;
  } else if (splitaxis == 2) {
    midpoint_1.z += splitoffset;
    midpoint_2.z -= splitoffset;
  }

  BBox splitboxleft = current_bb;
  splitboxleft.most_positive = midpoint_2;

  BBox splitboxright = current_bb;
  splitboxright.most_negative = midpoint_1;

  node->left = new KDNode();
  node->right = new KDNode();

  // put primitives into appropriate bounding box, duplicating if necessary

  for (Geometry* primitive : node->primitives) {
    if (splitboxleft.intersect(primitive->getBBox())) {
      node->left->add_primitive(primitive, splitboxleft);
    }
    if (splitboxright.intersect(primitive->getBBox())) {
      node->right->add_primitive(primitive, splitboxright);
    }
  }

  // deallocate space from vector because we don't need to hold on to primitives
  // as they now belong to the children
  node->primitives.clear();
  node->primitives.shrink_to_fit();

  build_kd_tree(node->left);
  build_kd_tree(node->right);
}

KDNode::~KDNode() {
  if (left != NULL) {
    delete left;
  }
  if (right != NULL) {
    delete right;
  }
}