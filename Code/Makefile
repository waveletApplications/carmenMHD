# Makefile

# Compiler
CPP=g++

# Optimization flags
OFLAG=-O2

# Debug flags
DFLAG=-g3

# Static flag
SFLAG=-static

# Warning flags
WFLAG=-Wall -Wno-deprecated

# Optimization
FLAGS=$(OFLAG) $(SFLAG) $(WFLAG)

# Debugging
#FLAGS=$(DFLAG) $(SFLAG) $(WFLAG)


OBJECTS=\
AdaptTimeStep.o \
ArtificialViscosity.o\
Backup.o \
BC.o \
BoundaryRegion.o \
Cell.o \
ComputedTolerance.o \
CPUTimeRef.o \
DigitNumber.o \
FileWrite.o \
FineMesh.o \
Flux.o \
FluxCorrection.o\
GetBoundaryCells.o \
InitAverage.o \
InitTimeStep.o \
InitTree.o \
IntermediaryStates.o\
Limiter.o \
Matrix.o \
MinAbs.o \
Node.o \
NormMaxQuantities.o \
Parallel.o \
Parameters.o \
Performance.o \
PhysicalFluxMHD.o\
PrintGrid.o \
PrintIntegral.o \
RefreshTree.o \
Remesh.o \
ResistiveTerms.o\
SchemeHLL.o\
SchemeHLLD.o\
ShowTime.o \
Sign.o \
Source.o \
Step.o \
TimeAverageGrid.o \
TimeEvolution.o \
Timer.o \
Vector.o \
View.o \
ViewEvery.o \
ViewIteration.o \
main.o

HEADERS=\
Carmen.h \
FineMesh.h \
Node.h \
PreProcessor.h \
TimeAverageGrid.h \
Vector.h \
Cell.h \
Matrix.h \
Parameters.h \
PrintGrid.h \
Timer.h

# Compile source files
.cpp.o:
	$(CPP) -c $(FLAGS) $<

# Link objects
carmen: $(OBJECTS) $(HEADERS)
	$(CPP) -o carmen $(FLAGS) $(OBJECTS)

clean:
	rm -f *.o
	rm -f *~
dats:
	rm -f *.dat
	rm -f *.bak
	rm -f *.png
	rm -f *.eps
	rm -f *.vtk
