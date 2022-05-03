#include "utils/image.h"

int main(){
  Image img("images/glassware_noisy.ascii.pgm");
  int **array = img.get_array();
  for(int i = 0; i < img.get_numrows(); i++){
    for(int j = 0; j < img.get_numcols(); j++){
      cout << array[i][j] << " ";
    }
    cout << endl;
  }
}