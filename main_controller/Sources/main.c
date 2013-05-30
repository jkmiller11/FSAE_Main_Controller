/* main.c - ADC_ADC_scan example for MPC56xxS */
/* Description: Converts inputs ANS0, ANS1 using scan mode (continuous) */
/* Rev 1 Oct 26 2009 S Mihalik - initial version */ 
/* Rev 1.1 Mar 15 2010 S Mihalik- simplified initModesAndClock, new header */
/* Copyright Freescale Semiconductor, Inc 2009, 2010. All rights reserved. */

#include "MPC5604B.h" /* Use proper header file */
uint16_t result;

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
	                              		/* Mode Transition to enter RUN0 mode: */
	ME.MCTL.R = 0x40005AF0;         	/* Enter RUN0 Mode & Key */
	ME.MCTL.R = 0x4000A50F;         	/* Enter RUN0 Mode & Inverted Key */  
	while (ME.GS.B.S_MTRANS) {}     	/* Wait for mode transition to complete */    
	                          			/* Note: could wait here using timer and/or I_TC IRQ */
	while(ME.GS.B.S_CURRENTMODE != 4) {}/* Verify RUN0 is the current mode */
	
	//while (ME.IS.B.I_MTC != 1) {}    /* Wait for mode transition to complete */    
	//ME.IS.R = 0x00000001;           /* Clear Transition flag */ 
}

void disableWatchdog(void) {
	SWT.SR.R = 0x0000c520;     			/* Write keys to clear soft lock bit */
  	SWT.SR.R = 0x0000d928; 
  	SWT.CR.R = 0x8000010A;     			/* Clear watchdog enable (WEN) */
}

void initPeriClkGen(void) {
	CGM.SC_DC[0].R = 0x80; 				/* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
  	CGM.SC_DC[2].R = 0x80;         		/* MPC56xxB: Enable peri set 3 sysclk divided by 1*/
}

void initADC() {
	SIU.PCR[24].R = 0x2000; /* MPC56xxS: Initialize PC[0] as ANS0 */
	//SIU.PCR[25].R = 0x2000; /* MPC56xxS: Initialize PC[1] as ANS1 */
	//SIU.PCR[26].R = 0x2000; /* MPC56xxS: Initialize PC[2] as ANS2 */
	ADC.MCR.R = 0x20000000; /* Initialize ADC0 for scan mode */
	ADC.NCMR[1].R = 0x00000007; /* Select ANS0:2 inputs for conversion */
	ADC.CTR[1].R = 0x00008606; /* Conversion times for 32MHz ADClock */
	ADC.MCR.B.NSTART=1; /* Trigger normal conversions for ADC0 */
}

void getVoltage(void) {
	while (ADC.CDR[33].B.VALID != 1) {}; /* Wait for last scan to complete */
	result = ADC.CDR[32].B.CDATA; /* Read ANS0 conversion result data */
}

void initLED() {
	SIU.PCR[68].R = 0x0200;				/* Program the drive enable pin of LED1 (PE4) as output*/
	SIU.PCR[69].R = 0x0200;				/* Program the drive enable pin of LED2 (PE5) as output*/
	SIU.PCR[70].R = 0x0200;				/* Program the drive enable pin of LED3 (PE6) as output*/
	SIU.PCR[71].R = 0x0200;				/* Program the drive enable pin of LED4 (PE7) as output*/
}

void toLED(void) {
	SIU.PGPDO[2].R |= 0x0f000000;		/* Disable LEDs*/
	SIU.PGPDO[2].R &= result << 18;		/* Enable LED1*/
}

void main (void) {
	vuint32_t i = 0;
	initModesAndClock(); /* Initialize mode entries and system clock */
	disableWatchdog(); /* Disable watchdog */
	initPeriClkGen(); /* Initialize peripheral clock generation for DSPIs */
	initADC();
	initLED();
	
	/* Loop forever */
	for (;;) 
	{
		getVoltage();
		toLED();
		i++;
	}
}
