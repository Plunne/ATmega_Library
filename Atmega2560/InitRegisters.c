#include "Setup.h"

void InitRegisters(void)
{
    /***********
     * PULL UP *
     ***********/

    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    PORTF = 0x00;
    PORTG = 0x00;
    PORTH = 0x00;
    PORTJ = 0x00;
    PORTK = 0x00;
    PORTL = 0x00;

    /****************** 
     * INPUTS/OUTPUTS *
     ******************/

    DDRA |= 0x00;
    DDRB |= (1 << PB7); // LED Arduino Cards
    DDRC |= 0x00;
    DDRD |= 0x00;
    DDRE |= 0x00;
    DDRF |= 0x00;
    DDRG |= 0x00;
    DDRH |= 0x00;
    DDRJ |= 0x00;
    DDRK |= 0x00;
    DDRL |= 0x00; 

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
