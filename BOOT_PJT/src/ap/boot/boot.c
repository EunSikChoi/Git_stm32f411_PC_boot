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
static void bootCmdFlashErase(cmd_t *p_cmd);
static void bootCmdFlashWrite(cmd_t *p_cmd);

static bool bootIsFlashRange(uint32_t addr_begin, uint32_t length);


extern firm_version_t boot_ver;

firm_version_t *p_boot_ver = &boot_ver;
firm_version_t *p_firm_ver = (firm_version_t *)(FLASH_ADDR_FW_VER);
firm_tag_t     *p_firm_tag = (firm_tag_t *)FLASH_ADDR_TAG;

uint8_t firm_ver[32]  = "V12031123R2";  // 임시
uint8_t firm_name[32] = "STM32F411V2";	// 임시

void bootInit(void)
{

}


bool bootVerifyFw(void)
{
  uint32_t *jump_addr = (uint32_t *)(FLASH_ADDR_FW + 4);


  if ((*jump_addr) >= FLASH_ADDR_START && (*jump_addr) <  FLASH_ADDR_END)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//bool bootVerifyCrc(void)
//{
//  uint8_t *p_data;
//  uint16_t fw_crc;
//
//  if (p_firm_tag->magic_number != FLASH_MAGIC_NUMBER)
//  {
//    return false;
//  }
//
//  p_data = (uint8_t *)p_firm_tag->tag_flash_start;
//  fw_crc = 0;
//
//  for (int i=0; i<p_firm_tag->tag_flash_length; i++)
//  {
//    utilUpdateCrc(&fw_crc, p_data[i]);
//  }
//
//  if (fw_crc == p_firm_tag->tag_flash_crc)
//  {
//    return true;
//  }
//  else
//  {
//    return false;
//  }
//}

void bootJumpToFw(void)
{
  void (**jump_func)(void) = (void (**)(void))(FLASH_ADDR_FW + 4);

  bspDeInit();
  (*jump_func)();
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

    case BOOT_CMD_FLASH_ERASE:
      bootCmdFlashErase(p_cmd);
      break;

    case BOOT_CMD_FLASH_WRITE:
      bootCmdFlashWrite(p_cmd);
      break;

    case BOOT_CMD_JUMP_TO_FW:
      bootCmdJumpToFw(p_cmd);
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

bool bootIsFlashRange(uint32_t addr_begin, uint32_t length)
{
  bool ret = false;
  uint32_t addr_end;
  uint32_t flash_start;
  uint32_t flash_end;


  addr_end = addr_begin + length - 1;

  flash_start = FLASH_ADDR_START;
  flash_end   = FLASH_ADDR_END;

  if ((addr_begin >= flash_start) && (addr_begin < flash_end) &&
      (addr_end   >= flash_start) && (addr_end   < flash_end))
  {
    ret = true;
  }


  return ret;
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


void bootCmdFlashErase(cmd_t *p_cmd)
{
  uint8_t err_code = CMD_OK;
  uint32_t addr;
  uint32_t length;
  cmd_packet_t *p_packet;

  p_packet = &p_cmd->rx_packet;


  addr  = (uint32_t)(p_packet->data[0] <<  0);
  addr |= (uint32_t)(p_packet->data[1] <<  8);
  addr |= (uint32_t)(p_packet->data[2] << 16);
  addr |= (uint32_t)(p_packet->data[3] << 24);

  length  = (uint32_t)(p_packet->data[4] <<  0);
  length |= (uint32_t)(p_packet->data[5] <<  8);
  length |= (uint32_t)(p_packet->data[6] << 16);
  length |= (uint32_t)(p_packet->data[7] << 24);


  // 유효한 메모리 영역인지 확인.
  if (bootIsFlashRange(addr, length) == true)
  {
    // 메모리를 지움.
    if (flashErase(addr, length) != true)
    {
      err_code = BOOT_ERR_FLASH_ERASE;
    }
  }
  else
  {
    err_code = BOOT_ERR_WRONG_RANGE;
  }

  cmdSendResp(p_cmd, BOOT_CMD_FLASH_ERASE, err_code, NULL, 0);
}

void bootCmdFlashWrite(cmd_t *p_cmd)
{
  uint8_t err_code = CMD_OK;
  uint32_t addr;
  uint32_t length;
  cmd_packet_t *p_packet;

  p_packet = &p_cmd->rx_packet;


  addr  = (uint32_t)(p_packet->data[0] <<  0);
  addr |= (uint32_t)(p_packet->data[1] <<  8);
  addr |= (uint32_t)(p_packet->data[2] << 16);
  addr |= (uint32_t)(p_packet->data[3] << 24);

  length  = (uint32_t)(p_packet->data[4] <<  0);
  length |= (uint32_t)(p_packet->data[5] <<  8);
  length |= (uint32_t)(p_packet->data[6] << 16);
  length |= (uint32_t)(p_packet->data[7] << 24);


  // 유효한 메모리 영역인지 확인.
  if (bootIsFlashRange(addr, length) == true)  // length는  cli에서 get한 file의 size//
  {
    // 데이터를 Write.
    if (flashWrite(addr, &p_packet->data[8], length) != true) // 8부터가 DATA 바이트임//
    {
      err_code = BOOT_ERR_FLASH_WRITE;
    }
  }
  else
  {
    err_code = BOOT_ERR_WRONG_RANGE;
  }

  cmdSendResp(p_cmd, BOOT_CMD_FLASH_WRITE, err_code, NULL, 0);
}

void bootCmdJumpToFw(cmd_t *p_cmd)
{
  if (bootVerifyFw() == true)
  {
    //if (bootVerifyCrc() == true)
    //{
      cmdSendResp(p_cmd, BOOT_CMD_JUMP_TO_FW, CMD_OK, NULL, 0);
      delay(100);
      bootJumpToFw();
    //}
   // else
   // {
   //   cmdSendResp(p_cmd, BOOT_CMD_JUMP_TO_FW, BOOT_ERR_FW_CRC, NULL, 0);
   // }
  }
  else
  {
    cmdSendResp(p_cmd, BOOT_CMD_JUMP_TO_FW, BOOT_ERR_INVALID_FW, NULL, 0);
  }
}
