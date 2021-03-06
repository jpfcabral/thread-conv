#ifndef FIGURA_H
#define FIGURA_H

#include <iostream>
#include <fstream> 
#include <sstream>
#include "kernel.h"

using namespace std;


class Image {
    protected:
        int numrows;
        int numcols;
        int **array;
    public:
        Image(string filename);
        ~Image();

    int get_numrows();
    int get_numcols();
    int **get_array();
};

#endif // FIGURA_H