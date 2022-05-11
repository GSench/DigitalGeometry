def read2DOutput(filename):
    file = open(filename, "r")

    meshParamsLine = file.readline()
    cellCountX, cellCountY, dx = [float(val) for val in meshParamsLine.split("\t") if val != ""][:4]
    cellCountX = int(cellCountX)
    cellCountY = int(cellCountY)
    
    timeParamsLine = file.readline()
    NTimeSteps, realNTimeSteps, dt  = [float(val) for val in timeParamsLine.split("\t") if val != ""][:3]
    NTimeSteps = int(NTimeSteps)
    realNTimeSteps = int(realNTimeSteps)
    
    frames = []
    for i in range(realNTimeSteps+1):
        f = []
        for y in range(cellCountY):
            lineX = file.readline()
            fx = [float(fi) for fi in lineX.split("\t") if len(fi)>1 or fi.isnumeric()]
            f.append(fx)
        frames.append(f.copy())
    
    file.close()
    return cellCountX, cellCountY, dx, NTimeSteps, realNTimeSteps, dt, frames