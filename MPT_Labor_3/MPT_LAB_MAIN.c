/*
 * MPT.c
 *
 * Created: 25.05.2012 18:12:01
 *  Author: holtv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "MPT_LAB_MAIN.h"
#include "MPT_LAB_UTIL.h"

#include "Labor_3/MPT_LAB_3_1.h"
#include "Labor_3/MPT_LAB_3_2.h"
#include "Labor_3/MPT_LAB_3_3.h"
#include "Labor_3/MPT_LAB_3_4.h"


int main(void)
{	
	//##############################################################################
	//
	// Aufgabe A_3
	//
	//##############################################################################
  //------------------------------------------------------------------------------
  // Aufgabe A_3_1: LED-Blinken mit Zeitverzögerung über 8-Bit-Timer0 und Polling des Timers.
  // A_3_1_1: Blinken einer LED mit Warten durch 8-Bit-Timer0. (nicht sichtbar)
  // A_3_1_2: Blinken einer LED mit Timer0 und mehreren Durchläufen. (sichtbar)
  // A_3_1_3: Blinken einer LED mit Timer0 und definierter Frequenz durch
  //          Vorladen des Timers.
  // A_3_1_4: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 10ms-Raster.
  // A_3_1_5: Blinken einer LED mit Warten auf Timer0 über eine Funktion im 1ms-Raster.
  //------------------------------------------------------------------------------
  //A_3_1_1();
  //A_3_1_2();
  //A_3_1_3();
  //A_3_1_4();
  //A_3_1_5();


  //------------------------------------------------------------------------------
  // Aufgabe A_3_2: LED-Blinken mit Zeitverzögerung über 8-Bit-Timer0 und 
  //                Interrupt-Betrieb des Timers über ISR in verschiedenen Betriebsarten.
  // A_3_2_1: Blinken einer LED mit ISR auf Timer-Overflow.
  // A_3_2_2: Blinken einer LED mit ISR auf Timer-Compare.
  //------------------------------------------------------------------------------
  //A_3_2_1();
  //A_3_2_2();


  //------------------------------------------------------------------------------
  // Aufgabe A_3_3: Ansteuerung eines Schrittmotors mit Zeitintervallen aus Timer0.
  // A_3_3_1: Ansteuerung Schrittmotor in festen Intervallen.
  // A_3_3_2: Ansteuerung Schrittmotor als Sekundenzeiger einer Uhr.
  // A_3_3_3: Ansteuerung Schrittmotor als Sekundenzeiger einer Uhr mit Ausschalten
  //          nach jedem Schritt.
  //------------------------------------------------------------------------------
  //A_3_3_1();
  //A_3_3_2();
  //A_3_3_3();


  //------------------------------------------------------------------------------
  // Hausaufgabe A_3_4: Entwickeln eines Reaktionstesters
  // A_3_4_1: Reaktionstester mit Zeitmessung über Timer0 und Terminalausgabe
  //------------------------------------------------------------------------------
  //A_3_4_1();



  while(1)
  {
      //TODO:: Please write your application code 
  }
}

