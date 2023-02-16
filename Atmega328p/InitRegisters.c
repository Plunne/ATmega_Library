#include "Setup.h"

void InitRegisters(void)
{
    /***********
     * PULL UP *
     ***********/

    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;

    /****************** 
     * INPUTS/OUTPUTS *
     ******************/

    DDRB |= (1 << PB5); // LED Arduino Cards
    DDRC |= 0x00;
    DDRD |= 0x00;

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
