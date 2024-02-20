#ifndef IMAGE_SHARPENING_H
#define IMAGE_SHARPENING_H

#include "ImageMatrix.h"
#include "Convolution.h"

class ImageSharpening {
    public:
        ImageSharpening(); // default constructor
        ~ImageSharpening(); 

        ImageMatrix sharpen(const ImageMatrix& input_image, double k);  

    private:
    int kernel_height ;
    int kernel_width ;
    double** blurring_kernel;

        // add your private functions and variables 
};

#endif // IMAGE_SHARPENING_H



