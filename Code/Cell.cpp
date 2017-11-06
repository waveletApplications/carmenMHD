/***************************************************************************
                          Cell.cpp  -  description
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
/** @file Cell.cpp
  * @brief Constructor and distructor of the cell class. Also computes the cell-averages of the MHD variables.
  */
#include "Carmen.h"

/*
______________________________________________________________________________________________

Constructor
______________________________________________________________________________________________

*/

/**
 * @brief Cell constructor.
 * 
 */
Cell::Cell () :
	X(Dimension),
	dX(Dimension),
	Q(QuantityNb),
	Qs(QuantityNb),
	Qlow(((!ConstantTimeStep && StepNb > 2) || TimeAdaptivity)? QuantityNb:0),
	Qold((UseBoundaryRegions)? QuantityNb:0),
	D(QuantityNb),
	Res(),
	PGrad(Dimension),
	Grad(((EquationType==6))? Dimension:0, ((EquationType==6))? QuantityNb:0),
	Grads(((EquationType==6) && SchemeNb > 5)? Dimension:0, ((EquationType==6) && SchemeNb > 5)? QuantityNb:0)
{
	// Empty constructor
	;
}
/*
______________________________________________________________________________________________

Distructor
______________________________________________________________________________________________

*/
/**
 * @brief Cell distructor.
 * 
 */
Cell::~Cell()
{
	// Empty distructor
}
/*
______________________________________________________________________________________________

	Set procedures
______________________________________________________________________________________________

*/

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the pressure of the fluid.
 * The pressure is computed in terms of the energy density, velocity and magnetic field.
 * It is given by (Gamma-1.)*(rhoE - .5*(rhoV*rhoV)/rho - .5*(B*B));
 * return double
 */

real	Cell::pressure() const
{
	// Conservative quantities;

	real rho, rhoE;
	Vector rhoV(3), B(3);

	// Get conservative quantities

      	rho = Q.value(1);

	for (int i=1 ; i<=3; i++){
	  B.setValue(i, Q.value(i+6));
	  rhoV.setValue(i,Q.value(i+1));
	}
	rhoE = Q.value(5);

	// Return pressure

	return (Gamma-1.)*(rhoE - .5*(rhoV*rhoV)/rho - .5*(B*B));


}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the temporary pressure of the fluid.
 * This computation is needed for the Runge-Kutta time integration. 
 * @return double
 */
real	Cell::tempPressure() const
{
	// Conservative quantities;

	real rho, rhoE;
	Vector rhoV(3), B(3);

	// Get conservative quantities

	rho = Qs.value(1);

	for (int i=1 ; i<=3 ; i++){
	    rhoV.setValue(i,Qs.value(i+1));
            B.setValue(i, Qs.value(i+6));
	}
	
	rhoE = Qs.value(5);

	// Return pressure

	return (Gamma-1.)*(rhoE - .5*(rhoV*rhoV)/rho - .5*(B*B));

}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the pressure of the fluid at the instant n-1.
 * This value is useful for time integration computations.
 * @return double
 */

real	Cell::oldPressure() const
{
	// Conservative quantities;

	real rho, rhoE;
	Vector rhoV(3), B(3);

	// Get conservative quantities

      	rho = Qold.value(1);

	for (int i=1 ; i<=3 ; i++){
		rhoV.setValue(i,Qold.value(i+1));
        B.setValue(i, Qold.value(i+6));
	}
	rhoE = Qold.value(5);

	// Return pressure

	return (Gamma-1.)*(rhoE - .5*(rhoV*rhoV)/rho -.5*(B*B));

}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the temperature. Not useful for MHD computarions.
 * 
 * @return double
 */

real  Cell::temperature() const
{

    if(!ComputeTemp) exit(1);
	
   // Conservative quantities;
    real rho, p, T;

    // Get conservative quantities
    rho = density();
    p = pressure();
    T = p/rho;

    // Return temperature

    return T;
}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the temporary temperature. Not useful for MHD computarions.
 * 
 * @return double
 */

real  Cell::tempTemperature() const
{

    if(!ComputeTemp) exit(1);
    
    // Conservative quantities;
    real rho, p, T;
    T = Qs.value(1);

    // Get conservative quantities
    rho = tempDensity();
    p = tempPressure();
    T = Gamma*Ma*Ma*p/rho;


    // Return temperature

    return T;
}

/*
______________________________________________________________________________________________

*/

/**
 * @brief Computes the magnetic field.
 * Allocates the magnetic field initial condition Q[i+6] to its components.
 * 
 * @return Vector
 */
