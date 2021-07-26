#ifndef LCD_FUNCT_H
#define LCD_FUNCT_H

#define F_CPU 10000000UL

#include <avr/io.h>
#include <util/delay.h>
#define  LCD_RS PA3
#define  LCD_EN PA2

//typedef uint8_t uin8;

void LCD_send_data(unsigned char, char);
void LCD_init();
void LCD_clear_screen();
void LCD_send_string(char, char, char* );

#endif
