#include "image.h"

using namespace std;

Image::Image(string filename){
    ifstream file(filename);
    stringstream ss;
    string line = "";
    int numcols = 0;
    int numrows = 0;
    int *shape = new int[2];

    getline(file,line);

    // Second line : comment
    getline(file,line);
    //cout << "Comment : " << line << endl;

    // Continue with a stringstream
    ss << file.rdbuf();
    // Third line : size
    ss >> numcols >> numrows;
    //cout << numcols << " columns and " << numrows << " rows" << endl;
    file.close();

    shape[0] = numcols;
    shape[1] = numrows;

    this->numrows = numrows;
    this->numcols = numcols;
    this->array = (int**)malloc(numrows*sizeof(int*));

    for(int i = 0; i < numrows; i++){
        array[i] = (int*)malloc(numcols*sizeof(int));
    }
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