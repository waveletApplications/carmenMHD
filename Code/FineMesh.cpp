/***************************************************************************
                          FineMesh.cpp  -  description
                             -------------------
    begin                : Wed Jun 13 2001
    last correction      : Thu Jan 10 2012 by Margarete Domingues
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
/** @file FineMesh.cpp
  * @brief Fine mesh simulation functions
  * @version 2.0
  * @date November-2016
  */
#include "Carmen.h"

/*
______________________________________________________________________________________________

Constructor
______________________________________________________________________________________________

*/

FineMesh::FineMesh()
{
	// --- Local variables ---

	int n=0, i=0, j=0, k=0; 		// position numbers

	real  x=0.,  y=0.,  z=0.;	// positions
	real dx=0., dy=0., dz=0.; 	// space steps

	// --- Create an array of 2^(ScaleNb*Dimension) cells ---

	MeshCell = new Cell[(1<<(ScaleNb*Dimension))];

//Parallel

#if defined PARMPI
	Neighbour_iL = new Cell**[NeighbourNb];
  Neighbour_iU = new Cell**[NeighbourNb];
	Neighbour_jL = new Cell**[NeighbourNb];
	Neighbour_jU = new Cell**[NeighbourNb];
	Neighbour_kL = new Cell**[NeighbourNb];
	Neighbour_kU = new Cell**[NeighbourNb];

	for (i=0;i<NeighbourNb;i++) {
		Neighbour_iL[i] = new Cell*[one_D];
		Neighbour_iU[i] = new Cell*[one_D];
		Neighbour_jL[i] = new Cell*[one_D];
		Neighbour_jU[i] = new Cell*[one_D];
		Neighbour_kL[i] = new Cell*[one_D];
		Neighbour_kU[i] = new Cell*[one_D];
	}

	for (i=0;i<NeighbourNb;i++)
		for (j=0;j<one_D;j++) {
      Neighbour_iL[i][j] = new Cell[two_D];
      Neighbour_iU[i][j] = new Cell[two_D];
      Neighbour_jL[i][j] = new Cell[two_D];
      Neighbour_jU[i][j] = new Cell[two_D];
      Neighbour_kL[i][j] = new Cell[two_D];
      Neighbour_kU[i][j] = new Cell[two_D];
	}
#endif



	// --- Create a time-average grid ---

	if (TimeAveraging)
		MyTimeAverageGrid = new TimeAverageGrid(ScaleNb);

	// --- Compute dx, dy, dz ---

	dx = (XMax[1]-XMin[1])/(1<<ScaleNb);
	if (Dimension > 1) dy = (XMax[2]-XMin[2])/(1<<ScaleNb);
	if (Dimension > 2) dz = (XMax[3]-XMin[3])/(1<<ScaleNb);

	// --- Loop on all cells ---

	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
	{
		// -- Compute i, j, k --

		i = n%(1<<ScaleNb);
		if (Dimension > 1) j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
		if (Dimension > 2) k = n/(1<<(2*ScaleNb));
		// -- Compute x, y, z --

		x = XMin[1] + (i+.5)*dx;
		if (Dimension > 1) y = XMin[2] + (j+.5)*dy;
		if (Dimension > 2) z = XMin[3] + (k+.5)*dz;

		// -- Set position --

		cell(n)->setCenter(1,x);
		if (Dimension > 1) cell(n)->setCenter(2,y);
		if (Dimension > 2) cell(n)->setCenter(3,z);

		// -- Set size --

		cell(n)->setSize(1,dx);
		if (Dimension > 1) cell(n)->setSize(2,dy);
		if (Dimension > 2) cell(n)->setSize(3,dz);
	}
	// --- End loop on all cells ---

//Parallel

#if defined PARMPI

	for (i=0;i<one_D;i++)
		for (j=0;j<two_D;j++)
			for (k=0;k<NeighbourNb;k++) {
				Neighbour_iL[k][i][j].setSize(1,dx);
				Neighbour_iU[k][i][j].setSize(1,dx);
				Neighbour_jL[k][i][j].setSize(1,dx);
				Neighbour_jU[k][i][j].setSize(1,dx);
				Neighbour_kL[k][i][j].setSize(1,dx);
				Neighbour_kU[k][i][j].setSize(1,dx);

				if (Dimension > 1) {
					Neighbour_iL[k][i][j].setSize(2,dy);
					Neighbour_iU[k][i][j].setSize(2,dy);
					Neighbour_jL[k][i][j].setSize(2,dy);
					Neighbour_jU[k][i][j].setSize(2,dy);
					Neighbour_kL[k][i][j].setSize(2,dy);
					Neighbour_kU[k][i][j].setSize(2,dy);
				}

				if (Dimension > 2) {
					Neighbour_iL[k][i][j].setSize(3,dz);
					Neighbour_iU[k][i][j].setSize(3,dz);
					Neighbour_jL[k][i][j].setSize(3,dz);
					Neighbour_jU[k][i][j].setSize(3,dz);
					Neighbour_kL[k][i][j].setSize(3,dz);
					Neighbour_kU[k][i][j].setSize(3,dz);
				}
		}

#endif



	// -- Set initial cell-average value --


   //!!!DEBUG
   /*
    printf("\nRecovery: %d",Recovery);
    printf("\nUseBackup: %d",UseBackup);
    printf("\nComputeCPUTimeRef: %d\n",ComputeCPUTimeRef);
*/

	if (Recovery && UseBackup && !ComputeCPUTimeRef)   {
//    printf("\nRestore!\n");
		restore();
  }
  else
	{
		for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
		{
			cell(n)->setAverageZero();

			if (UseBoundaryRegions && BoundaryRegion(cell(n)->center()) != 0)
			{
				x = cell(n)->center(1);
				y = (Dimension > 1)? cell(n)->center(2): 0.;
				z = (Dimension > 2)? cell(n)->center(3): 0.;
				cell(n)->setAverage(InitAverage(x,y,z));
			}
			else
			{

				switch (Dimension)
				{
					case 1:
						for (i=0;i<=1;i++)
							cell(n)->setAverage( cell(n)->average()+.5* InitAverage(
							cell(n)->center(1)+(i-0.5)*cell(n)->size(1)) );
					break;

					case 2:
                        if(IcNb){
                            for (i=0;i<=1;i++)
                                for (j=0;j<=1;j++){
                                    cell(n)->setAverage( cell(n)->average()+.25* InitAverage(
                                    cell(n)->center(1)+(i-0.5)*cell(n)->size(1),
                                    cell(n)->center(2)+(j-0.5)*cell(n)->size(2) ) );
                                    cell(n)->setRes(InitResistivity(cell(n)->center(1),cell(n)->center(2)));
                                }
                        }else{
                            cell(n)->setAverage(InitAverage(cell(n)->center(1),cell(n)->center(2)));
                            cell(n)->setRes(InitResistivity(cell(n)->center(1),cell(n)->center(2)));
                        }
					break;

					case 3:
                        if(IcNb){
                            for (i=0;i<=1;i++)
                                for (j=0;j<=1;j++)
                                    for (k=0;k<=1;k++){
                                        cell(n)->setAverage( cell(n)->average()+.125* InitAverage(
                                        cell(n)->center(1)+(i-0.5)*cell(n)->size(1),
                                        cell(n)->center(2)+(j-0.5)*cell(n)->size(2),
                                        cell(n)->center(3)+(k-0.5)*cell(n)->size(3) ) );
                                        cell(n)->setRes(InitResistivity(cell(n)->center(1),cell(n)->center(2),cell(n)->center(3)));
                                    }
                        }else{
                            cell(n)->setAverage(InitAverage(cell(n)->center(1),cell(n)->center(2),cell(n)->center(3)));
                            cell(n)->setRes(InitResistivity(cell(n)->center(1),cell(n)->center(2),cell(n)->center(3)));
                        }

						break;
				};
			}
		}
	}

 #if defined PARMPI
      //Important moment: Exchange boundary (neighbour) cells before start computation (1st iteration)

      CPUExchange(this, SendQ);
      if (MPIRecvType == 1)	MPI_Waitall(4*Dimension,req,st);   //Send quantity number one (code name "Q")

			if (EquationType==6) {
        CPUExchange(this, SendGrad);
      if (MPIRecvType == 1)	MPI_Waitall(4*Dimension,req,st);   //Send gradient
      }
 #endif

}
/*
______________________________________________________________________________________________

Distructor
______________________________________________________________________________________________

*/
FineMesh::~FineMesh()
{
	// --- Delete pointers to cells ---

	delete[] MeshCell;

  #if defined PARMPI
	int i,j;

	for (i=0;i<NeighbourNb;i++)
		for (j=0;j<one_D;j++) {
			delete[] Neighbour_iL[i][j];
			delete[] Neighbour_iU[i][j];
			delete[] Neighbour_jL[i][j];
			delete[] Neighbour_jU[i][j];
			delete[] Neighbour_kL[i][j];
			delete[] Neighbour_kU[i][j];
		}

	for (i=0;i<NeighbourNb;i++) {
			delete[] Neighbour_iL[i];
			delete[] Neighbour_iU[i];
			delete[] Neighbour_jL[i];
			delete[] Neighbour_jU[i];
			delete[] Neighbour_kL[i];
			delete[] Neighbour_kU[i];
	}

	delete[] Neighbour_iL;
	delete[] Neighbour_iU;
	delete[] Neighbour_jL;
	delete[] Neighbour_jU;
	delete[] Neighbour_kL;
	delete[] Neighbour_kU;
 #endif


	if (TimeAveraging)
		delete MyTimeAverageGrid;
}
/*
______________________________________________________________________________________________

	Get procedures
______________________________________________________________________________________________

*/
Cell* FineMesh::cell(const int i, const int j, const int k) const
{
	int n = (1<<ScaleNb);


#if defined PARMPI
	int BCi,BCj,BCk;
	Cell *C;
	BCi=BC(i,1,n);
	BCj=BC(j,2,n);
	BCk=BC(k,3,n);

  if (BCi>=n && BCj>=n)  printf("\nDiagonal neighbours not implemented!");
  if (BCi<0 && BCj<0)  printf("\nDiagonal neighbours not implemented!");
  if (BCi<0 && BCj>=n)  printf("\nDiagonal neighbours not implemented!");
  if (BCi>=n && BCj<0)  printf("\nDiagonal neighbours not implemented!");

	if (BCi<0) C=&Neighbour_iL[NeighbourNb+BCi][j][k]; else
	if (BCi>=n) C=&Neighbour_iU[BCi-n][j][k]; else

	if (BCj<0) C=&Neighbour_jL[NeighbourNb+BCj][i][k]; else
	if (BCj>=n) C=&Neighbour_jU[BCj-n][i][k]; else

	if (BCk<0) C=&Neighbour_kL[NeighbourNb+BCk][i][j]; else
	if (BCk>=n) C=&Neighbour_kU[BCk-n][i][j]; else

	C=MeshCell + BCi + n*(BCj + n*BCk);

	return C;
#else
	return ( MeshCell + BC(i,1,n) + n*(BC(j,2,n) + n*BC(k,3,n)) );
#endif

}



