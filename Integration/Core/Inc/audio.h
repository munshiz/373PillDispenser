/*
 * audio.h
 *
 *  Created on: Apr 23, 2024
 *      Author: zawad
 */

/*#ifndef INC_AUDIO_H_
#define INC_AUDIO_H_

//#include "main.h"
#include "stm32l4xx_hal.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void fill_LUT(void);


//sets compare value (period) for tim2
void setComp(uint32_t newComp);

void changeNote(float frequency);
void TIM2_ISR();


void runAudio();


#endif /* INC_AUDIO_H_ */
