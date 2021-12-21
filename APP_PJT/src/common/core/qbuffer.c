/*
 * qbuffer.c
 *
 *  Created on: 2021. 11. 16.
 *      Author: 82109
 */


#include "qbuffer.h"
#include "reset.h"





const char *JUMP_BOOT_STR = "PC 5A5AA5A5";


void     qbufferInit(void)
{



}




bool qbufferCreate (qbuffer_t *p_node, uint8_t *p_buf,  uint32_t length)
{

	 uint8_t id = 0;
   bool ret = true;

   id =  *(uint8_t *)0x08070000;

   p_node->in =  0;
   p_node->out = 0;
   p_node->len = length;
   p_node->size  = 1;
   p_node->p_buf = p_buf;
   p_node->id		 = id;


   return ret;

}


bool     qbufferWrite(qbuffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  uint32_t next_in;

  for(int i =0; i<length; i++)
  {
    next_in = (p_node->in + 1) % p_node->len;

    if(next_in != p_node->out)
    {
      if(p_node-> p_buf != NULL)
      {
        p_node-> p_buf[p_node->in] = p_data[i];
      }
      p_node->in = next_in;
    }
    else
    {
      ret = false;
      break;
    }
  }

  return ret;
}

static volatile  uint8_t k , y;

bool qbufferRead(qbuffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
 // uint8_t boot_flash_id = 0;


  for(int i =0; i<length; i++)
  {
    if(p_node-> p_buf != NULL)
    {
      p_data[i] = p_node->p_buf[p_node->out];
    }

    // Magic key // app -> boot boot jump //
    // 나중에는 TPC나 외부 통신값에 의해 활성화 해야함.
    // 안그려면 "P"값마다 지연이 발생함

    // 매직키 11 + 1(Boot_ID) 촣 12문자 수신 //
    if( y <= 10)
    {
			if(JUMP_BOOT_STR[k++] != p_data[i])
			{
					 k = 0;
			}
			else  // 같으면 STR 진입
			{
				y++;
				delay(1); // Wait for next char //
			}
    }
    else
    { // 매직키 11개, 일치시 마지막으로 ID 판별 //
      if(p_node-> id == p_data[i])
      {
      	y++;
  			delay(1); // Wait for next char //
      }
      else
      {
      	y = k = 0 ;
      }
    }


    if( y == 12)
    {
    	resetToBoot();
    }




    if(p_node->out != p_node->in)
    {
      p_node->out = (p_node->out + 1) % p_node->len;
    }
    else
    {
      ret = false;
      break;
    }

  }


  return ret;

}


uint32_t qbufferAvailable(qbuffer_t *p_node)
{
  uint32_t ret;

  ret = (p_node ->in - p_node->out) % p_node->len;

  return ret;

}
void qbufferFlush(qbuffer_t *p_node)
{
  p_node->in = 0;
  p_node->out = 0;

}
