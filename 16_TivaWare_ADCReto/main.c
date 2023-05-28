// Si el voltaje leído es mayor a 1.65 volts, enciente el led rojo, en caso
// contrario se apaga

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/adc.h"

uint32_t muestras;

void main(void){
    // Configuración del LED rojo
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    // Configuración del ADC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);     // Habilito el reloj para el ADC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    // Habilito reloj en el puerto B
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);    // Configuro PB.5 como entrada analógica
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);    // Pull-Down en PB.5
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0); // Configura la fuente asociada a la CPU
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_CH8 | ADC_CTL_END); // Habilitamos la forma del secuenciador (muestrea por secuencia, hab, int, del canal 11, la primera muestra es la última muestra)
    ADCSequenceEnable(ADC0_BASE, 3);    // Habilitamos el secuenciador

    while(1){
        ADCProcessorTrigger(ADC0_BASE, 3);  // Iniciamos la converión analógica-digital
        //SysCtlDelay(100);   // Tiempo muerto para que haga la conversión el ADC
        while(!ADCIntStatus(ADC0_BASE, 3, 0));
        ADCSequenceDataGet(ADC0_BASE, 3, &muestras);    // Almacenamos el valor en la muestra en la variable muestras
        if(muestras > 2048)
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);  // Enciende el led rojo
        else
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);           // Apaga el led rojo
    }
}
