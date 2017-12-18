/* 
 * File:   timerInterrupt.h
 * Author: Martin
 *
 * Created on den 13 januari 2016, 22:56
 */

#ifndef TIMERINTERRUPT_H
#define	TIMERINTERRUPT_H

#ifdef	__cplusplus
extern "C" {
#endif

void ISR(void);
void delayMicrosecond();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMERINTERRUPT_H */
