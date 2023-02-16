#define F_CPU 16000000UL

#include "Setup.h"


int main(void)
{
    /* Init */
    InitRegisters();
    
    /* Program */
    while (1) {
        toggleBIT(PORTD, TX_LED);
        toggleBIT(PORTB, RX_LED);
        _delay_ms(500);
    }
}
