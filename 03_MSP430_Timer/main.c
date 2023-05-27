/**
 * Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
 * Implementación de Sistemas Digitales
 * Código tomado de clase
 *
 *
 */

#include <msp430.h> 

int i = 0;                          // Contador

void main(void){
	WDTCTL = WDTPW | WDTHOLD;	    // stop watchdog timer

	// Configurar la salida
	P1DIR |= BIT0;                  // Se declara 1.0 como salida

	// Configuración del Timer
	TA0CTL |= TASSEL_2 | MC_3;      // Se selecciona la fuente auxiliar del reloj - ACLK (32_768 Hz) con Modo up
	TA0CCR0 = 0x8000;               // 32_768
	TA0CCTL0 |= CCIE;               // Habilita la interrupción en el registro CC
	_BIS_SR(LPM0_bits + GIE);       // Modo de bajo consumo (Duerme el CPU) | GIE Habilita las interrupciones (General Interruption Enable)
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0 (void){     // Rutina de interrupción
    if(i++ == 10){
        P1OUT ^= BIT0;              // Apaga/prende el LED1
        i = 0;
    }
}
