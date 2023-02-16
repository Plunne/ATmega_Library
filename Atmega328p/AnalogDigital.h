#ifndef _ANALOGNUM_H
#define _ANALOGNUM_H

#include <avr/io.h>

/*********************
 * Digital Functions *
 *********************/

/* Reading */

// Read digital input
// PINx     : Digital Input Port Register
// IN       : Digital Input Pin
// return   : Pin state
unsigned char digitalRead(volatile unsigned char *PINx, unsigned char IN);

/* Writing */

// Set bit to Low level
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
#define setHIGH(PORTx, OUT)             (PORTx |= (1 << OUT))

// Set bit to High level
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
#define setLOW(PORTx, OUT)              (PORTx &= ~(1 << OUT))

// Toggle bit
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
#define toggleBIT(PORTx, OUT)           (PORTx ^= (1 << OUT))

/* Read + Write */

// Assign digital input with digital output
// PINx     : Digital Input Port Register
// IN       : Digital Input Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
void setDigitalCommand(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT);

/********************
 * Analog Functions *
 ********************/

/* Reading */

// Read analog input
// PINx     : Analog Input Port Register
// IN       : Analog Input Pin
// return   : ADC register
unsigned short analogRead(volatile unsigned char *PINx, unsigned char IN);

/* Writing */

// Write analog output
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
// pwm      : Analog output PWM duty cycle value
void analogWrite(volatile unsigned char *PORTx, unsigned char OUT , unsigned short pwm);

/* Read + Write */

// Assign analog input with analog output
// PINx     : Analog Input Port Register
// IN       : Analog Input Pin
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
void setAnalogCommand(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT);

/******************************
 * Analog to Digital Function *
 ******************************/

// Assign analog input with digital output
// PINx     : Analog Input Port Register
// IN       : Analog Input Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
void setAnalogDigitalCommand(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT);

#endif // _ANALOGNUM_H