void FineMesh::computeDivergence_cell(int n)
{
	// --- Local variables ---

	int i=0, j=0, k=0; 		// position numbers
	Vector FluxIn, FluxOut;			// ingoing and outgoing fluxes
	real divCor=0.;

	// --- Loop on all cells ---

		// --- Only in fluid region ---

	  if (!UseBoundaryRegions || BoundaryRegion(cell(n)->center())==0)
	  {
		// --- Compute source term --

		cell(n)->setDivergence(Source(*cell(n)));

		// -- Compute i, j, k --

		i = n%(1<<ScaleNb);
		if (Dimension > 1) j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
		if (Dimension > 2) k = n/(1<<(2*ScaleNb));

		// Add flux in x-direction

		FluxIn  = Flux( *cell(i-2, j, k), *cell(i-1, j, k), *cell(i,   j, k), *cell(i+1, j, k), 1 );
		divCor  = -auxvar;
		FluxOut = Flux( *cell(i-1, j, k), *cell(i  , j, k), *cell(i+1, j, k), *cell(i+2, j, k), 1 );
        divCor +=  auxvar;

		//! 2D resistive part of the model added to the Flux

        if(Resistivity){
            FluxIn  = FluxIn  - ResistiveTerms(*cell(i,j,k)  , *cell(i-1,j,k), *cell(i,j-1,k)  , *cell(i,j,k-1)  , 1);
            FluxOut = FluxOut - ResistiveTerms(*cell(i+1,j,k), *cell(i,j,k)  , *cell(i+1,j-1,k), *cell(i+1,j,k-1), 1);
        }

        cell(n)->setDivergence( cell(n)->divergence() + (FluxIn - FluxOut)/(cell(n)->size(1)));

        // Variables \grad(psi) and \div(B) to evaluate GLM and EGLM divergence cleaning
        PsiGrad      = cell(n)->average(7)*(FluxOut.value(7) - FluxIn.value(7) - divCor)/(cell(n)->size(1));
        Bdivergence += (FluxOut.value(6) - FluxIn.value(6))/(cell(n)->size(1));

		// Add flux in y-direction

		if (Dimension > 1)
		{
			FluxIn  = Flux( *cell(i, j-2, k), *cell(i, j-1, k), *cell(i, j  , k), *cell(i, j+1, k), 2 );
			divCor  = -auxvar;
			FluxOut = Flux( *cell(i, j-1, k), *cell(i, j  , k), *cell(i, j+1, k), *cell(i, j+2, k), 2 );
			divCor +=  auxvar;

			if(Resistivity){
                FluxIn  = FluxIn  - ResistiveTerms(*cell(i,j,k)  , *cell(i-1,j,k)  , *cell(i,j-1,k), *cell(i,j,k-1)  , 2);
                FluxOut = FluxOut - ResistiveTerms(*cell(i,j+1,k), *cell(i-1,j+1,k), *cell(i,j,k)  , *cell(i,j+1,k-1), 2);
            }

			cell(n)->setDivergence( cell(n)->divergence() + (FluxIn - FluxOut)/(cell(n)->size(2)) );

			// Variables \grad(psi) and \div(B) to evaluate GLM and EGLM divergence cleaning
			PsiGrad     += cell(n)->average(8)*(FluxOut.value(8) - FluxIn.value(8) - divCor)/(cell(n)->size(2));
            Bdivergence += (FluxOut.value(6) - FluxIn.value(6))/(cell(n)->size(2));
		}

		// Add flux in z-direction

		if (Dimension > 2)
		{
			FluxIn  = Flux( *cell(i, j, k-2), *cell(i, j, k-1), *cell(i, j, k  ), *cell(i, j, k+1), 3 );
			divCor  = -auxvar;
			FluxOut = Flux( *cell(i, j, k-1), *cell(i, j, k  ), *cell(i, j, k+1), *cell(i, j, k+2), 3 );
            divCor += auxvar;

			if(Resistivity){
                FluxIn  = FluxIn  - ResistiveTerms(*cell(i,j,k)  , *cell(i-1,j,k)  , *cell(i,j-1,k)  , *cell(i,j,k-1), 3);
                FluxOut = FluxOut - ResistiveTerms(*cell(i,j,k+1), *cell(i-1,j,k+1), *cell(i,j-1,k+1), *cell(i,j,k)  , 3);
            }

			cell(n)->setDivergence( cell(n)->divergence() + (FluxIn - FluxOut)/(cell(n)->size(3)) );

			// Variables \grad(psi) and \div(B) to evaluate GLM and EGLM divergence cleaning
			PsiGrad     += cell(n)->average(9)*(FluxOut.value(9) - FluxIn.value(9) - divCor)/(cell(n)->size(3));
            Bdivergence += (FluxOut.value(6) - FluxIn.value(6))/(cell(n)->size(3));
		}
	 }

	// --- End loop on all cells ---
}



