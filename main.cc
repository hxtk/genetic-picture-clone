/**********
 * Main program for genetic picture matcher
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "./main.h"

hxtk::Graphics * target;

double fitness_function(hxtk::Graphics & g){
  return hxtk::Graphics::KullbackLeiblerDistance(*target, g);
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0]
              <<" <input>.ppm <output>.ppm" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream input_file(argv[1], std::ios::in | std::ios::binary);
  hxtk::PpmImage *input_image = new hxtk::PpmImage(input_file);
  input_file.close();

  target = input_image->ToGraphics();
  delete input_image;

  delete target;
  return 0;
}
