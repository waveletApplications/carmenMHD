OpenDatabase("localhost:./Average.vtk", 0)
AddPlot("Pseudocolor", "Density", 1, 1)
DrawPlots()
DefineScalarExpression("unnamed1", "abs(DivB)")
ChangeActivePlotsVar("unnamed1")
SetQueryFloatFormat("%g")
print(Query("Weighted Variable Sum"))
print(Query("Variable Sum"))
exit()
