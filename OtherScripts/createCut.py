OpenDatabase("localhost:Average.vtk", 0)
AddPlot("Pseudocolor", "Density", 1, 1)
AddOperator("Slice", 1)
SetActivePlots(0)
SetActivePlots(0)
SliceAtts = SliceAttributes()
SliceAtts.originType = SliceAtts.Intercept  # Point, Intercept, Percent, Zone, Node
SliceAtts.originIntercept = 0.5
SliceAtts.axisType = SliceAtts.YAxis  # XAxis, YAxis, ZAxis, Arbitrary, ThetaPhi
SliceAtts.project2d = 0
SetOperatorOptions(SliceAtts, 1)
DrawPlots()
ExportDBAtts = ExportDBAttributes()
ExportDBAtts.allTimes = 0
ExportDBAtts.db_type = "Xmdv"
ExportDBAtts.db_type_fullname = "Xmdv_1.0"
ExportDBAtts.filename = "SC_2D_L7_eps001_res"
ExportDBAtts.dirname = "."
ExportDBAtts.variables = ("Density", "Pressure", "Vx", "Vy", "Vz", "Bx", "By", "Bz")
ExportDBAtts.opts.types = (0)
ExportDatabase(ExportDBAtts)
exit()
