#include "AnalogDigital.h"

/******************
 * Analog Reading *
 ******************/

// Read analog input
// PINx     : Analog Input Port Register
// IN       : Analog Input Pin
// return   : ADC register
unsigned short analogRead(volatile unsigned char *PINx, unsigned char IN) {
    
    unsigned char canal;
    
    /* Assign analog canal */
    if (PINx == &PINC) canal = IN;  // A0_5

    /* Setup ADC */
    ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);

    /* Conversion ADC */
    setHIGH(ADCSRA, ADSC); // Begin Conversion
    while (ADCSRA & (1 << ADSC)); // Waiting Conversion ending
    
    /* Return ADC Data register */
    return ADC;
}

/******************
 * Analog Writing *
 ******************/

// Write analog output
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
// pwm      : Analog output PWM duty cycle value
void analogWrite(volatile unsigned char *PORTx, unsigned char OUT, unsigned short pwm) {
    
    unsigned char pwm8 = pwm / 4;   // PWM 0,2 -> 8 bits data registers
    unsigned short pwm16 = pwm;     // PWM 1 -> 16 bits data registers

    /* PORTB */
    if (PORTx == &PORTB) {
        switch (OUT) {
            // PB1 = 1A
            case 1: TCCR1A |= (1 << COM1A1) | (1<<WGM11) | (1 << WGM10);
	                TCCR1B |= (1 << CS10) ;
                    OCR1A = pwm16;
                    break;
            // PB2 = 1B
            case 2: TCCR1A |= (1 << COM1B1) | (1<<WGM11) | (1 << WGM10);
	                TCCR1B |= (1 << CS10) ;
                    OCR1B = pwm16;
                    break;
            // PB3 = 2A
            case 3: TCCR2A |= (1 << COM2A1) | (1<<WGM21) | (1 << WGM20);
	                TCCR2B |= (1 << CS20) ;
                    OCR2A = pwm8;
                    break;
        }
    }
    /* PORTD */
    if (PORTx == &PORTD) {
        switch (OUT) {
            // PD3 = 2B
            case 3: TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
	                TCCR2B |= (1 << CS20) ;
                    OCR2B = pwm8;
                    break;
            // PD5 = 0B
            case 5: TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	                TCCR0B |= (1 << CS00) ;
                    OCR0B = pwm8;
                    break;
            // PD6 = 0A
            case 6: TCCR0A |= (1 << COM0A1) | (1<<WGM01) | (1 << WGM00);
	                TCCR0B |= (1 << CS00) ;
                    OCR0A = pwm8;
                    break;
        }
    }
}

/******************
 * Analog Command *
 ******************/

// Assign analog input with analog output
// PINx     : Analog Input Port Register
// IN       : Analog Input Pin
// PORTx    : Analog Output Port Register
// OUT      : Analog Output Pin
void setAnalogCommand(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT) {
    analogWrite(PORTx, OUT, analogRead(PINx, IN));
}

/*****************************
 * Analog to Digital Command *
 *****************************/

// Assign analog input with digital output
// PINx     : Analog Input Port Register
// IN       : Analog Input Pin
// PORTx    : Digital Output Port Register
// OUT      : Digital Output Pin
void setAnalogDigitalCommand(volatile unsigned char *PINx, unsigned char IN, volatile unsigned char *PORTx, unsigned char OUT) {
    if (analogRead(PINx, IN) > 100) setHIGH(*PORTx, OUT);
    else setLOW(*PORTx, OUT);    
}
