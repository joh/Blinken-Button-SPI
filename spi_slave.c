#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int i = 0;

//Interrupt routine
ISR(SPI_STC_vect)
{
        SPDR = i++;  
        PORTA ^= (1<<PA0);  //Status LED   
}

void spi_setup() 
{
    volatile char IOReg;
    // Set PB6(MISO) as output 
    DDRB    = (1<<PB6);
    DDRA = (1 << PA0);
    SPCR    = (1<<SPIE) | (1<<SPE);
    //This stuff apparently needs to be done
    IOReg   = SPSR;
    IOReg   = SPDR;
    sei(); //Enable interrupts
}


int main() 
{
    spi_setup();
    for(;;);
}
