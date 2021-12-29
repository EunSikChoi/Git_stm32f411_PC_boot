/*
 * ap.h
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */

#ifndef SRC_AP_AP_H_
#define SRC_AP_AP_H_


#include "hw.h"



void apInit(void);
void apMain(int argc, char *argv[]);
void apExit(void);
uint8_t getBootid(void);



#endif /* SRC_AP_AP_H_ */
