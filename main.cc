/**********
 * Main program for genetic picture matcher
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "./main.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0]
              <<" <output>.ppm" << std::endl;
    exit(EXIT_FAILURE);
  }
  hxtk::Graphics * g = new hxtk::Graphics(512,512);
  g->add_polygon({
       { {100,100}, {100,300}, {300,300}, {300, 100} },
       { 100, 100, 255 }
     });
  g->add_polygon({
       { {200, 200}, {200, 500}, {500, 500} },
       { 255, 100, 100 }
     });
  std::ofstream output_file(argv[1], std::ios::out | std::ios::binary);
  g->savePpm(output_file);
  output_file.close();

  return EXIT_SUCCESS;
}

/*
int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0]
              <<" <input>.ppm <output>.ppm" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream input_file(argv[1], std::ios::in | std::ios::binary);
  hxtk::PpmImage *input_image = new hxtk::PpmImage(input_file);
  input_file.close();

  delete input_image;
  return 0;
}
*/
