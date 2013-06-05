/*
 * CAN_init.h
 *
 *  Created on: Jun 4, 2013
 *      Author: Jake Miller
 */

#ifndef MPC5604B_H_
#define MPC5604B_H_

#include "MPC5604B.h" /* Use proper header file */

#endif

#ifndef CAN_H_
#define CAN_H_

typedef struct {
	uint32_t ID;
	
	union {
		uint8_t B[8];      /* Data buffer in Bytes (8 bits) */
		uint16_t H[4];     /* Data buffer in Half-words (16 bits) */
		uint32_t W[2];     /* Data buffer in words (32 bits) */
		uint32_t R[2];     /* Data buffer in words (32 bits) */
	} DATA;
} CanPacket;

void initDSPI_1();
void canSetup();
void ReadDataDSPI_1();
void initCAN_1();
void canSend(CanPacket txPacket);
void RecieveMsg();

#endif /* CAN_H_ */
