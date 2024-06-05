#ifndef VOXMAP_H
#define VOXMAP_H

#include <bitset>
#include <deque>
#include <istream>
#include <tuple>
#include <vector>

#include "Point.h"
#include "Route.h"

class VoxMap {
  // Member Variables
  int width, depth, height;
  std::vector<std::vector<std::bitset<4>>> map;

  // Helper Functions
  // isValid, canStand, equals
  bool isValid(Point p);
  bool equals(Point p1, Point p2);
  bool canStep(Point curr, Point step);
  bool canStand(Point p);
  int find_z(Point step);
  bool is_valid_no_z(Point p);

public:
  VoxMap(std::istream &stream);
  ~VoxMap();

  Route route(Point src, Point dst);
};

#endif
