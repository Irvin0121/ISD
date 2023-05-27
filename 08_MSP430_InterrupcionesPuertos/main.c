/**
* Unidad Profesional Interdisciplinaria de Ingenier�a Campus Zacatecas
* Implementaci�n de Sistemas Digitales
*
*
*
*/

#include <msp430.h> 

void main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Configuraci�n de puertos
	P1DIR |= BIT0;              // Se configura P1.0 como salida (LED rojo)
	P1OUT &= ~BIT0;             // Se apaga el LED
	P2DIR &= ~BIT1;             // Se configura P2.1 como entrada (bot�n)
	P2REN |= BIT1;              // Se habilita la resistencia interna
	P2OUT |= BIT1;              // Se conecta como Pull-up
	// Configuraci�n de la interrupci�n
	P2IE |= BIT1;               // Se habilita en P2.1 la interrupci�n externa
	P2IES |= BIT1;              // Se configura la interrupci�n en flanco de bajada
	__bis_SR_register(LPM4_bits + GIE); // Se habilita el modo de bajo consumo m�ximo y se habilitan las interrupciones
	__no_operation();
}

#pragma vector = PORT2_VECTOR
__interrupt void PUERTOS (void){     // Rutina de interrupci�n
    P1OUT ^= BIT0;              // Prende y apaga el LED
    P2IFG &= ~BIT1;             // Se limpia la bandera de interrupci�n (permite que vuelva a haber una interrupci�n)
}
