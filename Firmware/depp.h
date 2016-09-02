#ifndef DEPP_H
#define DEPP_H

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "mpu.h"
//#include "mpu6050.h"

#define TMR1_VECTOR     4
#define TMR3_VECTOR     12
#define INT1_VECTOR     7
#define INT2_VECTOR     11
#define INT3_VECTOR     15
#define INT4_VECTOR     19
#define BUS_COL_VECTOR  33

#define RED         85, 0, 0
#define GREEN       0, 85, 0
#define BLUE        0, 0, 85
#define PURPLE      50, 0, 50
#define WHITE       85, 85, 85

#define ACK         0
#define NACK        1
/*
**      Define macro about config pin
**      x = letter of pin
**      y = number of pin 
**      Usage : MACRO(x, y);
*/

#define LAT_ON(x, y) LAT ## x ## bits.LAT ## x ## y = 1
#define LAT_OFF(x, y) LAT ## x ## bits.LAT ## x ## y = 0
#define TRIS_IN(x, y) TRIS ## x ## bits.TRIS ## x ## y = 1
#define TRIS_OUT(x, y) TRIS ## x ## bits.TRIS ## x ## y = 0
#define MOS_ON(x, y) LAT ## x ## bits.LAT ## x ## y = 1
#define MOS_OFF(x, y) LAT ## x ## bits.LAT ## x ## y = 0

#define BUZZER_ON OC4CONbits.ON = 1
#define BUZZER_OFF OC4CONbits.ON = 0
#define NOTE 100

enum    mode{SIMPLE, MULTI, COUNTDOWN, CHRONO};

void    init_interrupt();
void    init_mpu();
void    init_port();
void    init_pwm();
void    pwm_buzzer(u8 note);
void    pwm_led(u8 r, u8 g, u8 b);
void    putnbr(u8 nb, u8 dp);
void    disp_off();
void    i2c_init();
u8      i2c_read(u8 amslave);
void    i2c_write(u8 amslave, u8 value);
void    generate_9clock();


#endif /* DEPP_H */