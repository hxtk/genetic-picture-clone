// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-10-21

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

namespace hxtk::graphics {
class PpmImage : public Graphics {
 public:
  PpmImage() {}
  ~PpmImage() {};

  bool StreamInitialize(std::istream &);

  void Save(std::ostream &);
  void Convert(std::string);
 private:
  bool ReadAsciiStream(std::istream &);
  bool ReadByteStream(std::istream &);

  void writeByteBody(std::ostream &);
  void writeAsciiBody(std::ostream &);

  std::string ppm_version_;
  int num_levels_;
};  // class PpmImage
}  // namespace hxtk::graphics

#endif  // LIB_PPM_IMAGE_H_
