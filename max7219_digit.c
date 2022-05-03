#include "max7219_digit.h"


void _max7219_print_one_digit	( max7219_struct 	_max7219_handler 	,
								uint8_t 			_position 			,
								uint32_t 			_value1				,
								uint32_t 			_value2				) ;

void _max7219_write_strob		( max7219_struct 	_max7219_handler	) ;
void _max7219_push_data			( max7219_struct 	_max7219_handler	) ;
void _local_delay				( uint32_t 			_delay_u32			) ;
uint8_t inverse_order_in_byte	( uint8_t 			_input 				) ;

/***************************************************************************************/
/***************************************************************************************/

void max7219_init2(	max7219_struct 			*_max7219_handler	,
					max7219_Decode_Mode 	_decodemode			,
					max7219_LED_Intensity	_intensity			,
					max7219_Scan_Limit 		_scanlimit			,
					max7219_Shutdown 		_shutdown 			) {

	// test - Off
	_max7219_handler->data[ 0] = ADDR_DISPLAY_TEST ;  _max7219_handler->data[ 1] = WorkMode ;
	_max7219_handler->data[ 2] = ADDR_DISPLAY_TEST ;  _max7219_handler->data[ 3] = WorkMode ;
	_max7219_handler->data[ 4] = ADDR_DISPLAY_TEST ;  _max7219_handler->data[ 5] = WorkMode ;
	_max7219_handler->data[ 6] = ADDR_DISPLAY_TEST ;  _max7219_handler->data[ 7] = WorkMode ;
	_max7219_push_data( *_max7219_handler ) ;

	// Decode Mode - No. 1 in 1
	_max7219_handler->data[ 0] = ADDR_DECODE_MODE ;  _max7219_handler->data[ 1] = _decodemode ;
	_max7219_handler->data[ 2] = ADDR_DECODE_MODE ;  _max7219_handler->data[ 3] = _decodemode ;
	_max7219_handler->data[ 4] = ADDR_DECODE_MODE ;  _max7219_handler->data[ 5] = _decodemode ;
	_max7219_handler->data[ 6] = ADDR_DECODE_MODE ;  _max7219_handler->data[ 7] = _decodemode ;
	_max7219_push_data( *_max7219_handler ) ;

	// Intensity x/32
	_max7219_handler->data[ 0] = ADDR_INTENSITY ;  _max7219_handler->data[ 1] = _intensity ;
	_max7219_handler->data[ 2] = ADDR_INTENSITY ;  _max7219_handler->data[ 3] = _intensity ;
	_max7219_handler->data[ 4] = ADDR_INTENSITY ;  _max7219_handler->data[ 5] = _intensity ;
	_max7219_handler->data[ 6] = ADDR_INTENSITY ;  _max7219_handler->data[ 7] = _intensity ;
	_max7219_push_data( *_max7219_handler ) ;

	//Scan Limit - All
	_max7219_handler->data[ 0] = ADDR_SCAN_LIMIT ;  _max7219_handler->data[ 1] = _scanlimit ;
	_max7219_handler->data[ 2] = ADDR_SCAN_LIMIT ;  _max7219_handler->data[ 3] = _scanlimit ;
	_max7219_handler->data[ 4] = ADDR_SCAN_LIMIT ;  _max7219_handler->data[ 5] = _scanlimit ;
	_max7219_handler->data[ 6] = ADDR_SCAN_LIMIT ;  _max7219_handler->data[ 7] = _scanlimit ;
	_max7219_push_data( *_max7219_handler ) ;

	// Shutdown - none
	// myTrans[1] -> 00 sleep
	// myTrans[1] -> 01 work
	_max7219_handler->data[ 0] = ADDR_SHUTDOWN;  _max7219_handler->data[ 1] = _shutdown;
	_max7219_handler->data[ 2] = ADDR_SHUTDOWN;  _max7219_handler->data[ 3] = _shutdown;
	_max7219_handler->data[ 4] = ADDR_SHUTDOWN;  _max7219_handler->data[ 5] = _shutdown;
	_max7219_handler->data[ 6] = ADDR_SHUTDOWN;  _max7219_handler->data[ 7] = _shutdown;
	_max7219_push_data( *_max7219_handler ) ;
}
/***************************************************************************************/
/***************************************************************************************/

