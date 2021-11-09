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
/* Funktionen:   A_3_4: Ansteuerung eines Schrittmotors als Scheibenwischer.  */
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
#include <stdlib.h>

// Eigene Headerdateien
#include "MPT_LAB_MAIN.h"
#include "MPT_LAB_UTIL.h"
#include "MPT_LAB_3_4.h"

#ifdef ENABLE_A_3
#ifdef ENABLE_A_3_4
//------------------------------------------------------------------------------
//  Makro-/Konstantendefinitionen
//------------------------------------------------------------------------------
#define LED_DDR     DDRC
#define LED_PORT    PORTC
#define LED_DELAY   50
#define TASTER_DDR  DDRB
#define TASTER_PIN  PINB

// Makrodefinitionen für Start- und Stoptaste
#define TASTER_START 7
#define TASTER_STOP 6

//Faktoren für besseres Testen 
#define TIME_FAKTOR 100
#define WAIT_EN 0


//------------------------------------------------------------------------------
//  Private Variablen
//------------------------------------------------------------------------------
//Statusspeicher, Arbeitsweise mit Statemashine
static uint8_t state = 0;
//Millisekundenzähler für Reaktionszeitmessungen
static uint16_t milliSec = 0;

//------------------------------------------------------------------------------
//  Interrupt Service Routinen
//------------------------------------------------------------------------------
//Routine um Millisekunden zu messen und den Miilisekundencounter zu inkrementieren
ISR(TIMER0_COMP_vect)
{
	milliSec++;
	TCNT0 = 0;
}

//(Zusätzlich) Routine zu Interupt basierten Verarbeitung
ISR(INT2_vect){
	state = 3;
	GICR &= ~(1 << INT2);
}

//(Zusätzlich) Hilfe: Terminal hat Hilfe durch senden von 'h' angefordert
ISR(USART_RXC_vect){
	if(UDR == 'h'){
		//Hilfestellungstext
		UsartPuts("Taster 7 ist Start\nTaster 6 ist Stopp(Normal)\nTaster 2 ist Stopp(Interupt verarbeitet mit INT2)\n");
	}
}

//------------------------------------------------------------------------------
//  Private Funktionen
//------------------------------------------------------------------------------
static void WaitTimer0_x_10ms(uint8_t x_10ms)
{
	// IHR_CODE_HIER ...
	//Initialisierung der Timer
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCNT0 = 100;
	OCR0 = 0;
	TIMSK = 0;
	
	//Wait Variable einfügen zum Vergleich mit der Variable x_10ms
	uint8_t waiter = 0;
	
	//Sofortiges beenden der Funktions, falls nicht gewartet werden soll
	if(x_10ms == 0){
		return;
	}
	
	while(1){
		//Überprüfung des Overflow-Flags
		if(BIT_IS_SET(TIFR, TOV0)){
			//Rücksetzen des Overflow-Flags
			SET_BIT(TIFR, TOV0);
			//Wait Variable inkrementieren, zählt in 10ms-Schritten
			waiter++;
			//TCNT0 auf Startwert setzen
			TCNT0 = 100;
			
			//Abbruchbedingung, wenn wait gleich der x_10ms ist ist die Wartezeit vorbei
			if(waiter >= x_10ms){
				return;
			}
		}
	}
}

//Funktion zum potenzieren
int potenz(int basis, int exponent){
	int result = 1;
	for(int i = 0; i < exponent; i++){
		result *= basis;
	}
	return result;
}

char* uint16ToString(uint16_t number){
	//Anzahl an Ziffern feststellen
	uint16_t num = number;
	uint8_t len = 0;
	while(num >= 1){
		num = number / potenz(10, len);
		len++;
	}
	
	//Setzen der min Laenge auf 5, da Zeit in Sek angegeben werden soll.
	//Komma, 3 Nachkommastellen und Einer
	if(len < 4){
		len = 4;
	}
	len++;
	
	//String anlegen, mit vorreserviertem Speicher
	char* result;
	result = malloc(sizeof(char) * len);
	
	for(int8_t i = len - 1; i >= 0; i--){
		//If Abfrage, um Komma an richtige Position zu setzen
		if(i == len - 4){
			char zeichen = ',';
			result[i] = zeichen;
			continue;
		}
		//Letzte Ziffer in entsprechendes ASCII-Zeichen umwandeln
		char zeichen = (number % 10) + '0';
		result[i] = zeichen;
		//number neu berechnen, sodass die nächste Ziffer im folgenden Schleifendurchlauf abgespeichert werden kann
		number = number / 10;
	}
	
	//String zurück geben
	return result;
}

//------------------------------------------------------------------------------
//  Public Funktionen
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Hausaufgabe A_3_4: Entwickeln eines Reaktionstesters
// A_3_4_1: Reaktionstester mit Zeitmessung über Timer0 und Terminalausgabe
//------------------------------------------------------------------------------

//##############################################################################

