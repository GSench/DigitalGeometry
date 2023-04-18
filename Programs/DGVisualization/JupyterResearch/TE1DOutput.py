def readHeader1D(file):
    meshParamsLine = file.readline()
    cellCount, dx = [float(val) for val in meshParamsLine.split("\t") if val != ""][:3]
    cellCount = int(cellCount)
    
    timeParamsLine = file.readline()
    NTimeSteps, realNTimeSteps, dt  = [float(val) for val in timeParamsLine.split("\t") if val != ""][:3]
    NTimeSteps = int(NTimeSteps)
    realNTimeSteps = int(realNTimeSteps)
    
    return cellCount, dx, NTimeSteps, realNTimeSteps, dt

def read1DMinimalOutput(filename):
    file = open(filename, "r")

    cellCount, dx, NTimeSteps, realNTimeSteps, dt = readHeader1D(file)
    
    frames = []
    for i in range(realNTimeSteps+1):
        line = file.readline()
        f = [float(fi) for fi in line.split("\t") if len(fi)>1 or fi.isnumeric()]
        frames.append(f)
    
    file.close()
    return cellCount, dx, NTimeSteps, realNTimeSteps, dt, frames

def readGS1DMinimalOutput(filename):
    file = open(filename, "r")
    
    cellCount, dx, NTimeSteps, realNTimeSteps, dt = readHeader1D(file)
    
    VolumeFraction = []
    Velocity = []
    Density = []
    Pressure = []
    for i in range(realNTimeSteps+1):
        line = file.readline()
        q = [[float(qij) for qij in qi.split(",") if len(qij)>1 or qij.isnumeric()] for qi in line.split("\t") if len(qi)>1]
        VolumeFraction.append([qi[0] for qi in q])
        Velocity.append([qi[1] for qi in q])
        Density.append([qi[2] for qi in q])
        Pressure.append([qi[3] for qi in q])
    
    file.close()
    return cellCount, dx, NTimeSteps, realNTimeSteps, dt, VolumeFraction, Velocity, Density, Pressure
