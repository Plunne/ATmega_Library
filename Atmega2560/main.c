#define F_CPU 16000000UL

#include "Setup.h"

int main(void)
{
    /* Initialisations */
    InitRegisters();
    
    /* Program */
    while (1) {
        toggleBIT(PORTB, LED);
        _delay_ms(500);
    }
}
