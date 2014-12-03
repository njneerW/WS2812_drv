This library can be used to get a Stellaris or Tiva C Series MCU to control a
chain of WS2812b LEDs using the SPI peripheral.  Functions for interacting
directly with the LEDs can be found in lib/WS2812_drv.  A library for using
the uDMA peripheral to communicate with the LEDs can be found in
lib/SPI_uDMA_drv.  Sample source code for how to use this library, including
a startup_css.c defining all necessary interrupt vectors, can be found in the
example directory.

Currently, this library only supports a single SPI peripheral controlling the
chain of LEDs on PF1 using SPI1.  In the future, this will be renamed
WS2812_simple_drv, and a new WS2812_drv will be added that will contain a
much more generic (but unfortunately, also complex) API that will allow for
using multiple SPI peripherals in parallel, and let the user specify the SPI
peripheral, uDMA channel, SPI TX pin, and other options to be used for each
instance of the driver.
