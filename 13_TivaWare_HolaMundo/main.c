#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

void main(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    // Habilitamos el reloj al puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);   // Se habilita F.1,.2,.3 como salida
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);  // Se habilita F.4 como entrada (SW1)
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);    // Pull-up en F.4

    while(1){
        if(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)){  // Se lee F.4
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0E); // Se escribe un 1 en F.1,.2,.3
            SysCtlDelay(1e5);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // Se escribe un 0 en F.1,.2,.3
            SysCtlDelay(1e5);
        }
        else
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // Se escribe un 0 en F.1,.2,.3
    }
}
