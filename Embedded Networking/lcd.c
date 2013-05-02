#include "lcd.h"
#include <stdio.h>
#include <ctype.h>

/*
Allgemeiner Aufbau der zu übertragenden Bytes
2 Byte sind ein Befehl
D E R/S R/W + high_nibble
D E R/S R/W + low_nibble
*/

/* Initialisiert das Display mit 4-Bit Interface 
(siehe: http://www.sprut.de/electronic/lcd/#init) */
void lcd_init(void)
{		
	// 15 ms
	MS(16);
	data_write(0x43);
	data_write(0x00);

	// 4.1 ms
	MS(5);
	data_write(0x43);
	data_write(0x00);
	
	// 100 µs
	US(110);
	data_write(0x43);
	data_write(0x00);

	// auf 4 bit setzen 
	data_write(0x42);
	data_write(0x00);
	
	// matrix 
	data_write(0x42);
	data_write(0x00);
	data_write(0x48);
	data_write(0x00);
	
	// display aus	
	data_write(0x40);
	data_write(0x00); 		
	data_write(0x48);
	data_write(0x00);

	// display löschen
	data_write(0x40);
	data_write(0x00);
	data_write(0x41);
	data_write(0x00);

	// cursor rechts, kein display shift
	data_write(0x40);
	data_write(0x00);
	data_write(0x46);
	data_write(0x00);

	// display ein
	data_write(0x40);
	data_write(0x00);
	data_write(0x4C);
	data_write(0x00);
}

/* Schreibt Text auf das Display
zeile:		Auf welche Zeile geschrieben werden soll(ZEILE_1/2)
start_pos:	Legt fest an welcher Stelle mit dem Schreiben angefangen wird
*str:		Der zu schreibende Text */
void lcd_write(unsigned char zeile, unsigned char start_pos, char *str)
{
	unsigned int i = 0;
	// character high nibble
	unsigned char high_nibble;
	// character low nibble
	unsigned char low_nibble;		

	// Addresse für Zeichen	
	data_write(DDRAM | zeile);
	data_write(0x00);
	data_write(0x40 | start_pos);
	data_write(0x00);

	// Jedes Zeichen im String muss einzeln gesendet werden
	while(!(str[i] == '\0'))
	{		
		// high nibble des aktuellen Zeichens ermitteln
		high_nibble = 0xF0 & str[i];
		// high nibble auf low nibble schieben
		high_nibble = (high_nibble >> 4);

		// low nibble des aktuellen Zeichens ermitteln
		low_nibble = 0x0F & str[i];

		data_write(DDRAM_WRITE | high_nibble);
		data_write(0x00);		
		data_write(DDRAM_WRITE | low_nibble);
		data_write(0x00);
		i++;
	}	
}

/* Schreibt Zahlen auf das Display
Benötigt eigene Funktion, da lcd_write alles als ASCII interpretiert
(Z.B.: 1 wird als ASCII 1 interpretiert und nicht als die Zahl 1)
lcd_num konvertiert die Zahl nach ASCII und ruft dann lcd_write auf
(z.B.: 1 wird 0x31) */
void lcd_num(unsigned char zeile, unsigned char start_pos, char *str)
{
	char buf[5];	
	
	sprintf(buf, "%d", str);
	lcd_write(zeile, start_pos, buf);
}

/* Lässt den Text auf dem Display "laufen" 
l:	Wie weit der Text nach Links/Rechts laufen soll 
(siehe: http://www.sprut.de/electronic/lcd/#befehle) */
void lcd_lauf(unsigned int l)
{
	unsigned int i;	
	for(;;)
	{
		// Lasse Text nach Links laufen
		for(i = 0; i < l; i++)
		{
			data_write(0x41);
			data_write(0x00);
			data_write(0x48);
			data_write(0x00);
			MS(1000);
		}
		// Lasse Text nach Rechts laufen
		for(i = 0; i < l; i++)
		{
			data_write(0x41);
			data_write(0x00);
			data_write(0x4C);
			data_write(0x00);			
			MS(1000);
		}
	}
}

/* Löscht den aktuellen Displayinhalt */
void lcd_clear(void)
{
	// display löschen
	data_write(0x40);
	data_write(0x00);
	data_write(0x41);
	data_write(0x00);
}
