#include <pthread.h>
#include <unistd.h>
#include "utils/image.h"
#include "utils/kernel.h"

#define NUM_THREADS 3

struct conv_data {
  Kernel *kernel;
  Image *image;
  string output_filename;
};

void *convolution(void *thread_data) {
  struct conv_data *data = (struct conv_data *)thread_data;
  Image *image = data->image;
  Kernel *kernel = data->kernel;
  string output_filename = data->output_filename;

  int **conv_array = (int**)malloc(image->get_numrows()*sizeof(int*));
  for(int i = 0; i < image->get_numrows(); i++){
    conv_array[i] = (int*)malloc(image->get_numcols()*sizeof(int));
  }

  for(int row = 0; row < image->get_numrows(); ++row){
    for (int col = 0; col < image->get_numcols(); ++col){
      int sum = 0;
      for(int i = 0; i < kernel->get_height(); i++){
        for(int j = 0; j < kernel->get_width(); j++){
          int kernel_row = row - i;
          int kernel_col = col - j;
          if(kernel_row >= 0 && kernel_col >= 0){
            sum += image->get_array()[kernel_row][kernel_col] * kernel->get_kernel()[i][j];
          }
        }
      }
      conv_array[row][col] = sum;
    }
  }

  ofstream file(output_filename);

  file << "P2" << endl;
  file << image->get_numcols() << " " << image->get_numrows() << endl;
  file << 255 << endl;

  for(int row = 0; row < image->get_numrows(); ++row){
    for (int col = 0; col < image->get_numcols(); ++col){
      file << conv_array[row][col] << " ";
    }
    file << endl;
  }

  file.close();

  return NULL;
}

int main(int argc, char **argv){
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  int kernel_sizes[NUM_THREADS] = {3, 5, 7};
  void *status;
  struct conv_data data[NUM_THREADS];

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0; i < NUM_THREADS; i++){
    data[i].kernel = new Kernel(kernel_sizes[i], kernel_sizes[i]);
    data[i].image = new Image("images/glassware_noisy.ascii.pgm");
    data[i].output_filename = "images/glassware_" + to_string(kernel_sizes[i]) + "_.ascii.pgm";
    pthread_create(&threads[i], &attr, convolution, (void *)&data[i]);
  }

  pthread_attr_destroy(&attr);
  for (int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], &status);
  }
  pthread_exit(NULL);
  return 0;
}