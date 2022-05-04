#include "kernel.h"

Kernel::Kernel(int width, int height){
    this->width = width;
    this->height = height;
    this->kernel = (float**)malloc(height*sizeof(float*));
    int coeficient = width*height;

    for(int i = 0; i < height; i++){
        kernel[i] = (float*)malloc(width*sizeof(float));
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            kernel[i][j] = 1.0/coeficient;
        }
    }
}

Kernel::~Kernel(){
    for(int i = 0; i < height; i++){
        free(kernel[i]);
    }
    free(kernel);
}

float **Kernel::get_kernel(){
    return kernel;
}

int Kernel::get_width(){
    return width;
}

int Kernel::get_height(){
    return height;
}

void Kernel::print_kernel(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cout << kernel[i][j] << " ";
        }
        cout << endl;
    }
}