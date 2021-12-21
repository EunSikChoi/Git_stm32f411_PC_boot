/*
 * cmd.h
 *
 *  Created on: 2021. 12. 15.
 *      Author: 82109
 */

#ifndef SRC_COMMON_HW_INCLUDE_CMD_H_
#define SRC_COMMON_HW_INCLUDE_CMD_H_




#include "hw_def.h"

#ifdef _USE_HW_CMD



#define CMD_MAX_DATA_LENGTH       HW_CMD_MAX_DATA_LENGTH


#define CMD_OK                0
#define CMD_FALSE             1


#define CMD_DIR_M_TO_S        0
#define CMD_DIR_S_TO_M        1


#define CMD_STX                     0x02
#define CMD_ETX                     0x03
#define CMD_LENGTH									9
#define CMD_DATA_LEN								6


#define CMD_STATE_WAIT_STX          0
#define CMD_CHECK_ID								1
#define CMD_STATE_WAIT_CMD          2
#define CMD_STATE_WAIT_DIR          3
#define CMD_STATE_WAIT_ERROR        4
#define CMD_STATE_WAIT_LENGTH_L     5
#define CMD_STATE_WAIT_LENGTH_H     6
#define CMD_STATE_WAIT_DATA         7
#define CMD_STATE_WAIT_CHECKSUM     8
#define CMD_STATE_WAIT_ETX          9


typedef struct
{
  uint8_t   cmd;
  uint8_t   id;
  uint8_t   dir;
  uint8_t   error;
  uint16_t  length;
  uint8_t   check_sum;
  uint8_t   check_sum_recv;
  uint8_t   buffer[CMD_MAX_DATA_LENGTH];
  uint8_t   *data;
} cmd_packet_t;


typedef struct
{
  uint8_t   ch;
  uint8_t 	boot_id;
  bool      is_init;
  uint32_t  baud;
  uint8_t   state;
  uint32_t  pre_time;
  uint32_t  index;
  uint8_t   error;

  cmd_packet_t  rx_packet;
  cmd_packet_t  tx_packet;
} cmd_t;


void cmdInit(cmd_t *p_cmd);                             // cmd 함수 초기
bool cmdOpen(cmd_t *p_cmd, uint8_t ch, uint32_t baud);  // cmd 함수 오픈 및 설정
bool cmdClose(cmd_t *p_cmd);                            // cmd 함수 닫기
bool cmdReceivePacket(cmd_t *p_cmd);                    // cmd 패킷 수신(상태머신에 의해 수신)
void cmdSendCmd(cmd_t *p_cmd, uint8_t cmd, uint8_t *p_data, uint32_t length);                   // cmd 명령 송신 함수          // PC -> MCU
void cmdSendResp(cmd_t *p_cmd, uint8_t cmd, uint8_t err_code, uint8_t *p_data, uint32_t length);// cmd 패킷 수신 응답 함수 //  MCU -> PC
bool cmdSendCmdRxResp(cmd_t *p_cmd, uint8_t cmd, uint8_t *p_data, uint32_t length, uint32_t timeout); // cmd 명령 송신 및 정상수신확인 함수 // PC <-> MCU

#endif



#endif /* SRC_COMMON_HW_INCLUDE_CMD_H_ */
