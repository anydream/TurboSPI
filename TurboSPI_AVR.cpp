
#include "TurboSPI.h"

#ifdef __AVR__
//------------------------------------------------------------------------------
void TurboSPI::Begin()
{
#ifdef __AVR_ATmega328P__
	// Save a few bytes for 328 CPU - gcc optimizes single bit '|' to sbi.
	PORTB |= 1 << 2;  // SS high
	DDRB |= 1 << 2;  // SS output mode
	DDRB |= 1 << 3;  // MOSI output mode
	DDRB |= 1 << 5;  // SCK output mode
#else  // __AVR_ATmega328P__

	// set SS high - may be chip select for another SPI device
	digitalWrite(SS, HIGH);

	// SS must be in output mode even it is not chip select
	pinMode(SS, OUTPUT);
	pinMode(MOSI, OUTPUT);
	pinMode(SCK, OUTPUT);
#endif  // __AVR_ATmega328P__
}
//------------------------------------------------------------------------------
void TurboSPI::Init(uint8_t divisor)
{
	uint8_t b = 2;
	uint8_t r = 0;

	// See AVR processor documentation.
	for (; divisor > b && r < 7; b <<= 1, r += r < 5 ? 1 : 2)
	{
	}
	SPCR = (1 << SPE) | (1 << MSTR) | (r >> 1);
	SPSR = r & 1 ? 0 : 1 << SPI2X;
}
//------------------------------------------------------------------------------
uint8_t TurboSPI::Receive()
{
	SPDR = 0XFF;
	while (!(SPSR & (1 << SPIF)))
		;
	return SPDR;
}
//------------------------------------------------------------------------------
uint8_t TurboSPI::Receive(uint8_t * buf, size_t n)
{
	if (n-- == 0)
	{
		return 0;
	}
	SPDR = 0XFF;
	for (size_t i = 0; i < n; i++)
	{
		while (!(SPSR & (1 << SPIF)))
			;
		uint8_t b = SPDR;
		SPDR = 0XFF;
		buf[i] = b;
	}
	while (!(SPSR & (1 << SPIF)))
		;
	buf[n] = SPDR;
	return 0;
}
//------------------------------------------------------------------------------
void TurboSPI::Send(uint8_t data)
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)))
		;
}
//------------------------------------------------------------------------------
void TurboSPI::Send(const uint8_t * buf, size_t n)
{
	if (n == 0)
	{
		return;
	}
	SPDR = buf[0];
	if (n > 1)
	{
		uint8_t b = buf[1];
		size_t i = 2;
		while (1)
		{
			while (!(SPSR & (1 << SPIF)))
				;
			SPDR = b;
			if (i == n)
			{
				break;
			}
			b = buf[i++];
		}
	}
	while (!(SPSR & (1 << SPIF)))
		;
}

//////////////////////////////////////////////////////////////////////////
DigitalPin::DigitalPin()
	: m_Pin(0)
	, m_Port(0)
	, m_Mask(0)
{
}

void DigitalPin::Begin(uint8_t pinID)
{
	m_Pin = pinID;
	m_Port = portOutputRegister(digitalPinToPort(pinID));
	m_Mask = digitalPinToBitMask(pinID);
}

void DigitalPin::PinMode(uint8_t dwMode)
{
	pinMode(m_Pin, dwMode);
}

void DigitalPin::High()
{
	*m_Port |= m_Mask;
}

void DigitalPin::Low()
{
	*m_Port &= ~m_Mask;
}

#endif  // __AVR__
