cmake_minimum_required(VERSION 3.19)
project(TransportEquation)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_HEADERS
        source/TransportEquationSolver/InterpolationFunctions.h
        source/math/MathUtils.h
        source/TransportEquationSolver/THINC1D.h
        source/TransportEquationSolver/THINCUtils.h
        source/Tests/TransportEquation1Dtests.cpp source/Tests/TransportEquation1Dtests.h)
set(PROJECT_SOURCES
        source/main.cpp
        source/TransportEquationSolver/InterpolationFunctions.cpp
        source/math/MathUtils.cpp
        source/TransportEquationSolver/THINC1D.cpp
        source/TransportEquationSolver/THINCUtils.cpp
        source/stuff/CompilerDifferenceHighlighter.cpp source/Tests/TransportEquation1Dtests.cpp source/Tests/TransportEquation1Dtests.h source/TransportEquationSolver/THINC1DparamsStruct.h)

add_executable(TransportEquation ${PROJECT_SOURCES} ${PROJECT_HEADERS})