/*
 * boot.h
 *
 *  Created on: 2021. 12. 16.
 *      Author: 82109
 */

#ifndef SRC_AP_BOOT_BOOT_H_
#define SRC_AP_BOOT_BOOT_H_



#include "hw.h"

// ERR DEFINE //
#define BOOT_ERR_WRONG_CMD      0x01
#define BOOT_ERR_LED            0x02
#define BOOT_ERR_FLASH_ERASE    0x03
#define BOOT_ERR_WRONG_RANGE    0x04
#define BOOT_ERR_FLASH_WRITE    0x05
#define BOOT_ERR_BUF_OVF        0x06
#define BOOT_ERR_INVALID_FW     0x07
#define BOOT_ERR_FW_CRC         0x08

// CMD DEINFE //
#define BOOT_CMD_READ_BOOT_VERSION      0x00
#define BOOT_CMD_READ_BOOT_NAME         0x01
#define BOOT_CMD_READ_FIRM_VERSION      0x02
#define BOOT_CMD_READ_FIRM_NAME         0x03
#define BOOT_CMD_FLASH_ERASE            0x04
#define BOOT_CMD_FLASH_WRITE            0x05
#define BOOT_CMD_JUMP_TO_FW             0x08
#define BOOT_CMD_LED_CONTROL            0x10

bool bootInit(uint8_t channel, char *port_name, uint32_t baud);
bool bootDeInit(uint8_t channel);


uint8_t bootCmdReadBootVersion( uint8_t *p_version);
uint8_t bootCmdReadBootName(uint8_t *p_str);
uint8_t bootCmdReadFirmVersion(uint8_t *p_version);
uint8_t bootCmdReadFirmName(uint8_t *p_str);
uint8_t bootCmdFlashErase(uint32_t addr, uint32_t length, uint32_t timeout);
uint8_t bootCmdFlashWrite(uint32_t addr, uint8_t *p_data, uint32_t length, uint32_t timeout);
uint8_t bootCmdJumpToFw(void);

#endif /* SRC_AP_BOOT_BOOT_H_ */