Vector Cell::magField() const
{

	// Local variables
	Vector B(3);
	int i;

	for (i=1; i<=3; i++)
	    B.setValue(i,Q.value(i+6));

	return	B;
}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes temporary the magnetic field.
 * This value is useful for time integration computations.
 * 
 * @return Vector
 */
Vector Cell::tempMagField() const
{

	// Local variables

	Vector B(3);
	int i;

	for (i=1; i<=3; i++)
		B.setValue(i,Qs.value(i+6));

	return	B;
}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the velocity of the fluid.
 * Allocates the velocity initial condition Q[i+6] to its components.
 * 
 * @return Vector
 */
Vector Cell::velocity() const
{

	// Local variables

	Vector V(3);
	int i;

	for (i=1; i<=3; i++)
		V.setValue(i,Q.value(i+1)/Q.value(1));

	return	V;
}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the temporary velocity of the fluid.
 * This value is useful for time integration computations.
 * 
 * @return Vector
 */
Vector Cell::tempVelocity() const
{

	// Local variables

	Vector V(3);
	int i;

	for (i=1; i<=3; i++)
		V.setValue(i,Qs.value(i+1)/Qs.value(1));

	return	V;
}


/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the fast magnetoacoustic wave at each direction.
 * 
 * @param AxisNo Number of axis of interest. 1: x-direction, 2: y-direction, 3: z-direction.
 * @return double
 */

real	Cell::fastSpeed(const int AxisNo) const
{
    real result;
    real a = Gamma*pressure()/density();
    real b = (magField()*magField())/density();
    real bk= (magField(AxisNo)*magField(AxisNo))/density();


    result = sqrt(.5*(a+b+sqrt((a+b)*(a+b) - 4.0*a*bk)));

    return result;
}

/*
______________________________________________________________________________________________

*/
/**
 * @brief Computes the volume of a cell.
 * 
 * @return double
 */

real	Cell::volume() const
{
	int AxisNo = 1;
	real result = 1.;

	for (AxisNo = 1; AxisNo <= Dimension; AxisNo++)
		result *= size(AxisNo);

	return result;

}

/*
______________________________________________________________________________________________

	Test procedures
______________________________________________________________________________________________

*/
bool Cell::isOverflow() const
{
	// --- Local variables ---

	int n;					// Counter on the quantities

	// --- If one of the values is overflow, return true ---

	for (n = 1; n <= QuantityNb; n++)
		if (average().isNaN()) return true;

	return false;
}
/*
______________________________________________________________________________________________

	Operator
______________________________________________________________________________________________

*/
/**
 * @brief Defines the cell operators.
 * It is possible to obtain the cell values as:
 * - Center coordinates
 * - Size
 * - Average
 * - Temporary average
 * - Divergence
 * - Gradient of Psi
 * 
 * @param C Cell of interest
 * @return void
 */

void Cell::operator=(const Cell& C)
{
	// local cell becomes equal to cell C

	setCenter(C.center());
	setSize(C.size());
	setAverage(C.average());
	setTempAverage(C.tempAverage());
	setDivergence(C.divergence());
        setPsiGrad(C.PsiGrad());

	return;
	
}

/*
______________________________________________________________________________________________

	Returns true if the cell is inside the boundary
______________________________________________________________________________________________

*/

/**
 * @brief Returns true if the cell is inside the boundary
 * 
 * @return bool
 */
bool Cell::isInsideBoundary() const
{
	int ei = 1;
	int ej = (Dimension > 1) ? 1:0;
	int ek = (Dimension > 2) ? 1:0;

	int i, j, k;

	Vector Edge(Dimension);

	bool result=false;

	// Loop: if one edge of the cell is in the boundary, return true
	for (i=-ei; i <= ei; i+=2)
	for (j=-ej; j <= ej; j+=2)
	for (k=-ek; k <= ek; k+=2)
	{
		Edge.setValue(1,center(1) + i*0.5*size(1));

		if (Dimension > 1)
			Edge.setValue(2,center(2) + j*0.5*size(2));
		if (Dimension > 2)
			Edge.setValue(3,center(3) + k*0.5*size(3));

		if (BoundaryRegion(Edge) != 0) result = true;
	}

	return result;

}
/*
______________________________________________________________________________________________

	Returns true if the cell is inside the boundary
______________________________________________________________________________________________

*/

/**
 * brief Returns true if the cell is inside the boundary
 * 
 * return bool
 */
bool Cell::isInFluid() const
{
	return (!isInsideBoundary());
}
