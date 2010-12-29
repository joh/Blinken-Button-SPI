#define F_CPU 8000000UL

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>



int main(void)
{
    DDRB = 0b10000011;
    DDRC = 0xff;    // OUT on all PORTC pins
    DDRD = 0xff;
    
    PORTB |= 0b10000000;
    
    PORTC = 0b00000001;
    PORTD = 0b10000000;
    
    PORTD = 0xff;
    
    uint8_t pattern = 0b00000001;
    uint8_t i = 0;
    uint8_t j = 0;
    
    while (1) {
        for (i = 0; i < 8; i++) {
            if (i < 6) {
                PORTB &= 0b11111100;
                PORTC = pattern << i;
            } else {
                PORTC = 0;
                PORTB &= 0b11111100;
                PORTB |= (pattern << (i - 6));
            }
            /*for (j = 0; j < 8; j++) {
                PORTD = pattern << j;
            }*/
            _delay_ms(50);
        }
    }
}
