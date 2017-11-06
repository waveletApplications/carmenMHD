/***************************************************************************
                          ComputedTolerance.cpp  -  description
                             -------------------
    begin                : May 13 2011 changed by Kai, Sonia, Margarete
    copyright            : (C) 2005 by Olivier Roussel
    email                : roussel@ict.uni-karlsruhe.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/** @file ComputedTolerance.cpp
  * @brief Adapt trheshold parameter or use it fixed
  */
#include "Carmen.h"

real ComputedTolerance(const int ScaleNo)
{
//if ThresholdNorm==0 const Tolerance, else L1 Harten norm

    if(ThresholdNorm)
        return((Tolerance/GlobalVolume)*exp(Dimension*(ScaleNo-ScaleNb+1)*log(2.)));
    else
        return(Tolerance);

}
