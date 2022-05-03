#include "utils/image.h"
#include "utils/kernel.h"

int main(){
  Image img("images/glassware_noisy.ascii.pgm");
  int **array = img.get_array();

  Kernel k(3,3);
  k.print_kernel();
}