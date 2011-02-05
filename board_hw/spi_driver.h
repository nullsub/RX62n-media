/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : RS22
Module name  : SPI driver
File Name    : spi_driver.h

File Description:


Author :

Rev History:
Ver  By         date          Description
---------------------------------------------------------
1.1  Redpine Signals
--------------------------------------------------------
*END**************************************************************************/

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "rsi_compiler.h"

typedef struct spi_data_s
{
  uint8_t *TX_DATA;
  uint32_t len;
}spi_data_t;


#define DISABLE_TXRX  //disable_TX_RX() ;
#define ENABLE_TXRX   //enable_TX_RX() ;

#define ENABLE_CHIPSELECT   	P7.DR.BIT.B0 = 0;
#define DISABLE_CHIPSELECT   	P7.DR.BIT.B0 = 1;


#define DISABLE_SLAVE_INTERRUPT  //(ICU.IER09.BIT.IEN7 = 0)
#define ENABLE_SLAVE_INTERRUPT   //(ICU.IER09.BIT.IEN7 = 1)

/* Prototype functions. Documentation found in source file */

void SPI_MasterTransceiveByte(uint8_t *src_data, uint8_t *dst_data,
                              uint32_t len);


#endif
