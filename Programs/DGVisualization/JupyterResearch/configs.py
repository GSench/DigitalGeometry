from FileUtils import *

OutputDir = downDir(upDir(upDir(currentDir)), "Output")

CalculationResultsPath = downDir(OutputDir, "CalculationResults")

TECalculationsPath = downDir(CalculationResultsPath, "TransportEquation")
TE1DCalculationsPath = downDir(TECalculationsPath, "Solver1D")
TE2DCalculationsPath = downDir(TECalculationsPath, "Solver2D")

PlotOutputPath = downDir(OutputDir, "GraphicsResults")

TEPlotPath = downDir(PlotOutputPath, "TransportEquation")
TE1DPlotPath = downDir(TEPlotPath, "Solver1D")
TE2DPlotPath = downDir(TEPlotPath, "Solver2D")



