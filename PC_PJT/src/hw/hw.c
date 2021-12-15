/*
 * hw.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "hw.h"
#include "ap.h"

void hwInit(void)
{

	bspInit();

	cliInit();

	uartInit();

}
