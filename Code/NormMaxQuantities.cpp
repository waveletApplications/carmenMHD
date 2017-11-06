/***************************************************************************
                          NormMaxQuantities.cpp  -  description
                             -------------------
    begin                : ven jan 23 2004
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
/** @file NormMaxQuantities.cpp
  * @brief Compute the Linf norm of a vector containing the physical quantities divided by their characteristic value
    @author Anna Karina Fontes Gomes
    @date January-2017
  */
#include "Carmen.h"


real NormMaxQuantities(const Vector& V)
{
	Vector W(QuantityNb);
	int AxisNo=1;
	real MomentumMax=0.;
	real MagMax=0.;



    W.setZero();

/*
    // Density
    W.setValue(1, V.value(1)/QuantityMax.value(1));

    // Momentum
    W.setValue(2 , V.value(2)/QuantityMax.value(2) );
    W.setValue(3 , V.value(3)/QuantityMax.value(3) );
    W.setValue(4 , V.value(4)/QuantityMax.value(4) );

    // Energy
    W.setValue(5 , V.value(5)/QuantityMax.value(5) );

    // psi
   // W.setValue(6, V.value(6)/QuantityMax.value(6));

    // Magnetic Field
    W.setValue(7 , V.value(7)/QuantityMax.value(7) );
    W.setValue(8 , V.value(8)/QuantityMax.value(8) );
    W.setValue(9 , V.value(9)/QuantityMax.value(9) );
*/

  // --- Compute Linf norm --

	W.setValue(1, (V.value(1))/QuantityMax.value(1));
    W.setValue(5, (V.value(5))/QuantityMax.value(5));
    //W.setValue(6, (V.value(6))/QuantityMax.value(6));


    for (AxisNo = 1; AxisNo <= Dimension; AxisNo++)
    {
        MomentumMax = Max( MomentumMax, QuantityMax.value(AxisNo+1) );
        MagMax      = Max( MagMax,      QuantityMax.value(AxisNo+6) );
        W.setValue(2, W.value(2) + V.value(AxisNo+1)*V.value(AxisNo+1));
        W.setValue(7, W.value(7) + V.value(AxisNo+6)*V.value(AxisNo+6));
    }

	if(Dimension==2){
		W.setValue(4, (V.value(4))/QuantityMax.value(4));
		W.setValue(9, (V.value(9))/QuantityMax.value(9));
    }

	W.setValue(2, sqrt(W.value(2))/MomentumMax);
    W.setValue(7, sqrt(W.value(7))/MagMax );

    if(IterationNo==0)return NMax(V);
	return NMax(W);
}
