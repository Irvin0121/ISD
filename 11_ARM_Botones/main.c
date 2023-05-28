#include <MyLibrary_V1.h>

#define R   0x02
#define B   0x04
#define G   0x06

unsigned Nint barrido = 0x02;

void main(void){
    SYSCTL |= BIT5;                 // Se habilita el reloj en el puerto F
    PORTF_EN |= BIT1 | BIT2 | BIT3 | BIT4;               // Habilitar el puerto F con función digital en F.1
    PFDIR |= BIT1 | BIT2 | BIT3;    // PF.1,.2,.3 como salidas
    PFDIR &= ~BIT4;                 // PF.4 como entrada
    PF_PU |= BIT4;                  // Se habilita el pull-up en PF.4

    while(1){
        if( !(PFIN & BIT4) ){
            __delay_cycles(4e6);
        }
        else{
            __delay_cycles(4e5);
        }
        PFOUT ^= barrido;

        if(barrido == 8){
            barrido = 2;
        }
        else
            barrido *= 2;

    }
}
