// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>
#include <bitset>
#include <cstring>
#include <cstdint>

using namespace std; // I'm generally using namespace std, especially for creating variables in functions teacher.

std::string pad_with_zeros(string binary_string, int length) { // Using a padding function here.
    string padded_string(length - binary_string.length(), '0');
    return padded_string.append(binary_string);
}

// Default constructor
DecodeMessage::DecodeMessage() =default;
    // Nothing specific to initialize here

// Destructor
DecodeMessage::~DecodeMessage() =default;
    // Nothing specific to clean up
    

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<pair<int, int>>& edgePixels) {


    string binaryMessage;
    for (const auto& pixel : edgePixels) { // Extracting LSB's from the edgePixels.
        int lsb = getLSB(image.get_data(pixel.first, pixel.second));
        binaryMessage += to_string(lsb);
    }

    while (binaryMessage.length() % 7 != 0) {
       binaryMessage = pad_with_zeros(binaryMessage, static_cast<int>(binaryMessage.length() + 1));
        //binaryMessage = pad_with_zeros(binaryMessage, binaryMessage.length() + 1); // I was getting type casting error here so I updated it and it's better with static_cast rn here.
    }

    string asciiMessage = binaryToASCII(binaryMessage);//I'm using the function that I created in this class to help me.
    string decodedMessage ;

    for (char decodedChar : asciiMessage) {
        decodedMessage += decodedChar;
    }

    return decodedMessage;

}


int DecodeMessage::getLSB(double value) { // Most significant bit getter.

    int lsb = static_cast<int>(value);
    return lsb & 1;

    //unsigned long long binaryRep; // This using type occurs an error so I changed with other using.
    //memcpy(&binaryRep, &value, sizeof(value)); // Using the memcpy to copying the memory here.
    //return binaryRep & 1;
}


std::string DecodeMessage::binaryToASCII(const std::string& binaryMessage) {  // This turns to binary values into the ASCII ones.
    string asciiMessage;
    for (int i = 0; i < binaryMessage.length(); i += 7) {
        string segment = binaryMessage.substr(i, 7);
        int decimalValue = bitset<7>(segment).to_ulong(); // Creating a bit set and turning it into an integer value by to_ulong.


        if (decimalValue <= 32) {
            decimalValue += 33;
        } else if (decimalValue == 127) {
            decimalValue = 126;
        }

        asciiMessage += static_cast<char>(decimalValue); // Typecasting
    }
    return asciiMessage;
}