#include "depp.h"

void    pwm_led(u8 r, u8 g, u8 b)
{
    OC1RS = r;
    OC2RS = b;
    OC3RS = g;
}