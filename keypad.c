/* 
 * File:   keypad.c
 */

#include <xc.h>
#include "lcd18f.h"
#include "keypad.h"

#pragma config OSC = HS, FCMEN = OFF, PWRT = ON, BOREN = OFF
#pragma config WDT = OFF, MCLRE = ON, PBADEN = OFF, LVP = OFF

#define _XTAL_FREQ 20000000 

// function prototype
unsigned char keypad(void);

unsigned char key_press(void);

// switch case function which checks if matrix keys are pressed
unsigned char keypad(void)
{	
    Nop();
	Nop();
    
	LATBbits.LATB0 = 0;                 // 0 rotated through lower nibble
	LATBbits.LATB1 = 1;                 // upper nibble set to inputs with
	LATBbits.LATB2 = 1;                 // internal weak pull-ups - checks which is low
	LATBbits.LATB3 = 1;
	Nop();
	Nop();
	
  if(!PORTBbits.RB4)return('1');      // checking the first row of the keypad
	if(!PORTBbits.RB5)return('4');
	if(!PORTBbits.RB6)return('7');
	if(!PORTBbits.RB7)return('*');
	LATBbits.LATB0 = 1;
	LATBbits.LATB1 = 0;
	Nop();
	Nop();
	
  if(!PORTBbits.RB4)return('2');      // checking the second row of the keypad
	if(!PORTBbits.RB5)return('5');
	if(!PORTBbits.RB6)return('8');
	if(!PORTBbits.RB7)return('0');
	LATBbits.LATB1 = 1;
	LATBbits.LATB2 = 0;
	Nop();
	Nop();
	
  if(!PORTBbits.RB4)return('3');      // checking the third row of the keypad
	if(!PORTBbits.RB5)return('6');	
	if(!PORTBbits.RB6)return('9');
	if(!PORTBbits.RB7)return('#');
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 0;
	Nop();
	Nop();
	
  if(!PORTBbits.RB4)return('A');       // checking the fourth row of the keypad
	if(!PORTBbits.RB5)return('B');
	if(!PORTBbits.RB6)return('C');
	if(!PORTBbits.RB7)return('D');

	return(0);                           // no valid key pressed, exit switch case
} // end keypad())

// keypad de-bounce function
unsigned char key_press(void)           
{
    unsigned char key_press = keypad();
    
    if (key_press !=0) {
        __delay_ms(30);
        while (keypad()!=0);            // waiting for key to be released
        __delay_ms(30);
    }
    return key_press;
} // end key_press())
