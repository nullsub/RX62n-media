#include "i2c.h"
#include "accelerometer.h"


volatile int16_t BSP_Accel_X_Zero;
volatile int16_t BSP_Accel_Y_Zero;
volatile int16_t BSP_Accel_Z_Zero;


/*
*********************************************************************************************************
*                                      INITIALIZE ACCELEROMETER
*********************************************************************************************************
*/

void  accel_init (void)
{
    uint8_t  accel_data[2];

                                                                  /* accelerometer data format                     */
                                                                  /* range +/- 16g                                 */
                                                                  /* right justified with sign extension           */
    accel_data[0] = DATA_FORMAT_REG;                              /* Full resolution mode                          */
    accel_data[1] = 0x0B;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 2, true);
    
    accel_data[0] = POWER_CTRL;                                   /* take accelerometer out of standby mode        */
    accel_data[1] = 0x08;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 2, true);
    
    accel_data[0] = FIFO_CTRL;                                    /* put FIFO into bypass mode                     */
    accel_data[1] = 0x00;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 2, true);
}


/*
*********************************************************************************************************
*                                     READ ACCELEROMETER'S X AXIS
*********************************************************************************************************
*/

int16_t  accel_get_x(void)
{
    uint8_t  accel_data[2];
    uint16_t  x_axis_val;

    
    accel_data[0] = DATAX0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, true);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, true);
    
    x_axis_val    = accel_data[1] << 8;
    x_axis_val   += accel_data[0];

    return x_axis_val;
}


/*
*********************************************************************************************************
*                                     READ ACCELEROMETER'S Y AXIS
*********************************************************************************************************
*/

int16_t accel_get_y(void)
{
    uint8_t  accel_data[2];
    uint16_t  y_axis_val;

    
    accel_data[0] = DATAY0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, true);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, true);
    
    y_axis_val    = accel_data[1] << 8;
    y_axis_val   += accel_data[0];

    return y_axis_val;
}


/*
*********************************************************************************************************
*                                     READ ACCELEROMETER'S Z AXIS
*********************************************************************************************************
*/

int16_t  accel_get_z (void)
{
    uint8_t  accel_data[2];
    uint16_t  z_axis_val;

    
    accel_data[0] = DATAZ0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, true);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, true);
    
    z_axis_val    = accel_data[1] << 8;
    z_axis_val   += accel_data[0];

    return z_axis_val;
}


/*
*********************************************************************************************************
*                                       CALIBRATE ACCELEROMETER
*********************************************************************************************************
*/

void  accel_calibrate_zero(void)
{
    uint8_t  indx;


    BSP_Accel_X_Zero = 0;
    BSP_Accel_Y_Zero = 0;
    BSP_Accel_Z_Zero = 0;
    
    for (indx = 0; indx < 8; indx++) {
        BSP_Accel_X_Zero += accel_get_x();
        BSP_Accel_Y_Zero += accel_get_y();
        BSP_Accel_Z_Zero += accel_get_z();
    }
    
    BSP_Accel_X_Zero = BSP_Accel_X_Zero / 8;
    BSP_Accel_Y_Zero = BSP_Accel_Y_Zero / 8;
    BSP_Accel_Z_Zero = BSP_Accel_Z_Zero / 8;
}

