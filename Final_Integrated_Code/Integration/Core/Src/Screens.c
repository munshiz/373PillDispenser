/*
 * Screens.c
 *
 *  Created on: Apr 13, 2024
 *      Author: zawad
 */
#include "Screens.h"
#include "ds1307.h"
#include "Pills.h"
#include "Stepper.h"
#include "Pixy.h"

#include "008_Open_Sans_Bold.h"
#include "009_Open_Sans_Bold.h"
#include "010_Open_Sans_Bold.h"
#include "012_Open_Sans_Bold.h"
#include "014_Open_Sans_Bold.h"
#include "016_Open_Sans_Bold.h"
#include "018_Open_Sans_Bold.h"
#include "020_Open_Sans_Bold.h"
#include "022_Open_Sans_Bold.h"
#include "024_Open_Sans_Bold.h"
#include "026_Open_Sans_Bold.h"
#include "028_Open_Sans_Bold.h"
#include "036_Open_Sans_Bold.h"
#include "048_Open_Sans_Bold.h"
#include "072_Open_Sans_Bold.h"
#include "096_Open_Sans_Bold.h"
#include "112_Open_Sans_Bold.h"
#include "128_Open_Sans_Bold.h"

#define _Open_Sans_Bold_8      &Open_Sans_Bold_8
#define _Open_Sans_Bold_9      &Open_Sans_Bold_9
#define _Open_Sans_Bold_10     &Open_Sans_Bold_10
#define _Open_Sans_Bold_11     &Open_Sans_Bold_11
#define _Open_Sans_Bold_12      &Open_Sans_Bold_12
#define _Open_Sans_Bold_14      &Open_Sans_Bold_14
#define _Open_Sans_Bold_16      &Open_Sans_Bold_16
#define _Open_Sans_Bold_18      &Open_Sans_Bold_18
#define _Open_Sans_Bold_20      &Open_Sans_Bold_20
#define _Open_Sans_Bold_22      &Open_Sans_Bold_22
#define _Open_Sans_Bold_24      &Open_Sans_Bold_24
#define _Open_Sans_Bold_26      &Open_Sans_Bold_26
#define _Open_Sans_Bold_28      &Open_Sans_Bold_28
#define _Open_Sans_Bold_36      &Open_Sans_Bold_36
#define _Open_Sans_Bold_48      &Open_Sans_Bold_48
#define _Open_Sans_Bold_72      &Open_Sans_Bold_72
#define _Open_Sans_Bold_96      &Open_Sans_Bold_96
#define _Open_Sans_Bold_112      &Open_Sans_Bold_112
#define _Open_Sans_Bold_128      &Open_Sans_Bold_128

	uint16_t touchX = 0;
	uint16_t touchY = 0;

