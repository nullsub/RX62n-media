
#include "ip_apps.h"

void init_apps( void ){
	char mac_adress[6];
	mac_adress[0] = configMAC_ADDR0;
mac_adress[1] = configMAC_ADDR1;
mac_adress[2] = configMAC_ADDR2;
mac_adress[3] = configMAC_ADDR3;
mac_adress[4] = configMAC_ADDR4;
mac_adress[5] = configMAC_ADDR5;
		
	dhcpc_init(mac_adress,6);
	telnetd_init();
	return;
}


void ip_appcall(void){
	switch(uip_conn->lport) {
	case HTONS(67):
	case HTONS(68):
	//	dhcpc_appcall();
		break;
	case HTONS(23):
		telnetd_appcall();
		 break;
	}
}
