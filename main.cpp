#include "utils/image.h"
#include "utils/kernel.h"

int main(){
  Image img("images/glassware_noisy.ascii.pgm");
  Kernel k(3,3);

  img.conv(k, "images/3x3_glassware_noisy.ascii.pgm");
}