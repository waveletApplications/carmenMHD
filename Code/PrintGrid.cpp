/***************************************************************************
                          PrintGrid.cpp  -  description
                             -------------------
    begin                : Tue Mar 19 2002
    copyright            : (C) 2002 by Olivier Roussel & Alexei Tsigulin
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
/** @file PrintGrid.cpp
  * @brief Functions to print every variable of the MHD model
  */
#include "Carmen.h"


/*
______________________________________________________________________________________________

Constructor
______________________________________________________________________________________________

*/
PrintGrid::PrintGrid(int L)
{

	int n=0; // Array size

	localScaleNb=L;
	elementNb = n =	(1<<localScaleNb)+1;
	if (Dimension > 1) elementNb *= n;
	if (Dimension > 2) elementNb *= n;

	Q  = new Vector[elementNb];
	Qt = new Vector[elementNb];

  int i;
  for (i=0;i<elementNb;i++)
  {
    Q[i].setDimension(QuantityNb);
    Qt[i].setDimension(QuantityNb);
  }


}
/*
______________________________________________________________________________________________

Distructor
______________________________________________________________________________________________

*/
PrintGrid::~PrintGrid()
{
	delete[] Q;
	delete[] Qt;
}
/*
______________________________________________________________________________________________

Set procedure
______________________________________________________________________________________________

*/
void PrintGrid::setValue(const int i, const int j, const int k, const Vector& UserAverage)
{
	// --- Local variables ---

	int n=(1<<localScaleNb)+1;	// n = 2^localScaleNb+1

  *(Q + i + n*(j + n*k)) = UserAverage;
}
/*
______________________________________________________________________________________________

Get procedure
______________________________________________________________________________________________

*/
Vector PrintGrid::value(const int i, const int j, const int k) const
{
	// --- Local variables ---

	int n = (1<<localScaleNb)+1; // n = 2^localScaleNb

	return *(Q + i + n*(j + n*k));
}
/*
______________________________________________________________________________________________

*/

real PrintGrid::value(const int i, const int j, const int k, const int QuantityNo) const
{
	// --- Local variables ---

	int n = (1<<localScaleNb)+1; 						// n = 2^localScaleNb

	return (Q + i + n*(j + n*k))->value(QuantityNo);
}

/*
______________________________________________________________________________________________

*/

real PrintGrid::cellValue(const int i, const int j, const int k, const int QuantityNo) const
{
	// --- Local variables ---

	int n = (1<<localScaleNb)+1; 					// n = 2^localScaleNb+1
	int li=0, lj=0, lk=0;									// local i,j,k


	if (CMin[1] == 2)
	  li = ((i+n)/n==1)? i : (2*n-i-1)%n;  // Neumann
	else
		li = (i+n)%n;                        // Periodic

	// -- in y --

	if (Dimension > 1)
	{
		if (CMin[2] == 2)
	 		lj = ((j+n)/n==1)? j : (2*n-j-1)%n; // Neumann
		else
			lj = (j+n)%n;                       // Periodic
	}

	// -- in z --

	if (Dimension > 2)
	{
		if (CMin[3] == 2)
	  	lk = ((k+n)/n==1)? k : (2*n-k-1)%n; // Neumann
		else
			lk = (k+n)%n;												// Periodic
	}

	return (Q + li + n*(lj + n*lk))->value(QuantityNo);
}

/*
______________________________________________________________________________________________

*/

Vector PrintGrid::velocity(const int i, const int j, const int k) const
{
	Vector V(3);

 for (int AxisNo=1; AxisNo <= 3; AxisNo++)
		V.setValue( AxisNo, cellValue(i,j,k,AxisNo+1)/cellValue(i,j,k,1));

	return V;
}

/*
______________________________________________________________________________________________

*/

Vector PrintGrid::magField(const int i, const int j, const int k) const
{
	Vector V(3);

 for (int AxisNo=1; AxisNo <= 3; AxisNo++)
		V.setValue( AxisNo, cellValue(i,j,k,AxisNo+6));

	return V;
}

/*
______________________________________________________________________________________________

*/

real PrintGrid::pressure(const int i, const int j, const int k) const
{
	Vector V(3), B(3);
	real rho, rhoE;

	rho  = density(i,j,k);
	V    = velocity(i,j,k);
	B    = magField(i,j,k);
	rhoE = energy(i,j,k);

	return (Gamma-1.)*(rhoE - .5*rho*(V*V) - .5*(B*B));
}

