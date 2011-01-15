/**
 * Blinken button SPI-slave test
 */

// Clock rate: should match the master
#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SS PB2
#define MOSI PB3
#define MISO PB4
#define SCK PB5

/**
 * Initialize SPI in slave mode
 */
void spi_init(void)
{
    volatile char IOReg;
    
    // Set MISO output
    DDRB = (1<<MISO);
    
    // Enable SPI (slave) and SPI interrupts
    SPCR = (1<<SPE) | (1<<SPIE);
    
    // Clear SPIF bit in SPSR
    IOReg   = SPSR;
    IOReg   = SPDR;
    
    // Enable interrupts
    sei();
}

// Interrupt routine
ISR(SPI_STC_vect)
{
    PORTD = SPDR;
}


int main() 
{
    spi_init();
    
    DDRC = 0xff;
    DDRD = 0xff;
    
    PORTC = 0x01;   // Enable row 1
    PORTD = 0x00;   // Disable column
    
    PORTD = 0xff;
    
    for(;;);
}