void FineMesh::computeDivergence(int mode)
{
	int i,j,k,d;


	// --- Loops for internal cells
	if (mode==0)
	{
  if (Dimension==1)
		for (i=2*NeighbourNb;i<(1<<ScaleNb)-2*NeighbourNb;i++)
		{
			j=0; k=0;
			d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
			computeDivergence_cell(d);
		}

  if (Dimension==2)
		for (i=2*NeighbourNb;i<(1<<ScaleNb)-2*NeighbourNb;i++)
			for (j=2*NeighbourNb;j<(1<<ScaleNb)-2*NeighbourNb;j++)
			{
				k=0;
				d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
				computeDivergence_cell(d);
			}


  if (Dimension==3)
		for (i=2*NeighbourNb;i<(1<<ScaleNb)-2*NeighbourNb;i++)
			for (j=2*NeighbourNb;j<(1<<ScaleNb)-2*NeighbourNb;j++)
				for (k=2*NeighbourNb;k<(1<<ScaleNb)-2*NeighbourNb;k++) {
					d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
					computeDivergence_cell(d);
				}
 }

//  --- loop for neighbour cells
	if (mode==1) {

  if (Dimension==1)
	for (i=0;i<(1<<ScaleNb);i++)
   	if (i<2*NeighbourNb || i>=(1<<ScaleNb)-2*NeighbourNb)  {
						j=0; k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
  					computeDivergence_cell(d);
		}

  if (Dimension==2)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
     	if (i<2*NeighbourNb || j<2*NeighbourNb  ||
					i>=(1<<ScaleNb)-2*NeighbourNb || j>=(1<<ScaleNb)-2*NeighbourNb)  {
						k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
						computeDivergence_cell(d);
			}

  if (Dimension==3)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
	  	for (k=0;k<two_D;k++)
   	  	if (i<2*NeighbourNb || j<2*NeighbourNb  ||   k<2*NeighbourNb ||
						i>=(1<<ScaleNb)-2*NeighbourNb || j>=(1<<ScaleNb)-2*NeighbourNb  || k>=(1<<ScaleNb)-2*NeighbourNb)  {
							d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
							computeDivergence_cell(d);
				}

}

/*
	int n;
	for (n = 0; n < 1<<(ScaleNb*Dimension); n++) computeDivergence_cell(n);*/
}

/*
______________________________________________________________________________________________

	Compute divergence cleaning source term (MHD only)
______________________________________________________________________________________________

*/

void FineMesh::computeCorrection_cell(int n)
{
	// --- Local variables ---
	real rho=0., psi=0.;        // Variables density and psi
	int  q=0;	                // Counters
    real Bx=0.;                 // Magnetic field

	// --- Computation ---


		if(DivClean==1) // EGLM
        {

        	rho = cell(n)->density();
        	psi = cell(n)->psi();

		    for (q=1; q <= 3; q++) //GLM
		    {
		        Bx = cell(n)->magField(q);
		        cell(n)->setAverage(q+1, cell(n)->average(q+1) - TimeStep*Bx*Bdivergence/(ch*ch));
		    }

        	cell(n)->setAverage(5, cell(n)->average(5) - TimeStep*PsiGrad);
        	cell(n)->setAverage(6,psi*exp(-(cr*ch*TimeStep/SpaceStep)));

        }else if(DivClean==2)
        {
        	psi = cell(n)->psi();
        	cell(n)->setAverage(6,psi*exp(-(cr*ch*TimeStep/SpaceStep)));
        }


}
void FineMesh::computeCorrection(int mode)
{
 	int i,j,k,d;
    	// --- Loops for internal cells
	if (mode==0) {
  if (Dimension==1)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++) {
			j=0; k=0;
			d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
			computeCorrection_cell(d);
		}

  if (Dimension==2)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++)
			for (j=NeighbourNb;j<(1<<ScaleNb)-NeighbourNb;j++) {
				k=0;
				d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
				computeCorrection_cell(d);
			}


  if (Dimension==3)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++)
			for (j=NeighbourNb;j<(1<<ScaleNb)-NeighbourNb;j++)
				for (k=NeighbourNb;k<(1<<ScaleNb)-NeighbourNb;k++) {
					d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
					computeCorrection_cell(d);
				}
 }

//  --- loop for neighbour cells
	if (mode==1) {

  if (Dimension==1)
	for (i=0;i<(1<<ScaleNb);i++)
   	if (i<NeighbourNb || i>=(1<<ScaleNb)-NeighbourNb)  {
						j=0; k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
  					computeCorrection_cell(d);
		}

  if (Dimension==2)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
     	if (i<NeighbourNb || j<NeighbourNb  ||
					i>=(1<<ScaleNb)-NeighbourNb || j>=(1<<ScaleNb)-NeighbourNb)  {
						k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
						computeCorrection_cell(d);
			}

  if (Dimension==3)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
	  	for (k=0;k<two_D;k++)
   	  	if (i<NeighbourNb || j<NeighbourNb  ||   k<NeighbourNb ||
						i>=(1<<ScaleNb)-NeighbourNb || j>=(1<<ScaleNb)-NeighbourNb  || k>=(1<<ScaleNb)-NeighbourNb)  {
							d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
							computeCorrection_cell(d);
				}
	}
/*
	int n;
	for (n = 0; n < 1<<(ScaleNb*Dimension); n++) computeDivergence_cell(n);*/
}

/*
______________________________________________________________________________________________

	Compute quantity gradient (Navier-Stokes only)
______________________________________________________________________________________________

*/

