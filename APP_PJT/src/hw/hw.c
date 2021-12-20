/*
 * hw.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "hw.h"
#include "ap.h"

extern uint32_t __flash_tag_addr;
extern uint32_t __isr_vector_addr;

extern uint32_t __flash_start;
extern uint32_t __flash_end;
extern uint32_t __flash_length;


__attribute__((section(".tag"))) firm_tag_t firm_tag =
    {
        .magic_number = 0xAAAA5555,

        //-- fw info
        //
        .addr_tag = (uint32_t)&__flash_tag_addr,
        .addr_fw  = (uint32_t)&__isr_vector_addr,
        .size_tag = 1024,

        .tag_flash_start  = (uint32_t)&__flash_start,
        .tag_flash_end    = (uint32_t)&__flash_end,
        .tag_flash_length = (uint32_t)& __flash_length,

        .tag_length    = 1024,
        .tag_flash_crc = 0,

        .tag_date_str = __DATE__,
        .tag_time_str = __TIME__,
        //-- tag info
        //
    };

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
