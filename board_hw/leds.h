/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : 
Module name  :
File Name    : leds.h

File Description:
    

Author :

Rev History:
Ver   By               date        Description
---------------------------------------------------------
1.1   Redpine Signals
---------------------------------------------------------
*/

#ifndef _PUSH_BUTTON_H_
#define _PUSH_BUTTON_H_

#include "typedefine.h"
#include "includes.h"


extern int16_t       SockHandle0;
extern int16_t       SockHandle1;

/* LED related defines statr */

#define LED_ADDR  PORTD.DR.BYTE

#define LED1    PORTD.DR.BIT.B0
#define LED2    PORTD.DR.BIT.B1
#define LED3    PORTD.DR.BIT.B2
#define LED4    PORTD.DR.BIT.B3
#define LED5    PORTD.DR.BIT.B4
#define LED6    PORTD.DR.BIT.B5
#define LED7    PORTD.DR.BIT.B6
#define LED8    PORTD.DR.BIT.B7
#define LED9    PORTE.DR.BIT.B0
#define LED10   PORTE.DR.BIT.B1
#define LED11   PORTE.DR.BIT.B2
#define LED12   PORTE.DR.BIT.B3
 

#define LED1_DDR    PORTD.DDR.BIT.B0
#define LED2_DDR    PORTD.DDR.BIT.B1
#define LED3_DDR    PORTD.DDR.BIT.B2
#define LED4_DDR    PORTD.DDR.BIT.B3
#define LED5_DDR    PORTD.DDR.BIT.B4
#define LED6_DDR    PORTD.DDR.BIT.B5
#define LED7_DDR    PORTD.DDR.BIT.B6
#define LED8_DDR    PORTD.DDR.BIT.B7

#define LED9_DDR     PORTE.DDR.BIT.B0
#define LED10_DDR    PORTE.DDR.BIT.B1
#define LED11_DDR    PORTE.DDR.BIT.B2
#define LED12_DDR    PORTE.DDR.BIT.B3

 

#define LED_ON      0
#define LED_OFF     1

#define ALL_LEDS_ON      {LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=LED9=LED10=LED11=LED12=LED_ON;}
#define ALL_LEDS_OFF    {LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=LED9=LED10=LED11=LED12=LED_OFF;}
#define ENABLE_LEDS     {LED1_DDR = LED2_DDR = LED3_DDR = LED4_DDR=LED5_DDR=LED6_DDR=LED7_DDR= LED8_DDR = LED9_DDR = LED10_DDR = LED11_DDR = LED12_DDR = 1;}
#define LED_ADDR  PORTD.DR.BYTE


/* LED related defines end */      

#define IS_PUSH_BUTTON_PRESSED (push_button_pressed == 1)
#define CLR_PUSH_BUTTON_FLAG   (push_button_pressed = 0)
#define ENABLE_SW_IRQ enable_push_button_irq()


#define ENABLE_IRQ   enable_irq()	/* enables all maskable interrupts */
#define DISABLE_IRQ	 disable_irq()  /* disables all maskable interrupts */



extern uint8_t tx_switch_buff[5];
extern volatile uint32_t push_button_pressed;

void enable_push_button_irq(void);
#pragma inline_asm disable_irq
void disable_irq(void);

#pragma inline_asm enable_irq
void enable_irq(void);


#endif
