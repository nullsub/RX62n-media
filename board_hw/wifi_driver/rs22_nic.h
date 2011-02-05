/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : RS22
Module name  : SPI driver
File Name    : rs22_nic.h

File Description:


Author :

Rev History:
Ver  By         date          Description
---------------------------------------------------------
1.1 Redpine Signals
--------------------------------------------------------
*END**************************************************************************/
#ifndef __RS22_NIC__
#define __RS22_NIC__

#include "includes.h"

#define   NEW_FIRMWARE						1 // 0 - Old firmware & 1 - New firmware
#define   LITTLE_ENDIAN						1 // 0 - Big-endian & 1 - Little-endian
#define	  SPI_MODE							0 // 0 - Normal speed & 1 - High Speed Mode
#define	  USE_NO_DMA						1 // 0 - USE DMA for all transfer
											  // 1 - USE DMA only for data pkt transfer
#define   BOOT_LOAD							1
#define   LEVEL_TRIGGERED					0


//#define   CALC_THRUPUT						0 // 0 - Throughput not required & 1 - required throughput

#define   MAX_TABLE_ENTRY					32  //Maximum Table entries

#define   MAX_APP_ID_ENTRIES				16  //Maximum number of application ID entries

#define   RSI_PROTO_TCP						0   //We can define enumerated data type also
#define   RSI_PROTO_UDP						1
#define   RSI_PROTO_LTCP					2

#define   RSI_PROTO_UDP_OFFSET 				42
#define   RSI_PROTO_TCP_OFFSET 				54

#define   RSI_HEADER_SIZE                   14
#define   RSI_RCV_BUFFER_LEN                1600

#define   TRUE   1
#define   FALSE  0
#define   OUT
#define   IN
#define   RS22_STATUS_FAILURE              -1
#define   RS22_STATUS_SUCCESS               0
#define   RS22_FW_UPGRADE_SUCCESS           2
#define   RS22_STATUS                       int32_t

#define   RSI_STATUS_SUCCESS                0
#define   RSI_STATUS_BUSY                   1
#define   RSI_STATUS_FAIL                  -1


#define   TRUE                              1
#define   FALSE                             0
#define   FRAME_DESC_SZ                     16
#define   MGMT_FRAME_DESC_SZ                16
#define   MAX_PAYLOAD_SIZE 					1400
/*Queue Addresses */
#define   RCV_LMAC_MGMT_Q                   0x01
#define   RCV_DATA_Q                        0x02
#define   RCV_TA_MGMT_Q                     0x04

#define   SND_MGMT_Q                        0x1
#define   SND_DATA_Q                        0x2
#define   SND_TA_MGMT_Q                     0x4

#if BOARD == EVK1105
	#define RS21_SPI					    	WEXPANSION_SPI
	#define RS21_SPI_NPCS			      		WEXPANSION_SPI_NPCS
	#define RS21_SPI_SCK_PIN					WEXPANSION_SPI_SCK_PIN
	#define RS21_SPI_SCK_FUNCTION				WEXPANSION_SPI_SCK_FUNCTION
	#define RS21_SPI_MISO_PIN					WEXPANSION_SPI_MISO_PIN
	#define RS21_SPI_MISO_FUNCTION				WEXPANSION_SPI_MISO_FUNCTION
	#define RS21_SPI_MOSI_PIN					WEXPANSION_SPI_MOSI_PIN
	#define RS21_SPI_MOSI_FUNCTION				WEXPANSION_SPI_MOSI_FUNCTION
	#define RS21_SPI_NPCS_PIN					WEXPANSION_SPI_NPCS_PIN
	#define RS21_SPI_NPCS_FUNCTION				WEXPANSION_SPI_NPCS_FUNCTION
