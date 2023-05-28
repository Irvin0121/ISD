/**
 * Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
 * Implementación de Sistemas Digitales
 * Código tomado de clase
 *
 * PWM a través de PF.1
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"

void main(void){
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
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 15000);
    // Arrancamos el PWM en el generador 2
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    // Habilitar la salida PWM
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
}
