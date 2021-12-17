/*
 * hw.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "hw.h"
#include "ap.h"

__attribute__((section(".version"))) firm_version_t firm_ver = // 섹션 version에 firm_ver 변수를 할당선언 의미 //
    {
        "B210422R2",
        "STM32F411"
    };

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

	if (sdInit() == true)
	{
	  fatfsInit();
	}

	spiInit();
  //spiBegin(_DEF_SPI1); // 나중에 w5500이로 이동

 	W5500_hw_Rst();
	W5500_init();

	logBoot(false); // END Boot log //

}
