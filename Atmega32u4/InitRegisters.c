#include "Setup.h"

void InitRegisters(void)
{
    /***********
     * PULL UP *
     ***********/

    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    PORTF = 0x00;

    /****************** 
     * INPUTS/OUTPUTS *
     ******************/

    DDRB |= (1 << RX_LED);
    DDRC |= 0x00;
    DDRD |= (1 << TX_LED); // TX LED Arduino Micro cards
    DDRE |= 0x00;
    DDRF |= 0x00;

    /*******
     * ADC *
     *******/
    
    // Reset ADC Registers
    ADMUX   = 0x00;
    ADCSRA  = 0x00;
    ADC     = 0x0000;

    // Select Vref=AVcc
    ADMUX |= (1<<REFS0);

    // Set prescaller to 128 and enable ADC 
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADEN);


} // InitRegisters
