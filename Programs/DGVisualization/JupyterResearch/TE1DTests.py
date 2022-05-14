from configs import *
from TE1DOutput import *
from FileUtils import *
from TE1DPlot import *

def TE1DTestVisualization(testDir, plotDir, testTitle, testFile, timeStepInterval, animationSlow, showPics):
    calcResPath = downDir(testDir, testTitle)
    plotOutPath = downDir(plotDir, testTitle)
    
    cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames = read1DMinimalOutput(downDir(calcResPath, testFile))
    
    for t in range(0, len(frames), timeStepInterval):
        plotArea1D(cellCount, dx, frames[t], testTitle+"_t"+str(t), plotOutPath, showPics)
    
    animation1D(cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames, animationSlow, testTitle, plotOutPath)
    