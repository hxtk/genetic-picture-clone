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
  std::ifstream input_file(argv[1], std::ifstream::in);
  hxtk::PpmImage *input_image = new hxtk::PpmImage(input_file);
  input_file.close();

  delete input_image;
  return 0;
}
