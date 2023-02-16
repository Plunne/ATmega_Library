#include "Joystick.h"

/********************
 * Joystick Reading *
 ********************/

// Read Negative Axis
// PINx     : Axis Neg Port Register
// IN       : Axis Neg Pin
// return   : ADCtoPWM variable
unsigned short readJoystickNeg(volatile unsigned char *PINx, unsigned char IN) {
    
    unsigned short ADCtoPWM = analogRead(PINx, IN);

    unsigned short deadZone = AXIS_CENTER_NEG - AXIS_MINIMUM; // [******] 0 [______]
    
    unsigned short backup;
    unsigned long percentage;
    unsigned long conversion;

    if (ADCtoPWM <= AXIS_CENTER_NEG) {
        backup = AXIS_CENTER_NEG - ADCtoPWM; // [____**] 0 [______]
        percentage = (10000 / deadZone) * backup;
    }
    else if (ADCtoPWM > AXIS_CENTER_NEG){
        return 0;
    }
    
    conversion = (10000 / 1023) * percentage;
    ADCtoPWM = (unsigned short)conversion;

    return ADCtoPWM;

}

// Read Positive Axis
// PINx     : Axis Pos Port Register
// IN       : Axis Pos Pin
// return   : ADCtoPWM variable
unsigned short readJoystickPos(volatile unsigned char *PINx, unsigned char IN) {
    
    unsigned short ADCtoPWM = analogRead(PINx, IN);

    unsigned short deadZone = AXIS_MAXIMUM - AXIS_CENTER_POS; // [______] 0 [******]
    
    unsigned short backup;
    unsigned long percentage;
    unsigned long conversion;

    if (ADCtoPWM >= AXIS_CENTER_POS) {
        backup = AXIS_MAXIMUM - ADCtoPWM; // [______] 0 [____**]
        percentage = (10000 / deadZone) * backup;
    }
    else if (ADCtoPWM < AXIS_CENTER_POS){
        return 0;
    }
    
    conversion = (10000 / 1023) * percentage;
    ADCtoPWM = (unsigned short)conversion;

    return ADCtoPWM;
}

/******************************
 * Joystick Reading + Writing *
 ******************************/

// Assign joystick negative with analog output
// PINx     : Axis Neg Port Register
// IN       : Axis Neg Pin
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
void setJoystickNeg(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT) {
    analogWrite(PORTx, OUT, readJoystickNeg(PINx, IN));
}

// Assign joystick positive with analog output
// PINx     : Axis Pos Port Register
// IN       : Axis Pos Pin
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
void setJoystickPos(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT) {
    analogWrite(PORTx, OUT, readJoystickPos(PINx, IN));
}

// Assign Negative Axis with 1st Analog Output + Positive Axis with 2nd Analog Output
// PINx     : Axis Port Register
// IN       : Axis Pin
// PORT1x   : Axis- Analog Output1 Port Register
// OUT1     : Axis- Analog Output1 Pin
// PORT2x   : Axis+ Analog Output2 Port Register
// OUT2     : Axis+ Analog Output2 Pin
void setJoystickAxis(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORT1x, unsigned char OUT1, volatile unsigned char *PORT2x, unsigned char OUT2) {
    setJoystickNeg(PINx, IN, PORT1x, OUT1);
    setJoystickPos(PINx, IN, PORT2x, OUT2);
}

/**************************************
 * Joystick Digital Reading + Writing *
 **************************************/

// Assign joystick negative with digital output
// PINx     : Axis Neg Port Register
// IN       : Axis Neg Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
void setJoystickDigitalNeg(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT) {
    if (analogRead(PINx, IN) < AXIS_CENTER_NEG) setHIGH(*PORTx, OUT);
    else setLOW(*PORTx, OUT);
}

// Assign joystick positive with digital output
// PINx     : Axis Pos Port Register
// IN       : Axis Pos Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
void setJoystickDigitalPos(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT) {
    if (analogRead(PINx, IN) > AXIS_CENTER_POS) setHIGH(*PORTx, OUT);
    else setLOW(*PORTx, OUT);
}

// Assign Negative Axis with 1st Digital Output + Positive Axis with 2nd Digital Output
// PINx     : Axis Port Register
// IN       : Axis Pin
// PORT1x   : Axis- Digital Output1 Port Register
// OUT1     : Axis- Digital Output1 Pin
// PORT2x   : Axis+ Digital Output2 Port Register
// OUT2     : Axis+ Digital Output2 Pin
void setJoystickDigitalAxis(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORT1x, unsigned char OUT1, volatile unsigned char *PORT2x, unsigned char OUT2) {
    setJoystickDigitalNeg(PINx, IN, PORT1x, OUT1);
    setJoystickDigitalPos(PINx, IN, PORT2x, OUT2);
}
