import matplotlib.pyplot as plt
from matplotlib import animation
from celluloid import Camera
from FileUtils import *


def xCells(cellCount, dx):
    #https://stackoverflow.com/questions/31820107/is-there-a-numpy-function-that-allows-you-to-specify-start-step-and-number
    return [dx/2+i*dx for i in range(cellCount)]


def plotArea1D(cellCount, dx, frame, plotTitle, plotOutPath, showPic, yMin, yMax):
    fig = plt.figure(figsize=(12, 4))
    plt.rcParams.update({'font.size': 10})
    ax = plt.axes(xlim=(0, dx*cellCount), ylim=(yMin, yMax))
    ax.grid()
    ax.set(xlabel='x', ylabel='f')

    x = xCells(cellCount, dx)
    y = frame

    plt.plot(x, y, 'b-')

    if cellCount < 100:
        plt.plot(x, y, 'ro')
        for i,j in zip(x,y):
            ax.annotate("{:10.4f}".format(j),xy=(i,j), ha='left', rotation=90)

    plt.title(plotTitle)
    plt.savefig(downDir(plotOutPath, plotTitle + ".png"))
    if showPic:
        plt.show()



def animation1D(cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames, slowmo, plotTitle, plotOutPath, minY, maxY):
    fig = plt.figure(figsize=(12, 4))
    plt.rcParams.update({'font.size': 10})
    ax = plt.axes(xlim=(0, dx*cellCount), ylim=(minY, maxY))
    ax.grid()
    
    x = xCells(cellCount, dx)
    
    camera = Camera(fig)
    for frame in frames:
        y = frame
        plt.plot(x, y, 'b-')
        if cellCount < 100:
            plt.plot(x, y, 'ro')
            for i,j in zip(x,y):
                ax.annotate("{:10.4f}".format(j),xy=(i,j), ha='left', rotation=90)
    
        camera.snap()

    animation = camera.animate()

    time = dt * NTimeSteps
    print("Animation time: ", time)
    realTimeStep = time / realNTimeSteps * slowmo
    print("Animation real time step: ", realTimeStep)
    fps = 1 / realTimeStep
    print("Animation fps: ", fps)

    animation.save(downDir(plotOutPath, plotTitle + "_anim.gif"), writer='PillowWriter', fps=fps)
    
def drawAreaGS1D(fig, axs, x, VolumeFraction, Velocity, Density, Pressure):
    axs[0].plot(x, VolumeFraction, 'r-')
    axs[1].plot(x, Velocity, 'g-')
    axs[2].plot(x, Density, 'b-')
    axs[3].plot(x, Pressure, 'r-')

def setupAreaGS1D(fig, axs, cellCount, dx, minVF=0, maxVF=0, minU=0, maxU=0, minD=0, maxD=0, minP=0, maxP=0):
    
    # Volume fraction
    #____________________________________________________
    axs[0].set_xlim([0, dx*cellCount])
    if minVF!=maxVF:
        axs[0].set_ylim([minVF, maxVF])
    axs[0].grid()
    axs[0].set(xlabel='x', ylabel='Volume fraction')
    
    # Velocity
    #____________________________________________________
    axs[1].set_xlim([0, dx*cellCount])
    if minU!=maxU:
        axs[1].set_ylim([minU, maxU])
    axs[1].grid()
    axs[1].set(xlabel='x', ylabel='Velocity')
    
    # Density
    #____________________________________________________
    axs[2].set_xlim([0, dx*cellCount])
    if minD!=maxD:
        axs[2].set_ylim([minD, maxD])
    axs[2].grid()
    axs[2].set(xlabel='x', ylabel='Density')
    
    # Pressure
    #____________________________________________________
    axs[3].set_xlim([0, dx*cellCount])
    if minP!=maxP:
        axs[3].set_ylim([minP, maxP])
    axs[3].grid()
    axs[3].set(xlabel='x', ylabel='Pressure')
    


def plotAreaGS1D(cellCount, dx, VolumeFraction, Velocity, Density, Pressure, plotTitle, plotOutPath, showPic, minVF=0, maxVF=0, minU=0, maxU=0, minD=0, maxD=0, minP=0, maxP=0):
    plt.rcParams.update({'font.size': 14})
    fig, axs = plt.subplots(4, 1, figsize=(12, 16))
    fig.suptitle(plotTitle)
    setupAreaGS1D(fig, axs, cellCount, dx, minVF, maxVF, minU, maxU, minD, maxD, minP, maxP)
    x = xCells(cellCount, dx)
    drawAreaGS1D(fig, axs, x, VolumeFraction, Velocity, Density, Pressure)
    plt.savefig(downDir(plotOutPath, plotTitle + ".png"))
    if showPic:
        plt.show()

def animationGS1D(cellCount, dx, NTimeSteps, realNTimeSteps, dt, VolumeFraction, Velocity, Density, Pressure, slowmo, plotTitle, plotOutPath, minVF=0, maxVF=0, minU=0, maxU=0, minD=0, maxD=0, minP=0, maxP=0):
    plt.rcParams.update({'font.size': 16})
    fig, axs = plt.subplots(4, 1, figsize=(12, 16))
    fig.suptitle(plotTitle)
    setupAreaGS1D(fig, axs, cellCount, dx, minVF, maxVF, minU, maxU, minD, maxD, minP, maxP)
    x = xCells(cellCount, dx)
    
    camera = Camera(fig)
    for t in range(len(VolumeFraction)):
        drawAreaGS1D(fig, axs, x, VolumeFraction[t], Velocity[t], Density[t], Pressure[t])
        camera.snap()

    animation = camera.animate()

    time = dt * NTimeSteps
    print("Animation time: ", time)
    realTimeStep = time / realNTimeSteps * slowmo
    print("Animation real time step: ", realTimeStep)
    fps = 1 / realTimeStep
    print("Animation fps: ", fps)

    animation.save(downDir(plotOutPath, plotTitle + "_anim.gif"), writer='PillowWriter', fps=fps)
    

    
    
    
    
    
    
    