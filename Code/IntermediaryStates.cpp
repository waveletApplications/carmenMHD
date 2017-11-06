// -*- C++ -*-

/** @file IntermediatyStates.cpp
  * @brief Computes the intermediary HLLD states to evaluate the Riemann Solver
  * @author Anna Karina Fontes Gomes
  * @version 2.0
  * @date 2014
  */

#include "Carmen.h"

Matrix stateUstar(const Vector& AvgL, const Vector& AvgR, const real prel, const real prer, real& slopeLeft, real& slopeRight,real& slopeM, real& slopeLeftStar, real& slopeRightStar, int AxisNo)
{
	real rhol=0.,rhor=0.;
	real psil=0.,psir=0.;
	real vxl=0.,vxr=0.,vyl=0.,vyr=0.,vzl=0.,vzr=0.;
	real Bxr=0.,Bxl=0.,Byl=0.,Byr=0.,Bzl=0.,Bzr=0.;
	real vl=0.,vr=0.,mf=0.;
	real Bl=0.,Br=0.;
	real pTl=0.,pTr=0.;
	real vBl=0.,vBr=0.;
	real el=0., er=0.;
	real rhols=0.,rhors=0.;
	real vxls=0.,vxrs=0.,vyls=0.,vyrs=0.,vzls=0.,vzrs=0.;
	real Bxls=0.,Bxrs=0.,Byls=0.,Byrs=0.,Bzls=0.,Bzrs=0.;
	real pTs=0.;
	real vBls=0.,vBrs=0.;
	real Els=0.,Ers=0.;
	real rholss=0.,rhorss=0.;
	real vxlss=0.,vxrss=0.,vylss=0.,vyrss=0.,vzlss=0.,vzrss=0.;
	real Bxlss=0.,Bxrss=0.,Bylss=0.,Byrss=0.,Bzlss=0.,Bzrss=0.;
	real vBlss=0.,vBrss=0.;
	real Elss=0.,Erss=0.;
	int Bsign=0;
	real half=0.5;
    real epsilon2=1e-16;
    real auxl=0.,auxr=0., Sqrtrhols=0.;

    Matrix U(QuantityNb,4);

    //Variables
    rhol = AvgL.value(1);
    vxl  = AvgL.value(2)/rhol;
    vyl  = AvgL.value(3)/rhol;
    vzl  = AvgL.value(4)/rhol;
    el   = AvgL.value(5);
    psil = AvgL.value(6);
    Bxl  = AvgL.value(7);
    Byl  = AvgL.value(8);
    Bzl  = AvgL.value(9);

    rhor = AvgR.value(1);
    vxr  = AvgR.value(2)/rhor;
    vyr  = AvgR.value(3)/rhor;
    vzr  = AvgR.value(4)/rhor;
    er   = AvgR.value(5);
    psir = AvgR.value(6);
    Bxr  = AvgR.value(7);
    Byr  = AvgR.value(8);
    Bzr  = AvgR.value(9);

    //v_x and v_y
	vl = AvgL.value(AxisNo+1)/rhol;
    vr = AvgR.value(AxisNo+1)/rhor;

	// Average B value
	mf = (AvgL.value(AxisNo+6)+AvgR.value(AxisNo+6))/(double (2.0));

		if(AxisNo==1)
		{
		    //|B|
            Bl = sqrt( mf*mf + Byl*Byl + Bzl*Bzl );
            Br = sqrt( mf*mf + Byr*Byr + Bzr*Bzr );
                //Inner product v.B
            vBl = vxl*mf + vyl*Byl + vzl*Bzl;
            vBr = vxr*mf + vyr*Byr + vzr*Bzr;
		}else if(AxisNo==2){
		    //|B|
            Bl = sqrt( Bxl*Bxl + mf*mf + Bzl*Bzl );
            Br = sqrt( Bxr*Bxr + mf*mf + Bzr*Bzr );
                //Inner product v.B
            vBl = vxl*Bxl + vyl*mf + vzl*Bzl;
            vBr = vxr*Bxr + vyr*mf + vzr*Bzr;
		}else{
		    //|B|
            Bl = sqrt( Bxl*Bxl + Byl*Byl + mf*mf );
            Br = sqrt( Bxr*Bxr + Byr*Byr + mf*mf );
                //Inner product v.B
            vBl = vxl*Bxl + vyl*Byl + vzl*mf;
            vBr = vxr*Bxr + vyr*Byr + vzr*mf;
		}

    //Total Pressure
	pTl = prel + half*Bl*Bl;
	pTr = prer + half*Br*Br;

    // S_M - Equation 38
	slopeM = ((slopeRight - vr)*rhor*vr - (slopeLeft - vl)*rhol*vl - pTr +pTl)/
             ((slopeRight - vr)*rhor    - (slopeLeft - vl)*rhol);

    //Sign function
	if(mf > 0)	Bsign =  1;
	else		Bsign = -1;

		//!variables U-star

			//density - Equation 43
			rhols = rhol*(slopeLeft-vl)/(slopeLeft-slopeM);
			rhors = rhor*(slopeRight-vr)/(slopeRight-slopeM);

			if(AxisNo==1){
				//velocities
				//Equation 39
				vxls = slopeM;
				vxrs = vxls;
				//B_x
				Bxls = mf;
				Bxrs = Bxls;

                auxl= (rhol*(slopeLeft  - vl)*(slopeLeft  - slopeM)-mf*mf);
                auxr= (rhor*(slopeRight - vr)*(slopeRight - slopeM)-mf*mf);

                    if( fabs(auxl)<epsilon2 ||
                    ( ( ( fabs(slopeM -vl) ) < epsilon2 )   &&
                    ( ( fabs(Byl) + fabs(Bzl) ) < epsilon2 )  &&
                    ( ( mf*mf ) >  (Gamma*prel) ) ) ) {
						vyls = vyl;
						vzls = vzl;
						Byls = Byl;
						Bzls = Bzl;
					}else{
						//Equation 44
						vyls = vyl - mf*Byl*(slopeM-vl)/auxl;
						//Equation 46
						vzls = vzl - mf*Bzl*(slopeM-vl)/auxl;
						//Equation 45
						Byls = Byl*(rhol*(slopeLeft-vl)*(slopeLeft-vl) - mf*mf)/auxl;
						//Equation 47
						Bzls = Bzl*(rhol*(slopeLeft-vl)*(slopeLeft-vl) - mf*mf)/auxl;
					}
                    if( fabs(auxr)<epsilon2 ||
                    ( ( ( fabs(slopeM -vr) ) < epsilon2 )   &&
                    ( ( fabs(Byr) + fabs(Bzr) ) < epsilon2 )  &&
                    ( ( mf*mf ) >  (Gamma*prer) ) ) ) {
						vyrs = vyr;
						vzrs = vzr;
						Byrs = Byr;
						Bzrs = Bzr;
					}else{
						//Equation 44
						vyrs = vyr - mf*Byr*(slopeM-vr)/auxr;
						//Equation 46
						vzrs = vzr - mf*Bzr*(slopeM-vr)/auxr;
						//Equation 45;
						Byrs = Byr*(rhor*(slopeRight-vr)*(slopeRight-vr) - mf*mf)/auxr;
						//Equation 47
						Bzrs = Bzr*(rhor*(slopeRight-vr)*(slopeRight-vr) - mf*mf)/auxr;
					}

			}else if(AxisNo==2){
				//velocities
				//Equation 39
				vyls = slopeM;
				vyrs = vyls;
				//B_y
				Byls = mf;
				Byrs = Byls;

                auxl= (rhol*(slopeLeft  - vl)*(slopeLeft  - slopeM)-mf*mf);
                auxr= (rhor*(slopeRight - vr)*(slopeRight - slopeM)-mf*mf);

                if( fabs(auxl)<epsilon2 ||
                    ( ( ( fabs(slopeM -vl) ) < epsilon2 )   &&
                    ( ( fabs(Bxl) + fabs(Bzl) ) < epsilon2 )  &&
                    ( ( mf*mf ) >  (Gamma*prel) ) ) ) {
					vxls = vxl;
					vzls = vzl;
					Bxls = Bxl;
					Bzls = Bzl;
				}else{
					//Equation 44
					vxls = vxl - mf*Bxl*(slopeM-vl)/auxl;
					//Equation 46
					vzls = vzl - mf*Bzl*(slopeM-vl)/auxl;
					//Equation 45
					Bxls = Bxl*(rhol*(slopeLeft-vl)*(slopeLeft-vl) - mf*mf)/auxl;
					//Equation 47
					Bzls = Bzl*(rhol*(slopeLeft-vl)*(slopeLeft-vl) - mf*mf)/auxl;
                }

                if( fabs(auxr)<epsilon2 ||
                    ( ( ( fabs(slopeM -vr) ) < epsilon2 )   &&
                    ( ( fabs(Bxr) + fabs(Bzr) ) < epsilon2 )  &&
                    ( ( mf*mf ) >  (Gamma*prer) ) ) ) {
					vxrs = vxr;
					vzrs = vzr;
					Bxrs = Bxr;
					Bzrs = Bzr;
				}else{
					//Equation 44
					vxrs = vxr - mf*Bxr*(slopeM-vr)/auxr;
					//Equation 46
					vzrs = vzr - mf*Bzr*(slopeM-vr)/auxr;
					//Equation 45
					Bxrs = Bxr*(rhor*(slopeRight-vr)*(slopeRight-vr) - mf*mf)/auxr;
					//Equation 47
					Bzrs = Bzr*(rhor*(slopeRight-vr)*(slopeRight-vr) - mf*mf)/auxr;
				}
			}else{
				//velocities
				//Equation 39
				vzls = slopeM;
				vzrs = vzls;
				//B_z
				Bzls = mf;
				Bzrs = Bzls;

                auxl= (rhol*(slopeLeft  - vl)*(slopeLeft  - slopeM)-mf*mf);
                auxr= (rhor*(slopeRight - vr)*(slopeRight - slopeM)-mf*mf);

                if( fabs(auxl)<epsilon2 ||
                    ( ( ( fabs(slopeM -vl) ) < epsilon2 )   &&
                    ( ( fabs(Bxl) + fabs(Byl) ) < epsilon2 )  &&
                    ( ( mf*mf ) >  (Gamma*prel) ) ) ) {
					vxls = vxl;
					vyls = vyl;
					Bxls = Bxl;
					Byls = Byl;
				}else{
					//Equation 44
					vxls = vxl - mf*Bxl*(slopeM-vl)/auxl;
					//Equation 46
					vyls = vyl - mf*Byl*(slopeM-vl)/auxl;
					//Equation 45
					Bxls = Bxl*(rhol*(slopeLeft-vl)*(slopeLeft-vl) - mf*mf)/auxl;
					//Equation 47
					Byls = Byl*(rhol*(slopeLeft-vl)*(slopeLeft-vl) - mf*mf)/auxl;
                }

                if( fabs(auxr)<epsilon2 ||
                    ( ( ( fabs(slopeM -vr) ) < epsilon2 )   &&
                    ( ( fabs(Bxr) + fabs(Byr) ) < epsilon2 )  &&
                    ( ( mf*mf ) >  (Gamma*prer) ) ) ) {
					vxrs = vxr;
					vyrs = vyr;
					Bxrs = Bxr;
					Byrs = Byr;
				}else{
					//Equation 44
					vxrs = vxr - mf*Bxr*(slopeM-vr)/auxr;
					//Equation 46
					vyrs = vyr - mf*Byr*(slopeM-vr)/auxr;
					//Equation 45
					Bxrs = Bxr*(rhor*(slopeRight-vr)*(slopeRight-vr) - mf*mf)/auxr;
					//Equation 47
					Byrs = Byr*(rhor*(slopeRight-vr)*(slopeRight-vr) - mf*mf)/auxr;
				}
			}

			//total pressure - Equation 41
			pTs = pTl + rhol*(slopeLeft - vl)*(slopeM - vl);

			//inner product vs*Bs
			vBls = vxls*Bxls + vyls*Byls + vzls*Bzls;
			vBrs = vxrs*Bxrs + vyrs*Byrs + vzrs*Bzrs;

			//energy - Equation 48
			Els = ((slopeLeft -vl)*el - pTl*vl+pTs*slopeM+mf*(vBl - vBls))/(slopeLeft  - slopeM);
			Ers = ((slopeRight-vr)*er - pTr*vr+pTs*slopeM+mf*(vBr - vBrs))/(slopeRight - slopeM);

			//U-star variables
			//Left
			U.setValue(1,1,rhols);
			U.setValue(2,1,rhols*vxls);
			U.setValue(3,1,rhols*vyls);
			U.setValue(4,1,rhols*vzls);
			U.setValue(5,1,Els);
			U.setValue(6,1,psil);
			U.setValue(7,1,Bxls);
			U.setValue(8,1,Byls);
			U.setValue(9,1,Bzls);
			//Right
			U.setValue(1,2,rhors);
			U.setValue(2,2,rhors*vxrs);
			U.setValue(3,2,rhors*vyrs);
			U.setValue(4,2,rhors*vzrs);
			U.setValue(5,2,Ers);
			U.setValue(6,2,psir);
			U.setValue(7,2,Bxrs);
			U.setValue(8,2,Byrs);
			U.setValue(9,2,Bzrs);


		//!variables U-star-star


            Sqrtrhols = (sqrt(rhols)+sqrt(rhors));

            if((mf*mf/min((Bl*Bl),(Br*Br))) < epsilon2){
			for(int k=1;k<=QuantityNb;k++){
				    U.setValue(k,3, U.value(k,1));
				    U.setValue(k,4, U.value(k,2));
				}
			}else{
			    //density - Equation 49
                rholss = rhols;
                rhorss = rhors;

				if(AxisNo==1){
                    //velocities
					//Equation 39
					vxlss = slopeM;
					vxrss = slopeM;
					//Equation 59
					vylss = (sqrt(rhols)*vyls + sqrt(rhors)*vyrs + (Byrs - Byls)*Bsign)/Sqrtrhols;
					vyrss = vylss;
					//Equation 60
                    vzlss = (sqrt(rhols)*vzls + sqrt(rhors)*vzrs + (Bzrs - Bzls)*Bsign)/Sqrtrhols;
                    vzrss = vzlss;

					//Magnetic Field components
					//B_x
					Bxlss = mf;
					Bxrss = mf;
					//Equation 61
                    Bylss = (sqrt(rhols)*Byrs + sqrt(rhors)*Byls + sqrt(rhols*rhors)*(vyrs - vyls)*Bsign)/Sqrtrhols;
					Byrss = Bylss;
                    //Equation 62
                    Bzlss = (sqrt(rhols)*Bzrs + sqrt(rhors)*Bzls + sqrt(rhols*rhors)*(vzrs - vzls)*Bsign)/Sqrtrhols;
                    Bzrss = Bzlss;
				}
				else if(AxisNo==2){
					//velocities
					//Equation 59
					vxlss = (sqrt(rhols)*vxls + sqrt(rhors)*vxrs + (Bxrs - Bxls)*Bsign)/Sqrtrhols;
					vxrss = vxlss;
					//Equation 39
					vylss = slopeM;
					vyrss = slopeM;
					//Equation 60
                    vzlss = (sqrt(rhols)*vzls + sqrt(rhors)*vzrs + (Bzrs - Bzls)*Bsign)/Sqrtrhols;
                    vzrss = vzlss;

					//Magnetic Field components
					//Equation 61
					Bxlss = (sqrt(rhols)*Bxrs + sqrt(rhors)*Bxls + sqrt(rhols*rhors)*(vxrs - vxls)*Bsign)/Sqrtrhols;
					Bxrss = Bxlss;
					//B_y
					Bylss = mf;
					Byrss = mf;
                    //Equation 62
                    Bzlss = (sqrt(rhols)*Bzrs + sqrt(rhors)*Bzls + sqrt(rhols*rhors)*(vzrs - vzls)*Bsign)/Sqrtrhols;
                    Bzrss = Bzlss;

				}else{
					//velocities
					//Equation 59
					vxlss = (sqrt(rhols)*vxls + sqrt(rhors)*vxrs + (Bxrs - Bxls)*Bsign)/Sqrtrhols;
					vxrss = vxlss;
					//Equation 60
                    vylss = (sqrt(rhols)*vyls + sqrt(rhors)*vyrs + (Byrs - Byls)*Bsign)/Sqrtrhols;
					vyrss = vylss;
					//Equation 39
					vzlss = slopeM;
					vzrss = slopeM;

					//Magnetic Field components
					//Equation 61
					Bxlss = (sqrt(rhols)*Bxrs + sqrt(rhors)*Bxls + sqrt(rhols*rhors)*(vxrs - vxls)*Bsign)/Sqrtrhols;
					Bxrss = Bxlss;
					//Equation 62
                    Bylss = (sqrt(rhols)*Byrs + sqrt(rhors)*Byls + sqrt(rhols*rhors)*(vyrs - vyls)*Bsign)/Sqrtrhols;
					Byrss = Bylss;
					//B_y
					Bzlss = mf;
					Bzrss = mf;

				}


                //inner product vss*Bss
                vBlss = vxlss*Bxlss + vylss*Bylss + vzlss*Bzlss;
                vBrss = vxrss*Bxrss + vyrss*Byrss + vzrss*Bzrss;

                //Energy - Equation 63
                Elss = Els - sqrt(rhols)*(vBls - vBlss)*Bsign;
                Erss = Ers + sqrt(rhors)*(vBrs - vBrss)*Bsign;




				//U-star-star variables
				//Left
				U.setValue(1,3,rholss);
				U.setValue(2,3,rholss*vxlss);
				U.setValue(3,3,rholss*vylss);
				U.setValue(4,3,rholss*vzlss);
				U.setValue(5,3,Elss);
				U.setValue(6,3,psil);
				U.setValue(7,3,Bxlss);
				U.setValue(8,3,Bylss);
				U.setValue(9,3,Bzlss);
				//Right
				U.setValue(1,4,rhorss);
				U.setValue(2,4,rhorss*vxrss);
				U.setValue(3,4,rhorss*vyrss);
				U.setValue(4,4,rhorss*vzrss);
				U.setValue(5,4,Erss);
				U.setValue(6,4,psir);
				U.setValue(7,4,Bxrss);
				U.setValue(8,4,Byrss);
				U.setValue(9,4,Bzrss);
			}
			//Equation 61 - S-star left and S-star right
			slopeLeftStar  = slopeM - Abs(mf)/sqrt(rhols);
			slopeRightStar = slopeM + Abs(mf)/sqrt(rhors);

    return U;
}
