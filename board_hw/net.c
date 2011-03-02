
#include "FreeRTOS.h"
#include "task.h"


/* Header file includes */
#include "includes.h"
#include "rsi_spi.h"
#include "rsi_api.h"
#include "board.h"
#include "process_data.h"
#include "rsi_util.h"
#include "rsi_nic.h"
#include "network_config.h"
#include "lcd.h"
#include "iodefine.h"



/* Global variables */
networkConfig_t networkConfig;
struct WiFi_CNFG_Scan_t *scan_info = &Adaptor.scan_params;
struct WiFi_CNFG_Join_t *join_info = &Adaptor.join_params;
ipconfig_t *ipConfig = &Adaptor.ipConfig;

volatile uint8_t ps_mode = POWERSAVE_MODE;
int16_t       SockHandle0;
uint8_t       ip_buff[17];
uint8_t       data[200];

/* Extern variable declaration */
extern uint8_t auto_connect_open_ap;


/* Interrupt handler function  // now int inthandler implemented!!!!!
#pragma interrupt (Excep_IRQ13(vect=77))
void __attribute__ ((interrupt)) INT_Excep_IRQ13(void)
{ 

}
*/

void displayInfo( uint8_t type );
static void rsi_configure_device( void );
void debug(char * str);

/*FUNCTION*********************************************************************
Function Name  : main
Description    : This is the main function
Returned Value : NONE
Parameters     : NONE

-----------------+-----+-----+-----+------------------------------
Name             | I/P | O/P | I/O | Purpose
-----------------+-----+-----+-----+------------------------------
*END****************************************************************************/
void wifi_driver_task( void *pvParameters )
{
	int16_t  			rssi_value = 0;
	int32_t  			send_count = 0;
	uint32_t 			size;
	volatile int32_t  val = 0;   

	debug ("start");
	ENABLE_LEDS;
	ALL_LEDS_OFF;
	
	if((rsi_poweron_device()) == RSI_STATUS_FAILURE)
	{
		displayInfo(SPI_INIT_FAILED); 
		vTaskSuspend(NULL); // lets suspend ourself
		while(1);	   
	}
    
   	/* After Data Flash Area is enabled, you can access Data Flash Memory */
	if( FIRMWARE_UPGRADE == ENABLE )
	{
		displayInfo(IMAGE_UPGRADE); 
	}   
	else
	{
		displayInfo(IN_PROGRESS);
	}    
	rsi_configure_device();   

	debug("i am here");

   while(1)
   { 
      if(send_count == 4000000)
	  {
	   val = get_sock_status(SockHandle0);
       if ((val == 1) && (NETWORKTYPE != IBSS))
       {
	       
		   uint16_t index;
		  rsi_wlan_conn_query_req();
       	  if((rssi_value = rsi_send_rssi_query_req()) != RSI_STATUS_FAILURE)
	   	  {
			 /* send the push button status to the client */
			 index = rsi_prepare_pkt_to_send(RSSI, rssi_value, data);

		     while ((rsi_send_data(SockHandle0, index, data)) != RSI_STATUS_SUCCESS)
             {
	           /* Do some thing here */
			   ;

	         } 	
			if( ps_mode == 1)
			{
			  rsi_send_sleep_request();	 
			}
	   	  }
		
	   }
		send_count = 0;
	  }
	  send_count++;
	 
	   /* Process the pending interrupts */   
	   if(Adaptor.pkt_received > 0)
	   { 
  		 rsi_interrupt_handler(Adaptor.RcvPkt, &size);
	   }	  
   }
}

void debug(char * str){
		/* De-Assert the CS for spi device - WIFI */
    PORTC.DR.BIT.B1 = 1 ;	
  PORTC.DR.BIT.B2 = 0	  ;
	lcd_string(LCD_LINE7,0 ,str);
	/* Re-Assert the CS for spi device - WIFI */
  PORTC.DR.BIT.B2 = 1	  ;
    PORTC.DR.BIT.B1 = 0 ;	
}

/*FUNCTION*********************************************************************
Function Name  : rsi_configure_device
Description    : This function is used to configure the wlan device 
Returned Value : NONE
Parameters     : NONE

-----------------+-----+-----+-----+------------------------------
Name             | I/P | O/P | I/O | Purpose
-----------------+-----+-----+-----+------------------------------

*END****************************************************************************/

