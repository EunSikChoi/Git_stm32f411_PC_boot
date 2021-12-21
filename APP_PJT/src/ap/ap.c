/*
 * ap.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "ap.h"
#include "spi.h"
#include "loopback.h"
#include "log.h"

const uint8_t spi_ch1 = _DEF_SPI1; // Wiz5500

void cliBoot(cli_args_t *args);

#ifdef _USE_HW_W5500
BYTE    bTxTcpFrameSize;
BYTE    bTxTcpFrameSend;
WORD wSelCmdMode;
WORD wRefModeVoltage, wRefModeVoltage1, wRefModeVoltage2, wRefModeVoltage3, wRefModeVoltage4, wRefModeVoltage5;
WORD wRefModeVoltage6, wRefModeVoltage7, wRefModeVoltage8, wRefModeVoltage9, wRefModeVoltage10;
char UartTx[32] ={0};


#endif

void apInit(void)
{
	uint8_t id = 0;

	 //cliOpen(_DEF_UART1, 57600);
	 uartOpen(_DEF_UART2, 57600);
	 cliOpen(_DEF_UART3, 115200);

	 cliAdd("boot", cliBoot);

}

UART_HandleTypeDef huart2;

uint16_t count;

void apMain(void)
{
  uint32_t pre_time, pre_baud;
  uint32_t led_blink_time = 2000;
  uint8_t loopback_Cnt;
	uint8_t buffer[256]= {0,};

  pre_baud = uartGetBaud(_DEF_UART2);
  pre_time = millis();


	while(1)
	{
		if(millis()-pre_time >= led_blink_time)
		{
			pre_time = millis();
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}


	#ifdef _USE_HW_W5500

		 if( loopback_Cnt++ > 10)
		 {
			 loopback_Cnt = 0;

			 for(uint8_t index = 0; index < 4; index++)
			 {
					loopback_tcps(index ,buffer,502);
			 }
		 }
	#endif

		cliMain();

	}

}

void cliBoot(cli_args_t *args)
{
  bool ret = false;
  uint8_t id;



  if (args->argc == 1 && args->isStr(0, "info") == true)
  {

    firm_version_t *p_boot_ver = (firm_version_t *)(FLASH_ADDR_BOOT_VER);

    id =  *(uint8_t *)0x08070000;

    cliPrintf("\n");
  	cliPrintf("boot id     : 0x%x\n", id);
    cliPrintf("boot ver    : %s\n", p_boot_ver->version);
    cliPrintf("boot name   : %s\n", p_boot_ver->name);
    cliPrintf("boot param  : 0x%X\n", rtcbackupRegRead(0));

    ret = true;
  }


  if (args->argc == 2 && args->isStr(0, "id") == true)
  {

  	 uint32_t data ;
  	 data    = (uint32_t) args->getData(1);

  	if(data <= 9 && data >= 1)
  	{
			if ( flashErase(0x08070000, 1) == true)
			{
				delay(100);

				if( flashWrite(0x08070000, (uint8_t *)&data, 1) == true )
				{
						cliPrintf("flash write OK\n");
						delay(100);
						NVIC_SystemReset(); // 안하면 cli 기능이 활성화 안됨..//
				}
				else
				{
						cliPrintf("flash write fail\n");
				}
			}
			else
			{
					cliPrintf("flash erase fail\n");
			}
  	}
  	else
  	{
  		cliPrintf("flash id range err ::  0x01~0x09\n");
  	}

     ret = true;
  }


  if (args->argc == 1 && args->isStr(0, "jump_boot") == true)
  {

    resetToBoot();

    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "jump_fw") == true)
  {

    rtcbackupRegWrite(1, 0);
    ret = true;
  }



  if (ret != true)
  {
    cliPrintf("boot info\n");
    cliPrintf("boot id 0xid // 0x31 ~ 0x39\n");
    cliPrintf("boot jump_boot\n");
    cliPrintf("boot jump_fw\n");
  }
}

