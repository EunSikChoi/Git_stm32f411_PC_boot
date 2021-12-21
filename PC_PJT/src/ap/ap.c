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

#define TX_BLOCK_LENGTH     512

int32_t getFileSize(char *file_name);
bool addTagToBin(char *src_filename, char *dst_filename);

//cmd_t cmd;


void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600); // CLI는  채널1로 정의(키보드)

}

uint8_t boot_id;

void apMain(int argc, char *argv[])
{
	// 변수 정의
  bool ret;
  uint8_t err_code;
  uint8_t  uart_ch;
  uint8_t boot_flash_id[0];
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
      arg_cnt = 8;
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
    logPrintf("stm32cli comxx 115200 type[fw:bin] 0x8010000 file_name run[0:1]\n");
    logPrintf("stm32cli comxx 115200 type[tag] file_name\n");
    apExit();
  }


  //  MCU와 연동될 노트북 COM Port 설정  //
  //  각 입력 문자 정의 //
  uart_ch   = _DEF_UART2; // 노트북의 COM 포트 COM7, 11 등// 실제 잡히는 드라이브 port임 //
  uart_port = argv[1];
  uart_baud = (int32_t)strtoul(argv[2], (char **)NULL, (int) 0);
  boot_id   =  (int8_t)strtoul(argv[7], (char **)NULL, (int) 0);


  logPrintf("uart ch   : %d\n", uart_ch);
  logPrintf("uart port : %s\n", uart_port);
  logPrintf("uart baud : %d bps\n", uart_baud);
  logPrintf("boot_id   : 0x%x\n", boot_id);

  if(boot_id >= 0x10 || boot_id <= 0x00) // id 기준은 0x01~0x09 범위로 제한 //
  {
  	logPrintf("wrong boot Id :: 0x01 ~ 0x09 \n");
  	apExit();
  }

  //-- boot 초기화 시작
	//
	ret = bootInit(uart_ch, uart_port, uart_baud);
	if (ret != true)
	{
		logPrintf("bootInit Fail\n");
		apExit();
	}

	logPrintf("\n\nboot start...\n");

  // if 2 , magic key printf //
  if(*argv[6] == '2')
  {
  	boot_flash_id[0] = boot_id;
  	logPrintf("\nMagic Key Write\n\n");
  	uartPrintf(uart_ch, "PC 5A5AA5A5");
  	uartWrite(uart_ch, boot_flash_id, 1 ); 		// Add + 1(boot id) // total 12 byte //
  	delay(1000); 															// wait for Boot mode change //
  }

  file_addr = (uint32_t)strtoul(argv[4], (char **)NULL, (int) 0); // 변수 타입을 unsigned int long 변경 //
  logPrintf("file addr : 0x%X\n", file_addr);

  strcpy(file_name, argv[5]);  // 파일이름 복사, 업데이트할 bin파일명 //
  logPrintf("file name : %s\n", file_name);

  file_size = getFileSize(file_name);
  if (file_size <= 0)
  {
    logPrintf("file size error\n");
    apExit();
  }
  logPrintf("file size : %d bytes\n", file_size);

  if (*argv[6] == '1' || *argv[6] == '2' )
  {
    file_run = true;
    logPrintf("file run  : true\n");
  }
  else
  {
    logPrintf("file run  : false\n");
    apExit();
  }

  //-- Tag 파일(.bin) 파일 생성
  //
  if (file_type == FILE_TYPE_FW)
  {
    logPrintf("\r\nadd tag...\r\n");
    strcpy(dst_filename, file_name); // 기존 파일 이름  stm32f411_App.bin 을  dst 배열에 복사
    strcat(dst_filename, ".fw");     // dst 배열에 복사 한 파일 이름 마지막에 .fw 이름 추가 // 배열 합치는 함수

    if(addTagToBin(file_name, dst_filename) != true)
    {
      fprintf( stderr, "  Add tag info to binary Fail! \n");
      apExit();
    }


    strcpy(file_name, dst_filename); // 생성된 파일(stm32f411_fw_for_boot.bin.fw)이름을 기존파일(stm32f411_fw_for_boot.bin)에 덮어 씌움 //
                                     // 즉 file_name = stm32f411_fw_for_boot.bin.fw 이기 때문에 이후에는 .fw 파일을 Write함 MCU에           //
  }                                  // 즉 기존 파일에는 tag영역에 crc값 없지만. 위 코드을 통해, 기존파일을 신규파일 전부 복사하고, 신규 파일에 crc 값을 추가하여 다시 기존 파일에 전부 복사함 //



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
      apExit();
      break;

    }
    logPrintf("boot ver \t: %s\n",  boot_ver);


    //-- boot name cmd
    //
    err_code = bootCmdReadBootName(boot_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootName fail : %d\n", err_code);
      apExit();
      break;
    }
    logPrintf("boot name \t: %s\n", boot_name);


    //-- app version cmd
    //
    err_code = bootCmdReadFirmVersion(firm_ver);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmVersion fail : %d\n", err_code);
      apExit();
      break;
    }
    logPrintf("App  ver \t: %s\n",  firm_ver);


    //-- app name cmd
    //
    err_code = bootCmdReadFirmName(firm_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmName fail : %d\n", err_code);
      apExit();
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
      apExit();
      break;
    }
    logPrintf("OK (%dms)\n", exe_time);


    //-- Flash Write
    //
    if ((fp = fopen(file_name, "rb")) == NULL) // 파일 오픈. read binary //
    {
      logPrintf("Unable to open %s\n", file_name);
      apExit();
    }


    uint32_t addr;
    uint32_t len;
    bool     write_done = false;
    uint8_t  tx_buf[TX_BLOCK_LENGTH];
    uint16_t write_percent;
    uint16_t pre_percent = 0;

    addr = file_addr;
    //file_addr : flash Write 시작주소
    //addr  : 다음 루프에 써야할 Flash 주소
    pre_time = millis();
    while(1)
    {
      if (!feof(fp)) // 파일의 끝을 감지 // 마지막 위치 도달하면 0, 그전에는 1 리턴 //
      {
        len = fread(tx_buf, 1, TX_BLOCK_LENGTH, fp); // tx_buf : 파일에서 읽어 저장할 위치 , size(몇개씩), 길이 , 읽을 파일 포인터)

        err_code = bootCmdFlashWrite(addr, tx_buf, len, 1000); // 256바이트 크기를 Write // feof 종료시까지 //
        if (err_code == CMD_OK)
        {
          addr += len; // 다음 Write 할 주소 저장 //
          delay(100);  // 안하면 hardware Fault 진입함 //

          write_percent = (addr-file_addr) * 100 / file_size; // (8100 - 8100)*100 /  400 = 0% , (8500 - 8100)*100 / 400 = 100%

          if ((write_percent/10) != pre_percent)
          {
            logPrintf("flash write \t: %d%%\r", write_percent);
            pre_percent = (write_percent/10);
          }


          if ((addr-file_addr) >= file_size)// 써야할 주소 - 시작주소  의미는  현재까지 쓴 데이터의 크기 의미 즉 파일크기와 현재까지 쓴 크기가 같으면 전체 Write END//
          {
            write_done = true; // Flash Write 종료 //
            break;
          }
        }
        else
        {
          logPrintf("bootCmdFlashWrite fail : 0x%x, %d\n", addr, err_code);
          apExit();
          break;
        }
      }
      else
      {
        break;
      }
    }

    fclose(fp);
    exe_time = millis()-pre_time;

    logPrintf("\n");

    if (write_done == true)
    {
      logPrintf("flash write \t: OK (%dms)\n", exe_time);

      if (file_run == true && file_type == FILE_TYPE_FW)
      {
        pre_time = millis();
        err_code = bootCmdJumpToFw();
        exe_time = millis()-pre_time;
        if (err_code == CMD_OK)
        {
          logPrintf("jump to fw \t: OK (%dms)\n", exe_time);
        }
        else
        {
          logPrintf("jump to fw \t: fail, %d\n", err_code);
          apExit();
        }
        bootDeInit(uart_ch);
      }
    }
    else
    {
      logPrintf("flash write \t: Fail \n");
    }

    break;

