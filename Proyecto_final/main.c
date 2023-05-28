/**
 * Unidad Profesional Interdisciplinaria de Ingenier�a Campus Zacatecas
 * Implementaci�n de Sistemas Digitales
 * C�digo hecho por: Irvin Adolfo Ram�rez Torres
 *
 * Men� del TM4C123G
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
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include <string.h>

int i = 0, tim = 0;
uint32_t muestras;
char s = ' ', opc = ' ';
const char menu[] = "Bienvenido al men� del UART \n\rIngresa alguna de las siguientes opciones:\n\r1.- Encender/Apagar LED\n\r2.- Regular intensidad del LED\n\r3.- Generar un tono en el Buzzer \n\r4.- Leer el ADC \n\r5.- Salir del programa\n\r";

/************************************************************
 *                                                          *
 *          Prototipos de las funciones a usar              *
 *                                                          *
 ************************************************************/
/************* Funciones de inicializar los m�dulos ***********/
void initUART();                // Inicializa el m�dulo UART
void initPWM();                 // Inicializa el m�dulo PWM en PF.1
void initTimer();               // Inicializa el m�dulo Timer
void initADC();                 // Inicializa el m�dulo ADC en PB.6
void initGPIO();                // Inicializa el PB.5 como salida (Buzzer)

/******** Funciones de activar/desactivar los m�dulos *********/
void PWMSetState(int state);    // Activa/desactiva el m�dulo PWM
void TimerSetState(int state);  // Activa/desactiva el m�dulo Timer
void ADCSetState(int state);    // Activa/desactiva el m�dulo ADC

/****************** Funciones de los submen�s *****************/
void PWM();                     // Entra al submen� del PWM
void LED();                     // Entra al submen� del LED
void Timer();                   // Entra al submen� del Timer
void ADC();                     // Entra al submen� del ADC

/******************** Funciones auxiliares *******************/
void enviar(const char* str);   // Env�a la cadena pasada como par�metro
void enviarnum(float num);   // Env�a un n�mero
void limpiar();                 // Limpia la pantalla de la terminal
void SetPWM(uint32_t dc);       // Pone el PWM indicado (con una frecuencia base de 16kHz)
void SetTimer(int tim);         // Pone el timer indicado (100, 200 y 1200 Hz disponibles)
void TimerOut();                // Interrupci�n del timer en PB.5






/************************************************************
 *                                                          *
 *                      Funci�n main                        *
 *                                                          *
 ************************************************************/
void main(void){

    initUART();                 // Inicializa la UART en PA.0 y PA.1
    initPWM();                  // Inicializa PWM en PF.1
    initTimer();                // Inicializa Timer en
    initADC();                  // Inicializa ADC en
    initGPIO();                 // Inicializa PB.5 como salida

    while(opc != '5'){
        limpiar();
        enviar(menu);

        opc = UARTCharGet(UART0_BASE);
        switch(opc){
            case '1':           // Controlar el encendido del LED
                LED();
                break;
            case '2':           // Controlar la intensidad del LED
                PWM();
                break;
            case '3':           // Controlar tono de un buzzer
                Timer();
                break;
            case '4':           // Leer valor del ADC
                ADC();
                break;
            case '5':
                break;
            default:
                enviar("Opci�n no v�lida");
                limpiar();
        }

    }
    limpiar();
    enviar("Gracias por usar el programa\n\rHasta la pr�ximaaaaa");
}



/************************************************************
 *                                                          *
 *              Funciones de los submen�s                   *
 *                                                          *
 ************************************************************/

// Opci�n 1 - Controlar el encendido/apagado de un LED
void LED(){
    PWMSetState(1);             // Habilita el m�dulo PWM
    limpiar();
    enviar("Submen� LED \t - \t Encender/Apagar LED \n\r1.- Encender \n\r2.- Apagar \n\r3.- Salir\n\r");
    char op_LED = ' ';
    while(op_LED != '3'){
        op_LED = UARTCharGet(UART0_BASE);
        switch(op_LED){
            case '1':           // Led encendido
                SetPWM(15999);
                break;
            case '2':           // Led apagado
                SetPWM(1);
                break;
            case '3':           // Salir del submen� y apagar el m�dulo PWM
                PWMSetState(0); // Deshabilita el m�dulo PWM
                break;
            default:
                break;
        }
    }
}


/* Opci�n 2 - Controlar la intensidad de un LED*/
void PWM(){
    PWMSetState(1);             // Habilita el m�dulo PWM
    char op_PWM = ' ';          // Variable donde se guarda la opci�n le�da
    uint32_t Duty = 0;          // Variable donde se indica el ciclo de trabajo (base de 16kHz)
    limpiar();
    enviar("Submen� PWM - Regular la intensidad del LED \n\r1.- 10 % \n\r2.- 40 % \n\r3.- 80 % \n\r4.- Salir\n\r");

    while(op_PWM != '4'){
        op_PWM = UARTCharGet(UART0_BASE);
        switch(op_PWM){
            case '1':           // Intensidad al 10%
                Duty =  1600;
                break;
            case '2':           // Intensidad al 40%
                Duty =  6400;
                break;
            case '3':           // Intensidad al 80%
                Duty =  12800;
                break;
            case '4':           // Salir del submen� y apagar m�dulo PWM
                PWMSetState(0);
                break;
            default:
                break;
        }
        SetPWM(Duty);           // Settea el ciclo de trabajo indicado seg�n la opci�n
    }

}

