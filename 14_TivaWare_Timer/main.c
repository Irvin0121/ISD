#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"


int i = 0;
void timerOut(void);

void main(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        // Se habilita el reloj en el puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);   // Se habilita F.1,.2,.3 como salida
    // Configuración del timer
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);       // Se habilita el reloj al timer0
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);    // Se configura que sea modo periódico en el timer0
    TimerLoadSet(TIMER0_BASE, TIMER_A, 8e6);           // Se establece el límite de conteo
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);    // Se habilitan las interrupciones en el timerA
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerOut);   // Asocia el nombre de la función con el manejador de la interrupción del timer0,A
    IntEnable(INT_TIMER0A);                             // Habilita la interrupción del timer por parte del NVIC
    IntMasterEnable();                                  // Habilita las int de forma general
    TimerEnable(TIMER0_BASE, TIMER_A);                  // Habilita la operación del Timer A

}

void timerOut(void){
    if(i == 0){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0E);
        i++;
    }
    else{
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        i=0;
    }
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
