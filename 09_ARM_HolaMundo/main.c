/*
* Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
* Implementación de Sistemas Digitales
* Código tomado de clase
*
*
*/
#define R 0x02
#define B 0x04
#define G 0x08
const int t = 2.6666e6; // 16e6/3/2
#include <stdint.h>
//#include "tm4c123gh6pm.h"

void main(void){
    /*SYSCTL_RCGCGPIO_R |= 0x20;  // Se habilita el reloj en el puerto F
                                // Siempre se habilitan los relojes en GPIO usando uno de 32bits
*/

    (*((uint32_t *)0x400FE608)) |= 0x20;    // Se habilita el reloj en el puerto F
                                            // Siempre se habilitan los relojes en GPIO usando uno de 32bits
    (*((uint32_t *)0x4002551C)) |= 0x0E;    // Se habilita las función digital en F.1
    (*((uint32_t *)0x40025400)) |= 0x0E;    // Se habilita como salida el F.1,2,3
    (*((uint32_t *)0x400253FC)) |= 0x00;    // Se manda un 0 al puerto F
                                            // Se aplica el offset 3FC para que a máscara permita la escritura
    while(1){
        (*((uint32_t *)0x400253FC)) ^= 0x0E;
        __delay_cycles(t);
    }
}
