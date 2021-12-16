/*
 * usb.h
 *
 *  Created on: 2021. 11. 16.
 *      Author: 82109
 */

#ifndef SRC_COMMON_HW_INCLUDE_USB_H_
#define SRC_COMMON_HW_INCLUDE_USB_H_



#include "hw_def.h"

#ifdef _USE_HW_USB

bool usbInit(void);
void usbDeInit(void);


#endif


#endif /* SRC_COMMON_HW_INCLUDE_USB_H_ */
