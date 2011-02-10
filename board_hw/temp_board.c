#include "temp_board.h"

#include "i2c.h"

/*
*********************************************************************************************************
*                                    INITIALIZE TEMPERATURE SENSOR
*********************************************************************************************************
*/

void  temp_init (void)
{
    uint8_t temp_data[2];
    
    
    temp_data[0] = BSP_TEMP_CFG;                      /* configure temperature sensor                   */
    temp_data[1] = 0x00;
    BSP_RIIC0_MasterWr(BSP_TEMP_ADDR, &temp_data[0], 2, true);
}


/*
*********************************************************************************************************
*                                       READ TEMPERATURE SENSOR
*********************************************************************************************************
*/

float  temp_read(void)
{
    uint8_t  temp_data[2];
    uint16_t  temp;
    float    val;
      

    temp_data[0] = BSP_TEMP_REG;
    BSP_RIIC0_MasterWr(BSP_TEMP_ADDR, &temp_data[0], 1, false);

    BSP_RIIC0_MasterRd(BSP_TEMP_ADDR, &temp_data[0], 2, false);
    temp  = temp_data[0] << 8;
    temp += temp_data[1];
    temp  = temp >> 3;

    val   = (float)temp * 0.0625f;

    return val;
}
