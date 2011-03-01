#ifndef _BSP_ADT7420_H
#define _BSP_ADT7420_H


#define   BSP_TEMP_ADDR  (0x90 >> 1)

#define   BSP_TEMP_REG    0x00u
#define   BSP_TEMP_CFG    0x03u

void	temp_init (void);
float  	temp_read(void);

#endif
