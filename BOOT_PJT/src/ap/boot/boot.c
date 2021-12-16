/*
 * boot.c
 *
 *  Created on: 2021. 12. 16.
 *      Author: 82109
 */

#include "boot/boot.h"




#define BOOT_CMD_READ_BOOT_VERSION      0x00
#define BOOT_CMD_READ_BOOT_NAME         0x01
#define BOOT_CMD_READ_FIRM_VERSION      0x02
#define BOOT_CMD_READ_FIRM_NAME         0x03
#define BOOT_CMD_FLASH_ERASE            0x04
#define BOOT_CMD_FLASH_WRITE            0x05
#define BOOT_CMD_JUMP_TO_FW             0x08
#define BOOT_CMD_LED_CONTROL            0x10



static void bootCmdLedControl(cmd_t *p_cmd);
static void bootCmdReadBootVersion(cmd_t *p_cmd);
static void bootCmdReadBootName(cmd_t *p_cmd);
static void bootCmdReadFirmVersion(cmd_t *p_cmd);
static void bootCmdReadFirmName(cmd_t *p_cmd);


extern firm_version_t boot_ver;

firm_version_t *p_boot_ver = &boot_ver;
firm_version_t *p_firm_ver = (firm_version_t *)(FLASH_ADDR_FW_VER);
firm_tag_t     *p_firm_tag = (firm_tag_t *)FLASH_ADDR_TAG;

uint8_t firm_ver[32]  = "V12031123R2";
uint8_t firm_name[32] = "STM32F411V2";

void bootInit(void)
{

}

void bootProcessCmd(cmd_t *p_cmd)
{
  switch(p_cmd->rx_packet.cmd)
  {
    case BOOT_CMD_LED_CONTROL: //0x10
      bootCmdLedControl(p_cmd);
      break;

    case BOOT_CMD_READ_BOOT_VERSION:
      bootCmdReadBootVersion(p_cmd);
      break;

    case BOOT_CMD_READ_BOOT_NAME:
      bootCmdReadBootName(p_cmd);
      break;

    case BOOT_CMD_READ_FIRM_VERSION:
      bootCmdReadFirmVersion(p_cmd);
      break;

    case BOOT_CMD_READ_FIRM_NAME:
      bootCmdReadFirmName(p_cmd);
      break;

    default:
      cmdSendResp(p_cmd, p_cmd->rx_packet.cmd, BOOT_ERR_WRONG_CMD, NULL, 0);
      break;
  }
}




void bootCmdLedControl(cmd_t *p_cmd)
{
  uint8_t err_code = CMD_OK;

  cmd_packet_t *p_packet;
  p_packet = &p_cmd->rx_packet;


  if (p_packet->data[0] == 1)
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // low가 on임
  }
  else if (p_packet->data[0] == 2)
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET); // high off 임
  }
  else if (p_packet->data[0] == 3)
  {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  }
  else
  {
    err_code = BOOT_ERR_LED;
  }

  cmdSendResp(p_cmd, BOOT_CMD_LED_CONTROL, err_code, NULL, 1);
}

void bootCmdReadBootVersion(cmd_t *p_cmd)
{
  cmdSendResp(p_cmd, BOOT_CMD_READ_BOOT_VERSION, CMD_OK, (uint8_t *)p_boot_ver->version, 32);
}

void bootCmdReadBootName(cmd_t *p_cmd)
{
  cmdSendResp(p_cmd, BOOT_CMD_READ_BOOT_NAME, CMD_OK, (uint8_t *)p_boot_ver->name, 32);
}

void bootCmdReadFirmVersion(cmd_t *p_cmd)
{
 // 나중에 Flash 영역에 펌웨어 버전을 쓸 경우 사용	현재 아래는 firm_ver 배열형태로 구현한것임 //
 // cmdSendResp(p_cmd, BOOT_CMD_READ_FIRM_VERSION, CMD_OK, (uint8_t *)p_firm_ver->version, 32);
  cmdSendResp(p_cmd, BOOT_CMD_READ_FIRM_VERSION, CMD_OK, firm_ver, 32);
}

void bootCmdReadFirmName(cmd_t *p_cmd)
{
// 나중에 Flash 영역에 펌웨어 이름을 쓸 경우 사용	현재 아래는 firm_name 배열형태로 구현한것임 //
 // cmdSendResp(p_cmd, BOOT_CMD_READ_FIRM_NAME, CMD_OK, (uint8_t *)p_firm_ver->name, 32);
  cmdSendResp(p_cmd, BOOT_CMD_READ_FIRM_NAME, CMD_OK, firm_name, 32);
}

