#include <stdint.h>
#include "main.h"

void Pixy_init(SPI_HandleTypeDef * hspi1);
void sendToPixy(uint8_t *data, uint8_t length);
void recvFromPixy(uint8_t *data, uint8_t length);
uint8_t Scan();
