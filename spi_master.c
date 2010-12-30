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

uint8_t SPI_Transmit(char data)
{
    // Start transmission
    SPDR = data;
    
    // Wait for transmission complete
    while(!(SPSR & (1<<SPIF)));
    
    // Return any received byte
    return SPDR;
}

void SPI_Send(char data) {
    SPI_Transmit(data);
}

uint8_t SPI_Receive() {
    return SPI_Transmit(0x00);
}


int main(void)
{
    uint8_t data = 0x43;
    
    SPI_MasterInit();
    
    DDRC = 0xff;
    DDRD = 0xff;
    
    PORTC = 0x01;   // Enable row 1
    PORTD = 0x00;   // Disable column
    
    PORTD = 42;
    
    _delay_ms(1000);
    
    while (1) {
        data = SPI_Receive();
        
        PORTD = data;
        
        _delay_ms(500);
        /*
        SPI_MasterTransmit(0xab);
        
        _delay_ms(500);
        
        PORTC = 0x01;
        PORTD = 0x02;
        
        _delay_ms(500);*/
    }
}
