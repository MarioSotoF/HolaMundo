/*
 * Nombre: Mario Soto
 * Carnet: 18351
 * Proyecto 4 parte de code composer
 * Catedratico: Pablo Mazariegos
 * Seccion 20
 */

//Agregamos las librerias necesarias

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#define XTAL 16000000

uint32_t ui32Period;//Se incluye la variable para el temporizador

uint8_t parqueo1 = 0;
uint8_t parqueo2 = 0;
uint8_t parqueo3 = 0;
uint8_t parqueo4 = 0;

int32_t color;

//void InitUART(void);
//void Timer0IntHandler(void);
void InitUART(void);



/**
 * main.c
 */
int main(void)
{
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ ) ;//Hacemos la cofig del clck
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF|SYSCTL_PERIPH_GPIOD ) ;//Activamos el uso de periferios para el puerto F y D

    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);//Configuramos los push buttoms como entradas

    GPIOPinConfigure(GPIO_PD0_WT2CCP0);
    GPIOPinConfigure(GPIO_PD1_WT2CCP1);
    GPIOPinConfigure(GPIO_PD2_WT3CCP0);
    GPIOPinConfigure(GPIO_PD3_WT3CCP1);

    //Configuramos los push como pull up
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2);//Configuramos los dos leds del parqueo 1 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_4);//Configuramos los dos leds del parqueo 2 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7);//Configuramos los dos leds del parqueo 3 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6|GPIO_PIN_7);//Configuramos los dos leds del parqueo 4 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);//Configuramos los dos leds del parqueo 4 como salidas

//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//Se habilita el reloj para el temporizador
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);//Se configura al timer 0 como termporizador periodico
//    ui32Period = (SysCtlClockGet()) / 2;//Se calcula el periodo del temporizador
//    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);//Se establece el periodo del temporizador


//    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//Se habilita el time out
//    TimerIntRegister(TIMER0_BASE,TIMER_A,Timer0IntHandler);

    InitUART();

//    IntEnable(INT_TIMER0A);//Se habilita la interrupción en el timer 0
//    IntMasterEnable();//Se habilitan interrupciones globales
//    TimerEnable(TIMER0_BASE, TIMER_A);//Se habilita el timer


//    UARTCharPut(UART0_BASE, 'R');
//    UARTCharPut(UART0_BASE, 'B');
//    UARTCharPut(UART0_BASE, 'G');

    while (1)
    {
//        color = UARTCharGet(UART0_BASE);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
        if (!GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0))
        {
            SysCtlDelay(500000);
            while (!GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0))
            {

            }

            if (parqueo1 == 0)
            {
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0xFF);//Led verde indicando que le parqueo esta libre
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0x00);//Led roja apagada
                SysCtlDelay(500000);
                parqueo1 = 1;
            }
            else if(parqueo1 == 1)
            {
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x00);//Led verde apagada
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0xFF);//Led roja indicando que le parqueo esta ocuapo
                SysCtlDelay(500000);
                parqueo1 = 0;
            }
        }


    }



}


//void Timer0IntHandler(void){
//    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//Se limpia la interrupcion del timer
//
//    switch (color)
//    {
//    case 'r':
//        if (bandera == 0)
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x02); //Se enciende el led rojo
//            bandera = 1;
//        }
//        else
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
//            bandera = 0;
//        }
//        break;
//    case 'b':
//        if (bandera == 0)
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x04);
//            bandera = 1;
//        }
//        else
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
//            bandera = 0;
//        }
//        break;
//    case 'g':
//        if (bandera == 0)
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
//            bandera = 1;
//        }
//       else
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
//            bandera = 0;
//        }
//        break;
//    }
//}

void InitUART(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//Habilitamos el puerto A del GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);//Se activa el periferio del Uart
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);//Hacemos que los pines de la comunicación Uart se puedean controlar de manera periferica
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);


}



