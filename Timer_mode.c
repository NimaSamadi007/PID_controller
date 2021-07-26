#include "Timer_mode.h"
#include <stdlib.h>

void Timer_start(){
	int end = 0;
	int M = 0, S = 0;
	
	char time_val[] = "00:00";
	
	LCD_clear_screen();
	LCD_send_string(0, 0, "Timer mode: ");
	LCD_send_string(1, 0, time_val);
	
	while(!end){
		S++;
		M += S / 60;
		S %= 60;
		M %= 60;
		// minutes:		
		time_val[0] = 48 + M / 10;
		time_val[1] = 48 + M % 10;
		// seconds:
		time_val[3] = 48 + S / 10;
		time_val[4] = 48 + S % 10;
		LCD_send_string(1, 0, time_val);
		if(M == 1)
			end = 1;
		_delay_ms(1);
	}
	LCD_clear_screen();
	LCD_send_string(0, 0, "Sending to PORTD");
	for(int i = 0; i < 5; i++){
		PORTD = rand() % 256; // random number in mem
		_delay_ms(500);
	}
	
}