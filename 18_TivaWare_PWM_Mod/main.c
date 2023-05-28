/**
 * Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
 * Implementación de Sistemas Digitales
 * Código tomado de clase
 *
 * PWM a través de PF.1 y PF.2
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
    // Se habilita el PWM1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    // Activa la función PWM en PF.1 y PF.2, Módulo 1, salida 5 y salida
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    // Configurar PF.1 y PF.2 como salida PWM
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);

    // Configura el generador 2 y 3 en cuenta descendente
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
    // El reloj está a 16MHz, si cuenta 16,000 tarda 0.001 segundos
    // por tanto se genera una frecuencia base de 1 KHz por PF.1
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 16000);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 16000);
    //PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 16000);
    // Configurar duty cycle de PF.1
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 12000);
    // Configurar duty cycle de PF.2
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 4000);
    // Arrancamos el PWM en el generador 3
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    // Habilitar la salida PWM
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_6_BIT, true);
}











/* Para ver en PB.6
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
    // Se habilita el reloj del puerto B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    // Se habilita el PWM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    // Activa la función PWM en PB.6, Módulo 0, salida 0
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    // Configurar PB.6 como salida PWM
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    // Configura el generador 2 en cuenta descendente
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    // El reloj está a 16MHz, si cuenta 16,000 tarda 0.001 segundos
    // por tanto se genera una frecuencia base de 1 KHz por PB.6
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 16000);
    // Configurar duty cycle de 75%
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1000);
    // Arrancamos el PWM en el generador 2
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    // Habilitar la salida PWM
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
}
*/
