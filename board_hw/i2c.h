/*
*********************************************************************************************************
*
*                                         BOARD SUPPORT PACKAGE
*
*                                              Renesas RX62N
*                                                on the
*                                      RSK-2+RX62N Evaluation Board
*
*                                 (c) Copyright 2010, Micrium, Weston, FL
*                                          All Rights Reserved
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : FGK
*********************************************************************************************************
*/

#ifndef  BSP_H_
#define  BSP_H_

#include "stdint.h"
#include <stdbool.h>
 


/*
*********************************************************************************************************
*                                            RIIC SERVICES
*********************************************************************************************************
*/

void        i2c_init(void);
void        BSP_RIIC0_MasterRd(uint8_t   addr, uint8_t  *p_data, uint32_t   len, bool  start);
void        BSP_RIIC0_MasterWr(uint8_t  addr, uint8_t *p_data, uint32_t   len, bool  stop);


#endif
