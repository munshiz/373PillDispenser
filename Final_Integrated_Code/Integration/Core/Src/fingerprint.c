/*
 * xbee.c
 *
 *  Created on: Apr 14, 2024
 *      Author: shikhar
 */
 
 
 
 /**FINGERPRINT COMMAND LIST**/
/* Add: 1
 * Authenticate/Scan : 2
 * Remove: 3
 */
#include "fingerprint.h"
  
  
 
UART_HandleTypeDef * arduino_uart;

//Sets UART Handle for our UART Stuff.
void fingerprint_init(UART_HandleTypeDef * uart_handle) {
	arduino_uart = uart_handle;
}


int fingerprintAddPrint(){
	uint8_t tx_buffer [1];
	tx_buffer [0] = 0x1;
	uint8_t rx_buffer [1];
	HAL_UART_Transmit(arduino_uart, tx_buffer, 1, HAL_MAX_DELAY);
	HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
	return rx_buffer[0];
}

int fingerprintScanPrint(){
	uint8_t tx_buffer [1];
	tx_buffer [0] = 0x2;
	uint8_t rx_buffer [1];
	HAL_UART_Transmit(arduino_uart, tx_buffer, 1, HAL_MAX_DELAY);
	HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
	return rx_buffer[0];
}

int fingerprintRemovePrint(){
	uint8_t tx_buffer [1];
	tx_buffer [0] = 0x3;
	uint8_t rx_buffer [1];
	HAL_UART_Transmit(arduino_uart, tx_buffer, 1, HAL_MAX_DELAY);
	HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
	return rx_buffer[0];

}

uint8_t fingerprint_UART_read(){
	uint8_t rx_buffer [1];
	HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
	return rx_buffer[0];
}
