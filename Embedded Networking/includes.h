// includes.h

/* Bündelt alle benötigten Header-Dateien in einer Datei */

#define F_CPU 1000000UL	// Taktfrequenz der CPU (ggf. anpassen)

#include <avr/io.h>
#include <util/delay.h>

#include "i2c.h"
#include "lcd.h"
