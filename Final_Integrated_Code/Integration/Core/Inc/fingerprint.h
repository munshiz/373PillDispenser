#include <stdint.h>
#include "main.h"

void fingerprint_init(UART_HandleTypeDef * uart_handle);


int fingerprintAddPrint();

int fingerprintScanPrint();

int fingerprintRemovePrint();

uint8_t fingerprint_UART_read();
