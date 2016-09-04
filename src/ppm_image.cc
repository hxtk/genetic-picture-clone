/**********
 * PpmImage object definition
 *
 * Copyright: 2016 Peter Sanders
 * Author: Peter Sanders
 * Date: 2016-09-03
 */

#include "../lib/ppm_image.h"

namespace hxtk {

void PpmImage::init_ascii(const std::ifstream & input_file) {
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
}

void PpmImage::init_byte(const std::ifstream & input_file) {
  input_file.read(data_.pixels, data_pixels.size());
  if ( input_file.bad() ) {
    std::cerr << "bad PPM Body" << std::endl;
    delete this;
    input_file.close();
    exit(EXIT_FAILURE);
  }
}

void PpmImage::init(const std::ifstream & input_file) {
  input_file >> data_.ppm_version
             >> data_.width
             >> height
             >> num_levels;
  if ( input_file.bad() ) {
    std::cerr << "Bad PPM Header" << std::endl;
    delete this;
    input_file.close();
    exit(EXIT_FAILURE);
  }

  data_pixels.resize(3 * data_.width * data_.height);
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
explicit PpmImage::PpmImage(const std::ifstream & input_file) {
  init(input_file);
}

}  // namespace hxtk
