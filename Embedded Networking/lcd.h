// lcd.h

// Schutz vor Mehrfachinkludierung
#ifndef __LCD_H_INCLUDED__
#define __LCD_H_INCLUDED__

#include "includes.h"

// Konfiguration zum Schreiben eines Zeichens
#define DDRAM_WRITE	0x50
// Adressen für Displayzeilen
#define ZEILE_1 	0x08
#define ZEILE_2 	0x0C
// Konfiguration zum Schreiben eines Steuerbefehls
#define DDRAM 		0x40


/* Initialisiert das Display mit 4-Bit Interface 
(siehe: http://www.sprut.de/electronic/lcd/#init) */
void lcd_init(void);

/* Schreibt Text auf das Display
zeile:		Auf welche Zeile geschrieben werden soll(ZEILE_1/2)
start_pos:	Legt fest an welcher Stelle mit dem Schreiben angefangen wird
*str:		Der zu schreibende Text */
void lcd_write(unsigned char zeile, unsigned char start_pos, char *str);

/* Schreibt Zahlen auf das Display
Benötigt eigene Funktion, da lcd_write alles als ASCII interpretiert
(Z.B.: 1 wird als ASCII 1 interpretiert und nicht als die Zahl 1)
lcd_num konvertiert die Zahl nach ASCII und ruft dann lcd_write auf
(z.B.: 1 wird 0x31) */
void lcd_num(unsigned char zeile, unsigned char start_pos, char *str);

/* Lässt den Text auf dem Display "laufen" 
l:	Wie weit der Text nach Links/Rechts laufen soll 
http://www.sprut.de/electronic/lcd/#befehle */
void lcd_lauf(unsigned int l);

/* Löscht den aktuellen Displayinhalt */
void lcd_clear(void);

#endif // __LCD_H_INCLUDED__
