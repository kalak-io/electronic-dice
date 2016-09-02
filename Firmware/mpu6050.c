#include "mpu6050.h"
#include "types.h"
#include <math.h>
#include "depp.h"

#define ABS(x) (x<0)?-x:x

s16 vx = 0;
s16 vy = 0;
s16 vz = 0;
s16 rx = 0;
s16 ry = 0;
s16 rz = 0;
s16 temp = 0;
s16 thr = 0;
s16 difvx = 0;
s16 difvy = 0;
s16 difvz = 0;
s16 difrx = 0;
s16 difry = 0;
s16 difrz = 0;

void    MPUinit(u16 nthr, u8 div)
{
    thr = nthr;
    I2Cset8(MPU_PWR_MGMT_1, 0x00);      // disable sleep
    I2Cset8(MPU_SMPRT_DIV, div);        // set sample div
    I2Cset8(MPU_GYRO_CONFIG, 0);        // set gyro scale:
                                    // [0 => 250, 1 => 500, 2 => 1000, 3 =>2000]

    I2Cset8(MPU_ACCEL_CONFIG, 0);       // set accel scale:
                                    // [0 => 2g, 1 => 4g, 2 => 8g, 3 => 16g]



    //interruptions
    //
    I2Cset8(MPU_MOT_THR, thr);          // set threshold interrupt
    I2Cset8(MPU_MOT_DETECT_CTRL, 0x10);
    I2Cset8(MPU_INT_ENABLE, 0x41);
    I2Cset8(MPU_INT_PIN_CFG, 0x30);
    //
}

u8    MPUgetdata()
{
    s16 nvx = 0;
    s16 nvy = 0;
    s16 nvz = 0;
    s16 nrx = 0;
    s16 nry = 0;
    s16 nrz = 0;
    s16 ntemp = 0;

    I2Csendstart();             // bit de start
    sendI2Cadress(0);           // envoi adresse du 6 axis mode write

    sendI2C(MPU_ACCEL_XOUT_H);            // envoi adresse du registre

    I2Csendrestart();           // bit de restart
    sendI2Cadress(1);           // envoi adresse de 6 axis mode read

    nvx = readI2C() << 8;      // lecture du registre
    I2Cack(0);                  // ack
    nvx += readI2C();          // lecture du registre
    I2Cack(0);                  // ack

    nvy = readI2C() << 8;      // lecture du registre
    I2Cack(0);                  // ack
    nvy += readI2C();          // lecture du registre
    I2Cack(0);                  // ack

    nvz = readI2C() << 8;      // lecture du registre
    I2Cack(0);                  // ack
    nvz += readI2C();          // lecture du registre
    I2Cack(0);                  // ack

    ntemp = readI2C() << 8;      // lecture du registre
    I2Cack(0);                  // ack
    ntemp += readI2C();          // lecture du registre
    I2Cack(0);                  // ack

    nrx = readI2C() << 8;      // lecture du registre
    I2Cack(0);                  // ack
    nrx += readI2C();          // lecture du registre
    I2Cack(0);                  // ack

    nry = readI2C() << 8;      // lecture du registre
    I2Cack(0);                  // ack
    nry += readI2C();          // lecture du registre
    I2Cack(0);                  // ack

    nrz = readI2C() << 8;      // lecture du registre
    I2Cack(0);                  // ack
    nrz += readI2C();          // lecture du registre
    I2Cack(1);                  // ack
//    I2Csendstop();              // bit stop
    I2Cget8(MPU_INT_STATUS);

    difvx = vx - nvx;
    difvy = vy - nvy;
    difvz = vz - nvz;
    difrx = rx - nrx;
    difry = ry - nry;
    difrz = rz - nrz;

//    if (difvx > thr  || difvy > thr  /*|| difvz > thr*/
//     || difvx < -thr || difvy < -thr /*|| difvz < -thr
//     || difrx > thr  || difry > thr  || difrz > thr
//     || difrx < -thr || difry < -thr || difrz < -thr*/)
//    {
        vx = nvx;
        vy = nvy;
        vz = nvz;
        temp = ntemp;
        rx = nrx;
        ry = nry;
        rz = nrz;
        return 1;
//    }
//    return 0;
}

s16 getvx()
{
    return -vy;     //a cause de la position de l'accelero
}

s16 getvy()
{
    return -vx;     //a cause de la position de l'accelero
}

s16 getvz()
{
    return vz;
}

s16 getrx()
{
    return -rx;
}

s16 getry()
{
    return ry;
}

s16 getrz()
{
    return -rz;
}

s16 getthr()
{
    return thr;
}

s16 getdifvx()
{
    return difvx;
}

s16 getdifvy()
{
    return difvy;
}

s16 getdifvz()
{
    return difvz;
}

s16 getdifrx()
{
    return difrx;
}

s16 getdifry()
{
    return difry;
}

s16 getdifrz()
{
    return difrz;
}

#define ACCEL_SENS 8192.0
#define GYRO_SENS 65.536	    
 
#define dt 0.01							// 10 ms sample rate!

void    filter(s16 *x, s16 *y)
{
    float pitch;
    float roll;
    float pitchAcc;
    float rollAcc;
    int fma;
    
    pitch += (rx / GYRO_SENS) * dt;
    roll -= (ry / GYRO_SENS) * dt;
    
    fma = abs(vx) + abs(vy) + abs(vz);
    
    if (fma > ACCEL_SENS && fma < 32768)
    {
        pitchAcc = atan2f(vy, vz) * 180 / M_PI;
        pitch = pitch * 0.98 + pitchAcc * 0.02;
 
        rollAcc = atan2f(vx, vz) * 180 / M_PI;
        roll = roll * 0.98 + rollAcc * 0.02;
    }
    *x = (s16)(pitch * 40.0);
    *y = (s16)(roll * 40.0);
}

void    filterbis(s16 *x, s16 *y)
{
    static s16 tabx[5] = {0};
    static s16 taby[5] = {0};
    int       i = 0;
    s16     tmp;
    s32     myx;
    s32     myy;
    
    myx = 0;
    myy = 0;
    while (i < 4)
    {
        tmp = tabx[i];
        tabx[i] = tabx[i + 1];
        tabx[i + 1] = tmp;
        tmp = taby[i];
        taby[i] = taby[i + 1];
        taby[i + 1] = tmp;
        myx += tabx[i];
        myy += taby[i];
        i++;
    }
    tabx[4] = -rx;
    taby[4] = -rz - 200;
    myx += tabx[4];
    myy += tabx[4];
    *x = (s16)(myx / 500);
    *y = (s16)(myy / 300);
}

void    filterbibis(s16 *x, s16 *y)
{
    static s16 tabx[5] = {0};
    static s16 taby[5] = {0};
    int       i = 0;
    s16     tmp;
    s32     myx;
    s32     myy;
    
    myx = 0;
    myy = 0;
    while (i < 4)
    {
        tmp = tabx[i];
        tabx[i] = tabx[i + 1];
        tabx[i + 1] = tmp;
        tmp = taby[i];
        taby[i] = taby[i + 1];
        taby[i + 1] = tmp;
        myx += tabx[i];
        myy += taby[i];
        i++;
    }
    tabx[4] = -rz;
    taby[4] = -ry;
    myx += tabx[4];
    myy += tabx[4];
    *x = (s16)(myx / 1000);
    *y = (s16)(myy / 1000);
}