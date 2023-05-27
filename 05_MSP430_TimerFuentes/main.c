/**
 * Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
 * Implementación de Sistemas Digitales
 * Generar una señal de:
 * 1 kHz
 * 100 kHz
 *
 */

#include <msp430.h> 

void main(void){
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // Configurar la salida
    P6DIR |= BIT5;                  // Se declara 1.0 como salida
    P6OUT &=~ BIT5;                 // Se apaga el pin 6.5

    // Configuración del Timer
    TA0CCTL0 |= CCIE;               // Habilita la interrupción en el registro CC

    // Para 100 kHz
    TA0CTL |= TASSEL__SMCLK | MC__UPDOWN;       // Se selecciona la fuente SMCLK (1.045 MHz) con Modo up -> 1.045MHz*(1/250Hz)=4180
    TA0CCR0 = 4180;


    _BIS_SR(LPM0_bits + GIE);       // Modo de bajo consumo (Duerme el CPU) | GIE Habilita las interrupciones (General Interruption Enable)
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0 (void){     // Rutina de interrupción
    if( !(P2IN & 0x02) ){
        TA0CCR0 =  4180;            // 500 Hz
    } else{
        TA0CCR0 = 2090;             // 1 kHz
    }
    P6OUT ^= BIT5;                  // Apagar y prender el P6.5

}
