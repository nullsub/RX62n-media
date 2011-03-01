#include "i2c.h"
#include "accelerometer.h"


static int16_t Accel_X_Zero;
static int16_t Accel_Y_Zero;
static int16_t Accel_Z_Zero;


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
    int16_t  x_axis_val;

    
    accel_data[0] = DATAX0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, true);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, true);
    
    x_axis_val    = accel_data[1] << 8;
    x_axis_val   += accel_data[0];

	x_axis_val -= Accel_X_Zero;

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
    int16_t  y_axis_val;

    
    accel_data[0] = DATAY0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, true);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, true);
    
    y_axis_val    = accel_data[1] << 8;
    y_axis_val   += accel_data[0];

	y_axis_val -= Accel_Y_Zero;

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
    int16_t  z_axis_val;

    
    accel_data[0] = DATAZ0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, true);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, true);
    
    z_axis_val    = accel_data[1] << 8;
    z_axis_val   += accel_data[0];

	z_axis_val -= Accel_Z_Zero;

    return z_axis_val;
}


/*
*********************************************************************************************************
*                                       CALIBRATE ACCELEROMETER
*********************************************************************************************************
*/

void  accel_calibrate_zero(void)
{
    int X_Zero = 0;
    int Y_Zero = 0;
    int Z_Zero = 0;
    
    for (int i = 0; i < 8; i++) {
        X_Zero += accel_get_x();
        Y_Zero += accel_get_y();
        Z_Zero += accel_get_z();
    }
    
    Accel_X_Zero = X_Zero / 8;
    Accel_Y_Zero = Y_Zero / 8;
    Accel_Z_Zero = Z_Zero / 8;
}

