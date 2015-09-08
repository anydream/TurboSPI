# Overview
This is another Arduino SPI library separated from SdFat library, it uses SPI registers and DMA (Arduino Due only) to accelerate SPI communication.

Thanks to Bill Greiman

# Configuration
##### Put this folder into your arduino "libraries" folder.

I have test this library on Arduino Uno/Mega2560/Due, maybe support other AVR/SAM3X MCUs.
You can search keywords like "Arduino Mega2560 pinout" to find pinout mapping with your board.

##### Connect your slave module to arduino:
	SCK to SCK,
	MISO to MISO,
	MOSI to MOSI,
	Reset to Reset,
	CS to any digital pin.

 * Arduino Uno SPI pinout:

	![alt tag](https://github.com/anydream/TurboSPI/raw/master/SPIpinout/uno.jpg)

 * Arduino Mega2560 SPI pinout:

	![alt tag](https://github.com/anydream/TurboSPI/raw/master/SPIpinout/mega2560.jpg)

 * Arduino Due SPI pinout:

	![alt tag](https://github.com/anydream/TurboSPI/raw/master/SPIpinout/due.jpg)

# Example code:
```cpp
#include <TurboSPI.h>

TurboSPI	g_SPI;
DigitalPin	g_PinCS, g_PinRS;
uint8_t		g_Buffer[256];	// some data buffer to transfer
uint8_t		g_Divisor = 2;	// transfer speed set to MCU's clock divide by 2

void setup()
{
	// setup pins
	g_PinCS.Begin(45);
	g_PinRS.Begin(47);

	g_PinCS.PinMode(OUTPUT);
	g_PinRS.PinMode(OUTPUT);

	// setup SPI
	g_SPI.Begin();
}

void loop()
{
	// setup speed and select slave
	g_SPI.Init(g_Divisor);
	g_PinCS.Low();
	
	// set some pins
	g_PinRS.High();

	// transfer data to slave
	g_SPI.Send(g_Buffer, sizeof(g_Buffer));
	
	// unselect slave
	g_PinCS.High();
}
```