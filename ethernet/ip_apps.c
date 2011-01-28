
#include "ip_apps.h"

void init_apps( void ){
	telnetd_init();
	return;
}


void ip_appcall(void){
	switch(uip_conn->lport) {
	case HTONS(23):
		telnetd_appcall();
		 break;
	}
}