void FineMesh::computeGradient_cell(int n)
{
	// --- Local variables ---
	int i=0, j=0, k=0;		// Counter on children
	real V1=0., V2=0.;  		// Velocities
	real dx=0.;			// Distance between the centers of the neighbour cells
	real dxV=0.;			// Correction of dx for the computation of GradV close to solid walls											// Cell size
	real rho1=0., rho2=0.;          // Densities
	real rhoE1=0., rhoE2=0.;	// Energies
	int p=0, q=0;			// Counters on dimension (between 0 and Dimension)
	int ei=0, ej=0, ek=0;		// 1 if this direction is chosen, 0 elsewhere

	real result;
	result = 0.;

	// --- Recursion ---

	if (EquationType != 6)
	{
		cout << "FineMesh.cpp: In method `void FineMesh::computeGradient()':\n";
		cout << "FineMesh.cpp: EquationType not equal to 6 \n";
		cout << "carmen: *** [FineMesh.o] Execution error\n";
		cout << "carmen: abort execution.\n";
		exit(1);
	}

	// --- Loop on all cells ---

	   // Only in the fluid
	   if (BoundaryRegion(cell(n)->center()) == 0)
	   {
		  i = n%(1<<ScaleNb);
  		if (Dimension > 1) j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
  		if (Dimension > 2) k = n/(1<<(2*ScaleNb));

  		for (p=1; p <= Dimension; p++)
  		{
  			ei = (p==1)? 1:0;
  			ej = (p==2)? 1:0;
  			ek = (p==3)? 1:0;

	  		dx = cell(i,j,k)->size(p);
		  	dx *= 2.;

			// dxV = correction on dx for the computation of GradV close to solid walls

  			if (BoundaryRegion(cell(i+ei,j+ej,k+ek)->center()) > 3 ||
  			    BoundaryRegion(cell(i-ei,j-ej,k-ek)->center()) > 3 )
  			    	dxV = 0.75*dx;
	  		else
  				dxV = dx;

  			rho1 = cell(i+ei,j+ej,k+ek)->density();
  			rho2 = cell(i-ei,j-ej,k-ek)->density();

	  		cell(n)->setGradient(p, 1, (rho1-rho2)/dx);

		  	for (q=1; q <= Dimension; q++)
  			{
  				V1=cell(i+ei,j+ej,k+ek)->velocity(q);
  				V2=cell(i-ei,j-ej,k-ek)->velocity(q);
  				result = (V1-V2)/dx;
  				cell(n)->setGradient(p, q+1, (V1-V2)/dxV);
	  		}

  			rhoE1 = cell(i+ei,j+ej,k+ek)->energy();
  			rhoE2 = cell(i-ei,j-ej,k-ek)->energy();

  			cell(n)->setGradient(p, Dimension+2, (rhoE1-rhoE2)/dx);
  		}
	 }

}


void FineMesh::computeGradient(int mode)
{
 	int i,j,k,d;
    	// --- Loops for internal cells
	if (mode==0) {
  if (Dimension==1)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++) {
			j=0; k=0;
			d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
			computeGradient_cell(d);
		}

  if (Dimension==2)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++)
			for (j=NeighbourNb;j<(1<<ScaleNb)-NeighbourNb;j++) {
				k=0;
				d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
				computeGradient_cell(d);
			}


  if (Dimension==3)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++)
			for (j=NeighbourNb;j<(1<<ScaleNb)-NeighbourNb;j++)
				for (k=NeighbourNb;k<(1<<ScaleNb)-NeighbourNb;k++) {
					d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
					computeGradient_cell(d);
				}
 }

//  --- loop for neighbour cells
	if (mode==1) {

  if (Dimension==1)
	for (i=0;i<(1<<ScaleNb);i++)
   	if (i<NeighbourNb || i>=(1<<ScaleNb)-NeighbourNb)  {
						j=0; k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
  					computeGradient_cell(d);
		}

  if (Dimension==2)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
     	if (i<NeighbourNb || j<NeighbourNb  ||
					i>=(1<<ScaleNb)-NeighbourNb || j>=(1<<ScaleNb)-NeighbourNb)  {
						k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
						computeGradient_cell(d);
			}

  if (Dimension==3)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
	  	for (k=0;k<two_D;k++)
   	  	if (i<NeighbourNb || j<NeighbourNb  ||   k<NeighbourNb ||
						i>=(1<<ScaleNb)-NeighbourNb || j>=(1<<ScaleNb)-NeighbourNb  || k>=(1<<ScaleNb)-NeighbourNb)  {
							d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
							computeGradient_cell(d);
				}
	}
/*
	int n;
	for (n = 0; n < 1<<(ScaleNb*Dimension); n++) computeDivergence_cell(n);*/
}

/*
______________________________________________________________________________________________

	Runge-Kutta step
______________________________________________________________________________________________

*/

void FineMesh::RungeKutta_cell(int n)
{
	// --- Local variables ---
	real c1=0., c2=0., c3=0.;		// Runge-Kutta coefficients

	Vector Q(QuantityNb), Qs(QuantityNb), D(QuantityNb);		// Cell-average, temporary cell-average and divergence

	// --- Loop on all cells ---

		if (!UseBoundaryRegions || BoundaryRegion(cell(n)->center()) == 0)
		{
			switch(StepNo)
			{
				case 1:
					c1 = 1.; c2 = 0.; c3 = 1.;
					break;
				case 2:
					if (StepNb == 2) {c1 = .5;  c2 = .5;  c3 = .5;  }
					if (StepNb == 3) {c1 = .75; c2 = .25; c3 = .25; }
					break;
				case 3:
					if (StepNb == 3) {c1 = 1./3.; c2 = 2.*c1; c3 = c2;}
					break;
			};

			// --- Runge-Kutta step ---

            Q  = cell(n)->average();
			Qs = cell(n)->tempAverage();
			D  = cell(n)->divergence();

			cell(n)->setAverage( c1*Qs + c2*Q + (c3 * TimeStep)*D );
		}

}

/*
______________________________________________________________________________________________

	Runge-Kutta step (parallel version)
______________________________________________________________________________________________

*/

void FineMesh::RungeKutta(int mode) {
	int i,j,k,d;

	// --- Loops for internal cells

	if (mode==0) {
  if (Dimension==1)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++) {
			j=0; k=0;
			d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
			RungeKutta_cell(d);
		}

  if (Dimension==2)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++)
			for (j=NeighbourNb;j<(1<<ScaleNb)-NeighbourNb;j++) {
				k=0;
				d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
				RungeKutta_cell(d);
			}


  if (Dimension==3)
		for (i=NeighbourNb;i<(1<<ScaleNb)-NeighbourNb;i++)
			for (j=NeighbourNb;j<(1<<ScaleNb)-NeighbourNb;j++)
				for (k=NeighbourNb;k<(1<<ScaleNb)-NeighbourNb;k++) {
					d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
					RungeKutta_cell(d);
				}
 }

//  --- loop for neighbour cells
	if (mode==1) {

  if (Dimension==1)
	for (i=0;i<(1<<ScaleNb);i++)
   	if (i<NeighbourNb || i>=(1<<ScaleNb)-NeighbourNb)  {
						j=0; k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
						RungeKutta_cell(d);
		}

  if (Dimension==2)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
     	if (i<NeighbourNb || j<NeighbourNb  ||
					i>=(1<<ScaleNb)-NeighbourNb || j>=(1<<ScaleNb)-NeighbourNb)  {
						k=0;
						d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
						RungeKutta_cell(d);
			}

  if (Dimension==3)
	for (i=0;i<(1<<ScaleNb);i++)
  	for (j=0;j<one_D;j++)
	  	for (k=0;k<two_D;k++)
   	  	if (i<NeighbourNb || j<NeighbourNb  ||   k<NeighbourNb ||
						i>=(1<<ScaleNb)-NeighbourNb || j>=(1<<ScaleNb)-NeighbourNb  || k>=(1<<ScaleNb)-NeighbourNb)  {
							d=i + (1<<ScaleNb)*(j + (1<<ScaleNb)*k);
							RungeKutta_cell(d);
				}

	}

//	int n;
//	for (n = 0; n < 1<<(ScaleNb*Dimension); n++) RungeKutta_cell(n);
}

/*
______________________________________________________________________________________________

	Store cell-average values into temporary ones
______________________________________________________________________________________________

*/
void FineMesh::store()
{
	// --- Local variables ---

	int 	n=0; 					// cell number

	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
	{
		if (UseBoundaryRegions)
		{
			if (IterationNo == 1)
				cell(n)->setOldAverage(cell(n)->average());
			else
				cell(n)->setOldAverage(cell(n)->tempAverage());
		}

		cell(n)->setTempAverage(cell(n)->average());
	}
}

