#include "Pills.h"

static pillEntry pillList [50];
static uint8_t next_time_pill_idx = 0;
static uint8_t last_taken_pill_idx = 0;

uint8_t used_slots = 0; //stores dispenser availablity through one-hot encoding


void addNewEntry(uint8_t dispenserNum, char * name, uint8_t dayofWeek, uint8_t hour, uint8_t min){
	//uint8_t ID; uint8_t dispenserNum; char * name; uint8_t dayofWeek; uint8_t hour; uint8_t min; uint8_t taken;
	pillEntry wew = {numPills, dispenserNum, name, dayofWeek, hour, min, 1};
	pillList[numPills] = wew;
	numPills++;
	used_slots |= 0x1 << dispenserNum;
	sortEntries();
	//update_next_pill_idx(DS1307_GetDayOfWeek, DS1307_GetHour, DS1307_GetMinute);
}

void sortEntries(){
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t minimum_idx = 0;

	//WOOOO SELECTION SORT MY BELOVED!!!!
	for (i = 0; i < numPills; i++){
		minimum_idx = i;
		for (j = i + 1; j < numPills; j++){
			if (compPillEntry(pillList[j], pillList[minimum_idx])){
				minimum_idx = j;
			}
		}
		pillEntry temp = pillList[i];
		pillList[i] = pillList[minimum_idx];
		pillList[minimum_idx] = temp;
		pillList[i].ID = i;

	}
}

//returns 1 if lhs is less than rhs
uint8_t compPillEntry(pillEntry lhs, pillEntry rhs){

	if (!(lhs.dayofWeek == rhs.dayofWeek)){
		return lhs.dayofWeek < rhs.dayofWeek;
	}

	if (!(lhs.hour == rhs.hour)){
		return lhs.hour < rhs.hour;
	}

	if (!(lhs.min == rhs.min)){
		return lhs.min < rhs.min;
	}

	return 0;
}

uint8_t update_last_due_pill_idx(uint8_t dayofweek, uint8_t hour, uint8_t min){

	uint8_t i = 0;
	//find closest next pill to the current time. Actual search algorithms be damned.
	for (i = 0; i < numPills; i++){
		if (!(dayofweek == pillList[i].dayofWeek)){
			if (dayofweek < pillList[i].dayofWeek){
				next_time_pill_idx = i;
			}

		}

		if (!(hour == pillList[i].hour)){
			if (dayofweek < pillList[i].dayofWeek){
				next_time_pill_idx = i;
			}
		}

		if (!(min == pillList[i].min)){
			if (dayofweek < pillList[i].dayofWeek){
				next_time_pill_idx = i;
			}
		}
	}
	last_taken_pill_idx = (i == 0) ? 0 : i -1;

}

uint8_t get_next_pill_idx(){
	if (numPills == 1){
		return 1;
	}
	else{
	return next_time_pill_idx;
	}
}

uint8_t getNumDuePills(){
	return abs((int16_t)(next_time_pill_idx - last_taken_pill_idx)) % numPills;
}

//call after pills have been dispensed up to current time
uint8_t updatelastTakenPill(){
	update_next_pill_idx(DS1307_GetDayOfWeek, DS1307_GetHour, DS1307_GetMinute);
	//rolling over to the next week.
	if (next_time_pill_idx == 0){
		last_taken_pill_idx = numPills - 1;
	}
	else {
		last_taken_pill_idx = next_time_pill_idx - 1;
	}

}

pillEntry getPillInfo(uint8_t idx){
	return pillList[idx];
}

uint8_t getNumPills(){
	return numPills;
}

uint8_t dispenserAvailable(uint8_t disp){
	return (~used_slots & (0x1 << disp)) >> disp;
}

void deleteDispenser(uint8_t disp){
	used_slots &= ~(0x1 << disp);
	uint8_t i = 0;
	uint8_t newNumPills = 0;

	pillEntry temp [numPills];
	for (i = 0; i < numPills; i++){
		if (pillList[i].dispenserNum != disp){
			pillEntry next =  {pillList[i].ID, pillList[i].dispenserNum, " ", pillList[i].hour, pillList[i].min, pillList[i].taken};
			memcpy(next.name, pillList[i].name, 25);
			temp[newNumPills] = next;
			newNumPills++;
		}
	}


	for (i = 0; i < newNumPills; i++){
		pillList[i] = temp[i];
	}

	sortEntries();
	numPills = newNumPills;
	return;
}


void clearPillList(){
	numPills = 0;
}

void loadNewPillsDisplay(uint8_t dispNum, uint8_t pillOption, uint8_t * daysofWeek, uint8_t hour, uint8_t Minute, uint8_t AMPM){
	uint8_t i = 0;
	char name[25];

	switch (pillOption){
	case 'r':
		memcpy(name, "Red Skittle", 12);
		break;
	case 'y':
		memcpy(name, "Yellow Skittle", 15);
		break;
	case 'g':
		memcpy(name, "Green Skittle", 14);
		break;
	case 'h':
		memcpy(name, "Hot Tamale", 11);
		break;
	}




	for (i = 0; i < 7; i++){
		if (daysofWeek[i]){
			loadNewPillEntry(dispNum, name, i, hour % 12 + (AMPM * 12), Minute);

		}
	}

}
//explicitly ONLY for when we are loading in a pre-sorted list of entries.
void loadNewPillEntry(uint8_t dispenserNum, char * name, uint8_t dayofWeek, uint8_t hour, uint8_t min){
	//uint8_t ID; uint8_t dispenserNum; char * name; uint8_t dayofWeek; uint8_t hour; uint8_t min; uint8_t taken;
	//lmao don't know how to do this a better way but it might work ig
	pillEntry wew = {numPills, dispenserNum, " ", dayofWeek, hour, min, 1};
	memcpy(wew.name, name, 25);
	used_slots |= 0x1 << dispenserNum;
	pillList[numPills] = wew;
	numPills++;
}


void automaticDispense(){
	uint8_t i = last_taken_pill_idx;
	for (; i < next_time_pill_idx; i++){
		switch(pillList[i].dispenserNum){
		case 0:
			Dispense1();
			break;
		case 1:
			Dispense2();
			break;
		case 2:
			Dispense3();
			break;
		}
	}
	last_taken_pill_idx = i - 1;
}

void Dispense1(){


	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(500);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);

	return;
}

void Dispense2(){
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);

	return;
}

void Dispense3(){

	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_RESET);
	return;
}
