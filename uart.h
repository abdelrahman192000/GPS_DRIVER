/*
 * uart.h
 *
 *  Created on: Jul 12, 2023
 *
 * Author: Abdelrahman Adel
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

#define DOUBLE_TR_SPEED





/************************** UCSRA types definition  **************************/

typedef enum
{
	ASYNCHRONOUS_NORMAL_MODE=0,
	SYNCHRONOUS_DOUBLE_SPEED_MODE=2

}asynchronous_speed_mode_select_t;


/* ********************************************************** */


/************************** UCSRB types definition  **************************/

typedef enum
{
	RX_COMPLETE_INTERRUPT_DISABLE,
	RX_COMPLETE_INTERRUPT_ENABLE=128

}RX_complete_interrupt_enable_t;

typedef enum
{
	TX_COMPLETE_INTERRUPT_DISABLE,
	TX_COMPLETE_INTERRUPT_ENABLE

}TX_complete_interrupt_enable_t;

typedef enum
{
	Data_REG_EMPTY_INTERRUPT_DISABLE,
	Data_REG_EMPTY_INTERRUPT_ENABLE

}DATA_reg_interrupt_enable_t;

typedef enum
{
	RX_DISABLE,
	RX_ENABLE = 16


}recive_data_statuse_t;

typedef enum
{
	TX_DISABLE,
	TX_ENABLE = 8


}transmitter_data_statuse_t;


/* ********************************************************** */

/************************** UCSRC types definition  **************************/

typedef enum
{
	ASYNCHRONOUS_OPERATION,
	SYNCHRONOUS_OPERATION

}USART_mode_select_t;

typedef enum
{
	DISABLED,
	EVEN_PARITY,
	ODD_PARITY

}parity_mode_select_t;

typedef enum
{
	_1_BIT,
	_2_BIT

}stop_bit_select_t;

typedef enum
{
	_5_BIT=0,
	_6_BIT,
	_7_BIT,
	_8_BIT,
	_9_BIT

}character_size_t;

/* ********************************************************** */



typedef struct
{
	asynchronous_speed_mode_select_t asynchronous_speed_mode_select;
	USART_mode_select_t USART_mode_select ;
	parity_mode_select_t parity_mode_select ;
	stop_bit_select_t stop_bit_select ;
	character_size_t character_size ;
	RX_complete_interrupt_enable_t RX_complete_interrupt_enable;
	TX_complete_interrupt_enable_t TX_complete_interrupt_enable;
	DATA_reg_interrupt_enable_t DATA_reg_interrupt_enable;
	recive_data_statuse_t recive_data_statuse;
	transmitter_data_statuse_t transmitter_data_statuse;
	uint32 baud_rate;

}USART_config_t;

void UART_initialize (USART_config_t *USART_config);

void UART_init(uint32 baud_rate);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #




#endif /* UART_H_ */
