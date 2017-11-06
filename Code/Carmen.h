/***************************************************************************
                          Carmen.h  -  description
                             -------------------
    begin                : Thu Jun 7 2001
    copyright            : (C) 2001 by Olivier Roussel & Alexei Tsigulin
    email                : roussel@ict.uni-karlsruhe.de, lpsoft@mail.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/** @file Carmen.h
  * @brief The .h that includes all functions headers
  */

#include "carmen.pre"


#if defined PARMPI
#include <mpi.h>
#endif

#include "PreProcessor.h"


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;


#include "Vector.h"
#include "Matrix.h"
#include "Timer.h"
#include "Parameters.h"
#include "PrintGrid.h"
#include "TimeAverageGrid.h"
#include "Cell.h"
#include "Node.h"
#include "FineMesh.h"


/** @def Max(x,y)
 *  Returns the Maximum value between x and y.
 */
#define Max(x,y) (((x) > (y)) ? (x):(y))
/** @def Max3(x,y,z)
 *  Returns the Maximum value between x, y and z.
 */
#define Max3(x,y,z) (Max((x),Max((y),(z))))
/** @def Min(x,y)
 *  Returns the mininum value between x and y.
 */
#define Min(x,y) (((x) < (y)) ? (x):(y))
/** @def Min3(x,y)
 *  Returns the minimum value between x, y and z.
 */
#define Min3(x,y,z) (Min((x),Min((y),(z))))
/** @def power2(x)
 *  Returns the square of x.
 */
#define power2(x)  ((x)*(x))
/** @def power3(x)
 *  Returns the cube of x.
 */
#define power3(x)  ((x)*(x)*(x))
/** @def Abs(x)
 *  Returns the absolute value of x.
 */
#define Abs(x) ( ((x) < 0)? -(x):(x) )

/*
______________________________________________________________________________________________

External functions
______________________________________________________________________________________________

*/

/**
 * @brief Adapts time step when required.
 * 
 * @return void
 */
void AdaptTimeStep();

/**
 * @brief Returns the position of <I>i</I> taking into account the boundary conditions
 * in the direction <I>AxisNo</I>. The number of points in this direction is <I>N</I>. <BR>
 * Example: for AxisNo=1 and for N=256, i must be between 0 and 255.
 * If i=-1, the function returns 255 for periodic boundary conditions and 0 for Neumann
 * boundary conditions.
 * 
 * @param i Position
 * @param AxisNo Axis of interest
 * @param N Defaults to (1<<ScaleNb).
 * @return int
 */
int BC(int i, int AxisNo, int N=(1<<ScaleNb));

/**
 * @brief Returns the boundary region type at the position <I>X=(x,y,z)</I>.<BR>
 * The returned value correspond to:
 * 0 = Fluid (not in the boundary)
 * 1 = Inflow
 * 2 = Outflow
 * 3 = Solid with free-slip walls
 * 4 = Solid with adiabatic walls
 * 5 = Solid with isothermal walls
 * 
 * @param X Vector
 * @return int
 */
int BoundaryRegion(const Vector& X);

/**
 * @brief Stores the tree structure and data in order to restart a multiresolution computation.
 + <i>Root</i> denotes the pointer to the first node of the tree structure.
 * 
 * @param Root Root
 * @return void
 */
void Backup(Node* Root);

/**
 * @brief Stores the data countained in a regular mesh <i>Root</i> in order to restart a
 * finite volume computation.
 * 
 * @param Root Root
 * @return void
 */
void Backup(FineMesh* Root);

/**
 * @brief Returns the time required by a finite volume computation using <i>iterations</i>
 * iterations and <i>scales</i> scales. It is use to estimate the CPU time compression.
 * 
 * @param iterations Number of iterations.
 * @param scales Scales
 * @return double
 */
double CPUTimeRef(int iterations, int scales);

/**
 * @brief Returns the computed tolerance at the scale <i>ScaleNo</i>, either using
 * Harten or Donoho thresholding (if <i>CVS</i>=true).
 * 
 * @param ScaleNo Level of interest.
 * @return double
 */
real ComputedTolerance(const int ScaleNo);

/**
 * @brief Returns the number of digits of the integer <i>arg</i>.
 * 
 * @param arg Argument
 * @return int
 */
int DigitNumber(int arg);

