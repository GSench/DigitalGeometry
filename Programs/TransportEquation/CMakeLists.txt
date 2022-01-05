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
        source/TransportEquationSolver/Solver2D/PsyScalar.h
        source/TransportEquationSolver/Solver2D/Solver2D.cpp
        source/TransportEquationSolver/Solver2D/Solver2D.h
        source/math/VectorField2D.h source/math/Vector2D.h
        source/TransportEquationSolver/Solver2D/PsyScalarUtils.cpp
        source/TransportEquationSolver/Solver2D/PsyScalarUtils.h
        source/Tests/StandardSolver.cpp source/Tests/StandardSolver.h
        source/TransportEquationSolver/Solver1D/Solver1DOutput.h source/TransportEquationSolver/Solver1D/Solver1DOutput.cpp)

add_executable(TransportEquation ${PROJECT_SOURCES} ${PROJECT_HEADERS})