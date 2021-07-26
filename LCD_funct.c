#include "LCD_funct.h"


void LCD_send_data(unsigned char input, char which){
	PORTA = (PORTA & 0x0f) |
			(input & 0xf0);
	
	if(which != 0) // So, we want to send data:
		PORTA |= (1 << LCD_RS);
	else // else, we want to send command:
		PORTA &= (~ (1 << LCD_RS) );
	
	PORTA |= (1 << LCD_EN);
	_delay_us(2);
	// apply high to low pulse to EN pin of LCD
	PORTA = PORTA & ( ~ (1 << LCD_EN) );
	
	// wait for data to be written:
	_delay_us(200);
	
	// send second four bit:
	PORTA = (PORTA & 0x0f) |
			(input << 4);  // Low four bit
	
	if(which != 0) // So, we want to send data:
		PORTA |= (1 << LCD_RS);
	else // else, we want to send command:
		PORTA &= (~ (1 << LCD_RS) );
	
	
	PORTA |= (1 << LCD_EN);
	
	_delay_us(2);
	PORTA = PORTA & ( ~ (1 << LCD_EN) );
	
	// wait for data to be written:
	_delay_ms(2);
	
	return;
}


void LCD_clear_screen(){
	LCD_send_data(0x01, 0);
	_delay_ms(2);
	LCD_send_data(0x80, 0);
}

void LCD_init(){
	DDRA = 0xfc;
	_delay_ms(20);
	
	LCD_send_data(0x02, 0); 
	LCD_send_data(0x28, 0);
	LCD_send_data(0x0c, 0);
	LCD_send_data(0x06, 0);
	LCD_send_data(0x01, 0);
	_delay_ms(2);
}

void LCD_send_string(char x, char y, char* data){
	y &= 0x0f;
	y |= (x == 0) ? 0x80 : 0xc0;
	
	LCD_send_data(y, 0);
	for(int i = 0; data[i] != 0; i++)
		LCD_send_data(data[i], 1);
}