
/***************************************************************************
                          InitResistivity.cpp  -  description
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
 /** @file InitResistivity.cpp
  * @brief Fill the magnetic resistivity parameter \eta(x,y,z)
  */
#include "Carmen.h"

real InitResistivity(real x, real y, real z)
{
	// --- Local variables ---

	real Result=0.;
    real Res = 0.;
	#include "carmen.res"

	Result = Res;

	return Result;
}
