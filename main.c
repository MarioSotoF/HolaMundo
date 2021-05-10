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

}