/*
______________________________________________________________________________________________

	Store gradient values into temporary ones
______________________________________________________________________________________________

*/

void FineMesh::storeGrad()
{
	// --- Local variables ---

	int 	n=0; 					// cell number

	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
		cell(n)->setTempGradient(cell(n)->gradient());
}

/*
______________________________________________________________________________________________

	Check stability
______________________________________________________________________________________________

*/
void FineMesh::checkStability() const
{
	// --- Local variables ---

	int 	n=0, iaux; 					// cell number
	real x=0., y=0., z=0.;				// Real position
    iaux = 0;
	// --- Loop on all cells ---

	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
	{
		// --- Compute x, y, z ---

		x = cell(n)->center(1);
		if (Dimension > 1) y = cell(n)->center(2);
		if (Dimension > 2) z = cell(n)->center(3);

		// --- Test if one cell is overflow ---

		if (cell(n)->isOverflow())
		{
			iaux=system("echo Unstable computation.>> carmen.prf");
			if (Cluster == 0) iaux=system("echo carmen: unstable computation. >> OUTPUT");
			cout << "carmen: instability detected at iteration no. "<< IterationNo <<"\n";
			cout << "carmen: position ("<< x <<", "<<y<<", "<<z<<")\n";
			cout << "carmen: abort execution.\n";
			exit(1);
		}
	}
	// --- End loop on all cells ---
}
/*
______________________________________________________________________________________________

	Compute integral values
______________________________________________________________________________________________

*/
void FineMesh::computeIntegral()
{
	// --- Local variables ---

	int	n=0;			// cell number
	int 	AxisNo;			// Counter on dimension
	real	dx=0., dy=0., dz=0.;	// Cell size
	Vector 	Center(Dimension);  	// local center of the flame ball
	real 	VelocityMax=0.;		// local maximum of the velocity
    real    divB=0;
	Vector	GradDensity(Dimension);	// gradient of density
	Vector  GradPressure(Dimension);// gradient of pressure
    real    B1=0., B2=0.;           // Left and right magnetic field cells
    real    modB=0.;
	real    MaxSpeed;
	real    QuantityNo=0.;

	int 	ei=0, ej=0, ek=0;	// 1 if this direction is chosen, 0 elsewhere
	int 	i=0, j=0, k=0;		// Counter on children

	// --- Init ---

	// Init integral values

	FlameVelocity 		= 0.;
	GlobalMomentum 		= 0.;
	GlobalEnergy		= 0.;
	GlobalEnstrophy		= 0.;
	ExactMomentum   	= 0.;
	ExactEnergy		= 0.;

	GlobalReactionRate	= 0.;
	AverageRadius		= 0.;
	ReactionRateMax		= 0.;

	for (AxisNo=1; AxisNo <= Dimension; AxisNo++)
		Center.setValue(AxisNo,XCenter[AxisNo]);

	ErrorMax	= 0.;
	ErrorMid	= 0.;
	ErrorL2		= 0.;
	ErrorNb		= 0;

	RKFError 	= 0.;

	Eigenvalue = 0.;
	QuantityMax.setZero();

	IntVorticity=0.;
	IntDensity=0.;
	IntMomentum.setZero();
	BaroclinicEffect=0.;

// --- Loop on all cells ---

	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
	{
		i = n%(1<<ScaleNb);
		if (Dimension > 1) j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
		if (Dimension > 2) k = n/(1<<(2*ScaleNb));

            dx = cell(n)->size(1);
			dy = (Dimension > 1) ? cell(n)->size(2) : 1.;
			dz = (Dimension > 2) ? cell(n)->size(3) : 1.;

			// --- Compute the global momentum, global energy and global enstrophy ---

			GlobalMomentum 	+= cell(n)->average(2)*dx*dy*dz;
			GlobalEnergy 	+= .5*(cell(n)->magField()*cell(n)->magField() + cell(n)->density()*(cell(n)->velocity()*cell(n)->velocity())) + cell(n)->pressure()/(Gamma-1.0);
			//GlobalEnergy 	+= .5*(cell(n)->density()*(cell(n)->velocity()*cell(n)->velocity()));
			GlobalEnergy    *= dx*dy*dz;
			Helicity        += (cell(n)->magField(2)*cell(n)->velocity(3) - cell(n)->magField(3)*cell(n)->velocity(2))*cell(n)->magField(1) +
                               (cell(n)->magField(3)*cell(n)->velocity(1) - cell(n)->magField(1)*cell(n)->velocity(3))*cell(n)->magField(2) +
                               (cell(n)->magField(1)*cell(n)->velocity(2) - cell(n)->magField(2)*cell(n)->velocity(1))*cell(n)->magField(3);
            Helicity        *=  2*dx*dy*dz;

			// --- Compute maximum of the conservative quantities ---

			for (QuantityNo=1; QuantityNo <=QuantityNb; QuantityNo++)
			{
				if ( QuantityMax.value(QuantityNo) < fabs(cell(n)->average(QuantityNo)) )
					QuantityMax.setValue(QuantityNo, fabs(cell(n)->average(QuantityNo)) );
       		}

			// --- Compute the maximal eigenvalue ---

          		VelocityMax = 0.;
                MaxSpeed    = 0.;
			for (AxisNo=1; AxisNo <= Dimension; AxisNo ++){
				VelocityMax = Max( VelocityMax, fabs(cell(n)->velocity(AxisNo)));
                MaxSpeed    = Max( MaxSpeed   , fabs(cell(n)->fastSpeed(AxisNo)));
			}

			VelocityMax  += MaxSpeed;

			EigenvalueMax = Max (EigenvalueMax, VelocityMax);

            for (AxisNo = 1; AxisNo <= Dimension; AxisNo ++)
			{

				ei = (AxisNo == 1)? 1:0;
				ej = (AxisNo == 2)? 1:0;
				ek = (AxisNo == 3)? 1:0;

                dx = cell(n)->size(AxisNo);
               // dx *= 2.;

                B1=cell(i+ei,j+ej,k+ek)->magField(AxisNo);
  				B2=cell(i-ei,j-ej,k-ek)->magField(AxisNo);
  				modB += (B1 + B2)/dx;
  				divB += (B1-B2)/dx;

            }
        modB += 1.120e-13;
        DIVBMax = Max(DIVBMax,0.5*Abs(divB));
	    DIVB    = DIVBMax/modB;
		break;
		}

	// --- End loop on all cells ---

  ReduceIntegralValues();
}