#elif BOARD == EVK1100
	#define SPARE_SPI                   		(&AVR32_SPI0)
	#define SPARE_SPI_NPCS              		0
	#define SPARE_SPI_SCK_PIN           		AVR32_SPI0_SCK_0_0_PIN
	#define SPARE_SPI_SCK_FUNCTION      		AVR32_SPI0_SCK_0_0_FUNCTION
	#define SPARE_SPI_MISO_PIN          		AVR32_SPI0_MISO_0_0_PIN
	#define SPARE_SPI_MISO_FUNCTION     		AVR32_SPI0_MISO_0_0_FUNCTION
	#define SPARE_SPI_MOSI_PIN          		AVR32_SPI0_MOSI_0_0_PIN
	#define SPARE_SPI_MOSI_FUNCTION    			AVR32_SPI0_MOSI_0_0_FUNCTION
	#define SPARE_SPI_NPCS_PIN          		AVR32_SPI0_NPCS_0_0_PIN
	#define SPARE_SPI_NPCS_FUNCTION    			AVR32_SPI0_NPCS_0_0_FUNCTION

	#define RS21_SPI			      			SPARE_SPI
	#define RS21_SPI_SCK_PIN		      		SPARE_SPI_SCK_PIN
	#define RS21_SPI_SCK_FUNCTION		      	SPARE_SPI_SCK_FUNCTION
	#define RS21_SPI_MISO_PIN		      		SPARE_SPI_MISO_PIN
	#define RS21_SPI_MISO_FUNCTION		      	SPARE_SPI_MISO_FUNCTION
	#define RS21_SPI_MOSI_PIN		      		SPARE_SPI_MOSI_PIN
	#define RS21_SPI_MOSI_FUNCTION		      	SPARE_SPI_MOSI_FUNCTION
	#define RS21_SPI_NPCS_PIN		      		SPARE_SPI_NPCS_PIN
	#define RS21_SPI_NPCS_FUNCTION		      	SPARE_SPI_NPCS_FUNCTION
	#define RS21_SPI_NPCS			      		SPARE_SPI_NPCS
#endif
//USART0-CTS pin is used as interrupt line
#define RS21_SPI_INT_PIN                    AVR32_EIC_EXTINT_5_PIN
//Function B on GPIO 4 line will act as a EXTINT
#define RS21_SPI_INT_FUNCTION               AVR32_EIC_EXTINT_5_FUNCTION

#define RS21_SPI_INT                        AVR32_EIC_INT5

#define AVR32_PDCA_PID_SPI_TX       		AVR32_PDCA_PID_SPI0_TX
#define AVR32_PDCA_PID_SPI_RX       		AVR32_PDCA_PID_SPI0_RX
#define PDCA_CHANNEL_RS22_TX		  		0
#define PDCA_CHANNEL_SPI_RX	 	  			1

/* SDIO_FUN1_FIRM_LD_CTRL_REG register bits */
#define   BIT(n)                  			(1 << (n))

#define   TA_SOFT_RST_CLR             0
#define   TA_SOFT_RST_SET             BIT(0)

#define   SD_WAKEUP_INDCN             (1<<5)
#define   SD_SLEEP_INDCN              (1<<4)
#define   SD_DATA_PENDING             (1<<3)
#define   SD_MGMT_PENDING             (1<<2)
#define   SD_PKT_BUFF_EMPTY           (1<<1)
#define   SD_PKT_BUFF_FULL            (1<<0)
#define   RSI_MAC_ADDR_LEN            6

#define   MAX_SPI_PKT_SIZE            1600
#define   CMD_INITIALIZATION          0x15
#define   CMD_READ_WRITE              0x40
#define   CMD_WRITE                   0x20
#define   AHB_BUS_ACCESS              0x10
#define   AHB_SLAVE                   0x08
#define   TRANSFER_LEN_16_BITS        0x04
#define   WRITE_READ_32_BIT_GRAN      0x40

#define   SPI_INITIALIZATION          1
#define   SPI_INTERNAL_READ           2
#define   SPI_INTERNAL_WRITE          3
#define   AHB_MASTER_READ             4
#define   AHB_MASTER_WRITE            5
#define   AHB_SLAVE_READ              6
#define   AHB_SLAVE_WRITE             7
#define   SPI_DUMMY_WRITE             8

#define   SPI_STATUS_SUCCESS          0x58
#define   SPI_STATUS_BUSY             0x54
#define   SPI_STATUS_FAILURE          0x52

#define   SSP_START_TOKEN_8           0x55

#define   BIT_GRAN_8                  8


#define   LOBYTE(val)				  (val & 0x00ff)
#define   HIBYTE(val)				  ((val & 0xff00) >> 8)

#if	LITTLE_ENDIAN
	#define  CPU_TO_LE16(val)             (val)
	#define  CPU_TO_LE32(val)             (val)
	#define  LE32_TO_CPU(val)             (val)
	#define  LE16_TO_CPU(val)             (val)
