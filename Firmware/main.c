#include "depp.h"
#include <p32xxxx.h>

u8 mode = SIMPLE;
u8 max_ds1 = 6;
u8 max_ds2 = 6;
u8 max_ds3 = 6;
u16 absolute_max = 6;
u8 current_ds1 = 0;
u8 current_ds2 = 0;
u8 current_ds3 = 6;
u8 current_time = 0;
u8 default_count = 30;
u8 default_min = 0;
u8 default_chrono = 0;
u8 chrono = 0;
u16 counter_tmr = 0;
u8 dp = 0;
u8 minute = 0;
u32 random_value1 = 0; //u32 in order to avoid overflow
u32 random_value2 = 0;
u32 random_value3 = 0;
s16 x = 0;
s16 y = 0;
s16 z = 0;
u8 blink = 0;

void set_number(u16 n) {
    current_ds1 = n / 100;
    current_ds2 = n % 100 / 10;
    current_ds3 = n % 10;
}

void show_result() {
    u8 result = 0;

    blink = 0;
    if (mode == SIMPLE) {
        if (absolute_max != 0) {
            random_value1 %= absolute_max;
            random_value2 %= absolute_max;
            random_value3 %= absolute_max;
            result = ((random_value1 + random_value2 + random_value3) % absolute_max) + 1;
            set_number(result);
        }
    } else if (mode == MULTI) {
        current_ds1 = (max_ds1 > 0) ? (random_value1 % max_ds1) + 1 : 0;
        current_ds2 = (max_ds2 > 0) ? (random_value2 % max_ds2) + 1 : 0;
        current_ds3 = (max_ds3 > 0) ? (random_value3 % max_ds3) + 1 : 0;
    } else if (mode == COUNTDOWN && chrono == 0) {
        chrono = 1;
    }
}

void __ISR(INT1_VECTOR, ipl1SOFT) Button2_handler(void) {
    while (PORTCbits.RC4 == 1);
    while (PORTCbits.RC4 == 1);
    counter_tmr = 0;
    if (mode == SIMPLE) {
        if (blink == 1) {
            ++current_ds2;
            if (current_ds2 >= 10)
                current_ds2 = 0;
            absolute_max = (current_ds1 * 100) + (current_ds2 * 10) + current_ds3;
            set_number(absolute_max);
        } else
        {
            blink = 1;
            set_number(absolute_max);
        }
    } else if (mode == MULTI) {
        if (blink == 1) {
            ++max_ds2;
            if (max_ds2 >= 10)
                max_ds2 = 0;
            set_number((max_ds1 * 100) + (max_ds2 * 10) + max_ds3);
        } else{
            blink = 1;
            set_number((max_ds1 * 100) + (max_ds2 * 10) + max_ds3);
        }
    } else if (mode == COUNTDOWN) {
        if (PORTCbits.RC5 == 1) {
            current_time = default_count;
            set_number(current_time);
        } else if (chrono == 0) {
            if (blink == 1) {
                ++current_ds2;
                if (current_ds2 >= 6)
                    current_ds2 = 0;
                default_count = (current_ds2 * 10) + current_ds3;
                current_time = default_count;
                set_number((default_min * 100) + default_count);
            } else{
                blink = 1;
                set_number((default_min * 100) + default_count);
            }
        }
    } else if (mode == CHRONO) {
        chrono = (chrono == 1) ? 0 : 1;
    }
    IFS0bits.INT1IF = 0;
}

void __ISR(INT2_VECTOR, ipl2SOFT) Button1_handler(void) {
    while (PORTCbits.RC3 == 1);
    while (PORTCbits.RC3 == 1);
    counter_tmr = 0;
    if (mode == SIMPLE) {
        if (blink == 1) {
            ++current_ds3;
            if (current_ds3 >= 10)
                current_ds3 = 0;
            absolute_max = (current_ds1 * 100) + (current_ds2 * 10) + current_ds3;
            set_number(absolute_max);
        } else
        {
            blink = 1;
            set_number(absolute_max);
        }
    } else if (mode == MULTI) {
        if (blink == 1) {
            ++max_ds3;
            if (max_ds3 >= 10)
                max_ds3 = 0;
            set_number((max_ds1 * 100) + (max_ds2 * 10) + max_ds3);
        } else{
            blink = 1;
            set_number((max_ds1 * 100) + (max_ds2 * 10) + max_ds3);
        }
    } else if (mode == COUNTDOWN) {
        if (chrono == 0) {
            if (blink == 1) {
                ++current_ds3;
                if (current_ds3 >= 10)
                    current_ds3 = 0;
                current_time = (current_ds2 * 10) + current_ds3;
                default_count = current_time;
                set_number((default_min * 100) + default_count);
            } else{
                blink = 1;
                set_number((default_min * 100) + default_count);
            }
        } else
            chrono = 0;
    }
    IFS0bits.INT2IF = 0;
}

void __ISR(INT3_VECTOR, ipl2SOFT) Mode_handler(void) {
    chrono = 0;
    blink = 0;
    while (PORTBbits.RB5 == 1);
    while (PORTBbits.RB5 == 1);
    mode = (mode + 1) % 4;
    if (mode == SIMPLE) {
        dp = 0;
        set_number(absolute_max);
        pwm_led(BLUE);
    } else if (mode == MULTI) {
        dp = 0;
        set_number((max_ds1 * 100) + (max_ds2 * 10) + max_ds3);
        pwm_led(PURPLE);
    } else if (mode == COUNTDOWN) {
        dp = 1;
        current_time = 30;
        counter_tmr = 0;
        set_number((default_min * 100) + default_count);
        pwm_led(RED);
    } else if (mode == CHRONO) {
        dp = 1;
        current_time = 0;
        counter_tmr = 0;
        set_number(default_chrono);
        pwm_led(GREEN);
    }
    while (PORTBbits.RB5 == 1);
    IFS0bits.INT3IF = 0;
}

