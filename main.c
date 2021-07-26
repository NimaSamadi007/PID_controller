#define F_CPU 10000000UL

#include <avr/io.h>
#include <util/delay.h>

// LCD functions - implemented in LCD_funct.c and header file is in LCD_funct.h
#include "LCD_funct.h"
// Keypad functions:
#include "Keyboard_funct.h"


// global variables:
int Kp = 0, Ki = 0, Kd = 0;

void Micro_initializer(){
	char MSB [3];
	char LSB [3];
	char MSB_write[2] = {0, 0};
	char LSB_write[2] = {0, 0};
		
	LCD_init();
	LCD_clear_screen();
	// Kp read:
	LCD_send_string(0, 0, "Enter Kp value:");
	MSB[0] = scan_keyboard();
	MSB_write[0] = MSB[0];
	LCD_send_string(1, 0, MSB_write);
	LSB[0] = scan_keyboard();
	LSB_write[0] = LSB[0];
	LCD_send_string(1, 1, LSB_write);
	Kp = (MSB[0] - 48) * 10 + (LSB[0] - 48);
	
	_delay_ms(200);
	LCD_clear_screen();
	// Ki read:
	LCD_send_string(0, 0, "Enter Ki value:");
	MSB[1] = scan_keyboard();
	MSB_write[0] = MSB[1];
	LCD_send_string(1, 0, MSB_write);
	LSB[1] = scan_keyboard();
	LSB_write[0] = LSB[1];
	LCD_send_string(1, 1, LSB_write);
	Ki = (MSB[1] - 48) * 10 + (LSB[1] - 48);

	_delay_ms(200);
	LCD_clear_screen();
	// Kd read:
	LCD_send_string(0, 0, "Enter Kd value:");
	MSB[2] = scan_keyboard();
	MSB_write[0] = MSB[2];
	LCD_send_string(1, 0, MSB_write);
	LSB[2] = scan_keyboard();
	LSB_write[0] = LSB[2];
	LCD_send_string(1, 1, LSB_write);
	Kd = (MSB[2] - 48) * 10 + (LSB[2] - 48);
	
	_delay_ms(200);
	LCD_clear_screen();
	LCD_send_string(0, 0, "PID values:");
	char output[] = {'P', '=', MSB[0], LSB[0], 
					 ',', 'I', '=', MSB[1], LSB[1],
					 ',', 'D', '=', MSB[2], LSB[2]};
	LCD_send_string(1, 0, output);
}

int main(void){
	DDRA = 0xFC; // LCD output
	DDRB = 0x0F; // PB[7:4] => input, PB[3:0] => output - for keyboard
	DDRC = 0xFF; // output to DAC
	DDRD = 0xFF; // output for timer:

	ADCSRA = 0x87; // Enable ADC, Disbale interrupt, set prescalar: clk/128
	ADMUX = 0xC0; // Internal Vref, Right aligned, ADC0 channel
	
	
	Micro_initializer();
		
	int ADC_val_p = 0; // previous val
	int ADC_val_c = 0; // current val
	int I_p = 0, I_c = 0;
	int P_c = 0;
	int D_p = 0, D_c = 0;
	char ADCH_val = 0, ADCL_val = 0;
	
	LCD_init();
	LCD_clear_screen();
	
	while(1){
		ADCSRA |= (1 << ADSC); // start conversion:
		_delay_ms(20);
		while( (ADCSRA & (1 << ADIF)) == 0 ); // wait for ADIF to be set
		ADCSRA |= (1 << ADIF); // write one to clear interrupt
		
		ADC_val_p = ADC_val_c;
		ADCL_val = ADCL;
		ADCH_val = ADCH;
		ADC_val_c = ADCL_val | (ADCH_val << 8); // concat two byte together
		ADC_val_c /= 4; // to be fit into 8 bit
		I_p = I_c;
		D_p = D_c;
		P_c = Kp * ADC_val_c;
		I_c = (Ki / 100) * (ADC_val_c + ADC_val_p) + I_p;
		D_c = (Kd * 100) * (ADC_val_c - ADC_val_p) + D_p;
		
		PORTC = P_c + I_c + D_c;
		read_keyboard();
	}
	
}

