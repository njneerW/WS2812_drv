//*****************************************************************************
//
// Comments here, eventually
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "WS2812_drv.h"
#include "SPI_uDMA_drv.h"
#include "samplePatterns.h"

//*****************************************************************************
//
// Configure the UART and its pins to A0 and A1, which are routed to the UART
// over USB chip.  This must be called before UARTprintf().
//
//*****************************************************************************
void
configureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}


//*****************************************************************************
//
// This example application demonstrates the use of the WS2812B uDMA library
// to scroll through the color wheel on a strip of 30 WS2812b LEDs that have
// the data in line connected to PF1.
//
//*****************************************************************************
int
main(void)
{
	//
	// An array to hold the colors.  30 LEDs for this example, each has a red,
	// green, and blue intensity.  Note that these are actually stored GRB,
	// because WS2812b LEDs are weird.
	//
	static uint8_t pui8Colors[30][3];

	//
	// The output array for the SPI bus.  The nature of the timing for the LEDs
	// makes it so we can't just map a single intensity byte onto a single byte
	// to transmit out the SPI peripheral.  Instead, we separate each bit of
	// the intensity to four bits of SPI out.  The WS one wire protocol
	// basically boils down to "110" on the SPI bus is read as a 1 by the LED,
	// "100" is a 0.  We use some macros to figure out how many bytes of SPI array
	// we need to represent each of the 30 LEDs.
	//
	static uint8_t pui8SPIOut[30][WS2812_SPI_BYTE_PER_CLR * WS2812_SPI_BIT_WIDTH];

	//
	// We'll pass this flag to the uDMA library, which will tell us when each
	// transfer is done.  This is only necessary if you want the update rate of
	// the LED strip to be based on how fast the data can be read by the WSB LED.
	//
	uint8_t ui8SPIDone;
	int i;

	//
	// Set the clocking to run from the PLL at 50MHz
	//
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
					   SYSCTL_XTAL_16MHZ);

	//
	// This is in every example ever.  It involves how floating point values
	// get passed around... ignore it.
	//
	ROM_FPULazyStackingEnable();

	//
	// Initialize the UART and say hello.
	//
	configureUART();
	UARTprintf("\033[2JLet's do some DMA!\n");

	//
	// Initialize the color array to be evenly spaced along the color wheel.
	//
	rainbowInit(pui8Colors, 30);

    //
    // Initialize and start the inifinite uDMA transfers
    //
    InitSPITransfer((uint8_t*)pui8SPIOut, sizeof(pui8SPIOut), &ui8SPIDone);

    while(1)
    {
    	if(ui8SPIDone)
    	{
    		ui8SPIDone = 0;
    		for(i=0;i<30;i++)
			{
					rainbowShift(&(pui8Colors[i][0]), &(pui8Colors[i][1]), &(pui8Colors[i][2]));
					WSGRBtoSPI(pui8SPIOut[i], pui8Colors[i][0], pui8Colors[i][1],
							   pui8Colors[i][2]);
			}
    	}
    }
}
