/*
 * Nombre: Mario Soto
 * Carne: 18351
 * Laboratorio 6: Iniciando con tiva ware y code composer
 */



#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
volatile uint32_t i;





int main(void)
{

    SysCtlClockSet ( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ ) ;//Hacemos la cofig del clck
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF ) ;//Activamos el uso de perierios para el puerto F
    // Setup de pines como salidas y de botones como entradas
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    //Configuramos el boton como pullup
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while(1)
        {
            if (!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)){//Semaforo

                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x02); //Se enciende el led rojo
                for (i=0;i<5000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x0A); //Se enciende los leds rojo y verde para crear amarillo
                for (i=0;i<5000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se enciende la led verde
                for (i=0;i<5000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se inicia la secuencia de parpadeo para el verde
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se enciende la led verde
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se enciende la led verde
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se enciende la led verde
                for (i=0;i<1000000;i++){}
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todas las leds
                for (i=0;i<1000000;i++){}

                }

        }

}


