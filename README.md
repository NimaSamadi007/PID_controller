# PID_controller
A simple PID_controller

# Description

This project is a simple PID_controller which is implemented on AVR Atmega32 microcontrollers. This code has been simulated in Proteus software. An overview of the circuit looks like below:

<img src="/circuit.png">

In the picture you can see Atmega32 microcontroller. A keypad is connected to the micro so one can enter desired coefficents for P, I and D parameters. Microcontroller states can be seen in the LCD which works in 8 bit mode. 
To test the circuit, A tempreture sensor is added and you can set the desired tempreature and the micro will try to obtain the work point.
In addition to the PID mode, there is also a timer mode which you can select it by pushing the '+' key on the keypad. After 16 minute it micro will load some data from memory and show it on LCD.

# Codes

Functions are written in seperate files. The Keybord_funct.h and its implementation file contiants functions required for interacting with keypad. The LCD_funct.h does the same for the LCD, and Timer_mode is used for timer mode in microcontroller. Finally main.c file is the program driver.

