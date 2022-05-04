#include "image.h"

using namespace std;

Image::Image(string filename){
    ifstream file(filename);
    stringstream ss;
    string line = "";
    int numcols = 0;
    int numrows = 0;
    int *shape = new int[2];
    int max_value = 0;

    getline(file,line);

    // Continue with a stringstream
    ss << file.rdbuf();
    // Third line : size
    ss >> numcols >> numrows;
    cout << numcols << " columns and " << numrows << " rows" << endl;
    
    ss >> max_value;
    cout << "Max value : " << max_value << endl;

    shape[0] = numcols;
    shape[1] = numrows;

    this->numrows = numrows;
    this->numcols = numcols;
    this->array = (int**)malloc(numrows*sizeof(int*));

    for(int i = 0; i < numrows; i++){
        array[i] = (int*)malloc(numcols*sizeof(int));
    }

    for(int row = 0; row < numrows; ++row){
        for (int col = 0; col < numcols; ++col){
            ss >> array[row][col];
        }
    }
    
    file.close();
}

Image::~Image(){
    for(int i = 0; i < numrows; i++){
        free(array[i]);
    }
    free(array);
}

int** Image::get_array(){
    return array;
}

int Image::get_numrows(){
    return numrows;
}

int Image::get_numcols(){
    return numcols;
}

int** Image::conv(Kernel k, string filename){
    ofstream file(filename);

    int **conv_array = (int**)malloc(numrows*sizeof(int*));
    for(int i = 0; i < numrows; i++){
        conv_array[i] = (int*)malloc(numcols*sizeof(int));
    }

    for(int row = 0; row < numrows; ++row){
        for (int col = 0; col < numcols; ++col){
            int sum = 0;
            for(int i = 0; i < k.get_height(); i++){
                for(int j = 0; j < k.get_width(); j++){
                    int kernel_row = row - i;
                    int kernel_col = col - j;
                    if(kernel_row >= 0 && kernel_col >= 0){
                        sum += array[kernel_row][kernel_col] * k.get_kernel()[i][j];
                    }
                }
            }
            conv_array[row][col] = sum;
        }
    }

    file << "P2" << endl;
    file << numcols << " " << numrows << endl;
    file << 255 << endl;
    for(int row = 0; row < numrows; ++row){
        for (int col = 0; col < numcols; ++col){
            file << conv_array[row][col] << " ";
        }
        file << endl;
    }
    file.close();
    return conv_array;
}