void authenticate(){
	   fillScreen(ILI9488_WHITE);
		uint16_t touchX = 0, touchY = 0;
	   fillRect(100, 30,75,75, ILI9488_RED);
	   drawCharTest(130, 55, '1', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(200, 30,75,75, ILI9488_RED);
	   drawCharTest(230, 55, '2', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(300, 30,75,75, ILI9488_RED);
	   drawCharTest(319, 55, '3', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(100, 130,75,75, ILI9488_RED);
	   drawCharTest(130, 150, '4', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(200, 130,75,75, ILI9488_RED);
	   drawCharTest(230, 150, '5', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(300, 130,75,75, ILI9488_RED);
	   drawCharTest(319, 150, '6', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(100, 230,75,75, ILI9488_RED);
	   drawCharTest(130, 250, '7', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(200, 230,75,75, ILI9488_RED);
	   drawCharTest(230, 250, '8', ILI9488_WHITE,ILI9488_RED, 3);
	   fillRect(300, 230,75,75, ILI9488_RED);
	   drawCharTest(319, 250, '9', ILI9488_WHITE,ILI9488_RED, 3);
	   //drawChar(135, 61, '1', ILI9488_BLACK,ILI9488_RED, 1);


	   uint16_t count = 0;
	   char entered[6] = "     ";
	   char passcode[6] = "12345";
	   uint8_t temp;

	  while (1)
	  {
		  touchX = getX();
		  touchY = getY();

		  ILI9488_printText(entered, 10, 10, ILI9488_BLACK, ILI9488_WHITE, 1);

		  //absolutely horrible password checking...but works for testing TODO: make this not horrible.
		  if(count == 5){
			  if (!strcmp(entered, passcode)){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
				  Home_Screen();
				  return;

			  }
			  else {
				  char not_success_msg [50] = "Invalid, try again";
				  
				  LCD_Font(10, 10, not_success_msg, _Open_Sans_Bold_16, 1, ILI9488_BLACK);
				  memset(passcode,' ', 5);
				  count = 0;
				  HAL_Delay(1000);

			  }
			  break;
		  }

		  /*
		   * 75, 52
			75, 67
			97, 55
			97, 67
		   */
		  if(touchX >= 75 && touchX < 97 && touchY >= 52 && touchY < 67){
			fillRect(100, 30,75,75, ILI9488_GREEN);
			HAL_Delay(250);
			entered[count] = '1';
			count++;
		    fillRect(100, 30,75,75, ILI9488_RED);
		    drawCharTest(130, 55, '1', ILI9488_WHITE,ILI9488_RED, 3);
		  }

		  /*
		   * 2nd box:
			97, 52
			287, 52
			97, 67
			287, 67
		   */
		  if(touchX >= 100 && touchX < 287 && touchY >= 52 && touchY < 67){
			fillRect(200, 30,75,75, ILI9488_GREEN);
			HAL_Delay(250);
			entered[count] = '2';
			count++;
			fillRect(200, 30,75,75, ILI9488_RED);
			drawCharTest(230, 55, '2', ILI9488_WHITE,ILI9488_RED, 3);

		  }
		  /*else
			  fillRect(200, 30,75,75, ILI9488_RED);*/
		  //fillRect(touchX, touchY,5,5, ILI9488_RED);
		  //HAL_Delay(250);

		  /*3rd box:
			299, 52
			390, 52
			299, 67
			390, 167*/
		  if(touchX >= 299 && touchX < 372 && touchY >= 52 && touchY < 160){
			fillRect(300, 30,75,75, ILI9488_GREEN);
			HAL_Delay(250);
			entered[count] = '3';
			count++;
			fillRect(300, 30,75,75, ILI9488_RED);
			drawCharTest(319, 55, '3', ILI9488_WHITE,ILI9488_RED, 3);
		  }


			/*4th box:
			 * 75, 163
			 * 75, 219
			 * 97, 163
			 * 97, 219
			 *
			 *
			 */
			if(touchX >= 75 && touchX < 97 && touchY >= 163 && touchY < 219){
				fillRect(100, 130,75,75, ILI9488_GREEN);
				HAL_Delay(250);
				entered[count] = '4';
				count++;
				fillRect(100, 130,75,75, ILI9488_RED);
				drawCharTest(130, 150, '4', ILI9488_WHITE,ILI9488_RED, 3);

			}

			/*5th box:
			 * 97, 165
			 * 262, 165
			 * 97, 207
			 * 262, 207
			 */
			 if(touchX >= 100 && touchX < 262 && touchY >= 165 && touchY < 207){
				fillRect(200, 130,75,75, ILI9488_GREEN);
				HAL_Delay(250);
				entered[count] = '5';
				count++;
				fillRect(200, 130,75,75, ILI9488_RED);
				drawCharTest(230, 150, '5', ILI9488_WHITE,ILI9488_RED, 3);

			 }

			  /*6th box:
			 * 294, 166
			 * 381, 167
			 * 299, 207
			 * 372, 207
			 */
			 if(touchX >= 299 && touchX < 372 && touchY >= 167 && touchY < 207){
				fillRect(300, 130,75,75, ILI9488_GREEN);
				HAL_Delay(250);
				entered[count] = '6';
				count++;
				fillRect(300, 130,75,75, ILI9488_RED);
				drawCharTest(319, 150, '6', ILI9488_WHITE,ILI9488_RED, 3);
			 }


			/*7th box:
			 * 75, 242
			 * 97, 242
			 * 75, 309
			 * 97, 309
			 */
			if(touchX >= 75 && touchX < 97 && touchY >= 242 && touchY < 309){
				fillRect(100, 230,75,75, ILI9488_GREEN);
				HAL_Delay(250);
				entered[count] = '7';
				count++;
				fillRect(100, 230,75,75, ILI9488_RED);
				drawCharTest(130, 250, '7', ILI9488_WHITE,ILI9488_RED, 3);
			}


			/*8th box:
			 * 97, 242
			 * 262, 242
			 * 97, 309
			 * 287, 306
			 */
			if(touchX >= 100 && touchX < 280 && touchY >= 242 && touchY < 309){
				fillRect(200, 230,75,75, ILI9488_GREEN);
				HAL_Delay(250);
				entered[count] = '8';
				count++;
				fillRect(200, 230,75,75, ILI9488_RED);
				drawCharTest(230, 250, '8', ILI9488_WHITE,ILI9488_RED, 3);
			}



			/*9th box:
			 * 299, 242
			 * 381, 242
			 * 299, 309
			 * 372, 309
			 */
			if(touchX >= 299 && touchX < 372 && touchY >= 242 && touchY < 309){
			   fillRect(300, 230,75,75, ILI9488_GREEN);
			   HAL_Delay(250);
			   entered[count] = '9';
			   fillRect(300, 230,75,75, ILI9488_RED);
			   drawCharTest(319, 250, '9', ILI9488_WHITE,ILI9488_RED, 3);
			   count++;
			}

	  }

}


void DispenseScreen(){
	char success_msg [10] = "Dispensing...";
	fillScreen(ILI9488_WHITE);
	ILI9488_printText(success_msg, 10, 10, ILI9488_BLACK, ILI9488_WHITE, 1);

	return;
}

void scan_pill_screen(){
	char Place [50] = "Place Pill in Scanner";
	char count [50];
	uint16_t touchX = 0, touchY = 0;
	touchX = getX();
	touchY = getY();
	uint8_t i = 5;
	while (i != 0){
			fillScreen(ILI9488_WHITE);
			sprintf(count, "Scanning pill in %i seconds", i);
			LCD_Font(10, 30, Place, _Open_Sans_Bold_36, 1, ILI9488_WHITE);
			LCD_Font(10, 80, count, _Open_Sans_Bold_36, 1, ILI9488_BLACK);
			HAL_Delay(1000);
			i--;
	}



	uint8_t result = Scan();

	char result_word[25] = "dummy";

	if (result == 0){
		strcpy(result_word, "nothing");
	}
	else if (result == 1){
		strcpy(result_word, "Red Skittle");
	}
	else if (result == 2){
		strcpy(result_word, "Yellow Skittle");
	}
	else if (result == 3){
		strcpy(result_word, "Green Skittle");
	}
	else if (result == 4){
		strcpy(result_word, "Hot Tamale");
	}

	fillScreen(ILI9488_WHITE);
	LCD_Font(100, 100,  result_word,_Open_Sans_Bold_20, 1, ILI9488_BLACK);

	char back[] = "Back";

	fillRect(100, 250, 150, 75, ILI9488_RED);
	LCD_Font(180, 300, back,_Open_Sans_Bold_20, 1, ILI9488_BLACK);
	while(1){
		touchX = getX();
		touchY = getY();
	if (touchX >= 100 && touchX < 300 && touchY >= 250 && touchY < 325) {
		fillRect(100, 250, 150, 75, ILI9488_GREEN);

			return;
		}
	}


}

void testTouch(){
	fillScreen(ILI9488_WHITE);
	uint16_t touchX = 0, touchY = 0;
	touchX = getX();
	touchY = getY();
	char weee[50];
	sprintf(weee, "X = %i, Y = %i", touchX, touchY);
	ILI9488_printText(weee, 10,10,ILI9488_BLACK, ILI9488_WHITE, 1);

}


void LockScreen(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	const char *DAYS_OF_WEEK[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	const char *MONTHS_OF_YEAR[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


	uint8_t last_min = DS1307_GetMinute();
	char unlockButton[] = "Keypad";
	char fingerPrint[] = "Fingerprint";

	fillScreen(ILI9488_WHITE);;

	fillRect(40, 240, 170, 50, ILI9488_RED);
	LCD_Font(50, 280, unlockButton, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

	fillRect(230, 240, 170, 50, ILI9488_RED);
	LCD_Font(230, 280, fingerPrint, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

	while (1) {

	touchX = getX();
	touchY = getY();

	uint8_t date = DS1307_GetDate();
	uint8_t month = DS1307_GetMonth();
	uint16_t year = DS1307_GetYear();
	uint8_t dow = DS1307_GetDayOfWeek();
	uint8_t hour = DS1307_GetHour();
	uint8_t minute = DS1307_GetMinute();
	//uint8_t second = DS1307_GetSecond();

	char buffer[100] = { 0 };
	char ampm[4] = "AM";
	char formattedMinute[4];
	if (minute < 10){
		sprintf(formattedMinute, "0%i", minute);
	}
	else{
		sprintf(formattedMinute, "%i", minute);
	}
 	//convert to 12hr time
	if (hour == 0){
		hour = 12;
	}
	else if (hour > 12){
		hour = hour - 12;
		sprintf(ampm, "%s", "PM");
	}

	if (minute != last_min){
		fillScreen(ILI9488_WHITE);

		fillRect(40, 240, 170, 50, ILI9488_RED);
		LCD_Font(50, 280, unlockButton, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(230, 240, 170, 50, ILI9488_RED);
		LCD_Font(230, 280, fingerPrint, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
	}

	/* May show warning below. Ignore and proceed. */
	sprintf(buffer, "%i:%s %s", hour, formattedMinute, ampm);
	LCD_Font(10, 30, buffer, _Open_Sans_Bold_36, 1, ILI9488_BLACK);
	sprintf(buffer, "%s, %s %i %i", DAYS_OF_WEEK[dow], MONTHS_OF_YEAR[month - 1], date, year);
	//ILI9488_printText(buffer, 10, 10, ILI9488_BLACK, ILI9488_WHITE, 1);
	LCD_Font(10, 55, buffer, _Open_Sans_Bold_24, 1, ILI9488_BLACK);

	HAL_Delay(50);


	update_last_due_pill_idx(DS1307_GetDayOfWeek(), DS1307_GetHour(), DS1307_GetMinute());

	 uint8_t pil = 0;
	 uint8_t listSize = (getNumPills() <= 3) ? getNumPills() : 3;
	 for (pil = 0; pil < listSize; pil++){

		 //12 hour time for every pill
		 pillEntry temp = getPillInfo(pil);
		 uint8_t tempHour = temp.hour;
		 char tempampm[4] = "AM";
		 char pillTime [50];
		 char pillFormatMinute [5] = " ";


		 if (temp.min < 10){
				sprintf(pillFormatMinute, "0%i", temp.min);
			}

		 else{
				sprintf(pillFormatMinute, "%i", temp.min);
			}
		 if (tempHour == 0){
			tempHour = 12;
		 }
		 else if (tempHour > 12){
			tempHour = tempHour - 12;
			sprintf(tempampm, "%s", "PM");
		 }

		sprintf(pillTime, "%s due at %s, %s %i @ %i:%s %s",temp.name,  DAYS_OF_WEEK[temp.dayofWeek], MONTHS_OF_YEAR[month - 1], date + (temp.dayofWeek - dow),tempHour,  pillFormatMinute, tempampm);
		//overdue pills.
		uint8_t overdue_idx = get_next_pill_idx();
		if (pil < overdue_idx){
			LCD_Font(10, (pil + 1)*70 + 10, pillTime, _Open_Sans_Bold_16, 1, ILI9488_RED);
		}
		else {
			LCD_Font(10, (pil + 1) *70 + 10, pillTime,  _Open_Sans_Bold_16, 1, ILI9488_BLACK);
		}

		//LCD_Font(temp.name, 10, (pil + 1) * 80, ILI9488_BLACK, ILI9488_WHITE, 1);


		if (touchX >= 50 && touchX < 200 && touchY >= 250 && touchY < 300) {

			fillRect(40, 240, 170, 50, ILI9488_GREEN);
			authenticate();
			return;
			HAL_Delay(100);
			
		}

		if (touchX >= 200 && touchX < 400 && touchY >= 250 && touchY < 300) {
			fillRect(230, 240, 170, 50, ILI9488_GREEN);
			uint8_t rx_buffer[1], temp;
			temp = fingerprintScanPrint();
				//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
				if (temp == 9){
					if (FingerprintScan()){
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
						Home_Screen();
						return;
					}
					else
					{
						return;
					}
			}
	 }

	 last_min = minute;

	 }
}
}

void Home_Screen() {

	char refill[] = "Refill";
	char scan[] = "Scan";
	char dispense[] = "Dispense";
	char new_pill[] = "New Pill";
	char fingerprint[] = "Fingerprints";
	char back[] = "Back";
	char option;
	uint8_t redraw = 1;
	fillScreen(ILI9488_WHITE);


	while (1){

	if (redraw){
		fillScreen(ILI9488_WHITE);
		fillRect(70, 40, 150, 75, ILI9488_RED);
		LCD_Font(120, 80, refill, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(250, 40, 150, 75, ILI9488_RED);
		LCD_Font(300, 80, scan, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(70, 125, 150, 75, ILI9488_RED);
		LCD_Font(120, 165, back, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(250, 125, 150, 75, ILI9488_RED);
		LCD_Font(280, 165, dispense, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(70, 210, 150, 75, ILI9488_RED);
		LCD_Font(100, 250, new_pill, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(250, 210, 150, 75, ILI9488_RED);
		LCD_Font(260, 250, fingerprint, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
		redraw=0;
	}
	touchX = getX();
	touchY = getY();

	char touch[20];


	sprintf(touch, "                ");
	LCD_Font(10, 10, touch, _Open_Sans_Bold_16, 1, ILI9488_BLACK);

	sprintf(touch, "x = %i, y = %i", touchX, touchY);
	LCD_Font(10, 10, touch, _Open_Sans_Bold_16, 1, ILI9488_BLACK);

	// Touch function for Refill
	if (touchX >= 70 && touchX < 220 && touchY >= 40 && touchY < 115) {
		fillRect(70, 40, 150, 75, ILI9488_GREEN);
		option = 'r';
		lid_open_screen();
		redraw = 1;

		// Insert Function for refill - this literally just opens the lid
	}

	// Touch function for Scan
	else if (touchX >= 250 && touchX < 400 && touchY >= 40 && touchY < 115) {
		fillRect(250, 40, 150, 75, ILI9488_GREEN);
		option = 's';
		scan_pill_screen();
		redraw = 1;

		// Insert function for Pixycam stuff
	}


	// Touch function for Dispense
	else if (touchX >= 215 && touchX < 418 && touchY >= 125 && touchY < 200) {
		fillRect(250, 125, 150, 75, ILI9488_GREEN);
		Dispense_Auto_Manual();
		option = 'd';
		redraw = 1;

	}

	//BACK
	else if (touchX >= 6 && touchX < 226 && touchY >= 125 && touchY < 200) {
		fillRect(70, 125, 150, 75, ILI9488_GREEN);
		return;
		option = 'd';
		redraw = 1;
	
	}

	// Touch function for New Pill
	else if (touchX >= 70 && touchX < 220 && touchY >= 210 && touchY < 285) {
		//
		fillRect(70, 210, 150, 75, ILI9488_GREEN);
		dispenserChoose(2);
		option = 'n';
		redraw = 1;

	}

	// Touch function for Fingerprints
	else if (touchX >= 250 && touchX < 400 && touchY >= 210 && touchY < 285) {
		fillRect(250, 210, 150, 75, ILI9488_GREEN);
		FingerPrint_Manager();
		HAL_Delay(1000);
		option = 'f';
		redraw = 1;
	}
	}

}

void Dispense_Auto_Manual() {

	fillScreen(ILI9488_WHITE);



	char manual[] = "Manual";
	char automatic[] = "Automatic";
	char back[] = "Back";

	fillRect(50, 50, 150, 150, ILI9488_RED);
	LCD_Font(80, 140, manual, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

	fillRect(250, 50, 150, 150, ILI9488_RED);
	LCD_Font(270, 140, automatic, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

	fillRect(50, 250, 350, 50, ILI9488_RED);
	LCD_Font(200, 280, back, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

	while (1){

		touchX = getX();
		touchY = getY();


	if (touchX >= 50 && touchX < 200 && touchY >= 50 && touchY < 200) {
		fillRect(50, 50, 150, 150, ILI9488_GREEN);
		dispenserChoose(1);
		return;
	}




	if (touchX >= 250 && touchX < 400 && touchY >= 50 && touchY < 200) {
		fillRect(250, 50, 150, 150, ILI9488_GREEN);
		DispenseScreen();
		automaticDispense();
		return;
	}



	if (touchX >= 50 && touchX < 400 && touchY >= 250 && touchY < 300) {
		fillRect(50, 250, 350, 50, ILI9488_GREEN);
		return;
	}
	}

}

//0 - Delete, 1 - manual dispense, 2 - loadNewPill.
void dispenserChoose(uint8_t mode) {
	char one[] = "1";
	char two[] = "2";
	char three[] = "3";
	char back[] = "Back";

	uint8_t dispOneEnabled;
	uint8_t dispTwoEnabled;
	uint8_t dispThreeEnabled;
	fillScreen(ILI9488_WHITE);

	if (mode == 1 || mode == 0){
		 dispOneEnabled = !dispenserAvailable(0);
		 dispTwoEnabled = !dispenserAvailable(1);
		 dispThreeEnabled = !dispenserAvailable(2);

	}

	else{
		 dispOneEnabled = dispenserAvailable(0);
		 dispTwoEnabled = dispenserAvailable(1);
		 dispThreeEnabled = dispenserAvailable(2);
	}

		uint16_t dispOneColor = dispOneEnabled ? ILI9488_RED : ILI9488_DARKGREY;
		uint16_t dispTwoColor = dispTwoEnabled ? ILI9488_RED : ILI9488_DARKGREY;
		uint16_t dispThreeColor = dispThreeEnabled ? ILI9488_RED : ILI9488_DARKGREY;

		fillRect(50, 50, 100, 150, dispOneColor);
		LCD_Font(90, 150, one, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(200, 50, 100, 150, dispTwoColor);
		LCD_Font(240, 150, two, _Open_Sans_Bold_20, 1, ILI9488_WHITE);


		fillRect(350, 50, 100, 150, dispThreeColor);
		LCD_Font(390, 150, three, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

		fillRect(70, 250, 350, 50, ILI9488_RED);
		LCD_Font(220, 280, back, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
		// 1 for Delete, 0 for Manual

	uint8_t choice = 0;
	while (1){
	touchX = getX();
	touchY = getY();




	if (dispOneEnabled && touchX >= 50 && touchX < 150 && touchY >= 50 && touchY < 200) {
		fillRect(50, 50, 100, 150, ILI9488_GREEN);
		choice = 1;
		break;
		//return;
	}



	if (dispTwoEnabled && touchX >= 200 && touchX < 300 && touchY >= 50 && touchY < 200) {
		fillRect(200, 50, 100, 150, ILI9488_GREEN);
		choice = 2;
		break;
		//return;
	}


	if (dispThreeEnabled && touchX >= 350 && touchX < 450 && touchY >= 50 && touchY < 200) {
		fillRect(350, 50, 100, 150, ILI9488_GREEN);
		choice = 3;
		break;
	}



	if (touchX >= 70 && touchX < 400 && touchY >= 250 && touchY < 300) {
		fillRect(70, 250, 350, 50, ILI9488_GREEN);
		choice = 4;
		break;
	}


	}

	//go back home.
	if (choice == 4) {
		return;
	}

	switch (mode){
	case 0: //delete
		deleteDispenser(choice - 1);
		break;
	case 1: //manual dispense
		//insert manual dispense function here
		switch(choice - 1){
		case 0:
			DispenseScreen();
			Dispense1();
			break;
		case 1:
			DispenseScreen();
			Dispense2();
			break;
		case 2:
			DispenseScreen();
			Dispense3();
			break;
		}
		break;
	case 2:
		New_Pill_Screen(choice -  1);
		break;

	}


}



void lid_open_screen(){
	char unlockButton[] = "Re-Lock";

	char lockingMsg[] = "Re-locking lid";

	fillScreen(ILI9488_WHITE);
	fillRect(50, 250, 350, 50, ILI9488_RED);
	LCD_Font(200, 280, unlockButton, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
	unlock();
	while(1){
		touchX = getX();
		touchY = getY();
	if (touchX >= 50 && touchX < 400 && touchY >= 250 && touchY < 300) {
		fillRect(50, 250, 350, 50, ILI9488_GREEN);
		LCD_Font(10, 50, lockingMsg, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		lock();
		return;
	}
	}
}

void FingerPrint_Manager() {

	fillScreen(ILI9488_WHITE);

	uint16_t touchX = 0, touchY = 0;


	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	 //the keys:

	fillRect(125, 30, 250, 75, ILI9488_RED);
	char addFing[] = "Add Fingerprint";


	LCD_Font(165, 70, addFing, _Open_Sans_Bold_20, 1, ILI9488_WHITE);

	fillRect(125, 130, 250, 75, ILI9488_RED);
	char scanFing[] = "Scan Fingerprint";


	LCD_Font(165, 170, scanFing, _Open_Sans_Bold_20, 1, ILI9488_WHITE);


	fillRect(125, 230, 250, 75, ILI9488_RED);
	char delFing[] = "Delete Fingerprint";


	LCD_Font(165, 270, delFing, _Open_Sans_Bold_20, 1, ILI9488_WHITE);





	//fillRect(125, 75,250,75, ILI9488_RED);
	   //char addFing[] = "Add Fingerprint";


	//LCD_Font(165, 115, addFing, _Open_Sans_Bold_20, 1, ILI9488_BLACK);


	while (1)
	{
		//ILI9488_printTextTest(greetings, 25, 25, ILI9488_BLACK, ILI9488_RED, 3);



		char buf[20];
		char buf1[20];
		//char buf2[20];
		//char buf3[20];

			//ILI9488_printTextTest(buf1, 250 , 25, ILI9488_BLACK, ILI9488_WHITE, 2);
		   //ILI9488_printText(buf3, 150, 25, ILI9488_WHITE, ILI9488_WHITE, 1);
		LCD_Font(25, 25, buf1, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		touchX = getX();
		touchY = getY();
		sprintf(buf, "x=%3d y=%3d", touchX, touchY);
		sprintf(buf1, "x=%3d y=%3d", touchX, touchY);
		//sprintf(buf2,"count=%3d entered=%3d",count,entered[count]);
		//sprintf(buf3,"count=%3d entered=%3d",count,entered[count]);

		//ILI9488_printTextTest(buf1, 250, 25, ILI9488_BLACK,  ILI9488_WHITE, 2);
		//ILI9488_printText(buf3, 150, 25, ILI9488_BLACK, ILI9488_BLACK, 1);
		LCD_Font(25, 25, buf1, _Open_Sans_Bold_20, 1, ILI9488_BLACK);



		//add finger print box.
		/*
		 79, 55
		  79, 67
		  390, 67
		  390, 165
		 */


		if (touchX >= 79 && touchX < 390 && touchY >= 55 && touchY < 165) {
			fillRect(125, 30, 250, 75, ILI9488_GREEN);
			HAL_Delay(300);
			fillRect(125, 30, 250, 75, ILI9488_RED);
			LCD_Font(165, 70, addFing, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
			uint8_t rx_buffer[1], temp;
			temp = fingerprintAddPrint();
				//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
				if (temp == 1){
					newFingerprintScreen();
				}
			return;
		}


		/*
		 * scan finger print box:
		  79, 169
		  79, 233
		  377, 172
		  377, 207
		 */
		if (touchX >= 79 && touchX < 377 && touchY >= 169 && touchY < 233) {
			fillRect(125, 130, 250, 75, ILI9488_GREEN);
			HAL_Delay(300);
			fillRect(125, 130, 250, 75, ILI9488_RED);
			LCD_Font(165, 170, scanFing, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
			uint8_t rx_buffer[1], temp;
			temp = fingerprintScanPrint();
				//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
				if (temp == 9){
					FingerprintScan();
				}
			return;
		}

		/*Delete Finger Print:
		  79, 248
		  377, 254
		  97, 305
		  372, 312*/
		if (touchX >= 79 && touchX < 377 && touchY >= 248 && touchY < 312) {
			fillRect(125, 230, 250, 75, ILI9488_GREEN);
			HAL_Delay(300);
			fillRect(125, 230, 250, 75, ILI9488_RED);
			LCD_Font(165, 270, delFing, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
			uint8_t rx_buffer[1], temp;
			temp = fingerprintRemovePrint();
				//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
				if (temp == 14){
					FingerprintDelete();
				}
			return;

		}


}
}


void newFingerprintScreen(){
	fillScreen(ILI9488_WHITE);
	char place [] = "Place Finger on Scanner";
	LCD_Font(100, 100, place, _Open_Sans_Bold_20, 1, ILI9488_BLACK);

	uint8_t rx_buffer[1];

	//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
	uint8_t temp = fingerprint_UART_read();
	while(1){
		temp = fingerprint_UART_read();
	if (temp == 4){// Succeed for Case 1: Registering fingerprint
		//Works
		fillScreen(ILI9488_WHITE);
		char samp_suc [] = "Sampling Succeeds";
		LCD_Font(100, 100, samp_suc, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
		HAL_Delay(1000);
		if (fingerprint_UART_read() == 6){
			fillScreen(ILI9488_WHITE);
			char release [] = "Release Finger";
			LCD_Font(100, 100, release, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
			if (fingerprint_UART_read() == 3){newFingerprintScreen();}
			return;
		}

	}
	else if (temp == 5){ //Fail for case 1: Registering fingerprint
		//Fails
		fillScreen(ILI9488_WHITE);
		char fail [] = "Sampling Failed";
		LCD_Font(100, 100, fail, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		FingerPrint_Manager();
		return;
	}
	else if (temp == 7){ // Success for case 1: Successful Saving
		//Saving succeeded
		fillScreen(ILI9488_WHITE);
		char save_suc [] = "Saving Succeeded";
		LCD_Font(100, 100, save_suc, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		HAL_Delay(2000);
		return;
	}
	else if (temp == 8){ // Fail for case 1: Failed Saving
		//Saving failed
		fillScreen(ILI9488_WHITE);
		char save_fail [] = "Saving Failed";
		LCD_Font(100, 100, save_fail, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		HAL_Delay(2000);
		return;
	}
	}
	//return;
}

uint8_t FingerprintScan(){

	fillScreen(ILI9488_WHITE);
	char place [] = "Place Finger on Scanner";
	LCD_Font(100, 100, place, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
	uint8_t rx_buffer[1], temp;

	while(1){
		temp = fingerprint_UART_read();
	//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
	if (temp == 10){ // Succeeds in capture: Send to release finger
		fillScreen(ILI9488_WHITE);
		char release [] = "Release Finger";
		LCD_Font(100, 100, release, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
		HAL_Delay(1000);
		uint8_t temp = fingerprint_UART_read();
		if (temp == 11){// Matching Scan
			fillScreen(ILI9488_WHITE);
			char scan_suc [] = "Scan has been matched";
			LCD_Font(100, 100, scan_suc, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			HAL_Delay(2000);
			return 1;
		}
		else if (temp == 12){//Matching failed
			fillScreen(ILI9488_WHITE);
			char scan_fail [] = "Scan has no match";
			LCD_Font(100, 100, scan_fail, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			HAL_Delay(2000);
			return 0;
		}
	}
	}

}

void FingerprintDelete(){

		fillScreen(ILI9488_WHITE);
		char place [] = "Place Finger on Scanner";
		LCD_Font(100, 100, place, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		uint8_t rx_buffer[1], temp;
		while(1){
		temp = fingerprint_UART_read();
		//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
		if (temp == 15){ // Succeeds in capture: Send to release finger
			fillScreen(ILI9488_WHITE);
			char del_succ [] = "Delete Successful";
			LCD_Font(100, 100, del_succ, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
			HAL_Delay(1000);
		}else if (temp == 16){
			fillScreen(ILI9488_WHITE);
			char unreg [] = "Fingerprint Unregistered";
			LCD_Font(100, 100, unreg, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
			HAL_Delay(1000);
		}else if (temp == 17){
			fillScreen(ILI9488_WHITE);
			char cap_fail [] = "Capturing Failed";
			LCD_Font(100, 100, cap_fail, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
			temp = fingerprint_UART_read();
			HAL_Delay(1000);
			return;
		}
		//HAL_UART_Receive(arduino_uart, rx_buffer, 1, HAL_MAX_DELAY);
		//temp = fingerprint_UART_read();
		if(temp == 18){
			fillScreen(ILI9488_WHITE);
			char release [] = "Release Finger";
			LCD_Font(100, 100, release, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			HAL_Delay(1000);
			return;
		}
		}
}

void New_Pill_Screen(uint8_t dispNum) {

	fillScreen(ILI9488_WHITE);

	char red_skittle[] = "Red Skittle";
	char yellow_skittle[] = "Yellow Skittle";
	char green_skittle[] = "Green Skittle";
	char hot_tamale[] = "Hot Tamale";
	char home[] = "  Back";
	char option;


	fillRect(70, 40, 150, 75, ILI9488_RED);
	LCD_Font(100, 80, red_skittle, _Open_Sans_Bold_16, 1, ILI9488_WHITE);
	fillRect(250, 40, 150, 75, ILI9488_RED);
	LCD_Font(260, 80, yellow_skittle, _Open_Sans_Bold_16, 1, ILI9488_WHITE);

	fillRect(160, 125, 150, 75, ILI9488_RED);
	LCD_Font(190, 165, home, _Open_Sans_Bold_20, 1, ILI9488_WHITE);


	fillRect(70, 210, 150, 75, ILI9488_RED);
	LCD_Font(80, 250, green_skittle, _Open_Sans_Bold_16, 1, ILI9488_WHITE);
	fillRect(250, 210, 150, 75, ILI9488_RED);
	LCD_Font(280, 250, hot_tamale, _Open_Sans_Bold_16, 1, ILI9488_WHITE);


	while (1){

		touchX = getX();
		touchY = getY();


	if (touchX >= 70 && touchX < 220 && touchY >= 40 && touchY < 115) {
		fillRect(70, 40, 150, 75, ILI9488_GREEN);
		option = 'r';
		break;
	}

	if (touchX >= 250 && touchX < 400 && touchY >= 40 && touchY < 115) {
		fillRect(250, 40, 150, 75, ILI9488_GREEN);

		option = 'y';
		break;
	}

	// Home
	else if (touchX >= 160 && touchX < 310 && touchY >= 125 && touchY < 200) {
		fillRect(160, 125, 150, 75, ILI9488_GREEN);
		return;
	}


	if (touchX >= 70 && touchX < 220 && touchY >= 210 && touchY < 285) {
		fillRect(70, 210, 150, 75, ILI9488_GREEN);
		option = 'g';
		break;
	}

	if (touchX >= 250 && touchX < 400 && touchY >= 210 && touchY < 285) {
		fillRect(250, 210, 150, 75, ILI9488_GREEN);
		option = 'h';
		break;
	}
	}
	weekdaySelector(dispNum, option);


}

void weekdaySelector(char dispNum, char pillOption){
	fillScreen(ILI9488_WHITE);

	   uint16_t touchX = 0, touchY = 0;


	   uint8_t Sunday = 0;
	   uint8_t Monday = 0;
	   uint8_t Tuesday = 0;
	   uint8_t Wednesday = 0;
	   uint8_t Thursday = 0;
	   uint8_t Friday = 0;
	   uint8_t Saturday = 0;




	   char addSunday[] = "SUN";
	   char addMonday[] = "MON";
	   char addTuesday[] = "TUE";
	   char addWednesday[] = "WED";
	   char addThursday[] = "THU";
	   char addFriday[] = "FRI";
	   char addSaturday[] = "SAT";
	   char addNext[] = "Next";

	   //Sunday
	   fillRect(65, 30,75,75, ILI9488_RED);


	   //Monday
	   fillRect(150, 30,75,75, ILI9488_RED);

	   //Tuesday
	   fillRect(235, 30,75,75, ILI9488_RED);

	   //Wednesday
	   fillRect(320, 30,75,75, ILI9488_RED);


	   //char addSunday[] = "S";

	   //Thursday
	   fillRect(105, 120,75,75, ILI9488_RED);


	   //Friday
	   fillRect(190, 120,75,75, ILI9488_RED);


	   //Saturday
	   fillRect(275, 120,75,75, ILI9488_RED);


	   //Next button
	   fillRect(50, 250, 350, 50, ILI9488_RED);


	   LCD_Font(85, 70, addSunday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
	   LCD_Font(160, 70, addMonday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
	   LCD_Font(255, 70, addTuesday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
	   LCD_Font(335, 70, addWednesday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
	   LCD_Font(125, 160, addThursday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
	   LCD_Font(210, 160, addFriday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
	   LCD_Font(295, 160, addSaturday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);

	   LCD_Font(200, 285, addNext, _Open_Sans_Bold_20, 1, ILI9488_BLACK);


	  while (1)
	  {

		  char buf[20];
		  char buf1[20];

		  	  LCD_Font(25, 25, buf1, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
		  	  touchX = getX();
		  	  touchY = getY();
		  	  sprintf(buf,"x=%3d y=%3d",touchX,touchY);
		  	  sprintf(buf1,"x=%3d y=%3d",touchX,touchY);

		  	  LCD_Font(25, 25, buf1, _Open_Sans_Bold_20, 1, ILI9488_BLACK);



		  	  if(touchX >= 6 && touchX < 88 && touchY >= 55 && touchY < 161){
		  		  if(Sunday == 0){
		  			  fillRect(65, 30,75,75, ILI9488_GREEN);
		  			  LCD_Font(85, 70, addSunday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		  			  Sunday = 1;
		  			  HAL_Delay(300);
		  		  }
		  		  else{
		  			  Sunday = 0;
		  			  fillRect(65, 30,75,75, ILI9488_RED);
		  			  LCD_Font(85, 70, addSunday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		  			  HAL_Delay(300);

		  		  }
		  	  }

		  	if(touchX >= 88 && touchX < 221 && touchY >= 55 && touchY < 161){
		  		  		  if(Monday == 0){
		  		  			  fillRect(150, 30,75,75, ILI9488_GREEN);
		  		  			  LCD_Font(160, 70, addMonday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		  		  			  Monday = 1;
		  		  			  HAL_Delay(300);
		  		  		  }
		  		  		  else{
		  		  			  Monday = 0;
		  		  			  fillRect(150, 30,75,75, ILI9488_RED);
		  		  			  LCD_Font(160, 70, addMonday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
		  		  			  HAL_Delay(300);

		  		  		  }
		  		  	  }


			if(touchX >= 245 && touchX < 299 && touchY >= 55 && touchY < 161){
			  		  		  if(Tuesday == 0){
			  		  			  fillRect(235, 30,75,75, ILI9488_GREEN);
			  		  			  LCD_Font(255, 70, addTuesday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			  		  			  Tuesday = 1;
			  		  			  HAL_Delay(300);
			  		  		  }
			  		  		  else{
			  		  			  Tuesday = 0;
			  		  			  fillRect(235, 30,75,75, ILI9488_RED);
			  		  			  LCD_Font(255, 70, addTuesday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
			  		  			  HAL_Delay(300);

			  		  		  }
			  		  	  }


			if(touchX >= 308 && touchX < 390 && touchY >= 67 && touchY < 161){
					  		  		  if(Wednesday == 0){
					  		  			  fillRect(320, 30,75,75, ILI9488_GREEN);
					  		  			  LCD_Font(335, 70, addWednesday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
					  		  			  Wednesday = 1;
					  		  			  HAL_Delay(300);
					  		  		  }
					  		  		  else{
					  		  			  Wednesday = 0;
					  		  			  fillRect(320, 30,75,75, ILI9488_RED);
					  		  			  LCD_Font(335, 70, addWednesday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
					  		  			  HAL_Delay(300);

					  		  		  }
					  		  	  }


			if(touchX >= 75 && touchX < 97 && touchY >= 165 && touchY < 207){
							  		  		  if(Thursday == 0){
							  		  			  fillRect(105, 120,75,75, ILI9488_GREEN);
							  		  			  LCD_Font(125, 160, addThursday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
							  		  			  Thursday = 1;
							  		  			  HAL_Delay(300);
							  		  		  }
							  		  		  else{
							  		  			  Thursday = 0;
							  		  			  fillRect(105, 120,75,75, ILI9488_RED);
							  		  			  LCD_Font(125, 160, addThursday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
							  		  			  HAL_Delay(300);

							  		  		  }
							  		  	  }



			if(touchX >= 184 && touchX < 258 && touchY >= 165 && touchY < 207){
									  		  		  if(Friday == 0){
									  		  			  fillRect(190, 120,75,75, ILI9488_GREEN);
									  		  			  LCD_Font(210, 160, addFriday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
									  		  			  Friday = 1;
									  		  			  HAL_Delay(300);
									  		  		  }
									  		  		  else{
									  		  			  Friday = 0;
									  		  			  fillRect(190, 120,75,75, ILI9488_RED);
									  		  			  LCD_Font(210, 160, addFriday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
									  		  			  HAL_Delay(300);

									  		  		  }
									  		  	  }



				 if(touchX >= 262 && touchX < 335 && touchY >= 165 && touchY < 207){
				  if(Saturday == 0){
					  fillRect(275, 120,75,75, ILI9488_GREEN);
					  LCD_Font(295, 160, addSaturday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
					  Saturday = 1;
					  HAL_Delay(300);
				  }
				  else{
					  Saturday = 0;
					  fillRect(275, 120,75,75, ILI9488_RED);
					  LCD_Font(295, 160, addSaturday, _Open_Sans_Bold_20, 1, ILI9488_BLACK);
					  HAL_Delay(300);

				  }
			  }


				 if(touchX >= 6 && touchX < 392 && touchY >= 265 && touchY < 306){
					 	 	fillRect(50, 250, 350, 50, ILI9488_GREEN);
					  		HAL_Delay(300);
					  		fillRect(50, 250, 350, 50, ILI9488_RED);
					  		LCD_Font(200, 285, addNext, _Open_Sans_Bold_20, 1, ILI9488_BLACK);

					  		uint8_t days [7] = {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
					  		timeSet(dispNum, pillOption, days);
					  		return;

				}


	  }


}

void timeSet(uint8_t dispNum, uint8_t pillOption, uint8_t * daysOfWeek){
	   fillScreen(ILI9488_WHITE);
	   uint16_t touchX = 0, touchY = 0;

	   //the keys:

	   uint16_t Hour = 12;
	   uint16_t Minute = 0;
	   uint8_t PM = 0;





	   char hourPrint[20];
	   char minPrint[20];

	   //convert int to string
	   sprintf(hourPrint, "%d", Hour);
	   sprintf(minPrint, "%d", Minute);


	   strcat(minPrint, "0");



	   char  downwardArrow[] = "<";
	   char upwardArrow[] = ">";

	   char colon[] = ":";
	   char am[] = "AM";
	   char pm[] = "PM";
	   char addNext[] = "Next";
	   char addAnother[] = "Another Time";

	   //minute down arrow
	   fillRect(275, 185,50,50, ILI9488_RED);


	   //minute up arrow
	   fillRect(275, 25,50,50, ILI9488_RED);


	   //hour down arrow
	   fillRect(75, 185,50,50, ILI9488_RED);


	     //hour up arrow
	   fillRect(75, 25,50,50, ILI9488_RED);

	   //am arrow
	   fillRect(382, 50,85,65, ILI9488_GREEN);

	   //PM arrow
	   fillRect(382, 135,85,65, ILI9488_RED);


	   //Next button.
	   fillRect(340, 250,105,55, ILI9488_RED);

	   //Add another button.
	   fillRect(15, 250,295,55, ILI9488_RED);



	   LCD_Font(45, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);
	   LCD_Font(250, 165, minPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);
	   LCD_Font(195, 165, colon, _Open_Sans_Bold_96, 1, ILI9488_BLACK);
	   LCD_Font(385, 100, am, _Open_Sans_Bold_48, 1, ILI9488_BLACK);
	   LCD_Font(385, 180, pm, _Open_Sans_Bold_48, 1, ILI9488_BLACK);


	   //next and another time
	   LCD_Font(350, 295, addNext, _Open_Sans_Bold_36, 1, ILI9488_BLACK);
	   LCD_Font(25, 295, addAnother, _Open_Sans_Bold_36, 1, ILI9488_BLACK);

	   	   setRotation(2);
		  LCD_Font(35, 200, downwardArrow, _Open_Sans_Bold_48, 1, ILI9488_BLACK);
		  LCD_Font(200, 200, upwardArrow, _Open_Sans_Bold_48, 1, ILI9488_BLACK);

		  LCD_Font(35, 400, downwardArrow, _Open_Sans_Bold_48, 1, ILI9488_BLACK);
		  LCD_Font(200, 400, upwardArrow, _Open_Sans_Bold_48, 1, ILI9488_BLACK);
		  setRotation(1);

	  while (1)
	  {



		  char buf[20];
		  char buf1[20];

		  	  LCD_Font(25, 25, buf1, _Open_Sans_Bold_20, 1, ILI9488_WHITE);
		  	  touchX = getX();
		  	  touchY = getY();
		  	  sprintf(buf,"x=%3d y=%3d",touchX,touchY);
		  	  sprintf(buf1,"x=%3d y=%3d",touchX,touchY);

		  	  LCD_Font(25, 25, buf1, _Open_Sans_Bold_20, 1, ILI9488_BLACK);



		  	  //AM button.
		  	  /*

				390, 67
				464, 67
				390, 169
				464, 172
		  	   */


		  	  if(touchX >= 390 && touchX < 464 && touchY >= 67 && touchY < 172){
		  		  if(PM == 1){

		  			  //make PM 0.
		  			  PM = 0;

		  			  //make AM Green & PM Red

		  			 //am arrow
		  			   fillRect(382, 50,85,65, ILI9488_GREEN);

		  			   //PM arrow
		  			   fillRect(382, 135,85,65, ILI9488_RED);


		  			 LCD_Font(385, 100, am, _Open_Sans_Bold_48, 1, ILI9488_BLACK);
		  			 LCD_Font(385, 180, pm, _Open_Sans_Bold_48, 1, ILI9488_BLACK);

		  			  HAL_Delay(300);
		  		  }

		  	  }




		  	  /*
		  	   * PM button
				390, 172
				464, 192
				393, 207
				464, 207
		  	   */
		  	if(touchX >= 390 && touchX < 464 && touchY >= 172 && touchY < 207){
		  		  		  if(PM == 0){

		  		  			  //make PM 0.
		  		  			  PM = 1;

		  		  			  //make AM RED & PM Green
						   //am arrow
						     fillRect(382, 50,85,65, ILI9488_RED);

						     //PM arrow
						     fillRect(382, 135,85,65, ILI9488_GREEN);


						   LCD_Font(385, 100, am, _Open_Sans_Bold_48, 1, ILI9488_BLACK);
						     LCD_Font(385, 180, pm, _Open_Sans_Bold_48, 1, ILI9488_BLACK);
		  		  			  HAL_Delay(300);
		  		  		  }

		  	}


		  	/*Next Button:

				335, 265
				464, 271
				335, 309
				464, 312
		  		  			  			  		  	  		  	 */
		  				 if(touchX >= 335 && touchX < 464 && touchY >= 265 && touchY < 312){
		  					 	 	fillRect(340, 250,105,55, ILI9488_GREEN);
		  					  		loadNewPillsDisplay(dispNum, pillOption, daysOfWeek, Hour, Minute, PM);
		  					  		return;

		  				 }
			/*Another Time Button:

						1, 265
						308, 265
						1, 312
						299, 306
																		 */
								 if(touchX >= 1 && touchX < 308 && touchY >= 265 && touchY < 312){
									 	 	 fillRect(15, 250,295,55, ILI9488_GREEN);
											HAL_Delay(300);
											loadNewPillsDisplay(dispNum, pillOption, daysOfWeek, Hour, Minute, PM);
											timeSet(dispNum, pillOption, daysOfWeek);
											return;

								 }



		  		/*
		  		 minute top arrow:
					262, 55
					331, 55
					271, 67
					326, 67
						  			  		  	  		  	 */
				 if(touchX >= 262 && touchX < 331 && touchY >= 55 && touchY < 67){
					 	 	fillRect(275, 25,50,50, ILI9488_GREEN);
					  		HAL_Delay(300);
					  		fillRect(275, 25,50,50, ILI9488_RED);


							//print minPrint
					  		LCD_Font(250, 165, minPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
							if(Minute == 0){
								Minute = 30;
							   //copying over minPrint
							   sprintf(minPrint, "%d", Minute);
							}
							else{
								Minute = 0;
							   //copying over minPrint
							   sprintf(minPrint, "%d", Minute);
							   strcat(minPrint, "0");
							}




							//print minPrint
							LCD_Font(250, 165, minPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);

				}



		  		/*minute bottom arrow:
				262, 201
				331, 207
				287, 262
				326, 259*/
		  			 if(touchX >= 262 && touchX < 331 && touchY >= 201 && touchY < 262){
		  				 	 fillRect(275, 185,50,50, ILI9488_GREEN);
					  		HAL_Delay(300);
					  		fillRect(275, 185,50,50, ILI9488_RED);
							//print minPrint
					  		LCD_Font(250, 165, minPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
							if(Minute == 30){
								Minute = 0;
							   //copying over minPrint
							   sprintf(minPrint, "%d", Minute);
							   strcat(minPrint, "0");
							}
							else{
								Minute = 30;
							   //copying over minPrint
							   sprintf(minPrint, "%d", Minute);
							}




							//print minPrint
							LCD_Font(250, 165, minPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);

				}

		  			/*
		  				  		 hour top arrow:
		  							6, 52
									66, 55
									6, 67
									79, 67
		  								  			  		  	  		  	 */
		  						 if(touchX >= 6 && touchX < 79 && touchY >= 52 && touchY < 67){
		  							 	 	 fillRect(75, 25,50,50, ILI9488_GREEN);
		  							  		HAL_Delay(300);
		  							  		fillRect(75, 25,50,50, ILI9488_RED);



		  									//print minPrint

		  									if(Hour == 12){
		  										Hour = 1;
		  										LCD_Font(45, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
		  									}
		  									else if(Hour > 9){
		  										LCD_Font(45, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
		  										Hour++;
		  									}

		  									else{
		  										LCD_Font(75, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
		  										Hour++;
		  									}



		  										sprintf(hourPrint, "%d", Hour);




		  									//print minPrint
		  									if(Hour < 10){
		  										LCD_Font(75, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);
		  									}
		  									else{
		  										LCD_Font(45, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);
		  									}


		  						}

		  						/*
		  							  				  		 hour bottom arrow:
		  							  							75, 201
																79, 201
																75, 262
																79, 262
		  							  								  			  		  	  		  	 */
		  							  						 if(touchX >= 75 && touchX < 79 && touchY >= 201 && touchY < 262){
		  							  							fillRect(75, 185,50,50, ILI9488_GREEN);
		  							  							  		HAL_Delay(300);
		  							  							  	fillRect(75, 185,50,50, ILI9488_RED);



		  							  									//print minPrint

		  							  									if(Hour == 1){
		  							  										Hour = 12;
		  							  										LCD_Font(75, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
		  							  									}
		  							  									else if(Hour > 9){
		  							  										LCD_Font(45, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
		  							  										Hour--;
		  							  									}

		  							  									else{
		  							  										LCD_Font(75, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_WHITE);
		  							  										Hour--;
		  							  									}



		  							  										sprintf(hourPrint, "%d", Hour);




		  							  									//print minPrint
		  							  									if(Hour < 10){
		  							  										LCD_Font(75, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);
		  							  									}
		  							  									else{
		  							  										LCD_Font(45, 165, hourPrint, _Open_Sans_Bold_96, 1, ILI9488_BLACK);
		  							  									}


		  							  						}



	  }

	  }


