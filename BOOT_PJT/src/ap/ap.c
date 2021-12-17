/*
 * ap.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "ap.h"
#include "boot.h"
#include "log.h"


cmd_t cmd;

void apInit(void)
{
	//  cliOpen(_DEF_UART1, 57600); // CDC for CLI
	// uartOpen(_DEF_UART2, 57600); //NOT USED
	 cliOpen(_DEF_UART3, 115200);    // UART for CLI

	 cmdInit(&cmd);
	 cmdOpen(&cmd, _DEF_UART3, 115200);
}

UART_HandleTypeDef huart2;

uint16_t count;

void apMain(void)
{
  uint32_t pre_time;
  uint32_t led_blink_time = 200;


  // boot 점프 // Reset시 버튼이 눌려 있으면 강제로 bootjump 실행 //
  if (buttonGetPressed(_DEF_BUTTON1) == false)
  {
    if (bootVerifyFw()  == true)
    {
      bootJumpToFw();

    }
  }




  pre_time = millis();

  if(resetGetCount() >= 2)
  {
    led_blink_time = 200;
  }


	while(1)
	{
		if(millis()-pre_time >= led_blink_time) //
		{
			pre_time = millis();
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}


#if 0
		cliMain();
#else

    if(cmdReceivePacket(&cmd) == true)
    {
      bootProcessCmd(&cmd);
    }

#endif

	}

}

