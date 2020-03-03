#include <iostream>
#include "image.h"

using std::cout;
using std::endl;
int main() {
  igg::Image image;
  image.FillFromPgm("/Users/med/dev/igg_image/data/lil.pgm");
  image.ComputeHistogram(1);
  

  
  
  
 
  cout << "works\n";
  return 0;
}