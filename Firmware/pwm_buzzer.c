#include "depp.h"

void    pwm_buzzer(u8 note)
{
    OC4RS = note;
    BUZZER_ON;
}