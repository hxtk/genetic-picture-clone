/**********
 * Graphics object definition
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-04
 */

#include "../lib/graphics.h"

namespace hxtk {

// Ray Casting Algorithm inner calculations
bool Graphics::RayCrossesEdge(graphics::Point ray_origin,
                              graphics::Point vertex_a,
                              graphics::Point vertex_b) {
  // Enforce A.y <= B.y
  if ( vertex_a.y > vertex_b.y )
    return RayCrossesEdge(ray_origin, vertex_b, vertex_a);

  #ifdef EBUG
  std::cout << "(" << vertex_a.x << ", " << vertex_a.y << ")"
            << "(" << vertex_b.x << ", " << vertex_b.y << ")" << std::endl;
  #endif
  
  // Eliminate edge case of vertex and test point at same height
  if (abs(ray_origin.y - vertex_a.y) < kEpsilon ||
      abs(ray_origin.y - vertex_b.y) < kEpsilon) ray_origin.y += kEpsilon;

  // Handle trivial FALSE cases:
  // - test point above or below both verticies
  // - test point right of both verticies
  if ( ray_origin.y <= vertex_a.y ||
       ray_origin.y > vertex_b.y ||
       ray_origin.x >= std::max(vertex_a.x, vertex_b.x) ) {
    #ifdef EBUG
    std::cout << "Trivial FALSE" << std::endl;
    #endif
    return false;
  }

  // Handle trivial TRUE cases:
  // - test point was not trivial FALSE case
  // - test point left of both verticies
  if ( ray_origin.x <= std::min(vertex_a.x, vertex_b.x) ) {
    #ifdef EBUG
    std::cout << "Trivial TRUE" << std::endl;
    #endif
    return true;
  }

  // tangent of angle between segment PA and the positive X direction
  double angle_pax = abs(ray_origin.x - vertex_a.x) >= kEpsilon
                   ? (vertex_a.y - ray_origin.y) / (vertex_a.x - ray_origin.x)
                   : std::numeric_limits<double>::infinity();

  // tangent of angle between BA and the positive X direction
  double angle_bax = abs(vertex_b.x - vertex_a.x) >= kEpsilon
                   ? (vertex_a.y - vertex_b.y) / (vertex_a.x - vertex_b.x)
                   : std::numeric_limits<double>::infinity();

  #ifdef EBUG
  std::cout << angle_pax << " >= " << angle_bax << std::endl;
  #endif

  return (angle_pax >= angle_bax);
}

// Ray casting algorithm
bool Graphics::PointWithinPolygon(graphics::Point point,
                                  graphics::Polygon polygon) {
  bool response = this->RayCrossesEdge(point,
      *polygon.points.begin(),
       polygon.points.end()[-1]);

  for ( std::vector<graphics::Point>::iterator i = polygon.points.begin();
        (i+1) != polygon.points.end(); ++i) {
    if ( RayCrossesEdge(point, *i, *(i + 1)) ) response ^= true;
  }

  return response;
}

// For each pixel, see which polygons it is in and combine colors additively
void Graphics::Render() {
  std::fill(canvas_.begin(), canvas_.end(), 0);
  if ( polygons_.empty() ) {
    #ifdef EBUG
    std::cout << "No polygons" << std::endl;
    #endif
    rendered_ = true;
    return;
  }
  for (int i = 0; i < width_*height_; ++i) {
    graphics::Point p(i % width_, i / width_);
    for (std::vector<graphics::Polygon>::iterator it = polygons_.begin();
         it != polygons_.end(); ++it) {
      if ( this->PointWithinPolygon(p, *it) ) {
        #ifdef EBUG
        std::cout << "(" << p.x << ", " << p.y << ") "
                  << "within polygon" << std::endl;
        #endif
        canvas_.at(3*i) =
            kNumLevels - canvas_.at(3*i) < it->color.red ? kNumLevels :
            canvas_.at(3*i) + it->color.red;
        canvas_.at(3*i + 1) =
            kNumLevels - canvas_.at(3*i + 1) < it->color.green ? kNumLevels :
            canvas_.at(3*i + 1) + it->color.green;
        canvas_.at(3*i + 2) =
            kNumLevels - canvas_.at(3*i + 2) < it->color.blue ? kNumLevels :
            canvas_.at(3*i + 2) + it->color.blue;
      }
    }
  }
  rendered_ = true;
}

void Graphics::Histogram(std::vector<int> * hist) {
  hist->resize(256);
  std::fill(hist->begin(), hist->end(), 0);

  for (std::vector<uint8_t>::iterator it = canvas_.begin();
       it != canvas_.end(); ++it) {
    ++(hist->at(*it));
  }
}

void Graphics::SavePpm(std::ostream & output_stream) {
  if ( !rendered_ ) Render();
  ppm::PpmData data = {
    "P6",
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

void Graphics::init(int width, int height, std::vector<uint8_t> pixels) {
  canvas_ = pixels;
  width_  = width;
  height_ = height;
}

Graphics::Graphics(int width, int height) {
  init(width, height);
}

Graphics::Graphics(int width, int height, std::vector<uint8_t> pixels) {
  init(width, height, pixels);
}

Graphics::~Graphics() {
}

double Graphics::KullbackLeiblerDistance(Graphics & p, Graphics & q){
  if (p.width_ != q.width_ || p.height_ != q.height_) {
    std::cerr << "Graphics must be the same size" << std::endl;
    return std::numeric_limits<double>::signaling_NaN();
  }
  std::vector<int> hist_p = {};
  p.Histogram(&hist_p);
  std::vector<int> hist_q = {};
  q.Histogram(&hist_q);
  
  double distance = 0;
  for (uint i = 0; i < hist_p.size(); ++i) {
    if ( hist_p.at(i) != 0 && hist_q.at(i) != 0 ) {
      distance += hist_p.at(i) * log( hist_p.at(i) / hist_q.at(i) );
    }
  }
  return distance;
}
}  // namespace hxtk
