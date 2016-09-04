/**********
 * PpmImage object definition
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "../lib/ppm_image.h"

namespace hxtk {

// Parses the body of P3 files that are in text format
void PpmImage::init_ascii(std::ifstream & input_file) {
  for ( std::vector<uint8_t>::iterator i = data_.pixels.begin();
        i != data_.pixels.end(); ++i) {
    if ( input_file.bad() ) {
      std::cerr << "bad PPM Body" << std::endl;
      delete this;
      input_file.close();
      exit(EXIT_FAILURE);
    }
    input_file >> *i;
  }
  input_file.close();
}

// Parses the body of P6 files that are in binary format
void PpmImage::init_byte(std::ifstream & input_file) {
  input_file.read(reinterpret_cast<char*>(&data_.pixels[0]),
                  static_cast<int>(data_.pixels.size()));
  if ( input_file.bad() ) {
    std::cerr << "bad PPM Body" << std::endl;
    delete this;
    input_file.close();
    exit(EXIT_FAILURE);
  }
  input_file.close();
}

// Reads the header and prepares to read body when initializing from stream
void PpmImage::init(std::ifstream & input_file) {
  input_file >> data_.ppm_version
             >> data_.width
             >> data_.height
             >> data_.num_levels;
  if ( input_file.bad() ) {
    std::cerr << "Bad PPM Header" << std::endl;
    delete this;
    input_file.close();
    exit(EXIT_FAILURE);
  }

  data_.pixels.resize(3 * data_.width * data_.height);

  if ( data_.ppm_version.compare("P6") == 0 ) {
    init_byte(input_file);
  } else if ( data_.ppm_version.compare("P3") == 0 ) {
    init_ascii(input_file);
  } else {
    std::cerr << "Bad PPM Header" << std::endl;
    delete this;
    input_file.close();
    exit(EXIT_FAILURE);
  }
}

// Read in a PPM image from a file
PpmImage::PpmImage(std::ifstream & input_file) {
  init(input_file);
}

PpmImage::~PpmImage() {
  // TODO(hxtk) deconstructor
}

}  // namespace hxtk
