/*
 * Nombre: Mario Soto
 * Carnet: 18351
 * Laboratorio 7
 * Catedratico: Pablo Mazariegos
 * Seccion 20
 */

//Agregamos las librerias necesarias

//Bibliotecas
#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"inc/tm4c123gh6pm.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/timer.h"
#include"driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"

#define XTAL 16000000

uint32_t ui32Period;//Se incluye la variable para el temporizador
uint32_t i = 0;
uint32_t j = 0;


//lectura de los pines de los push
int lectura;
int lectura1;
int lectura2;
int lectura3;
int libres;


//void InitUART(void);


void delay(uint32_t msec);
void delay1ms(void);


/**
 * main.c
 */
int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5| SYSCTL_USE_PLL| SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF) ;//Activamos el uso de periferios para el puerto F
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOE) ;//Activamos el uso de periferios para el puerto E
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOD) ;//Activamos el uso de periferios para el puerto D
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB) ;//Activamos el uso de periferios para el puerto B
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOC) ;//Activamos el uso de periferios para el puerto C
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA) ;//Activamos el uso de periferios para el puerto C

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2);//Configuramos los dos leds del parqueo 1 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_4);//Configuramos los dos leds del parqueo 2 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7);//Configuramos los dos leds del parqueo 3 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);//Configuramos los dos leds del parqueo 3 como salidas


    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);//Configuramos el pin a del 7 segmentos como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_6);//Configuramos el pin b y c del 7 segmentos como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_4);//Configuramos el pin d y e del 7 segmentos como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3|GPIO_PIN_2);//Configuramos el pin f ygc del 7 segmentos como salidas


    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_5);//Configuramos los push buttoms como entradas
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);//Configuramos los push buttoms como entradas
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_2);//Configuramos los push buttoms como entradas
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_3);//Configuramos los push buttoms como entradas


    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//Configuramos los push buttoms como pull up
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//Configuramos los push buttoms como pull up
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//Configuramos los push buttoms como pull up
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//Configuramos los push buttoms como pull up

    //Se configura la comunicacion UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);//Se habilita el UART1
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 |GPIO_PIN_1); //definicion de los pines del UART1
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
    //Configuracion de UART0 a 115200 con 8 bits de datos y 1 de stop sin pariedad
    UARTConfigSetExpClk(UART1_BASE, 16000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));


    UARTEnable(UART1_BASE);





    while (1)
    {

        lectura=GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);//Lectura para el parqueo 1
        lectura1=GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1);//Lectura para el parqueo 2
        lectura2=GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2);//Lectura para el parqueo 3
        lectura3=GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3);//Lectura para el parqueo 4
        libres = 4;

        if (lectura==0)
        {
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);//Led verde apagada
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);//Led roja encendida indicando que el parqueo esta ocupado
            libres --;
        }
        if (!lectura==0)
        {
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);//Led verde encendida indicando que le parqueo esta libre
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);//Led roja apagada
        }
        if(lectura1 == 0)
        {
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0);//Led verde apagada
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4);//Led roja encendida indicando que el parqueo esta ocupado
            libres --;

        }
        if(!lectura1 == 0)
        {
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);//Led verde encendida indicando que le parqueo esta libre
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);//Led roja apagada
        }
        if(lectura2 == 0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0);//Led verde apagada
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7);//Led roja encendida indicando que el parqueo esta ocupado
            libres --;

        }
        if(!lectura2 == 0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_PIN_6);//Led verde encendida indicando que le parqueo esta libre
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);//Led roja apagada
        }
        if(lectura3 == 0)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);//Led verde apagada
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);//Led roja encendida indicando que el parqueo esta ocupado
            libres --;

        }
        if(!lectura3 == 0)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);//Led verde encendida indicando que le parqueo esta libre
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);//Led roja apagada
        }
        if(libres == 4)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);//Apagamos a
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);//Encendemos b
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);//Encendemos c
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);//Apagamos d
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);//Apagamos e
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);//Encendemos f
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);//Encendemos g


        }
        if(libres == 3)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);//Encendemos a
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);//Encendemos b
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);//Encendemos c
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);//Encendemos d
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);//Apagamos e
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);//Apagamos f
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);//Encendemos g
        }
        if(libres == 2)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);//Encendemos a
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);//Encendemos b
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);//Apagamos c
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);//Encendemos d
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);//Encendemos e
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);//Apagamos f
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);//Encendemos g
        }
        if(libres == 1)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);//Apagamos a
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);//Encendemos b
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);//Encendemos c
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);//Apagamos d
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);//Apagamos e
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);//Apagamos f
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);//Apagamos g
        }
        if(libres == 0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);//Encendemos a
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);//Encendemos b
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);//Encendemos c
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);//Encendemos d
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);//Encendemos e
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);//Encendemos f
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);//Apagamos g
        }
        else
        {

        }
        //Se envian datos por el UART
        UARTCharPut(UART1_BASE, lectura);
        UARTCharPut(UART1_BASE, lectura1);
        UARTCharPut(UART1_BASE, lectura2);
        UARTCharPut(UART1_BASE, lectura3);

        delay(100);

    }



}

void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        delay1ms();
    }

}

void delay1ms(void)
{
    SysTickDisable();
    SysTickPeriodSet(16000);
    SysTickEnable();

    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);
}




