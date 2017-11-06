/** @file SchemeHLL.cpp
  * @brief Computes the HLL Riemann solver
  * @author Anna Karina Fontes Gomes
  * @version 4.0
  * @date July-2016
  */

#include "Carmen.h"


Vector SchemeHLL(const Cell& Cell1,const Cell& Cell2,const Cell& Cell3,const Cell& Cell4, int AxisNo)
{

    // General variables

	Vector	LeftAverage(QuantityNb);	//
	Vector	RightAverage(QuantityNb);	// Conservative quantities
	Vector	Result(QuantityNb);		    // MHD numerical flux
	int aux=0;
    // Variables for the HLL scheme
    Vector  FL(QuantityNb), FR(QuantityNb); //Left and right physical fluxes
	Vector	VL(3), VR(3);	// Left and right velocities
	Vector	BL(3), BR(3);	// Left and right velocities
	real	rhoL=0., rhoR=0.;		// Left and right densities
	real	eL=0., eR=0.;			// Left and right energies
    real    preL=0., preR=0.;
    real    bkL=0., bkR=0.;
    real    aL=0., aR=0.;
    real    bL=0., bR=0.;
    real    cfL=0., cfR=0.;
    real    SL=0., SR=0.;
    real    dx=0.;
    dx = Cell2.size(AxisNo);
	real   r, Limit, LeftSlope = 0., RightSlope = 0.; // Left and right slopes
	int i;

//	--- Limiter function ---------------------------------------------------------

    for (i=1; i<=QuantityNb; i++)
	{
		// --- Compute left cell-average value ---

		if (Cell2.average(i) != Cell1.average(i))
		{
			RightSlope 	= Cell3.average(i)-Cell2.average(i);
			LeftSlope	= Cell2.average(i)-Cell1.average(i);
			r		    = RightSlope/LeftSlope;
			Limit 	    = Limiter(r);
			LeftAverage.setValue(i, Cell2.average(i) + 0.5*Limit*LeftSlope);
			aux = 1;
		}
		else
			LeftAverage.setValue(i, Cell2.average(i));

		// --- Compute right cell-average value ---

		if (Cell3.average(i) != Cell2.average(i))
		{
			RightSlope  = Cell4.average(i)-Cell3.average(i);
			LeftSlope	= Cell3.average(i)-Cell2.average(i);
			r		    = RightSlope/LeftSlope;
			Limit 	    = Limiter(r);
			RightAverage.setValue(i, Cell3.average(i) - 0.5*Limit*LeftSlope);
			aux = 1;
		}
		else
			RightAverage.setValue(i, Cell3.average(i));
	}


	// --- HLL scheme -------------------------------------------------------------

	// --- Conservative variables ---

	// Left and right densities
	rhoL = LeftAverage.value(1);
	rhoR = RightAverage.value(1);

	// Left and right momentum and magnetic field
	for (int i=1;i<=3;i++)
	{
		VL.setValue( i, LeftAverage.value(i+1));
		VR.setValue( i, RightAverage.value(i+1));
		BL.setValue( i, LeftAverage.value(i+6));
		BR.setValue( i, RightAverage.value(i+6));
	}

	// Left and right energies
	eL = LeftAverage.value(5);
	eR = RightAverage.value(5);

    // Left and right pressures
    preL = (Gamma -1.)*(eL - 0.5*(VL*VL)/rhoL - 0.5*(BL*BL));
    preR = (Gamma -1.)*(eR - 0.5*(VR*VR)/rhoR - 0.5*(BR*BR));

    // --- Magnetoacoustic waves calculations --

    bkL = power2(BL.value(AxisNo))/rhoL;
    bkR = power2(BR.value(AxisNo))/rhoR;

    aL = Gamma*preL/rhoL;
    aR = Gamma*preR/rhoR;

    bL = (BL*BL)/rhoL;
    bR = (BR*BR)/rhoR;

    // Left and Right fast speeds
    cfL = sqrt(0.5*(aL + bL + sqrt(power2(aL + bL) - 4.0*aL*bkL)));
    cfR = sqrt(0.5*(aR + bR + sqrt(power2(aR + bR) - 4.0*aR*bkR)));

    // Left and right slopes
    SL = Min(Min(VL.value(AxisNo)/rhoL - cfL, VR.value(AxisNo)/rhoR - cfR),0.0);
    SR = Max(Max(VL.value(AxisNo)/rhoL + cfL, VR.value(AxisNo)/rhoR + cfR),0.0);

    // --- Physical flux ---
     if(AxisNo ==1){
        EigenvalueX = Max(Max(Abs(SL),Abs(SR)),EigenvalueX);
        FL = FluxX(LeftAverage);
        FR = FluxX(RightAverage);
     }else if(AxisNo ==2){
        EigenvalueY = Max(Max(Abs(SL),Abs(SR)),EigenvalueY);
        FL = FluxY(LeftAverage);
        FR = FluxY(RightAverage);
    }else{
        EigenvalueZ = Max(Max(Abs(SL),Abs(SR)),EigenvalueZ);
        FL = FluxZ(LeftAverage);
        FR = FluxZ(RightAverage);
    }


    // --- HLL Riemann Solver ---

    for(int i=1;i<=QuantityNb;i++)
    {
        Result.setValue(i, (SR*FL.value(i) - SL*FR.value(i) + SR*SL*(RightAverage.value(i) - LeftAverage.value(i)))/(SR-SL));
    }

    // Parabolic-Hyperbolic divergence Cleaning (Dedner, 2002)
    fluxCorrection(Result, LeftAverage, RightAverage, AxisNo);

    // Artificial diffusion terms
    if(Diffusivity && aux==1) Result = Result - ArtificialViscosity(LeftAverage,RightAverage,dx,AxisNo);

    return Result;

}
