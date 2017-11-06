
/** @file ResistiveTerms.cpp
  * @brief This computes the resistive terms of energy and magnetic field Equations.
  * @author Anna Karina Fontes Gomes
  * @version 2.0
  * @date Sep-2016
  */

#include "Carmen.h"

Vector ResistiveTerms(Cell& Cell1, Cell& Cell2, Cell& Cell3, Cell& Cell4, int AxisNo)
{
	// ---  Local variables ---
    Vector  B(3), Bi(3), Bj(3), Bk(3);
    Vector  Result(QuantityNb);
    Vector  Bavg(3);
    real    Jx = 0., Jy = 0., Jz = 0.;
    real    dx, dy, dz;
    real    ResX= 0., ResY= 0., ResZ= 0., ResE= 0.;
    real    eta0=0., etai=0., etaj=0., etak=0., etaR=0.;
    
    eta = 0.;
    
    dx = Cell2.size(1);
    dy = Cell2.size(2);
    dz = Cell2.size(3);

    eta0 = Cell1.Res;
    etai = Cell2.Res;
    etaj = Cell3.Res;
    etak = Cell4.Res;

    for(int i=1; i <= 3; i++){
        B.setValue (i, Cell1.average(i+6));
        Bi.setValue(i, Cell2.average(i+6));
        Bj.setValue(i, Cell3.average(i+6));
        Bk.setValue(i, Cell4.average(i+6));
    }


    if(AxisNo == 1){
        //! X - direction
        etaR = (eta0 + etai)/2.;

        Bavg.setValue(2, 0.5*(B.value(2) + Bi.value(2)));
        Bavg.setValue(3, 0.5*(B.value(3) + Bi.value(3)));

        Jy = -(B.value(3) - Bi.value(3))/dx;
        Jz =  (B.value(2) - Bi.value(2))/dx;

        //! 2D
        Jz = Jz - (B.value(1) - Bj.value(1))/dy;

        if(Dimension==3){
            Jy   = Jy   + (B.value(1) - Bk.value(1))/dz;
        }

        ResE =  etaR*(Bavg.value(2)*Jz - Bavg.value(3)*Jy);
        ResX = 0.;
        ResY =  etaR*Jz;
        ResZ = -etaR*Jy;


    }else if(AxisNo == 2){
        //! Y - direction
        etaR = (eta0 + etaj)/2.;

        Bavg.setValue(1, 0.5*(B.value(1) + Bj.value(1)));
        Bavg.setValue(3, 0.5*(B.value(3) + Bj.value(3)));

        Jx =  (B.value(3) - Bj.value(3))/dy;
        Jz = -(B.value(1) - Bj.value(1))/dy;

        //! 2D
        Jz = Jz + (B.value(2) - Bi.value(2))/dx;

        if(Dimension==3){
            Jx   = Jx   - (B.value(2) - Bk.value(2))/dz;
        }

        ResE =  etaR*(Bavg.value(3)*Jx - Bavg.value(1)*Jz);
        ResX = -etaR*Jz;
        ResY = 0.;
        ResZ =  etaR*Jx;

    }else{
        //! Z - direction
        etaR = (eta0 + etak)/2.;

        Bavg.setValue(1, 0.5*(B.value(1) + Bk.value(1)));
        Bavg.setValue(2, 0.5*(B.value(2) + Bk.value(2)));

        Jx = -(B.value(2) - Bk.value(2))/dz;
        Jy =  (B.value(1) - Bk.value(1))/dz;

        //! 3D
        Jx = Jx + (B.value(3) - Bj.value(3))/dy;
        Jy = Jy - (B.value(3) - Bi.value(3))/dx;

        ResE =  etaR*(Bavg.value(1)*Jy - Bavg.value(2)*Jx);
        ResX =  etaR*Jy;
        ResY = -etaR*Jx;
        ResZ = 0.;
    }
    
    eta = max(eta,etaR);

    Result.setZero();

    // These values will be added to the numerical flux
    Result.setValue(5, ResE);
    Result.setValue(7, ResX);
    Result.setValue(8, ResY);
    Result.setValue(9, ResZ);

	return Result;

}

