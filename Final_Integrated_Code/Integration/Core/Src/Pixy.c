#include <stdint.h>
#include "Pixy.h"

I2C_HandleTypeDef * pixyi2c;

void Pixy_init(I2C_HandleTypeDef * i2c){
	pixyi2c = i2c;
}
void sendToPixy(uint8_t *data, uint8_t length){


	//uint8_t numBytes = 0;

	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET); // Driving SPI SS for Pixy low (because it is active low)

	//HAL_SPI_Transmit(&hspi1, data, length, 1000);

	HAL_I2C_Master_Transmit(pixyi2c, 0x54 << 1, data, length, 1000);

}


void recvFromPixy(uint8_t *data, uint8_t length){

	//HAL_SPI_Receive(&hspi1, data, length, 1000);

	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	HAL_I2C_Master_Receive(pixyi2c, 0x54 << 1, data, length, 1000);

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

	HAL_Delay(100);

    recvFromPixy(recvBuf, 12);


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

	HAL_Delay(100);

	recvFromPixy(recvBuf, 10);


//	uint8_t idx = 255; // idx used to find where in the recvBuf the 16-bit sync appears

//

//	for (int i = 0; i < (149); i++){

//		if ((recvBuf[i]== 0xaf) && (recvBuf[i+1] == 0xc1)){

//			idx = i;

//			break;

//		}

//	}


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

    HAL_Delay(100);

    recvFromPixy(recvBuf, 20);


    int timer = 0;


    uint8_t color_sig = recvBuf[6];


    while ((color_sig > 4) & (timer < 20)){

    	color_sig = recvBuf[6];

    	sendToPixy(getBlocks, 6);

		HAL_Delay(100);

		recvFromPixy(recvBuf, 20);

    }


    if (timer == 20){return 5;}


	color_sig = recvBuf[6];

	uint16_t width_val = recvBuf[12];

    uint16_t height_val = recvBuf[14];


    uint16_t longest = 0;

    uint16_t changeable_val = 80;

    uint8_t response;

    //char color;


    if (height_val > width_val){ longest = height_val;}

    else{ longest = width_val;}


    // Index understanding:

    // 0 is nothing detectd

    // 1 is red skittle

    // 2 is yellow skittle

    // 3 is green skittle

    // 4 is hot tamale

    // 5 is a bad bad sign


    if (longest < 10){response = 0;}

    else if (longest > changeable_val){response = 4;}

    else if (color_sig == 1){response = 1;}

    else if (color_sig == 3){response = 2;}

    else if (color_sig == 4){response = 3;}

    else {response = 5;}



    sendToPixy(setLampOFF, 6);

	HAL_Delay(100);

	recvFromPixy(recvBuf, 10);


	return response;

}
