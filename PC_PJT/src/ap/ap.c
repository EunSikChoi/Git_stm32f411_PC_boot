/*
 * ap.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "ap.h"


cmd_t cmd;


void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600); // CLI는  채널1로 정의(키보드)

  cmdInit(&cmd);
}

void apMain(int argc, char *argv[])
{
  uint8_t  uart_ch;
  char    *uart_port;
  uint32_t uart_baud;


  if (argc != 3)
  {
    logPrintf("wrong args\n");
    apExit();
  }

  uart_ch   = _DEF_UART2;
  uart_port = argv[1];
  uart_baud = (int32_t)strtoul(argv[2], (char **)NULL, (int) 0);

  logPrintf("uart ch   : %d\n", uart_ch);
  logPrintf("uart port : %s\n", uart_port);
  logPrintf("uart baud : %d bps\n", uart_baud);

  if (uartOpenPort(uart_ch, uart_port, uart_baud) == true)
  {
    logPrintf("uart open : OK\n");
  }
  else
  {
    logPrintf("uart open : Fail\n");
    apExit();
  }

  cmdOpen(&cmd, _DEF_UART2, 57600); // MCU와 통신할 채널2 포트 // node는 cmd 구조체로 정의 //


  while(1)
  {
#if 1
    cliMain();
#else

    if (uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx_data;

      rx_data = uartRead(_DEF_UART1);

      if (rx_data == '1')
      {
        uint8_t tx_data;

        tx_data = 1;
        if (cmdSendCmdRxResp(&cmd, 0x10, &tx_data, 1, 1000) == true)
        {
          printf("LED ON\n");
        }
        else
        {
          printf("LED ON Fail\n");
        }
      }

      if (rx_data == '2')
      {
        uint8_t tx_data;

        tx_data = 2;
        if (cmdSendCmdRxResp(&cmd, 0x10, &tx_data, 1, 1000) == true)
        {
          printf("LED OFF\n");
        }
        else
        {
          printf("LED OFF Fail\n");
        }
      }

      if (rx_data == '3')
      {
        uint8_t tx_data;

        tx_data = 3;
        if (cmdSendCmdRxResp(&cmd, 0x10, &tx_data, 1, 1000) == true)
        {
          printf("LED Toggle\n");
        }
        else
        {
          printf("LED Toggle Fail\n");
        }
      }
    }
#endif
  }
}

void apExit(void)
{
  for (int i=0; i<UART_MAX_CH; i++)
  {
    uartClose(i);
  }
  printf("\ncli exit\n");
  exit(0);
}


