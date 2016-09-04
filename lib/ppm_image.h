/**********
 * Header file for PpmImage object.
 *
 * Parses PPM Image files in and out of filesystem
 *
 * Copyright: 2016 Peter Sanders
 * Author: Peter Sanders
 * Date: 2016-09-03
 */

#ifndef LIB_PPM_IMAGE_H_
#define LIB_PPM_IMAGE_H_

#include <string>
#include <vector>
#include <cstdlib>

namespace hxtk {

struct PpmData {
  string ppm_version;
  int width;
  int height;
  int max;
  std::vector<std::vector<int>> pixels_;
};

class PpmImage{
 public:
  explicit PpmImage(const std::ifstream &);
  ~PpmImage();

  inline get_width() { return data_.width; }
  inline get_height() { return data_.height; }
 private:
  void init(const std::ifstream &);

  PpmData data_;  
};  // class PpmImage
}  // namespace hxtk

#endif  // LIB_PPM_IMAGE_H_
