/* main.c - ADC_ADC_scan example for MPC56xxS */
/* Description: Converts inputs ANS0, ANS1 using scan mode (continuous) */
/* Rev 1 Oct 26 2009 S Mihalik - initial version */ 
/* Rev 1.1 Mar 15 2010 S Mihalik- simplified initModesAndClock, new header */
/* Copyright Freescale Semiconductor, Inc 2009, 2010. All rights reserved. */

#include "MPC5604B.h" /* Use proper header file */

#define MODE 0 //0 = speed, 1 = torque

#define MAX_TORQUE 200
#define MAX_SPEED 600

#define MAX_ANALOG 1023

#define ENERGIZE_ID 849
#define DEENERGIZE_ID 850
#define TORQUE_ID 848
#define SPEED_ID 592
#define SHUTDOWN_ID 851

#define LOOP_TIME 10000

//Enumeration of states
enum myState {NOT_ENERGIZED = 0, ENERGIZED = 1, SHUTDOWN = 2};
typedef enum myState state;

typedef struct {
	uint32_t ID;
	
	union {
		uint8_t B[8];      /* Data buffer in Bytes (8 bits) */
		uint16_t H[4];     /* Data buffer in Half-words (16 bits) */
		uint32_t W[2];     /* Data buffer in words (32 bits) */
		uint32_t R[2];     /* Data buffer in words (32 bits) */
	} DATA;
} CanPacket;

CanPacket energizePacket;
CanPacket deenergizePacket;
CanPacket torquePacket;
CanPacket speedPacket;
CanPacket shutdownPacket;


state currentState =  NOT_ENERGIZED;
uint16_t analog0, analog1;
int16_t torque;
int16_t speed;
vuint32_t i = 0;                      /* Dummy idle counter */
uint16_t RecDataMaster = 0;           /* Data recieved on master SPI */
uint8_t energizeButton = 1;
uint8_t prevEnergizeButton = 1;
int16_t analogError = 0;

uint16_t imp_count = 0;


void initModesAndClock(void) {
	ME.MER.R = 0x0000001D;          	/* Enable DRUN, RUN0, SAFE, RESET modes */
	                              		/* Initialize PLL before turning it on: */
										/* Use 1 of the next 2 lines depending on crystal frequency: */
	CGM.FMPLL_CR.R = 0x02400100;    	/* 8 MHz xtal: Set PLL0 to 64 MHz */   
	/*CGM.FMPLL_R = 0x12400100;*/     	/* 40 MHz xtal: Set PLL0 to 64 MHz */   
	ME.RUN[0].R = 0x001F0074;       	/* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */
	
	//ME.RUNPC[0].R = 0x00000010; 	  	/* Peri. Cfg. 0 settings: only run in RUN0 mode */
   										/* Use the next lines as needed for MPC56xxB/S: */  	    	
	//ME.PCTL[48].R = 0x0000;         	/* MPC56xxB LINFlex0: select ME.RUNPC[0] */	
	//ME.PCTL[68].R = 0x0000;         	/* MPC56xxB/S SIUL:  select ME.RUNPC[0] */	
	
	ME.RUNPC[1].R = 0x00000010;     	/* Peri. Cfg. 1 settings: only run in RUN0 mode */
	ME.PCTL[32].R = 0x01;       		/* MPC56xxB ADC 0: select ME.RUNPC[1] */
  	ME.PCTL[57].R = 0x01;       		/* MPC56xxB CTUL: select ME.RUNPC[1] */
  	ME.PCTL[48].R = 0x01;           	/* MPC56xxB/P/S LINFlex 0: select ME.RUNPC[1] */
	ME.PCTL[68].R = 0x01;           	/* MPC56xxB/S SIUL:  select ME.RUNPC[1] */
	ME.PCTL[72].R = 0x01;           	/* MPC56xxB/S EMIOS 0:  select ME.RUNPC[1] */
	
	//can stuff
	ME.PCTL[4].R = 0x01;            /* MPC56xxB/P/S DSPI0:  select ME.RUNPC[1] */	
	ME.PCTL[5].R = 0x01;            /* MPC56xxB/P/S DSPI1:  select ME.RUNPC[1] */	
	ME.PCTL[17].R = 0x01;           /* MPC56xxB/S FlexCAN1:  select ME.RUNPC[1] */	
	  
	                              		/* Mode Transition to enter RUN0 mode: */
	ME.MCTL.R = 0x40005AF0;         	/* Enter RUN0 Mode & Key */
	ME.MCTL.R = 0x4000A50F;         	/* Enter RUN0 Mode & Inverted Key */  
	while (ME.GS.B.S_MTRANS) {}     	/* Wait for mode transition to complete */    
	                          			/* Note: could wait here using timer and/or I_TC IRQ */
	while(ME.GS.B.S_CURRENTMODE != 4) {}/* Verify RUN0 is the current mode */
	
	//while (ME.IS.B.I_MTC != 1) {}    /* Wait for mode transition to complete */    
	//ME.IS.R = 0x00000001;           /* Clear Transition flag */ 
}

