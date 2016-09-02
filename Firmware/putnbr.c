#include "depp.h"

void    disp_off()
{
    LAT_OFF(B, 0);
    LAT_OFF(B, 1);
    LAT_OFF(C, 0);
    LAT_OFF(B, 3);
    LAT_OFF(B, 2);
    LAT_OFF(A, 1);
    LAT_OFF(A, 0);
    LAT_OFF(C, 1);
}

void    putnbr(u8 nb, u8 dp)
{
    disp_off();
    if (dp != 0)
        LAT_ON(C, 1);
    switch(nb)
    {
        case 0 :
            LAT_ON(B, 0);
            LAT_ON(B, 1);
            LAT_ON(C, 0);
            LAT_ON(B, 3);
            LAT_ON(B, 2);
            LAT_ON(A, 1);
        break;
        case 1 :
            LAT_ON(B, 1);
            LAT_ON(C, 0);
            break;
        case 2 :
            LAT_ON(B, 0);
            LAT_ON(B, 1);
            LAT_ON(A, 0);
            LAT_ON(B, 2);
            LAT_ON(B, 3);
            break;
        case 3 :
            LAT_ON(B, 0);
            LAT_ON(B, 1);
            LAT_ON(A, 0);
            LAT_ON(C, 0);
            LAT_ON(B, 3);
        break;
        case 4 :
            LAT_ON(A, 1);
            LAT_ON(A, 0);
            LAT_ON(B, 1);
            LAT_ON(C, 0);
        break;
        case 5 :
            LAT_ON(B, 0);
            LAT_ON(A, 1);
            LAT_ON(A, 0);
            LAT_ON(C, 0);
            LAT_ON(B, 3);
        break;
        case 6 :
            LAT_ON(B, 0);
            LAT_ON(A, 1);
            LAT_ON(A, 0);
            LAT_ON(C, 0);
            LAT_ON(B, 3);
            LAT_ON(B, 2);
        break;
        case 7 :
            LAT_ON(B, 0);
            LAT_ON(B, 1);
            LAT_ON(C, 0);
        break;
        case 8 :
            LAT_ON(B, 0);
            LAT_ON(B, 1);
            LAT_ON(C, 0);
            LAT_ON(B, 3);
            LAT_ON(B, 2);
            LAT_ON(A, 1);
            LAT_ON(A, 0);
        break;
        case 9 :
            LAT_ON(A, 1);
            LAT_ON(B, 0);
            LAT_ON(B, 1);
            LAT_ON(A, 0);
            LAT_ON(C, 0);
            LAT_ON(B, 3);
        break;
        default : LAT_ON(C, 1);
    }
}
