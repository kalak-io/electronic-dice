#include "depp.h"

void    init_pwm()
{
    //PR2 = pic frequency / pwm frequency - 1
    //8000000 / 50000 - 1 = 159
    OC1RS = 0;   
    OC2RS = 0;
    OC3RS = 0;

    PR2 = 255; 
    
    //RED
    OC1CON = 0x0;           //Turn off OCx when performing setup
    OC1R = 0;
    OC1CONbits.OCM = 0b110; //Primary Compare register

    //BLUE
    OC2CON = 0x0;           //Turn off OCx when performing setup
    OC2R = 0;
    OC2CONbits.OCM = 0b110; //Primary Compare register

    //GREEN
    OC3CON = 0x0;           //Turn off OCx when performing setup
    OC3R = 0;
    OC3CONbits.OCM = 0b110; //Primary Compare register

    //BUZZER
    /*OC4CON = 0x0;           //Turn off OCx when performing setup
    OC4R = 0;
    OC4CONbits.OCM = 0b110; //Primary Compare register*/
    
    T2CON = 0x40;           //prescale : 1/16
    T2CONSET = 0x8000;                  //Turn T2 ON
    OC1CONbits.ON = 1;                  //Turn OCx ON
    OC2CONbits.ON = 1;
    OC3CONbits.ON = 1;
    BUZZER_OFF;
}