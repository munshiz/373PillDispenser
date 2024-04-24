#include <stdint.h>
#include "main.h"

void Pixy_init(I2C_HandleTypeDef * i2c);
void sendToPixy(uint8_t *data, uint8_t length);
void recvFromPixy(uint8_t *data, uint8_t length);
uint8_t Scan();



