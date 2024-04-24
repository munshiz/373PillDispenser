#include "Pixy.h"

SPI_HandleTypeDef * Pixy_spi;

void Pixy_init(SPI_HandleTypeDef * hspi1){
	Pixy_spi = hspi1;
}
void sendToPixy(uint8_t *data, uint8_t length){
	//uint8_t numBytes = 0;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET); // Driving SPI SS for Pixy low (because it is active low)
	HAL_SPI_Transmit(Pixy_spi, data, length, 1000);
}

void recvFromPixy(uint8_t *data, uint8_t length){
	HAL_SPI_Receive(Pixy_spi, data, length, 1000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

uint8_t Scan(){


	uint8_t recvBuf[150] = {0x00};


	uint8_t versionRequest[] = {

		0xae,

		0xc1,

		0x0e,

		0x00

	  };


	sendToPixy(versionRequest, 4); // This is the dummy transaction

	HAL_Delay(1);

    recvFromPixy(recvBuf, 6+144);


    // Light Setting and also transaction to find idx


    uint8_t setLampON[] = {


			  0xae,

			  0xc1,

			  0x16,

			  0x02,

			  0x00,

			  0x01

    };


    uint8_t setLampOFF[] = {


      		  0xae,

      		  0xc1,

      		  0x16,

      		  0x02,

      		  0x00,

      		  0x00

    };


    sendToPixy(setLampON, 6);

	HAL_Delay(1);

	recvFromPixy(recvBuf, 6 + 144);


	uint8_t idx = 255; // idx used to find where in the recvBuf the 16-bit sync appears


	for (int i = 0; i < (149); i++){

		if ((recvBuf[i]== 0xaf) && (recvBuf[i+1] == 0xc1)){

			idx = i;

			break;

		}

	}


	//getBlocks command can now process properly

	uint8_t getBlocks[] = {


			  0xae,

			  0xc1,

			  0x20,

			  0x02,

			  0xff, //All signatures

			  0x01 // Returning 1 block

	};


	sendToPixy(getBlocks, 6);

    HAL_Delay(1);

    recvFromPixy(recvBuf, 6+144);


	uint8_t color_sig = recvBuf[idx + 6];

	uint16_t width_val = recvBuf[idx + 12];

    uint16_t height_val = recvBuf[idx + 14];


    uint16_t longest;

    uint16_t changeable_val = 90;

    char type;

    char color;


    if (height_val > width_val){ longest = height_val;}

    else{ longest = width_val;}


    if (longest > changeable_val){

    	type = 't';

    }

    else {type = 's';}


    if (color_sig == 1){color = 'r';}

    else if (color_sig == 3){color = 'y';}

    else if(color_sig == 4){color = 'g';}

    else {color = 'L';}


    sendToPixy(setLampOFF, 6);

	HAL_Delay(1);

	recvFromPixy(recvBuf, 6 + 144);

	return 0;
}

