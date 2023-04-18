from configs import *
from TE1DOutput import *
from FileUtils import *
from TE1DPlot import *

def TE1DTestVisualization(testDir, plotDir, testTitle, testFile, timeStepInterval, animationSlow, showPics, minY = 0, maxY = 0):
    calcResPath = downDir(testDir, testTitle)
    plotOutPath = downDir(plotDir, testTitle)
    
    cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames = read1DMinimalOutput(downDir(calcResPath, testFile))
    
    if minY==0:
        minY = min(0, min([min(y) for y in frames]))-1
    if maxY==0:
        maxY = max([max(y) for y in frames])+1
    
    for t in range(0, len(frames), timeStepInterval):
        plotArea1D(cellCount, dx, frames[t], testTitle+"_t"+str(t), plotOutPath, showPics, minY, maxY)
    
    animation1D(cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames, animationSlow, testTitle, plotOutPath, minY, maxY)

def TEGS1DTestVisualization(testDir, plotDir, testTitle, testFile, timeStepInterval, animationSlow, showPics, minVF=0, maxVF=0, minU=0, maxU=0, minD=0, maxD=0, minP=0, maxP=0):
    calcResPath = downDir(testDir, testTitle)
    plotOutPath = downDir(plotDir, testTitle)
    
    cellCount, dx, NTimeSteps, realNTimeSteps, dt, VolumeFraction, Velocity, Density, Pressure = readGS1DMinimalOutput(downDir(calcResPath, testFile))
    
    if minVF==maxVF:
        minVF = min(0, min([min(y) for y in VolumeFraction]))-0.1
        maxVF = max([max(y) for y in VolumeFraction])+0.1
    
    if minU==maxU:
        minU = min(0, min([min(y) for y in Velocity]))-0.1
        maxU = max([max(y) for y in Velocity])+0.1
    
    if minD==maxD:
        minD = min(0, min([min(y) for y in Density]))-0.1
        maxD = max([max(y) for y in Density])+0.1
        
    if minP==maxP:
        minP = min(0, min([min(y) for y in Pressure]))-0.1
        maxP = max([max(y) for y in Pressure])+0.1
    
    for t in range(0, len(VolumeFraction), timeStepInterval):
        plotAreaGS1D(cellCount, dx, VolumeFraction[t], Velocity[t], Density[t], Pressure[t], testTitle+"_t"+str(t), plotOutPath, showPics, minVF, maxVF, minU, maxU, minD, maxD, minP, maxP)
        
    animationGS1D(cellCount, dx, NTimeSteps, realNTimeSteps, dt, VolumeFraction, Velocity, Density, Pressure, animationSlow, testTitle, plotOutPath, minVF, maxVF, minU, maxU, minD, maxD, minP, maxP)
