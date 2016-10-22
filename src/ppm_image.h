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

  // Sets the graphics canvas to be a provided PPM image.
  //
  // Accepts an istream which contains a PPM image file.
  //   If the first token is "P6", the stream should have binary
  //     as well as text mode available
  //     ex: ifstream("foo.ppm", std::ios::in | std::ios::binary);
  //   If the first token is "P3", only text mode is necessary.
  //   The calling context is responsible for closing the stream if necessary.
  //
  // Returns false if initialization failed.
  bool StreamInitialize(std::istream &);

  // Write the graphics object contained to a PPM Image File.
  //
  // Accepts an open ostream. If the type of this image is P6,
  // both binary and text output should be available.
  // For P3, only text output is necessary.
  //
  // The calling context is responsible for closing the stream if necessary.
  void Save(std::ostream &);

  // Change between P3 and P6 type PPM files.
  //
  // P3 stores the lightness values as numbers printed out in ASCII.
  //     This is useful for debugging.
  // P6 stores the lightness values directly in their binary form.
  void Convert(std::string);
 private:
  // The following two functions read the lightness values for the pixels
  // into an array.
  //
  // They are called by |StreamInitialize()| after it determines which type
  // of PPM image is being read. P3 stores the pixels as triples (RGB) of
  // integers printed out in human-readable format (i.e., ASCII, decimal).
  //     ex: "255 255 255" represents a white pixel for |num_levels = 255|
  // P6 stores the pixels as their direct binary values.
  //     ex: |0xff ff ff| represents a white pixel for 24-bit.
  bool ReadAsciiStream(std::istream &);
  bool ReadByteStream(std::istream &);

  // The following two functions are called by |Save()|.
  // They are the inverses of their "Read..." counterparts.
  void WriteByteBody(std::ostream &);
  void WriteAsciiBody(std::ostream &);

  std::string ppm_version_ = "P6";  // Magic number indicating the PPM version
  int num_levels_ = 255;  // Maximum lightness value of a pixel.
                          // Should not exceed 255.
                          // TODO(hxtk): reimplement Graphics to allow
                          //             greater bitdepth.
};  // class PpmImage
}  // namespace hxtk::graphics

#endif  // LIB_PPM_IMAGE_H_
