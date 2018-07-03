#ifndef MAX7219_DIGIT_H_INCLUDED
#define MAX7219_DIGIT_H_INCLUDED

typedef struct
{
	SPI_HandleTypeDef	*spi;
	GPIO_TypeDef 		*cs_port;
    uint16_t 			 cs_pin;
} max7219_struct;

void max7219_init(max7219_struct *max7219_handler);
void max7219_print_value(max7219_struct *max7219_handler, uint32_t value, uint8_t position);

#endif 	//	MAX7219_DIGIT_H_INCLUDED