/**
 * @brief Writes in binary or ASCII mode the real number <i>arg</i> into the file <i>f</i>
 * with the format <i>format</i>.
 * The global parameter <i>DataIsBinary</i> determines this choice.
 * 
 * @param f File name
 * @param format Format
 * @param arg Argument
 * @return int
 */
int FileWrite(FILE *f, const char* format, real arg);

/**
 * @brief Returns the flux at the interface between <i>Cell2</i> and <i>Cell3</i>.
 * Here a 4-point space scheme is used.
 * <i>Cell2</i> and <i>Cell3</i> are the first neighbours on the left and right sides.
 * <i>Cell1</i> and <i>Cell4</i> are the second neighbours on the left and right sides.
 * 
 * @param Cell1 second neighbour on the left side
 * @param Cell2 first neighbour on the left side
 * @param Cell3 first neighbour on the right side
 * @param Cell4 second neighbour on the right side
 * @param AxisNo Axis of interest
 * @return Vector
 */
Vector Flux(Cell& Cell1, Cell& Cell2, Cell& Cell3, Cell& Cell4, int AxisNo);

/**
 * @brief Transform the 4 cells of the flux <i>Cell1</i>, <i>Cell2</i>, <i>Cell3</i>, <i>Cell4</i> into
 * <i>C1</i>, <i>C2</i>, <i>C3</i>, <i>C4</i>, to take into account boundary conditions (used in Flux.cpp).
 * 
 * @param Cell1 second neighbour on the left side
 * @param Cell2 first neighbour on the left side
 * @param Cell3 first neighbour on the right side
 * @param Cell4 second neighbour on the right side
 * @param C1 Auxiliar cell1
 * @param C2 Auxiliar cell2
 * @param C3 Auxiliar cell3
 * @param C4 Auxiliar cell4
 * @param AxisNo ...
 * @return void
 */
void GetBoundaryCells(Cell& Cell1, Cell& Cell2, Cell& Cell3, Cell& Cell4,
			Cell& C1, Cell& C2, Cell& C3, Cell& C4, int AxisNo);

/**
 * @brief Returns the initial condition in (<i>x, y, z</i>) form the one defined in <i>carmen.ini</i>.
 * 
 * @param x Position x
 * @param y Position y. Defaults to 0..
 * @param z Position z. Defaults to 0..
 * @return Vector
 */
Vector InitAverage(real x, real y=0., real z=0.);

/**
 * @brief Returns the initial resistivity condition in (<i>x, y, z</i>) form the one defined in <i>carmen.eta</i>.
 * 
 * @param x Position x
 * @param y Position y. Defaults to 0..
 * @param z Position z. Defaults to 0..
 * @return double
 */
real InitResistivity(real x, real y=0., real z=0.);

/**
 * @brief Inits parameters from file <i>carmen.par</i>. If a parameter is not mentioned
 * in this file, the default value is used.
 * 
 * @return void
 */
void InitParameters();

/**
 * @brief Inits time step and all the parameters which depend on it.
 * 
 * @return void
 */
void InitTimeStep();

/**
 * @brief Inits tree structure from initial condition, starting form the node <i>Root</i>.
 * Only for multiresolution computations.
 * 
 * @param Root Root
 * @return void
 */
void InitTree(Node* Root);

/**
 * @brief Returns the value of the slope limiter between the slopes <i>u</i> and <i>v</i>.
 * 
 * @param u Vector
 * @param v Vector
 * @return Vector
 */
Vector Limiter(const Vector u, const Vector v);

/**
 * @brief Returns the valur of slope limiter from a real value x.
 * 
 * @param x ...
 * @return double
 */
real Limiter(const real x);

/**
 * @brief Returns the minimum in module of <i>a</i> and <i>b</i>.
 * 
 * @param a Real value
 * @param b Real value
 * @return double
 */
real MinAbs(const real a, const real b);

/**
 * @brief Returns the Max-norm of the vector where every quantity is divided by its
 * characteristic value.
 * 
 * @param V Vector
 * @return double
 */
real NormMaxQuantities(const Vector& V);

/**
 * @brief Computes the performance of the computation and, for cluster computations, write it
 * into file <i>FileName</i>.
 * 
 * @param FileName Name of the file.
 * @return void
 */
void Performance(const char* FileName);

/**
 * @brief Writes the integral values, like e.g flame velocity, global error, into file <i>FileName</i>.
 * 
 * @param FileName Name of the file
 * @return void
 */
void PrintIntegral(const char* FileName);

