/**
 * Unidad Profesional Interdisciplinaria de Ingenier�a Campus Zacatecas
 * Implementaci�n de Sistemas Digitales
 * C�digo tomado de clase
 *
 * Comunicaci�n UART en PB0(Rx) y PB1 (Tx)
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
char str[] = "Hola mundo";

void enviar(const char* str);

void main(void){
    // Habilita el reloj del m�dulo UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Habilita el reloj al puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Se activa la funci�n de transmisi�n y recepci�n
    // Activa la funci�n de Rx en PB.0 asociado el m�dulo UART1
    GPIOPinConfigure(GPIO_PA0_U0RX);
    // Activa la funci�n de Tx en PB.1 asociado el m�dulo UART1
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // Configurar los pines para el UART
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    // 8 bits de datos, 9600 Bps, 1 bit de paro, sin paridad
    UARTConfigSetExpClk(UART0_BASE, 16e6, 9600, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);

    enviar(str);
}

void enviar(const char* str){
    for (i = 0; i<strlen(str); i++){
        UARTCharPut(UART0_BASE, str[i]);
    }
}
