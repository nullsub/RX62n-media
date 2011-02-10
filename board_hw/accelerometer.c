#include "cpu.h"
#include "bsp.h"
#include "bsp_adxl345.h"
#include "lib_def.h"


volatile CPU_INT16S BSP_Accel_X_Zero;
volatile CPU_INT16S BSP_Accel_Y_Zero;
volatile CPU_INT16S BSP_Accel_Z_Zero;


/*
*********************************************************************************************************
*                                      INITIALIZE ACCELEROMETER
*********************************************************************************************************
*/

void  BSP_Accel_Init (void)
{
    CPU_INT08U  accel_data[2];


                                                                  /* accelerometer data format                     */
                                                                  /* range +/- 16g                                 */
                                                                  /* right justified with sign extension           */
    accel_data[0] = DATA_FORMAT_REG;                              /* Full resolution mode                          */
    accel_data[1] = 0x0B;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 2, DEF_TRUE);
    
    accel_data[0] = POWER_CTRL;                                   /* take accelerometer out of standby mode        */
    accel_data[1] = 0x08;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 2, DEF_TRUE);
    
    accel_data[0] = FIFO_CTRL;                                    /* put FIFO into bypass mode                     */
    accel_data[1] = 0x00;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 2, DEF_TRUE);
}


/*
*********************************************************************************************************
*                                     READ ACCELEROMETER'S X AXIS
*********************************************************************************************************
*/

CPU_INT16S  BSP_Accel_X_AxisRd (void)
{
    CPU_INT08U  accel_data[2];
    CPU_INT16U  x_axis_val;

    
    accel_data[0] = DATAX0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, DEF_TRUE);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, DEF_TRUE);
    
    x_axis_val    = accel_data[1] << 8;
    x_axis_val   += accel_data[0];

    return ((CPU_INT16S)x_axis_val);
}


/*
*********************************************************************************************************
*                                     READ ACCELEROMETER'S Y AXIS
*********************************************************************************************************
*/

CPU_INT16S  BSP_Accel_Y_AxisRd (void)
{
    CPU_INT08U  accel_data[2];
    CPU_INT16U  y_axis_val;

    
    accel_data[0] = DATAY0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, DEF_TRUE);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, DEF_TRUE);
    
    y_axis_val    = accel_data[1] << 8;
    y_axis_val   += accel_data[0];

    return ((CPU_INT16S)y_axis_val);
}


/*
*********************************************************************************************************
*                                     READ ACCELEROMETER'S Z AXIS
*********************************************************************************************************
*/

CPU_INT16S  BSP_Accel_Z_AxisRd (void)
{
    CPU_INT08U  accel_data[2];
    CPU_INT16U  z_axis_val;

    
    accel_data[0] = DATAZ0;
    BSP_RIIC0_MasterWr(ACCEL_ADDR, accel_data, 1, DEF_TRUE);
    BSP_RIIC0_MasterRd(ACCEL_ADDR, accel_data, 2, DEF_TRUE);
    
    z_axis_val    = accel_data[1] << 8;
    z_axis_val   += accel_data[0];

    return ((CPU_INT16S)z_axis_val);
}


/*
*********************************************************************************************************
*                                       CALIBRATE ACCELEROMETER
*********************************************************************************************************
*/

void  BSP_Accel_ZeroCal (void)
{
    CPU_INT08U  indx;


    BSP_Accel_X_Zero = 0;
    BSP_Accel_Y_Zero = 0;
    BSP_Accel_Z_Zero = 0;
    
    for (indx = 0; indx < 8; indx++) {
        BSP_Accel_X_Zero += BSP_Accel_X_AxisRd();
        BSP_Accel_Y_Zero += BSP_Accel_Y_AxisRd();
        BSP_Accel_Z_Zero += BSP_Accel_Z_AxisRd();
    }
    
    BSP_Accel_X_Zero = BSP_Accel_X_Zero / 8;
    BSP_Accel_Y_Zero = BSP_Accel_Y_Zero / 8;
    BSP_Accel_Z_Zero = BSP_Accel_Z_Zero / 8;
}
