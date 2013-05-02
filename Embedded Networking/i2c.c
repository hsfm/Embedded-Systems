// i2c.c

#include "i2c.h"

/* Erlaubt das setzen von sda/scl mithilfe eines Makros: SET_SXX(1/0)
bit:	Welches Bit soll gesetzt werden (PB0 für SCL PB1 für SDA)
mode:	Entscheidet ob die Leitung High(1) oder Low(0) geschaltet wird */
void set_mode(unsigned char bit, unsigned char mode)
{
	if(mode == 1)
	{
		PORT |= (1 << bit);
	}
	if(mode == 0)
	{
		PORT &= ~(1 << bit);
	}
}

/* Setze Datenrichtung auf dem I2C-Bus auf lesen/schreiben 
v:	Die Datenrichtung, kann entweder READ oder WRITE sein. */
void set_ddr(unsigned char v)
{
	DDR = v;
}

/* Bereitet die Leitung auf den Datentransfer vor (siehe fig5_start and stop) */
void start_condition(void)
{
	// setze beide H
	SET_SDA(1);
	SET_SCL(1);
	US(DELAY_S);
	
	// setze sda L für START
	SET_SDA(0);
	US(DELAY_S);
	SET_SCL(0);
	US(DELAY_S);
	// beide sind nun L und Leitung ist bereit für Übertragung	
}

/* Zeigt an, dass der Datentransfer beendet wurde (siehe fig5_start and stop) */
void stop_condition(void)
{
	// Bereite Leitung für STOP vor
	SET_SDA(0);
	SET_SCL(1);
	US(DELAY_S);	
	
	// Erzeuge STOP
	SET_SDA(1);
	US(DELAY_S);
}

/* Legt fest an welche Adresse zukünftige Daten gesendet werden
fügt automatisch das "Schreib"-Bit (0) ein.
(siehe fig14_1st byte after START (address)) 
address:	Die Adresse, kann in Binär (0b)oder Hexadezimal(0x) angegeben werden. 
(siehe: figh. 14 The first byte after the START procedure) */
void address_7_write(unsigned char address)
{
	// setze Schreib-Bit (0)
	address &= ~(1 << 0);
	data_write(address);		
}

/* Schreibt ein Datenbyte an die vorher festgelegte Addresse 
byte:	Das Byte welches gesendet werden soll, 
		kann in Binär (0b)oder Hexadezimal(0x) angegeben werden.*/
void data_write(unsigned char byte)
{	
	// Byte muss aufgrund eines Glitches Invertiert werden
	byte = ~byte;
	// Aktuelles Bit
	unsigned int bit;
	// Maske zum abfragen gesetzter Bits in byte
	unsigned char mask = 0x80;
	// Setze beide L als Vorbereitung für Übertragung	
	SET_SDA(0);
	SET_SCL(0);
	US(DELAY_S);	
	// Prüfe jedes Bit im zu sendenden Byte
	for(bit = 0; bit < 8; bit++)
	{
		// Falls Bit gesetzt sende HIGH
		if(!((mask >> bit) & byte))
		{
			SET_SDA(1);
			US(DELAY_S);
			SET_SCL(1);			
			US(DELAY_S);
			
			SET_SCL(0);
			US(DELAY_S);
			SET_SDA(0);
			US(DELAY_S);
		}
		else // Falls Bit nicht gesetzt sende LOW
		{
			SET_SDA(0);
			US(DELAY_S);
			SET_SCL(1);
			US(DELAY_S);
			
			SET_SCL(0);
			US(DELAY_S);
			SET_SDA(0); 
			US(DELAY_S);
		}
	}	
	// sende ACK	
	SET_SDA(1);
	US(DELAY_S);		
	set_ddr(READ);
	SET_SCL(1);
	US(DELAY_S);
	SET_SCL(0);
	set_ddr(WRITE);
}
