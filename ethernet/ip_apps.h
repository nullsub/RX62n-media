
#ifndef IP_APPS_H
#define IP_APPS_H IP_APPS_H


#include "telnetd.h"
#include "net/uip.h"



void init_apps( void );
void ip_appcall( void );


/* UIP_APPCALL: the name of the application function. This function
   must return void and take no arguments (i.e., C type "void
   appfunc(void)"). */
#define UIP_APPCALL     ip_appcall

#endif
