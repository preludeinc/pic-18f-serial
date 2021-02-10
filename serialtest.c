/***********************************************************************************************************

Description:          User entered data (via the Matrix keypad) is sent serially through the PIC's built-in
 *                    TX and RX pins. Pressing 'A' scrolls text to the right, 'B' acts as a back-space, 'C'
 *                    clears entered data, and 'D' scrolls text to the left.

*************************************************************************************************************/

#include  <xc.h> 
#include "lcd18f.h"
#include "keypad.h"
#include "serial.h"

#pragma config OSC = HS, FCMEN = OFF, PWRT = ON, BOREN = OFF
#pragma config WDT = OFF, MCLRE = ON, PBADEN = OFF, LVP = OFF

#define _XTAL_FREQ 20000000   

// initialization function for registers
void set_registers();

// de-bounce function
unsigned char key_press(void);

void main(void){
    
    INTCON2bits.nRBPU = 0;                                          // turns on weak pull-ups on port B 
    
    ADCON1 = 0x0F;                                                  // AN1 - AN12 are all digital inputs
    CMCON = 0x07;                                                   // comparators are turned off
    TRISB = 0xF0;                                                   // upper nibble inputs lower outputs for keypad
    TRISC = 0x00;                                                   // output for the LED bar
    TRISD = 0;                                                      // output for the LCD
    
    PORTC = 0;                                                      // clearing used ports
    PORTD = 0;
    
    lcd_init();                                                     // LCD initialization 
    set_registers();                                                // initialization of registers
    lcd_bl(1);                                                      // turns on the back light
    lcd_clear();                                                    // clears LCD
      
    unsigned char i = 0;                                            // holds position of text on LCD 
    unsigned char key;                                              // holds keypad state
    
    while (1)
    {    
        key = key_press();                                          // calls keypad de-bounce function (which calls the keypad function)
        
        if (PIR1bits.RCIF)                                          // has data been received?
        {                                                     
            lcd_putch(RCREG);                                       // if so, print the key to the receive register
            i++;                                                    // data is incremented as it is printed
        }
        if (key !=0)                                                // if a key has been pressed, below switch-case executes
        {
            // keypad switch case statement
            switch (key)
            {
                case 'A':                                           // if an 'A' is pressed on the keypad
                    lcd_cmd(0x1C);                                  // text will scroll to the right
                break;

                case 'B':                                           // if a 'B' is pressed on the keypad                                   
                        if (i > 0x00)                               // backspace
                        {                                           // if the cursor is not at the first position
                            i--;                                    // decrement position
                        }
                            lcd_goto(i);
                            lcd_putch(' ');                         // displays a space as position decrements
                            lcd_goto(i);
                        if (i == 0x40)                              // if the cursor is on the first character of the second line
                        {
                            (i = 0x0F);                             // text will wrap to the last character of the first line
                        }
                break;

                case 'C':                                           // if a 'C' is pressed on the keypad                  
                    lcd_clear();                                    // the LCD is cleared       
                    __delay_ms(5);     
                break;

                case 'D':                                           // if a 'D' is pressed on keypad
                    lcd_cmd(0x18);                                  // text will scroll to the left    
                break;
                
                case '#':                                           // if '#' is pressed on the keypad
                    if ((i >= 0x00) && (i <= 0x0F))                 // acts as a return key and toggles the line on the lCD
                    {
                        (i = 0x40);
                        lcd_goto(i);
                    }
                    if ((i >= 0x40) && (i <= 0x4F))
                    {
                        (i = 0x00);
                        lcd_goto(i);
                    }
                break;

                default:                    
                    TXREG = key;                                    // data is sent to the transmit register
                break;
                    } // end switch
                    if (i == 0x10)                                  // text-wrapping functionality
                    {                                               // if character is on the last position of the first line 
                    (i = 0x40);                                     // it prints to position 0x40 of the second line 
                    lcd_goto(i);        
                    }     
                    if (i == 0x50)                                  // if character is on the last position of the second line
                    {                                               // it prints to position 0x00 of the first line 
                    (i = 0x00);                                          
                    lcd_goto(i);   
                    } 
            } // end if
        } // end while(1)                                                  
} // end main
 