void __ISR(INT4_VECTOR, ipl1SOFT) Button3_handler(void) {
    while (PORTCbits.RC5 == 1);
    while (PORTCbits.RC5 == 1);
    counter_tmr = 0;
    if (mode == SIMPLE) {
        if (blink == 1) {
            dp = 0;
            ++current_ds1;
            if (current_ds1 >= 10)
                current_ds1 = 0;
            absolute_max = (current_ds1 * 100) + (current_ds2 * 10) + current_ds3;
            set_number(absolute_max);
        } else{
            blink = 1;
            set_number(absolute_max);
        }
    } else if (mode == MULTI) {
        if (blink == 1) {
            dp = 0;
            ++max_ds1;
            if (max_ds1 >= 10)
                max_ds1 = 0;
            set_number((max_ds1 * 100) + (max_ds2 * 10) + max_ds3);
        } else{
            blink = 1;
            set_number((max_ds1 * 100) + (max_ds2 * 10) + max_ds3);
        }
    } else if (mode == COUNTDOWN) //reset to default value
    {
        if (PORTCbits.RC4 == 1) {
            current_time = default_count;
            set_number(current_time);
        } else if (chrono == 0) {
            if (blink == 1) {
                ++default_min;
                if (default_min >= 10)
                    default_min = 0;
                minute = default_min;
                set_number((default_min * 100) + (current_ds2 * 10) + current_ds3);
            } else{
                set_number((default_min * 100) + default_count);
                blink = 1;
            }
        }
    } else if (mode == CHRONO) //reset to default value
    {
        chrono = 0;
        current_time = 0;
        set_number(current_time);
    }
    IFS0bits.INT4IF = 0;
}

u8 mpu_is_shaking() {
    static u8 stock_stack = 0;
    u8 ret = 0;

    x = (i2c_read(ACCEL_XOUT_H) << 8) + i2c_read(ACCEL_XOUT_L);
    y = (i2c_read(ACCEL_YOUT_H) << 8) + i2c_read(ACCEL_YOUT_L);
    z = (i2c_read(ACCEL_ZOUT_H) << 8) + i2c_read(ACCEL_ZOUT_L);
    
    if ((x / 8192 <= -2 || 2 <= x / 8192) ||
            (y / 8192 <= -2 || 2 <= y / 8192) ||
            (z / 8192 <= -2 || 2 <= z / 8192)) {
        ++stock_stack;
        if (stock_stack % 3 == 0)
            random_value1 = x + y + z;
        else if (stock_stack % 3 == 1)
            random_value2 = x + y + z;
        else if (stock_stack % 3 == 2)
            random_value3 = x + y + z;
    } else {
        ret = stock_stack >= 10 ? 1 : 0;
        stock_stack = 0;
    }
    return (ret);
}

void __ISR(TMR1_VECTOR, ipl3SOFT) Tmr1_handler(void) //TRM1 allows switch between DS1 & DS2
{
    ++counter_tmr;
    if (blink == 0 || (blink == 1 && counter_tmr % 5 == 1)) {
        if (LATAbits.LATA10 == 1) {
            MOS_OFF(A, 10);
            //    MOS_OFF(B, 14);
            MOS_ON(B, 15);
            putnbr(current_ds1, dp);
        } else if (LATBbits.LATB15 == 1) {
            //    MOS_OFF(A, 10);
            MOS_OFF(B, 15);
            MOS_ON(B, 14);
            putnbr(current_ds2, 0);
        } else if (LATBbits.LATB14 == 1) {
            MOS_OFF(B, 14);
            //    MOS_OFF(B, 15);
            MOS_ON(A, 10);
            putnbr(current_ds3, 0);
        }
    }
    if (counter_tmr > 15 && (mode == COUNTDOWN || mode == SIMPLE || mode == MULTI)) {
        if (mpu_is_shaking() == 1) {
            show_result();
        }
    }
    if (blink == 1 && counter_tmr > 400) {
        blink = 0;
        counter_tmr = 0;
    }
    if (counter_tmr > 200 && mode == COUNTDOWN && chrono == 1 && blink == 0) {
        counter_tmr = 0;
        if (current_time == 0) {
            if (minute != 0) {
                --minute;
                current_time = 59;
            } else
                chrono = 0;
        } else
            --current_time;
        set_number(minute * 100 + current_time);
    } else if (counter_tmr > 200 && mode == CHRONO && chrono == 1 && blink == 0) {
        counter_tmr = 0;
        if (current_time < 59)
            ++current_time;
        else {
            if (current_ds1 < 9) {
                ++current_ds1;
                current_time = 0;
            }
        }
        counter_tmr = 0;
        set_number(current_ds1 * 100 + current_time);
    }
    IFS0bits.T1IF = 0;
}

int main() {
    u16 delay = 1000;

    while (--delay > 0);
    generate_9clock();
    init_port();
    i2c_init();
    init_mpu();
    init_interrupt();
    init_pwm();

    DDPCONbits.JTAGEN = 0;
    pwm_led(BLUE);
    while (1) {
    }
}
