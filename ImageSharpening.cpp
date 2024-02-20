#include "ImageSharpening.h"
#include "Convolution.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    kernel_height=3;// As report's said I got the dimensions as threes.
    kernel_width=3;
    blurring_kernel= new double * [kernel_height];
    for (int i =0; i < kernel_height;i ++ ){ // Creating the basic kernel which we will use on sharpening process.
        blurring_kernel[i]=new double[kernel_width];
        for(int j =0; j< kernel_width; j++){
            blurring_kernel[i][j]=1.0/9.0;

        }

    }

}

ImageSharpening::~ImageSharpening(){ // Defining the destructor
    for ( int i =0; i< kernel_height; i++){
        delete[] blurring_kernel[i];
    }

    delete [] blurring_kernel;

}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {


    Convolution convolution(blurring_kernel, kernel_height, kernel_width, 1, true);
    ImageMatrix blurred_img = convolution.convolve(input_image); // I'm calling the convolve function that I created in Convolution class to go to next step here.

    int input_height = input_image.get_height();
    int input_width = input_image.get_width();
    ImageMatrix sharpened_img(input_height, input_width);

    for (int y = 0; y < input_height; y++) {
        for (int x = 0; x < input_width; x++) {
            double first_pixel = input_image.get_data(y, x);
            double blurred_pixel = blurred_img.get_data(y, x);
            double sharpened_pixel = first_pixel + k * (first_pixel - blurred_pixel); // SharpImg ← InputImg + k × (InputImg − BlurredImg) doing this step here.

            if (sharpened_pixel < 0.0) {
                sharpened_pixel = 0.0;
            } else if (sharpened_pixel > 255.0) {
                sharpened_pixel = 255.0;
            }
            sharpened_img.set_data(y, x, sharpened_pixel);
        }
    }

    return sharpened_img;
}
