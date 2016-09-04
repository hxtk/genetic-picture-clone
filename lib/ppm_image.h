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
#include <iostream>
#include <fstream>
#include <cstdint>

namespace hxtk {

class PpmImage{
 public:
  explicit PpmImage(std::ifstream &);
  ~PpmImage();

  inline int get_width() { return data_.width; }
  inline int get_height() { return data_.height; }
 private:
  void init(std::ifstream &);
  void init_ascii(std::ifstream &);
  void init_byte(std::ifstream &);

  struct PpmData {
    std::string ppm_version;
    int width;
    int height;
    int num_levels;
    std::vector<uint8_t> pixels;
  } data_;

};  // class PpmImage
}  // namespace hxtk

#endif  // LIB_PPM_IMAGE_H_
