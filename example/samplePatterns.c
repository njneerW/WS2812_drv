#include <stdint.h>

#include "WS2812_drv.h"
#include "SPI_uDMA_drv.h"
#include "samplePatterns.h"

//*****************************************************************************
//
// Shift through the full RGB color wheel
//
// This function takes in green, red, and blue 1 byte color values and
// increments them by one bit to the next color in the color wheel.  It will
// only change one color at a time, and follows this pattern:
//    ONE:
//      R:255
//      G:0-255
//      B:0
//    TWO:
//      R:255-0
//      G:255
//      B:0
//    THREE:
//      R:0
//      G:255
//      B:0-255
//    FOUR:
//      R:0
//      G:255-0
//      B:255
//    FIVE:
//      R:0-255
//      G:0
//      B:255
//    SIX:
//      R:255
//      G:0
//      B:255-0
//
// @input *ui8Green is the intensity of the green LED
// @input *ui8Red is the intensity of the red LED
// @input *ui8Blue is the intensity of the blue LED
// @returns none, but input variables are changed to appropriate values
//
//*****************************************************************************
void rainbowShift(uint8_t *ui8Green, uint8_t *ui8Red, uint8_t *ui8Blue)
{
    if((*ui8Red == 0xff) && (*ui8Green != 0xff))
    {
        if(*ui8Blue > 0)
        {
            *ui8Blue = *ui8Blue - 1;
        }
        else
        {
            *ui8Green = *ui8Green + 1;
        }
    }
    else if((*ui8Green == 0xff) && (*ui8Blue != 0xff))
    {
        if(*ui8Red > 0)
        {
            *ui8Red = *ui8Red - 1;
        }
        else
        {
            *ui8Blue = *ui8Blue + 1;
        }
    }
    else
    {
        if(*ui8Green > 0)
        {
            *ui8Green = *ui8Green - 1;
        }
        else
        {
            *ui8Red = *ui8Red + 1;
        }
        return;
    }
}

#define NUMSECT     6
//*****************************************************************************
//
// Initialize an array of LEDs to a color wheel.
//
// This function will take in an array of RGB values representing RGB LEDs and
// initialize them such that they are evenly spaced throughout the color wheel.
// It assumes that there are six sections of the color wheel (as defined in the
// documentation for the @rainbowShift function), and sets up the LEDs such that
// they are all evenly spaced throughout those ranges.
//
// This function might misbehave if you give it less than 6 LEDs...
//
// @input ints[][3] is the array of RGB values
// @input ui8NumLED is the number of LEDs represented by ints
//
// @returns none, but values stored in ints are changed.
//
//*****************************************************************************
void rainbowInit(uint8_t ints[][3], uint8_t ui8NumLED)
{
    //
    // For the love of toast, why didn't I comment this while I was writing it?
    // ...oh right, it was probably 2 in the morning.  If anyone's trying to
    // fix a bug here, good luck :(
    //

    int i;
    int j;
    int ledPerSect;

    for(i=0;i<ui8NumLED;i+=ledPerSect)
    {
        //
        // Cycle through each of the six LED sections
        //
        if(i < (ui8NumLED/NUMSECT) * 1)
        {
            ledPerSect = ui8NumLED/NUMSECT;
            if((ui8NumLED%NUMSECT == 3) || (ui8NumLED%NUMSECT == 4) ||
               (ui8NumLED%NUMSECT == 5))
            {
                ledPerSect++;
            }
            for(j=0;j<ledPerSect;j++)
            {
                ints[i+j][0] = (0xFF/ledPerSect)*j;
                ints[i+j][1] = 0xff;
                ints[i+j][2] = 0x00;
            }
        }
        else if(i < (ui8NumLED/NUMSECT) * 2)
        {
            ledPerSect = ui8NumLED/NUMSECT;
            if((ui8NumLED%NUMSECT == 2) || (ui8NumLED%NUMSECT == 5))
            {
                ledPerSect++;
            }
            for(j=0;j<ledPerSect;j++)
            {
                ints[i+j][0] = 0xFF;
                ints[i+j][1] = 0xFF - (0xFF/ledPerSect*j);
                ints[i+j][2] = 0x00;
            }
        }
        else if(i < (ui8NumLED/NUMSECT) * 3)
        {
            ledPerSect = ui8NumLED/NUMSECT;
            if((ui8NumLED%NUMSECT == 3) || (ui8NumLED%NUMSECT == 4) ||
               (ui8NumLED%NUMSECT == 5))
            {
                ledPerSect++;
            }
            for(j=0;j<ledPerSect;j++)
            {
                ints[i+j][0] = 0xFF;
                ints[i+j][1] = 0x00;
                ints[i+j][2] = (0xFF/ledPerSect)*j;
            }
        }
        else if(i < (ui8NumLED/NUMSECT) * 4)
        {
            ledPerSect = ui8NumLED/NUMSECT;
            if((ui8NumLED%NUMSECT == 5) || (ui8NumLED%NUMSECT == 4))
            {
                ledPerSect++;
            }
            for(j=0;j<ledPerSect;j++)
            {
                ints[i+j][0] = 0xFF - (0xFF/ledPerSect*j);
                ints[i+j][1] = 0x00;
                ints[i+j][2] = 0xFF;
            }
        }
        else if(i < (ui8NumLED/NUMSECT) * 5)
        {
            ledPerSect = ui8NumLED/NUMSECT;
            if((ui8NumLED%NUMSECT == 2) || (ui8NumLED%NUMSECT == 3) ||
               (ui8NumLED%NUMSECT == 5))
            {
                ledPerSect++;
            }
            for(j=0;j<ledPerSect;j++)
            {
                ints[i+j][0] = 0x00;
                ints[i+j][1] = (0xFF/ledPerSect)*j;
                ints[i+j][2] = 0xFF;
            }
        }
        else if(i < (ui8NumLED/NUMSECT) * 6)
        {
            ledPerSect = ui8NumLED/NUMSECT;
            if((ui8NumLED%NUMSECT == 1) || (ui8NumLED%NUMSECT == 4))
            {
                ledPerSect++;
            }
            for(j=0;j<ledPerSect;j++)
            {
                ints[i+j][0] = 0x00;
                ints[i+j][1] = 0xFF;
                ints[i+j][2] = 0xFF - (0xFF/ledPerSect*j);
            }
        }
    }
}
