/**********
 * PpmImage object definition
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "ppm_image.h"

namespace hxtk::graphics {

void PpmImage::WriteByteBody(std::ostream & output_stream) {
  output_stream.write(reinterpret_cast<const char *>(get_canvas().data()),
      get_canvas().size()*sizeof(uint8_t));
}

void PpmImage::WriteAsciiBody(std::ostream & output_stream) {
  for (int i = 0; i < get_canvas().size(); ++i) {
    output_stream << std::setw(4) << int{get_canvas().at(i)};
    if (i % 3 == 2) {
      if (i / 3 % get_width() == 0) {
        output_stream << "\n";
      } else {
        output_stream << "\t";
      }
    } else {
      output_stream << " ";
    }
  }
}

void PpmImage::Save(std::ostream & output_stream) {
  output_stream << ppm_version_ << "\n"
                << get_width() << " " << get_height() << "\n"
                << num_levels_ << "\n";
  if (ppm_version_ == "P6") {
    WriteByteBody(output_stream);
  } else if (ppm_version_ == "P3") {
    WriteAsciiBody(output_stream);
  } else {
    std::cerr << "Unsupported PPM. File not written." << std::endl;
  }
}

void PpmImage::Convert(std::string new_version) {
  if (new_version == "P6" || new_version == "P3") {
    ppm_version_ = new_version;
  } else {
    std::cerr << "invalid PPM version" << std::endl;
  }
}

// Parses the body of P3 files that are in text format
bool PpmImage::ReadAsciiStream(std::istream & input_file) {
  for (auto it = get_canvas().begin();
       it != get_canvas().end(); ++it) {
    if ( input_file.bad() ) {
      std::cerr << "bad PPM Body" << std::endl;
      return false;
    }
    input_file >> *it;
  }
  return true;
}

// Parses the body of P6 files that are in binary format
bool PpmImage::ReadByteStream(std::istream & input_file) {
  input_file.read(
      reinterpret_cast<char*>(get_canvas().data()),
      static_cast<int>(get_canvas().size()));
  if (input_file.bad()) {
    std::cerr << "bad PPM Body" << std::endl;
    return false;
  }
  return true;
}

// Reads the header and prepares to read body when initializing from stream
bool PpmImage::StreamInitialize(std::istream & input_file) {
  int width = -1;
  int height = -1;
  input_file >> ppm_version_
             >> width
             >> height
             >> num_levels_;

  if (input_file.bad()) {
    std::cerr << "Bad PPM Header" << std::endl;
    return false;
  }

  set_width(width);
  set_height(height);

  get_canvas().resize(3 * get_width() * get_height());

  if ( ppm_version_.compare("P6") == 0 ) {
    return ReadAsciiStream(input_file);
  } else if ( ppm_version_.compare("P3") == 0 ) {
    return ReadByteStream(input_file);
  } else {
    std::cerr << "Bad PPM Header" << std::endl;
    return false;
  }
  return true;
}
}  // namespace hxtk::graphics
