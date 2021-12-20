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

  bool run_boot = false;
  uint8_t reg = 0;

  reg = rtcbackupRegRead(1);



  if (reg & (1<<0))
  {
  	run_boot = true;
  	reg &= ~(1<<0);
  	rtcbackupRegWrite(1, reg);
  }

  // 리셋키 2번 눌린경우 App 부트점프 하지 않고, Boot 펌웨에서 대기 //
  if (resetGetCount() == 2)
  {
  	run_boot = true;
  }

  //전원을 껏다가 키면 백업 레지스터 모두 초기화 , 무조건 아래 루프 실행, App 으로 부트점프함//
  if (run_boot == false)
  {
    // boot 점프 // Reset시  강제로 bootjump 실행 APP프로그램 실행 //
    //  RESET시 버튼이 눌린 경우에는 부트점프 안함 //
  	if (buttonGetPressed(_DEF_BUTTON1) == false)
  	{
      if (bootVerifyFw() == true && bootVerifyCrc() == true)
  		{
  			bootJumpToFw();
  		}
		}
  }

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