#endif
  }// END WHILE LOOP //

  apExit();
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

bool addTagToBin(char *src_filename, char *dst_filename)
{
  FILE    *p_fd;
  uint8_t *buf;
  size_t   src_len;
  uint16_t t_crc = 0;
  firm_tag_t *p_tag;


  if (!strcmp(src_filename, dst_filename)) // 두 이름이 같으면  "0" 리턴, 반대 는 "1" 즉 같으면  Err ,app exit 실행 //
  {
    fprintf( stderr, "  src file(%s) and dst file(%s) is same! \n", src_filename, dst_filename );
    apExit();
  }

  /* Open src file */
  if ((p_fd = fopen(src_filename, "rb")) == NULL) // 파일 포인터는(p_fd) 기존 stm32f411_fw_for_boot.bin 을 의미 //
  {
    fprintf( stderr, "  unable to open src file(%s)\n", src_filename );
    exit( 1 );
  }


  fseek( p_fd, 0, SEEK_END );  // 파일위치지시자를 컨트롤 // fseek(스트림,옵셋,어디인지 장소) // 파일 지시자를 맨뒤로 이동, 크기를 알아내도록함//
  src_len = ftell( p_fd );     // 파일 위치지시자의 위치를 알려줌 // 즉 마지막 위치정보는 현재 파일의 크기임
  fseek( p_fd, 0, SEEK_SET );  // 파일 위치자를 맨뒤로 보내고 나서는 반드시 다시 처음 위치로 이동(SEEK_SET) 해줘야 함 //
  														 // 즉 src_len 는 파일의 마지막 주소값(크기)을 의미


  /* Make Space for copy scr file */                                 // 기존 파일을(bin) 복사를 위한 메모리 생성, 새로운 bin.fw 파일을 생성을 위해서 //
  if ((buf = (uint8_t *) calloc(src_len, sizeof(uint8_t))) == NULL)  // calloc 메모리 할당 및 초기화 함수(포인터형변환)calloc(크기, 데이터 1개 자료형 크기) //
  {                                                                  // 즉 buf 에 기존 파일 만큼의 데이터 메모리 할당 시킴 //
    fclose(p_fd);
    fprintf( stderr, "  malloc Error \n");
    apExit();
  }

  /* Copy read fp to buf */                         // 앞에서 생성산 매모리 영역에 기존 파일을 읽어서 복사 //
  if(fread( &buf[0], 1, src_len, p_fd ) != src_len) // fread() :  파일을 읽어서 설정된 변수에 저장하는 함수
  {                                                 // fread(저장한 메모리 포인터, 한번에 읽어올 크기 , 읽어올 횟수(데이터크기), 파일 포인터)
    fclose(p_fd);
    free(buf); 																			// 오동작시, 메모리 누수를  막기 위해 생성한 메모리 삭제
    fprintf( stderr, "  length is wrong! \n" );
    apExit();
  }
  fclose(p_fd);


  p_tag = (firm_tag_t *)buf; // 여기서 buf를 데이터형변환(firm_tag_t)로 선언하고 포인터 변수(p_tag)를 입력하면
                             // p_tag는 tag 구조체를 주소 가르치는 포인터가 되므로  복사한파일 메모리의 tag 메모리의 접근이 가능해짐
                             // tag 영역이 시작 주소 이기 때문에 buf의 시작 주소를 구조체(firm_tag_t_) 정의하면, 해당 구조체 주소에 각 맴버변수로 접근이 가능


  if (p_tag->magic_number == FLASH_MAGIC_NUMBER)    // 매직키 5555AAAA는 PC에서 생성한 bin.fw 파일에 매직키임,
  {																								  // 즉 5555AAAA 와 같으면, 이미 생성된 bin 파일이기 때문에 에러임
    free(buf);                                  		// 오동작시, 메모리 누수를  막기 위해 생성한 메모리 삭제
    fprintf( stderr, "  already magic number\n");
    return true;
  }
  if (p_tag->magic_number != 0xAAAA5555)  // 매직키 AAAA5555는 APP에서 만든 bin 파일에 존재하는 매직키임
  {																				// 동일해야지만 정상 App에서 온 bin 파일임. 다르면 에러임
    free(buf);
    fprintf( stderr, "  wrong magic number 0x%X \n", p_tag->magic_number);
    return false;
  }



  /* Calculate CRC16 */
  size_t i;
  uint32_t tag_size;

  tag_size = p_tag->size_tag;

  for (i = 0; i<src_len-tag_size; i++)        	// 파일 마지막 위치( Total Size - 1K )  //
  {
    utilUpdateCrc(&t_crc, buf[tag_size + i]); 	// 실제 CRC 검사는 tag_size(1K) 이후부터 수행 // tag 영역은 제외 //
  }

  p_tag->magic_number     = FLASH_MAGIC_NUMBER; 										 // 신규 매직키 입력 0x5555AAAA
  p_tag->tag_flash_start  = p_tag->addr_fw;
  p_tag->tag_flash_end    = p_tag->addr_fw + (src_len - tag_size);   // 0x08010400 + ( Total Size - 1K ) //
  p_tag->tag_flash_length = p_tag->tag_flash_end - p_tag->tag_flash_start;
  p_tag->tag_length       = tag_size;
  strcpy((char *)p_tag->tag_date_str, __DATE__);
  strcpy((char *)p_tag->tag_time_str, __TIME__);
  p_tag->tag_flash_crc = t_crc;  // CRC 계산값을 해당 메모리변수에 입력 // PC에서 계산된 CRC 값 //
                                 // 부트프르그램에서 해당 영역 CRC와 자체 계산한 CRC 일치해야 APP 부트점프 실행


  /* Store data to dst file */
  if ((p_fd = fopen(dst_filename, "wb")) == NULL) // stm32f411_App.bin.fw 파일 열기 //
  {
   free(buf);
   fprintf( stderr, "  unable to open dst file(%s)\n", dst_filename );
   apExit();
  }
  																						 // buf = 0x08010000 ~ 메모리 종료시점 // 변경된매직키, 업데이트된 CRC값 포함된 //
  if(fwrite(buf, 1, src_len, p_fd) != src_len) // buf에 저정된 신규파일 데이터를  p_fd(stm32f411_App.bin.fw)에 Write //
  {
   fclose(p_fd);
   free(buf);
   //_unlink(dst_filename);
   fprintf( stderr, "  total write fail! \n" );
   apExit();
  }
  // tag info 출력//
  printf("created file    : %s (%d KB)\n", dst_filename, (int)((src_len)/1024) );
  printf("tag fw start    : 0x%08X \n"   , p_tag->tag_flash_start);
  printf("tag fw end      : 0x%08X \n"   , p_tag->tag_flash_end);
  printf("tag crc         : 0x%04X \n"   , p_tag->tag_flash_crc);
  printf("tag date        : %s \n"       , p_tag->tag_date_str);
  printf("tag time        : %s \n"       , p_tag->tag_time_str);

  fclose(p_fd); // 마무리 파일 닫고
  free(buf);    // 잡앗던 malloc 메모리 해제하면 신규 fw 파일 만들기 종료 //

  return true;
}

uint8_t getBootid(void)
{
	uint8_t ret = 0;
	ret = boot_id;
	return ret;
}





