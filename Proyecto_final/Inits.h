/*
 * Inits.h
 *
 *  Created on: 13 may 2023
 *      Author: irvin
 */

#ifndef INITS_H_
#define INITS_H_

int tim = 0;

void timerOut(void){
    if(tim == 0){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0E);
        tim++;
    }
    else{
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        tim=0;
    }
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

void initUART(){
    /* Inicialización del UART por los puertos PA.0(Rx) y PA.1(Tx), 8 bits de datos, 9600 Bps, 1 bit de paro, sin paridad */

    // Habilita el reloj del módulo UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Habilita el reloj al puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Se activa la función de transmisión y recepción
    // Activa la función de Rx en PA.0 asociado el módulo UART1
    GPIOPinConfigure(GPIO_PA0_U0RX);
    // Activa la función de Tx en PA.1 asociado el módulo UART1
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // Configurar los pines para el UART
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    // 8 bits de datos, 9600 Bps, 1 bit de paro, sin paridad
    UARTConfigSetExpClk(UART0_BASE, 16e6, 9600, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
}

void initPWM(){

    /* Inicialización del PWM por el puerto PF.1 (Led rojo)*/
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
    // Configurar duty cycle
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 1);
}

void initTimer(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);       // Se habilita el reloj al timer0
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);    // Se configura que sea modo periódico en el timer0
    TimerLoadSet(TIMER0_BASE, TIMER_A, 8e6);            // Se establece el límite de conteo
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);    // Se habilitan las interrupciones en el timerA
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerOut);   // Asocia el nombre de la función con el manejador de la interrupción del timer0,A
    IntEnable(INT_TIMER0A);                             // Habilita la interrupción del timer por parte del NVIC
    IntMasterEnable();                                  // Habilita las int de forma general
    TimerEnable(TIMER0_BASE, TIMER_A);                  // Habilita la operación del Timer A
}

void initADC(){

}

void PWMSetState(int state){
    if(state == 1){
        // Configurar duty cycle inicial de 1 (Apagado)
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 1);
        // Arrancamos el PWM en el generador 2
        PWMGenEnable(PWM1_BASE, PWM_GEN_2);
        // Habilitar la salida PWM
        PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
    } else{
        // Deshabilitar la salida PWM
        PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, false);
        // Se apaga el generador 2
        PWMGenDisable(PWM1_BASE, PWM_GEN_2);
    }
}

void TimerSetState(int State){
    if(State == 1){
        TimerEnable(TIMER0_BASE, TIMER_A);                  // Habilita la operación del Timer A
    } else{
        TimerDisable(TIMER0_BASE, TIMER_A);                 // Deshabilita la operación del Timer A
    }
}

void ADCSetState(int State){
    if(State == 1){

    } else{

    }
}

#endif /* INITS_H_ */
