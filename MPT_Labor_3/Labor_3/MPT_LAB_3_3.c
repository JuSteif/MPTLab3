/******************************************************************************/
/*                                                                            */
/*              Ostfalia Hochschule für angewandte Wissenschaften             */
/*                        Fakultät für Fahrzeugtechnik                        */
/*           Institut für Fahrzeuginformatik und Fahrzeugelektronik           */
/*                             Fahrzeuginformatik                             */
/*                                                                            */
/* Paket:        MPT_LAB                                                      */
/*                                                                            */
/* Modul:        MPT_LAB_3                                                    */
/*                                                                            */
/* Beschreibung: Aufgaben 3.MPT-Labor                                         */
/*                                                                            */
/* Funktionen:   A_3_3: Ansteuerung eines Schrittmotors mit Zeitintervallen   */
/*                      aus Timer0.                                           */
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
#include "MPT_LAB_3_3.h"

#ifdef ENABLE_A_3
#ifdef ENABLE_A_3_3
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


//------------------------------------------------------------------------------
//  Interrupt Service Routinen
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Private Funktionen
//------------------------------------------------------------------------------
static void WaitTimer0_x_ms(uint16_t x_ms)
{
	// IHR_CODE_HIER ... => Aufgabe A_3_1
	TCCR0 |= (1 << CS01) | (1 << CS00);
	TCNT0 = 6;
	OCR0 = 0;
	TIMSK = 0;
	
	uint8_t waiter = 0;
	
	if(x_ms == 0){
		return;
	}
	
	while(1){
		if(BIT_IS_SET(TIFR, TOV0)){
			SET_BIT(TIFR, TOV0);
			waiter++;
			TCNT0 = 6;
			
			if(waiter >= x_ms){
				return;
			}
		}
	}
}


//------------------------------------------------------------------------------
//  Public Funktionen
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Aufgabe A_3_3: Ansteuerung eines Schrittmotors mit Zeitintervallen aus Timer0.
// A_3_3_1: Ansteuerung Schrittmotor in festen Intervallen.
// A_3_3_2: Ansteuerung Schrittmotor als Sekundenzeiger einer Uhr.
// A_3_3_3: Ansteuerung Schrittmotor als Sekundenzeiger einer Uhr mit Ausschalten
//          nach jedem Schritt.
//------------------------------------------------------------------------------

//##############################################################################

// A_3_3_1: Ansteuerung Schrittmotor in festen Intervallen.
void A_3_3_1(void)
{
	uint8_t Stepper[] = {0b0011, 0b1001, 0b1100, 0b0110};
	uint8_t StepPhase;
	uint16_t StepTime;
	
	// Richtungsregister für Port C auf Ausgang
	LED_DDR = 0b11111111;

	// Alle Bits an Port C auf '0' setzen
	LED_PORT = 0b11111111;

	// Beginnen mit Stepper[0]
	StepPhase = 0;

	// Intervall zwischen 2 Steps
	StepTime = 500;
	
	while (1)
	{
		// Aufruf der Warteroutine
		WaitTimer0_x_ms(StepTime);

		// Ausgabe Stepper-Schritt
		// Stepper ist an den Bits 4-7 angeschlossen
		PORTC = (Stepper[StepPhase]<<4);

		// Index für nächsten Stepper-Schritt berechnen
		StepPhase = (StepPhase + 1) % 4;
	}
}

//##############################################################################

// A_3_3_2: Ansteuerung Schrittmotor als Sekundenzeiger einer Uhr.
void A_3_3_2(void)
{
	// IHR_CODE_HIER ...
	uint8_t Stepper[] = {0b0011, 0b0001, 0b1001, 0b1000, 0b1100, 0b0100, 0b0110, 0b0010};
	uint8_t StepPhase;
	uint16_t StepTime;
	
	// Richtungsregister für Port C auf Ausgang
	LED_DDR = 0b11111111;

	// Alle Bits an Port C auf '0' setzen
	LED_PORT = 0b11111111;

	// Beginnen mit Stepper[0]
	StepPhase = 0;

	// Intervall zwischen 2 Steps
	StepTime = 6000 / 8;
	
	while (1)
	{
		// Aufruf der Warteroutine
		WaitTimer0_x_ms(StepTime);

		// Ausgabe Stepper-Schritt
		// Stepper ist an den Bits 4-7 angeschlossen
		PORTC = (Stepper[StepPhase]<<4);

		// Index für nächsten Stepper-Schritt berechnen
		StepPhase = (StepPhase + 1) % 8;
	}
}

//##############################################################################

// A_3_3_3: Ansteuerung Schrittmotor als Sekundenzeiger einer Uhr mit Ausschalten
//          nach jedem Schritt.
void A_3_3_3(void)
{
	// IHR_CODE_HIER ...
	uint8_t Stepper[] = {0b0011, 0b0001, 0b1001, 0b1000, 0b1100, 0b0100, 0b0110, 0b0010};
	uint8_t StepPhase;
	uint16_t StepTime;
	
	// Richtungsregister für Port C auf Ausgang
	LED_DDR = 0b11111111;

	// Alle Bits an Port C auf '0' setzen
	LED_PORT = 0b11111111;

	// Beginnen mit Stepper[0]
	StepPhase = 0;

	// Intervall zwischen 2 Steps
	StepTime = 6000 / 8;
	
	while (1)
	{
		// Aufruf der Warteroutine
		WaitTimer0_x_ms(StepTime * 0.2f);

		// Ausgabe Stepper-Schritt
		// Stepper ist an den Bits 4-7 angeschlossen
		PORTC = (Stepper[StepPhase]<<4);
		
		WaitTimer0_x_ms(StepTime * 0.8f);
		
		PORTC = 0x0;

		// Index für nächsten Stepper-Schritt berechnen
		StepPhase = (StepPhase + 1) % 8;
	}
}

//##############################################################################

#endif /* ENABLE_A_3_3 */
#endif /* ENABLE_A_3 */

/*
*  EoF
*/
