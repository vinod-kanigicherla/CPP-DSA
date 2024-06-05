#include "VoxMap.h"
#include "Errors.h"
#include <bitset>
#include <deque>
#include <sstream>
#include <string>
#include <tuple>

VoxMap::VoxMap(std::istream &stream) {
  stream >> width >> depth >> height;
  map.resize(height, std::vector<std::bitset<4>>(depth * (width / 4)));

  std::string line;
  std::getline(stream, line);

  for (int z = 0; z < height; z++) {
    std::getline(stream, line);
    for (int y = 0; y < depth; y++) {
      std::getline(stream, line);
      std::istringstream iss(line);
      for (int x = 0; x < (width / 4); x++) {
        char c;
        iss >> c;
        int value = std::stoi(std::string(1, c), nullptr, 16);
        map[z][y * (width / 4) + x] = std::bitset<4>(value);
      }
    }
  }
}

VoxMap::~VoxMap() {}

bool VoxMap::isValid(Point p) {
  return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z >= 0 &&
         p.z < height;
}

bool VoxMap::is_valid_no_z(Point p) {
  return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth;
}

bool VoxMap::equals(Point p1, Point p2) {
  return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
}

bool VoxMap::canStep(Point curr,
                     Point step) { // can you stand on voxel at max height??
  // int rem_step   = (step.x % 4);
  int rem_curr = (curr.x % 4);
  // int voxel_step = (step.y * (width / 4)) + step.x / 4;
  int voxel_curr = (curr.y * (width / 4)) + curr.x / 4;
  if (step.z >= curr.z + 2) {
    return false;
  }
  if (curr.z < height && map[curr.z + 1][voxel_curr][rem_curr] == 1 &&
      step.z >= curr.z + 1) {
    return false;
  }
  return true;
}

bool VoxMap::canStand(Point p) {
  if (!isValid(p))
    return false;
  if (p.z == 0 || !map[p.z - 1][p.y * (width / 4) + p.x / 4][3 - (p.x % 4)])
    return false;
  return !map[p.z][p.y * (width / 4) + p.x / 4][3 - (p.x % 4)];
}

int VoxMap::find_z(Point step) {
  // What about tunnels i.e there would be two possible z values
  if (!is_valid_no_z(step)) {
    return -1;
  }
  int rem_step = (step.x % 4);
  int voxel_step = (step.y * (width / 4)) + step.x / 4;
  for (int z = height - 1; z >= 0; z--) {
    if (map[z][voxel_step][rem_step] == 1) {
      return z + 1;
    }
  }
  return -1; // if there is nothing there (fall in the water)
}

Route VoxMap::route(Point src, Point dst) {
  if (!canStand(src))
    throw InvalidPoint(src);
  if (!canStand(dst))
    throw InvalidPoint(dst);

  std::deque<std::tuple<Point, Route>> q;
  std::vector<std::vector<std::vector<bool>>> visited(
      width,
      std::vector<std::vector<bool>>(depth, std::vector<bool>(height, false)));

  q.push_front({src, Route()});
  visited[src.x][src.y][src.z] = true;

  const Move dirs[4] = {Move::NORTH, Move::SOUTH, Move::EAST, Move::WEST};
  const std::vector<std::tuple<int, int>> disp = {
      {0, -1}, {0, 1}, {1, 0}, {-1, 0}};

  while (!q.empty()) {
    auto [curr, path] = q.front();
    q.pop_front();

    if (equals(curr, dst)) {
      return path;
    }

    for (size_t i = 0; i < 4; i++) {
      auto [dx, dy] = disp[i];
      Point next = {curr.x + dx, curr.y + dy, curr.z};

      int found_z = find_z(next);
      next.z = found_z;

      if (next.z == -1)
        continue;
      if (!isValid(next))
        continue;
      if (visited[next.x][next.y][next.z])
        continue;
      if (!canStep(curr, next))
        continue;

      Route newPath = path;
      newPath.push_back(dirs[i]);
      q.push_back({next, newPath});
      visited[next.x][next.y][next.z] = true;
    }
  }

  throw NoRoute(src, dst);
}
