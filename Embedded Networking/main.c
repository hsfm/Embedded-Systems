
#include "includes.h"
#include <stdio.h>

int main(void)
{			
	set_ddr(WRITE);

	// Pull-Ups aus
	PORTB = 0x00;	

	start_condition();
	
	address_7_write(0x40);		
	
	lcd_init();		
	
	lcd_write(ZEILE_1, 0, "HS-Fulda");	
	lcd_write(ZEILE_2, 0, "Hallo Welt");			

	stop_condition();
	
	return 0;
}
