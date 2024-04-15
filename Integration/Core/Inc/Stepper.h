/*
 * Pills.h
 *
 *  Created on: Apr 14, 2024
 *      Author: shikhar
 */

#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_

void lock(){
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
    for(int i=1;i<=100;i++){  //Moving stepper motor forward
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
      HAL_Delay(delay);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
      HAL_Delay(delay);
    }
}
void unlock(){
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    for(int i=1;i<=100;i++){  //Moving stepper motor forward
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
      HAL_Delay(delay);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
      HAL_Delay(delay);
    }
};
#endif /* INC_STEPPER_H_ */