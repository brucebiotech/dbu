/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

typedef struct {
	uint8_t const *bytes;
	uint32_t size;
} byte_slice_t;

#define def_byte_slice(P,S) (byte_slice_t) {.bytes = P,.size = S}

typedef struct {
	uint8_t *bytes;
	uint32_t size;
} byte_buffer_t;

#define def_byte_buffer(P,S) (byte_buffer_t) {.bytes = P,.size = S}


#define HAL_GPIO_PORTA       0
#define HAL_GPIO_PORTB       1
#define HAL_GPIO_PORTC       2

#define HAL_GPIO_PMUX_A      0
#define HAL_GPIO_PMUX_B      1
#define HAL_GPIO_PMUX_C      2
#define HAL_GPIO_PMUX_D      3
#define HAL_GPIO_PMUX_E      4
#define HAL_GPIO_PMUX_F      5
#define HAL_GPIO_PMUX_G      6
#define HAL_GPIO_PMUX_H      7
#define HAL_GPIO_PMUX_I      8

#define PORT_PMUX_PMUXE_C PORT_PMUX_PMUXE(HAL_GPIO_PMUX_C)
#define PORT_PMUX_PMUXE_D PORT_PMUX_PMUXE(HAL_GPIO_PMUX_D)
#define PORT_PMUX_PMUXE_G PORT_PMUX_PMUXE(HAL_GPIO_PMUX_G)

#define HAL_GPIO_PIN_ACTIVE		1
#define HAL_GPIO_PIN_INACTIVE		0


