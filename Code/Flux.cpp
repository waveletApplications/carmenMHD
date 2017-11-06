/***************************************************************************
                          Flux.cpp  -  description
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
/** @file Flux.cpp
  * @brief Computes the numerical fluxes HLL and HLLD
  */
#include "Carmen.h"

Vector Flux(Cell& Cell1, Cell& Cell2, Cell& Cell3, Cell& Cell4, int AxisNo)
{
	// --- Local variables ---

	Vector Result(QuantityNb);

	Cell C1, C2, C3, C4;

    int BoundaryCell1 = BoundaryRegion(Cell1.center());
  	int BoundaryCell2 = BoundaryRegion(Cell2.center());
  	int BoundaryCell3 = BoundaryRegion(Cell3.center());
  	int BoundaryCell4 = BoundaryRegion(Cell4.center());

    bool UseBoundaryCells = (UseBoundaryRegions && (BoundaryCell1!=0 || BoundaryCell2!=0 || BoundaryCell3!=0 || BoundaryCell4!=0));
    
    // --- Take into account boundary conditions ---

			if (UseBoundaryCells)
				GetBoundaryCells(Cell1, Cell2, Cell3, Cell4, C1, C2, C3, C4, AxisNo);

    switch(SchemeNb)
    {
        case 1:
        default:
			if (UseBoundaryCells)
				Result = SchemeHLL(C1, C2, C3, C4, AxisNo);
			else
            	Result = SchemeHLL(Cell1, Cell2, Cell3, Cell4, AxisNo);
        	break;

        case 2:
			if (UseBoundaryCells)
				Result = SchemeHLLD(C1, C2, C3, C4, AxisNo);
			else
            	Result = SchemeHLLD(Cell1, Cell2, Cell3, Cell4, AxisNo);
        	break;
        break;

    }


	return Result;
}
