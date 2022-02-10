from FileUtils import *

OutputDir = downDir(upDir(upDir(currentDir)), "Output")

CalculationResultsPath = downDir(OutputDir, "CalculationResults")
Calculation1DResultsPath = downDir(CalculationResultsPath, "Solver1D")
Calculation2DResultsPath = downDir(CalculationResultsPath, "Solver2D")

PlotOutputPath = downDir(OutputDir, "GraphicsResults")
Plot1DOutputPath = downDir(PlotOutputPath, "Solver1D")
Plot2DOutputPath = downDir(PlotOutputPath, "Solver2D")



