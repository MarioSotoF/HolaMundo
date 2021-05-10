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



}