/*
______________________________________________________________________________________________

*/

real PrintGrid::temperature(const int i, const int j, const int k) const
{
	real rho, p;

	if (EquationType >=3 && EquationType <=5)
		return value(i,j,k,1);

	rho  = density(i,j,k);
	p    = pressure(i,j,k);

	return Gamma*Ma*Ma*p/rho;
}
/*
______________________________________________________________________________________________

*/

real PrintGrid::concentration(const int i, const int j, const int k) const
{

	if (EquationType >=3 && EquationType <=5)
		return value(i,j,k,2);

	return 0.;
}

/*
______________________________________________________________________________________________

*/

// Returns 0 in 1D, the scalar vorticity in 2D, the vorticity norm in 3D

real PrintGrid::divergenceB(const int i, const int j, const int k) const
{
	int L=localScaleNb;
	int n = (1<<L);
	real dx=0., dy=0., dz=0.;
	real Div=0.;
	real By1=0., By2=0., Bz1=0., Bz2=0.;
	real Bx1=0., Bx2=0.;
    real Bx =0., By=0.;

	if (Dimension == 1){
        dx = (XMax[1]-XMin[1])/n;

        Bx1 = magField(BC(i-1,1,n), BC(j,2,n),BC(k,3,n),1);
        Bx2 = magField(BC(i+1,1,n), BC(j,2,n),BC(k,3,n),1);

        Div = (Bx2-Bx1)/(2.*dx);

	}else if (Dimension == 2){

        dx = (XMax[1]-XMin[1])/n;
        dy = (XMax[2]-XMin[2])/n;
        Bx1 = magField(BC(i-1,1,n), BC(j  ,2,n),BC(k,3,n),1);
        Bx2 = magField(BC(i+1,1,n), BC(j  ,2,n),BC(k,3,n),1);
        By1 = magField(BC(i  ,1,n), BC(j-1,2,n),BC(k,3,n),2);
        By2 = magField(BC(i  ,1,n), BC(j+1,2,n),BC(k,3,n),2);
        Bx = magField(BC(i,1,n), BC(j,2,n),BC(k,3,n),1);
        By = magField(BC(i,1,n), BC(j,2,n),BC(k,3,n),2);

        //if(Bx2!=Bx1 && By2!=By1)
            //;Div = ((Bx2-Bx1)/(dx) + (By2-By1)/(dy))/((fabs(Bx1)+fabs(Bx2))/(dx) + (fabs(By1)+fabs(By2))/(dy) + 1.120e-13);

        Div = ((Bx2-Bx1)/(2.*dx) + (By2-By1)/(2.*dy));

	}else if (Dimension == 3){

        dx = (XMax[1]-XMin[1])/n;
        dy = (XMax[2]-XMin[2])/n;
        dz = (XMax[3]-XMin[3])/n;

        Bx1 = magField(BC(i-1,1,n), BC(j  ,2,n),BC(k  ,3,n),1);
        Bx2 = magField(BC(i+1,1,n), BC(j  ,2,n),BC(k  ,3,n),1);
        By1 = magField(BC(i  ,1,n), BC(j-1,2,n),BC(k  ,3,n),2);
        By2 = magField(BC(i  ,1,n), BC(j+1,2,n),BC(k  ,3,n),2);
        Bz1 = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k-1,3,n),3);
        Bz2 = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k+1,3,n),3);

        Div = (Bx2-Bx1)/(2.*dx) + (By2-By1)/(2.*dy) + (Bz2-Bz1)/(2.*dz);

	}

    return Div;
}

/*
______________________________________________________________________________________________

*/

// Returns 0 in 1D, the scalar vorticity in 2D, the vorticity norm in 3D

