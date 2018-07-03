
#include "stm32f1xx_hal.h"
#include "max7219_digit.h"

void _max7219_print_one_digit(max7219_struct max7219_handler, uint8_t position, uint32_t value);
void _max7219_write_strob(max7219_struct max7219_handler);
/***************************************************************************************/


void max7219_init(max7219_struct *max7219_handler)
{
	uint8_t spi_buffer[2];
	HAL_GPIO_WritePin(max7219_handler->cs_port, max7219_handler->cs_pin, RESET);

	// test - On
	spi_buffer[0] = 0x0F;  spi_buffer[1] = 0x01;
	HAL_SPI_Transmit(max7219_handler->spi, spi_buffer, 2, 1);
	_max7219_write_strob(*max7219_handler);

	HAL_Delay(1000);

	// test - Off
	spi_buffer[0] = 0x0F;  spi_buffer[1] = 0x00;
	HAL_SPI_Transmit(max7219_handler->spi, spi_buffer, 2, 1);
	_max7219_write_strob(*max7219_handler);

	// Decode Mode - No 1 in 1
	// spi_buffer[1] hex   -> FF
	// spi_buffer[1] pixel -> 00
	int DecodeMode = 0xFF;
	spi_buffer[0] = 0x09;  spi_buffer[1] = DecodeMode;	// pixel
	HAL_SPI_Transmit(max7219_handler->spi, spi_buffer, 2, 1);
	_max7219_write_strob(*max7219_handler);

	// Intensity 3/32 0x01,
	spi_buffer[0] = 0x0A;  spi_buffer[1] = 0x03;
	HAL_SPI_Transmit(max7219_handler->spi, spi_buffer, 2, 1);
	_max7219_write_strob(*max7219_handler);

	//Scan Limit - All
	spi_buffer[0] = 0x0B;  spi_buffer[1] = 0x07;
	HAL_SPI_Transmit(max7219_handler->spi, spi_buffer, 2, 1);
	_max7219_write_strob(*max7219_handler);

	// Shutdown - none
	// spi_buffer[1] -> 00 sleep
	// spi_buffer[1] -> 01 work
	spi_buffer[0] = 0x0C;  spi_buffer[1] = 0x01;
	HAL_SPI_Transmit(max7219_handler->spi, spi_buffer, 2, 1);
	_max7219_write_strob(*max7219_handler);
}
/***************************************************************************************/

void max7219_print_value(max7219_struct *max7219_handler,uint32_t value, uint8_t position)
{
	if (position == 0) position = 4;
	else 			position = 0;
	_max7219_print_one_digit(*max7219_handler, 4 + position, (value/1000) % 10 );
	_max7219_print_one_digit(*max7219_handler, 3 + position, (value/100 ) % 10 );
	_max7219_print_one_digit(*max7219_handler, 2 + position, (value/10  ) % 10 );
	_max7219_print_one_digit(*max7219_handler, 1 + position, (value     ) % 10 );
}
/***************************************************************************************/
/***************************************************************************************/

void _max7219_print_one_digit(max7219_struct max7219_handler, uint8_t position, uint32_t value)
{
	uint8_t spi_buffer[2];
	spi_buffer[0] = position	; // razryad
	spi_buffer[1] = value	; // znachenie
	HAL_SPI_Transmit(max7219_handler.spi, spi_buffer, 2, 1);
	_max7219_write_strob(max7219_handler);
}
/***************************************************************************************/

void _max7219_write_strob(max7219_struct max7219_handler)
{
	HAL_Delay(1);
	HAL_GPIO_WritePin(max7219_handler.cs_port, max7219_handler.cs_pin, SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(max7219_handler.cs_port, max7219_handler.cs_pin, RESET);
	HAL_Delay(1);
}
/***************************************************************************************/
