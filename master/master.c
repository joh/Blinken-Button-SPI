/**
 * SPI master
 *
 * Communicates with Blinken-button (slave)
 */

// Clock rate: should match the slave
#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Adjust these to fit the MCU (ATmega8535)
#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7

/**
 * Initialize SPI in master mode
 */
void spi_init(void)
{
    volatile char IOReg;
    
    // Set MOSI, SCK and SS as output
    DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
    
    // Enable SPI in Master Mode with SCK = CK/4
    SPCR = (1<<SPE) | (1<<MSTR);
    
    // Clear SPIF bit in SPSR
    IOReg   = SPSR;
    IOReg   = SPDR;
}

/**
 * Transmit a byte, returning the byte received by the slave
 */
uint8_t spi_transmit(uint8_t data)
{
    // Start transmission
    SPDR = data;
    
    // Wait for transmission complete
    while(!(SPSR & (1<<SPIF)));
    
    // Return any received byte
    return SPDR;
}

void spi_send(char data) {
    spi_transmit(data);
}

uint8_t spi_receive() {
    return spi_transmit(0x00);
}

void spi_begin() {
    PORTB &= ~(1 << SS);
}

void spi_end() {
    PORTB |= 1 << SS;
}


int main() 
{
    uint8_t i = 0;
    
    // Initialize SPI
    spi_init();
    
    // Set PORTD as output
    DDRD = 0xff;
    
    for(;;) {
        for (i = 0; i <= 0xff; i++) {
            PORTD = ~i;
            
            spi_begin();
            spi_send(i);
            spi_end();
            
            _delay_ms(500);
        }
    }
}
