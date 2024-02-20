#include "EncodeMessage.h"
#include <cmath>

using namespace std;

// Default Constructor
EncodeMessage::EncodeMessage() = default;

// Destructor
EncodeMessage::~EncodeMessage() = default;

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    ImageMatrix encodedImage = img; // Copying the img reference here, we will change smth in encodedImage below.

    for (size_t i = 0; i < message.length(); i++) {
        if (primeControl(positions[i].first)) { // If it returns true(the value is prime number) we will calculate process here.
            int fibonacciNumber = calculateFibonacciNumber(positions[i].first);
            int currentedASCI = message[i] + fibonacciNumber; // I'm adding the fibo number to our message the get the current ASCII that I mentioned as currrentedASCI.
            currentedASCI = max(33, min(currentedASCI, 126)); // Bordering the currentedASCI between 33-126.
            encodedImage.set_data(positions[i].first, positions[i].second,currentedASCI); // Updating the encoded image's value here as currentedASCII.
        }
    }

    int shiftAmount = message.length() / 2; // Shifting clockwise rotation.
    string shiftedMessage = message;
    for (size_t i = 0; i < message.length(); i++) {
        shiftedMessage[i] = message[(i + shiftAmount) % message.length()]; // New location.
    }
    size_t pixelIndex = 0;
    for (size_t i = 0; i < positions.size(); i++) {
        int x = positions[i].first;
        int y = positions[i].second;
        if (pixelIndex < shiftedMessage.length()) {

            int bit = shiftedMessage[pixelIndex];
            int currentPixelValue = encodedImage.get_data(x, y);
            currentPixelValue = (currentPixelValue & 0xFE) | bit; // I learned the 0xFE turns the all bits 1 except the lsb. And | this updating the currentPixelValue by the bit value as lsb!
            encodedImage.set_data(x, y, currentPixelValue); // I'm replacing the currentpixelvalue bit with our old lsb here.
            pixelIndex++;
        }

    }

    return encodedImage;
}

bool EncodeMessage::primeControl(int n) { // I'm controlling the value if it's prime number or not.
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int EncodeMessage::calculateFibonacciNumber(int m) { // I'm calculating the fibonacci number here by the fibonacci rules.
    if (m <= 0) return 0; // If it's 0 result is 0.
    if (m == 1) return 1;  // If it's 1, 0+1=1;
    int a = 0, b = 1;
    for (int i = 2; i <= m; i++) { // Summing process up to n.
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b;
}
