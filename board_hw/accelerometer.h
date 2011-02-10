#ifndef _BSP_ADXL345_H
#define _BSP_ADXL345_H

#include "stdint.h"

#define DATA_FORMAT_REG 0x31u
#define POWER_CTRL      0x2Du
#define FIFO_CTRL       0x38u
#define DATAX0          0x32u
#define DATAY0          0x34u
#define DATAZ0          0x36u

void            accel_init     (void);
int16_t      accel_get_x(void);
int16_t      accel_get_y(void);
int16_t     accel_get_z(void);
void            BSP_Accel_ZeroCal  (void);

#define ACCEL_ADDR  (0x3A >> 1)

#endif
