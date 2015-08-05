# TurboSPI
This is another Arduino SPI library separated from SdFat library, it uses SPI registers and DMA (Arduino Due only) to accelerate SPI communication.

Thanks to Bill Greiman

# Install
I have test this library on Arduino Uno/Mega2560/Due, maybe support other AVR/SAM3X MCUs.
You can search keywords like "Arduino Mega2560 pinout" to find pinout mapping with your board like this:

Arduino Uno SPI pinout:
![alt tag](https://github.com/anydream/TurboSPI/raw/master/SPIpinout/uno.jpg)

Arduino Mega2560 SPI pinout:
![alt tag](https://github.com/anydream/TurboSPI/raw/master/SPIpinout/mega2560.jpg)

Arduino Due SPI pinout:
![alt tag](https://github.com/anydream/TurboSPI/raw/master/SPIpinout/due.jpg)