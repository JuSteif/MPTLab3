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
/* Funktionen:   A_3_1: LED-Blinken mit Zeitverzögerung über 8-Bit-Timer0     */
/*                      und Polling des Timers.                               */
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
#include "MPT_LAB_3_1.h"

#ifdef ENABLE_A_3
#ifdef ENABLE_A_3_1
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
static void WaitTimer0_x_10ms(uint8_t x_10ms)
{
	// IHR_CODE_HIER ...
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCNT0 = 100;
	OCR0 = 0;
	TIMSK = 0;
	
	uint8_t waiter = 0;
	
	if(x_10ms == 0){
		return;
	}
	
	while(1){
		if(BIT_IS_SET(TIFR, TOV0)){
			SET_BIT(TIFR, TOV0);
			waiter++;
			TCNT0 = 100;
			
			if(waiter >= x_10ms){
				return;
			}
		}
	}
}

static void WaitTimer0_x_ms(uint16_t x_ms)
{
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
// Aufgabe A_3_1: LED-Blinken mit Zeitverzögerung über 8-Bit-Timer0 und Polling des Timers.
// A_3_1_1: Blinken einer LED mit Warten durch 8-Bit-Timer0. (nicht sichtbar)
// A_3_1_2: Blinken einer LED mit Timer0 und mehreren Durchläufen. (sichtbar)
// A_3_1_3: Blinken einer LED mit Timer0 und definierter Frequenz durch
//          Vorladen des Timers.
// A_3_1_4: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 10ms-Raster.
// A_3_1_5: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 1ms-Raster.
//------------------------------------------------------------------------------

//##############################################################################

// A_3_1_1: Blinken einer LED mit Warten durch 8-Bit-Timer0. (nicht sichtbar)
void A_3_1_1(void)
{
	// IHR_CODE_HIER ...
	LED_DDR = 0xff;
	LED_PORT = 0xff;
	
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCNT0 = 0;
	OCR0 = 0;
	TIMSK = 0;
	
	uint8_t waiter = 0;
	
	while(1){
		if(BIT_IS_SET(TIFR, TOV0)){
			SET_BIT(TIFR, TOV0);
			waiter++;
			
			if(waiter > 30){
				TGL_BIT(LED_PORT, 0);
				waiter = 0;
			}
		}
	}
}

//##############################################################################

// A_3_1_2: Blinken einer LED mit Timer0 und mehreren Durchläufen. (sichtbar)
void A_3_1_2(void)
{
	// IHR_CODE_HIER ...
	LED_DDR = 0xff;
	LED_PORT = 0xff;
	
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCNT0 = 0;
	OCR0 = 0;
	TIMSK = 0;
	
	uint8_t waiter = 0;
	
	while(1){
		if(BIT_IS_SET(TIFR, TOV0)){
			SET_BIT(TIFR, TOV0);
			waiter++;
			
			if(waiter > 29){
				TGL_BIT(LED_PORT, 0);
				waiter = 0;
			}
		}
	}
}

//##############################################################################

// A_3_1_3: Blinken einer LED mit Timer0 und definierter Frequenz durch
//          Vorladen des Timers.
void A_3_1_3(void)
{
	// IHR_CODE_HIER ...
	LED_DDR = 0xff;
	LED_PORT = 0xff;
	
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCNT0 = 100;
	OCR0 = 0;
	TIMSK = 0;
	
	uint8_t waiter = 0;
	
	while(1){
		if(BIT_IS_SET(TIFR, TOV0)){
			SET_BIT(TIFR, TOV0);
			waiter++;
			TCNT0 = 100;
			
			if(waiter > 24){
				TGL_BIT(LED_PORT, 0);
				waiter = 0;
			}
		}
	}
}

//##############################################################################

// A_3_1_4: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 10ms-Raster.
void A_3_1_4(void)
{
	// IHR_CODE_HIER ...
	LED_DDR = 0xff;
	LED_PORT = 0xff;
	
	while(1){
		TGL_BIT(LED_PORT, 0);
		WaitTimer0_x_10ms(25);
	}
}

//##############################################################################

// A_3_1_5: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 1ms-Raster.
void A_3_1_5(void)
{
	// IHR_CODE_HIER ...
	LED_DDR = 0xff;
	LED_PORT = 0xff;
	
	while(1){
		TGL_BIT(LED_PORT, 0);
		WaitTimer0_x_ms(200);
	}
}

//##############################################################################

#endif /* ENABLE_A_3_1 */
#endif /* ENABLE_A_3 */


/*
*  EoF
*/
