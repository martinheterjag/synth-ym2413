/* 
 * File:   main.c
 * Author: Martin
 *
 * Created on den 1 december 2017, 19:56
 */

#include <stdio.h>
#include <stdlib.h>
#include "p18f452.h"
#include "delays.h"

//Global variables

#include "GPIO.h"
#include "globals.h"

// PIC18F452 config settings
#pragma config OSC = HS  //HSPLL = HS with 4 x PLL enabled - clock is speed of crystal x 4
#pragma config OSCS = OFF   // turning off Oscillator Switching
#pragma config WDT = OFF    //Watchdog timer can be enabled in software with SWDTEN bit
#pragma config LVP = OFF   	//Low voltage programming disabled

// Global variables

void YM2413Write(char adr, char dta);
void playnote(int channel, int note, int oct, int instrument, int vol, int on);
void stopnote(int channel);

/*
 * Main program
 */
void main(void) {
    // INIT EVERYTHING!
    int i;
    TRISD = 0;  // Set port D as outputs
    LATD = 0;   
    
    A0_DIR = OUTPUT;
    A0_ = LOW;  // LOW = ADDRESS, HIGH = VALUE
    
    CS_DIR = OUTPUT;
    CS_ = HIGH;  // SET LOW TO ENABLE WRITING TO YM2413
    
    IC_DIR = OUTPUT;
    IC_ = LOW;
    Delay10KTCYx(50);
    IC_ = HIGH;
    initGPIO();
    
    // IT'S TURNED ON!
    LED_DIR = OUTPUT;
    LED = HIGH;
    
    Delay10KTCYx(1);
    // turn off drums.
    YM2413Write(0x0E , 0x00);
    Delay10KTCYx(1);
    // turn off test data.
    YM2413Write(0x0F , 0x00);
    Delay10KTCYx(1);
    // Modulator settings.
    YM2413Write(0x00 , 0x21);
    Delay10KTCYx(1);
    // Carrier settings.
    YM2413Write(0x01 , 0x21);
    Delay10KTCYx(1);    
    // play and stop note on all channels 0-9.
    LED = LOW;
    for (i=0; i<10; i++) {
        playnote(i, 3, 4, 2, 15, 1);
        Delay10KTCYx(50);
        playnote(i, 3, 4, 2, 15, 0);
    }
    LED = HIGH;
    // MAIN PROGRAM LOOP
    while(1)
    {
        //channel, note, oct, instrument, vol, on/off
        playnote(0, 0, 3, 3, 0, 1);
        // LED = HIGH;
        Delay10KTCYx(250);

        playnote(0, 0, 3, 3, 0, 0);
        // LED = LOW;
        Delay10KTCYx(250);
    }
}


void YM2413Write(char adr, char dta) {
    // From the datasheet:
    //  CS WE A0
    //  1  x  x  = Bus Inactive
    //  0  0  0  = Write register address
    //  0  0  1  = Write register content 
    // I grounded WE, so we dont have to worry.

    // write register address
    CS_ = HIGH;  // Make sure to keep high while setting other ports.
    Delay10TCYx(5);
    A0_ = LOW;
    Delay10TCYx(5);
    LATD = adr;
    Delay10TCYx(5);
    CS_ = LOW;  // Now, enable.
    // wait at leat 12 cycles.
    Delay10TCYx(5);
  
    CS_ = HIGH;
    Delay10TCYx(5);
    A0_ = HIGH;
    Delay10TCYx(5);
    LATD = dta;
    Delay10TCYx(5);
    CS_ = LOW;
    // wait at least 84 cycles.
    Delay10TCYx(12);
    CS_ = HIGH; // its cool to be high!
    Delay10TCYx(1);
}



void playnote(int channel, int note, int oct, int instrument, int vol, int on) {
  
    // channel = channel 0 to channel 8
    // note = 0-11
    // oct = the octave
    // instrument = the instrument number
    // vol = the volume, 0 = max, 15=min
    char freq_msb = 0, freq_lsb = 0, msg = 0;
    // int freq[]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    int freq[12] = {172,181,192,204,216,229,242,257,272,288,305,323};
    if(note > 11) {
        note = 11;
    }

    freq_msb = (freq[note] >> 8) & 0xff;
    freq_lsb = freq[note]  & 0xff;
    // 0E D0..D4 = Rhythm instrument on / off
    // D5 -> 1= Rhythm sound mode, 0= melody sound mode
    // Drums off, all channels are melody
    

    // 10 = F-Number LSB 8 bits
    YM2413Write((0x10 + channel), freq_lsb); // );

    
    // 30 -> D0..D3 = vol (0 to 15)
    //       D4..D7 = instrument (0 to 15)

    msg = instrument << 4 | vol ;
    YM2413Write((0x30 + channel), msg);
    
    // NoteON & Oct & Note
    // 20 -> D0 = MSB fnumber
    //       D1..D3 = octave 0 to 7
    //       D4 = key On/Off 
//(1 << 5) | 
    if(on != 0) {
        msg = (1 << 5) | (0 << 4) | (oct << 1) | freq_msb;
    } else {
        msg = (0 << 5) | (1 << 4) | (oct << 1) | freq_msb;
    }
    
    
    YM2413Write((0x20 + channel), msg);


}

void stopnote(int channel){
  YM2413Write((0x20 + channel), 0x20);
}

