import os
# https://stackoverflow.com/questions/9856683/using-pythons-os-path-how-do-i-go-up-one-directory

def upDir(directory):
    return os.path.dirname(directory)
def downDir(directory, subdir):
    return os.path.join(directory, subdir)
def filename(filepath):
    _, fname = os.path.split(filepath)
    return fname
def listSubdirs(directory):
    return [subdir[0] for subdir in os.walk(directory)][1:]

currentDir = os.getcwd()

OutputDir = downDir(upDir(upDir(currentDir)), "Output")

CalculationResultsPath = downDir(OutputDir, "CalculationResults")
Calculation1DResultsPath = downDir(CalculationResultsPath, "Solver1D")
Calculation2DResultsPath = downDir(CalculationResultsPath, "Solver2D")

PlotOutputPath = downDir(OutputDir, "GraphicsResults")
Plot1DOutputPath = downDir(PlotOutputPath, "Solver1D")
Plot2DOutputPath = downDir(PlotOutputPath, "Solver2D")



