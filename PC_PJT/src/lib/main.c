/*
 * main.c
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */


#include "main.h"

void exitISR(int sig)
{
  apExit();
}

int main(int argc, char *argv[])
{

  signal(SIGINT, exitISR); // 종료시(Ctrl+C, SIGINT발생) exitISR 루프 실행 명령 //
  setbuf(stdout, NULL);    // DOS에서 콘솔에서는 데이터를 버퍼에 저장 하는데 저장 하지 말고
                           // 바로 출력, 수정사항 바로 적용의 의미
                           // stdout 출력 스트림을 버퍼에 저장하지 말고 바로 화면에 출력 의미


	hwInit();
	apInit();

	apMain(argc, argv);

	return 0;


}
