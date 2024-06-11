#include "Errors.h"
#include "VoxMap.h"
#include <bitset>
#include <deque>
#include <sstream>
#include <string>
#include <tuple>

VoxMap::VoxMap(std::istream &stream) {
  // Read dimensions: width, depth, height
  stream >> width >> depth >> height;

  // Resize the map to fit the dimensions
  map.resize(height, std::vector<std::bitset<4>>(depth * (width / 4)));

  std::string line;

  // Clear any leftover newline character from the input stream
  std::getline(stream, line);

  for (int z = 0; z < height; z++) {
    // Read the blank line separating the tiers
    std::getline(stream, line);
    std::cout << "Reading tier " << z << std::endl;

    for (int y = 0; y < depth; y++) {
      std::getline(stream, line);
      std::istringstream iss(line);

      for (int x = 0; x < (width / 4); x++) {
        char c;
        iss >> c;
        int value = std::stoi(std::string(1, c), nullptr, 16);
        map[z][y * (width / 4) + x] = std::bitset<4>(value);
        std::cout << "map[" << z << "][" << y << "][" << x
                  << "] = " << std::bitset<4>(value) << std::endl;
      }
    }
  }
}

VoxMap::~VoxMap() {}

bool VoxMap::isValid(Point p) {
  return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z >= 0 &&
         p.z <= height;
}

bool VoxMap::is_valid_no_z(Point p) {
  return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth;
}

bool VoxMap::equals(Point p1, Point p2) {
  return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
}

std::tuple<bool, int> VoxMap::canStepAndFindZ(Point curr, Point step) {
  // int rem_curr = (curr.x % 4);
  // int voxel_curr = (curr.y * (width / 4)) + curr.x / 4;

  int rem_step = (step.x % 4);
  int voxel_step = (step.y * (width / 4)) + step.x / 4;

  if (voxel_step >= static_cast<int>(map[0].size())) {
    std::cout << "Invalid step: Out of bounds" << std::endl;
    return std::make_tuple(false, -1);
  }

  std::cout << "Checking move from (" << curr.x << ", " << curr.y << ", "
            << curr.z << ") to (" << step.x << ", " << step.y << ", " << step.z
            << ")" << std::endl;

  // Check for flat move or jump up
  for (int z = height - 1; z >= 0; z--) {
    if (map[z][voxel_step][rem_step] == 1) {
      int found_z = z + 1;

      // Ensure we don't jump too high
      if (found_z > curr.z + 1) {
        std::cout << "Cannot jump too high to z=" << found_z << std::endl;
        return std::make_tuple(false, found_z);
      }

      // Allow flat moves
      if (found_z == curr.z) {
        std::cout << "Flat move to z=" << found_z << std::endl;
        return std::make_tuple(true, found_z);
      }

      // Check if we can move up
      // if (found_z == curr.z + 1) {
      //   // Ensure the voxel above the current position is empty
      //   if (curr.z < height - 1 && map[curr.z + 1][voxel_curr][rem_curr] ==
      //   0) {
      //     std::cout << "Jump to z=" << found_z << std::endl;
      //     return std::make_tuple(true, found_z);
      //   } else {
      //     std::cout << "Blocked jump up to z=" << found_z << std::endl;
      //     return std::make_tuple(false, found_z);
      //   }
      // }
    }
  }

  // Handle fall down
  for (int z = 0; z < height; z++) {
    if (map[z][voxel_step][rem_step] == 1) {
      // Check if the voxel below the step is empty, indicating water
      if (z == 0 || map[z - 1][voxel_step][rem_step] == 0) {
        std::cout << "Fall into water at z=" << z << std::endl;
        return std::make_tuple(false, z); // Fell into water
      }
      std::cout << "Fall down to z=" << z << std::endl;
      return std::make_tuple(true, z);
    }
  }

  std::cout << "Fall into water: No solid ground found" << std::endl;
  return std::make_tuple(false,
                         -1); // Fell into water if no solid ground is found
}

// bool VoxMap::canStep(Point curr,
//                      Point step) { // can you stand on voxel at max height??
//   // int rem_step   = (step.x % 4);
//   int rem_curr = (curr.x % 4);
//   // int voxel_step = (step.y * (width / 4)) + step.x / 4;
//   int voxel_curr = (curr.y * (width / 4)) + curr.x / 4;
//   if (step.z >= curr.z + 2) {
//     return false;
//   }
//   if (curr.z < height && map[curr.z + 1][voxel_curr][rem_curr] == 1 &&
//       step.z >= curr.z + 1) {
//     return false;
//   }
//   return true;
// }

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

    std::cout << "Current point: (" << curr.x << ", " << curr.y << ", "
              << curr.z << ")" << std::endl;
    std::cout << "Current path: ";
    for (auto move : path) {
      switch (move) {
      case Move::NORTH:
        std::cout << "n";
        break;
      case Move::SOUTH:
        std::cout << "s";
        break;
      case Move::EAST:
        std::cout << "e";
        break;
      case Move::WEST:
        std::cout << "w";
        break;
      }
    }
    std::cout << std::endl;

    if (equals(curr, dst)) {
      std::cout << "Destination reached: (" << dst.x << ", " << dst.y << ", "
                << dst.z << ")" << std::endl;
      return path;
    }

    for (size_t i = 0; i < 4; i++) {
      auto [dx, dy] = disp[i];
      Point next = {curr.x + dx, curr.y + dy, curr.z};

      if (!is_valid_no_z(next)) {
        std::cout << "Next point out of bounds: (" << next.x << ", " << next.y
                  << ", " << next.z << ")" << std::endl;
        continue;
      }

      auto [canStep, found_z] = canStepAndFindZ(curr, next);
      next.z = found_z;

      std::cout << "Next point: (" << next.x << ", " << next.y << ", " << next.z
                << "), canStep: " << canStep << std::endl;

      if (!canStep || next.z == -1) {
        std::cout << "Can't step check" << std::endl;
        continue;
      }
      if (!isValid(next)) {
        std::cout << "Not valid check" << std::endl;
        continue;
      }
      if (visited[next.x][next.y][next.z]) {
        std::cout << "Visited check" << std::endl;
        continue;
      }

      Route newPath = path;
      newPath.push_back(dirs[i]);
      q.push_back({next, newPath});
      visited[next.x][next.y][next.z] = true;
    }
  }

  throw NoRoute(src, dst);
}
