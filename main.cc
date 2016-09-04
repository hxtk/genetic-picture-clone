/**********
 * Main program for genetic picture matcher
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "./main.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0]
              <<" <input>.ppm <output>.ppm" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream input_file(argv[1], std::ios::in | std::ios::binary);
  hxtk::PpmImage *input_image = new hxtk::PpmImage(input_file);
  input_file.close();

  input_image->convert("P3");

  std::ofstream output_file(argv[2], std::ios::out | std::ios::binary);
  input_image->write(output_file);
  output_file.close();

  delete input_image;
  return 0;
}
