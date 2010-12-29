#include <WProgram.h>
#include <avr/io.h>

#define SPI_SCK 13
#define SPI_MISO 12
#define SPI_MOSI 11
#define SPI_SS 10

char SPI_SlaveReceive(void)
{
    SPDR = 0x00;
    
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)))
    ;
    /* Return Data Register */
    return SPDR;
}


void setup() {
    // Set MISO as output
    pinMode(SPI_MISO, OUTPUT);
    
    /* Enable SPI */
    SPCR = (1<<SPE);
    
    // Clear SPIF bit in SPSR
    volatile char IOReg;
    IOReg   = SPSR;
    IOReg   = SPDR;
    
    // Serial communication with computer
    Serial.begin(9600);
    
    Serial.println("SPI:");
}

char d;

void loop() {
    d = SPI_SlaveReceive();
    
    Serial.println(d, HEX);
//    Serial.println();
}

