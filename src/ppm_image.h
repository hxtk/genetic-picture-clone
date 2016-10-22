/**********
 * Header file for PpmImage object.
 *
 * Parses PPM Image files in and out of filesystem
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#ifndef LIB_PPM_IMAGE_H_
#define LIB_PPM_IMAGE_H_

#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "./graphics.h"

namespace hxtk {
namespace ppm {
struct PpmData {
  std::string ppm_version;
  int width;
  int height;
  int num_levels;
  std::vector<uint8_t> pixels;
};
}  // namespace ppm

class PpmImage{
 public:
  explicit PpmImage(std::istream &);
  explicit PpmImage(ppm::PpmData &);
  ~PpmImage();

  void write(std::ostream &);
  void convert(std::string);

  inline int get_width() { return data_.width; }
  inline int get_height() { return data_.height; }
 private:
  void writeByteBody(std::ostream &);
  void writeAsciiBody(std::ostream &);
  void init_stream(std::istream &);
  void init_ascii_stream(std::istream &);
  void init_byte_stream(std::istream &);
  void init_struct(ppm::PpmData &);

  ppm::PpmData data_;
};  // class PpmImage
}  // namespace hxtk

#endif  // LIB_PPM_IMAGE_H_
