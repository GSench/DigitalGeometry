import matplotlib.pyplot as plt
from celluloid import Camera
from FileUtils import *

def lowValueHighlighter(f):
    fh = []
    for y in range(len(f)):
        fh.append([])
        for x in range(len(f[y])):
            fh[y].append(pow(abs(f[y][x]), 0.125))
    return fh

def plotArea2D(frame, plotTitle, plotOutPath):
    fig = plt.figure(figsize=(12, 12))
    plt.imshow(frame, origin='lower')
    plt.savefig(downDir(plotOutPath, plotTitle+".png"))
    
def linspace(a, b, n=10):
    if n < 2:
        return b
    diff = (float(b) - a)/(n - 1)
    return [diff * i + a  for i in range(n)]

def plotArea2DFrames(frames, plotTitle, nFrames, plotOutPath):
    f, axs = plt.subplots(nFrames, 1,figsize=(6, 6*nFrames))
    for i, t in enumerate(linspace(0, len(frames)-1, nFrames)):
        ti = int(t)
        plt.subplot(nFrames, 1, i+1)
        plt.title('t:'+str(ti))
        plt.imshow(frames[ti], origin='lower')    
    plt.savefig(downDir(plotOutPath, plotTitle+".png"))
    
    
def animation2D(cellCountX, cellCountY, dx, NTimeSteps, realNTimeSteps, dt, frames, slowmo, plotTitle, plotOutPath, highlight = False):
    fig = plt.figure(figsize=(12, 12))
    camera = Camera(fig)
    for frame in frames:
        if highlight:
            plt.imshow(lowValueHighlighter(frame), origin='lower')
        else:
            plt.imshow(frame, origin='lower')
        camera.snap()
    animation = camera.animate()

    time = dt * NTimeSteps
    print("Animation real time: ", time)
    realTimeStep = time / realNTimeSteps * slowmo
    print("Animation real time step: ", realTimeStep)
    fps = 1 / realTimeStep
    print("Animation fps: ", fps)

    if highlight:
        animation.save(downDir(plotOutPath, plotTitle+'_anim_hl.gif'), writer='PillowWriter', fps=fps)
    else:
        animation.save(downDir(plotOutPath, plotTitle+'_anim.gif'), writer='PillowWriter', fps=fps)