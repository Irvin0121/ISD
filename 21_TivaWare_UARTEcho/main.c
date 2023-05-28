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
#include <string.h>

int i = 0;
char s = ' ', s_ant=' ';

void enviar(const char* str);
void parpadeo();
void main(void){
    /* Configuración del LED */
    // Habilita el reloj al puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // Se configura como salida los pines F.1,.2,.3
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

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

    while(1){
        s = UARTCharGet(UART0_BASE);
        // Si se recibe un 1 se encienden los LEDS
        if(s == '1'){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
            enviar("LED encendido\n\r");
        }
        else if(s == '0'){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
            enviar("LED apagado\n\r");
        }
        else
            parpadeo();
    }
}

void enviar(const char* str){
    for (i = 0; i<strlen(str); i++){
        UARTCharPut(UART0_BASE, str[i]);
    }
}

void parpadeo(){
    enviar("Elige un 1 o 0\n\r");
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
    for(i=0; i<2; i++){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        SysCtlDelay(160000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        SysCtlDelay(160000);
    }
}
