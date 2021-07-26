#ifndef KEYBOARD_FUNCT_H_
#define KEYBOARD_FUNCT_H_

#define F_CPU 10000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "Timer_mode.h"

char read_keyboard();
char scan_keyboard();


#endif /* KEYBOARD_FUNCT_H_ */