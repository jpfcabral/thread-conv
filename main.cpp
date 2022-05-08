#include <pthread.h>
#include <unistd.h>
#include "utils/image.h"
#include "utils/kernel.h"

#define NUM_THREADS 3

struct conv_data {
  int kernel_size;
  string filename;
  string output_filename;
};

void *convolutional_worker(void *arg){
  struct conv_data *data = (conv_data *)arg;

  cout << "Convolving " << (string)data->filename << " with " << (int)data->kernel_size << "x" << (int)data->kernel_size << " kernel" << endl;
  Image img((string)data->filename);
  Kernel k((int)data->kernel_size, (int)data->kernel_size);

  img.conv(k, data->output_filename);
  cout << "Output written to " << data->output_filename << endl;
  pthread_exit(NULL);
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
    data[i].kernel_size = kernel_sizes[i];
    data[i].filename = "images/glassware_noisy.ascii.pgm";
    data[i].output_filename = "images/glassware_noisy_conv_" + to_string(i + 1) + ".ascii.pgm";

    pthread_create(&threads[i], &attr, convolutional_worker, (void *)&data[i]);
  }

  pthread_attr_destroy(&attr);
  for (int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], &status);
  }
  pthread_exit(NULL);
}