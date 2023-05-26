cmake_minimum_required(VERSION 3.19)
project(TransportEquation)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(PROJECT_HEADERS

        )
set(PROJECT_SOURCES
        ##source/DGProblem/DGSolver1D/DGSolver1D.cpp
        ##source/DGProblem/DGSolver1D/DGSolver1D.h
        ##source/DGProblem/DGSolver1D/DGSolver1DParams.cpp
        ##source/DGProblem/DGSolver1D/DGSolver1DParams.h
        ##source/DGProblem/DGSolver2D/DGSolver2D.cpp
        ##source/DGProblem/DGSolver2D/DGSolver2D.h
        ##source/DGProblem/DGSolver2D/DGSolver2DOutput.cpp
        ##source/DGProblem/DGSolver2D/DGSolver2DOutput.h
        ##source/DGProblem/DGSolver2D/DGSolver2DParams.cpp
        ##source/DGProblem/DGSolver2D/DGSolver2DParams.h
        ##source/DGProblem/Tools/VectorFieldCalculation.cpp
        ##source/DGProblem/Tools/VectorFieldCalculation.h
        ##source/EulerEquationProblem/EESolver1D/EESolver1D.cpp
        ##source/EulerEquationProblem/EESolver1D/EESolver1D.h
        ##source/EulerEquationProblem/EESolver1D/EESolver1DParams.cpp
        ##source/EulerEquationProblem/EESolver1D/EESolver1DParams.h
        ##source/EulerEquationProblem/EESolver2D/EESolver2D.cpp
        ##source/EulerEquationProblem/EESolver2D/EESolver2D.h
        ##source/EulerEquationProblem/EESolver2D/EESolver2DOutput.cpp
        ##source/EulerEquationProblem/EESolver2D/EESolver2DOutput.h
        ##source/EulerEquationProblem/EESolver2D/EESolver2DParams.cpp
        ##source/EulerEquationProblem/EESolver2D/EESolver2DParams.h
        ##source/EulerEquationProblem/Tools/IntegrationTools.cpp
        ##source/EulerEquationProblem/Tools/IntegrationTools.h
        ##source/Tests/DigitalGeometryTests1D.cpp
        ##source/Tests/DigitalGeometryTests1D.h
        ##source/Tests/DigitalGeometryTests2D.cpp
        ##source/Tests/DigitalGeometryTests2D.h
        ##source/Tests/EulerEquation1Dtests.cpp
        ##source/Tests/EulerEquation1Dtests.h
        ##source/Tests/EulerEquation2Dtests.cpp
        ##source/Tests/EulerEquation2Dtests.h
        ##source/Tests/StandardSolver.cpp source/Tests/StandardSolver.h
        source/Tests/Tests.cpp
        source/Tests/Tests.h
        source/Tests/TransportEquation1Dtests.cpp
        source/Tests/TransportEquation1Dtests.h
        ##source/Tests/TransportEquation2Dtests.cpp
        ##source/Tests/TransportEquation2Dtests.h
        ##source/TransportEquationSolver/Instances/Area1D.cpp
        ##source/TransportEquationSolver/Instances/Area1D.h
        ##source/TransportEquationSolver/Instances/Area2D.h
        ##source/TransportEquationSolver/Instances/RBVectorField1D.cpp
        ##source/TransportEquationSolver/Instances/RBVectorField1D.h
        ##source/TransportEquationSolver/Instances/RBVectorField2D.cpp
        ##source/TransportEquationSolver/Instances/RBVectorField2D.h
        source/TransportEquationSolver/Instances/TESolver1DInstances.cpp
        source/TransportEquationSolver/Instances/TESolver1DInstances.h
        ##source/TransportEquationSolver/Instances/VectorField1D.cpp
        ##source/TransportEquationSolver/Instances/VectorField1D.h
        ##source/TransportEquationSolver/Instances/VectorField2D.cpp
        ##source/TransportEquationSolver/Instances/VectorField2D.h
        source/TransportEquationSolver/Methods/OverEdgeFlow.h
        source/TransportEquationSolver/Methods/ContinuousSolidFlow.h
        source/TransportEquationSolver/Methods/Mesh.h
        source/TransportEquationSolver/Methods/TimeStepVelocity.h
        ##source/TransportEquationSolver/Solver1D/TERBJRSolver1D.cpp
        ##source/TransportEquationSolver/Solver1D/TERBJRSolver1D.h
        ##source/TransportEquationSolver/Solver1D/TERBSolver1D.cpp
        ##source/TransportEquationSolver/Solver1D/TERBSolver1D.h
        source/TransportEquationSolver/Solver1D/TESolver1D.cpp
        source/TransportEquationSolver/Solver1D/TESolver1D.h
        source/TransportEquationSolver/Solver1D/TESolver1DOutput.cpp
        source/TransportEquationSolver/Solver1D/TESolver1DOutput.h
        source/TransportEquationSolver/Solver1D/TESolver1DParams.h
        ##source/TransportEquationSolver/Solver2D/TERBJRSolver2D.cpp
        ##source/TransportEquationSolver/Solver2D/TERBJRSolver2D.h
        ##source/TransportEquationSolver/Solver2D/TERBSolver2D.cpp
        ##source/TransportEquationSolver/Solver2D/TERBSolver2D.h
        ##source/TransportEquationSolver/Solver2D/TESolver2D.cpp
        ##source/TransportEquationSolver/Solver2D/TESolver2D.h
        ##source/TransportEquationSolver/Solver2D/TESolver2DOutput.cpp
        ##source/TransportEquationSolver/Solver2D/TESolver2DOutput.h
        ##source/TransportEquationSolver/Solver2D/TESolver2DParams.cpp
        ##source/TransportEquationSolver/Solver2D/TESolver2DParams.h
        source/TransportEquationSolver/Tools/InterpolationFunctions.cpp
        source/TransportEquationSolver/Tools/InterpolationFunctions.h
        source/TransportEquationSolver/Tools/JRUtils.cpp
        source/TransportEquationSolver/Tools/JRUtils.h
        source/TransportEquationSolver/Tools/THINCUtils.cpp
        source/TransportEquationSolver/Tools/THINCUtils.h
        source/Utils/ArrayUtils.cpp
        source/Utils/ArrayUtils.h
        source/Utils/FileUtils.cpp
        source/Utils/FileUtils.h
        source/configs.cpp
        source/configs.h
        source/main.cpp
        source/math/Constants.h
        source/math/MathUtils.cpp
        source/math/MathUtils.h
        source/math/Vector.h
        #source/math/VectorMeshTools.cpp
        #source/math/VectorMeshTools.h
        #source/stuff/CompilerDifferenceHighlighter.cpp
        source/TransportEquationSolver/Methods/Mesh.cpp
        source/Utils/TimeLogger.cpp
        source/Utils/TimeLogger.h
        source/TransportEquationSolver/Methods/GSQuantity.h
        source/TransportEquationSolver/Methods/GSFlow.h
        source/TransportEquationSolver/Tools/RiemannProblem.cpp
        source/TransportEquationSolver/Tools/RiemannProblem.h
        source/TransportEquationSolver/Methods/SQuantity.h
        source/TransportEquationSolver/Methods/SFlow.h
        source/UnitTests/math/UTVector.cpp
        source/UnitTests/math/UTVector.h
        source/UnitTests/UnitTestsLauncher.cpp
        source/UnitTests/UnitTestsLauncher.h
        source/UnitTests/TransportEquationSolver/Methods/UTSQuantityFlow.cpp
        source/UnitTests/TransportEquationSolver/Methods/UTSQuantityFlow.h
        source/UnitTests/TransportEquationSolver/Methods/UTMesh.cpp
        source/UnitTests/TransportEquationSolver/Methods/UTMesh.h
        source/TransportEquationSolver/Methods/GasSolidFlow.h source/TransportEquationSolver/Methods/PostProcessors.cpp source/TransportEquationSolver/Methods/PostProcessors.h source/TransportEquationSolver/Methods/FlowMachine.h source/TransportEquationSolver/Methods/SolidFlowMachine.h source/TransportEquationSolver/Methods/GasSolidFlowMachine.h source/Utils/Logger.h)

add_executable(TransportEquation ${PROJECT_SOURCES} ${PROJECT_HEADERS})