/**********
 * Graphics object definition
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-04
 */

#include "../lib/graphics.h"

namespace hxtk {

// Ray Casting Algorithm inner calculations
bool Graphics::rayCrossesEdge(graphics::Point ray_origin,
                              graphics::Point vertex_a,
                              graphics::Point vertex_b) {
  // Edge case for horizontal line
  if ( abs(vertex_a.y - vertex_b.y) < kEpsilon &&
       abs(vertex_a.y - ray_origin.y) < kEpsilon ) {
    return (ray_origin.x < vertex_a.x && ray_origin.x < vertex_b.x);
  }

  // Vertex A must always be below Vertex B
  if ( vertex_a.y > vertex_b.y ) {
    graphics::Point tmp = vertex_b;
    vertex_b = vertex_a;
    vertex_a = tmp;
  }

  // If ray is above or below edge, it does not cross it
  if ( ray_origin.y > vertex_b.y || ray_origin.y < vertex_a.y ) return false;

  // If ray is within y-range and left of edge, it crosses it
  if ( ray_origin.x < vertex_a.x && ray_origin.x < vertex_b.x ) return true;

  float angle_pax;  // Angle between test point, A, and the horizontal
  if ( ray_origin.x == vertex_a.x ) {
    angle_pax = std::numeric_limits<float>::infinity();
  } else {
    angle_pax = (ray_origin.y - vertex_a.y) / (ray_origin.x - vertex_a.x);
  }

  float angle_bax;  // Angle between B, A, and the horizontal
  if ( vertex_b.x == vertex_a.x ) {
    angle_bax = std::numeric_limits<float>::infinity();
  } else {
    angle_bax = (vertex_b.y - vertex_a.y) / (vertex_b.x - vertex_a.x);
  }

  // Test point is left of AB iff angle PAX is not less than BAX
  return (angle_pax >= angle_bax);
}

// Ray casting algorithm
bool Graphics::pointWithinPolygon(graphics::Point point,
                                  graphics::Polygon polygon) {
  bool response = false;
  for ( std::vector<graphics::Point>::iterator i = polygon.points.begin();
        (i+1) != polygon.points.end(); ++i) {
    if ( rayCrossesEdge(point, *i, *(i + 1)) ) response ^= true;
  }

  return response;
}

void Graphics::init(int width, int height) {
  canvas_.resize(3*width*height);
}

Graphics::Graphics(int width, int height) {
  init(width, height);
}

Graphics::~Graphics() {
}

}  // namespace hxtk
