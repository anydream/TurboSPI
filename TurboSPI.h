
#ifndef __TurboSPI_h__
#define __TurboSPI_h__

#include <Arduino.h>

class TurboSPI
{
public:
	/** Initialize the SPI bus */
	void Begin();
	/** Set SPI options.
	 *
	 * \param[in] divisor SCK clock divider relative to the system clock.
	 */
	void Init(uint8_t divisor);
	/** Receive a byte.
	 *
	 * \return The byte.
	 */
	uint8_t Receive();
	/** Receive multiple bytes.
	 *
	 * \param[out] buf Buffer to receive the data.
	 * \param[in] n Number of bytes to receive.
	 *
	 * \return Zero for no error or nonzero error code.
	 */
	uint8_t Receive(uint8_t* buf, size_t n);
	/** Send a byte.
	 *
	 * \param[in] data Byte to send
	 */
	void Send(uint8_t data);
	/** Send multiple bytes.
	 *
	 * \param[in] buf Buffer for data to be sent.
	 * \param[in] n Number of bytes to send.
	 */
	void Send(const uint8_t* buf, size_t n);
};

class DigitalPin
{
public:
	DigitalPin();

	void Begin(uint8_t pinID);
	void PinMode(uint8_t dwMode);

	void High();
	void Low();

private:
	uint8_t				m_Pin;
#if defined(__SAM3X8E__) || defined(__SAM3X8H__)
	Pio					*m_Port;
	uint32_t			m_Mask;
#elif defined(__AVR__)
	volatile uint8_t	*m_Port;
	uint8_t				m_Mask;
#endif
};

#endif  // __TurboSPI_h__
