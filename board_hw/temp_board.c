#include "bsp_adt7420.h"
#include "cpu.h"
#include "bsp.h"
#include "lib_def.h"

/*
*********************************************************************************************************
*                                    INITIALIZE TEMPERATURE SENSOR
*********************************************************************************************************
*/

void  BSP_Temp_Init (void)
{
    CPU_INT08U  temp_data[2];
    
    
    temp_data[0] = BSP_TEMP_CFG;                      /* configure temperature sensor                   */
    temp_data[1] = 0x00;
    BSP_RIIC0_MasterWr(BSP_TEMP_ADDR, &temp_data[0], 2, DEF_TRUE);
}


/*
*********************************************************************************************************
*                                       READ TEMPERATURE SENSOR
*********************************************************************************************************
*/

CPU_FP32  BSP_Temp_Rd (void)
{
    CPU_INT08U  temp_data[2];
    CPU_INT16U  temp;
    CPU_FP32    val;
      

    temp_data[0] = BSP_TEMP_REG;
    BSP_RIIC0_MasterWr(BSP_TEMP_ADDR, &temp_data[0], 1, DEF_FALSE);

    BSP_RIIC0_MasterRd(BSP_TEMP_ADDR, &temp_data[0], 2, DEF_FALSE);
    temp  = temp_data[0] << 8;
    temp += temp_data[1];
    temp  = temp >> 3;

    val   = (CPU_FP32)temp * 0.0625f;

    return (val);
}
