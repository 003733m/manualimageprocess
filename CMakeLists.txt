cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        .idea/.gitignore
        .idea/modules.xml
        .idea/src.iml
        .idea/workspace.xml
        Convolution.cpp
        Convolution.h
        DecodeMessage.cpp
        DecodeMessage.h
        EdgeDetector.cpp
        EdgeDetector.h
        EncodeMessage.cpp
        EncodeMessage.h
        ImageLoader.cpp
        ImageLoader.h
        ImageMatrix.cpp
        ImageMatrix.h
        ImageProcessor.cpp
        ImageProcessor.h
        ImageSharpening.cpp
        ImageSharpening.h
        main.cpp)
