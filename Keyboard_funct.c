#include "Keyboard_funct.h"

char read_keyboard(){
	char output = 'f';
		
	PORTB = 0x0E; // 0b0000_1110
	_delay_ms(2); // wait for debouncing:
	if( (PINB & (0x10)) == 0 )
		output = '7';
	if( (PINB & (0x20)) == 0 )
		output = '8';
	if( (PINB & (0x40)) == 0 )
		output = '9';
	if( (PINB & (0x80)) == 0 )
		output = '/';
	
	PORTB = 0x0F;
	
	PORTB = 0x0D; // 0b0000_1110
	_delay_ms(2); // wait for debouncing:
	if( (PINB & (0x10)) == 0 )
		output = '4';
	if( (PINB & (0x20)) == 0 )
		output = '5';
	if( (PINB & (0x40)) == 0 )
		output = '6';
	if( (PINB & (0x80)) == 0 )
		output = '*';

	PORTB = 0x0F;
	
	PORTB = 0x0B; // 0b0000_1110
	_delay_ms(2); // wait for debouncing:
	if( (PINB & (0x10)) == 0 )
		output = '1';
	if( (PINB & (0x20)) == 0 )
		output = '2';
	if( (PINB & (0x40)) == 0 )
		output = '3';
	if( (PINB & (0x80)) == 0 )
		output = '-';
	
	PORTB = 0x0F;

	PORTB = 0x07; // 0b0000_1110
	_delay_ms(2); // wait for debouncing:
	if( (PINB & (0x10)) == 0 )
		output = 'n';
	if( (PINB & (0x20)) == 0 )
		output = '0';
	if( (PINB & (0x40)) == 0 )
		output = '=';
	if( (PINB & (0x80)) == 0 )
		output = '+';
	
	PORTB = 0x0F;
	if(output == '+'){
		Timer_start();
		read_keyboard();
	}
	return output;
}

char scan_keyboard(){
	char input = 'f'; // false - no read has been done
	while(1){
		input = read_keyboard();
		if(input != 'f'){
			_delay_ms(20);
			return input;
		}	
	}
}