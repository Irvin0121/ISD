/**
 * Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
 * Implementación de Sistemas Digitales
 * Código tomado de clase
 *
 * Enciende y apaga los leds de forma alternada
 */

#include <msp430.h> 

void main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;  // Configuro P1.0 como salida
	P4DIR |= BIT7;  // Configuro P4.7 como salida

	// Inicialización de los leds
	P1OUT |= BIT0;  // Enciendo el led 1.0
	P4OUT &= ~BIT7; // Apago el led 4.7
	
	// Ciclo infinito
	while(1){
	    P1OUT ^= 0x01;  // Alternamos encendido/apagado
	    P4OUT ^= 0x80;  // Alternamos encendido/apagado
	    __delay_cycles(1e6);
	}
}
