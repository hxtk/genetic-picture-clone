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
  // Enforce A.y <= B.y
  if ( vertex_a.y > vertex_b.y ) {
    graphics::Point tmp = vertex_b;
    vertex_b = vertex_a;
    vertex_a = tmp;
  }

  // Eliminate edge case of vertex and test point at same height
  if ( abs(ray_origin.y - vertex_a.y) < kEpsilon ||
       abs(ray_origin.y - vertex_b.y) < kEpsilon ) ray_origin.y += kEpsilon;

  // Handle trivial FALSE cases:
  // - test point above or below both verticies
  // - test point right of both verticies
  if ( ray_origin.y < vertex_a.y ||
       ray_origin.y > vertex_b.y ||
       ray_origin.x > std::max(vertex_a.x, vertex_b.x) ) return false;

  // Handle trivial TRUE cases:
  // - test point was not trivial FALSE case
  // - test point left of both verticies
  if ( ray_origin.x < std::min(vertex_a.x, vertex_b.x) ) return true;

  // Angle between segment PA and the positive X direction
  double angle_pax = abs(ray_origin.x - vertex_a.x) >= kEpsilon
                   ? (vertex_a.y - ray_origin.y) / (vertex_a.x - ray_origin.x)
                   : std::numeric_limits<double>::infinity();

  // Angle between BA and the positive X direction
  double angle_bax = abs(vertex_b.x - vertex_a.x) >= kEpsilon
                   ? (vertex_a.y - vertex_b.y) / (vertex_a.x - vertex_b.x)
                   : std::numeric_limits<double>::infinity();

  #ifdef EBUG
  std::cout << angle_pax << " > " << angle_bax << std::endl;
  #endif

  return (angle_pax >= angle_bax);
  
}
    
    // Ray casting algorithm
    bool Graphics::pointWithinPolygon(graphics::Point point,
      graphics::Polygon polygon) {
    bool response = rayCrossesEdge(point,
      *polygon.points.begin(),
				 *polygon.points.end());
  for ( std::vector<graphics::Point>::iterator i = polygon.points.begin();
        (i+1) != polygon.points.end(); ++i) {
    if ( rayCrossesEdge(point, *i, *(i + 1)) ) response ^= true;
  }

  #ifdef EBUG
  std::cout << "Point: (" << point.x << ", " << point.y << ") "
	    << ((response) ? "is" : "is not") << " in polygon." << std::endl;
  #endif
  
  return response;
}

// For each pixel, see which polygons it is in and combine colors additively
void Graphics::render() {
  std::fill(canvas_.begin(), canvas_.end(), 0);
  if ( polygons_.empty() ) {
    #ifdef EBUG
    std::cout << "No polygons" << std::endl;
    #endif
    rendered_ = true;
    return;
  }
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      graphics::Point pixel {
	static_cast<double>(j),
	static_cast<double>(i)
      };
      for (std::vector<graphics::Polygon>::iterator it = polygons_.begin();
	   it != polygons_.end(); ++it) {
	if ( pointWithinPolygon(pixel, *it) ) {
	  int index = 3*i*j + 3*i;
	  canvas_.at(index) =
	    kNumLevels - canvas_.at(index) > it->color.red ?
	    canvas_.at(index) + it->color.red : kNumLevels;
	  canvas_.at(index + 1) =
	    kNumLevels - canvas_.at(index + 1) > it->color.green ?
	    canvas_.at(index + 1) + it->color.green : kNumLevels;
	  canvas_.at(index + 2) =
	    kNumLevels - canvas_.at(index + 2) > it->color.blue ?
	    canvas_.at(index + 2) + it->color.blue : kNumLevels;
	}
      }
    }
  }
  rendered_ = true;
}

void Graphics::savePpm(std::ostream & output_stream) {
  if ( !rendered_ ) render();
  ppm::PpmData data = {
    "P3",
    width_,
    height_,
    kNumLevels,
    canvas_
  };
  PpmImage ppm(data);
  ppm.write(output_stream);
}

void Graphics::init(int width, int height) {
  canvas_.resize(3*width*height);
  width_ = width;
  height_ = height;
}
  
Graphics::Graphics(int width, int height) {
  init(width, height);
}

Graphics::~Graphics() {
}

}  // namespace hxtk
