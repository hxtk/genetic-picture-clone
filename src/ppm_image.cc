/**********
 * PpmImage object definition
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "../lib/ppm_image.h"

namespace hxtk {

void PpmImage::writeByteBody(std::ostream & output_stream) {
  output_stream.write(reinterpret_cast<const char*>(&data_.pixels[0]),
                      data_.pixels.size()*sizeof(uint8_t));
}

void PpmImage::writeAsciiBody(std::ostream & output_stream) {
  for (uint i = 0; i < data_.pixels.size(); ++i) {
    output_stream << std::setw(3) << int{data_.pixels.at(i)};
    if (i % 3 == 2) {
      if (i / 3 % data_.width == 0) {
        output_stream << "\n";
      } else {
        output_stream << "\t";
      }
    } else {
      output_stream << " ";
    }
  }
}

void PpmImage::write(std::ostream & output_stream) {
  output_stream << data_.ppm_version << "\n"
                << data_.width << " " << data_.height << "\n"
                << data_.num_levels << "\n";
  if ( data_.ppm_version.compare("P6") == 0 ) {
    writeByteBody(output_stream);
  } else if ( data_.ppm_version.compare("P3") == 0 ) {
    writeAsciiBody(output_stream);
  } else {
    std::cerr << "Unsupported PPM. File not written." << std::endl;
  }
}

void PpmImage::convert(std::string new_version) {
  if ( new_version.compare("P6") == 0 ||
      new_version.compare("P3") == 0 ) {
    data_.ppm_version = new_version;
  } else {
    std::cerr << "invalid PPM version" << std::endl;
  }
}

// Parses the body of P3 files that are in text format
void PpmImage::init_ascii_stream(std::istream & input_file) {
  for ( std::vector<uint8_t>::iterator i = data_.pixels.begin();
        i != data_.pixels.end(); ++i) {
    if ( input_file.bad() ) {
      std::cerr << "bad PPM Body" << std::endl;
      delete this;
      exit(EXIT_FAILURE);
    }
    input_file >> *i;
  }
}

// Parses the body of P6 files that are in binary format
void PpmImage::init_byte_stream(std::istream & input_file) {
  input_file.read(reinterpret_cast<char*>(&data_.pixels[0]),
                  static_cast<int>(data_.pixels.size()));
  if ( input_file.bad() ) {
    std::cerr << "bad PPM Body" << std::endl;
    delete this;
    exit(EXIT_FAILURE);
  }
}

// Reads the header and prepares to read body when initializing from stream
void PpmImage::init_stream(std::istream & input_file) {
  input_file >> data_.ppm_version
             >> data_.width
             >> data_.height
             >> data_.num_levels;
  if ( input_file.bad() ) {
    std::cerr << "Bad PPM Header" << std::endl;
    delete this;
    exit(EXIT_FAILURE);
  }

  data_.pixels.resize(3 * data_.width * data_.height);

  if ( data_.ppm_version.compare("P6") == 0 ) {
    init_byte_stream(input_file);
  } else if ( data_.ppm_version.compare("P3") == 0 ) {
    init_ascii_stream(input_file);
  } else {
    std::cerr << "Bad PPM Header" << std::endl;
    delete this;
    exit(EXIT_FAILURE);
  }
}

void PpmImage::init_struct(ppm::PpmData & data) {
  this->data_ = data;
}

// Read in a PPM image from a file
PpmImage::PpmImage(std::istream & input_file) {
  init_stream(input_file);
}

PpmImage::PpmImage(ppm::PpmData & data) {
  init_struct(data);
}

PpmImage::~PpmImage() {
  // TODO(hxtk) deconstructor
}

}  // namespace hxtk
