

#ifndef __SPI_UDMA_DRV_H__
#define __SPI_UDMA_DRV_H__

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

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************

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
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SPI_UDMA_DRV_H__
