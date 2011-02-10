#ifndef _BSP_ADXL345_H
#define _BSP_ADXL345_H

#define DATA_FORMAT_REG 0x31u
#define POWER_CTRL      0x2Du
#define FIFO_CTRL       0x38u
#define DATAX0          0x32u
#define DATAY0          0x34u
#define DATAZ0          0x36u

void            BSP_Accel_Init     (void);
CPU_INT16S      BSP_Accel_X_AxisRd (void);
CPU_INT16S      BSP_Accel_Y_AxisRd (void);
CPU_INT16S      BSP_Accel_Z_AxisRd (void);
void            BSP_Accel_ZeroCal  (void);

#define ACCEL_ADDR  (0x3A >> 1)

#endif