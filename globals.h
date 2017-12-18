/* 
 * File:   globals.h
 * Author: Martin
 *
 * Created on den 3 januari 2016, 12:16
 * 
 * Global values and constants
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define OUTPUT 0
    #define INPUT 1
    #define HIGH 1
    #define LOW 0
    #define TRUE 1
    #define FALSE 0

    #define LED LATBbits.LATB4
    #define LED_DIR TRISBbits.RB4

    // #define POTENTIOMETER1 5 // pot on AN5
    // #define POTENTIOMETER2 6 // pot on AN6
    
    #define A0_DIR TRISCbits.RC4
    #define A0_ LATCbits.LATC4
    
    #define CS_DIR TRISCbits.RC5
    #define CS_ LATCbits.LATC5

    #define IC_DIR TRISCbits.RC6
    #define IC_ LATCbits.LATC6


//    #define SPI_CLK_DIR TRISCbits.RC3
//    #define SPI_SDO_DIR TRISCbits.RC5

    // Analog read filtering, used for dejitter HAVE TO BE BETWEEN 0.0f and 1.0f
    // #define FILTER_VAL 0.9f
 
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */
