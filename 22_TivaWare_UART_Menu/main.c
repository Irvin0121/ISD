/**
 * Unidad Profesional Interdisciplinaria de Ingeniería Campus Zacatecas
 * Implementación de Sistemas Digitales
 * Código tomado de clase
 *
 * Comunicación UART en PA0(Rx) y PA1 (Tx)
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include <string.h>

int i = 0;
char s = ' ', opc = ' ';
const char menu[] = "Bienvenido al menú del UART \n\rIngresa alguna de las siguientes opciones:\n\r1.- Encender/Apagar LED\n\r2.- Regular intensidad del LED\n\r3.- Salir del programa";

// Prototipos de las funciones a usar
void initUART();        // Inicializa la UART en PA.0 y PA.1
void initPWM();         // Inicializa PWM en PF.1
void enviar(const char* str);
void limpiar();         // Limpia la pantalla de la terminal
void PWM();             // Entra al submenú del PWM
void LED();             // Entra al submenú del LED
void SetPWM(uint32_t dc);


void main(void){

    initUART();         // Inicializa la UART en PA.0 y PA.1
    initPWM();          // Inicializa PWM en PF.1

    while(opc != '3'){
        limpiar();
        enviar(menu);
        enviar("\n\r");

        opc = UARTCharGet(UART0_BASE);
        switch(opc){
            case '1':
                LED();
                break;
            case '2':
                PWM();
                break;
            case '3':
                break;
            default:enviar("Opción no válida\n\n\n\n\r");
        }

    }
    limpiar();
    enviar("Gracias por usar el programa\n\rHasta la próximaaaaa");
}

void enviar(const char* str){
    for (i = 0; i<strlen(str); i++){
        UARTCharPut(UART0_BASE, str[i]);
        SysCtlDelay(100000);
    }
}

void initUART(){
    /* Congifuración de UART */
    // Habilita el reloj del módulo UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Habilita el reloj al puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Se activa la función de transmisión y recepción
    // Activa la función de Rx en PB.0 asociado el módulo UART1
    GPIOPinConfigure(GPIO_PA0_U0RX);
    // Activa la función de Tx en PB.1 asociado el módulo UART1
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // Configurar los pines para el UART
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    // 8 bits de datos, 9600 Bps, 1 bit de paro, sin paridad
    UARTConfigSetExpClk(UART0_BASE, 16e6, 9600, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
}

void initPWM(){
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
    // Arrancamos el PWM en el generador 2
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    // Habilitar la salida PWM
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
}

void limpiar(){
    for(i=0; i<10; i++){
        UARTCharPut(UART0_BASE, '\n');
        SysCtlDelay(100);
    }
    UARTCharPut(UART0_BASE, '\r');

}

void LED(){
    // Configurar duty cycle
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 1);
    // Arrancamos el PWM en el generador 2
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    // Habilitar la salida PWM
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
    limpiar();
    enviar("Submenú LED \t - \t Encender/Apagar LED \n\r1.- Encender \n\r2.- Apagar \n\r3.- Salir\n\r");
    char op_LED = ' ';
    while(op_LED != '3'){
        op_LED = UARTCharGet(UART0_BASE);
        switch(op_LED){
            case '1':
                SetPWM(15999);
                SysCtlDelay(1000);
                break;
            case '2':
                SetPWM(1);
                SysCtlDelay(16000);
                break;
            case '3':
                //SetPWM(1);
                PWMGenDisable(PWM1_BASE, PWM_GEN_2);
                PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, false);
                SysCtlDelay(10000);
                break;
            default:
                break;
        }
    }
}

void PWM(){

    char op_PWM = ' ';
    limpiar();
    enviar("Submenú PWM - Regular la intensidad del LED \n\r1.- 10 % \n\r2.- 40 % \n\r3.- 80 % \n\r4.- Salir\n\r");
    uint32_t Duty = 0;
    while(op_PWM != '4'){
        op_PWM = UARTCharGet(UART0_BASE);
        switch(op_PWM){
            case '1':
                Duty =  1600;
                SysCtlDelay(1000);
                break;
            case '2':
                Duty =  6400;
                SysCtlDelay(1000);
                break;
            case '3':
                Duty =  12800;
                SysCtlDelay(1000);
                break;
            case '4':
                Duty = 1;
                break;
            default:
                break;
        }
        SetPWM(Duty);
    }


}

void SetPWM(uint32_t dc){
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, dc);
}