/**
 * @brief Refresh the tree structure, i.e. compute the cell-averages of the
 * internal nodes by projection and those of the virtual leaves by prediction.
 * The root node is <i>Root</i>. Only for multiresolution computations.
 * 
 * @param Root Root
 * @return void
 */
void RefreshTree(Node* Root);

/**
 * @brief Remesh the tree structure after a time evolution. The root node is <i>Root</i>.
 * Only for multiresolution computations.
 * 
 * @param Root Root
 * @return void
 */
void Remesh(Node* Root);

/**
 * @brief Returns the physical flux of MHD equations in X direction
 * 
 * @param Avg Average vector.
 * @return Vector
 */
Vector FluxX(const Vector& Avg);

/**
 * @brief Returns the physical flux of MHD equations in Y direction
 * 
 * @param Avg Average vector.
 * @return Vector
 */
Vector FluxY(const Vector& Avg);

/**
 * @brief Returns the physical flux of MHD equations in Z direction
 * 
 * @param Avg Average vector.
 * @return Vector
 */
Vector FluxZ(const Vector& Avg);

/**
 * @brief Returns the HLL numerical flux for MHD equations.
 * The scheme uses four cells to estimate the flux at the interface.
 * <i>Cell2</i> and <i>Cell3</i> are the first neighbours on the left and right sides.
 * <i>Cell1</i> and <i>Cell4</i> are the second neighbours on the left and right sides.
 * 
 * @param Cell1 second neighbour on the left side
 * @param Cell2 first neighbour on the left side
 * @param Cell3 first neighbour on the right side
 * @param Cell4 second neighbour on the right side
 * @param AxisNo Axis of interest.
 * @return Vector
 */
Vector SchemeHLL(const Cell& Cell1, const Cell& Cell2, const Cell& Cell3, const Cell& Cell4, const int AxisNo);

/**
 * @brief Returns the HLLD numerical flux for MHD equations.
 * The scheme uses four cells to estimate the flux at the interface.
 * <i>Cell2</i> and <i>Cell3</i> are the first neighbours on the left and right sides.
 * <i>Cell1</i> and <i>Cell4</i> are the second neighbours on the left and right sides.
 * 
 * @param Cell1 second neighbour on the left side
 * @param Cell2 first neighbour on the left side
 * @param Cell3 first neighbour on the right side
 * @param Cell4 second neighbour on the right side
 * @param AxisNo Axis of interest.
 * @return Vector
 */
Vector SchemeHLLD(const Cell& Cell1, const Cell& Cell2, const Cell& Cell3, const Cell& Cell4, const int AxisNo);

/**
 * @brief Returns the intermediary states of HLLD numerical flux for MHD equations.
 * 
 * @param AvgL Left average vector
 * @param AvgR Right average vector
 * @param prel Left pressure
 * @param prer Right pressure
 * @param slopeLeft Left slope
 * @param slopeRight Right slope
 * @param slopeM Slope value computed for HLLD
 * @param slopeLeftStar Left star slope (intermediary states)
 * @param slopeRightStar Right star slope (intermediary states)
 * @param AxisNo Axis of interest
 * @return Matrix
 */
Matrix stateUstar(const Vector& AvgL, const Vector& AvgR, const real prel, const real prer, real& slopeLeft, real& slopeRight,real& slopeM, real& slopeLeftStar, real& slopeRightStar, int AxisNo);

/**
 * @brief This function apply the divergence-free correction to the numerical flux.
 * 
 * @param Flux Numerical flux vector
 * @param AvgL Left average vector
 * @param AvgR Right average vector
 * @param AxisNo Axis of interest
 * @return void
 */
void fluxCorrection(Vector& Flux,const Vector& AvgL, const Vector& AvgR, int AxisNo);

/**
 * @brief Writes on screen the estimation of total and remaining CPU times.
 * These informations are stored in the timer <i>arg</i>.
 * 
 * @param arg Argument
 * @return void
 */
void ShowTime(Timer arg);

/**
 * @brief Returns 1 if <i>a</i> is non-negative, -1 elsewhere.
 * 
 * @param a Real value
 * @return int
 */
int Sign(const real a);

/**
 * @brief Returns the artificial diffusion source terms in the cell <i>UserCell</i>.
 * 
 * @param Cell1 Left cell value
 * @param Cell2 Right cell value
 * @param AxisNo Axis of interest
 * @return Vector
 */
