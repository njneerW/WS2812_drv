

#ifndef __WS2812_DRV_H__
#define __WS2812_DRV_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#define WS2812_GREEN_OFFS       0
#define WS2812_RED_OFFS         1
#define WS2812_BLUE_OFFS        2

//#define WS2812_SPI_BIT_WIDTH    8
//#define WS2812_SPI_HIGH         0xF8
//#define WS2812_SPI_LOW          0xE0
#define WS2812_SPI_BIT_WIDTH    8
#define WS2812_SPI_HIGH         0xE
#define WS2812_SPI_LOW          0x8
#define WS2812_SPI_BYTE_PER_CLR 3
#define WS2812_SPI_BYTE_PER_LED WS2812_SPI_BYTE_PER_CLR * 3

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************

#if 0
//*****************************************************************************
//
// Kick off the SPI uDMA transfers.
//
// This function will configure the uDMA engine and SSI1 peripheral to
// continually data to a chain of WS2812b LEDs connected to PF1.
//
// @input pui8SPIData is the array containing the SPI data to send
// @input ui16DataSize is the number of bytes the data array can hold
// @input pui8DoneVar is a flag that can be used to determine when an LED frame
//        has finished transmitting.  This flag will be initialized to 0 on the
//        first uDMA start, and will be set to 1 each time the uDMA engine
//        finishes sending the entire SPI buffer.
//
//*****************************************************************************
extern void InitSPITransfer(uint8_t *pui8SPIData, uint16_t ui16DataSize,
		                    uint8_t *pui8DoneVar);

//*****************************************************************************
//
// Initialize an SPI out array to all LEDs off
//
// This function will fill the SPI array with values that will be interpreted
// by the LEDs as logical zeros.  Note that this isn't filling the array with
// zeroes, but rather filling the array with the values needed to set all RGB
// values of all LEDs to be off.
//
// @input pui8SPIData is the array containing the SPI data to send
// @input ui16Len is the number of bytes the data array can hold
//
//*****************************************************************************
extern void WSArrayInit(uint8_t *pi8SPIData, uint16_t ui16Len);
#endif

//*****************************************************************************
//
// Write a color byte to a set of SPI out bytes
//
// This function take a 1 byte color value and a location in the SPI data array
// and write the appropriate values in the data array to represent that color
// on the SPI line.  This function assumes the SPIData array has enough memory
// allocated such that the translated color value will not overflow the data
// array.
//
// @input pui8SPIData is the location in the SPI array of where the color value
//        is to begin being written
// @input ui8Color is the color to be translated from 1 byte RGB to the SPI
//        bitstream value
//
//*****************************************************************************
extern void WStoSPI(uint8_t *pi8SPIData, uint8_t ui8Color);

//*****************************************************************************
//
// Write a set of RGB color bytes to a set of SPI out bytes
//
// This function take three 1 byte color values and a location in the SPI data
// array and write the appropriate values in the data array to represent those
// colors on the SPI line.  This function assumes the SPIData array has enough
// memory allocated such that the translated color value will not overflow the
// data array.
//
// @input pui8SPIData is the location in the SPI array of where the color value
//        is to begin being written
// @input ui8Green is the green color to be translated from 1 byte GRB to the
//		  SPI bitstream value
// @input ui8Red is the red color to be translated from 1 byte GRB to the
//		  SPI bitstream value
// @input ui8Blue is the blue color to be translated from 1 byte GRB to the
//		  SPI bitstream value
//
//*****************************************************************************
extern void WSGRBtoSPI(uint8_t *pi8SPIData, uint8_t ui8Green, uint8_t ui8Red,
            uint8_t ui8Blue);

//*****************************************************************************
//
// Write a green color byte to a set of SPI out bytes
//
// This function take a 1 byte green color value and a location in the SPI data
// array and write the appropriate values in the data array to represent that
// color on the SPI line.  This function is used when the offset of the WSG LED
// in the SPI buffer is known, but the number of bits from the LED start
// location to where the "green" bits begins is unknown. This function assumes
// the SPIData array has enough memory allocated such that the translated color
// value will not overflow the data array.
//
// @input pui8SPIData is the location in the SPI array where the LED whose
//        green value is to be written is located.
// @input ui8Color is the color to be translated from 1 byte to the SPI
//        bitstream value
//
//*****************************************************************************
inline void
WSGtoSPI(uint8_t *pi8SPIData, uint8_t ui8Color)
{
    WStoSPI(pi8SPIData+(WS2812_SPI_BIT_WIDTH * WS2812_GREEN_OFFS), ui8Color);
}

