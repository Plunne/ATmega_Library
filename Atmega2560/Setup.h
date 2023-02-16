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

#define LED         PB7

#endif // _SETUP_H
