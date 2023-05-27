/**
* Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
* Implementación de Sistemas Digitales
* Código tomado de clase
*
* Enciende y apaga los leds de forma alternada cuando se presiona el botón
*/

#include <msp430.h> 
int i = 0;

void main(void){
WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
// Configuración de los pines
P1DIR |= BIT0;  // Configuro P1.0 como salida
P4DIR |= BIT7;  // Configuro P4.7 como salida
P2DIR &=~ BIT1; // Se pone un 0 en el bit, configura 2.1 como entrada
P2REN |= 0x02;  // Habilita la resistencia pull-up
P2OUT |= 0x02;  // Conecto a Vcc la resistencia en 2.1

// Inicialización de los leds
P1OUT |= 0x01;  // Enciendo el led 1.0
P4OUT &= ~0x80; // Apago el led 4.7

// Ciclo infinito
while(1){
    if( !(P2IN & 0x02) ){    // Si presiono
        P1OUT |= 0x01;  // Enciendo el led 1.0
        P4OUT &= ~0x80; // Apago el led 4.7
    } else{
        P1OUT &=~ 0x01;     // Apaga 1.0
        P4OUT &=~ 0x80;     // Apaga 4.7
    }
}
}
