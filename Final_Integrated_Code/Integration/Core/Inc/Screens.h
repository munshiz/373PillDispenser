/*
 * Screens.h
 *
 *  Created on: Apr 13, 2024
 *      Author: zawad
 */

#ifndef INC_SCREENS_H_
#define INC_SCREENS_H_

#include "ili9488.h"
#include "xpt2046.h"

void authenticate();
void Dispense();
void LockScreen();
void testTouch();
void Home_Screen();
void Dispense_Auto_Manual();
void FingerPrint_Manager();
void scan_pill_screen();
void dispenserChoose(uint8_t mode);
void timeSet(uint8_t dispNum, uint8_t pillOption, uint8_t * daysOfWeek);
void lid_open_screen();
void New_Pill_Screen(uint8_t dispNum);
uint8_t FingerprintScan();

#endif /* INC_SCREENS_H_ */
