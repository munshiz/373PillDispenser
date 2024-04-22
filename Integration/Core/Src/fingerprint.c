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
 
  
  
 
UART_HandleTypeDef * arduino_uart;

//Sets UART Handle for our UART Stuff.
void fingerprint_init(UART_HandleTypeDef * uart_handle) {
	arduino_uart = uart_handle;
}


int fingerprintAddPrint(){
	uint8_t tx_buffer [1];
	tx_buffer [0] = 0x1;
	uint8_t rx_buffer [1];
	HAL_UART_Transmit(arduino_uart, tx_buffer, 1, 100);
	HAL_UART_Receive(arduino_uart, rx_buffer, 1, 100);
	assert(rx_buffer == 0x3);
}

int fingerprintScanPrint(){
	uint8_t tx_buffer [1];
	tx_buffer [0] = 0x2;
	uint8_t rx_buffer [1];
	HAL_UART_Transmit(arduino_uart, tx_buffer, 1, 100);
	HAL_UART_Receive(arduino_uart, rx_buffer, 1, 100);
	assert(rx_buffer == 0x4);
}

int fingerprintRemovePrint(){
	uint8_t tx_buffer [1];
	tx_buffer [0] = 0x3;
	uint8_t rx_buffer [1];
	HAL_UART_Transmit(arduino_uart, tx_buffer, 1, 100);
	HAL_UART_Receive(arduino_uart, rx_buffer, 1, 100);
	assert(rx_buffer == 0x5);
}
