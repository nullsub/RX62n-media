/*
*********************************************************************************************************
*                                         BOARD SUPPORT PACKAGE
*
*                            (c) Copyright 2010; Micrium, Inc.; Weston, FL
*
*               All rights reserved. Protected by international copyright laws.
*
*               BSP is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         BOARD SUPPORT PACKAGE
*
*                                              Renesas RX62N
*                                                on the
*                                      RSK-2+RX62N Evaluation Board
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : FGK
*********************************************************************************************************
*/

#include  "iodefine.h"
#include "i2c.h"

#include "FreeRTOS.h"
#include "semphr.h"


static xSemaphoreHandle i2c_mutex;


/*
*********************************************************************************************************
*                                     RENESAS I2C INITIALIZATION
*********************************************************************************************************
*/

void  i2c_init(void)
{


    	i2c_mutex = xSemaphoreCreateMutex();                    /* Request mutex, block until mutex obtained          */
	
	xSemaphoreTake(i2c_mutex,portMAX_DELAY);

    MSTP(RIIC0)            =  0;                 /* enable RIIC channel 0 in module stop register      */

    PORT1.ICR.BIT.B2       =  1;
    PORT1.ICR.BIT.B3       =  1;

    RIIC0.ICCR1.BIT.ICE    =  0;                 /* RIIC0 disabled                                     */
    RIIC0.ICCR1.BIT.IICRST =  1;                 /* RIIC0 internal reset                               */

    for (int dly = 0; dly < 1000000; dly++) {
		__asm("nop");
    }

    RIIC0.ICCR1.BIT.IICRST =  0;                 /* cancel internal reset                              */

    RIIC0.ICSER.BIT.SAR0E  =  0;                 /* Slave addr in SARL0 and SARU0 disabled             */

    RIIC0.ICMR1.BIT.CKS    =  3;                 /* Pclk / 8                                           */
    RIIC0.ICBRL.BYTE       = 0xFD;
    RIIC0.ICBRH.BYTE       = 0xF8;               /* 96kbps operation                                   */

    RIIC0.ICMR3.BIT.ACKWP  =  1;                 /* enable access to the ACKBT bit in ICMR3            */

    RIIC0.ICFER.BIT.TMOE   =  0;                 /* timeout function disabled                          */
    RIIC0.ICFER.BIT.MALE   =  1;                 /* master arbitration lost detection enabled          */

    RIIC0.ICCR1.BIT.ICE    =  1;                 /* RIIC0 enabled                                      */

	xSemaphoreGive(i2c_mutex);                    /* release mutex                                      */
}


