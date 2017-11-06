/** @file PhysicalFluxMHD.cpp
  * @brief Computes the MHD physical flux
  * @author Anna Karina Fontes Gomes
  * @version 2.0
  */
#include "Carmen.h"

Vector FluxX(const Vector& Avg)
{
    real rho;
    real vx, vy, vz;
    real pre, e;
    real Bx, By, Bz;
    real Bx2, By2, Bz2, B2;
    real vx2, vy2, vz2, v2;
    real half = 0.5;
    Vector F(QuantityNb);

    //Variables
    rho = Avg.value(1);
    vx  = Avg.value(2)/rho;
    vy  = Avg.value(3)/rho;
    vz  = Avg.value(4)/rho;
    e   = Avg.value(5);
    Bx  = Avg.value(7);
    By  = Avg.value(8);
    Bz  = Avg.value(9);

    Bx2 = Bx*Bx;
    By2 = By*By;
    Bz2 = Bz*Bz;
    B2  = half*(Bz2+Bx2+By2);

    vx2 = vx*vx;
    vy2 = vy*vy;
    vz2 = vz*vz;
    v2  = half*(vz2+vx2+vy2);

    //pressure
	pre = (Gamma -1.)*(e - rho*v2 - B2);

    //Physical flux - x-direction
    F.setValue(1,rho*vx);
    F.setValue(2,rho*vx2 + pre + half*(Bz2+By2-Bx2));
    F.setValue(3,rho*vx*vy - Bx*By);
    F.setValue(4,rho*vx*vz - Bx*Bz);
    F.setValue(5,(e + pre + B2)*vx - Bx*(vx*Bx + vy*By + vz*Bz) );
    F.setValue(6,0.0);
    F.setValue(7,0.0);
    F.setValue(8,vx*By - vy*Bx);
    F.setValue(9,vx*Bz - vz*Bx);


    return F;
}


Vector FluxY(const Vector& Avg)
{
    real rho;
    real vx, vy, vz;
    real pre, e;
    real Bx, By, Bz;
    real Bx2, By2, Bz2, B2;
    real vx2, vy2, vz2, v2;
    real half = 0.5;

    Vector G(QuantityNb);

    //Variables
    rho = Avg.value(1);
    vx  = Avg.value(2)/rho;
    vy  = Avg.value(3)/rho;
    vz  = Avg.value(4)/rho;
    e   = Avg.value(5);
    Bx  = Avg.value(7);
    By  = Avg.value(8);
    Bz  = Avg.value(9);

    Bx2 = Bx*Bx;
    By2 = By*By;
    Bz2 = Bz*Bz;
    B2  = half*(Bz2+Bx2+By2);

    vx2 = vx*vx;
    vy2 = vy*vy;
    vz2 = vz*vz;
    v2  = half*(vz2+vx2+vy2);

    //pressure
	pre = (Gamma -1.)*(e - rho*v2 - B2);

    //Physical flux - y-direction
    G.setValue(1,rho*vy);
    G.setValue(2,rho*vx*vy - Bx*By);
    G.setValue(3,rho*vy2 + pre + half*(Bx2+Bz2-By2));
    G.setValue(4,rho*vy*vz - By*Bz);
    G.setValue(5,(e + pre + B2)*vy - By*(vx*Bx + vy*By + vz*Bz));
    G.setValue(6,0.0);
    G.setValue(7,vy*Bx - vx*By);
    G.setValue(8,0.0);
    G.setValue(9,vy*Bz - vz*By);
    return G;
}

Vector FluxZ(const Vector& Avg)
{
    real rho;
    real vx, vy, vz;
    real pre, e;
    real Bx, By, Bz;
    real Bx2, By2, Bz2, B2;
    real vx2, vy2, vz2, v2;
    real half = 0.5;

    Vector H(QuantityNb);

    //Variables
    rho = Avg.value(1);
    vx  = Avg.value(2)/rho;
    vy  = Avg.value(3)/rho;
    vz  = Avg.value(4)/rho;
    e   = Avg.value(5);
    Bx  = Avg.value(7);
    By  = Avg.value(8);
    Bz  = Avg.value(9);

    Bx2 = Bx*Bx;
    By2 = By*By;
    Bz2 = Bz*Bz;
    B2  = half*(Bz2+Bx2+By2);

    vx2 = vx*vx;
    vy2 = vy*vy;
    vz2 = vz*vz;
    v2  = half*(vz2+vx2+vy2);

    //pressure
	pre = (Gamma -1.)*(e - rho*v2 - B2);

    //Physical flux - y-direction
    H.setValue(1,rho*vz);
    H.setValue(2,rho*vz*vx - Bz*Bx);
    H.setValue(3,rho*vz*vy - Bz*By);
    H.setValue(4,rho*vz2 + pre + half*(Bx2+By2-Bz2));
    H.setValue(5,(e + pre + B2)*vz - Bz*(vx*Bx + vy*By + vz*Bz));
    H.setValue(6,0.0);
    H.setValue(7,vz*Bx - vx*Bz);
    H.setValue(8,vz*By - vy*Bz);
    H.setValue(9,0.0);

    return H;
}
