/*
 * qbuffer.h
 *
 *  Created on: 2021. 11. 16.
 *      Author: 82109
 */

#ifndef SRC_COMMON_CORE_QBUFFER_H_
#define SRC_COMMON_CORE_QBUFFER_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"

typedef struct
{
  uint32_t in;
  uint32_t out;
  uint32_t len;
  uint32_t size;
  uint8_t *p_buf;

}qbuffer_t;



void qbufferInit(void);

void     qbufferInit(void);
bool     qbufferCreate    (qbuffer_t *p_node, uint8_t *p_buf,  uint32_t length);
bool     qbufferWrite     (qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
bool     qbufferRead      (qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
uint32_t qbufferAvailable (qbuffer_t *p_node);
void     qbufferFlush     (qbuffer_t *p_node);



#ifdef __cplusplus
extern }
#endif




#endif /* SRC_COMMON_CORE_QBUFFER_H_ */