/* Opci�n 3 - Generar un tono por medio de un buzzer*/
void Timer(){
    TimerSetState(1);           // Habilita el m�dulo Timer
    char op_Timer = ' ';        // Variable donde se guarda la opci�n le�da
    uint32_t Timer = 0;         // Variable donde se indica el tono (base de 16MHz)
    limpiar();
    enviar("Submen� Timer - Generar un tono en el buzzer \n\r1.- Tono 100Hz \n\r2.- Tono 200Hz \n\r3.- Tono 1200Hz \n\r4.- Salir\n\r");

    while(op_Timer != '4'){
        op_Timer = UARTCharGet(UART0_BASE);
        switch(op_Timer){
            case '1':           // Tono 100 Hz
                Timer = 100;
                break;
            case '2':           // Tono 200 Hz
                Timer = 200;
                break;
            case '3':           // Tono 1.2 kHz
                Timer = 1200;
                break;
            case '4':           // Salir del submen� y apagar m�dulo Timer
                TimerSetState(0);
                break;
            default:
                break;
        }
        SetTimer(Timer);        // Pone la frecuencia indicada en el timer
    }

}

/* Opci�n 4 - Leer el valor de un potenci�metro*/
void ADC(){
    ADCSetState(1);             // Habilita el m�dulo ADC
    char op_ADC = ' ';          // Variable que guarda la opci�n le�da
    int32_t sal = -1;           // Variable que lee la opci�n mientras se ejecuta el ADC
    float voltaje=0;            // Variable para operar el voltaje le�do
    limpiar();
    enviar("Submen� ADC - Leer el valor del ADC \n\r1.- Leer potenci�metro \n\r2.- Salir \n\r");
    while(op_ADC != '2'){
        op_ADC = UARTCharGet(UART0_BASE);
        switch(op_ADC){
        case '1':               // Leer potenci�metro
            while(sal == -1){
                ADCProcessorTrigger(ADC0_BASE, 3);              // Iniciamos la converi�n anal�gica-digital
                while(!ADCIntStatus(ADC0_BASE, 3, 0));          // Espera a que termine la conversi�n
                ADCSequenceDataGet(ADC0_BASE, 3, &muestras);    // Almacenamos el valor en la muestra en la variable muestras
                // Linealizacion de potenci�metro
                voltaje = muestras*3.3/4096;
                voltaje = (voltaje + 0.4206)/0.0117;
                voltaje = voltaje*3.3/270;
                UARTCharsAvail(UART0_BASE);                     // Determina si hay un caracter disponible en el registro
                sal = UARTCharGetNonBlocking(UART0_BASE);       // Obtiene el caracter recibido en el registro sin pararse
                limpiar();
                enviarnum(voltaje);                             // Env�a el n�mero le�do para mostrar en la terminal
                SysCtlDelay(1e6);
            }
            op_ADC = '2';
            break;
        case '2':               // Salir del submen� y apaga el m�dulo ADC
            ADCSetState(0);     // Deshabilita el m�dulo ADC
            break;
        default:
            break;
        }
    }
}



/************************************************************
 *                                                          *
 *                   Funciones auxiliares                   *
 *                                                          *
 ************************************************************/

/* Env�a la cadena que le llega como par�metro*/
void enviar(const char* str){
    for (i = 0; i<strlen(str); i++){        // Obtiene la longitud de la cadena
        UARTCharPut(UART0_BASE, str[i]);    // Manda cada caracter de la cadena
        SysCtlDelay(100);
    }
}

/* Env�a un float de 1 entero y 2 decimales*/
void enviarnum(float num){
    num *= 100;                 // Se convierte para que est� en centenas
    int num2 = (int)num;        // Se castea a entero para operar con el m�dulo
    int res=0;                  // Variable para guardar el resultado
    int d = 100;                // M�dulo a aplicar
    for(i=0; i<3; i++){         // Se operan centenas, decenas y unidades
        res = num2/d;           // Obtiene las centenas y decenas
        num2 %= d;          // Actualiza el n�mero quitando las centenas y decenas
        UARTCharPut(UART0_BASE, res+48);    // Se suma un 48 para posicionarlo seg�n el caracter en ASCII
        SysCtlDelay(100);       // Se espera 100 ciclos
        if(i==0){               // Se pone un "." despu�s del primer d�gito
            UARTCharPut(UART0_BASE, '.');
            SysCtlDelay(100);
        }
        d /= 10;                // Se disminuye el m�dulo a aplicar
    }
}

/* Env�a saltos de l�nea y retorno de carro para limpiar la terminal*/
void limpiar(){                 // Limpia la pantalla
    for(i=0; i<10; i++){        // Pone 10 saltos de l�nea
        UARTCharPut(UART0_BASE, '\n');
        SysCtlDelay(100);
    }
    UARTCharPut(UART0_BASE, '\r');  // Retorno de carro
}

/* Funci�n para poner el PWM deseado (con base de 16 kHz)*/
void SetPWM(uint32_t dc){
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, dc);
}

// Funci�n para poner el l�mite seg�n la frecuencia deseada
void SetTimer(int tim){
    switch(tim){                // Selecciona la frecuencia indicada
        case 100:               // 100 HZ
            TimerLoadSet(TIMER0_BASE, TIMER_A, 80000);
            break;
        case 200:               // 200 Hz
            TimerLoadSet(TIMER0_BASE, TIMER_A, 40000);
            break;
        case 1200:              // 1200 Hz
            TimerLoadSet(TIMER0_BASE, TIMER_A, 6666);
            break;
        default:
            break;
    }
}

/* Funci�n manejadora de la interrupci�n de Timer*/
void timerOut(void){
    if(tim == 0){
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);  // Prende el pin PB.5
        tim++;
    }
    else{
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);   // Apaga el pin PB.5
        tim=0;
    }
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);     // Limpia la bandera de interrupci�n para permitir que otra entre de nuevo
}




/************************************************************
 *                                                          *
 *              Funciones de inicializaci�n                 *
 *                                                          *
 ************************************************************/

/* Inicializaci�n del UART por los puertos PA.0(Rx) y PA.1(Tx), 8 bits de datos, 9600 Bps, 1 bit de paro, sin paridad */
void initUART(){

    // Habilita el reloj del m�dulo UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Habilita el reloj al puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Se activa la funci�n de transmisi�n y recepci�n
    // Activa la funci�n de Rx en PA.0 asociado el m�dulo UART1
    GPIOPinConfigure(GPIO_PA0_U0RX);
    // Activa la funci�n de Tx en PA.1 asociado el m�dulo UART1
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // Configurar los pines para el UART
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    // 8 bits de datos, 9600 Bps, 1 bit de paro, sin paridad
    UARTConfigSetExpClk(UART0_BASE, 16e6, 9600, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
}

/* Inicializaci�n del PWM por el puerto PF.1 (Led rojo)*/
void initPWM(){

    // Se habilita el reloj del puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // Se habilita el PWM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    // Activa la funci�n PWM en PF.1, M�dulo 1, salida 5
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    // Configurar PF.1 como salida PWM
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    // Configura el generador 2 en cuenta descendente
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
    // El reloj est� a 16MHz, si cuenta 16,000 tarda 0.001 segundos
    // por tanto se genera una frecuencia base de 1 KHz por PF.1
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 16000);
    // Configurar duty cycle
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 1);
}

/* Inicializaci�n del Timer con el reloj de 16MHz*/
void initTimer(){
    // Se habilita el reloj al timer0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Se configura que sea modo peri�dico en el timer0
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    // Se establece el l�mite de conteo
    TimerLoadSet(TIMER0_BASE, TIMER_A, 8e6);
    // Se habilitan las interrupciones en el timerA
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Asocia el nombre de la funci�n con el manejador de la interrupci�n del timer0,A
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerOut);
    // Habilita la interrupci�n del timer por parte del NVIC
    IntEnable(INT_TIMER0A);
    // Habilita las int de forma general
    IntMasterEnable();
}

/* Inicializaci�n del ADC por el puerto PE.5*/
void initADC(){
    // Habilito el reloj para el ADC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    // Habilito reloj en el puerto E
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    // Configuro PE.5 como entrada anal�gica
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);
    // Pull-Down en PE.5
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    // Configura la fuente asociada a la CPU
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    // Habilitamos la forma del secuenciador (muestrea por secuencia, hab, int, del canal 11, la primera muestra es la �ltima muestra)
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_CH8 | ADC_CTL_END);
}

/* Inicializaci�n del GPIO por el puerto PB.5 como salida (buzzer)*/
void initGPIO(){
    // Se habilita el reloj en el puerto B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    // Se habilita PB.5 como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);
}


/************************************************************
 *                                                          *
 *      Funciones de activar/desactivar los m�dulos         *
 *                                                          *
 ************************************************************/

// Controla el estado del m�dulo PWM
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

// Controla el estado del m�dulo Timer
void TimerSetState(int State){
    TimerLoadSet(TIMER0_BASE, TIMER_A, 16e6);
    if(State == 1){
        TimerEnable(TIMER0_BASE, TIMER_A);                  // Habilita la operaci�n del Timer A
    } else{
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
        TimerDisable(TIMER0_BASE, TIMER_A);                 // Deshabilita la operaci�n del Timer A
    }
}

// Controla el estado del m�dulo ADC
void ADCSetState(int State){
    if(State == 1){
        ADCSequenceEnable(ADC0_BASE, 3);                    // Habilitamos el secuenciador
    } else{
        ADCSequenceDisable(ADC0_BASE, 3);                   // Deshabilitamos el secuenciador
    }
}
