/*
 * ADC.c
 *
 *  Created on: Jun 4, 2013
 *      Author: Jake Miller
 */

#include "ADC.h"
#include "definitions.h"

extern uint16_t torque0, torque1, brake0, brake1;

void initADC() {
	TORQUE0_INIT = 0x2000;
	TORQUE1_INIT = 0x2000;
	BRAKE0_INIT = 0x2000;
	BRAKE1_INIT = 0x2000;
	ADC.MCR.R = 0x20000000; /* Initialize ADC0 for scan mode */
	ADC.NCMR[1].R = 0x00005500; /* Select ANS0:2 inputs for conversion */
	ADC.CTR[1].R = 0x00008606; /* Conversion times for 32MHz ADClock */
	ADC.MCR.B.NSTART=1; /* Trigger normal conversions for ADC0 */
}

void getADC() {
	while (ADC.CDR[46].B.VALID != 1) {}; /* Wait for last scan to complete */
	torque0 = TORQUE0;
	torque1 = TORQUE1;
	brake0 = BRAKE0;
	brake1 = BRAKE1;
}
