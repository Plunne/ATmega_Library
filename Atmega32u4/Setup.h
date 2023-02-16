#ifndef _SETUP_H
#define _SETUP_H

#include <avr/io.h>
#include <util/delay.h>

#include "AnalogDigital.h"
#include "Joystick.h"

/*******************
 * Initialisations *
 *******************/

void InitRegisters(void); // Init registers

/*************
 * Functions *
 *************/

#define TX_LED      PD5
#define RX_LED      PB0

#endif // _SETUP_H
