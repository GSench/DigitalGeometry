cmake_minimum_required(VERSION 3.19)
project(TransportEquation)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_HEADERS
        InterpolationFunctions.h
        MathUtils.h
        THINC1D.h
        THINCUtils.h
        )
set(PROJECT_SOURCES
        main.cpp
        InterpolationFunctions.cpp
        MathUtils.cpp
        THINC1D.cpp
        THINCUtils.cpp
        CompilerDifferenceHighlighter.cpp)

add_executable(TransportEquation ${PROJECT_SOURCES} ${PROJECT_HEADERS})