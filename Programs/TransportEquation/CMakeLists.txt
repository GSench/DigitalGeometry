cmake_minimum_required(VERSION 3.19)
project(TransportEquation)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_HEADERS
        source/TransportEquationSolver/InterpolationFunctions.h
        source/math/MathUtils.h
        source/TransportEquationSolver/Solver1D/Solver1D.h
        source/TransportEquationSolver/THINCUtils.h
        source/Tests/TransportEquation1Dtests.cpp source/Tests/TransportEquation1Dtests.h)
set(PROJECT_SOURCES
        source/main.cpp
        source/TransportEquationSolver/InterpolationFunctions.cpp
        source/math/MathUtils.cpp
        source/TransportEquationSolver/Solver1D/Solver1D.cpp
        source/TransportEquationSolver/THINCUtils.cpp
        source/stuff/CompilerDifferenceHighlighter.cpp
        source/Tests/TransportEquation1Dtests.cpp
        source/Tests/TransportEquation1Dtests.h
        source/TransportEquationSolver/Solver1D/Area1D.h
        source/TransportEquationSolver/Solver2D/Solver2D.cpp
        source/TransportEquationSolver/Solver2D/Solver2D.h
        source/math/VectorField2D.h source/math/Vector2D.h
        source/Tests/StandardSolver.cpp source/Tests/StandardSolver.h
        source/TransportEquationSolver/Solver1D/Solver1DOutput.h
        source/TransportEquationSolver/Solver1D/Solver1DOutput.cpp
        source/TransportEquationSolver/Solver1D/Solver1DInstances.h
        source/TransportEquationSolver/Solver1D/Solver1DInstances.cpp source/TransportEquationSolver/Solver1D/VectorField1D.cpp source/TransportEquationSolver/Solver1D/VectorField1D.h source/TransportEquationSolver/Solver2D/Area2D.h source/TransportEquationSolver/Solver2D/Solver2DInstances.cpp source/TransportEquationSolver/Solver2D/Solver2DInstances.h source/TransportEquationSolver/Solver1D/Area1D.cpp)

add_executable(TransportEquation ${PROJECT_SOURCES} ${PROJECT_HEADERS})