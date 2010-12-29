#define F_CPU 8000000UL                                    /* Clock Frequency = 1Mhz */

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

#define SCK PB5
#define MISO PB4
#define MOSI PB3
#define SS PB2

void SPI_MasterInit(void)
{
    volatile char IOReg;
    
    // Set MOSI, SCK and SS as output
    DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
    
    // enable SPI in Master Mode with SCK = CK/4
    SPCR = (1<<SPE) | (1<<MSTR);
    
    // clear SPIF bit in SPSR
    IOReg   = SPSR;
    IOReg   = SPDR;
}

void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
}


int main(void)
{
    SPI_MasterInit();
    
    DDRC = 0xff;
    DDRD = 0xff;
    
    while (1) {
        PORTC = 0x01;
        PORTD = 0x01;
        
        SPI_MasterTransmit(0xab);
        
        _delay_ms(500);
        
        PORTC = 0x01;
        PORTD = 0x02;
        
        _delay_ms(500);
    }
}
