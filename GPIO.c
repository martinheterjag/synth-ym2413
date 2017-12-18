
#include "GPIO.h"
#include "p18f452.h"
#include "globals.h"
#include <stdlib.h>


void initGPIO()
{

    // set all analog pins to analog and use Vdd and Vss as ref.
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 0;

    // Set sample rate to Fosc/64 (ADCS2:ADCS0 = 110)
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 1;
    ADCON1bits.ADCS2 = 1;
    
    // A/D result will be right justified ADRESH=0b000000xx ADRESH=0bxxxxxxxx 
    // where x is the input and 6 msb of adresh is always 0.
    ADCON1bits.ADFM = 1;
    
    // see globals for pin.
    LED_DIR = OUTPUT;
    LED = LOW;
}

//Function to Read given ADC channel (0-13)
unsigned int AnalogRead(unsigned char ch)
{
   if(ch>7) return 0;  //Invalid Channel

   /*ADCON0bits.CHS0 = ch & 0b001;
   ADCON0bits.CHS1 = (ch & 0b010) >> 1;
   ADCON0bits.CHS2 = (ch & 0b100) >> 2;*/
   ADCON0bits.CHS = ch;
   
   //ADCON0=(ch<<3);   //Select ADC Channel

   ADCON0bits.ADON = 1;  //switch on the adc module

   ADCON0bits.GO_DONE=1;  //Start conversion

   while(ADCON0bits.GO_DONE); //wait for the conversion to finish

   ADCON0bits.ADON = 0;  //switch off adc

   return ADRES;
}
