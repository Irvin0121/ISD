/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Definiciones para el TIVA TM4123G6PM
 *  creado por IRVIN
 */



#define SYSCTL                  (*((volatile unsigned long *)0x400FE608))


// **************** General-Purpose Input/Outputs (GPIOs) ****************


#define PORTA_EN                (*((volatile unsigned long *)0x4000451C))
#define PORTB_EN                (*((volatile unsigned long *)0x4000551C))
#define PORTC_EN                (*((volatile unsigned long *)0x4000651C))
#define PORTD_EN                (*((volatile unsigned long *)0x4000751C))
#define PORTE_EN                (*((volatile unsigned long *)0x4002451C))
#define PORTF_EN                (*((volatile unsigned long *)0x4002551C))


#define PAOUT                  (*((volatile unsigned long *)0x400043FC))
#define PBOUT                  (*((volatile unsigned long *)0x400053FC))
#define PCOUT                  (*((volatile unsigned long *)0x400063FC))
#define PDOUT                  (*((volatile unsigned long *)0x400073FC))
#define PEOUT                  (*((volatile unsigned long *)0x400243FC))
#define PFOUT                  (*((volatile unsigned long *)0x400253FC))

#define PADIR                  (*((volatile unsigned long *)0x40004400))
#define PBDIR                  (*((volatile unsigned long *)0x40005400))
#define PCDIR                  (*((volatile unsigned long *)0x40006400))
#define PDDIR                  (*((volatile unsigned long *)0x40007400))
#define PEDIR                  (*((volatile unsigned long *)0x40024400))
#define PFDIR                  (*((volatile unsigned long *)0x40025400))


// BITS
#define BIT0                    (0x01)
#define BIT1                    (0x02)
#define BIT2                    (0x04)
#define BIT3                    (0x08)
#define BIT4                    (0x10)
#define BIT5                    (0x20)
#define BIT6                    (0x40)
#define BIT7                    (0x80)
