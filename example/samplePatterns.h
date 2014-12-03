
typedef enum {  INHALE, HOLD_IN, EXHALE, HOLD_OUT } breathState_t;
typedef enum { GREEN, RED, BLUE, WHITE } color_t;

//*****************************************************************************
//
// Shift through the full RGB color wheel
//
// This function takes in green, red, and blue 1 byte color values and
// increments them by one bit to the next color in the color wheel.  It will
// only change one color at a time, and follows this pattern:
//    ONE:
//		R:255
//		G:0-255
//		B:0
//	  TWO:
//		R:255-0
//		G:255
//		B:0
//	  THREE:
//		R:0
//		G:255
//		B:0-255
//	  FOUR:
//		R:0
//		G:255-0
//		B:255
//	  FIVE:
//		R:0-255
//		G:0
//		B:255
//	  SIX:
//		R:255
//		G:0
//		B:255-0
//
// @input *ui8Green is the intensity of the green LED
// @input *ui8Red is the intensity of the red LED
// @input *ui8Blue is the intensity of the blue LED
// @returns none, but input variables are changed to appropriate values
//
//*****************************************************************************
extern void
rainbowShift(uint8_t *ui8Green, uint8_t *ui8Red, uint8_t *ui8Blue);

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
// @input ints[][3] is the array of RGB values
// @input ui8NumLED is the number of LEDs represented by ints
//
// @returns none, but values stored in ints are changed.
//
//*****************************************************************************
extern void
rainbowInit(uint8_t ints[][3], uint8_t ui8NumLED);