#define HAL_GPIO_INLINE_FUNCTIONS(name,port,pin) \
  static inline void HAL_GPIO_##name##_set(void)				\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].OUTSET.reg = (1 << pin);			\
    (void)HAL_GPIO_##name##_set;						\
  }										\
										\
  static inline void HAL_GPIO_##name##_clr(void)				\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].OUTCLR.reg = (1 << pin);			\
    (void)HAL_GPIO_##name##_clr;						\
  }										\
										\
  static inline void HAL_GPIO_##name##_toggle(void)				\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].OUTTGL.reg = (1 << pin);			\
    (void)HAL_GPIO_##name##_toggle;						\
  }										\
										\
  static inline void HAL_GPIO_##name##_write(int active)				\
  {										\
    if (active)									\
      PORT->Group[HAL_GPIO_PORT##port].OUTSET.reg = (1 << pin);			\
    else									\
      PORT->Group[HAL_GPIO_PORT##port].OUTCLR.reg = (1 << pin);			\
    (void)HAL_GPIO_##name##_write;						\
  }										\
										\
  static inline void HAL_GPIO_##name##_write_state(int active)				\
  {										\
    if (active ^ HAL_GPIO_##name##_active_state)									\
      PORT->Group[HAL_GPIO_PORT##port].OUTCLR.reg = (1 << pin);			\
    else									\
      PORT->Group[HAL_GPIO_PORT##port].OUTSET.reg = (1 << pin);			\
  }										\
										\
  static inline void HAL_GPIO_##name##_in(void)					\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].DIRCLR.reg = (1 << pin);			\
    PORT->Group[HAL_GPIO_PORT##port].PINCFG[pin].reg |= PORT_PINCFG_INEN;	\
    PORT->Group[HAL_GPIO_PORT##port].PINCFG[pin].reg &= ~PORT_PINCFG_PULLEN;	\
    (void)HAL_GPIO_##name##_in;							\
  }										\
										\
  static inline void HAL_GPIO_##name##_out(void)				\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].DIRSET.reg = (1 << pin);			\
    PORT->Group[HAL_GPIO_PORT##port].PINCFG[pin].reg |= PORT_PINCFG_INEN;	\
    (void)HAL_GPIO_##name##_out;						\
  }										\
										\
  static inline void HAL_GPIO_##name##_pullup(void)				\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].OUTSET.reg = (1 << pin);			\
    PORT->Group[HAL_GPIO_PORT##port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;	\
    (void)HAL_GPIO_##name##_pullup;						\
  }										\
										\
  static inline int HAL_GPIO_##name##_read(void)				\
  {										\
    return (PORT->Group[HAL_GPIO_PORT##port].IN.reg & (1 << pin)) != 0;		\
    (void)HAL_GPIO_##name##_read;						\
  }										\
										\
  static inline int HAL_GPIO_##name##_active(void)				\
  {										\
    return ((PORT->Group[HAL_GPIO_PORT##port].IN.reg & (1 << pin)) >> pin);		\
  }										\
										\
  static inline int HAL_GPIO_##name##_state(void)				\
  {										\
    return (PORT->Group[HAL_GPIO_PORT##port].DIR.reg & (1 << pin)) != 0;	\
    (void)HAL_GPIO_##name##_state;						\
  }										\
										\
  static inline void HAL_GPIO_##name##_pmuxen(int mux)				\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].PINCFG[pin].reg |= PORT_PINCFG_PMUXEN;	\
    if (pin & 1)								\
      PORT->Group[HAL_GPIO_PORT##port].PMUX[pin>>1].bit.PMUXO = mux;		\
    else									\
      PORT->Group[HAL_GPIO_PORT##port].PMUX[pin>>1].bit.PMUXE = mux;		\
    (void)HAL_GPIO_##name##_pmuxen;						\
  }										\
										\
  static inline void HAL_GPIO_##name##_pmuxdis(void)				\
  {										\
    PORT->Group[HAL_GPIO_PORT##port].PINCFG[pin].reg &= ~PORT_PINCFG_PMUXEN;	\
    (void)HAL_GPIO_##name##_pmuxdis;						\
  }								\
	/**/

#ifdef IMPLEMENT_DBU

#define HAL_GPIO_PIN(name, port, pin, active_state)						\
	const uint32_t HAL_GPIO_##name##_active_state = active_state;\
	HAL_GPIO_INLINE_FUNCTIONS (name, port, pin)\
	/**/
	
#else 

#define HAL_GPIO_PIN(name, port, pin, normal_state)						\
	extern const uint32_t HAL_GPIO_##name##_active_state;\
	HAL_GPIO_INLINE_FUNCTIONS (name, port, pin)\
	/**/
	
#endif	/* IMPLEMENT_DBU */


void initialise_sercom_uart_rx_only (Sercom *scom,IRQn_Type,uint32_t);

//
// 
//
#define HAL_SCOM_UART_INLINE_FUNCTIONS_C(name,scom_name,mux,irqn,rx_pad) \
	static inline void HAL_UART_##name##_initialise(void) {\
		HAL_GPIO_##name##_pmuxen (mux);\
		MCLK->APBCMASK.reg |= MCLK_APBCMASK_##scom_name;\
		GCLK->PCHCTRL[scom_name##_GCLK_ID_CORE].reg = (\
				0\
			|	GCLK_PCHCTRL_GEN (0)\
			|	GCLK_PCHCTRL_CHEN\
		);\
		while (GCLK->SYNCBUSY.reg & ( 1 << (0 + 2)));\
		initialise_sercom_uart_rx_only (scom_name,irqn,rx_pad);\
	}\
	static inline void HAL_UART_##name##_enable(void) {\
		scom_name->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;\
		NVIC_EnableIRQ (irqn);\
	}\
	static inline void HAL_UART_##name##_disable(void) {\
		scom_name->USART.CTRLA.reg &= ~SERCOM_USART_CTRLA_ENABLE;\
		NVIC_DisableIRQ (irqn);\
	}\
  /**/

#define HAL_SCOM_UART_INLINE_FUNCTIONS_D(name,scom_name,mux,irqn,rx_pad) \
	static inline void HAL_UART_##name##_initialise(void) {\
		HAL_GPIO_##name##_pmuxen (mux);\
		MCLK->APBDMASK.reg |= MCLK_APBDMASK_##scom_name;\
		GCLK->PCHCTRL[scom_name##_GCLK_ID_CORE].reg = (\
				0\
			|	GCLK_PCHCTRL_GEN (0)\
			|	GCLK_PCHCTRL_CHEN\
		);\
		while (GCLK->SYNCBUSY.reg & ( 1 << (0 + 2)));\
		initialise_sercom_uart_rx_only (scom_name,irqn,rx_pad);\
	}\
	static inline void HAL_UART_##name##_enable(void) {\
		scom_name->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;\
		NVIC_EnableIRQ (irqn);\
	}\
	static inline void HAL_UART_##name##_disable(void) {\
		scom_name->USART.CTRLA.reg &= ~SERCOM_USART_CTRLA_ENABLE;\
		NVIC_DisableIRQ (irqn);\
	}\
  /**/

void initialise_sercom_spi (Sercom *scom,IRQn_Type,uint32_t,uint32_t);
void sercom_spi_write_read (SercomSpi*,byte_slice_t,byte_buffer_t);
uint32_t flash_get_chip_id (byte_buffer_t);
uint16_t flash_partial_erase (uint16_t,uint16_t);
uint8_t flash_begin_write (uint32_t);
uint8_t flash_write_chunk (uint8_t const*,uint32_t);
uint32_t flash_end_write (void);
uint32_t flash_read_content (uint32_t,byte_buffer_t);
void flash_wakeup (void);
void flash_sleep (void);

#define HAL_SCOM_SPI_INLINE_FUNCTIONS_C(name,scom_name,mux,irqn,dipo,dopo) \
	static inline void HAL_SPI_##name##_initialise(void) {\
		MCLK->APBCMASK.reg |= MCLK_APBCMASK_##scom_name;\
		GCLK->PCHCTRL[scom_name##_GCLK_ID_CORE].reg = (\
				0\
			|	GCLK_PCHCTRL_GEN (0)\
			|	GCLK_PCHCTRL_CHEN\
		);\
		while (GCLK->SYNCBUSY.reg & ( 1 << (0 + 2)));\
		initialise_sercom_spi (scom_name,irqn,dipo,dopo);\
	}\
	static inline void HAL_SPI_##name##_enable(void) {\
		HAL_GPIO_##name##_##MISO##_pmuxen (mux);\
		HAL_GPIO_##name##_##MOSI##_pmuxen (mux);\
		HAL_GPIO_##name##_##SCK##_pmuxen (mux);\
		scom_name->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_ENABLE;\
	}\
	static inline void HAL_SPI_##name##_disable(void) {\
		HAL_GPIO_##name##_##MISO##_pmuxdis ();\
		HAL_GPIO_##name##_##MOSI##_pmuxdis ();\
		HAL_GPIO_##name##_##SCK##_pmuxdis ();\
		HAL_GPIO_##name##_##MISO##_in ();\
		HAL_GPIO_##name##_##MOSI##_in ();\
		HAL_GPIO_##name##_##SCK##_in ();\
		scom_name->SPI.CTRLA.reg &= ~SERCOM_SPI_CTRLA_ENABLE;\
	}\
	static inline void HAL_SPI_##name##_write_read(byte_slice_t wr,byte_buffer_t rd) {\
		sercom_spi_write_read (&scom_name->SPI,wr,rd);\
	}\
  /**/

#ifdef IMPLEMENT_DBU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

void
initialise_sercom_spi (
	Sercom *scom,IRQn_Type interupt_number,uint32_t dipo,uint32_t dopo
) {
	SercomSpi *spi = &(scom->SPI);

	spi->CTRLA.reg = (
			SERCOM_SPI_CTRLA_MODE (0x03)	// Set the SERCOM in SPI master mode 
		|	SERCOM_SPI_CTRLA_SWRST
	);
	while (spi->CTRLA.bit.SWRST);
	
	uint64_t baud = F_CPU/(2 * FPGA_SPI_BIT_RATE) - 1;
	spi->BAUD.reg = (uint16_t) baud;

	spi->CTRLA.reg = (
			SERCOM_SPI_CTRLA_MODE (0x03)	// Set the SERCOM in SPI master mode 
		|	SERCOM_SPI_CTRLA_DOPO (dopo)
		|	SERCOM_SPI_CTRLA_DIPO (dipo)
	);

	spi->CTRLB.reg = (
			SERCOM_SPI_CTRLB_RXEN
		|	SERCOM_SPI_CTRLB_CHSIZE (0)
	);
}

void
sercom_spi_write_read (SercomSpi *spi,byte_slice_t wr,byte_buffer_t rd) {
	uint32_t write_incr = 1,read_incr = 1;
	uint8_t dummy_data = 0xff;
	int32_t length;

	if (wr.size == 0) {
		wr.bytes = &dummy_data;
		write_incr = 0;
	}
	
	if (rd.size == 0) {
		rd.bytes = &dummy_data;
		read_incr = 0;
	}
	
	length = (wr.size > rd.size)? wr.size : rd.size;
	while (length--) {
		while (spi->INTFLAG.bit.DRE == 0);
		spi->DATA.reg = *(wr.bytes);
		wr.bytes += write_incr;

		while ((spi->INTFLAG.reg & SERCOM_SPI_INTFLAG_RXC) == 0);
		*rd.bytes = (uint8_t) spi->DATA.reg;
		rd.bytes += read_incr;
	}
}


//
// do not enable TX so that the Tx pad is not claimed by the sercom
//
void
initialise_sercom_uart_rx_only (Sercom *scom,IRQn_Type irqn,uint32_t rx_pad) {

	scom->USART.CTRLA.reg = SERCOM_USART_CTRLA_SWRST;
	while (scom->USART.CTRLA.bit.SWRST);

	//
	// there is some difference with SERCOM5 that means the config used for
	// SERCOMs 0 .. 4, does not work for 5
	//
	// SERCOM5 is in power domain PD0 (others are in PD1)
	// need to use arithmetic baud rate for SERCOM5
	// (limititations of PD0)
	//

	if (scom == SERCOM5) {
		uint64_t baud;
		baud = 65536ULL - (65536ULL * 16 * SWO_UART_BIT_RATE )/F_CPU;
		
		scom->USART.CTRLA.reg = (
				SERCOM_USART_CTRLA_DORD 
			|	SERCOM_USART_CTRLA_MODE (1) 
			|	SERCOM_USART_CTRLA_FORM (0)
			|	SERCOM_USART_CTRLA_SAMPR (0) 
			|	SERCOM_USART_CTRLA_RXPO (rx_pad)
		);

		scom->USART.BAUD.reg = (uint16_t) baud;
	} else {
		uint32_t baud,fp;
		baud = F_CPU / (16 * SWO_UART_BIT_RATE);
		fp = (F_CPU / SWO_UART_BIT_RATE - 16 * baud) / 2;
		scom->USART.CTRLA.reg = (
				SERCOM_USART_CTRLA_DORD 
			|	SERCOM_USART_CTRLA_MODE (1) 
			|	SERCOM_USART_CTRLA_FORM (0)
			|	SERCOM_USART_CTRLA_SAMPR (1) 
			|	SERCOM_USART_CTRLA_RXPO (rx_pad)
		);

		scom->USART.BAUD.reg = (
				SERCOM_USART_BAUD_FRACFP_BAUD (baud)
			|	SERCOM_USART_BAUD_FRACFP_FP (fp)
		);
	}
	
//	baud = F_CPU / (16 * SWO_UART_BIT_RATE);
//	fp = (F_CPU / SWO_UART_BIT_RATE - 16 * baud) / 2;

	scom->USART.CTRLB.reg = (
			SERCOM_USART_CTRLB_RXEN
		|	SERCOM_USART_CTRLB_CHSIZE (0)
	);

	scom->USART.INTENSET.reg = (
			SERCOM_USART_INTENSET_RXC
		|	SERCOM_USART_INTENSET_ERROR
	);
	
//	scom->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
//	NVIC_EnableIRQ (irqn);
}


#endif	/* IMPLEMENT_DBU */
#endif // _HAL_GPIO_H_
/*
 * Copyright (c) 2014-2016, Alex Taradov <alex@taradov.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*

BSD 3-Clause License

Copyright (c) 2025, Gregor Bruce

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */





