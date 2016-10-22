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
  Graphics() {};
  ~Graphics() {};
  void Initialize(int, int);
  void Populate(int, int, std::vector<uint8_t>);

  // Accepts a vector<int> which will be erased (if non-empty)
  // and populates it with the monochrome histogram of the image
  // described by the canvas on this class instance.
  //
  // The monochrome histogram is defined here as the number of pixels
  // containing some lightness value, irrespective of color channel
  void Histogram(std::vector<int> *);

  // Quantifies the difference between two images passed as parameters
  // as a function of both images' probability distribution functions.
  //
  // The probability distribution function are approximated by
  // the monochrome histogram.
  static double KullbackLeiblerDistance(Graphics &, Graphics &);

  // Each point is collided with each polygon on the canvas
  // using a ray casting algorithm. If the point is within
  // the polygon, the color of that polygon is added to the color
  // of the pixel. Polygons here are treated as light sources
  // over a black canvas, and are considered to be transparent.
  void Render();

  //void SavePpm(std::ostream &);

  // Adds a new polygon to the list of polygons.
  void add_polygon(graphics::Polygon polygon) {
    polygons_.push_back(polygon);
    rendered_ = false;
  }
 protected:
  void set_width(int width) {
    width_ = width;
    rendered_ = false;
  }
  void set_height(int height) {
    height_ = height;
    rendered_ = false;
  }
  void set_canvas(const std::vector<uint8_t>& canvas) {
    canvas_ = canvas;
    rendered_ = true;
  }
  std::vector<uint8_t>& get_canvas() { return canvas_; }
 private:
  constexpr static double kEpsilon = std::numeric_limits<double>::min();
  constexpr static uint8_t kMaxLevel = 255;

  // Ray Casting Algorithm:
  // Begin at the point in question and iterate right.
  // Each time the ray crosses an edge of the polygon,
  //    it is either entering or leaving the polygon
  // At infinity, the ray cannot be inside the polygon.
  // Thus, there are an odd number of edge crossings
  //     IFF the point is within the polygon.
  bool PointWithinPolygon(graphics::Point, graphics::Polygon);

  // Accepts a point as the starting point for the ray
  // and two vertices as the end-points for the edge
  //
  // Trivially:
  // A horizontal ray does not ross an edge if the starting point is
  //     above, below, or beyond both edge vertices.
  // It does cross the edge if it does not meet those criteria
  //     and is left of both vertices.
  //
  // Non-trivially:
  // The point crosses the edge IFF the angle it formed between it
  //    and the horizontal through the bottom-most vertex is wider
  //    than that formed between the top-most vertex and the horizontal.
  bool RayCrossesEdge(graphics::Point, graphics::Point, graphics::Point);

  // List of polygons to be rendered
  std::vector<graphics::Polygon> polygons_;

  // Byte array of pixels
  std::vector<uint8_t> canvas_;
  int width_ = -1;
  int height_ = -1;

  // Has Render() been called since the last operation?
  bool rendered_ = false;
};
}  // namespace hxtk

#endif  // LIB_GRAPHICS_H_