void max7219_init4(	max7219_struct 			*_max7219_handler	,
					max7219_Decode_Mode 	_decodemode			,
					max7219_LED_Intensity	_intensity			,
					max7219_Scan_Limit 		_scanlimit			,
					max7219_Shutdown 		_shutdown 			) {

	// test - Off
	for (int i=0; i<2; i++) {
		_max7219_handler->data[ i*2 ] = ADDR_DISPLAY_TEST ;  _max7219_handler->data[ i*2+1] = WorkMode ;
	}
	_max7219_push_data( *_max7219_handler ) ;

	// Decode Mode - No. 1 in 1
	for (int i=0; i<2; i++) {
		_max7219_handler->data[ i*2 ] = ADDR_DECODE_MODE ;  _max7219_handler->data[ i*2+1] = _decodemode ;
	}
	_max7219_push_data( *_max7219_handler ) ;

	// Intensity x/32
	for (int i=0; i<2; i++) {
		_max7219_handler->data[ i*2 ] = ADDR_INTENSITY ;  _max7219_handler->data[ i*2+1] = _intensity ;
	}
	_max7219_push_data( *_max7219_handler ) ;

	//Scan Limit - All
	for (int i=0; i<2; i++) {
		_max7219_handler->data[ i*2 ] = ADDR_SCAN_LIMIT ;  _max7219_handler->data[ i*2+1] = _scanlimit ;
	}
	_max7219_push_data( *_max7219_handler ) ;

	// Shutdown - none
	// myTrans[1] -> 00 sleep
	// myTrans[1] -> 01 work
	for (int i=0; i<2; i++) {
		_max7219_handler->data[ i*2 ] = ADDR_SHUTDOWN ;  _max7219_handler->data[ i*2+1] = _shutdown ;
	}
	_max7219_push_data( *_max7219_handler ) ;
}
/***************************************************************************************/

void _max7219_push_data( max7219_struct 	_max7219_handler ) {
    HAL_SPI_Transmit( _max7219_handler.spi , _max7219_handler.data , BYTE4_IN_SPI_PACKAGE , SPI_PACKAGE_TIMEOUT ) ;
    _max7219_write_strob( _max7219_handler ) ;
}
/***************************************************************************************/

void _max7219_write_strob( max7219_struct 	_max7219_handler ) {
	HAL_GPIO_WritePin( _max7219_handler.cs_port , _max7219_handler.cs_pin , SET ) ;
	_local_delay( WRITE_STROB_DELAY ) ;
	HAL_GPIO_WritePin( _max7219_handler.cs_port , _max7219_handler.cs_pin , RESET ) ;
}
/***************************************************************************************/

void _local_delay ( uint32_t _delay_u32 ) {
	for ( ; _delay_u32 > 0; _delay_u32-- ) {
		__asm( "nop" ) ;
	}
}
/***************************************************************************************/

void max7219_print_value(	max7219_struct	*max7219_handler	,
							uint32_t 		value1				,
							uint32_t		value2				,
							position_enum 	position			) {

	_max7219_print_one_digit(*max7219_handler, position + 4, (value1/1000) % 10 , (value2/1000) % 10 );
	_max7219_print_one_digit(*max7219_handler, position + 3, (value1/100 ) % 10 , (value2/100 ) % 10 );
	_max7219_print_one_digit(*max7219_handler, position + 2, (value1/10  ) % 10 , (value2/10  ) % 10 );
	_max7219_print_one_digit(*max7219_handler, position + 1, (value1     ) % 10 , (value2     ) % 10 );
}
/***************************************************************************************/
/***************************************************************************************/


void _max7219_print_one_digit(	max7219_struct 	_max7219_handler	,
								uint8_t 		_position			,
								uint32_t 		_value1				,
								uint32_t 		_value2				) {

	uint8_t spi_buffer[4]		;
	spi_buffer[0] = _position	; // razryad
	spi_buffer[1] = _value1		; // znachenie
	spi_buffer[2] = _position	; // razryad
	spi_buffer[3] = _value2		; // znachenie
	HAL_SPI_Transmit( _max7219_handler.spi , spi_buffer , 4 , SPI_PACKAGE_TIMEOUT ) ;
	_max7219_write_strob( _max7219_handler ) ;
}
/***************************************************************************************/

uint8_t inverse_order_in_byte (uint8_t 		input) {

    uint8_t var_u8 =((input & 0x01) << 7) |
					((input & 0x02) << 5) |
					((input & 0x04) << 3) |
					((input & 0x08) << 1) |
					((input & 0x10) >> 1) |
					((input & 0x20) >> 3) |
					((input & 0x40) >> 5) |
					((input & 0x80) >> 7) ;
    return var_u8 ;
}
/***************************************************************************************/
