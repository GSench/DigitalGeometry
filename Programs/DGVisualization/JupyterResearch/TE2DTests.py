from configs import *
from TE2DOutput import *
from FileUtils import *
from TE2DPlot import *

def TE2DTestVisualization(testDir, plotDir, testTitle, testFile, timeStepInterval, animationSlow, highlightAnimation):
    calcResPath = downDir(testDir, testTitle)
    plotOutPath = downDir(plotDir, testTitle)
    
    cellCountX, cellCountY, dx, NTimeSteps, realNTimeSteps, dt, frames = read2DOutput(downDir(calcResPath, testFile))
    
    print("cellCountX: ", cellCountX)
    print("cellCountY: ", cellCountY)
    print("dx: ", dx)
    print("NTimeSteps: ", NTimeSteps)
    print("realNTimeSteps: ", realNTimeSteps)
    print("dt: ", dt)
    
    for t in range(0, len(frames), timeStepInterval):
        plotArea2D(frames[t], testTitle+"_t"+str(t), plotOutPath)
        
    plotArea2DFrames(frames, testTitle, 3, plotOutPath)
    
    animation2D(cellCountX, cellCountY, dx, NTimeSteps, realNTimeSteps, dt, frames, animationSlow, testTitle, plotOutPath, False)
    if highlightAnimation:
        animation2D(cellCountX, cellCountY, dx, NTimeSteps, realNTimeSteps, dt, frames, animationSlow, testTitle, plotOutPath, True)
    
