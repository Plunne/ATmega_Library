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
    if (PINx == &PINF) canal = IN;     // A0_7
    if (PINx == &PINK) canal = IN + 8; // A8_15


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
    unsigned short pwm16 = pwm;     // PWM 1,3,4,5 -> 16 bits data registers

    /* PORTB */
    if (PORTx == &PORTB) {
        switch (OUT) {
            // PB4 = 2A
            case 4: TCCR2A |= (1 << COM2A1) | (1<<WGM21) | (1 << WGM20);
	                TCCR2B |= (1 << CS20) ;
                    OCR2A = pwm8;
                    break;
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
    /* PORTE */
    else if (PORTx == &PORTE) {
        switch (OUT) {
            // PE3 = 3A
            case 3: TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);
	                TCCR3B |= (1 << CS30) ;
                    OCR3A = pwm16;
                    break;
            // PE4 = 3B
            case 4: TCCR3A |= (1 << COM3B1) | (1 << WGM31) | (1 << WGM30);
	                TCCR3B |= (1 << CS30) ;
                    OCR3B = pwm16;
                    break;
            // PE5 = 3C
            case 5: TCCR3A |= (1 << COM3C1) | (1 << WGM31) | (1 << WGM30);
	                TCCR3B |= (1 << CS30) ;
                    OCR3C = pwm16;
                    break;
        }
    }
    /* PORTG */
    else if (PORTx == &PORTG) {
        switch (OUT) {
            // PG5 = 0B
            case 5: TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	                TCCR0B |= (1 << CS00) ;
                    OCR0B = pwm8;
                    break;
        }
    }
    /* PORTH */
    else if (PORTx == &PORTH) {
        switch (OUT) {
            // PH3 = 4A
            case 3: TCCR4A |= (1 << COM4A1) | (1 << WGM41) | (1 << WGM40);
	                TCCR4B |= (1 << CS40) ;
                    OCR4A = pwm16;
                    break;
            // PH4 = 4B
            case 4: TCCR4A |= (1 << COM4B1) | (1 << WGM41) | (1 << WGM40);
	                TCCR4B |= (1 << CS40) ;
                    OCR4B = pwm16;
                    break;
            // PH5 = 4C
            case 5: TCCR4A |= (1 << COM4C1) | (1 << WGM41) | (1 << WGM40);
	                TCCR4B |= (1 << CS40) ;
                    OCR4C = pwm16;
                    break;
            // PH6 = 2B
            case 6: TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
	                TCCR2B |= (1 << CS20) ;
                    OCR2B = pwm8;
                    break;
        }
    }
    /* PORTL */
    else if (PORTx == &PORTL) {
        switch (OUT) {
            // PL3 = 5A
            case 3: TCCR5A |= (1 << COM5A1) | (1 << WGM51) | (1 << WGM50);
	                TCCR5B |= (1 << CS50) ;
                    OCR5A = pwm16;
                    break;
            // PL4 = 5B
            case 4: TCCR5A |= (1 << COM5B1) | (1 << WGM51) | (1 << WGM50);
	                TCCR5B |= (1 << CS50) ;
                    OCR5B = pwm16;
                    break;
            // PL5 = 5C
            case 5: TCCR5A |= (1 << COM5C1) | (1 << WGM51) | (1 << WGM50);
	                TCCR5B |= (1 << CS50) ;
                    OCR5C = pwm16;
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
