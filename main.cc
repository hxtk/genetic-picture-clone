/**********
 * Main program for genetic picture matcher
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "./main.h"

hxtk::graphics::Graphics * target;

double fitness_function(hxtk::graphics::Graphics & g){
  return hxtk::graphics::Graphics::KullbackLeiblerDistance(*target, g);
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0]
              <<" <input>.ppm <output>.ppm" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream input_file(argv[1], std::ios::in | std::ios::binary);
  hxtk::graphics::PpmImage input_image;
  if (!input_image.StreamInitialize(input_file)) {
    std::cerr << "Input Image failed to initialize. Terminating." << std::endl;
    exit(EXIT_FAILURE);
  }
  input_file.close();

  target = static_cast<hxtk::graphics::Graphics*>(&input_image);

  return 0;
}