/*
______________________________________________________________________________________________

	Print header for Data Explorer visualization
______________________________________________________________________________________________

*/
void FineMesh::writeHeader(const char* FileName) const
{
	// --- Local variables ---

	real dx=0., dy=0., dz=0.;		// deltas in x, y, and z
	FILE 	*output;		// Pointer to output file
	int GridPoints;			// Grid points
	char DependencyType[12];	// positions or connections


	// --- For the final data, use positions instead of connections ---

	if (WriteAsPoints)
	{
		GridPoints = (1<<(ScaleNb+PrintMoreScales));
		sprintf(DependencyType,"positions");
	}
	else
	{
		GridPoints = (1<<(ScaleNb+PrintMoreScales))+1;
		sprintf(DependencyType,"connections");
	}

	// --- Open file ---

	if ((output = fopen(FileName,"w")) != NULL)
	{
		// --- Header ---


        dx = (XMax[1]-XMin[1])/((1<<(ScaleNb+PrintMoreScales))-1);
		dy = (XMax[2]-XMin[2])/((1<<(ScaleNb+PrintMoreScales))-1);
		dz = (XMax[3]-XMin[3])/((1<<(ScaleNb+PrintMoreScales))-1);

		// GNUPLOT

		switch(PostProcessing)
		{
			// GNUPLOT
			case 1:
				fprintf(output,"#");
				fprintf(output, TXTFORMAT, " x");
                fprintf(output, TXTFORMAT, "Density");
				fprintf(output, TXTFORMAT, "Pressure");
				fprintf(output, TXTFORMAT, "Temperature");
				fprintf(output, TXTFORMAT, "Energy");
				fprintf(output, TXTFORMAT, "Velocity");
				fprintf(output, "\n");
				break;

			// DATA EXPLORER
			case 2:
				fprintf(output, "# Data Explorer file\n# generated by Carmen\n");

				switch(Dimension)
				{
					case 2:
						dx = (XMax[1]-XMin[1])/(1<<(ScaleNb+PrintMoreScales));
						dy = (XMax[2]-XMin[2])/(1<<(ScaleNb+PrintMoreScales));
						fprintf(output, "grid = %d x %d\n", GridPoints, GridPoints);
						fprintf(output, "positions = %f, %f, %f, %f\n#\n",XMin[1],dx,XMin[2],dy );
						break;

					case 3:
						dx = (XMax[1]-XMin[1])/(1<<(ScaleNb+PrintMoreScales));
						dy = (XMax[2]-XMin[2])/(1<<(ScaleNb+PrintMoreScales));
						dz = (XMax[3]-XMin[3])/(1<<(ScaleNb+PrintMoreScales));
						fprintf(output, "grid = %d x %d x %d\n", GridPoints, GridPoints, GridPoints);
						fprintf(output, "positions = %f, %f, %f, %f, %f, %f\n#\n",XMin[1],dx,XMin[2],dy,XMin[3],dz);
						break;
    				};

				if (DataIsBinary)
					fprintf(output, "format = binary\n");
				else
					fprintf(output, "format = ascii\n");

				fprintf(output, "interleaving = field\n");
                fprintf(output, "field = density, pressure, temperature, energy, velocity\n");
                fprintf(output, "structure = scalar, scalar, scalar, scalar, %d-vector\n",Dimension);
				fprintf(output, "type = %s, %s, %s, %s, %s\n", REAL, REAL, REAL, REAL, REAL);
				fprintf(output, "dependency = %s, %s, %s, %s, %s\n", DependencyType, DependencyType, DependencyType, DependencyType, DependencyType);


				fprintf(output, "header = marker \"START_DATA\\n\" \n");
				fprintf(output, "end\n");
				fprintf(output, "START_DATA\n");

    			break;

			// TECPLOT
			case 3:
				fprintf(output, "VARIABLES = \"x\"\n");
				if (Dimension > 1)
					fprintf(output,"\"y\"\n");
				if (Dimension > 2)
					fprintf(output,"\"z\"\n");
                fprintf(output,"\"RHO\"\n\"P\"\n\"T\"\n\"E\"\n\"U\"\n");
				if (Dimension > 1)
					fprintf(output,"\"V\"\n");
				if (Dimension > 2)
					fprintf(output,"\"W\"\n");
				fprintf(output,"ZONE T=\"Carmen %3.1f\"\n", CarmenVersion);
				fprintf(output,"I=%i, ",GridPoints-1);
				if (Dimension > 1)
					fprintf(output,"J=%i, ",GridPoints-1);
				if (Dimension > 2)
					fprintf(output,"K=%i, ",GridPoints-1);
				fprintf(output,"F=POINT\n");
				break;


                case 4:
                    int N=(1<<ScaleNb);
                    fprintf(output, "# vtk DataFile Version 2.8\nSolucao MHD\n");
                    if(DataIsBinary)
                        fprintf(output, "BINARY\n");
                    else
                        fprintf(output, "ASCII\n");

                    fprintf(output, "DATASET STRUCTURED_GRID\n");
                    if (Dimension == 2)
                    {
                        fprintf(output, "DIMENSIONS %d %d %d \n", N,N,1);
                        fprintf(output, "POINTS %d FLOAT\n", N*N);
                        for (int i = 0; i < N; i++)
                            for (int j = 0; j < N; j++)
                                fprintf(output, "%f %f %f \n", XMin[1] + i*dx, XMin[2] + j*dy, 0.0);

                        fprintf(output, "\n\nPOINT_DATA %d \n", N*N);
                    }
                    if (Dimension == 3)
                    {
                        fprintf(output, "DIMENSIONS %d %d %d \n", N,N,N);
                        fprintf(output, "POINTS %d FLOAT\n", N*N*N);
                        for (int i = 0; i < N; i++)
                            for (int j = 0; j < N; j++)
                                for (int k = 0; k < N; k++)
                                    fprintf(output, "%f %f %f \n", XMin[1] + i*dx, XMin[2] + j*dy, XMin[3] + k*dz);

                        fprintf(output, "\n\nPOINT_DATA %d \n", N*N*N);
                    }

                    break;
		};

		fclose(output);
		return;

	}
	else
	{
		cout << "FineMesh.cpp: In method `void FineMesh::writeHeader()':\n";
		cout << "FineMesh.cpp: cannot open file " << FileName << '\n';
		cout << "carmen: *** [FineMesh.o] Execution error\n";
		cout << "carmen: abort execution.\n";
		exit(1);
	}
}
/*
______________________________________________________________________________________________

	Print cell-average values for graphic visualization
______________________________________________________________________________________________

*/

