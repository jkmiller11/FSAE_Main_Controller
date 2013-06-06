/*
 * CAN_init.c
 *
 *  Created on: Jun 4, 2013
 *      Author: Jake Miller
 */

#include "CAN.h"

extern uint16_t RecDataMaster;           /* Data recieved on master SPI */

extern uint32_t RxCODE; /* Received message buffer code */
extern uint32_t RxID; /* Received message ID */
extern uint32_t RxLENGTH; /* Recieved message number of data bytes */
extern uint8_t RxDATA[8]; /* Received message data string*/
extern uint32_t RxTIMESTAMP; /* Received message time */


void initDSPI_1(void) {
	DSPI_1.MCR.R = 0x80010001;     /* Configure DSPI_1 as master */
	DSPI_1.CTAR[0].R = 0x7A0A7727; /* Configure CTAR0  */
	DSPI_1.MCR.B.HALT = 0x0;	     /* Exit HALT mode: go from STOPPED to RUNNING state*/      
	
	SIU.PCR[112].R = 0x0903;  /* Config pad as DSPI_1 SIN input */
	SIU.PCR[113].R = 0x0A04;  /* Config pad as DSPI_1 SOUT output */
	SIU.PCR[114].R = 0x0A04;  /* Config pad as DSPI_1 SCK output */
	SIU.PCR[115].R = 0x0A04;  /* Config pad as DSPI_1 CS0 output */    
	
	SIU.PSMI[7].R = 2;  /* Select PCR 114 for SCK */
	SIU.PSMI[8].R = 2;  /* Select PCR 112 for SIN */
	SIU.PSMI[9].R = 3;  /* Select PCR 115 
 CS0 */
}

void canSetup() {
	//AFTER POWER UP DEVICE IS IN INIT MODE
	DSPI_1.PUSHR.R = 0x0001DF80; // read  BAT FAIL
	ReadDataDSPI_1();          
	DSPI_1.PUSHR.R = 0x00011D80; // read  mode
	ReadDataDSPI_1();         
	DSPI_1.PUSHR.R = 0x00014C00; // write Init W/D  (simple W/D time out)
	ReadDataDSPI_1();          
	DSPI_1.PUSHR.R = 0x00010D00; // read  init W/D
	ReadDataDSPI_1();
	DSPI_1.PUSHR.R = 0x00014E28; // write init LIN
	ReadDataDSPI_1(); 
	DSPI_1.PUSHR.R = 0x00010F00; // read init LIN
	ReadDataDSPI_1(); 
	DSPI_1.PUSHR.R = 0x00015A00; // write normal mode
	ReadDataDSPI_1(); 
	//DEVICE IS IN NORMAL MODE
	DSPI_1.PUSHR.R = 0x00011D80; // read device mode
	ReadDataDSPI_1();
	DSPI_1.PUSHR.R = 0x00015A00; // W/D refresh
	ReadDataDSPI_1();
	//CONFIGURATION OF CAN/LIN
	DSPI_1.PUSHR.R = 0x000160C0; // write CAN
	ReadDataDSPI_1();
	DSPI_1.PUSHR.R = 0x00012100; // read CAN
	ReadDataDSPI_1();
	DSPI_1.PUSHR.R = 0x000166C0; // write LIN1
	ReadDataDSPI_1();
	DSPI_1.PUSHR.R = 0x00012700; // read LIN1
	ReadDataDSPI_1();
	DSPI_1.PUSHR.R = 0x000168C0; // write LIN1
	ReadDataDSPI_1();
	DSPI_1.PUSHR.R = 0x00012900; // read LIN1
	ReadDataDSPI_1();
					  
	initCAN_1();             /* Initialize FlexCAN 0 & one of its buffers for transmit*/
}

