#include "ImageProcessor.h"
#include "ImageSharpening.h"
#include "EdgeDetector.h"
#include "DecodeMessage.h"
#include "EncodeMessage.h"
//Implementing the other classes for doing final steps together clearly.


using namespace std;

ImageProcessor::ImageProcessor() = default;



ImageProcessor::~ImageProcessor() = default;

std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) { // Doing the steps orderly for the result.



    ImageSharpening sharpening;
    ImageMatrix sharpenedImage = sharpening.sharpen(img,2.0); // As you explained the K value later, I accept k=2 for this class.


    EdgeDetector edgeDetector;
    vector<pair<int, int>> edgePixels = EdgeDetector::detectEdges(sharpenedImage); // Finding the edges by our function, and it's our edgePixels value here for the next function(DecodeFromImage)
  //edgeDetector.
    DecodeMessage decoder;      
    string decodedMessage = decoder.decodeFromImage(sharpenedImage, edgePixels);  // Decoding the edgePixels which I found it by the edgeDetector.detectEdges here.//img


    return decodedMessage;

}



ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {

    ImageSharpening sharpening;
    ImageMatrix sharpenedImage = sharpening.sharpen(img,2.0); // As you explained the K value later, I accept k=2 for this class.

    EdgeDetector edgeDetector;
    vector<pair<int, int>> edgePixels = EdgeDetector::detectEdges(sharpenedImage);


    EncodeMessage encoder;
    ImageMatrix encodedImage = encoder.encodeMessageToImage(img, message, edgePixels); // And here I'm placing the password into our image.


    return encodedImage;
}