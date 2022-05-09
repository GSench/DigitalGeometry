from FileUtils import *

OutputDir = downDir(upDir(upDir(currentDir)), "Output")

#------------------------------------------------------------------------
# Calculation Data
CalculationResultsPath = downDir(OutputDir, "CalculationResults")
#------------------------------------------------------------------------

# Transport Equation
TECalculationsPath = downDir(CalculationResultsPath, "TransportEquation")
TE1DCalcRes = downDir(TECalculationsPath, "Solver1D")
TE2DCalcRes = downDir(TECalculationsPath, "Solver2D")

# EulerEquation
EECalculationsPath = downDir(CalculationResultsPath, "EulerEquation")
EE1DCalcRes = downDir(EECalculationsPath, "Solver1D")
EE2DCalcRes = downDir(EECalculationsPath, "Solver2D")

# DigitalGeometry
DGCalculationsPath = downDir(CalculationResultsPath, "DigitalGeometry")
DG1DCalcRes = downDir(DGCalculationsPath, "Solver1D")
DG2DCalcRes = downDir(DGCalculationsPath, "Solver2D")


#------------------------------------------------------------------------
# Plot results
PlotOutputPath = downDir(OutputDir, "GraphicsResults")
#------------------------------------------------------------------------

# Transport Equation
TEPlotPath = downDir(PlotOutputPath, "TransportEquation")
TE1DPlotRes = downDir(TEPlotPath, "Solver1D")
TE2DPlotPath = downDir(TEPlotPath, "Solver2D")

# EulerEquation
EEPlotPath = downDir(PlotOutputPath, "EulerEquation")
EE1DPlotRes = downDir(EEPlotPath, "Solver1D")
EE2DPlotPath = downDir(EEPlotPath, "Solver2D")

# DigitalGeometry
DGPlotPath = downDir(PlotOutputPath, "DigitalGeometry")
DG1DPlotRes = downDir(DGPlotPath, "Solver1D")
DG2DPlotPath = downDir(DGPlotPath, "Solver2D")


