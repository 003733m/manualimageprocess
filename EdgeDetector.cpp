// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>
#include "Convolution.h"

using namespace std;


// Default constructor
EdgeDetector::EdgeDetector() = default;

// Destructor
EdgeDetector::~EdgeDetector() = default;

// Detect Edges using the given algorithm
vector<pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    int Gx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };

    int Gy[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
    };

    double** GxDouble = new double*[3];
    double** GyDouble = new double*[3];

    for (int i = 0; i < 3; i++) {
        GxDouble[i] = new double[3];
        GyDouble[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            GxDouble[i][j] = static_cast<double>(Gx[i][j]); // Casting our int matrices to double here.
            GyDouble[i][j] = static_cast<double>(Gy[i][j]);
        }
    }

    Convolution convolutionGx(GxDouble, 3, 3, 1, true);
    Convolution convolutionGy(GyDouble, 3, 3, 1, true);


    ImageMatrix Ix = convolutionGx.convolve(input_image); // Calling the convolve function again here like in the Image Sharpening class.
    ImageMatrix Iy = convolutionGy.convolve(input_image);



    int width=input_image.get_width();
    int height=input_image.get_height();

    vector<vector<double>> magnitude(height, vector<double>(width, 0.0));

    for (int y = 0; y < height; y++) { // Doing the Gradient calculating process here.
        for (int x = 0; x < width; x++) {
            double gradient = sqrt(pow(Ix.get_data(y, x), 2) + pow(Iy.get_data(y, x), 2));
            magnitude[y][x] = gradient; // Adding the gradient values into the mangitude's values.
        }
    }

    double sum_magnitude = 0.0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            sum_magnitude += magnitude[y][x];
        }
    }
    double average_magnitude = sum_magnitude / (height * width); // Calculating the threshold by the formula. (height * width=total number of elements)
    int threshold = static_cast<int>(average_magnitude);


    vector<pair<int, int>> edgePixels; // Using the edge_pixels vector for pushing the values as appropriate threshold.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (magnitude[y][x] > threshold) { // Checking fo threshold value.
                edgePixels.emplace_back(y, x);
                //edgePixels.push_back(make_pair(y, x));
            }
        }

    }




    return edgePixels;

}