// A_3_4_1: Reaktionstester mit Zeitmessung über Timer0 und Terminalausgabe
void A_3_4_1(void)
{
	// IHR_CODE_HIER ...
	
	//Taster und LED´s initialisieren
	TASTER_DDR = 0x00;
	LED_DDR = 0xff;
	LED_PORT = 0xff;
	
	//USART-Schnittstelle initialisieren und Interupt für empfangene Daten aktivieren
	UsartInit(8,0,1,9600);
	SET_BIT(UCSRB, 7);
	
	//Timer initialisiern und zugehörige Interupts.(Zur Bestimmung einer zufälligen Wartezeit)
	TCCR0 = (0<<WGM01) | (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<CS02) | (0<<CS01) | (1<<CS00);
	TIMSK |= (0<<TOIE0) | (0<<OCIE0);
	OCR0 = 0;
	TCNT0 = 0;
	
	// Speichervariable für zufällige Speicherzeit
	uint8_t waitTime = 1;
	// Speichervariable für zufällige LED
	uint8_t led = 0;
	// String für die konvertierte Reaktionszeit
	char* reactionTime = "Fehler";
	
	// Startaufforderung an Terminal senden
	UsartPuts("Start drücken:\n");
	
	while(1){
		// switch für Statemaschine
		switch(state){
			//Case 0: Bildet den Start des Reaktionsspiels. Bevor Startknopf gedrückt wurde
			case 0:
				//Abfrage ob Spiel gestartet werden soll
				if(BIT_IS_SET(TASTER_PIN, TASTER_START)){
					// Neuen Status setzen(Start angefordert)
					state = 1;
					// Zufaellige Wartezeit- und LED-wahl
					// Pseudozufall, da nicht vorhersehbar und kann nur schwer von menchlichem Spieler beeinflusst werden.
					// An zufälligem Zeitpunkt wird Timerregister ausgelesen
					waitTime = TCNT0 % 10 + 1;
					led = TCNT0 % 8;
					//Entprellen der Taste
					WaitTimer0_x_10ms(5 * WAIT_EN);
					
					//Warten, bis Starttaste wieder losgelassen wurde
					while (BIT_IS_SET(TASTER_PIN, TASTER_START))
					{
					}
				}
				break;
			// Case 1: Start angefordert nachdem Start gedrückt wurde
 			case 1:
					// zufällige Zeit warten
					WaitTimer0_x_10ms(waitTime * TIME_FAKTOR * WAIT_EN);
					// Beschiss vermeiden, falls jemand schon den Stoptaster drückt bevor Lampe leuchtet
					if(BIT_IS_SET(TASTER_PIN, 6) || BIT_IS_SET(TASTER_PIN, 2)){
						UsartPuts("Nimm die Botten weg und Bescheis nicht!");
						while(BIT_IS_SET(TASTER_PIN, 6) || BIT_IS_SET(TASTER_PIN, 2)) {
							
						}
					}
					
					//Timer neu initialisieren, da jetzt in 1ms Schritten gezählt wird, und nicht in 10ms.
					TCCR0 |= (1 << CS01) | (1 << CS00);
					TCCR0 &= ~(1 << CS02);
					TIMSK |= (0<<TOIE0) | (1<<OCIE0);
					OCR0 = 249;
					milliSec = 0;
					TCNT0 = 0;
					// Neuen State bestimmen(Auf Stop warten)
					state = 2;
					// Interupts aktivieren
					sei();
					// LED aktivieren
					SET_BIT(LED_PORT, led);
					
					//(Zusaetzlich) Externen Interupt auf PB2 aktivieren(aufsteigende Flanke) 
					GICR |= (1 << INT2);
					MCUCSR |= (1 << ISC2);
				break;
			//Case 2: Auf Stop warten, bis der Nutzer die 6. Taste drückt oder die 2.
			case 2:
				// Kontinuierliche Abfrage des 6. Tasters(Alternativ Taster 2 drücken, basiert auf Interuptverarbeitung, ansonsten gleiches Prinzip)
				if(BIT_IS_SET(TASTER_PIN, 6)){
					// state auf 3 setzen(Auswertung)
					state = 3;
				}
				break;
			// Case 3: Auswertung des Spiels, letzter Status
			case 3:
				// Interupt für Timer deaktivieren
				TIMSK &= ~(1 << OCIE0);
				// Reaktionszeit von uint16_t in String konvertieren
				reactionTime = uint16ToString(milliSec);
				// Reaktionszeit an Terminal senden
				UsartPuts("Deine Reaktionszeit sind ");
				UsartPuts(reactionTime);
				UsartPuts("sek.\n");
				// Folgestatus setzen 0(Auf Neustart warten)
				state = 0;
				// Für die konvertierte Reaktionszeit reservierten Speicher auf dem Heap wieder freigeben
				free(reactionTime);
				// Vorausetzungen für den Neustart schaffen
				UsartPuts("Start drücken:\n");
				LED_PORT = 0xff;
				
				// Warten auf das Loslassen der Stoptaster
				while(BIT_IS_SET(TASTER_PIN, 6) || BIT_IS_SET(TASTER_PIN, 2)){
					
				}
				break;
			// defaultsollte nicht eintreten
			default:
				// Ausgabe Fehlermeldung und von Vorne anfangen
				UsartPuts("Fehler aufgetreten!\n");
				state = 0;
				break;
		}
	}
}

//##############################################################################

#endif /* ENABLE_A_3_4 */
#endif /* ENABLE_A_3 */

/*
*  EoF
*/