Vector ArtificialViscosity(const Vector& Cell1, const Vector& Cell2, real dx, int AxisNo);

/**
 * @brief Returns the resistive source terms in the cell <i>UserCell</i>.
 * 
 * @param Cell1 Cell 1
 * @param Cell2 Cell 2
 * @param Cell3 Cell 3
 * @param Cell4 Cell 4
 * @param AxisNo Axis of interest
 * @return Vector
 */
Vector ResistiveTerms(Cell& Cell1, Cell& Cell2, Cell& Cell3, Cell& Cell4, int AxisNo);

/**
 * @brief Returns the source term in the cell <i>UserCell</i>.
 * 
 * @param UserCell Cell value
 * @return Vector
 */
Vector Source(Cell& UserCell);

/**
 * @brief Returns a step (1 if x <0, 0 if x >0, 0.5 if x=0)
 * 
 * @param x Real value
 * @return double
 */
real Step(real x);

/**
 * @brief Computes a time evolution on the regular fine mesh <i>Root</i>.
 * Only for finite volume computations.
 * 
 * @param Root Fine mesh
 * @return void
 */
void TimeEvolution(FineMesh* Root);

/**
 * @brief Computes a time evolution on the tree structure, the root node being <i>Root</i>.
 * Only for multiresolution computations.
 * 
 * @param Root Root node
 * @return void
 */
void TimeEvolution(Node* Root);

/**
 * @brief Writes the current cel--averages of the fine mesh <i>Root</i> into file <i>AverageFileName</i>.
 * Only for finite volume computations.
 *
 * 
 * @param Root Fine mesh
 * @param AverageFileName File name
 * @return void
 */
void View(FineMesh* Root, const char* AverageFileName);

/**
 * @brief Writes the data of the tree structure into files <i>TreeFileName</i> (tree structure),
 * <i>MeshFileName</i> (mesh) and <i>AverageFileName</i> (cell-averages).
 * The root node is <i>Root</i>. Only for multiresolution computations.
 * 
 * @param Root Root node
 * @param TreeFileName Tree file name
 * @param MeshFileName Mesh file name
 * @param AverageFileName Average file name
 * @return void
 */
void View(Node* Root, const char* TreeFileName, const char* MeshFileName, const char* AverageFileName);

/**
 * @brief Same as previous for a fine mesh <i>Root</i>. Only for finite volume
 * computations.
 * 
 * @param Root Fine mesh
 * @param arg argument
 * @return void
 */
void ViewEvery(FineMesh* Root, int arg);

/**
 * @brief Writes into file the data of the tree structure at iteration <i>arg</i>.
 * The output file names are <i>AverageNNN.dat</i> and <i>MeshNNN.dat</i>, <i>NNN</i> being the
 * iteration in an accurate format.
 * The root node is <i>Root</i>. Only for multiresolution computations.
 * 
 * @param Root Root node
 * @param arg Argument
 * @return void
 */
void ViewEvery(Node* Root, int arg);

/**
 * @brief Same as previous for a fine mesh <i>Root</i>. Only for finite volume
 * computations.
 * 
 * @param Root Fine mesh
 * @return void
 */
void ViewIteration(FineMesh* Root);

/**
 * @brief Writes into file the data of the tree structure from physical time <i>PrintTime1</i>
 * to physical time <i>PrintTime6</i>.
 * The output file names are <i>Average_N.dat</i> and <i>Mesh_N.dat</i>, <i>N</i> being between 1 and 6.
 * The root node is <i>Root</i>. Only for multiresolution computations.
 * 
 * @param Root Root node
 * @return void
 */
void ViewIteration(Node* Root);


//Parallel
void CreateMPIType(FineMesh *Root);

/**
 * @brief Parallel function
 * DOES NOT WORK!
 * 
 * @param Root Fine mesh
 * @return void
 */
void CPUExchange(FineMesh *Root,int);

/**
 * @brief Parallel function
 * DOES NOT WORK!
 * 
 * @return void
 */
void FreeMPIType();

/**
 * @brief Parallel function
 * DOES NOT WORK!
 * 
 * @return void
 */
void CreateMPITopology();

/**
 * @brief Parallel function
 * DOES NOT WORK!
 * 
 * @return void
 */
void CreateMPILinks();

/**
 * @brief Parallel function
 * DOES NOT WORK!
 * 
 * @return void
 */
void ReduceIntegralValues();




