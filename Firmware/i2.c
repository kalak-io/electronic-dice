#include "depp.h"

void    generate_9clock()
{
    u8  clock = 0;

    LATBbits.LATB8 = 0;
    TRIS_OUT(B, 8);
    while (clock < 9)
    {
        if (LATBbits.LATB8 == 1)
        {
            LAT_OFF(B, 8);
            clock++;
        }
        else
            LAT_ON(B, 8);
    }
}

void    i2c_init()
{
    I2C1CONbits.ON = 1;     //Turn i2c ON
    I2C1BRG = 0x3;           //Set baudrate		// SOURCE ERREUR
}

void    i2c_transmit(u8 addr)
{
    I2C1TRN = addr;                   //Adress to transfer
    while (I2C1STATbits.TRSTAT || I2C1STATbits.TBF)        
        ;
    if (!I2C1STATbits.ACKSTAT)
        ;
}

void    i2c_start()
{
    I2C1CONbits.SEN = 1;                    //Assert start condition on SDA SCL
    while (I2C1CONbits.SEN)                 
        ;
}

void    i2c_repeat_start()
{
    I2C1CONbits.RSEN = 1;		    //Assert repeated start
    while (I2C1CONbits.RSEN == 1);	    //Wait until RSEN is cleared
}

void    i2c_stop()
{
    I2C1CONbits.PEN = 1;        //Generates STOP
    while (I2C1CONbits.PEN == 1);
}

void    i2c_getadress(u8 rw_bit)
{
    i2c_transmit((0x68 << 1) | rw_bit);     //Adress to the buffer
}

void    i2c_send_ack(u8 ack)
{
    I2C1CONbits.ACKDT = ack;
    I2C1CONbits.ACKEN = 1;      //Master generates ACK or NACK (ack -> 0 nack -> 1)
    while (I2C1CONbits.ACKEN == 1);
}

u8  i2c_receive()                   
{
    I2C1CONbits.RCEN = 1;       //Enable master reception
    while (!I2C1STATbits.RBF)  
        ;
    while (I2C1CONbits.RCEN == 1);
    return I2C1RCV;
}

u8 i2c_read(u8 amslave)
{
    u8 data = 0;

    i2c_start();                // bit start
    i2c_getadress(0);           // envoi adresse du 6 axis mode write

    i2c_transmit(amslave);      // envoi adresse du registre

    i2c_repeat_start();         // bit de restart
    i2c_getadress(1);           // envoi adresse de 6 axis mode read

    data = i2c_receive();       // lecture du registre
    i2c_send_ack(1);            // not ack
    i2c_stop();                 // bit stop

    return (data);
}

u16 i2c_read16(u8 amslave)
{
    u16 data = 0;

    i2c_start();             // bit start
    i2c_getadress(0);           // envoi adresse du 6 axis mode write

    i2c_transmit(amslave);            // envoi adresse du registre

    i2c_repeat_start();           // bit de restart
    i2c_getadress(1);           // envoi adresse de 6 axis mode read

    data = i2c_receive() << 8;           // lecture du registre
    i2c_send_ack(0);                  // ack
    data += i2c_receive();
    i2c_send_ack(1);                  // not ack
    i2c_stop();              // bit stop

    return (data);
}

void    i2c_write(u8 amslave, u8 value)
{
    i2c_start();
    i2c_getadress(0);           // envoi adresse du 6 axis mode write

    i2c_transmit(amslave);
    
    i2c_transmit(value);
    i2c_stop();
}

void    i2c_write16(u8 amslave, u16 value)
{
    i2c_getadress(0);
    i2c_transmit(amslave); 
    i2c_transmit(value >> 8);
    i2c_transmit(value);
    i2c_stop();
}
