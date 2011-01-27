
#include "ip_apps.h"

void init_apps( void ){
 	//httpd_init(); 
	telnetd_init();
	return;
}


void ip_appcall(void){
	switch(uip_conn->lport) {
	case HTONS(80):
		//httpd_appcall();
		 break;
	case HTONS(23):
		telnetd_appcall();
		 break;
	}
}
