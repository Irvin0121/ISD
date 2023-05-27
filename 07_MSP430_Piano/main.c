/*
* Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
* Implementación de Sistemas Digitales
* Piano
*
*
*/
int id = 4;
#define do3 501/id  // Do C4
#define re3 446/id  // Re D4
#define mi3 398/id  // Mi E4
#define fa3 375/id  // Fa F4
#define sol3 334/id  // Sol G4
#define la3 298/id  // La A4
#define si3 265/id  // Si B4
#define do4 250/id  // Do C4
#define re4 223/id  // Re D4
#define mi4 199/id  // Mi E4
#define fa4 188/id  // Fa F4
#define sol4 167/id  // Sol G4
#define la4 149/id  // La A4
#define si4 133/id  // Si B4



#include <msp430.h> 
unsigned int estado = 0;

int frecuencia(int freq);
void main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// Configuraciones de salidas y entradas
	P6DIR |= BIT0;              // Se habilita P6.0 como salida del buzzer
	P2DIR &= ~BIT1;             // Se habilita P2.1 como entrada
	P2REN |= BIT1;              // Se habilita la resistencia
	P2OUT |= BIT1;              // Se conecta a Vcc
	// Configuración del timer
	TA0CTL |= TASSEL__ACLK | MC__UP;    // Fuente auxiliar (32768) y modo Up
	TA0CCR0 = 0x10;             // Cuenta hasta 16
	TA0CCTL0 |= CCIE;           // Se habilitan las interrupciones de captura comparador
	_BIS_SR(LPM0_bits + GIE);   // Modo de bajo consumo (Duerme el CPU) | GIE Habilita las interrupciones (General Interruption Enable)
	
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0 (void){     // Rutina de interrupción

    // Lógica de estado siguiente
    if (estado == 0 && !(P2IN & BIT1))
        estado = 1;
    if (estado == 1 && (P2IN & BIT1))
        estado = 2;
    if (estado == 2 && !(P2IN & BIT1))
        estado = 3;
    if (estado == 3 && (P2IN & BIT1))
        estado = 4;
    if (estado == 4 && !(P2IN & BIT1))
        estado = 5;
    if (estado == 5 && (P2IN & BIT1))
        estado = 6;
    if (estado == 6 && !(P2IN & BIT1))
        estado = 7;
    if (estado == 7 && (P2IN & BIT1))
        estado = 8;
    if (estado == 8 && !(P2IN & BIT1))
        estado = 9;
    if (estado == 9 && (P2IN & BIT1))
        estado = 10;
    if (estado == 10 && !(P2IN & BIT1))
        estado = 11;
    if (estado == 11 && (P2IN & BIT1))
        estado = 12;
    if (estado == 12 && !(P2IN & BIT1))
        estado = 13;
    if (estado == 13 && (P2IN & BIT1))
        estado = 14;
    if (estado == 14 && !(P2IN & BIT1))
        estado = 15;
    if (estado == 15 && !(P2IN & BIT1))
            estado = 16;
        if (estado == 16 && (P2IN & BIT1))
            estado = 17;
        if (estado == 17 && !(P2IN & BIT1))
            estado = 18;
        if (estado == 18 && (P2IN & BIT1))
            estado = 19;
        if (estado == 19 && !(P2IN & BIT1))
            estado = 20;
        if (estado == 20 && (P2IN & BIT1))
            estado = 21;
        if (estado == 21 && !(P2IN & BIT1))
            estado = 22;
        if (estado == 22 && (P2IN & BIT1))
            estado = 23;
        if (estado == 23 && !(P2IN & BIT1))
            estado = 24;
        if (estado == 24 && (P2IN & BIT1))
            estado = 25;
        if (estado == 25 && !(P2IN & BIT1))
            estado = 26;
        if (estado == 26 && (P2IN & BIT1))
            estado = 27;
        if (estado == 27 && !(P2IN & BIT1))
            estado = 28;
        if (estado == 28 && (P2IN & BIT1))
            estado = 29;
        if (estado == 29 && !(P2IN & BIT1))
            estado = 0;

    switch (estado){
    case 1:
        TA0CCR0 = mi4;
        break;
    case 2:
        TA0CCR0 = fa4;
        break;
    case 3:
        TA0CCR0 = sol4;
        break;
    case 4:
        TA0CCR0 = sol4;
        break;
    case 5:
        TA0CCR0 = fa4;
        break;
    case 6:
        TA0CCR0 = mi4;
        break;
    case 7:
        TA0CCR0 = re4;
        break;
    case 8:
        TA0CCR0 = do4;//frecuencia(500);
        break;
    case 9:
        TA0CCR0 = do4;//frecuencia(500);
        break;
    case 10:
        TA0CCR0 = re4;//frecuencia(500);
        break;
    case 11:
        TA0CCR0 = mi4;//frecuencia(500);
        break;
    case 12:
        TA0CCR0 = mi4;//frecuencia(500);
        break;
    case 13:
        TA0CCR0 = re4;//frecuencia(500);
        break;
    case 14:
        TA0CCR0 = re4;//frecuencia(500);
        break;
    case 15:
            TA0CCR0 = mi4;
            break;
    case 16:
            TA0CCR0 = mi4;
            break;
        case 17:
            TA0CCR0 = fa4;
            break;
        case 18:
            TA0CCR0 = sol4;
            break;
        case 19:
            TA0CCR0 = sol4;
            break;
        case 20:
            TA0CCR0 = fa4;
            break;
        case 21:
            TA0CCR0 = mi4;
            break;
        case 22:
            TA0CCR0 = re4;
            break;
        case 23:
            TA0CCR0 = do4;//frecuencia(500);
            break;
        case 24:
            TA0CCR0 = do4;//frecuencia(500);
            break;
        case 25:
            TA0CCR0 = re4;//frecuencia(500);
            break;
        case 26:
            TA0CCR0 = mi4;//frecuencia(500);
            break;
        case 27:
            TA0CCR0 = re4;//frecuencia(500);
            break;
        case 28:
            TA0CCR0 = do4;//frecuencia(500);
            break;
        case 29:
            TA0CCR0 = do4;//frecuencia(500);
            break;
    default:
        TA0CCR0 =mi4;
        break;
    }

    P6OUT ^= BIT0;
}

int frecuencia(int freq){
    freq = 10;
    return freq;
}
