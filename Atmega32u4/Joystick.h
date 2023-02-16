#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include "AnalogDigital.h"

#define AXIS_MINIMUM         0       // Negative Axis min value
#define AXIS_CENTER_NEG      420     // Negative Axis max value
#define AXIS_CENTER_POS      600     // Positive Axis min value
#define AXIS_MAXIMUM         1000    // Positive Axis max value

/********************
 * Joystick Reading *
 ********************/

// Read Negative Axis
// PINx     : Axis Neg Port Register
// IN       : Axis Neg Pin
// return   : ADCtoPWM variable
unsigned short readJoystickNeg(volatile unsigned char *PINx, unsigned char IN);

// Read Positive Axis
// PINx     : Axis Pos Port Register
// IN       : Axis Pos Pin
// return   : ADCtoPWM variable
unsigned short readJoystickPos(volatile unsigned char *PINx, unsigned char IN);

/******************************
 * Joystick Reading + Writing *
 ******************************/

// Assign joystick negative with analog output
// PINx     : Axis Neg Port Register
// IN       : Axis Neg Pin
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
void setJoystickNeg(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT);

// Assign joystick positive with analog output
// PINx     : Axis Pos Port Register
// IN       : Axis Pos Pin
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
void setJoystickPos(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT);

// Assign Negative Axis with 1st Analog Output + Positive Axis with 2nd Analog Output
// PINx     : Axis Port Register
// IN       : Axis Pin
// PORT1x   : Axis- Analog Output1 Port Register
// OUT1     : Axis- Analog Output1 Pin
// PORT2x   : Axis+ Analog Output2 Port Register
// OUT2     : Axis+ Analog Output2 Pin
void setJoystickAxis(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORT1x, unsigned char OUT1, volatile unsigned char *PORT2x, unsigned char OUT2);

/**************************************
 * Joystick Digital Reading + Writing *
 **************************************/

// Assign joystick negative with digital output
// PINx     : Axis Neg Port Register
// IN       : Axis Neg Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
void setJoystickDigitalNeg(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT);

// Assign joystick positive with digital output
// PINx     : Axis Pos Port Register
// IN       : Axis Pos Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
void setJoystickDigitalPos(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT);

// Assign Negative Axis with 1st Digital Output + Positive Axis with 2nd Digital Output
// PINx     : Axis Port Register
// IN       : Axis Pin
// PORT1x   : Axis- Digital Output1 Port Register
// OUT1     : Axis- Digital Output1 Pin
// PORT2x   : Axis+ Digital Output2 Port Register
// OUT2     : Axis+ Digital Output2 Pin
void setJoystickDigitalAxis(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORT1x, unsigned char OUT1, volatile unsigned char *PORT2x, unsigned char OUT2);

#endif // _JOYSTICK_H
