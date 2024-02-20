#include "ImageMatrix.h"
#include <iostream>

using namespace std;


// Default constructor
ImageMatrix::ImageMatrix():height(0),width(0),data(nullptr){



}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data= new double*[height]; // Assigning the data pointer to reach elements of matrix and bc of the ''**'' we get the first * here.
    for (int i=0;i<height;i++){
        data[i]=new double [width];
        for (int j=0;j<width;j++){
            data[i][j]=0; // Every element is zero.

        }
    }
}
// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }
    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}

// Destructor
ImageMatrix::~ImageMatrix() {
    if (data != nullptr){
        for (int i=0 ; i<width;i++){
            delete[] data[i];
        }
        delete[]data;
    }
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth){
    height=imgHeight;
    width=imgWidth;

    data= new double*[height]; // Assigning the data pointer to reach elements of matrix and bc of the ''**'' we get the first * here.
    for (int i=0;i<height;i++){
        data[i]=new double [width];
        for (int j=0;j<width;j++){
            data[i][j]=inputMatrix[i][j]; // We get the inputMatrix for the initialization to our data matrix.
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) {

    height =other.height;
    width =other.width;

    data = new double*[height];
    for (int i = 0; i < height; i++) {
        data[i] = new double[width];
        for (int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }


}


// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if (this == &other) {
        return *this; // self-assignment check
    }


    if (data != nullptr){ // Deleting the old one.
        for (int i=0 ; i<height;i++){
            delete[] data[i];
        }
        delete[]data;
    }
    height =other.height;
    width =other.width;

    data = new double*[height]; // Allocate the memory and copying here.
    for (int i = 0; i < height; i++) {
        data[i] = new double[width];
        for (int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;


}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {

    ImageMatrix result(this->width, this->height);
    for (int i = 0; i<height; i++){
       for(int j = 0;j<width; j++){
           result.data[i][j]=this->data[i][j]+other.data[i][j];
       }
    }
    return result;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    ImageMatrix result(this->width, this->height);
    for (int i = 0; i<height; i++){
        for(int j = 0;j<width; j++){
            result.data[i][j]=this->data[i][j]-other.data[i][j];
        }
    }
    return result;

}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    ImageMatrix result(this->width, this->height);
    for (int i = 0; i<height; i++){
        for(int j = 0;j<width; j++){
            result.data[i][j]=this->data[i][j]*scalar;
        }
    }
    return result;



}


// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;


}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {

    if( i >= 0 && i < height && j >= 0 && j < width){ // I'm checking the boundaries.


        return data[i][j];

    }

    else{
        throw std::out_of_range("Numbers are out of borders.");
    }

}

int ImageMatrix::get_height() const {
    return height;
}

int ImageMatrix::get_width() const {
    return width;
}

void ImageMatrix::set_data(int i, int i1, double d) { // I'm creating this set_data function to update the values of the matrix's specific location.
    if (i >= 0 && i < height && i1 >= 0 && i1 < width) {
        data[i][i1] = d;
    }
    else {
        throw std::out_of_range("Numbers are out of borders.");
    }

    }
    
