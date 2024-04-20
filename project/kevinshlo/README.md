# Corner Stitching

## Basic Information

"Corner Stitching" is a fundamental data structure
for tile-based detailed routing in EDA.  
The code of this project is hosted on GitHub
[kevinshlo/CornerStitching](https://github.com/kevinshlo/CornerStitching) .

## Problem to Solve

In electronic design automation (EDA), the last step of circuit design
is detailed routing, which is considered the most difficult and
time consuming step.  
There are several categories of methods to address this problem,
and one of them is called tile-based detailed routing.
In which, corner stitching is a fundamental data structure
to represent tiles on routing layers.

Recently,
routers involves deep learning have gained a lot of research attention.
There is a need to make accessing routing data structures from DL tools
such as PyTorch more efficient.
This project aims to provide a Python interface for
accessing corner stitching data structure in C++ efficiently.

## Prospective Users

Researchers in EDA field who want to introduce DL into tile-based routers
might be interested with this tool.

## System Architecture

This tool will be developed as a C++ library and providing a Python interface.
The corner stitching data structures holding the tiles is managed by
C++ library while users can call APIs to access and modifies tiles.

A class `RoutingPlane` contains several `Layer` and
other meta information about the whole routing plane.

A class `Layer` holds several `CornerStitch` and
some meta information about current routing layer.

A class `CornerStitch` stores the single physical `Tile` it holds
and pointers to neighbor `CornerStitch` .

A class `Tile` describes the information about the physical tile it represents.
e. g. type of the tile, size, etc.

## API Description

The following codes describe the headers of the data structure.

### `RoutingPlane`

```c++
class RoutingPlane {
  vector<Layer> layers;
  /* and other information about the routing plane */

  /** Constructor
   * specifying the width and length of the routing plane,
   * and the number of layers.
   */
  RoutingPlane(length_t width, length_t length, size_t num_layers);
};
```

### `Layer`

```c++
class Layer {
  vector<CornerStitch> corner_stitches;

  /** Constructor
   * a list of static obstacle to portrait the routing space
   * of this layer. Constructing `CornerStitch` in the layer.
   */
  Layer(const vector<Obstacle> &obstacles);

  /**
   * Getter of the `CornerStitch` at specified position.
   */
  CornerStitch & get_corner_stitch(length_t x, length_t y);
};
```

### `CornerStitch`

```c++
class CornerStitch {
  Tile tile;
  vector<CornerStitch *> neighbors;
  Layer *parent_layer;
  
  /**
   * Getter of the `Tile` it holds.
   */
  Tile & get_tile() { return tile; }

  /* Modifiers such as: split, combine, etc. */
  bool split();
  bool combine(const vector<CornerStitch *>&);
};
```

### `Tile`

```c++
class Tile {
  type_t tile_type;
  length_t width, height, x, y;

  /**
   * Constructor: specifying the type of this tile, width, length,
   * and other information.
   */
  Tile(type_t tile_type, length_t width, length_t height, 
       length_t x, length_t y);

  /* Getters of information its holds. */
  type_t get_tile_type() { return tile_type; }
};
```

## Engineering Infrastructure

Using GoogleTest and PyTest for C++ library and Python interface testing.
The correctness of the code is tested by developer written testcases.
GitHub Action is configured for automated test
while a local testing script will also be provided.

## Schedule

- Week 9 (4/15)
  - Clarify the detailed APIs and data structures.
  - Building and testing systems.
  - Start the skeleton of presentation.
- Week 10 (4/22)
  - Implement basic C++ data structures and templates.
- Week 11 (4/29)
  - Implement detailed C++ library, correctness first.
  - Testing of C++ library.
- Week 12 (5/6)
  - Refactoring C++ library.
  - Python interface.
  - Testing of Python interface.
- Week 13 (5/13)
  - Documentation of this tool.
  - Improve efficiency of C++ library and Python interface.
- Week 14 (5/20)
  - Refactoring.
  - Presentation materials.
- Week 15 (5/27)
  - Review the whole project.
  - Practice presentation.
- Week 16 (6/3)
  - Presentation day.

## References

[Corner Stitching: A Data Structuring Technique for VLSI Layout Tools](
https://ieeexplore.ieee.org/document/1270061)
