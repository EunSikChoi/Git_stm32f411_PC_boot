/*
 * ap.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "ap.h"
#include "boot/boot.h"

//cmd_t cmd;


void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600); // CLI는  채널1로 정의(키보드)

}

void apMain(int argc, char *argv[])
{
  bool ret;
  uint8_t err_code;
  uint8_t  uart_ch;
  char    *uart_port;
  uint32_t uart_baud;
  uint8_t boot_ver[32];
  uint8_t boot_name[32];
  uint8_t firm_ver[32];
  uint8_t firm_name[32];
  uint32_t pre_time;
  uint32_t exe_time;
  uint8_t  file_type;
  uint32_t file_addr;
  int32_t  file_size;
  char     file_name[256];
  char     dst_filename[256];
  bool     file_run = false;
  FILE     *fp;
  uint8_t  arg_cnt = 0;

  // Check 입력 문자 // stm32.exe com99 57600 3개 //
  if (argc != 3)
  {
    logPrintf("wrong args\n");
    apExit();
  }

  //  MCU와 연동될 노트북 COM Port 설정  //
  uart_ch   = _DEF_UART2; // 노트북의 COM 포트 COM7, 11 등// 실제 잡히는 드라이브 port임 //
  uart_port = argv[1];
  uart_baud = (int32_t)strtoul(argv[2], (char **)NULL, (int) 0);

  logPrintf("uart ch   : %d\n", uart_ch);
  logPrintf("uart port : %s\n", uart_port);
  logPrintf("uart baud : %d bps\n", uart_baud);

  //-- boot 시작
	//
	ret = bootInit(uart_ch, uart_port, uart_baud);
	if (ret != true)
	{
		logPrintf("bootInit Fail\n");
		apExit();
	}

	logPrintf("\n\nboot start...\n");


  while(1)
  {
#if 0
    cliMain();
#else

    err_code = bootCmdReadBootVersion(boot_ver);

    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootVersion fail : %d\n", err_code);

    }
    logPrintf("boot ver \t: %s\n",  boot_ver);


    //-- 부트로더 이름 읽기
    //
    err_code = bootCmdReadBootName(boot_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootName fail : %d\n", err_code);
      break;
    }
    logPrintf("boot name \t: %s\n", boot_name);


    //-- 펌웨어 버전 읽기
    //
    err_code = bootCmdReadFirmVersion(firm_ver);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmVersion fail : %d\n", err_code);
      break;
    }
    logPrintf("App  ver \t: %s\n",  firm_ver);


    //-- 펌웨어 이름 읽기
    //
    err_code = bootCmdReadFirmName(firm_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmName fail : %d\n", err_code);
      break;
    }
    logPrintf("App  name \t: %s\n", firm_name);


    apExit();
#endif
  }// END WHILE LOOP //
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


