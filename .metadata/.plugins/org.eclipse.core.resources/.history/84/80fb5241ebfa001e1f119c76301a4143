/*
 * Pills.h
 *
 *  Created on: Apr 14, 2024
 *      Author: zawad
 */

#ifndef INC_PILLS_H_
#define INC_PILLS_H_

#include <stdint.h>

static uint8_t numPills;
typedef struct {
	uint8_t ID;
	uint8_t dispenserNum;
	char * name;
	uint8_t dayofWeek;
	uint8_t hour;
	uint8_t min;
	uint8_t taken;
} pillEntry;

void addNewEntry(uint8_t dispenserNum, char * name, uint8_t dayofWeek, uint8_t hour, uint8_t min);
void sortEntries();
uint8_t compPillEntry(pillEntry lhs, pillEntry rhs);


#endif /* INC_PILLS_H_ */
