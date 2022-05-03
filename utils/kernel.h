#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Kernel{
    protected:
        int width;
        int height;
        float **kernel;
    public:
        Kernel(int width, int height);
        ~Kernel();

        float **get_kernel();
        int get_width();
        int get_height();
        void print_kernel();
};

#endif // KERNEL_H