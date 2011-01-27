
#ifndef IP_APPS_H
#define IP_APPS_H IP_APPS_H


#include "telnetd.h"
#include "dhcpc.h"


typedef struct telnetd_state uip_tcp_appstate_t;
typedef struct dhcpc_state uip_udp_appstate_t;

void init_apps( void );
void ip_appcall( void );


/* UIP_APPCALL: the name of the application function. This function
   must return void and take no arguments (i.e., C type "void
   appfunc(void)"). */

#define UIP_APPCALL     ip_appcall
#define UIP_UDP_APPCALL dhcpc_appcall


#include "net/uip.h"

#endif