#else
	#define  CPU_TO_LE16(val)             (((((uint16_t)(val)) & 0xFF00) >>  8) | \
										   ((((uint16_t)(val)) & 0x00FF) <<  8))

	#define  CPU_TO_LE32(val)             (((((uint32_t)(val)) & 0xFF000000) >> 24) | \
										   ((((uint32_t)(val)) & 0x00FF0000) >>  8) | \
										   ((((uint32_t)(val)) & 0x0000FF00) <<  8) | \
										   ((((uint32_t)(val)) & 0x000000FF) << 24))

	#define  LE32_TO_CPU(val)             CPU_TO_LE32(val)
	#define  LE16_TO_CPU(val)             CPU_TO_LE16(val)
#endif

#define rs22_memcpy(a,b,c)            memcpy(a,b,c)
#define rs22_memset(a,b,c)            memset(a,b,c)
//#define rs22_memcmp(a,b,c)            memcmp(a,b,c)
#define rs22_strcmp(a,b)              strcmp(a,b)
#define rs22_strcpy(a,b)              strcpy(a,b)
#define rs22_strcat(a,b)              strcat(a,b)
#define rs22_strncpy(a,b,c)           strncpy(a,b,c)
#define rs22_equal_string(a,b)        strcmp(a,b)

typedef enum {
  BUFFER_FULL   = 0X1,
  BUFFER_FREE   = 0X2,
  MGMT_PENDING  = 0X3,
  DATA_PENDING  = 0X4,
  SLEEP_INDCN   = 0X5,
  WAKEUP_INDCN  = 0x6,
  UNKNOWN       = 0XB
} INTERRUPT_TYPE;

#define rs22_get_interrupt_type(_I)              \
                (_I & ( SD_PKT_BUFF_FULL)) ?        \
                BUFFER_FULL :\
                        (_I & (SD_PKT_BUFF_EMPTY)) ?       \
                        BUFFER_FREE :\
                                (_I & (SD_MGMT_PENDING)) ?         \
                                MGMT_PENDING:\
                                        (_I & (SD_DATA_PENDING)) ? \
                                        DATA_PENDING: \
                                        (_I & (SD_SLEEP_INDCN)) ? \
                                        SLEEP_INDCN: \
                                        (_I & (SD_WAKEUP_INDCN)) ? \
                                        WAKEUP_INDCN: UNKNOWN



struct bus_cmd_s
{
  uint16_t  type;
  uint16_t  length;
  void    *data;
  uint32_t  address;
};

struct cmd_fmt_s
{
  uint8_t  buf[4];
};

typedef enum
{
	E_TCP_CMD_Configure	 = 0x01,
	E_TCP_CMD_Socket	 = 0x02,
	E_TCP_CMD_Send  	 = 0x03,
	E_TCP_CMD_Close 	 = 0x04,
	E_TCP_RSSI_Query     = 0x05,
	E_TCP_CONSTATUS_Query = 0x07
	
}TCP_CMD_SUB_TYPE;

typedef enum {
	SOCKET_TCP = 0, //TCP Client
	SOCKET_UDP = 1, //UDP Client
	SOCKET_LTCP = 2 //TCP Server (Listening TCP)
}SOCKET_TYPE;

#define MGMT_LOAD_IMAGE_UPGRADER	     		0x1600
#define MGMT_LOAD_SOFT_BOOTLOADER	     		0x1700
#define LOAD_SB_TADM2                           0x2100

#define MGMT_DESC_TAIM1_DONE_RESPONSE    		0x9100
#define MGMT_DESC_TAIM2_DONE_RESPONSE    		0x9200
#define MGMT_DESC_TADM_DONE_RESPONSE     		0x9300

#define MGMT_UPGRADE_FF_TAIM1                   0x1300
#define MGMT_UPGRADE_FF_TAIM2                   0x1400
#define MGMT_UPGRADE_FF_TADM                    0x1500


#define RSI_DESC_LEN                            16
#define RSI_DESC_QUEUE_NUM_MASK  				0x7
#define RSI_DESC_AGGR_ENAB_MASK  				0x80

#define MGMT_DESC_TYP_CARD_RDY_IND          	0x8900
#define MGMT_DESC_INIT_RESPONSE             	0x9400
#define MGMT_DESC_SCAN_RESPONSE             	0x9500
#define MGMT_DESC_JOIN_RESPONSE             	0x9600
#define MGMT_DESC_PROG_PS_CNF                   0x8500
#define MGMT_DESC_RS22_WAKEUP                   0x8A00
#define MGMT_DESC_SLP                           0x9A00

