#include "MPC5604B.h"

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

int main(void) {
  volatile int i = 0;
  
	initModesAndClock(); /* Initialize mode entries and system clock */
	disableWatchdog(); /* Disable watchdog */
	initPeriClkGen(); /* Initialize peripheral clock generation for DSPIs */
  
	SIU.PCR[3].B.SMC = 0;
	SIU.PCR[3].B.APC = 0;
	SIU.PCR[3].B.PA = 0;
	SIU.PCR[3].B.OBE = 0;
	SIU.PCR[3].B.IBE = 1;
	SIU.PCR[3].B.SRC = 0;
	SIU.PCR[3].B.WPE = 0;
	SIU.PCR[3].B.WPS = 1;
	
	SIU.IRER.B.EIRE0 = 1;
	
	
	
	/* Loop forever */
	for (;;) {
		i++;
	}
}