void ReadDataDSPI_1(void) {
	while (DSPI_1.SR.B.RFDF != 1){}  /* Wait for Receive FIFO Drain Flag = 1 */
	RecDataMaster = DSPI_1.POPR.R;    /* Read data received by slave SPI */
	DSPI_1.SR.R = 0x80020000;        /* Clear TCF, RDRF flags by writing 1 to them */
}

void initCAN_1 (void) {
	uint8_t   i;
	
	CAN_1.MCR.R = 0x5000003F;       /* Put in Freeze Mode & enable all 64 msg bufs */
	CAN_1.CR.R = 0x00DB0006;        /* Configure for 8MHz OSC, 500KHz bit time */
	for (i=0; i<64; i++) {
		CAN_1.BUF[i].CS.B.CODE = 0;   /* Inactivate all message buffers */
	}
	
	CAN_1.BUF[4].CS.B.IDE = 0; /* MB 4 will look for a standard ID */
	CAN_1.BUF[4].ID.B.STD_ID = 555; /* MB 4 will look for ID = 555 */
	CAN_1.BUF[4].CS.B.CODE = 4; /* MB 4 set to RX EMPTY */
	CAN_1.RXGMASK.B.MI = 0x1FFFFFFF; /* Global acceptance mask */
	
	CAN_1.BUF[0].CS.B.CODE = 8;     /* Message Buffer 0 set to TX INACTIVE */
	SIU.PCR[42].R = 0x0624;         /* MPC56xxB: Config port C10 as CAN1TX, open drain */
	SIU.PCR[43].R = 0x0100;         /* MPC56xxB: Configure port C11 as CAN1RX */
	SIU.PSMI[0].R = 0x01;           /* MPC56xxB: Select PCR 43 for CAN1RX Input */  
	CAN_1.MCR.R = 0x0000003F;       /* Negate FlexCAN 0 halt state for 64 MB */
}


void canSend(CanPacket txPacket) {
	uint8_t	i;
	
	CAN_1.BUF[0].CS.B.IDE = 0;           /* Use standard ID length */
	CAN_1.BUF[0].ID.B.STD_ID = txPacket.ID;

	CAN_1.BUF[0].CS.B.RTR = 0;           /* Data frame, not remote Tx request frame */
	CAN_1.BUF[0].CS.B.LENGTH = sizeof(txPacket.DATA); /* # bytes to transmit w/o null */
	for (i=0; i<sizeof(txPacket.DATA); i++) {
		CAN_1.BUF[0].DATA.B[i] = txPacket.DATA.B[sizeof(txPacket.DATA) - i - 1];      /* Data to be transmitted */
	}
	CAN_1.BUF[0].CS.B.SRR = 1;           /* Tx frame (not req'd for standard frame)*/
	CAN_1.BUF[0].CS.B.CODE =0xC;         /* Activate msg. buf. to transmit data frame */
}


void canReceive (void) {
	uint8_t j;
	uint32_t dummy;
	
	CAN_1.BUF[4].CS.B.IDE = 0; /* MB 4 will look for a standard ID */
	CAN_1.BUF[4].ID.B.STD_ID = 555; /* MB 4 will look for ID = 555 */
	CAN_1.BUF[4].CS.B.CODE = 4; /* MB 4 set to RX EMPTY */
	
	while (CAN_1.IFRL.B.BUF04I == 0) {}; /* Wait for CAN 1 MB 4 flag */
	RxCODE = CAN_1.BUF[4].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP */
	RxID = CAN_1.BUF[4].ID.B.STD_ID;
	RxLENGTH = CAN_1.BUF[4].CS.B.LENGTH;
	for (j=0; j<RxLENGTH; j++) { 
		RxDATA[j] = CAN_1.BUF[4].DATA.B[j];
	}
	RxTIMESTAMP = CAN_1.BUF[4].CS.B.TIMESTAMP; 
	dummy = CAN_1.TIMER.R; /* Read TIMER to unlock message buffers */ 
	CAN_1.IFRL.R = 0x00000010; /* Clear CAN 1 MB 4 flag */
}