#define MGMT_DESC_RS22_SCAN                  	0x1100
#define MGMT_DESC_RS22_INIT                  	0x1000
#define MGMT_DESC_RS22_JOIN                  	0x1200
#define MGMT_DESC_RS22_PWSAVE                   0x1900
#define MGMT_DESC_RS22_PWR                      0x0200
#define MGMT_DESC_PS_SLP                        0x0500



/* Structure for sending Scan request */
struct WiFi_CNFG_Scan_t
{
  uint32_t uChannelNo;
  uint8_t  uSSID[32];
  uint8_t  pshk[32];
};//__attribute__ ((packed));

/*
 * Following structure instance would be a container of an AP information.
 * Multiple instances of the same gives the complete scan response, which
 * we can see in 'WiFi_CNFG_ScanRsp' structure
 */
struct WiFi_CNFG_ScanInfo
{
  uint8_t uChannelNumber;
  uint8_t uSecMode;
  uint8_t uRssiVal;
  uint8_t uSSID[32];
};//__attribute__ ((packed));

/*
 * Instance of the following structure gives the complete Scan Response
 * information, which gives the number of Access Points that were scanned,
 * Error code, if any and each AP information
 */
struct WiFi_CNFG_ScanRsp
{
  uint32_t uScanCount;
  uint32_t uErrorcode;
  struct WiFi_CNFG_ScanInfo stScanInfo[32];
};//__attribute__ ((packed)) ;

/* Structure for sending Join request */
struct WiFi_CNFG_Join_t
{
  uint8_t uNwType;
  uint8_t uSecType;
  uint8_t uDataRate;
  uint8_t uPowerlevel;
  uint8_t uPSK[32];
  uint8_t uSSID[32];
  uint8_t uIbss_mode;
  uint8_t uChannel;
  uint8_t uAction;
};//__attribute__((packed));;

/*
 * Structure for Join Response. Currently not used any where in the code
 * In future it may be useful
 */
struct WiFi_CNFG_JoinRsp
{
  uint8_t  uSSID[32];
  uint16_t uErrorCode;
};//__attribute__((packed));
/*
 * Combining Init, Scan and Join request frames in one single structure
 * and each frame is preceded by a 16 byte descriptor
 */
typedef struct WiFi_CNFG_powerSave_t
{
  uint8_t uPower_mode;
	
}WiFi_CNFG_powerSave_t;

struct RSI_Mac_frame_t{

  uint16_t descriptor[8];

  union {
    struct WiFi_CNFG_Scan_t Scan;
    struct WiFi_CNFG_Join_t Join;
	WiFi_CNFG_powerSave_t   Power_mode;
  }frameType;

};//__attribute__ ((packed));



/*
 * Following is the structure of TCP/IP Configure command
 */
struct TCP_CNFG_Configure
{
  uint16_t descriptor[9];

  uint8_t uUseDHCP;
  uint8_t uIPaddr[4];
  uint8_t uNetMask[4];
  uint8_t uDefaultGateway[4];
};//__attribute__ ((packed));

/*
 * Following is the structure of the TCP/IP Configure command's response
 */

/*
 * Structure to store an IP address
 */
struct in_addr1
{
  uint8_t s_addr[4];
};//__attribute__ ((packed));

/*
 * Structure to store remote application's logical address
 * (IP address of the destination machine & Port number of the application
 * on the destination machine)
 */
struct sockaddr_in
{
  uint16_t sin_port; /* Destination application's port number */
  struct in_addr1 sin_addr; /* Destination's IP address */
};//__attribute__ ((packed));

/*
 * Structure of Socket command to create TCP Client, UDP Client or
 * Listening TCP (TCP Server)
 */
struct TCP_CNFG_Socket
{
  uint16_t descriptor[9];

  uint16_t uSocketType; /* Type of the socket. 0 -  TCP Client, 1 - UDP Client, 2 - TCP Server */
  uint16_t stLocalPort; /* Local port on which the socket has to be found */
  struct sockaddr_in stRemoteAddress; /* Destination application's address (IP address & Port no) */
};//__attribute__ ((packed));

/*
 * Structure of Socket command's response
 */
struct TCP_CNFG_Socket_Resp
{
  uint16_t uSocketType; /* Created socket type as mentioned above */
  uint16_t uSocketDescriptor; /* Created Socket's Descriptor */
  struct sockaddr_in stLocalAddress; /* The local IP address and the port number
										on which the socket is created */
  uint16_t uErrorCode; /* 0 - Success, 1 - Failure */
};//__attribute__ ((packed));

/*
 * Structure of Socket close command
 */
struct TCP_CNFG_Close
{
  uint16_t descriptor[9];

