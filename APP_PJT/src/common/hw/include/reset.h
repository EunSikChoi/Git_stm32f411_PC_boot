/*
 * reset.h
 *
 *  Created on: 2021. 11. 19.
 *      Author: 82109
 */

#ifndef SRC_COMMON_HW_INCLUDE_RESET_H_
#define SRC_COMMON_HW_INCLUDE_RESET_H_



#include "hw_def.h"


#ifdef _USE_HW_RESET


bool resetInit(void);
uint32_t resetGetCount(void);
void resetToBoot(void);

#endif


#endif /* SRC_COMMON_HW_INCLUDE_RESET_H_ */
