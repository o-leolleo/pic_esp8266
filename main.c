#include <16F876A.h>
#fuses HS,NOLVP,NOWDT,NOPUT,PROTECT,NOBROWNOUT,DEBUG,NOCPD
#device ADC=10
#use delay(clock = 20000000)
#include <string.h>
#include <registers.h>
#include <timer1.h>
#include <USART.h>

int send_data_en = 0, cont = 0;

int main()
{
        char msg[] = { "essa mensagem nao possui o menor sentido... opa opa opa opa opa opa \r\n\0" };
        
	USART_config();
	
	timer1_config();
	timer1_set_start_value();
	timer1_enable();
        
        while(true) {
		if (send_data_en) {
			USART_send_string(msg);	
			send_data_en = 0;
		}
	}
}

#int_timer1
void isr_timer1()
{
	cont++;

	if (cont >= 30) {
		send_data_en = 1;
		cont = 0;
	}
	PIR1 &= ~1;
}
