/*
 * hw_def.h
 *
 *  Created on: Nov 15, 2021
 *      Author: 82109
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_




#include "def.h"
#include "bsp.h"


#define _USE_HW_UART
#define      HW_UART_MAX_CH         2

#define _USE_HW_CLI
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    64

#define _USE_HW_CMD
#define      HW_CMD_MAX_DATA_LENGTH 1024 + 8




//#define _USE_HW_W5500

#endif /* SRC_HW_HW_DEF_H_ */
