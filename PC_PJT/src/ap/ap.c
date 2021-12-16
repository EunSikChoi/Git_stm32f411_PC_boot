/*
 * ap.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "ap.h"
#include "boot/boot.h"

enum
{
  FILE_TYPE_NONE,
  FILE_TYPE_FW,
  FILE_TYPE_BIN,
  FILE_TYPE_TAG,
};

int32_t getFileSize(char *file_name);

//cmd_t cmd;


void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600); // CLI는  채널1로 정의(키보드)

}

void apMain(int argc, char *argv[])
{
	// 변수 정의
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

  file_type = FILE_TYPE_NONE;

  // 4번째 입력 문자에 따라 입력되는 문자 갯수를 정의 //
  if (argc >= 4)
  {
    if (strcmp(argv[3], "fw") == 0)
    {
      file_type = FILE_TYPE_FW;
      arg_cnt = 7;
    }
    if (strcmp(argv[3], "bin") == 0)
    {
      file_type = FILE_TYPE_BIN;
      arg_cnt = 7;
    }
    if (strcmp(argv[3], "tag") == 0)
    {
      file_type = FILE_TYPE_TAG;
      arg_cnt = 5;
    }
  }

  // Type에 다른 입력 문자 검사 //
  if (file_type == FILE_TYPE_NONE && argc != arg_cnt)
  {
    logPrintf("stm32cli comxx 57600 type[fw:bin] 0x8010000 file_name run[0:1]\n");
    logPrintf("stm32cli comxx 57600 type[tag] file_name\n");
    apExit();
  }

//  지금 사용 안함 //
//  if (file_type == FILE_TYPE_TAG)
//  {
//    logPrintf("\r\nadd tag...\r\n");
//
//    strcpy(file_name, argv[4]);
//    strcpy(dst_filename, file_name);
//    strcat(dst_filename, ".fw");
//
//    if(addTagToBin(file_name, dst_filename) != true)
//    {
//      fprintf( stderr, "  Add tag info to binary Fail! \n");
//      apExit();
//    }
//    apExit();
//  }

  //  MCU와 연동될 노트북 COM Port 설정  //
  //  각 입력 문자 정의 //
  uart_ch   = _DEF_UART2; // 노트북의 COM 포트 COM7, 11 등// 실제 잡히는 드라이브 port임 //
  uart_port = argv[1];
  uart_baud = (int32_t)strtoul(argv[2], (char **)NULL, (int) 0);

  logPrintf("uart ch   : %d\n", uart_ch);
  logPrintf("uart port : %s\n", uart_port);
  logPrintf("uart baud : %d bps\n", uart_baud);

  file_addr = (uint32_t)strtoul(argv[4], (char **)NULL, (int) 0); // 변수 타입을 unsigned int long 변경 //
  logPrintf("file addr : 0x%X\n", file_addr);

  strcpy(file_name, argv[5]);  // 문자열 복사 //
  logPrintf("file name : %s\n", file_name);

  file_size = getFileSize(file_name);
  if (file_size <= 0)
  {
    logPrintf("file size error\n");
    apExit();
  }
  logPrintf("file size : %d bytes\n", file_size);

  if (*argv[6] == '1')
  {
    file_run = true;
    logPrintf("file run  : true\n");
  }
  else
  {
    logPrintf("file run  : false\n");
  }

//   지금 사용 안함 //
//  if (file_type == FILE_TYPE_FW)
//  {
//    logPrintf("\r\nadd tag...\r\n");
//    strcpy(dst_filename, file_name);
//    strcat(dst_filename, ".fw");
//
//    if(addTagToBin(file_name, dst_filename) != true)
//    {
//      fprintf( stderr, "  Add tag info to binary Fail! \n");
//      apExit();
//    }
//
//
//    strcpy(file_name, dst_filename);
//  }


  //-- boot 초기화 시작
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
    //-- boot version cmd
  	//
    err_code = bootCmdReadBootVersion(boot_ver);

    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootVersion fail : %d\n", err_code);

    }
    logPrintf("boot ver \t: %s\n",  boot_ver);


    //-- boot name cmd
    //
    err_code = bootCmdReadBootName(boot_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootName fail : %d\n", err_code);
      break;
    }
    logPrintf("boot name \t: %s\n", boot_name);


    //-- app version cmd
    //
    err_code = bootCmdReadFirmVersion(firm_ver);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmVersion fail : %d\n", err_code);
      break;
    }
    logPrintf("App  ver \t: %s\n",  firm_ver);


    //-- app name cmd
    //
    err_code = bootCmdReadFirmName(firm_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmName fail : %d\n", err_code);
      break;
    }
    logPrintf("App  name \t: %s\n", firm_name);

    //-- Flash Erase
    //
    logPrintf("flash erase \t: ");
    pre_time = millis();
    //err_code = bootCmdFlashErase(0x08010000, 1024*64, 5000); // (file_addr, file_size, 5000);
    err_code = bootCmdFlashErase(file_addr, file_size, 5000);
    exe_time = millis()-pre_time;
    if (err_code != CMD_OK)
    {
      logPrintf("\nbootCmdFlashErase fail : %d\n", err_code);
      break;
    }
    logPrintf("OK (%dms)\n", exe_time);


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

int32_t getFileSize(char *file_name)
{
  int32_t ret = -1;
  FILE *fp;

  if ((fp = fopen( file_name, "rb")) == NULL) // fopne(이름, 모드) rb : read binaty wb: write binary
                                              // 즉 파일을 읽기 모드로 열겟다 라는 의미
  {
    fprintf( stderr, "Unable to open %s\n", file_name );
    return -1;
  }
  else
  {
    fseek( fp, 0, SEEK_END ); // 파일위치지시자를 컨트롤 // fseek(스트림,옵셋,어디인지 장소)
                              // 즉 fp 스트림의 파일에서 파일 위치 지시자를 옵셋 0, 파일 마지막 위치로 지정 //
    ret = ftell( fp );        // 파일 위치지시자의 위치를 알려줌 // 즉 마지막 위치정보는 현재 파일의 크기임
    fclose(fp);               // 파일 닫기
  }

  return ret;
}


