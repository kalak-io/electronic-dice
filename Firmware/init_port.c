#include "depp.h"

void    init_mosfet()
{
    //DS1 / Q1 in output mode
    MOS_ON(B, 15);
    TRIS_OUT(B, 15);
    //DS2 / Q2 in output mode
    MOS_OFF(B, 14);
    TRIS_OUT(B, 14);
    //DS3 / Q3 in output mode
    MOS_OFF(A, 10);
    TRIS_OUT(A, 10);
}

void    init_buttons()
{
    //BUTTON0 set in input mode
    LATCbits.LATC3 = 0;
    TRISCbits.TRISC3 = 1;
    
    //BUTTON1 set in input mode
    LATCbits.LATC4 = 0;
    TRISCbits.TRISC4 = 1;
    
    //BUTTON2 set in input mode
    LATCbits.LATC5 = 0;
    TRISCbits.TRISC5 = 1;
    
    //BUTTON3 set in input mode
    LATBbits.LATB5 = 0;
    TRISBbits.TRISB5 = 1;   
}

void    init_display()
{
    //DISPLAY0 set in output mode
    LATBbits.LATB0 = 0;
    TRISBbits.TRISB0 = 0;
    
    //DISPLAY1 set in output mode
    LATBbits.LATB1 = 0;
    TRISBbits.TRISB1 = 0;
    
    //DISPLAY2 set in output mode
    LATCbits.LATC1 = 0;
    TRISCbits.TRISC1 = 0;
    
    //DISPLAY3 set in output mode
    LATBbits.LATB3 = 0;
    TRISBbits.TRISB3 = 0;
    
    //DISPLAY4 set in output mode
    LATBbits.LATB2 = 0;
    TRISBbits.TRISB2 = 0;    
    
    //DISPLAY5 set in output mode
    LATAbits.LATA1 = 0;
    TRISAbits.TRISA1 = 0;
    
    //DISPLAY6 set in output mode
    LATAbits.LATA0 = 0;
    TRISAbits.TRISA0 = 0;
    
    //DISPLAY7 set in output mode
    LATCbits.LATC0 = 0;
    TRISCbits.TRISC0 = 0;
}

void    init_port()
{
    /*
     * Pin selection
     * Read pic32 datasheet page 130
     */
    INT1R = 0x7;    //(BUTTON1 => B2) Set INT1 pin to be on RPC4 pin
    INT2R = 0x7;    //(BUTTON0 => B1) Set INT2 pin to be on RPC3 pin
    INT3R = 0x1;    //(BUTTON3 => B4) Set INT3 pin to be on RPB5 pin
    INT4R = 0x7;    //(BUTTON2 => B3) Set INT4 pin to be on RPC5 pin
    RPC7R = 0x5;    //(OC1 => RED) Set OC1 pin to be on RPC7 pin
    RPC8R = 0x5;    //(OC2 => BLUE) Set OC2 pin to be on RPC8 pin
    RPC9R = 0x5;    //(OC3 => GREEN) Set OC3 pin to be on RPC9 pin
    RPA2R = 0x5;    //(OC4 => BUZZER) Set OC4 pin to be on RPA2 pin
    
    init_buttons();
    init_display();
    init_mosfet();
}