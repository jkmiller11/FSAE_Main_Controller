/* main.c - ADC_ADC_scan example for MPC56xxS */
/* Description: Converts inputs ANS0, ANS1 using scan mode (continuous) */
/* Rev 1 Oct 26 2009 S Mihalik - initial version */ 
/* Rev 1.1 Mar 15 2010 S Mihalik- simplified initModesAndClock, new header */
/* Copyright Freescale Semiconductor, Inc 2009, 2010. All rights reserved. */

#include "MPC5604B.h" /* Use proper header file */
#include "sys_init.h"
#include "CAN.h"
#include "ADC.h"

#include "definitions.h"

//Enumeration of states
enum myState {NOT_ENERGIZED = 0, ENERGIZED = 1, SHUTDOWN = 2};
typedef enum myState state;

enum myBool {FALSE = 0, TRUE = 1};
typedef enum myBool boolean;



CanPacket energizePacket;
CanPacket deenergizePacket;
CanPacket torquePacket;
CanPacket speedPacket;
CanPacket shutdownPacket;


state currentState =  NOT_ENERGIZED;
uint16_t torque0, torque1, brake0, brake1;
int16_t torque;
int16_t speed;
vuint32_t i = 0;                      /* Dummy idle counter */
uint16_t RecDataMaster = 0;           /* Data recieved on master SPI */
uint8_t energizeButton = 1;
uint8_t prevEnergizeButton = 1;
int16_t analogError = 0;

uint16_t imp_count = 0;

// Receive stuff
uint32_t RxCODE; /* Received message buffer code */
uint32_t RxID; /* Received message ID */
uint32_t RxLENGTH; /* Recieved message number of data bytes */
uint8_t RxDATA[8]; /* Received message data string*/
uint32_t RxTIMESTAMP; /* Received message time */


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


void convertTorque() {
	torque = (MAX_TORQUE * torque0) / MAX_ANALOG;
	torquePacket.DATA.W[0] = 0;
	torquePacket.DATA.W[1] = 0;
	torquePacket.DATA.H[3] = torque;
}

void convertSpeed() {
	speed = ((MAX_SPEED * torque0) / MAX_ANALOG);
	if (speed < 60) {
		speed = 0;
	} else {
		speed = speed - 60;
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
}

void toLED(uint8_t input) {
	SIU.PGPDO[2].R = ~(input << 24);
}

void processAnalog() {
	torque0 = torque0 - (MAX_ANALOG / 10);
	torque1 = torque1 - (MAX_ANALOG / 10);
	
	if ((int16_t) torque0 < 0) {
		torque0 = 0;
	}
	
	if ((int16_t) torque1 < 1) {
		torque1 = 0;
	}
	
	if (torque1 > torque0) {
		analogError = (torque1 - torque0) * 100 / torque0;
	} else {
		analogError = (torque0 - torque1) * 100 / torque1;
	}
	
	if (analogError > 10) {
		imp_count++;
	} else {
		imp_count = 0;
	}
}

void delay() {
	int i;
	for (i = 0; i < DELAY_TIME; i++) {}
}

void initDigitalOut() {
	BUZZER_INIT = 0x0200;
	SHUTDOWN_CIRCUIT_INIT = 0x0200;
	PUMP_INIT = 0x0200;
	BUZZER = FALSE;
	SHUTDOWN_CIRCUIT = FALSE;
	PUMP = TRUE; //???
}

void main (void) {
	vuint32_t i = 0;
	initModesAndClock(); /* Initialize mode entries and system clock */
	disableWatchdog(); /* Disable watchdog */
	initPeriClkGen(); /* Initialize peripheral clock generation for DSPIs */
	
	initADC();
	initLED();
	
	//can stuff	
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
	while (1) 
	{
		prevEnergizeButton = energizeButton;
		getEnergizeButton();
		switch (currentState) {
			case NOT_ENERGIZED:
				if (!energizeButton && prevEnergizeButton) {
					currentState = ENERGIZED;
					canSend(energizePacket);
				}
				break;
			case ENERGIZED:
				if (!energizeButton && prevEnergizeButton) {
					currentState = NOT_ENERGIZED;
					canSend(deenergizePacket);
				} else {
					getADC();
					processAnalog();
					if (imp_count < 2 || torque0 < 20) {
						convertSpeed();
						convertTorque();
						if (MODE == 0) {
							canSend(speedPacket);
						} else {
							canSend(torquePacket);
						}
					} else {
						currentState = SHUTDOWN;
						canSend(deenergizePacket);
					}
				}
				break;
			case SHUTDOWN:
				canSend(shutdownPacket);
				SHUTDOWN_CIRCUIT = TRUE;
				break;
		}
		
		toLED(currentState);
		
		//canReceive();
		
		delay();
		i++;
	}
}
