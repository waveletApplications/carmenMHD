/** @file FluxCorrection.cpp
  * @brief Computes the mixed correction in the numerical fluxes (Dedner, 2002)
  * @author Anna Karina Fontes Gomes
  * @version 2.0
  */

#include "Carmen.h"

void fluxCorrection(Vector& Flux,const Vector& AvgL, const Vector& AvgR, int AxisNo)
{
    auxvar = Flux.value(AxisNo+6);

    Flux.setValue(AxisNo+6, Flux.value(AxisNo+6) + (AvgL.value(6) +    .5*(AvgR.value(6) - AvgL.value(6))
                                          - ch*.5*(AvgR.value(AxisNo+6) - AvgL.value(AxisNo+6))));

    Flux.setValue(6, ch*ch*(AvgL.value(AxisNo+6) + .5*(AvgR.value(AxisNo+6) - AvgL.value(AxisNo+6))
                                          - .5*(AvgR.value(6) - AvgL.value(6))/ch));

}


