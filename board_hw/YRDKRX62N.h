/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corp. and is
* only intended for use with Renesas products.  

* No other uses are authorized.

* This software is owned by Renesas Electronics Corp. and is 
* protected under the applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH
* WARRANTIES ARE EXPRESSLY DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER 
* RENESAS ELECTRONICS CORP. NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR AND DIRECT, INDIRECT, SPECIAL, INCIDENTAL
* OR COSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE,
* EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE
* POSSIBILITIES OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue availability of this software.
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
*******************************************************************************/
/* Copyright (C) 2010. Renesas Electronics Corp., All Rights Reserved         */
/******************************************************************************
* File Name     : YRDKRX62N.h
* Version       : 1.1
* Device(s)     : R5F562N8
* Tool-Chain    : Renesas RX Standard Toolchain 1.0.1
* OS            : None
* H/W Platform  : YRDKRX62N
* Description   : Board-specific definitions
*******************************************************************************
* History : DD.MMM.YYYY     Version     Description
*         : 08.Oct.2010     1.00        First release
*         : 02.Dec.2010     1.10        Second YRDK release
*******************************************************************************/

#ifndef YRDKRX62N_H
#define YRDKRX62N_H

/* Local defines */
#define LED_ON              (1)
#define LED_OFF             (0)
#define SET_BIT_HIGH        (1)
#define SET_BIT_LOW         (0)
#define SET_BYTE_HIGH       (0xFF)
#define SET_BYTE_LOW        (0x00)

// I/0 port 2
#define USB0_EXICEN         PDL_IO_PORT_2_1
#define USB_DPUPEA          PDL_IO_PORT_2_3
#define USB_VBUSEN          PDL_IO_PORT_2_4

// I/O port 3
#define CAN_WIFI_TX         PDL_IO_PORT_3_2   

// I/O port 4: switches and various peripherals 
#define SW_ACTIVE FALSE
#define SW1                 PDL_IO_PORT_4_0  
#define SW2                 PDL_IO_PORT_4_1   
#define SW3                 PDL_IO_PORT_4_2   
#define JN1_AN3             PDL_IO_PORT_4_3
#define POTENTIOMETER       PDL_IO_PORT_4_4
#define MICROPHONE          PDL_IO_PORT_4_5
#define AUDIO_IN_R          PDL_IO_PORT_4_6
#define PWMLP_IN            PDL_IO_PORT_4_7

// I/O port 5 
#define LCD_RS              PDL_IO_PORT_5_0
#define LCD_A0              PDL_IO_PORT_5_1
#define BCLK                PDL_IO_PORT_5_3
#define PWMLP_OUT           PDL_IO_PORT_5_4
#define AMP_SHDN            PDL_IO_PORT_5_5

// I/O port A:  Extension slot (JN2) and E/N pins
#define JN2_SSLA1_B         PDL_IO_PORT_A_0
#define JN2_SSLA2_B         PDL_IO_PORT_A_1
#define JN2_SSLA3_B         PDL_IO_PORT_A_2
#define ETH_MDIO            PDL_IO_PORT_A_3
#define ETH_MDC             PDL_IO_PORT_A_4
#define ETH_LINK            PDL_IO_PORT_A_5
#define AUDIO_OUT_R         PDL_IO_PORT_A_6
#define AUDIO_OUT_L         PDL_IO_PORT_A_7

// I/O port B:  Ethernet I/O pins definitions
#define RMII_RXD1           PDL_IO_PORT_B_0
#define RMII_RXD0           PDL_IO_PORT_B_1
#define ETH_CLK             PDL_IO_PORT_B_2
#define RMII_RX_ER          PDL_IO_PORT_B_3
#define RMII_TX_EN          PDL_IO_PORT_B_4        
#define RMII_TXD0           PDL_IO_PORT_B_5        
#define RMII_TXD1           PDL_IO_PORT_B_6    
#define ETH_CRS             PDL_IO_PORT_B_7

// I/O port C:  RSPI and peripheral I/O pins definitions
#define RSPI_CHANNEL_0      0
#define RSPI_CHANNEL_1      1
#define FLASH_CS            PDL_IO_PORT_C_0        // SSL 1
#define WIFI_CS             PDL_IO_PORT_C_1        // SSL 2
#define LCD_CS              PDL_IO_PORT_C_2        // SSL 3
#define LCD_RESET           PDL_IO_PORT_C_3         
#define SDMICRO_CS          PDL_IO_PORT_C_4        // SSL 0
#define RSPI_SCLOCK         PDL_IO_PORT_C_5        
#define RSPI_MOSI           PDL_IO_PORT_C_6        
#define RSPI_MISO           PDL_IO_PORT_C_7

// I/O ports D & E:  LEDs
#define LED4                PDL_IO_PORT_D_5
#define LED5                PDL_IO_PORT_E_3
#define LED6                PDL_IO_PORT_D_2     
#define LED7                PDL_IO_PORT_E_0
#define LED8                PDL_IO_PORT_D_4
#define LED9                PDL_IO_PORT_E_2
#define LED10               PDL_IO_PORT_D_1
#define LED11               PDL_IO_PORT_D_7
#define LED12               PDL_IO_PORT_D_3
#define LED13               PDL_IO_PORT_E_1
#define LED14               PDL_IO_PORT_D_0
#define LED15               PDL_IO_PORT_D_6

#endif