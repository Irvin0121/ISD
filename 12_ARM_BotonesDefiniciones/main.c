#include <tm4c123gh6pm.h>
#include <stdint.h>

void main(void){
    SYSCTL_RCGCGPIO_R |= (1<<5);                            //
    // Configuración del GPIO
    GPIO_PORTF_DEN_R |= (1<<1) | (1<<2) | (1<<3) |(1<<4);   // Habilito la función digital en el puerto F.1,.2,.3,.4
    GPIO_PORTF_DIR_R |= (1<<1) | (1<<2) | (1<<3);           // Se pone F.1,.2,.3 como salida
    GPIO_PORTF_DIR_R &= ~(1<<4);                            // Se pone F.4 como entrada
    GPIO_PORTF_PUR_R |= (1<<4);                             // Se pone F.4 con Pull-up

    while(1){
        if( !(GPIO_PORTF_DATA_R & (1<<4))){
            __delay_cycles(1e6);
        } else{
            __delay_cycles(16e6);
        }
        GPIO_PORTF_DATA_R ^= (1<<1) ^(1<<2) ^(1<<3);
    }

}