//*****************************************************************************
//
// Write a red color byte to a set of SPI out bytes
//
// This function take a 1 byte red color value and a location in the SPI data
// array and write the appropriate values in the data array to represent that
// color on the SPI line.  This function is used when the offset of the WSG LED
// in the SPI buffer is known, but the number of bits from the LED start
// location to where the "red" bits begins is unknown. This function assumes
// the SPIData array has enough memory allocated such that the translated color
// value will not overflow the data array.
//
// @input pui8SPIData is the location in the SPI array where the LED whose
//        red value is to be written is located.
// @input ui8Color is the color to be translated from 1 byte to the SPI
//        bitstream value
//
//*****************************************************************************
inline void
WSRtoSPI(uint8_t *pi8SPIData, uint8_t ui8Color)
{
    WStoSPI(pi8SPIData+(WS2812_SPI_BIT_WIDTH * WS2812_RED_OFFS), ui8Color);
}

//*****************************************************************************
//
// Write a blue color byte to a set of SPI out bytes
//
// This function take a 1 byte blue color value and a location in the SPI data
// array and write the appropriate values in the data array to represent that
// color on the SPI line.  This function is used when the offset of the WSG LED
// in the SPI buffer is known, but the number of bits from the LED start
// location to where the "blue" bits begins is unknown. This function assumes
// the SPIData array has enough memory allocated such that the translated color
// value will not overflow the data array.
//
// @input pui8SPIData is the location in the SPI array where the LED whose
//        blue value is to be written is located.
// @input ui8Color is the color to be translated from 1 byte to the SPI
//        bitstream value
//
//*****************************************************************************
inline void
WSBtoSPI(uint8_t *pi8SPIData, uint8_t ui8Color)
{
    WStoSPI(pi8SPIData+(WS2812_SPI_BIT_WIDTH * WS2812_BLUE_OFFS), ui8Color);
}

//*****************************************************************************
//
// Set the green value for an LED in the WS2812b chain
//
// This function take a 1 byte green color value, an LED position in the
// WS2812b chain, and an SPI data array.  It determines what location in the
// SPI data array the specified LED is located, then translates the 1 byte
// color value to the bits needed on the SPI array to represent that color, and
// writes those bits to the proper location in the SPI data array.
//
// @input pui8SPILEDs is the entire SPI output data array
// @input ui16LED is the index of the LED whose color is to be modified
// @input ui8Color is the green value to be displayed on that LED
//
//*****************************************************************************
inline void
WSSetLEDGreen(uint8_t *pi8SPILEDs, uint16_t ui16LED, uint8_t ui8Color)
{
    WStoSPI(pi8SPILEDs + (3*WS2812_SPI_BIT_WIDTH*ui16LED) +
            (WS2812_SPI_BIT_WIDTH * WS2812_GREEN_OFFS), ui8Color);
}

//*****************************************************************************
//
// Set the red value for an LED in the WS2812b chain
//
// This function take a 1 byte red color value, an LED position in the
// WS2812b chain, and an SPI data array.  It determines what location in the
// SPI data array the specified LED is located, then translates the 1 byte
// color value to the bits needed on the SPI array to represent that color, and
// writes those bits to the proper location in the SPI data array.
//
// @input pui8SPILEDs is the entire SPI output data array
// @input ui16LED is the index of the LED whose color is to be modified
// @input ui8Color is the red value to be displayed on that LED
//
//*****************************************************************************
inline void
WSSetLEDRed(uint8_t *pi8SPILEDs, uint16_t ui16LED, uint8_t ui8Color)
{
    WStoSPI(pi8SPILEDs + (3*WS2812_SPI_BIT_WIDTH*ui16LED) +
            (WS2812_SPI_BIT_WIDTH * WS2812_RED_OFFS), ui8Color);
}

//*****************************************************************************
//
// Set the blue value for an LED in the WS2812b chain
//
// This function take a 1 byte blue color value, an LED position in the
// WS2812b chain, and an SPI data array.  It determines what location in the
// SPI data array the specified LED is located, then translates the 1 byte
// color value to the bits needed on the SPI array to represent that color, and
// writes those bits to the proper location in the SPI data array.
//
// @input pui8SPILEDs is the entire SPI output data array
// @input ui16LED is the index of the LED whose color is to be modified
// @input ui8Color is the blue value to be displayed on that LED
//
//*****************************************************************************
inline void
WSSetLEDBlue(uint8_t *pi8SPILEDs, uint16_t ui16LED, uint8_t ui8Color)
{
    WStoSPI(pi8SPILEDs + (3*WS2812_SPI_BIT_WIDTH*ui16LED) +
            (WS2812_SPI_BIT_WIDTH * WS2812_BLUE_OFFS), ui8Color);
}

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WS2812_DRV_H__