void initPeriClkGen(void) {
	CGM.SC_DC[0].R = 0x80; 				/* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
	CGM.SC_DC[1].R = 0x80;			    /* MPC56xxB/S: Enable peri set 2 sysclk divided by 1 */
	CGM.SC_DC[2].R = 0x80;         		/* MPC56xxB: Enable peri set 3 sysclk divided by 1*/
}

void disableWatchdog(void) {
	SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
	SWT.SR.R = 0x0000d928; 
	SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}

void initCAN_1 (void) {
	uint8_t   i;
	
	CAN_1.MCR.R = 0x5000003F;       /* Put in Freeze Mode & enable all 64 msg bufs */
	CAN_1.CR.R = 0x00DB0006;        /* Configure for 8MHz OSC, 100KHz bit time */
	for (i=0; i<64; i++) {
		CAN_1.BUF[i].CS.B.CODE = 0;   /* Inactivate all message buffers */
	} 
	CAN_1.BUF[0].CS.B.CODE = 8;     /* Message Buffer 0 set to TX INACTIVE */
	
	SIU.PCR[42].R = 0x0624;         /* MPC56xxB: Config port C10 as CAN1TX, open drain */
	SIU.PCR[43].R = 0x0100;         /* MPC56xxB: Configure port C11 as CAN1RX */
	SIU.PSMI[0].R = 0x01;           /* MPC56xxB: Select PCR 43 for CAN1RX Input */  
	CAN_1.MCR.R = 0x0000003F;       /* Negate FlexCAN 0 halt state for 64 MB */
}

//void TransmitMsg (void) {
//	uint8_t	i;
//	
//	union {
//		int8_t B[8];      /* Data buffer in Bytes (8 bits) */
//		int16_t H[4];     /* Data buffer in Half-words (16 bits) */
//		int32_t W[2];     /* Data buffer in words (32 bits) */
//		int32_t R[2];     /* Data buffer in words (32 bits) */
//	} TxData;
//	
//	TxData.W[0] = 0;
//	TxData.W[1] = 0;
//	
//	if (MODE == 1) {
//		TxData.H[3] = torque;  /* Transmit string*/
//	} else {
//		TxData.H[3] = speed;  /* Transmit string*/
//	}
//	CAN_1.BUF[0].CS.B.IDE = 0;           /* Use standard ID length */
//	if (MODE == 1) {
//		CAN_1.BUF[0].ID.B.STD_ID = 592;      /* Transmit ID is 592 */
//	} else {
//		CAN_1.BUF[0].ID.B.STD_ID = 848;      /* Transmit ID is 848 */
//	}
//	CAN_1.BUF[0].CS.B.RTR = 0;           /* Data frame, not remote Tx request frame */
//	CAN_1.BUF[0].CS.B.LENGTH = sizeof(TxData); /* # bytes to transmit w/o null */
//	for (i=0; i<sizeof(TxData); i++) {
//		CAN_1.BUF[0].DATA.B[i] = TxData.B[sizeof(TxData) - i - 1];      /* Data to be transmitted */
//	}
//	CAN_1.BUF[0].CS.B.SRR = 1;           /* Tx frame (not req'd for standard frame)*/
//	CAN_1.BUF[0].CS.B.CODE =0xC;         /* Activate msg. buf. to transmit data frame */
//}

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


void ReadDataDSPI_1(void) {
	while (DSPI_1.SR.B.RFDF != 1){}  /* Wait for Receive FIFO Drain Flag = 1 */
	RecDataMaster = DSPI_1.POPR.R;    /* Read data received by slave SPI */
	DSPI_1.SR.R = 0x80020000;        /* Clear TCF, RDRF flags by writing 1 to them */
}

void initADC() {
	SIU.PCR[24].R = 0x2000; // PB[8]
	SIU.PCR[25].R = 0x2000; // PB[9]
	//SIU.PCR[26].R = 0x2000; /* MPC56xxS: Initialize PC[2] as ANS2 */
	ADC.MCR.R = 0x20000000; /* Initialize ADC0 for scan mode */
	ADC.NCMR[1].R = 0x00000007; /* Select ANS0:2 inputs for conversion */
	ADC.CTR[1].R = 0x00008606; /* Conversion times for 32MHz ADClock */
	ADC.MCR.B.NSTART=1; /* Trigger normal conversions for ADC0 */
}

void getVoltage(void) {
	while (ADC.CDR[33].B.VALID != 1) {}; /* Wait for last scan to complete */
	analog0 = (MAX_ANALOG - ADC.CDR[32].B.CDATA); /* Read ANS0 conversion result data */
	analog1 = (MAX_ANALOG - ADC.CDR[33].B.CDATA); /* Read ANS1 conversion result data */
}

