/**
* \file
* \version 1.0
* \author bazhen.levkovets
** \date 2018
*
*************************************************************************************
* \copyright	Bazhen Levkovets
* \copyright	Brovary, Kyiv region
* \copyright	Ukraine
*
*************************************************************************************
*
* \brief
*
*/

#ifndef MAX7219_DIGIT_H_INCLUDED
#define MAX7219_DIGIT_H_INCLUDED

/*
**************************************************************************
*								INCLUDE FILES
**************************************************************************
*/
	#include "main.h"

/*
**************************************************************************
*								    ENUM
**************************************************************************
*/

typedef enum{
	DisplayDigit_0_only	=	0x00 ,
	DisplayDigit_0_1	=	0x01 ,
	DisplayDigit_0_2	=	0x02 ,
	DisplayDigit_0_3	=	0x03 ,
	DisplayDigit_0_4	=	0x04 ,
	DisplayDigit_0_5	=	0x05 ,
	DisplayDigit_0_6	=	0x06 ,
	DisplayDigit_0_7	=	0x07
}		max7219_Scan_Limit ;

typedef enum {
	Intensity_1		= 0x00 ,
	Intensity_3		= 0x01 ,
	Intensity_5		= 0x02 ,
	Intensity_7		= 0x03 ,
	Intensity_9		= 0x04 ,
	Intensity_11	= 0x05 ,
	Intensity_13	= 0x06 ,
	Intensity_15	= 0x07 ,
	Intensity_17	= 0x08 ,
	Intensity_19	= 0x09 ,
	Intensity_21	= 0x0A ,
	Intensity_23	= 0x0B ,
	Intensity_25	= 0x0C ,
	Intensity_27	= 0x0D ,
	Intensity_29	= 0x0E ,
	Intensity_31	= 0x0F
}		max7219_LED_Intensity ;
//----------------------------------

typedef enum
{
	ShutdownMode	= 0 ,
	NormalOperation	= 1
}		max7219_Shutdown ;
//----------------------------------

typedef enum
{
	WorkMode	= 0,
	TestMode	= 1
}		max7219_Display_Test ;
//----------------------------------

typedef enum
{
	NoDecode			= 0x00 ,
	DecodeForDigit_0	= 0x01 ,
	DecodeForDigit_1_0	= 0x03 ,
	DecodeForDigit_2_0	= 0x07 ,
	DecodeForDigit_3_0	= 0x0F ,
	DecodeForDigit_4_0	= 0x1F ,
	DecodeForDigit_5_0	= 0x3F ,
	DecodeForDigit_6_0	= 0x7F ,
	DecodeForDigit_7_0	= 0xFF ,
}		max7219_Decode_Mode ;


/*
**************************************************************************
*								    DEFINES
**************************************************************************
*/



/*
**************************************************************************
*								    STRUCT
**************************************************************************
*/

typedef struct
{
	SPI_HandleTypeDef	*spi;
	GPIO_TypeDef 		*cs_port;
    uint16_t 			 cs_pin;
} max7219_struct;

typedef struct
{
//	// test - On
//	spi_buffer[0] = 0x0F;  spi_buffer[1] = 0x01;
//
//	// test - Off
//	spi_buffer[0] = 0x0F;  spi_buffer[1] = 0x00;
//
//	// Decode Mode - No 1 in 1
//	// spi_buffer[1] hex   -> FF
//	// spi_buffer[1] pixel -> 00
//	uint8_t DecodeMode = 0xFF;
//	spi_buffer[0] = 0x09;  spi_buffer[1] = DecodeMode;	// pixel
//
//
//	// Intensity 3/32 0x01,
//	spi_buffer[0] = 0x0A;  spi_buffer[1] = 0x03;
//
//
//	//Scan Limit - All
//	spi_buffer[0] = 0x0B;  spi_buffer[1] = 0x07;
//
//
//	// Shutdown - none
//	// spi_buffer[1] -> 00 sleep
//	// spi_buffer[1] -> 01 work
//	spi_buffer[0] = 0x0C;  spi_buffer[1] = 0x01;

}
max7219_init_struct;

typedef enum
{
	most_position  = 0,
	least_position = 1
} position_enum;

/*
**************************************************************************
*                        GLOBAL FUNCTION PROTOTYPES
**************************************************************************
*/

	void max7219_init(max7219_struct *max7219_handler);
	void max7219_print_value(max7219_struct *max7219_handler, uint32_t value, position_enum position);

//	void max7219_init	( max7219_struct 		*max7219_handler	,
//						max7219_Decode_Mode 	_decodemode			,
//						max7219_LED_Intensity	_intensity			,
//						max7219_Scan_Limit 		_scanlimit	 		,
//						max7219_Shutdown 		_shutdown 			) ;
//
//	void Max7219_struct_init (	max7219_struct 		*handler		,
//								SPI_HandleTypeDef	*_spi			,
//								GPIO_TypeDef 		*_cs_port		,
//								uint16_t 			 _cs_pin		) ;


/*
**************************************************************************
*                                   END
**************************************************************************
*/

#endif 	//	MAX7219_DIGIT_H_INCLUDED

