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
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <fstream>

#include "./ppm_image.h"

namespace hxtk {
namespace graphics {
struct Point {
  Point(double h, double v) {
    x = h;
    y = v;
  }
  double x;
  double y;
};
struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};
struct Polygon {
  Polygon(std::vector<Point> p, Color c) {
    points = p;
    color = c;
  }
  std::vector<Point> points;
  Color color;
};
}  // namespace graphics

class Graphics {
 public:
  Graphics(int, int);
  ~Graphics();

  void render();
  void savePpm(std::ostream &);
  inline void add_polygon(graphics::Polygon polygon) {
    polygons_.push_back(polygon);
    rendered_ = false;
  }

 private:
  void init(int, int);
  bool pointWithinPolygon(graphics::Point, graphics::Polygon);
  bool rayCrossesEdge(graphics::Point, graphics::Point, graphics::Point);

  constexpr static double kEpsilon = std::numeric_limits<double>::min();
  constexpr static int kNumLevels = 255;
  std::vector<graphics::Polygon> polygons_;
  std::vector<uint8_t> canvas_;
  int width_ = -1;
  int height_ = -1;
  bool rendered_ = false;
};
}  // namespace hxtk

#endif  // LIB_GRAPHICS_H_
