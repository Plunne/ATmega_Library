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
    
    /* ADC : 0,1,4,5,6,7 */
    if (PINx == &PINF) {
        switch (IN) {
            case 0: canal = 0; // ADC0
                    break;
            case 1: canal = 1; // ADC1
                    break;
            case 4: canal = 4; // ADC4
                    break;
            case 5: canal = 5; // ADC5
                    break;
            case 6: canal = 6; // ADC6
                    break;
            case 7: canal = 7; // ADC7
                    break;
        }
    }
    /* ADC : 8,9,10 */
    else if (PINx == &PIND) {
        switch (IN) {
            case 4: canal = 8; // ADC8
                    break;
            case 6: canal = 9; // ADC9
                    break;
            case 7: canal = 10; // ADC10
                    break;
        }
    }
    /* ADC : 11,12,13 */
    else if (PINx == &PINB) {
        switch (IN) {
            case 4: canal = 11; // ADC11
                    break;
            case 5: canal = 12; // ADC12
                    break;
            case 6: canal = 13; // ADC13
                    break;
        }
    }

    /* Setup ADC */
    ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);

    /* ADC Conversion */
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
    
    unsigned char pwm8 = pwm / 4;   // PWM 0 -> 8 bits data registers
    unsigned short pwm16 = pwm;     // PWM 1,3 -> 16 bits data registers

    /* PORTB */
    if (PORTx == &PORTB) {
        switch (OUT) {
            // PB5 = 1A
            case 5: TCCR1A |= (1 << COM1A1) | (1<<WGM11) | (1 << WGM10);
	                TCCR1B |= (1 << CS10) ;
                    OCR1A = pwm16;
                    break;
            // PB6 = 1B
            case 6: TCCR1A |= (1 << COM1B1) | (1<<WGM11) | (1 << WGM10);
	                TCCR1B |= (1 << CS10) ;
                    OCR1B = pwm16;
                    break;
            // PB7 = 0A
            case 7: TCCR0A |= (1 << COM0A1) | (1<<WGM01) | (1 << WGM00);
	                TCCR0B |= (1 << CS00) ;
                    OCR0A = pwm8;
                    break;
        }
    }
    /* PORTC */
    else if (PORTx == &PORTC) {
        switch (OUT) {
            // PC6 = 3A
            case 6: TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);
	                TCCR3B |= (1 << CS30) ;
                    OCR3A = pwm16;
                    break;
        }
    }
    /* PORTD */
    if (PORTx == &PORTD) {
        switch (OUT) {
            // PD0 = 0B
            case 0: TCCR0A |= (1 << COM0B1) | (1<<WGM01) | (1 << WGM00);
	                TCCR0B |= (1 << CS00) ;
                    OCR0B = pwm8;
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
