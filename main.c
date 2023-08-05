/*
 * main.c
 *
 *
 *      Author: Abdelrahman Adel
 */
#include "gpio.h"
#include "lcd.h"
#include "avr/interrupt.h"
#include "util/delay.h"
#include "uart.h"
#include "avr/io.h"
#include "gpio.h"


uint8 data_arr_X [80],data_arr[9];
uint8 data ,flag=0 ;
uint8 i=0,x,b=9,m=0;

USART_config_t uart_element =
{
		.USART_mode_select = ASYNCHRONOUS_OPERATION,
		.character_size = _8_BIT,
		.recive_data_statuse = RX_ENABLE,
		.transmitter_data_statuse =TX_ENABLE,
		//.RX_complete_interrupt_enable = RX_COMPLETE_INTERRUPT_ENABLE,
		.baud_rate = 19200

};

ISR(USART_RXC_vect)


{
	GPIO_writePin(PORTC_INDEX,PIN1,GPIO_HIGH);
	flag=1;

}


int main (void)
{
	GPIO_setupPinDirection(PORTC_INDEX,PIN1,PIN_OUTPUT_);
	GPIO_writePin(PORTC_INDEX,PIN1,GPIO_LOW);

	UART_initialize(&uart_element);
	LCD_init();
	LCD_displayString("system loading..");
	_delay_ms(500);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("Waiting for GPS");
	_delay_ms(500);
	SREG = SREG |(1<<7);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	while (1)
	{
		while (i != 80 )
		{
			data = UART_recieveByte();
			data_arr_X[i] = data ;
			i++;

		}
		while (1) {
			LCD_displayString(" UTC time :");
			LCD_moveCursor(1,1);
			for (i=10;data_arr_X[i] != ',';i++)
			{

				//LCD_sendCommand(LCD_CLEAR_COMMAND);

				LCD_displayCharacter(data_arr_X[i]);
				_delay_ms(20);


			}
			LCD_displayCharacter(data_arr_X[19]);
			_delay_ms(1000);

			// ************************
			LCD_sendCommand(LCD_CLEAR_COMMAND);

			LCD_displayString("Latitude : ");
			LCD_moveCursor(1,1);
			for (i=23;data_arr_X[i] != ',';i++)
			{


				LCD_displayCharacter(data_arr_X[i]);
				_delay_ms(20);


			}
			LCD_displayCharacter(data_arr_X[33]);



			_delay_ms(2000);

			// ************************
			LCD_sendCommand(LCD_CLEAR_COMMAND);

			LCD_displayString("Longitude : ");
			LCD_moveCursor(1,1);
			for (i=35;data_arr_X[i] != ',';i++)
			{

				//LCD_sendCommand(LCD_CLEAR_COMMAND);

				LCD_displayCharacter(data_arr_X[i]);
				_delay_ms(20);


			}
			LCD_displayCharacter(data_arr_X[46]);
			_delay_ms(2000);

			LCD_sendCommand(LCD_CLEAR_COMMAND);

			//*********************************

			LCD_sendCommand(LCD_CLEAR_COMMAND);
			LCD_displayString("Updating GPS ");
			LCD_moveCursor(1,1);
			LCD_displayString("data-> ");
			LCD_displayCharacter('.');
			_delay_ms(300);
			LCD_displayCharacter('.');
			_delay_ms(300);
			LCD_displayCharacter('.');
			_delay_ms(300);
			LCD_displayCharacter('.');
			_delay_ms(300);
			LCD_displayCharacter('.');
			LCD_sendCommand(LCD_CLEAR_COMMAND);

		}

	}

}