void initLED() {
	SIU.PCR[68].R = 0x0200;				/* Program the drive enable pin of LED1 (PE4) as output*/
	SIU.PCR[69].R = 0x0200;				/* Program the drive enable pin of LED2 (PE5) as output*/
	SIU.PCR[70].R = 0x0200;				/* Program the drive enable pin of LED3 (PE6) as output*/
	SIU.PCR[71].R = 0x0200;				/* Program the drive enable pin of LED4 (PE7) as output*/
}

void initShutdownOutput() {
	SIU.PCR[0].R = 0x0200;
	SIU.GPDO[0].R = 0;
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

void convertTorque() {
	torque = (MAX_TORQUE * ((analog0 + analog1)/2)) / MAX_ANALOG;
	torquePacket.DATA.W[0] = 0;
	torquePacket.DATA.W[1] = 0;
	torquePacket.DATA.H[3] = torque;
}

void convertSpeed() {
	speed = ((MAX_SPEED * ((analog0 + analog1)/2)) / MAX_ANALOG);
	if (speed < 60) {
		speed = 0;
	}
	speedPacket.DATA.W[0] = 0;
	speedPacket.DATA.W[1] = 0;
	speedPacket.DATA.H[3] = speed;
}

void initEnergizeButton() {
	SIU.PCR[64].B.SME = 0;
	SIU.PCR[64].B.APC = 0;
	SIU.PCR[64].B.PA = 0;
	SIU.PCR[64].B.OBE = 0;
	SIU.PCR[64].B.IBE = 1;
	SIU.PCR[64].B.SRC = 0;
	SIU.PCR[64].B.WPE = 0;
	SIU.PCR[64].B.WPS = 1;
}

void getEnergizeButton() {
	energizeButton = SIU.GPDI[64].R;
	//SIU.PGPDO[2].R |= 0x0f000000;
	//SIU.PGPDO[2].R &= ~(energizeButton << 24);
}

void outputToLED(int32_t input) {
	SIU.PGPDO[2].R = ~input;
}

void processVoltage() {
	analog0 = analog0 - (MAX_ANALOG / 10);
	analog1 = analog1 - (MAX_ANALOG / 10);
	
	if ((int16_t) analog0 < 0) {
		analog0 = 0;
	}
	
	if ((int16_t) analog1 < 1) {
		analog1 = 0;
	}
	
	if (analog1 > analog0) {
		analogError = (analog1 - analog0) * 100 / analog0;
	} else {
		analogError = (analog0 - analog1) * 100 / analog1;
	}
	
	if (analogError > 10) {
		imp_count++;
	} else {
		imp_count = 0;
	}
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





void main (void) {
	vuint32_t i = 0;
	initModesAndClock(); /* Initialize mode entries and system clock */
	disableWatchdog(); /* Disable watchdog */
	initPeriClkGen(); /* Initialize peripheral clock generation for DSPIs */
	initADC();
	initLED();
	
	initShutdownOutput();
	
	//can stuff
	initPeriClkGen();            /* Initize peripheral clock generation for DSPIs */
	
	initDSPI_1();                /* Initialize DSPI_1 as Slave SPI and init CTAR0 */
	
	
	canSetup();
	
	initEnergizeButton();
	
	energizePacket.ID = ENERGIZE_ID;
	energizePacket.DATA.W[0] = 0xFFFFFFFF;
	energizePacket.DATA.W[1] = 0xFFFFFFFF;
	
	deenergizePacket.ID = DEENERGIZE_ID;
	deenergizePacket.DATA.W[0] = 0x00000000;
	deenergizePacket.DATA.W[1] = 0x00000000;
	
	torquePacket.ID = TORQUE_ID;
	speedPacket.ID = SPEED_ID;
	
	shutdownPacket.ID = SHUTDOWN_ID;
	shutdownPacket.DATA.W[0] = 0xDEADBEEF;
	shutdownPacket.DATA.W[1] = 0xDEADBEEF;
	
	
	/* Loop forever */
	for (;;) 
	{
		if (i % LOOP_TIME == 0) {
			switch (currentState) {
				case NOT_ENERGIZED:
					if (!energizeButton && prevEnergizeButton) {
						canSend(energizePacket);
						currentState = ENERGIZED;
					} else {
						outputToLED(15 << 24);
					}
					break;
				case ENERGIZED:
					if (!energizeButton && prevEnergizeButton) {
						canSend(deenergizePacket);
						currentState = NOT_ENERGIZED;
					} else {
						getVoltage();
						processVoltage();
						if (imp_count < 2 || ((analog0 + analog1)/2) < 20) {
							convertSpeed();
							convertTorque();
							outputToLED(((analog0 + analog1)/2) << 18);
							if (MODE == 0) {
								canSend(speedPacket);
							} else {
								canSend(torquePacket);
							}
						} else {
							currentState = SHUTDOWN;
							//open shutdown circuit
							canSend(deenergizePacket);
						}
					}
					break;
				case SHUTDOWN:
					outputToLED(0);
					canSend(shutdownPacket);
					SIU.GPDO[0].R = 1;
					break;
			}
			prevEnergizeButton = energizeButton;				
			getEnergizeButton();
		}
		i++;
	}
}
