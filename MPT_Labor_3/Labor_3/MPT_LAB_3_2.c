/******************************************************************************/
/*                                                                            */
/*              Ostfalia Hochschule f�r angewandte Wissenschaften             */
/*                        Fakult�t f�r Fahrzeugtechnik                        */
/*           Institut f�r Fahrzeuginformatik und Fahrzeugelektronik           */
/*                             Fahrzeuginformatik                             */
/*                                                                            */
/* Paket:        MPT_LAB                                                      */
/*                                                                            */
/* Modul:        MPT_LAB_3                                                    */
/*                                                                            */
/* Beschreibung: Aufgaben 3.MPT-Labor                                         */
/*                                                                            */
/* Funktionen:   A_3_2: LED-Blinken mit Zeitverz�gerung �ber 8-Bit-Timer0 und */
/*                      Interrupt-Betrieb des Timers �ber ISR in              */
/*                      verschiedenen Betriebsarten.                          */
/*                                                                            */
/* Version:      1.0 / 120716 / V. v. Holt                                    */
/*                                                                            */
/******************************************************************************/

//------------------------------------------------------------------------------
//  Headerdateien
//------------------------------------------------------------------------------
// Allgemeine Headerdateien
#include <avr/io.h>
#include <avr/interrupt.h>

// Eigene Headerdateien
#include "MPT_LAB_MAIN.h"
#include "MPT_LAB_UTIL.h"
#include "MPT_LAB_3_2.h"

#ifdef ENABLE_A_3
#ifdef ENABLE_A_3_2
//------------------------------------------------------------------------------
//  Makro-/Konstantendefinitionen
//------------------------------------------------------------------------------
#define LED_DDR     DDRC
#define LED_PORT    PORTC
#define LED_DELAY   50
#define TASTER_DDR  DDRB
#define TASTER_PIN  PINB


//------------------------------------------------------------------------------
//  Private Variablen
//------------------------------------------------------------------------------
// �berlaufz�hler - global damit sowohl von der ISR wie aus den Funktionen
//                  darauf zugegriffen werden kann
int16_t OvCnt;


//------------------------------------------------------------------------------
//  Interrupt Service Routinen
//------------------------------------------------------------------------------
// Interrupt-Service-Routine f�r den Interrupt bei �berlauf des Timer0
// ISR: Schl�sselwort f�r Compiler, dass dies eine ISR ist
// TIMER0_OVF_vect: Information an den Compiler, mit welchem Interrupt
//                  diese ISR verkn�pft werden soll. Der Bezeichner "TIMER0_OVF_vect"
//                  ist wie alle anderen ISR-Bezeichner in "avr/interrupt.h" definiert.
ISR(TIMER0_OVF_vect)
{
	// Z�hlerstandsregister reinitialisieren
	TCNT0 = 256-250;

	// �berlaufz�hler inkrementieren
	OvCnt++;
	// Nach 100 �berl�ufen = 100ms
	if (OvCnt == 2000)
	{
		// �berlaufz�hler zur�cksetzen
		OvCnt = 0;
		
		// LED toggeln
		TGL_BIT(LED_PORT,LED_0);
	}
}


// Interrupt-Service-Routine f�r den Interrupt bei Vergleich des Timer0
// ISR: Schl�sselwort f�r Compiler, dass dies eine ISR ist
// TIMER0_COMP_vect: Information an den Compiler, mit welchem Interrupt
//                   diese ISR verkn�pft werden soll. Der Bezeichner "TIMER0_COMP_vect"
//                   ist wie alle anderen ISR-Bezeichner in "avr/interrupt.h" definiert.
ISR(TIMER0_COMP_vect)
{
	// IHR_CODE_HIER ...
	// �berlaufz�hler inkrementieren
	OvCnt++;
	TCNT0 = 0;
	// Nach 100 �berl�ufen = 100ms
	if (OvCnt == 2000)
	{
		// �berlaufz�hler zur�cksetzen
		OvCnt = 0;
		
		// LED toggeln
		TGL_BIT(LED_PORT,LED_0);
	}
}


//------------------------------------------------------------------------------
//  Private Funktionen
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Public Funktionen
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Aufgabe A_3_2: LED-Blinken mit Zeitverz�gerung �ber 8-Bit-Timer0 und
//                Interrupt-Betrieb des Timers �ber ISR in verschiedenen Betriebsarten.
// A_3_2_1: Blinken einer LED mit ISR auf Timer-Overflow.
// A_3_2_2: Blinken einer LED mit ISR auf Timer-Compare.
//------------------------------------------------------------------------------

//##############################################################################

// A_3_2_1: Blinken einer LED mit ISR auf Timer-Overflow.
void A_3_2_1(void)
{
	// Richtungsregister f�r die LEDs initialisieren
	LED_DDR = 0b11111111;

	// Alle LEDs aus!
	LED_PORT = 0b11111111;

	// �berlaufz�hler zur�cksetzen
	OvCnt = 0;

	// Timer0 initialisieren
	// Z�hlerstandsregister initialisieren
	TCNT0 = 256-250;
	// Vergleichsregister zur�cksetzen
	OCR0  = 0;
	// Konfigurationsregister:
	// WGM01:0 = Normaler Betrieb
	// COM01:0 = Normaler Betrieb
	// CS02:0  = Vorteiler 64
	TCCR0 = (0<<WGM01) | (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<CS02) | (1<<CS01) | (1<<CS00); 

	// Interruptmaskenregister setzen:
	// TOIE0: INT ausl�sen bei �berlauf Timer0 inaktiv
	// OCIE0: INT ausl�sen bei Vergleich Timer0 aktiv
	TIMSK |= (1<<TOIE0) | (0<<OCIE0);

	// Interrupts global freigeben
	sei();
	
	while (1)
	{
		// nichts mehr zu tun ... vorerst
	}
}

//##############################################################################

// A_3_2_2: Blinken einer LED mit ISR auf Timer-Compare.
void A_3_2_2(void)
{
	// IHR_CODE_HIER ...
	// Richtungsregister f�r die LEDs initialisieren
	LED_DDR = 0b11111111;

	// Alle LEDs aus!
	LED_PORT = 0b11111111;

	// �berlaufz�hler zur�cksetzen
	OvCnt = 0;

	// Timer0 initialisieren
	// Z�hlerstandsregister initialisieren
	TCNT0 = 0;
	// Vergleichsregister setzen
	OCR0  = 249;
	// Konfigurationsregister:
	// WGM01:0 = Normaler Betrieb
	// COM01:0 = Normaler Betrieb
	// CS02:0  = Vorteiler 64
	TCCR0 = (0<<WGM01) | (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<CS02) | (1<<CS01) | (1<<CS00);

	// Interruptmaskenregister setzen:
	// TOIE0: INT ausl�sen bei �berlauf Timer0 aktiv
	// OCIE0: INT ausl�sen bei Vergleich Timer0 inaktiv
	TIMSK |= (0<<TOIE0) | (1<<OCIE0);

	// Interrupts global freigeben
	sei();
	
	while(1){
		
	}
}

//##############################################################################

#endif /* ENABLE_A_3_2 */
#endif /* ENABLE_A_3 */

/*
*  EoF
*/
