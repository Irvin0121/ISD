/*
 * Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
 * Implementación de Sistemas Digitales
 * Código tomado de clase
 *
 * Regular PWM con potenciómetro
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/adc.h"

uint32_t muestras = 0;
float duty = 0;
float PWM = 0;
float lineal = 0;

void main(void){

    /************************** CONFIGURACIÓN ADC **************************/
    // Habilito el reloj para el ADC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    // Habilito reloj en el puerto B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    // Configuro PB.5 como entrada analógica
    GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5);
    // Pull-Down en PB.5
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    // Configura la fuente asociada a la CPU
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    // Habilitamos la forma del secuenciador (muestrea por secuencia, hab, int, del canal 11, la primera muestra es la última muestra)
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_CH11 | ADC_CTL_END);
    // Habilitamos el secuenciador
    ADCSequenceEnable(ADC0_BASE, 3);


    /************************** CONFIGURACIÓN PWM **************************/
    // Se habilita el reloj del puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // Se habilita el PWM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    // Activa la función PWM en PF.1, Módulo 1, salida 5
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    // Configurar PF.1 como salida PWM
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    // Configura el generador 2 en cuenta descendente
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
    // El reloj está a 16MHz, si cuenta 16,000 tarda 0.001 segundos
    // por tanto se genera una frecuencia base de 1 KHz por PF.1
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 16000);
    // Configurar duty cycle de 75%
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 1600);
    // Arrancamos el PWM en el generador 2
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    // Habilitar la salida PWM
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);

    /************************** While **************************/
    while(1){
        // Iniciamos la converión analógica-digital
        ADCProcessorTrigger(ADC0_BASE, 3);

        while(!ADCIntStatus(ADC0_BASE, 3, false));
        // Almacenamos el valor en la muestra en la variable muestras
        ADCSequenceDataGet(ADC0_BASE, 3, &muestras);
        // Se
        duty = 3.3*muestras/4096;
        lineal = (duty  + 0.4206)/0.0117;
        PWM = lineal*16000/270;
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, PWM);
    }
}
