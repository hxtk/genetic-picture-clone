/**********
 * Main program for genetic picture matcher
 *
 * Copyright: Peter Sanders. All rights reserved.
 * Date: 2016-09-03
 */

#include "./main.h"

hxtk::graphics::Graphics * target = nullptr;

double fitness_function(hxtk::graphics::Graphics & g){
  return hxtk::graphics::Graphics::KullbackLeiblerDistance(*target, g);
}

int main(int argc, char* argv[]) {
  hxtk::graphics::PpmImage g;
  g.Initialize(250,250);
  std::vector<hxtk::graphics::Point> points;
  double pi = acos(-1.0);
  for (double t = 0.0; t < 2*pi; t += 0.01) {
    points.push_back(
        hxtk::graphics::Point(125+100*cos(t), 125+100*sin(t)));
  }
  hxtk::graphics::Color red(255,100,100);
  g.add_polygon(hxtk::graphics::Polygon(points, red));

  std::ofstream output_file(
      "test.ppm", std::ofstream::out | std::ofstream::binary);

  g.Render();
  g.Save(output_file);
  output_file.close();

  return 0;
}

/*
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
*/
