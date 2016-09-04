/**********
 * Header file for Graphics class
 *
 * Renders 2d graphics from polygon definitions.
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-04
 */

#ifndef LIB_GRAPHICS_H_
#define LIB_GRAPHICS_H_

#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdint>
#include <iostream>
#include <fstream>

namespace hxtk {
namespace graphics {
struct Point {
  float x;
  float y;
};
struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  float  alpha;
};
struct Polygon {
  std::vector<Point> points;
  Color color;
};
}  // namespace graphics

class Graphics {
 public:
  Graphics(int, int);
  ~Graphics();

  void writePpm(std::string);
  inline void add_polygon(graphics::Polygon polygon) {
    polygons_.push_back(polygon);
  }

 private:
  void init(int, int);
  void render();
  bool pointWithinPolygon(graphics::Point, graphics::Polygon);
  bool rayCrossesEdge(graphics::Point, graphics::Point, graphics::Point);
    
  std::vector<graphics::Polygon> polygons_;
  std::vector<uint8_t> canvas_;
  constexpr static float kEpsilon = 0.001F;
};
}  // namespace hxtk

#endif  // LIB_GRAPHICS_H_
