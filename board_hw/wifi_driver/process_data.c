/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : 
Module name  :
File Name    :process_data.c

File Description:
 
List of functions:
    

Author :

Rev History:
Ver   By               date        Description
---------------------------------------------------------
1.1  Redpine Signals
---------------------------------------------------------
*/

#include "includes.h"
#include "process_data.h"
#include "leds.h"
#include "iodefine.h"

/*FUNCTION*********************************************************************
Function Name  : rsi_process_data
Description    : This function processes the remote peer LED request related data
Returned Value : NONE
Parameters     : 

-----------------+-----+-----+-----+------------------------------
Name             | I/P | O/P | I/O | Purpose
-----------------+-----+-----+-----+------------------------------
rx_buf           | X   |     |     |  Remote peer LED request buffer
*END****************************************************************************/

int32_t rsi_process_data(unsigned char *rx_buff)
{
	uint8_t LED_START_PIN = 3;
	
    if (!((rx_buff[0] != LED) || (rx_buff[1] > SET_REQ) || (rx_buff[2] > 2)))
   {
	   if(rx_buff[2] == 0)
	   {
		  LED_START_PIN = 5; 
	   }
	   else if(rx_buff[2] == 2)
	   {
		 LED_START_PIN = 1;
	   }
       if (rx_buff[1] == SET_REQ)
       {
           if (rx_buff[3] == 1) /* switch off LED */
           {
               LED_ADDR |= (0x1 << (LED_START_PIN  + rx_buff[2]));    
			    
		   }
           else if (rx_buff[3] == 0) /* switch on LED */
           {
               LED_ADDR &= (~(0x1 << (LED_START_PIN  + rx_buff[2])));   
			
           }        
       }             
	   rx_buff[3] = (!!(LED_ADDR  & (0x1 << (LED_START_PIN  + rx_buff[2]))));	 
	   rx_buff[1] += 2;
	   return RSI_STATUS_SUCCESS;
   }
   return RSI_STATUS_FAIL;
}
