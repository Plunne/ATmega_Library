#include "AnalogDigital.h"

/*******************
 * Digital Reading *
 *******************/

// Read digital input
// PINx     : Digital Input Port Register
// IN       : Digital Input Pin
// return   : Pin state
unsigned char digitalRead(volatile unsigned char *PINx, unsigned char IN) {
    *PINx &= (1 << IN);   
    return *PINx;
}

/*******************
 * Digital Command *
 *******************/

// Assign digital input with digital output
// PINx     : Digital Input Port Register
// IN       : Digital Input Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pi
void setDigitalCommand(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT) {
    if (!digitalRead(PINx, IN)) setHIGH(*PORTx, OUT);
    else setLOW(*PORTx, OUT);
}
