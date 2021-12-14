/*
 * ap.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "ap.h"
#include "log.h"




void apInit(void)
{
	//  cliOpen(_DEF_UART1, 57600);
	 uartOpen(_DEF_UART2, 57600);
	 cliOpen(_DEF_UART3, 57600);
}

UART_HandleTypeDef huart2;

uint16_t count;

void apMain(void)
{
  uint32_t pre_time;
  uint32_t led_blink_time = 1000;


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
	  if(uartAvailable(_DEF_UART3) > 0)
	  {
			uint8_t rx_data;
			pre_time = millis();

			rx_data = uartRead(_DEF_UART3);

			uartPrintf(_DEF_UART3, "RxData1111222233334444444444555555555555 : %c 0x%x\n", rx_data, rx_data);

			uartPrintf(_DEF_UART3, "Time %d ms\n", millis()-pre_time );

			count++;
			logPrintf("No.%d  Time Date   \t: %s: %s \r\n", count, __TIME__,__DATE__ );


	  }
	#endif



		cliMain();

	}

}

