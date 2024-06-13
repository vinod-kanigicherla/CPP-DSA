# WRITEUP.md

## World Representation

The world map is represented as a 3D grid of voxels. Each voxel is either filled or empty, and the map is stored as a 3D vector of bitsets. The bitset allows for storage of the voxel data. Specifically:

* The highest binary digit (8s) represents the westernmost voxel.
* The next highest binary digit (4s) represents the voxel to the immediate east of the westernmost voxel.
* The next highest binary digit (2s) represents the next voxel to the east.
* The lowest binary digit (1s) represents the easternmost voxel.


## Route Queries Algorithm

The route queries are performed using a Breadth-First Search (BFS) algorithm. The BFS explores all possible paths from the source to the destination based on the movement constraints. The algorithm accounts for the possibility of moving up or down based on the terrain.

## Data Structures

- **3D Vector of Bitsets**: The voxel map is stored as a `std::vector<std::vector<std::bitset<4>>>` where each bitset represents four voxels.
- **Double-Ended Queue**: Used for the BFS queue to explore paths. The deque stores tuples of the current point and the path taken to reach that point.
- **3D Vector of Booleans**: Tracks visited voxels to avoid re-exploration.

## Algorithm Steps

### 1. Map Initialization
* Read the map dimensions (width, depth, height) from the input stream and resize the map to fit the dimensions.
* For each tier (height level) of the map:
  * Read and ignore the blank line separating the tiers.
  * For each row (depth) in the tier:
    * Read the line of hex characters.
    * Convert each hex character to a bitset representing four voxels and store it in the map.

### 2. Route Calculation
* Initialize a Breadth-First Search (BFS) algorithm from the source point.
* Use a double-ended queue to store tuples of the current point and the path taken to reach that point.
* Initialize a 3D vector of booleans to track visited voxels.
* Mark the source point as visited and push it to the queue.
* While the queue is not empty:
  * Pop the front of the queue to get the current point and path.
  * If the current point equals the destination, return the path.
  * For each of the four cardinal directions (north, south, east, west):
    * Calculate the next point by applying the direction to the current point. If the next point is out of bounds, continue to the next direction.
    * **Move Validation**:
      * Check if the next step is valid and find the appropriate z-coordinate using `canStepAndFindZ`.
      * Update the z-coordinate of the next point.
      * If the next point is not valid or has been visited, continue to the next direction.
      * Mark the next point as visited, update the path, and push the next point and path to the queue.

## Big-O Runtime Analysis
1. **Map Initialization**:
  * Reading the dimensions: `O(1)`
  * Resizing the map: `O(height * depth * (width / 4))`
  * Reading and storing each tier: `O(height * depth * (width / 4))`
  * Total: `O(height * depth * (width / 4))`
2. **Route Calculation**:
  * BFS Initialization: `O(1)`
  * BFS Exploration: `O(V + E)` where `V` is the number of vertices (voxels) and `E` is the number of edges (possible moves).
  * Each move validation: `O(1)`
  * Total: `O(V + E)`

## Total Runtime
* **Map Initialization**: `O(height * depth * (width / 4))`
* **Route Calculation**: `O(V + E)`
* Given that `V = width * depth * height` and each voxel can have at most 6 edges (north, south, east, west, up, down), we simplify the total runtime to `O(V)`.
