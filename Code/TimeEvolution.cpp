/***************************************************************************
                          TimeEvolution.cpp  -  description
                             -------------------
    begin                : Thu Jun 7 2001
    copyright            : (C) 2001 by Olivier Roussel & Alexei Tsigulin
    email                : roussel@ict.uni-karlsruhe.de, lpsoft@mail.ru
 ***************************************************************************/
/** @file TimeEvolution.cpp
  * @brief Time evolution for finite volume with multiresolution
  */
#include "Carmen.h"
/*
______________________________________________________________________________________________

Time evolution for finite volume with multiresolution
______________________________________________________________________________________________

*/
void TimeEvolution(Node* Root)
{

		// --- Smooth data ---

		if ( SmoothCoeff != 0.)
			Root->smooth();

		// --- Store cell-average values of leaves ---
		Root->store();

		// --- Refresh tree structure ---
		RefreshTree(Root);

		for (StepNo = 1; StepNo <= StepNb; StepNo++)
		{
			// --- Compute divergence ---
			Root->computeDivergence();
			// --- Runge-Kutta step ---
			Root->RungeKutta();
			// --- Divergence cleaning source-terms
            Root->computeCorrection();

        }

        // --- Refresh tree structure ---
        RefreshTree(Root);



		// --- Check stability ---
		Root->checkStability();

		// --- Compute integral values ---
		Root->computeIntegral();

		// --- Compute total number of cells and leaves ---

		TotalCellNb += CellNb;
		TotalLeafNb += LeafNb;
 //cout<<"eigen= "<<Eigenvalue<<endl;
		// --- Compute elapsed time and adapt time step ---
        Eigenvalue = Max(EigenvalueX,Max(EigenvalueY,EigenvalueZ));
		ElapsedTime += TimeStep;
		if (!ConstantTimeStep) AdaptTimeStep();

        // --- Compute divergence-free correction constant
        //ch = CFL*SpaceStep/TimeStep;
        ch = Max(CFL*SpaceStep/TimeStep, Eigenvalue);

}
/*
______________________________________________________________________________________________

Time evolution for finite volume on fine grid (no multiresolution)
______________________________________________________________________________________________

*/
void TimeEvolution(FineMesh* Root)
{

		// --- Store cell-average values into temporary ---
		Root->store();

		for (StepNo = 1; StepNo <= StepNb; StepNo++)
		{
			// --- Compute divergence for neighbour cells ---
			//The same conception with background computations, see upper...
			Root->computeDivergence(1);
			// --- Runge-Kutta step for neighbour cells ---
			Root->RungeKutta(1);
			// --- Divergence cleaning source term
			Root->computeCorrection(1);
			// --- Start inter-CPU exchanges ---
			CPUExchange(Root, SendQ);
			// --- Compute divergence for internal cells ---
			Root->computeDivergence(0);
			// --- Runge-Kutta step for internal cells ---
			Root->RungeKutta(0);
			// --- Divergence cleaning source term
			Root->computeCorrection(0);

#if defined PARMPI
			CommTimer.start();    //Communication Timer Start
			//Waiting while inter-CPU exchanges are finished
			if (MPIRecvType == 1)                     //for nonblocking recive...
				MPI_Waitall(4*Dimension,req,st);
			CommTimer.stop();
#endif

  		}

		// --- Check stability ---
		Root->checkStability();

		// --- Compute integral values ---
		Root->computeIntegral();

		// --- Compute elapsed time and adapt time step ---

		if (!ComputeCPUTimeRef)
		{
            Eigenvalue = Max(EigenvalueX,Max(EigenvalueY,EigenvalueZ));
			ElapsedTime += TimeStep;
			if (!ConstantTimeStep) AdaptTimeStep();
			// --- Compute divergence-free correction constant
            //ch = CFL*SpaceStep/TimeStep;
            ch = Max(CFL*SpaceStep/TimeStep, Eigenvalue);
		}

		// --- Compute time-average values ---

		if (TimeAveraging)
			Root->computeTimeAverage();

}