  uint16_t uSocketDescriptor; /* Socket Descriptor to be closed */
};

/*
 * Structure of Socket close command's response
 */
struct TCP_CNFG_Close_Resp
{
  uint16_t uSocketDescriptor; /* Closed Socket Descriptor */
  uint16_t uErrorCode; 		/* 0 - Success, 1 - Failure */
};//__attribute__ ((packed));

/*
 * Following is the structure of the Send command
 */
struct TCP_CNFG_Send
{
  uint16_t descriptor[9];

  uint16_t uSocketDescriptor; /* Socket Descriptor Created */
  uint32_t uBufferLength; /* Length of the data sent */
  uint16_t uDataOffset; /* Offset of the data in the buffer */
  uint8_t  uBuffer[MAX_PAYLOAD_SIZE]; /* Buffer comprising the data payload */
};//__attribute__ ((packed));

/*
 * Following is the data structure for the send response
 */
struct TCP_CNFG_Send_Resp
{
  uint16_t uSocketDescriptor; /* Socket Descriptor Created */
  uint32_t uBufferLength; /* Length of the data sent */
  uint16_t uErrorCode; /* 0 - Success , 1 - Failure */
};//__attribute__ ((packed));

struct RSSI_QUERY_Req
{
  uint16_t descriptor[9]; 
};

struct WLAN_CONN_Query_Req
{
  uint16_t descriptor[9]; 
};
/*
 * Structure of the Data receive event
 */
 

struct sock_table_t
{
	int32_t sockd;
	int32_t apid;
	int16_t prototype;
	int32_t sock_status;
};//__attribute__ ((packed));


extern struct sock_table_t gsock_table[MAX_TABLE_ENTRY];
typedef struct stRemoteAdress_s
{
	 uint16_t sinPort;
     uint8_t  ip[4];
}stRemoteAdress_t;

typedef struct networkConfig_s
{
  uint16_t uSocketType;
  uint16_t stLocalPort; 
  uint16_t uSocketDescriptor;
  stRemoteAdress_t remote_address;
  
}networkConfig_t;

int32_t            	rs22_send_ta_load_cmd(uint8_t *data,uint32_t size,uint32_t address);
int32_t            	rs22_send_ta_read_cmd(uint8_t *data,uint32_t size,uint32_t address);
int32_t            	rs22_send_ta_sft_rst_cmd(uint32_t val);
uint32_t            rs22_send_ssp_wakeup_cmd_read();
uint32_t            rs22_send_ta_config_params_cmd(uint8_t *data,uint32_t size,uint32_t address);
uint32_t            rs22_wakeup_reg_write();
uint32_t		  	rs22_send_ssp_wakeup_cmd(IN uint8_t byte);
uint32_t		  	rs22_send_dummy_write(IN uint8_t byte);
uint32_t 			rs22_send_ssp_mode_set(IN uint8_t byte);
uint32_t 			rs22_send_ssp_mode_read();
uint32_t 			rs22_set_high_speed_mode();
#if BOOT_LOAD
int32_t  			rs22_load_instructions(uint16_t sb);
int32_t            	rs22_load_TA_instructions(uint8_t i);
#endif
RS22_STATUS     	rs22_send_TA_mgmt_frame(uint8_t frame[],uint32_t len);
RS22_STATUS     	rs22_send_data_frame(uint8_t frame[],uint32_t len);
RS22_STATUS     	rs22_card_write(uint8_t *pkt,uint32_t Len,uint32_t queueno); //should be declared in rs22_mgmt.h
RS22_STATUS     	rs22_send_mgmt_frame(uint8_t frame[],uint32_t len); // should be declared in rs22_mgmt.h
int32_t 			rs22_ssp_bus_request_synch(struct bus_cmd_s *cmd);
int32_t 			rs22_spi_init(void);
int32_t      		rs22_ssp_receive_start_token();
void        		rs22_ssp_send_and_receive(uint8_t *, uint8_t *, uint32_t);
void        		rs22_ssp_send_junk_and_receive(uint8_t *, uint32_t);
void        		rs22_ssp_send_and_receive_junk(uint8_t *, uint32_t);
void        		rs22_ssp_send_and_receive_with_dma(uint8_t *, uint8_t *, uint32_t);
void        		rs22_ssp_send_junk_and_receive_with_dma(uint8_t *, uint32_t);
void        		rs22_ssp_send_and_receive_junk_with_dma(uint8_t *, uint32_t);













#endif
