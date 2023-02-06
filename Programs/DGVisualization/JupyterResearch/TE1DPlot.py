import matplotlib.pyplot as plt
from matplotlib import animation
from celluloid import Camera
from FileUtils import *


def xCells(cellCount, dx):
    #https://stackoverflow.com/questions/31820107/is-there-a-numpy-function-that-allows-you-to-specify-start-step-and-number
    return [dx/2+i*dx for i in range(cellCount)]


def plotArea1D(cellCount, dx, frame, plotTitle, plotOutPath, showPic):
    fig = plt.figure(figsize=(24, 8))
    ax = plt.axes(xlim=(0, dx*cellCount), ylim=(-0.1, 3))
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



def animation1D(cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames, slowmo, plotTitle, plotOutPath):
    fig = plt.figure(figsize=(24, 9))
    ax = plt.axes(xlim=(0, dx*cellCount), ylim=(-0.1, 3))
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
    
    
    
    
    
    
    
    
    
    
    
    