from TE1DTests import *
from TE2DTests import *

TE1DTestVisualization(TE1DCalcRes, TE1DPlotRes, "Solver1DStripMovementTest", "area_64_t_200.txt", 5, 2, False)
TE1DTestVisualization(TE1DCalcRes, TE1DPlotRes, "Solver1DStripBackMovementTest", "area_64_t_200.txt", 5, 2, False)
TE1DTestVisualization(TE1DCalcRes, TE1DPlotRes, "Solver1DJRStripMovementTest", "area_64_t_600.txt", 10, 3, False)

TE2DTestVisualization(TE2DCalcRes, TE2DPlotRes, "Solve2DRectMovementTest", "area_128x128_t_400.txt", 10, 3, False)
TE2DTestVisualization(TE2DCalcRes, TE2DPlotRes, "Solve2DWhiteBearMovementTest", "area_128x128_t_400.txt", 10, 3, False)