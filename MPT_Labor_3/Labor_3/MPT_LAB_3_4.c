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

#define TASTER_START 7
#define TASTER_STOP 6

#define TIME_FAKTOR 1
#define WAIT_EN 0


//------------------------------------------------------------------------------
//  Private Variablen
//------------------------------------------------------------------------------
static uint8_t state = 0;
static uint16_t milliSec = 0;

//------------------------------------------------------------------------------
//  Interrupt Service Routinen
//------------------------------------------------------------------------------
ISR(TIMER0_COMP_vect)
{
	milliSec++;
	TCNT0 = 0;
}

ISR(INT2_vect){
	state = 3;
}

ISR(USART_RXC_vect){
	if(UDR == 'h'){
		UsartPuts("Taster 7 ist Start\nTaster 6 ist Stopp(Normal)\nTaster 2 ist Stopp(Interupt verarbeitet mit INT2)\n");
	}
}

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

int potenz(int basis, int exponent){
	int result = 1;
	for(int i = 0; i < exponent; i++){
		result *= basis;
	}
	return result;
}

char* uint16ToString(uint16_t number){
	uint16_t num = number;
	uint8_t len = 0;
	while(num >= 1){
		num = number / potenz(10, len);
		len++;
	}
	
	if(len < 4){
		len = 4;
	}
	len++;
	
	char* result;
	result = malloc(sizeof(char) * len);
	
	for(int8_t i = len - 1; i >= 0; i--){
		if(i == len - 4){
			char zeichen = ',';
			result[i] = zeichen;
			continue;
		}
		char zeichen = (number % 10) + '0';
		result[i] = zeichen;
		number = number / 10;
	}
	
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
	
	TASTER_DDR = 0x00;
	LED_DDR = 0xff;
	
	UsartInit(8,0,1,9600);
	SET_BIT(UCSRB, 7);
	
	TCCR0 = (0<<WGM01) | (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<CS02) | (0<<CS01) | (1<<CS00);
	TIMSK |= (0<<TOIE0) | (0<<OCIE0);
	OCR0 = 0;
	TCNT0 = 0;
	
	uint8_t waitTime = 1;
	uint8_t led = 0;
	char* reactionTime = "Fehler";
	
	while(1){
		switch(state){
			case 0:
				UsartPuts("Start drücken:\n");
				if(BIT_IS_SET(TASTER_PIN, TASTER_START)){
					state = 1;
					waitTime = TCNT0 % 10 + 1;
					led = TCNT0 % 7;
					WaitTimer0_x_10ms(5 * WAIT_EN);
					
					while (BIT_IS_SET(TASTER_PIN, TASTER_START))
					{
					}
				}
				break;
 			case 1:
					WaitTimer0_x_10ms(waitTime * TIME_FAKTOR * WAIT_EN);
					if(BIT_IS_SET(TASTER_PIN, 6) || BIT_IS_SET(TASTER_PIN, 2)){
						UsartPuts("Nimm die Botten weg und Bescheis nicht!");
						while(BIT_IS_SET(TASTER_PIN, 6) || BIT_IS_SET(TASTER_PIN, 2)) {
							
						}
					}
					TCCR0 |= (1 << CS01) | (1 << CS00);
					TCCR0 &= ~(1 << CS02);
					TIMSK |= (0<<TOIE0) | (1<<OCIE0);
					OCR0 = 249;
					milliSec = 0;
					state = 2;
					sei();
					SET_BIT(LED_PORT, led);
					TCNT0 = 0;
					
					GICR |= (1 << INT2);
					MCUCSR |= (1 << ISC2);
				break;
			case 2:
				if(BIT_IS_SET(TASTER_PIN, 6)){
					state = 3;
				}
				break;
			case 3:
				GICR &= ~(1 << INT2);
				TIMSK &= ~(1 << OCIE0);
				reactionTime = uint16ToString(milliSec);
				UsartPuts("Deine Reaktionszeit sind ");
				UsartPuts(reactionTime);
				UsartPuts("sek.\n");
				state = 0;
				free(reactionTime);
				
				while(BIT_IS_SET(TASTER_PIN, 6)){
					
				}
				break;
			default:
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