/*
*********************************************************************************************************
*                                        BSP_RIIC0_MasterRd
*
* Description: This function reads one or more bytes from an I2C connected device.
*
* Arguments  : addr   is address on the I2C bus of the peripheral
*              p_data is a pointer for storage of the read data
*              len    is the number of bytes to read
*              start  true  generates a start condition at the start of the frame
*                     false generates a re-start condition at the start of the frame
*
*********************************************************************************************************
*/
void  BSP_RIIC0_MasterRd(uint8_t  addr, uint8_t *p_data, uint32_t   len, bool  start)
{
    int32_t    dummy;
    uint8_t  *RxData;
    uint32_t   RxBytesLeft;


    RxData      = p_data;
    RxBytesLeft = len;

	xSemaphoreTake(i2c_mutex,portMAX_DELAY);                    /* Request mutex, block until mutex obtained          */

    if(start == true){                       /* Generate a frame with a start condition            */
                                                
        while (RIIC0.ICCR2.BIT.BBSY == 1);     /* check bus is available                             */

        RIIC0.ICCR2.BIT.ST = 1;                  /* issue a start condition                            */
    } else {
                                                 /* Generate a frame with a re-start condition         */
        while (RIIC0.ICCR2.BIT.BBSY == 0);      /* check bus is busy                                  */
    

        RIIC0.ICCR2.BIT.RS = 1;                  /* issue a re-start condition                         */
        
        while (RIIC0.ICCR2.BIT.RS == 1);        /* wait for completion of re-start                    */
	
    }
    
    
    while (RIIC0.ICSR2.BIT.TDRE == 0);         /* transmit slave address                             */


    RIIC0.ICDRT        = (addr << 1 ) | 0x01;

    while (RIIC0.ICSR2.BIT.RDRF == 0);	          /* check ACK                                          */

    if (RIIC0.ICSR2.BIT.NACKF == 0) {
        if(len > 1) {
            dummy = RIIC0.ICDRR;                 /* ACK ok                                             */

            while (RIIC0.ICSR2.BIT.RDRF == 0);	/* read data                                          */

            while (RxBytesLeft > 2) {
                 RxBytesLeft--;
                *RxData = RIIC0.ICDRR;
                 RxData++;
                 while (RIIC0.ICSR2.BIT.RDRF == 0);
            }

            RIIC0.ICMR3.BIT.WAIT  = 1;           /* enable wait, final byte - 1                        */
            RIIC0.ICMR3.BIT.ACKBT = 1;
           *RxData                = RIIC0.ICDRR;
            RxData++;
        } else {
                                                 /* single byte read */
            RIIC0.ICMR3.BIT.WAIT  = 1;           /* enable wait, dummy read                            */
            RIIC0.ICMR3.BIT.ACKBT = 1;
            dummy                 = RIIC0.ICDRR;
        }
            
        while (RIIC0.ICSR2.BIT.RDRF == 0);
                
        RIIC0.ICSR2.BIT.STOP = 0;                /* read final byte and issue stop condition           */
        RIIC0.ICCR2.BIT.SP   = 1;
       *RxData               = RIIC0.ICDRR;
        RxData++;
        RIIC0.ICMR3.BIT.WAIT = 0;

    } else {

        RIIC0.ICSR2.BIT.STOP = 0;                /* bad ACK                                            */
        RIIC0.ICCR2.BIT.SP   = 1;
        dummy                = RIIC0.ICDRR;
    }

    while (RIIC0.ICSR2.BIT.STOP == 0);

    RIIC0.ICSR2.BIT.NACKF    = 0;

    RIIC0.ICSR2.BIT.STOP     = 0;

	xSemaphoreGive(i2c_mutex);                    /* release mutex                                      */
}


/*
*********************************************************************************************************
*                                        BSP_RIIC0_MasterWr
*
* Description: This function writes one or more bytes to an I2C connected device.
*
* Arguments  : addr   is address on the I2C bus of the peripheral
*              p_data is a pointer to the data to be written
*              len    is the number of bytes to write
*              stop   true  generates a stop condition at the end of the frame
*                     false does not generate a stop condition at the end of the frame
*
*********************************************************************************************************
*/
void  BSP_RIIC0_MasterWr(uint8_t  addr, uint8_t *p_data, uint32_t   len, bool  stop)
{
    int8_t  *TxData;
    uint8_t   TxBytesLeft;


    TxData      = p_data;
    TxBytesLeft = len;

	xSemaphoreTake(i2c_mutex,portMAX_DELAY);                   /* Request mutex, block until mutex obtained          */

    while (RIIC0.ICCR2.BIT.BBSY == 1);         /* check bus is available                             */

    RIIC0.ICCR2.BIT.ST = 1;                      /* issue a start condition                            */

    while (RIIC0.ICSR2.BIT.TDRE == 0);          /* transmit slave address                             */

    RIIC0.ICDRT        = addr << 1;

    while (TxBytesLeft > 0) {
        if (RIIC0.ICSR2.BIT.NACKF == 0) {
            if (RIIC0.ICSR2.BIT.TDRE == 1) {     /* Ack                                                */
                RIIC0.ICDRT = *p_data;           /* Send Data                                          */
                p_data++;
                TxBytesLeft--;
            }

        } else {

            break;                               /* bad Ack                                            */
        }
    }

    if (TxBytesLeft == 0) {
        while (RIIC0.ICSR2.BIT.TEND == 0);     /* All bytes transmitted                              */
    }

    RIIC0.ICSR2.BIT.STOP  = 0;
    if(stop == true){                       /* Send a stop condition                               */
        RIIC0.ICCR2.BIT.SP    = 1;

        while (RIIC0.ICSR2.BIT.STOP == 0) ;
    }

    RIIC0.ICSR2.BIT.NACKF = 0;
    RIIC0.ICSR2.BIT.STOP  = 0;

	xSemaphoreGive(i2c_mutex);                    /* release mutex                                      */
}


