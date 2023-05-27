#include "MyLibrary.h"

void main(void){
    SYSCTL |= BIT5;                 // Se habilita el reloj en el puerto F
    PORTF_EN |= BIT1 | BIT2 | BIT3;               // Habilitar el puerto F con función digital en F.1
    PFDIR |= BIT1 | BIT2 | BIT3;    // PF.1,.2,.3 como salidas

    while(1){
        PFOUT ^= BIT1 ^BIT2 ^BIT3;    // Togglear el F.1,.2,.3
        __delay_cycles(16e6);           // Esperar 16MHz
    }
}
