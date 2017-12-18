/* 
 * File:   timerInterrupt.c
 * Author: Martin
 *
 * Created on den 13 januari 2016
 */

#include <stdio.h>
#include "timerInterrupt.h"
#include "p18f452.h"
#include "globals.h"

char t0resetHi;
char t0resetLo;

//volatile int overflow = FALSE;

// Set up timer0 interrupt 
void initTimer0()
{
    // Registers: RCON INTCON T0CON TMR0H TMR0L
    
    RCONbits.IPEN = 0;      //
    
    INTCONbits.GIE = 1;     //global interrupt enable
    INTCONbits.PEIE = 1;    //peripharal interrupt enable
    INTCONbits.TMR0IF = 0;  //Clear timer0 overflow interrupt flag
    INTCONbits.TMR0IE = 1;  //enable the timer0 by turning on overflow flag
    
    T0CONbits.TMR0ON = 1;   // Timer0 off
    T0CONbits.T08BIT = 0;   // 16 bit counter
    T0CONbits.T0CS = 0;     // Use instruction clock
    T0CONbits.T0SE = 0;     // Trigger timer on rising edge
    T0CONbits.PSA = 0;      // Use prescaler
    T0CONbits.T0PS2 = 0;    // Prescaler bit 2
    T0CONbits.T0PS1 = 0;    // Prescaler bit 1
    T0CONbits.T0PS0 = 0;    // Prescaler bit 0

}

#pragma code ISR = 0x08 // Store the below code at address 0x08
#pragma interrupt ISR  // let the compiler know that the function isr() is an interrupt handler
// Interrupt handler for the timer0 overflow
void ISR(void) // this is meant to do nothing right now. used for delays!
{
    // Reset the timer count & interrupt flag
    // TMR0H = t0resetHi;
    // TMR0L = t0resetLo;
    INTCONbits.TMR0IF = 0;
}

#pragma code

