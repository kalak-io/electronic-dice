#include "depp.h"

void    init_mpu()
{
//    u16  delay = 1000;
//    i2c_write(PWR_MGMT_1, 0x80);
    i2c_write(MOT_DETECT_CTRL, 0x01);
//    while(--delay > 0);
    
    i2c_write(PWR_MGMT_1, 0);       //turn off sleep mode
    i2c_write(SIGNAL_PATH_RESET, 0);
    i2c_write(SMPLRT_DIV, 4);       //init
    i2c_write(ACCEL_CONFIG, 0x10);     //set mpu full scale = 4g
   /* 
    i2c_write(MOT_THR, 10);       // set threshold interrupt at 0)
    i2c_write(MOT_DETECT_CTRL, 0x10);
    i2c_write(INT_ENABLE, 0x41); //Allows the accelerometer to send interrupt when motion is detected
    i2c_write(INT_PIN_CFG, 0x30);
    */
	// Reset 0 all unused registers
	i2c_write(CONFIG, 0);
	i2c_write(GYRO_CONFIG, 0);
	i2c_write(MOT_THR, 0);
	i2c_write(FIFO_EN, 0);
	i2c_write(I2C_MST_CTRL, 0);
	i2c_write(I2C_SLV0_ADDR, 0);
	i2c_write(I2C_SLV0_REG, 0);
	i2c_write(I2C_SLV0_CTRL, 0);
	i2c_write(I2C_SLV1_ADDR, 0);
	i2c_write(I2C_SLV1_REG, 0);
	i2c_write(I2C_SLV1_CTRL, 0);
	i2c_write(I2C_SLV2_ADDR, 0);
	i2c_write(I2C_SLV2_REG, 0);
	i2c_write(I2C_SLV2_CTRL, 0);
	i2c_write(I2C_SLV3_ADDR, 0);
	i2c_write(I2C_SLV3_REG, 0);
	i2c_write(I2C_SLV3_CTRL, 0);
	i2c_write(I2C_SLV4_ADDR, 0);
	i2c_write(I2C_SLV4_REG, 0);
	i2c_write(I2C_SLV4_DO, 0);
	i2c_write(I2C_SLV4_CTRL, 0);
	i2c_write(I2C_SLV4_DI, 0);
	i2c_write(I2C_MST_STATUS, 0);
	i2c_write(INT_PIN_CFG, 0);
	i2c_write(INT_ENABLE, 0);
	i2c_write(I2C_SLV0_DO, 0);
	i2c_write(I2C_SLV1_DO, 0);
	i2c_write(I2C_SLV2_DO, 0);
	i2c_write(I2C_SLV3_DO, 0);
	i2c_write(I2C_MST_DELAY_CTRL, 0);
	i2c_write(MOT_DETECT_CTRL, 0);
	i2c_write(USER_CTRL, 0);
	i2c_write(PWR_MGMT_2, 0);
	i2c_write(FIFO_R_W, 0);
}
