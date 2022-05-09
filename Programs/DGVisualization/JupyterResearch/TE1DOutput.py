def read1DMinimalOutput(filename):
    file = open(filename, "r")

    meshParamsLine = file.readline()
    cellCount, dx = [float(val) for val in meshParamsLine.split("\t") if val != ""][:3]
    cellCount = int(cellCount)
    
    timeParamsLine = file.readline()
    NTimeSteps, realNTimeSteps, dt  = [float(val) for val in timeParamsLine.split("\t") if val != ""][:3]
    NTimeSteps = int(NTimeSteps)
    realNTimeSteps = int(realNTimeSteps)
    
    frames = []
    for i in range(realNTimeSteps+1):
        line = file.readline()
        f = [float(fi) for fi in line.split("\t") if len(fi)>1 or fi.isnumeric()]
        frames.append(f)
    
    file.close()
    return cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames

