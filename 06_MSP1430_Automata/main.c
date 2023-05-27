/**
* Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
* Implementación de Sistemas Digitales
* Tarea 2
*
* Implementar una máquina de estados que funcione de la siguiente manera con los LEDS 1 y 2
* Estado 0:
* 00
* Estado 1: Se presiona el botón (y si sigue presionando)
* 01
* Estado 2: Se suelta
* 10
* Estado 3: Se presiona (y si sigue presionando)
* 11
* Se suelta y regresa al estado inicial
*
*/

#include <msp430.h> 

unsigned char estado = 'A';

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// Configuración de GPIO
	P1DIR |= BIT0;              // Se habilita P1.0 como salida
	P4DIR |= BIT7;              // Se habilita P4.7 como salida
	P2DIR |= BIT1;              // Se habilita 2.1 como entrada
	P2REN |= BIT1;              // Se habilita la resistencia
	P2OUT |= BIT1;              // Se conecta a Vcc
	// Configuración del timer
	TA0CTL |= TASSEL__ACLK | MC__UP;    // Fuente auxiliar (32768) y modo Up
	TA0CCR0 = 0x10;             // Cuenta hasta 16
	TA0CCTL0 |= CCIE;            // Se habilitan las interrupciones de captura comparador
	_BIS_SR(LPM0_bits + GIE);       // Modo de bajo consumo (Duerme el CPU) | GIE Habilita las interrupciones (General Interruption Enable)
	
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0 (void){     // Rutina de interrupción
    // Lógica de estado siguiente
    if (estado == 'A' && !(P2IN & BIT1))
        estado = 'B';
    if (estado == 'B' && (P2IN & BIT1))
        estado = 'C';
    if (estado == 'C' && !(P2IN & BIT1))
        estado = 'D';
    if (estado == 'D' && (P2IN & BIT1))
        estado = 'A';
    // Lógica de salida
    switch (estado){
    case 'B':
        P1OUT &= ~BIT0;
        P4OUT ^= BIT7;
        break;
    case 'C':
        P1OUT ^= BIT0;
        P4OUT &= ~BIT7;
        break;
    case 'D':
        P1OUT ^= BIT0;
        P4OUT ^= BIT7;
        break;
    default:
        P1OUT &= ~BIT0;
        P4OUT &= ~BIT7;
        break;
    }
}