real PrintGrid::vorticity(const int i, const int j, const int k) const
{

//	return result;
	int L=localScaleNb;
	int n = (1<<L);
	real dx=0., dy=0., dz=0.;
	real Div=0.;
	real By1=0., By2=0., Bz1=0., Bz2=0.;
	real Bx1=0., Bx2=0.;
    real Bx =0., By=0., Bz=0.;
    real aux=0.;
    real mod=0.;

	if (Dimension == 1){
        dx = (XMax[1]-XMin[1])/n;

        Bx1 = magField(BC(i-1,1,n), BC(j,2,n),BC(k,3,n),1);
        Bx2 = magField(BC(i+1,1,n), BC(j,2,n),BC(k,3,n),1);

        Div = (Bx2-Bx1)/(2.*dx);

	}else if (Dimension == 2){

        dx  = (XMax[1]-XMin[1])/n;
        dy  = (XMax[2]-XMin[2])/n;

        Bx1 = magField(BC(i-1,1,n), BC(j  ,2,n),BC(k,3,n),1);
        Bx2 = magField(BC(i+1,1,n), BC(j  ,2,n),BC(k,3,n),1);
        By1 = magField(BC(i  ,1,n), BC(j-1,2,n),BC(k,3,n),2);
        By2 = magField(BC(i  ,1,n), BC(j+1,2,n),BC(k,3,n),2);
        Bx  = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k,3,n),1);
        By  = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k,3,n),2);
        Bz  = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k,3,n),3);

        aux = ((Bx2-Bx1)/(2.*dx) + (By2-By1)/(2.*dy));
        mod = sqrt(Bx*Bx+By*By+Bz*Bz);
        //if(mod > 0.0e-20)
            Div = dx*dy*(Abs(aux)/mod);
        //else
          //  Div = 0.0;
        if(isnan(Div))
            Div = 0.0;
       // Div = Max(Abs(dx),Abs(dy))*(Abs(aux)/sqrt(Bx*Bx+By*By+Bz*Bz));

	}else if (Dimension == 3){

        dx  = (XMax[1]-XMin[1])/n;
        dy  = (XMax[2]-XMin[2])/n;
        dz  = (XMax[3]-XMin[3])/n;

        Bx1 = magField(BC(i-1,1,n), BC(j  ,2,n),BC(k  ,3,n),1);
        Bx2 = magField(BC(i+1,1,n), BC(j  ,2,n),BC(k  ,3,n),1);
        By1 = magField(BC(i  ,1,n), BC(j-1,2,n),BC(k  ,3,n),2);
        By2 = magField(BC(i  ,1,n), BC(j+1,2,n),BC(k  ,3,n),2);
        Bz1 = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k-1,3,n),3);
        Bz2 = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k+1,3,n),3);
        Bx  = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k  ,3,n),1);
        By  = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k  ,3,n),2);
        Bz  = magField(BC(i  ,1,n), BC(j  ,2,n),BC(k  ,3,n),3);

        aux = (Bx2-Bx1)/(2.*dx) + (By2-By1)/(2.*dy) + (Bz2-Bz1)/(2.*dz);
        mod = sqrt(Bx*Bx+By*By+Bz*Bz);
        //if(mod > 0.0e-20)
            Div = dx*dy*dz*(Abs(aux)/mod);
        //else
        if(isnan(Div))
            Div = 0.0;

        //Div = Max(Abs(dx),Max(Abs(dy),Abs(dz)))*(Abs(aux)/sqrt(Bx*Bx+By*By+Bz*Bz));


	}

    return Div;
}
/*
______________________________________________________________________________________________

Get temporary value (private)
______________________________________________________________________________________________

*/
Vector PrintGrid::tempValue(const int l, const int i, const int j, const int k) const
{
	// --- Local variables ---

	int li=0, lj=0, lk=0; 		// Local i,j,k
	int n=(1<<l);	// n = 2^l
	int N=(1<<localScaleNb); // n=2^localScaleNb

	// --- Periodicity or Neumann ? (Dirichlet not accepted here) ---

	// -- in x --

	if (CMin[1] == 2)
	  li = ((i+n)/n==1)? i : (2*n-i-1)%n;  // Neumann
	else
		li = (i+n)%n;                        // Periodic

	// -- in y --

	if (Dimension > 1)
	{
		if (CMin[2] == 2)
	 		lj = ((j+n)/n==1)? j : (2*n-j-1)%n; // Neumann
		else
			lj = (j+n)%n;                       // Periodic
	}

	// -- in z --

	if (Dimension > 2)
	{
		if (CMin[3] == 2)
	  	lk = ((k+n)/n==1)? k : (2*n-k-1)%n; // Neumann
		else
			lk = (k+n)%n;												// Periodic
	}

	// --- return pointer to cell ---

	return *( Qt + li + (N+1)*(lj + (N+1)*lk) );
}
/*
______________________________________________________________________________________________

	Refresh procedure
______________________________________________________________________________________________

*/
void PrintGrid::refresh()
{
	for (int n=0; n<elementNb; n++)
		*(Qt+n) = *(Q+n);
}
/*
______________________________________________________________________________________________

	Predict procedure
______________________________________________________________________________________________

*/
void PrintGrid::predict(const int l, const int i, const int j, const int k)
{
	// --- Local variables ---

	int pi=1, pj=1, pk=1;	// Parity of i,j,k

	Vector	Result(QuantityNb);

	// --- Init result with the cell-average value of Qt ---

	Result = tempValue(l-1,(i+4)/2-2,(j+4)/2-2,(k+4)/2-2);

	// --- 1D case ---

	pi = (i%2 == 0)?1:-1;
	Result += (pi*-.125) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2,(k+4)/2-2);
	Result -= (pi*-.125) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2,(k+4)/2-2);

	// --- 2D case ---

 	if (Dimension > 1)
	{
		pj = (j%2 == 0)?1:-1;
		Result += (pj*-.125) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2+1,(k+4)/2-2);
		Result -= (pj*-.125) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2-1,(k+4)/2-2);

		Result += (pi*pj*.015625) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2+1,(k+4)/2-2);
		Result -= (pi*pj*.015625) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2-1,(k+4)/2-2);
		Result -= (pi*pj*.015625) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2+1,(k+4)/2-2);
		Result += (pi*pj*.015625) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2-1,(k+4)/2-2);
  }

	// --- 3D case ---

 	if (Dimension > 2)
	{
		pk = (k%2 == 0)?1:-1;
		Result += (pk*-.125) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2,(k+4)/2-2+1);
		Result -= (pk*-.125) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2,(k+4)/2-2-1);

		Result += (pi*pk*.015625) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2,(k+4)/2-2+1);
		Result -= (pi*pk*.015625) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2,(k+4)/2-2-1);
		Result -= (pi*pk*.015625) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2,(k+4)/2-2+1);
		Result += (pi*pk*.015625) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2,(k+4)/2-2-1);

		Result += (pj*pk*.015625) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2+1,(k+4)/2-2+1);
		Result -= (pj*pk*.015625) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2+1,(k+4)/2-2-1);
		Result -= (pj*pk*.015625) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2-1,(k+4)/2-2+1);
		Result += (pj*pk*.015625) * tempValue(l-1,(i+4)/2-2,(j+4)/2-2-1,(k+4)/2-2-1);

		Result += (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2+1,(k+4)/2-2+1);
		Result -= (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2+1,(k+4)/2-2-1);
		Result -= (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2-1,(k+4)/2-2+1);
		Result += (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2+1,(j+4)/2-2-1,(k+4)/2-2-1);
		Result -= (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2+1,(k+4)/2-2+1);
		Result += (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2+1,(k+4)/2-2-1);
		Result += (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2-1,(k+4)/2-2+1);
		Result -= (pi*pj*pk*-.001953125) * tempValue(l-1,(i+4)/2-2-1,(j+4)/2-2-1,(k+4)/2-2-1);
  }

	setValue(i,j,k,Result);
}
/*
______________________________________________________________________________________________

	Compute point-values
______________________________________________________________________________________________

*/
void PrintGrid::computePointValue()
{
	int i=0, j=0, k=0;
	int l=localScaleNb;
	int n=(1<<l);

	switch(Dimension)
	{
		case 1:
			for (i=0;i<=n;i++)
				setValue(i,j,k,.5*(tempValue(l,i-1,j,k)+tempValue(l,i,j,k)));
			break;

    case 2:
			for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
				setValue(i,j,k, .25*(tempValue(l,i-1,j-1,k)+tempValue(l,i-1,j,k)+tempValue(l,i,j-1,k)+tempValue(l,i,j,k)) );
			break;

		default:
			for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
			for (k=0;k<=n;k++)
				setValue(i,j,k,.125*(tempValue(l,i-1,j-1,k-1)+tempValue(l,i-1,j,k-1)+tempValue(l,i,j-1,k-1)+tempValue(l,i,j,k-1)
												+tempValue(l,i-1,j-1,k)+tempValue(l,i-1,j,k)+tempValue(l,i,j-1,k)+tempValue(l,i,j,k)) );
			break;
	};
}

