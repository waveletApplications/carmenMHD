/** @file ArtificialViscosity.cpp
  * @brief Computes the Laplacian terms for density, energy and momentum equations. It helps with the stability.
  * @author Anna Karina Fontes Gomes
  * @version 2.0
  * @date Oct-2016
  */


#include "Carmen.h"

Vector ArtificialViscosity(const Vector& Cell1, const Vector& Cell2, real dx, int AxisNo)
{
	// ---  Local variables ---
    Vector  ML(3), MR(3);
    Vector  Result(QuantityNb);
    real    EL,ER,RL,RR;
    real    viscR, viscX, viscY, viscZ, viscE;


    for(int i=1; i <= 3; i++){
        ML.setValue(i, Cell1.value(i+1));
        MR.setValue(i, Cell2.value(i+1));
    }

    RL = Cell1.value(1);
    RR = Cell2.value(1);
    EL = Cell1.value(5);
    ER = Cell2.value(5);


    if(AxisNo == 1){
        //! X - direction
        viscR = (RR - RL)/dx;
        viscE = (ER - EL)/dx;

        viscX = (MR.value(1) - ML.value(1))/dx;
        viscY = (MR.value(2) - ML.value(2))/dx;
        viscZ = (MR.value(3) - ML.value(3))/dx;


    }else if(AxisNo == 2){
        //! Y - direction
        viscR = (RR - RL)/dx;
        viscE = (ER - EL)/dx;

        viscX = (MR.value(1) - ML.value(1))/dx;
        viscY = (MR.value(2) - ML.value(2))/dx;
        viscZ = (MR.value(3) - ML.value(3))/dx;

    }else{
        //! Z - direction
        viscR = (RR - RL)/dx;
        viscE = (ER - EL)/dx;

        viscX = (MR.value(1) - ML.value(1))/dx;
        viscY = (MR.value(2) - ML.value(2))/dx;
        viscZ = (MR.value(3) - ML.value(3))/dx;

    }


    Result.setZero();

    // These values will be added to the numerical flux
    Result.setValue(1, chi*viscR);
    Result.setValue(2, chi*viscX);
    Result.setValue(3, chi*viscY);
    Result.setValue(4, chi*viscZ);
    Result.setValue(5, chi*viscE);

	return Result;

}

