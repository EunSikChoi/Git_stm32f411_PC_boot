/*
 * hw.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "hw.h"

void hwInit(void)
{

	bspInit();

	rtcInit();
	resetInit();

	cliInit();
	ledInit();
  logInit();

  logPrintf("[ Firmware Begin... ]\r\n");
  logPrintf("Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
  logPrintf("Booting..Ver  \t\t: %s\r\n", _DEF_FIRMWATRE_VERSION);

	usbInit();

	flashInit();

	uartInit();

	buttonInit();

	gpioInit();


	logBoot(false); // END Boot log //

}