void FineMesh::writeAverage(const char* FileName)
{
	// --- Local variables ---

	int i=0,j=0,k=0, n=0;		// Coordinates
	FILE 		*output;			// pointer to output file

	//real x=0., y=0., z=0., t=0.;

	// --- Open file ---

  if ((output = fopen(FileName,"a")) != NULL)
	{
		// --- Eventually coarsen grid
		if (PrintMoreScales == -1)
		{
			coarsen();
			ScaleNb--;
		}

		// --- Loop on all cells ---

		for (n=0; n < (1<<(Dimension*ScaleNb)); n++)
   	{

			// -- Compute i, j, k --

			// For Gnuplot and DX, loop order: for i... {for j... {for k...} }
			if (PostProcessing != 3)
			{
				switch(Dimension)
				{
					case 1:
						i = n;
						j = k = 0;
						break;

					case 2:
						j = n%(1<<ScaleNb);
						i = n/(1<<ScaleNb);
						k = 0;
						break;

					case 3:
						k = n%(1<<ScaleNb);
						j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
						i =  n/(1<<(2*ScaleNb));
						break;
				};
			}
			else
			{
				// For Tecplot, loop order: for k... {for j... {for i...} }
				i = n%(1<<ScaleNb);
				if (Dimension > 1) j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
				if (Dimension > 2) k = n/(1<<(2*ScaleNb));
			}

                if(PostProcessing == 4)
                {
					fprintf(output, "\n\nSCALARS eta float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                         switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->etaConst());
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS Density float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                         switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->density());
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS Pressure float\nLOOKUP_TABLE default\n");
					for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->pressure());
                        fprintf(output, "\n");
                    }

					fprintf(output, "\n\nSCALARS Energy float\nLOOKUP_TABLE default\n");
					for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->energy());
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS Vx float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->velocity(1));
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS Vy float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->velocity(2));
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS Vz float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->velocity(3));
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS Bx float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->magField(1));
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS By float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->magField(2));
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nSCALARS Bz float\nLOOKUP_TABLE default\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        FileWrite(output, FORMAT, cell(i,j,k)->magField(3));
                        fprintf(output, "\n");
                    }

  					fprintf(output, "\n\nSCALARS DivB float\nLOOKUP_TABLE default\n");
  					for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };
                        real divB=0, B1=0., B2=0.,dx=0.;
                        int ei=0,ej=0,ek=0;
                        for (int AxisNo = 1; AxisNo <= Dimension; AxisNo ++)
                        {

                            ei = (AxisNo == 1)? 1:0;
                            ej = (AxisNo == 2)? 1:0;
                            ek = (AxisNo == 3)? 1:0;

                            dx = cell(i,j,k)->size(AxisNo);
                            dx *= 2.;

                            B1 = cell(i+ei, j+ej, k+ek)->magField(AxisNo);
                            B2 = cell(i-ei, j-ej, k-ek)->magField(AxisNo);

                            divB += (B1-B2)/dx;
                        }
                        FileWrite(output, FORMAT, divB);
                        fprintf(output, "\n");
                    }

                    fprintf(output, "\n\nVECTORS Velocity float\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };


                        FileWrite(output, FORMAT, cell(i,j,k)->velocity(1));
                        FileWrite(output, FORMAT, cell(i,j,k)->velocity(2));
                        FileWrite(output, FORMAT, cell(i,j,k)->velocity(3));
                    }


                    fprintf(output, "\n\nVECTORS MagField float\n");
                    for (n=0; n < (1<<(Dimension*ScaleNb)); n++){
                        switch(Dimension)
                        {
                            case 1:
                                i = n;
                                j = k = 0;
                                break;

                            case 2:
                                j = n%(1<<ScaleNb);
                                i = n/(1<<ScaleNb);
                                k = 0;
                                break;

                            case 3:
                                k = n%(1<<ScaleNb);
                                        j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
                                i =  n/(1<<(2*ScaleNb));
                                break;
                        };


                        FileWrite(output, FORMAT, cell(i,j,k)->magField(1));
                        FileWrite(output, FORMAT, cell(i,j,k)->magField(2));
                        FileWrite(output, FORMAT, cell(i,j,k)->magField(3));
                    }

                }else{
                        // MHD
                        if (ScalarEqNb == 1)
                            FileWrite(output, FORMAT, cell(i,j,k)->average(Dimension+3)/cell(i,j,k)->density());
                        else
                                FileWrite(output, FORMAT, cell(i,j,k)->density());

                        FileWrite(output, FORMAT, cell(i,j,k)->pressure()*Gamma*Ma*Ma); // Dimensionless pressure
                        FileWrite(output, FORMAT, cell(i,j,k)->temperature());
                        FileWrite(output, FORMAT, cell(i,j,k)->energy());
                        if (PostProcessing == 1) FileWrite(output, FORMAT, 0.);
                            for (int AxisNo = 1; AxisNo <= Dimension; AxisNo++)
                                FileWrite(output, FORMAT, cell(i,j,k)->velocity(AxisNo));

                }



			if (!DataIsBinary)
				fprintf(output,"\n");

			if (PostProcessing == 1)
			{
				if (j==(1<<ScaleNb)-1)
					fprintf(output,"\n");

				if (k==(1<<ScaleNb)-1)
					fprintf(output,"\n");
			}
    }
		fclose(output);

		// --- Eventually refine grid

		if (PrintMoreScales == -1)
		{
			ScaleNb++;
			refine();
		}
	}
	else
	{
		cout << "FineMesh.cpp: In method `void FineMesh::writeAverage()':\n";
		cout << "FineMesh.cpp: cannot open file " << FileName << '\n';
		cout << "carmen: *** [FineMesh.o] Execution error\n";
		cout << "carmen: abort execution.\n";
		exit(1);
	}
}

/*
______________________________________________________________________________________________

	Write coarse
______________________________________________________________________________________________

*/





/*
______________________________________________________________________________________________

	Back up data
______________________________________________________________________________________________

*/
void FineMesh::backup()
{
	int n=0;				// Cell number
	FILE* output;				// Output file
  	int QuantityNo;				// Counter on quantities

	// --- Init ---

	output = fopen(BackupName,"w");

	// --- Backup data on cells ---

        fprintf(output, "Backup at iteration %i, physical time %e\n", IterationNo, ElapsedTime);
	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
	for (QuantityNo=1; QuantityNo <= QuantityNb; QuantityNo++)
		fprintf(output, FORMAT, cell(n)->average(QuantityNo));

	fclose(output);
}

