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
}

//##############################################################################

// A_3_1_2: Blinken einer LED mit Timer0 und mehreren Durchläufen. (sichtbar)
void A_3_1_2(void)
{
  // IHR_CODE_HIER ...
}

//##############################################################################

// A_3_1_3: Blinken einer LED mit Timer0 und definierter Frequenz durch
//          Vorladen des Timers.
void A_3_1_3(void)
{
  // IHR_CODE_HIER ...
}

//##############################################################################

// A_3_1_4: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 10ms-Raster.
void A_3_1_4(void)
{
  // IHR_CODE_HIER ...
}

//##############################################################################

// A_3_1_5: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 1ms-Raster.
void A_3_1_5(void)
{
  // IHR_CODE_HIER ...
}

//##############################################################################

#endif /* ENABLE_A_3_1 */
#endif /* ENABLE_A_3 */


/*
 *  EoF
 */
