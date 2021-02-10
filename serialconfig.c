/* 
 * File:   serialconfig.c
 */

#include <xc.h>
#include "keypad.h"
#include "lcd18f.h"
#include "serial.h"

#define _XTAL_FREQ 20000000   

// register initialization function
void set_registers(void)
{   
    SPBRG1 = 64;                                                    /* (oscillator frequency)/(16*SPBRG)+1) */    
    BAUDCONbits.BRG16 = 0;                                          /* 8-bit mode */
    TXSTA1bits.BRGH = 1;                                            /* high-speed baud rate */  
  
    TRISCbits.TRISC7 = 1;                                           /* Rx is set as an input */
    TRISCbits.TRISC6 = 0;                                           /* Tx set as an output */
    
    TXSTAbits.TX9 = 0;                                              /* 8 bit-mode */
    TXSTAbits.TXEN = 1;                                             /* enables the baud-rate clock generator */
    TXSTAbits.SYNC1 = 0;                                            /* puts USTART into UART mode */
    TXSTAbits.SENDB = 0;                                            /* disables sync break */
    TXSTAbits.BRGH = 1;                                             /* high-speed */
    
    RCSTAbits.ADDEN = 0;                                            /* enables address detection */
    RCSTAbits.SPEN = 1;                                             /* enables RC6 and RC7 as serial ports */
    RCSTAbits.RX9 = 0;                                              /* clearing for 8-bit reception */
    RCSTAbits.CREN = 1;                                             /* set, enabling continuous receive */  
} // end set_registers())

