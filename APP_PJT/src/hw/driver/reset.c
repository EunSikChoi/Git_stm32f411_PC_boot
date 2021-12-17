/*
 * reset.c
 *
 *  Created on: 2021. 11. 19.
 *      Author: 82109
 */




#include "reset.h"
#include "rtc.h"

static uint32_t reset_count = 0;
static uint32_t run_timeout_count = 0;
//static void resetToRunBoot(void);


void resetISR(void)
{
  if( run_timeout_count > 0)
  {
    run_timeout_count--;
  }
}

bool resetInit(void)
{
  bool  ret = true;
#if 0
 //Reset 핀이 눌리면//
 if(RCC->CSR & (1<<26))
 {
   rtcbackupRegWrite(1, rtcbackupRegRead(1) + 1);
   delay(500);
   reset_count = rtcbackupRegRead(1);

 }

 rtcbackupRegWrite(1, 0);
#endif

  return ret;

}

void resetToBoot(void)
//void resetToRunBoot(void)
{
  uint32_t reg;

  reg = rtcbackupRegRead(1);

  reg |= (1<<0);
  rtcbackupRegWrite(1, reg);
  NVIC_SystemReset();
}

uint32_t resetGetCount(void)
{
  return reset_count;
}
