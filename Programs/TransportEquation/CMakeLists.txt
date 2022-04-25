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
        source/math/Vector2D.h
        source/Tests/StandardSolver.cpp source/Tests/StandardSolver.h
        source/TransportEquationSolver/Solver1D/Solver1DOutput.h
        source/TransportEquationSolver/Solver1D/Solver1DOutput.cpp
        source/TransportEquationSolver/Solver1D/Solver1DInstances.h
        source/TransportEquationSolver/Solver1D/Solver1DInstances.cpp
        source/TransportEquationSolver/Solver1D/VectorField1D.cpp
        source/TransportEquationSolver/Solver1D/VectorField1D.h
        source/TransportEquationSolver/Solver2D/Area2D.h
        source/TransportEquationSolver/Solver2D/TESolver2DParams.cpp
        source/TransportEquationSolver/Solver2D/TESolver2DParams.h
        source/TransportEquationSolver/Solver1D/Area1D.cpp
        source/TransportEquationSolver/Solver2D/VectorField2D.cpp
        source/TransportEquationSolver/Solver2D/VectorField2D.h
        source/TransportEquationSolver/Solver2D/Solver2DOutput.cpp
        source/TransportEquationSolver/Solver2D/Solver2DOutput.h
        source/Tests/TransportEquation2Dtests.cpp
        source/Tests/TransportEquation2Dtests.h
        source/configs.h
        source/configs.cpp
        source/Tests/Tests.cpp
        source/Tests/Tests.h
        source/Utils/FileUtils.cpp
        source/Utils/FileUtils.h
        source/Utils/ArrayUtils.cpp
        source/Utils/ArrayUtils.h
        source/EulerEquationProblem/EESolver1D/EESolver1D.cpp
        source/EulerEquationProblem/EESolver1D/EESolver1D.h
        source/EulerEquationProblem/EESolver2D/EESolver2D.cpp
        source/EulerEquationProblem/EESolver2D/EESolver2D.h
        source/Tests/EulerEquation1Dtests.cpp
        source/Tests/EulerEquation1Dtests.h
        source/Tests/EulerEquation2Dtests.cpp
        source/Tests/EulerEquation2Dtests.h
        source/DGProblem/DGSolver1D/DGSolver1D.cpp
        source/DGProblem/DGSolver1D/DGSolver1D.h
        source/DGProblem/DGSolver2D/DGSolver2D.cpp
        source/DGProblem/DGSolver2D/DGSolver2D.h
        source/Tests/DigitalGeometryTests1D.cpp
        source/Tests/DigitalGeometryTests1D.h
        source/Tests/DigitalGeometryTests2D.cpp
        source/Tests/DigitalGeometryTests2D.h
        source/EulerEquationProblem/EESolver1D/EESolver1DParams.cpp
        source/EulerEquationProblem/EESolver1D/EESolver1DParams.h source/TransportEquationSolver/Solver1D/TESolver1DParams.h)

add_executable(TransportEquation ${PROJECT_SOURCES} ${PROJECT_HEADERS})