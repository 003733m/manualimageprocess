#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() : kernel(nullptr), kernel_height(0), kernel_width(0), stride(0), padding_value(false) {
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    kernel_height = kh;
    kernel_width = kw;
    stride = stride_val;
    padding_value= pad;
    kernel = new double*[kernel_height];
    for (int i = 0; i < kernel_height; ++i) {
        kernel[i] = new double[kernel_width];
        for (int j = 0; j < kernel_width; ++j) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {


    if(kernel != nullptr){
        for (int i = 0; i < kernel_height; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    kernel_height=other.kernel_height;
    kernel_width=other.kernel_width;
    stride=other.stride;
    padding_value=other.padding_value;

    kernel = new double*[kernel_height];
    for (int i = 0; i < kernel_height; ++i) {
        kernel[i] = new double[kernel_width];
        for (int j = 0; j < kernel_width; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {

    if (this == &other) {
        return *this; // self-assignment check
    }

    if(kernel != nullptr){
    for (int i = 0; i < kernel_height; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;
    }
    

    kernel_height=other.kernel_height;

    kernel_width=other.kernel_width;
    stride=other.stride;
    padding_value=other.padding_value;

    kernel = new double*[kernel_height];
    for (int i = 0; i < kernel_height; ++i) {
        kernel[i] = new double[kernel_width];
        for (int j = 0; j < kernel_width; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
    return *this;

}
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const { //It's for convolving the input image with a kernel and return the convolved image.
    int input_height = input_image.get_height();
    int input_width = input_image.get_width();
    int kh = kernel_height;
    int kw = kernel_width;

    int padding = padding_value ? 1 : 0;  // Checking the boolean value (padding_value) to


    int output_height = ((input_height - kh + 2 * padding) / stride) + 1;
    int output_width = ((input_width - kw + 2 * padding) / stride) + 1;



    ImageMatrix output_image(output_height, output_width);

    for (int i = 0; i < output_height; i++) {
        for (int j = 0; j < output_width; j++) {

            double sum = 0.0;

            for (int m = 0; m < kh; m++) {
                for (int n = 0; n < kw; n++) {
                    int input_row = i * stride + m - padding;
                    int input_col = j * stride + n - padding;
                    if (input_row >= 0 && input_row < input_height && input_col >= 0 && input_col < input_width) {
                        sum += input_image.get_data(input_row, input_col) * kernel[m][n]; // Pixels from the input image*kernel here ( Convolution )
                    }
                }
            }
            output_image.set_data(i, j, sum);
        }
    }

    return output_image;

}
