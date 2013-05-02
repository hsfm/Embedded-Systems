// i2c.h

// Schutz vor Mehrfachinkludierung
#ifndef __I2C_H_INCLUDED__
#define __I2C_H_INCLUDED__

#include "includes.h"

// sleep-zeit
#define DELAY_L 		1000
#define DELAY_S 		50
// Datenrichtungen für den Bus
#define WRITE 			0x03
#define READ 			0x00
// Globale Festlegung des Ports/Registers
#define PORT 			PORTB
#define DDR 			DDRB
// PB0
#define 				SCL 0
// PB1
#define 				SDA 1
// Macros zum setzen von sda/scl
#define SET_SCL(mode)	set_mode(SCL, mode)
#define SET_SDA(mode)	set_mode(SDA, mode)
// Warte Mikrosekunden
#define US(time) 		_delay_us(time)
// Warte Millisekunden
#define MS(time) 		_delay_ms(time)

/* Erlaubt das setzen von sda/scl mithilfe eines Makros: SET_SXX(1/0)
bit:	Welches Bit soll gesetzt werden (PB0 für SCL PB1 für SDA)
mode:	Entscheidet ob die Leitung High(1) oder Low(0) geschaltet wird */
void set_mode(unsigned char bit, unsigned char mode);

/* Setze Datenrichtung auf dem I2C-Bus auf lesen/schreiben 
v:	Die Datenrichtung, kann entweder READ oder WRITE sein. */
void set_ddr(unsigned char v);

/* Bereitet die Leitung auf den Datentransfer vor (siehe fig5_start and stop) */
void start_condition(void);

/* Zeigt an, dass der Datentransfer beendet wurde (siehe fig5_start and stop) */
void stop_condition(void);

/* Legt fest an welche Adresse zukünftige Daten gesendet werden
fügt automatisch das "Schreib"-Bit (0) ein.
(siehe fig14_1st byte after START (address)) 
address:	Die Adresse, kann in Binär (0b)oder Hexadezimal(0x) angegeben werden. 
(siehe: figh. 14 The first byte after the START procedure) */
void address_7_write(unsigned char address);

/* Schreibt ein Datenbyte an die vorher festgelegte Addresse 
byte:	Das Byte welches gesendet werden soll, 
		kann in Binär (0b)oder Hexadezimal(0x) angegeben werden.*/
void data_write(unsigned char byte);

#endif // __I2C_H_INCLUDED__
