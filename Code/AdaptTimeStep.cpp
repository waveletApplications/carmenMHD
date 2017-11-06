/***************************************************************************
                          AdaptTimeStep.cpp  -  description
                             -------------------
    begin                : jeu mar 25 2004
    copyright            : (C) 2004 by Olivier Roussel and Alexei Tsigulin
    email                : roussel@ict.uni-karlsruhe.de; lpsoft@mail.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

 /** @file AdaptTimeStep.cpp
  * @brief This function computes the time step for the next iteration.
  */

#include "Carmen.h"

void AdaptTimeStep()
{
	int 	RemainingIterations;
	real 	RemainingTime;


	// Security : do nothing if ConstantTimeStep is true

	if (ConstantTimeStep)
		return;

	// Compute remaining time

	RemainingTime = PhysicalTime-ElapsedTime;


    // In this case, use time adaptivity based on CFL
    if(Resistivity)
        TimeStep = CFL*min(SpaceStep/Eigenvalue,SpaceStep*SpaceStep/(4.*eta));
    else
        TimeStep = CFL*SpaceStep/Eigenvalue;

	// Recompute IterationNb

	if (RemainingTime <= 0.)
	{
		IterationNb = IterationNo;
	}
	else if (RemainingTime < TimeStep)
	{
		TimeStep = RemainingTime;
		IterationNb = IterationNo + 1;
	}
	else
	{
		RemainingIterations =  (int)(RemainingTime/TimeStep);
		IterationNb = IterationNo + RemainingIterations;
	}

	return;

}