/*
______________________________________________________________________________________________

	Restore data
______________________________________________________________________________________________

*/
void FineMesh::restore()
{
	int 	n,iaux;		// Cell number
	int 	QuantityNo;	// Counter on quantities
	FILE* 	input;		// Input file
  	real 	buf;		// Buffer
//        char    line[1024];

	// --- Init ---

  	input = fopen(BackupName,"r");

	// When there is no back-up file, return
	if (!input) return;

  	// --- Restore data on cells ---

        //fgets(line, 1024, input);
	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
 	for (QuantityNo=1; QuantityNo <= QuantityNb; QuantityNo++)
	{
        	iaux=fscanf(input, BACKUP_FILE_FORMAT, &buf);
        	cell(n)->setAverage(QuantityNo, buf);
    	}

	fclose(input);
	return;
}
/*
______________________________________________________________________________________________

	Compute time-average values
______________________________________________________________________________________________

*/
void FineMesh::computeTimeAverage()
{
	// Local variables

	int i=0, j=0, k=0, n=0;	// Counters on directions

	// Start this procedure when the physical time is larger than StartTimeAveraging

	if (TimeStep*IterationNo <= StartTimeAveraging)
		return;

	// Update time-average values with values in FineMesh

	for (n = 0; n < 1<<(ScaleNb*Dimension); n++)
	{
		i = n%(1<<ScaleNb);
		if (Dimension > 1) j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
		if (Dimension > 2) k = n/(1<<(2*ScaleNb));

		MyTimeAverageGrid->updateValue(i,j,k,cell(i,j,k)->average());
	}

	// Update the number of samples (Warning: currently only for constant time step !!)
	MyTimeAverageGrid->updateSample();
}
/*
______________________________________________________________________________________________

	Print cell-average values for graphic visualization
______________________________________________________________________________________________

*/
void FineMesh::writeTimeAverage(const char* FileName) const
{
	// --- Local variables ---

	int n=0, i=0, j=0, k=0;

	real dx, dy, dz;		// deltas in x, y, and z
	real x=0, y=0, z=0;		// positions
	FILE 	*output;		// Pointer to output file
	int GridPoints = (1<<ScaleNb)+1;// Grid points

	// --- Open file ---

	if ((output = fopen(FileName,"w")) != NULL)
	{
		// --- Header ---

		switch(PostProcessing)
		{
			// GNUPLOT
			case 1:
				fprintf(output,"# x             Velocity				Stress\n");
				break;

			// DATA EXPLORER
			case 2:
				fprintf(output, "# Data Explorer file\n# generated by Carmen\n");

				switch(Dimension)
				{
					case 2:
						dx = (XMax[1]-XMin[1])/(1<<ScaleNb);
						dy = (XMax[2]-XMin[2])/(1<<ScaleNb);
						fprintf(output, "grid = %d x %d\n", GridPoints, GridPoints);
						fprintf(output, "positions = %f, %f, %f, %f\n#\n",XMin[1],dx,XMin[2],dy );
						break;

					case 3:
						dx = (XMax[1]-XMin[1])/(1<<ScaleNb);
						dy = (XMax[2]-XMin[2])/(1<<ScaleNb);
						dz = (XMax[3]-XMin[3])/(1<<ScaleNb);
						fprintf(output, "grid = %d x %d x %d\n", GridPoints, GridPoints, GridPoints);
						fprintf(output, "positions = %f, %f, %f, %f, %f, %f\n#\n",XMin[1],dx,XMin[2],dy,XMin[3],dz);
						break;
    		};

				if (DataIsBinary)
					fprintf(output, "format = binary\n");
				else
					fprintf(output, "format = ascii\n");

				fprintf(output, "interleaving = field\n");

				fprintf(output, "field = U, V");

				if (Dimension >2)
					fprintf(output, ", W");

				fprintf(output, ", U\'U\', U\'V\', V\'V\'");

				if (Dimension >2)
					fprintf(output, ", U\'W\', V\'W\', W\'W\'");

 				fprintf(output, "\n");

				fprintf(output, "structure = scalar");
				for (n=1; n < (Dimension*(Dimension+3))/2 ; n++)
					 fprintf(output, ", scalar");
				fprintf(output, "\n");

				fprintf(output, "type = %s", REAL);
				for (n=1; n < (Dimension*(Dimension+3))/2 ; n++)
					 fprintf(output, ", %s", REAL);
				fprintf(output, "\n");

				fprintf(output, "dependency = connections");
				for (n=1; n < (Dimension*(Dimension+3))/2 ; n++)
					 fprintf(output, ", connections");
				fprintf(output, "\n");

				fprintf(output, "header = marker \"START_DATA\\n\" \n");
				fprintf(output, "end\n");
				fprintf(output, "START_DATA\n");

    		break;

			// TECPLOT
			case 3:

				// --- Write axes (x,y,z) ---

				fprintf(output, "VARIABLES = \"x\"\n");
				if (Dimension > 1)
					fprintf(output,"\"y\"\n");
				if (Dimension > 2)
					fprintf(output,"\"z\"\n");

        // --- Write averages U, V, W ---

				fprintf(output,"\"U\"\n");
				if (Dimension > 1)
					fprintf(output,"\"V\"\n");
				if (Dimension > 2)
					fprintf(output,"\"W\"\n");

        // --- Write stress tensor U'U', U'V', V'V', U'W', V'W', W'W' ---

				fprintf(output,"\"U\'U\'\"\n");
				if (Dimension > 1)
				{
					fprintf(output,"\"U\'V\'\"\n");
					fprintf(output,"\"V\'V\'\"\n");
				}
				if (Dimension > 2)
				{
					fprintf(output,"\"U\'W\'\"\n");
					fprintf(output,"\"V\'W\'\"\n");
					fprintf(output,"\"W\'W\'\"\n");
				}

				fprintf(output,"ZONE T=\"Carmen %3.1f\"\n",CarmenVersion);
				fprintf(output,"I=%i, ",(1<<ScaleNb));
				if (Dimension > 1)
					fprintf(output,"J=%i, ",(1<<ScaleNb));
				if (Dimension > 2)
					fprintf(output,"K=%i, ",(1<<ScaleNb));
				fprintf(output,"F=POINT\n");
				break;
		};

		// --- Loop on all cells ---

		for (n=0; n < (1<<(Dimension*ScaleNb)); n++)
   	{

			// -- Compute i, j, k --

			// For Gnuplot and DX, loop order: for i... {for j... {for k...} }

			if (PostProcessing != 3)
			{
				switch(Dimension)
				{
					case 1:
						i = n;
						break;

					case 2:
						j = n%(1<<ScaleNb);
						i = n/(1<<ScaleNb);
						break;

					case 3:
						k = n%(1<<ScaleNb);
            j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
						i =  n/(1<<(2*ScaleNb));
						break;
				};
			}
			else
			{
				// For Tecplot, loop order: for k... {for j... {for i...} }

				i = n%(1<<ScaleNb);
				if (Dimension > 1) j = (n%(1<<(2*ScaleNb)))/(1<<ScaleNb);
				if (Dimension > 2) k = n/(1<<(2*ScaleNb));
			}

			// Compute x,y,z

			x = cell(i,j,k)->center(1);
			if (Dimension > 1)
				y = cell(i,j,k)->center(2);
			if (Dimension > 2)
				z = cell(i,j,k)->center(3);

			// Write cell-center coordinates (only for Gnuplot and Tecplot)

			if (PostProcessing != 2)
			{
				fprintf(output, FORMAT, x);
				if (Dimension > 1)
					fprintf(output, FORMAT, y);
				if (Dimension > 2)
					fprintf(output, FORMAT, z);
			}

      for (int AxisNo = 1; AxisNo <= Dimension; AxisNo++)
				FileWrite(output, FORMAT,MyTimeAverageGrid->velocity(i,j,k,AxisNo));

      for (int AxisNo = 1; AxisNo <= (Dimension*(Dimension+1))/2; AxisNo++)
				FileWrite(output, FORMAT,MyTimeAverageGrid->stress(i,j,k,AxisNo));

    	if (!DataIsBinary)
				fprintf(output,"\n");

			if (PostProcessing == 1)
			{
				if (j==(1<<ScaleNb)-1)
					fprintf(output,"\n");

				if (k==(1<<ScaleNb)-1)
					fprintf(output,"\n");
			}
    }
		fclose(output);
	}
	else
	{
		cout << "FineMesh.cpp: In method `void FineMesh::writeTimeAverage()':\n";
		cout << "FineMesh.cpp: cannot open file " << FileName << '\n';
		cout << "carmen: *** [FineMesh.o] Execution error\n";
		cout << "carmen: abort execution.\n";
		exit(1);
	}
}
/*
______________________________________________________________________________________________

Make coarse grid data and store fine grid data into temporary
______________________________________________________________________________________________

*/

void FineMesh::coarsen()
{
	int n=0;

	int i=0,j=0,k=0;

	int li=0, lj=0, lk=0;

	int ei = 1;
	int ej = (Dimension > 1) ? 1:0;
	int ek = (Dimension > 2) ? 1:0;

	// --- Store data into temporary and reset it ---

	for (n=0; n < (1<<(Dimension*ScaleNb)); n++)
   	{
		cell(n)->setTempAverage(cell(n)->average());
		cell(n)->setAverageZero();
	}

	// -- Reset data ---

	n = 0;

	for (k = 0; k <= ek*((1<<(ScaleNb-1))-1); k++)
 	for (j = 0; j <= ej*((1<<(ScaleNb-1))-1); j++)
	for (i = 0; i <= ei*((1<<(ScaleNb-1))-1); i++)
  	{
		for (lk = 0; lk <= ek; lk++)
		for (lj = 0; lj <= ej; lj++)
		for (li = 0; li <= ei; li++)
			cell(n)->setAverage(cell(n)->average()+ cell(2*i+li, 2*j+lj, 2*k+lk)->tempAverage());


		cell(n)->setAverage( (1./(1<<Dimension)) * cell(n)->average() );

		n++;
	}

}

/*
______________________________________________________________________________________________

Restore fine grid data from temporary. Inverse of 'coarsen()'
______________________________________________________________________________________________

*/
void FineMesh::refine()
{
	int n;

	// --- Restore data from temporary ---

	for (n=0; n < (1<<(Dimension*ScaleNb)); n++)
   	{
		cell(n)->setAverage(cell(n)->tempAverage());
	}
}