static void rsi_configure_device( void )
{
	int16_t		status;	
	
   /* Get the configuration type (WIFI or DEFAULT )*/  
   scan_info->uChannelNo  =  SCAN_CHANNEL;  
   join_info->uNwType     =  NETWORKTYPE;   
   join_info->uDataRate   =  TX_RATE;       
   join_info->uPowerlevel =  TX_POWER;     
   if((NETWORKTYPE == IBSS) && (AUTO_CONNECT_OPEN_AP == DISABLE))
   {
     join_info->uChannel    =  IBSS_CHANNEL;
	 join_info->uIbss_mode  =  IBSS_MODE;
   }
   /* clear the SSID  */
   rsi_memset(scan_info->uSSID, 0, 32);
   if((SCAN_SSID != NULL) && (AUTO_CONNECT_OPEN_AP != ENABLE))
   {
     /* SSID to Scan  */
      rsi_memcpy(scan_info->uSSID, SCAN_SSID, sizeof(SCAN_SSID));
   }
   /* SSID to join */
   rsi_memcpy(join_info->uSSID, CONNECT_SSID, sizeof(CONNECT_SSID));
   /* clear the SSID  */
   rsi_memset(join_info->uPSK, 0, 32);
   rsi_memcpy(join_info->uPSK, PSK, sizeof(PSK));
   /*If aouto connect feature is enabled we have to scan 
	 in all the channels in broadcast mode */
   if((AUTO_CONNECT_OPEN_AP == ENABLE) && (NETWORKTYPE != IBSS))
   {
     scan_info->uChannelNo = 0;
     /* Initialize wireless lan parameters */
     rsi_memset(join_info->uSSID, 0, 32);
	 auto_connect_open_ap = ENABLE;
	}
    /* Initialize ipconfig parameters */
    rsi_initialize_ipconfig_parmas(ipConfig);
 
    /* Initialize socket creation info */
    rsi_initialize_netwrok_config1(&networkConfig);

    /* RSI initialize device */
debug("starting init");
    status = rsi_init_wlan_device();
debug("finished init");
    if(status != RSI_STATUS_SUCCESS)
    {
	  if(status == RS22_JOIN_FAILURE)
	  {
		LED2  = !LED2;        
	  }
	  displayInfo(JOIN_FAILED);
      while(1);	 	   
	}   
	/* Send the ipconfig request */
	status = rsi_send_ipconfig_request(ipConfig);
	if(status != RSI_STATUS_SUCCESS)

	{
       displayInfo(IPCONF_ERROR);

	   while(1)	;

	}
	rsi_convert_ip_to_string(ipConfig->uIPaddr,ip_buff);
    displayInfo(CONNECT_INFO);
		
	/* Create the first socket */

    SockHandle0 = rsi_create_user_socket(&networkConfig);

	if(SockHandle0 == RSI_STATUS_FAILURE)

	{

	  while(1)	;

	}
	/* Configure the wlan device in power save mode */
	rsi_send_power_save_request( ps_mode );
}

/*FUNCTION*********************************************************************
Function Name  : displayInfo
Description    : This function is used to display messages on the LCD
Returned Value : void
Parameters     : 
-----------------+-----+-----+-----+------------------------------
Name             | I/P | O/P | I/O | Purpose
-----------------+-----+-----+-----+------------------------------
 type            | X    |   |     |  Message type to be displayed on the LCD

*END****************************************************************************/
/* Displays the current connect information to LCD i.e IP address and SSID */
void displayInfo( uint8_t type )
{
	/* De-Assert the CS for spi device - WIFI */
    PORTC.DR.BIT.B1 = 1 ;	
  PORTC.DR.BIT.B2 = 0;
  
	switch(type)
	{
	
       /* SPI initialization faied */
	   case SPI_INIT_FAILED:
	   {
		 //GlyphClearScreen(G_lcd) ;
		lcd_string(LCD_LINE1,0,  "SPI INIT FAILED");
	   }
	   break;
	   /* Upgrading the firmware */
	   case IMAGE_UPGRADE:
	   {
        	 lcd_string(LCD_LINE1,0,  "    FIRMWARE    ");
		 lcd_string(LCD_LINE2,0,  "    UPGRADE     "); 
		 lcd_string(LCD_LINE3,0,  " IN PROGRESS... "); 
	   }
	   break;
	   /* Firmware upgradation completed */
	   case IMAGE_UPGRADE_COMPLETED:
	   {
        	 lcd_string(LCD_LINE1,0,   "    FIRMWARE    ");
		 lcd_string(LCD_LINE2,0,   "    UPGRADE     "); 
		 lcd_string(LCD_LINE3,0,   "   COMPLETED    "); 
	   }
	   break;
	   /* Scanning APs */
	   case IN_PROGRESS:
	   {
         	lcd_string(LCD_LINE1,0,   "SCANNING APs...");
	   }
	   break;
	   /* Scanning APs */
	   case SCAN_OVER:
	   {
         	 lcd_string(LCD_LINE1,0,   " SCAN COMPLETED ");
		 lcd_string(LCD_LINE2,0,   "   CONNECTION   ");
		 lcd_string(LCD_LINE3,0,   " IN PROGRESS... ");
	   }
	   break;
	   case JOIN_OVER:
	   {
		 lcd_string(LCD_LINE1,0,  "   CONNECTED    ");
		 lcd_string(LCD_LINE2,0,  " SENDING IPCONF ");
		 lcd_string(LCD_LINE3,0,  "   REQUEST...   ");
	   }
	   break;
	  /* Association failed */
	   case JOIN_FAILED:
	   {
	     	lcd_string(LCD_LINE1,0,   "  JOIN FAILED   ");
	   }
	   break;
	   /* Ipconfig failed */
	   case IPCONF_ERROR:
	   {
		 lcd_string(LCD_LINE1,0,  "  IPCONF ERROR  "); 
	   }
	   break;
	   /* Display connected AP ssid and ip address    */
	   case CONNECT_INFO:  
	   {
         	 lcd_string(LCD_LINE1,0,   (uint8_t *)join_info->uSSID);
		 lcd_string(LCD_LINE2,0,   ip_buff);
	   }
	   break;
	   /* Reset the board */
	   case RESET:  
	   {lcd_string(LCD_LINE2,0,   "RESET THE BOARD");
		 
	   }
	   break;
	}		   
  PORTC.DR.BIT.B2 = 1	  ;
    /* Assert the CS for spi device - WIFI */
    PORTC.DR.BIT.B1 = 0 ;
		    
}


