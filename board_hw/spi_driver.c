/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : RS22
Module name  : SPI driver
File Name    : spi_driver.c

File Description:

List of functions:
                  rs22_ssp_bus_request_synch
    
Author :

Rev History:
Sl  By           date        change     details
---------------------------------------------------------
1   Redpine Signals  
---------------------------------------------------------
*END*************************************************************************/
#include "spi_driver.h"
#include "iodefine.h"                  
#include "includes.h"


#include "FreeRTOS.h"
#include "semphr.h"


static xSemaphoreHandle spi_mutex;

unsigned char *msg_string;
volatile int global_flag = 0;
volatile unsigned int glbl_count = 0;
volatile unsigned int rx_buf = 0;

unsigned char junk_buf[1100];
unsigned int intr = 0;

volatile uint8_t src_junk_flag = 0;
volatile uint8_t dst_junk_flag = 0;


spi_data_t  spi_data_reg;
unsigned int glbl_flag1 = 0;
volatile unsigned char TEMP_RDR;
volatile unsigned int global_flag1 = 0;

void rsi_spi_MasterInit(void )
{
    	spi_mutex = xSemaphoreCreateMutex();                    /* Request mutex, block until mutex obtained          */
	
	xSemaphoreTake(spi_mutex, portMAX_DELAY);

   MSTP(RSPI0) = 0 ;

    /* Select proper bank of pins for SPI0 */
    IOPORT.PFGSPI.BIT.RSPIS = 0 ;
    /* SCK (PC.5) is active */
    IOPORT.PFGSPI.BIT.RSPCKE = 1 ;
    
   /* SSL3 (PC.2) is inactive (toggled as GPIO instead) */
    IOPORT.PFGSPI.BIT.SSL2E = 0 ;
    /* MOSI (PC.6) is active */
    IOPORT.PFGSPI.BIT.MOSIE = 1 ;
	
    IOPORT.PFGSPI.BIT.MISOE = 1 ;
    /* Set up chip select pin */
   	PORTC.DDR.BIT.B1 = 1 ;
    /* Set level to active */
    PORTC.DR.BIT.B1 = 0 ;
   
    /* MISO as an input */
    PORTC.DDR.BIT.B7 = 0 ;
    /* Enable input buffer for peripheral */
    PORTC.DR.BIT.B7 = 0 ;
    PORTC.ICR.BIT.B7 = 1;
	
	
    /* MOSI as an output */
    PORTC.DDR.BIT.B6 = 1 ;
    /* Enable input buffer for peripheral */
    PORTC.DR.BIT.B6 = 1 ;

    /* SCK as an output */
    PORTC.DDR.BIT.B5 = 1 ;
    /* Set level to inactive */
    PORTC.DR.BIT.B5 = 1 ;
    
    /* Initialize SPI (per flowchart in hardware manual) */
    /* No loopback, CMos Output */
    RSPI0.SPPCR.BYTE = 0x00 ;
    /* Full Speed is 0x00  255 works */
    //RSPI0.SPBR.BYTE = 0x00 ;
	RSPI0.SPBR.BYTE = 0x01; //0x05 - // 2.67 MBPS
    /* 16-bit data 1 frame 1 chip select */
    RSPI0.SPDCR.BYTE = 0x00 ;
    /* 2 clock delay before next access to SPI device */
    RSPI0.SPCKD.BYTE = 0x00 ;
    /* 2 clock delay after de-asserting SSL */
    RSPI0.SSLND.BYTE = 0x00 ;
    /* 2 clock delay before next access to SPI device */
    RSPI0.SPND.BYTE = 0x00 ;
    /* No parity no idle interrupts */
    RSPI0.SPCR2.BYTE = 0x00 ;
    /* MSB first 8-bit data, keep SSL low */
    RSPI0.SPCMD0.WORD = 0x0700 ;
         
	/* Enable RSPI 3wire in master mode with RSPI Enable Transmit Receive and Interupt */  
	RSPI0.SPCR.BYTE = 0xE8 ;
	
	/* SSL3A Polarity */
    RSPI0.SSLP.BYTE = 0x04 ;
    /* One frame. */
    RSPI0.SPSCR.BYTE = 0x00 ;
	
	
	/* Configure External interrupt */
	IOPORT.PF8IRQ.BIT.ITS13 = 0;
	
	ICU.IER[9].BIT.IEN5 = 0;
	
	/* Interrupt as an input */
    PORT5.DDR.BIT.B5 = 0 ;
    /* Enable input buffer for interrupt */
    PORT0.DR.BIT.B5 = 1 ;
    PORT0.ICR.BIT.B5 = 1;
	ICU.IRQCR[13].BIT.IRQMD = 0x00; //0x2 - raising edge
	ICU.IR[77].BIT.IR=0;

	ICU.IPR[0x2D].BIT.IPR = 0xe; //1111 is highest
	ICU.IER[9].BIT.IEN5 = 1;

	xSemaphoreGive(spi_mutex);
	
}

unsigned char DST_JUNK;
unsigned char SRC_JUNK = 0xff;

volatile unsigned int tx_int_count = 0;
volatile unsigned int rx_int_count = 0;


uint32_t glbl_cnt = 0;

void SPI_MasterTransceiveByte(uint8_t *src_data, uint8_t *dst_data,
                              uint32_t len)
{    
	xSemaphoreTake(spi_mutex, portMAX_DELAY);

	unsigned int bit_count = 0;

	rx_buf = 0;
	glbl_count = 0;
	src_junk_flag = 0;
	dst_junk_flag = 0;
	spi_data_reg.TX_DATA = NULL;
	spi_data_reg.len = 0;
	tx_int_count = 0;
	rx_int_count = 0;
	glbl_flag1 = 0;
	intr = 0;
	  
	  
	  if(src_data != NULL)
	  {
		spi_data_reg.TX_DATA = &src_data[0];	
	  }
	  else
	  {
	    spi_data_reg.TX_DATA = &junk_buf[0]; 	  
	  }
	  if(dst_data != NULL)
	  {
	     msg_string  = dst_data;
		 		  
	  }
	  else
	  {
	    msg_string = &junk_buf[0];
		dst_junk_flag = 1;	  
	  }

	
	glbl_count = 0;
	spi_data_reg.len = len; 
	

	if(spi_data_reg.len)
	{
	 	for (bit_count=0; bit_count < spi_data_reg.len; bit_count++)
	 	{	 
			while (RSPI0.SPSR.BIT.IDLNF) ;
		
    			/* short 16 bits */
    			RSPI0.SPDR.WORD.H = *(spi_data_reg.TX_DATA + bit_count);
    			/* Wait for transfer to complete */
    			while (RSPI0.SPSR.BIT.IDLNF) ;		

			if(RSPI0.SPCR.BIT.TXMD == 0)
			{			
				if(RSPI0.SPSR.BIT.OVRF == 0)
				{
					*(msg_string + bit_count) = RSPI0.SPDR.WORD.H;
				}
				else
				{
					TEMP_RDR = (uint8_t)RSPI0.SPDR.WORD.H;
					RSPI0.SPSR.BIT.OVRF = 0;
					break;
				}
			}
		}
	}

	xSemaphoreGive(spi_mutex);
	
   }



