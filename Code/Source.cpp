/***************************************************************************
                          Source.cpp  -  description
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
  /** @file Source.cpp
  * @brief Computes the source terms of the system
  */

#include "Carmen.h"

Vector Source(Cell& UserCell)
{
	// ---  Local variables ---

	Vector Force(Dimension);
    Vector Result(QuantityNb);
    Result.setZero();

    //! Gravity vector
    Vector V(3);
    real Gx=0., Gy=0., Gz=0.,rho=0.;
    for(int i=1;i<=3;i++)
        V.setValue(i,UserCell.average(i+1));
    rho = UserCell.density();
    Gz = 0.2;
    Result.setValue(2,rho*Gx);
    Result.setValue(3,rho*Gy);
    Result.setValue(4,rho*Gz);
    Result.setValue(5,rho*(Gx*V.value(1) + Gy*V.value(2) + Gz*V.value(3)));

    Result.setZero();
	return Result;

}
