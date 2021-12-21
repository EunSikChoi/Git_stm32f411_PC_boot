/*
 * boot.c
 *
 *  Created on: 2021. 12. 16.
 *      Author: 82109
 */


#include "boot.h"
#include "cmd.h"



static cmd_t cmd;

bool bootInit(uint8_t channel, char *port_name, uint32_t baud)
{
  bool ret = false;


  cmdInit(&cmd);

  uartSetPortName(channel, port_name);

  printf("\nrun bootloader...\n");

#if 0 // CDC 모드에서 boot 모드로 점프 시킬 경우에만 사용함 // 485에서는 사용 안됨 //

    uartPrintf(channel, "BOOT 5555AAAA");
    //uartClose(channel);

#endif

  delay(1000);

  for (int i=0; i<3; i++) // 통신 Open을 3번 시도하고, 실패시  빠져나감 //
  {
    ret = cmdOpen(&cmd, channel, baud);
    if (ret == true)
    {
    	ret = true;
      break;
    }
    delay(2000);
  }


  return ret;
}

bool bootDeInit(uint8_t channel)
{
  uartClose(channel);
  return true;
}


uint8_t bootCmdReadBootVersion( uint8_t *p_version)
{
  bool ret;
  uint8_t err_code = CMD_OK;


  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(&cmd, BOOT_CMD_READ_BOOT_VERSION, NULL, 0, 500);

  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_version[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = CMD_FALSE; // p_cmd->error // not receive error
  }

  return err_code;
}

uint8_t bootCmdReadBootName(uint8_t *p_str)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_BOOT_NAME, NULL, 0, 500);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_str[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = CMD_FALSE; // p_cmd->error // not receive error
  }

  return err_code;
}

uint8_t bootCmdReadFirmVersion(uint8_t *p_version)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_FIRM_VERSION, NULL, 0, 500);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_version[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = CMD_FALSE; // p_cmd->error // not receive error
  }

  return err_code;
}

uint8_t bootCmdReadFirmName(uint8_t *p_str)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_FIRM_NAME, NULL, 0, 500);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_str[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    err_code = CMD_FALSE; // p_cmd->error // not receive error
  }

  return err_code;
}

uint8_t bootCmdFlashErase(uint32_t addr, uint32_t length, uint32_t timeout)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;
  uint8_t tx_buf[CMD_LENGTH];


  tx_buf[0] = (uint8_t)(addr >>  0);
  tx_buf[1] = (uint8_t)(addr >>  8);
  tx_buf[2] = (uint8_t)(addr >> 16);
  tx_buf[3] = (uint8_t)(addr >> 24);

  tx_buf[4] = (uint8_t)(length >>  0);
  tx_buf[5] = (uint8_t)(length >>  8);
  tx_buf[6] = (uint8_t)(length >> 16);
  tx_buf[7] = (uint8_t)(length >> 24);


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_FLASH_ERASE, tx_buf, CMD_LENGTH, timeout);


  if (ret == true && p_cmd->rx_packet.error == CMD_OK)
  {
    err_code = CMD_OK;
  }
  else
  {
    err_code = p_cmd->rx_packet.error;
  }

  return err_code;
}


uint8_t bootCmdFlashWrite(uint32_t addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;
  uint8_t *tx_buf;


  if (length > CMD_MAX_DATA_LENGTH)
  {
    err_code = BOOT_ERR_BUF_OVF;
    return err_code;
  }

  tx_buf = p_cmd->tx_packet.data;
  //tx_buf = p_cmd->tx_packet.data; 앞에 8바이트 정보 overWrite됨. data로 해야됨 //


  tx_buf[0] = (uint8_t)(addr >>  0);
  tx_buf[1] = (uint8_t)(addr >>  8);
  tx_buf[2] = (uint8_t)(addr >> 16);
  tx_buf[3] = (uint8_t)(addr >> 24);

  tx_buf[4] = (uint8_t)(length >>  0);
  tx_buf[5] = (uint8_t)(length >>  8);
  tx_buf[6] = (uint8_t)(length >> 16);
  tx_buf[7] = (uint8_t)(length >> 24);

  for (int i=0; i<length; i++)
  {
    tx_buf[CMD_LENGTH + i] = p_data[i];
  }

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_FLASH_WRITE, tx_buf, CMD_LENGTH + length, timeout);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    err_code = CMD_OK;
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}

uint8_t bootCmdJumpToFw(void)
{
  bool ret;
  uint8_t err_code = CMD_OK;
  cmd_t *p_cmd = &cmd;


  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_JUMP_TO_FW, NULL, 0, 1000);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    err_code = CMD_OK;
  }
  else
  {
    err_code = p_cmd->error;
  }

  return err_code;
}
