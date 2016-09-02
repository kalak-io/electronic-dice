#include "depp.h"

void    init_bus_col()
{
    IEC1bits.I2C1BIE = 0;
    IFS1bits.I2C1BIF = 0;
    IPC8bits.I2C1IP = 7;
    IPC8bits.I2C1IS = 0;
    IEC1bits.I2C1BIE = 1;
}

void    init_int1()
{
    IEC0bits.INT1IE = 0;    //Disable interrupt while we configure it
    IFS0bits.INT1IF = 0;    //Clear the interrupt flag
    IPC1bits.INT1IP = 1;    //Set priority to 1
    IPC1bits.INT1IS = 3;    //Set subpriority to 0
    IEC0bits.INT1IE = 1;    //Enable interrupt
}

void    init_int2()
{
    ANSELCbits.ANSC3 = 0;   //Disable analogic on the pin
    IEC0bits.INT2IE = 0;    //Disable interrupt while we configure it
    IFS0bits.INT2IF = 0;    //Clear the interrupt flag
    IPC2bits.INT2IP = 2;    //Set priority to 1
    IPC2bits.INT2IS = 2;    //Set subpriority to 0
    IEC0bits.INT2IE = 1;    //Enable interrupt
}

void    init_int3()
{
    IEC0bits.INT3IE = 0;    //Disable interrupt while we configure it
    IFS0bits.INT3IF = 0;    //Clear the interrupt flag
    IPC3bits.INT3IP = 2;    //Set priority to 1
    IPC3bits.INT3IS = 0;    //Set subpriority to 0
    IEC0bits.INT3IE = 1;    //Enable interrupt
}

void    init_int4()
{
    IEC0bits.INT4IE = 0;    //Disable interrupt while we configure it
    IFS0bits.INT4IF = 0;    //Clear the interrupt flag
    IPC4bits.INT4IP = 1;    //Set priority to 1
    IPC4bits.INT4IS = 2;    //Set subpriority to 0
    IEC0bits.INT4IE = 1;    //Enable interrupt
}

void    init_tmr1()
{
    /*
     * We want to switch between displays 30 times every second
     * So PR1 = seconde * frequency / prescale
     * prescale -> 64
     * frequency -> 8Mhz
     * PR1 = (1/200) * 8M / 64
     *     = 625
     */
    T1CON = 0;          //Turn T1 off
    TMR1 = 0;
    T1CONSET = 0x20;    //Set prescale at 1/64
    PR1 = 625;
    T1CONbits.ON = 1;   //Turn T1 ON

    IEC0bits.T1IE = 0;  //Disable T1 interrupt
    IFS0bits.T1IF = 0;  //Clear T1 interrupt flag
    IPC1bits.T1IP = 3;  //Set T1 interrupt priority = 1
    IPC1bits.T1IS = 0;  //Set T1 interrupt subpriority = 0
    IEC0bits.T1IE = 1;  //Enable T1 interrupt
}

void    init_interrupt()
{
    INTCONbits.MVEC = 1;    //Enable multi-vector interrupt
    init_bus_col();
    init_int1();
    init_int2();
    init_int3();
    init_int4();
    init_tmr1();
    asm volatile("ei");     //Enable all interrupt
}