/*
 * definition.h
 *
 *  Created on: Jun 4, 2013
 *      Author: Jake Miller
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define MODE 0 //0 = speed, 1 = torque

#define MAX_TORQUE 200
#define MAX_SPEED 600

#define MAX_ANALOG 1023

#define ENERGIZE_ID 849
#define DEENERGIZE_ID 850
#define TORQUE_ID 848
#define SPEED_ID 592
#define SHUTDOWN_ID 851

#define DELAY_TIME 10000 // 10000 cycles ~ 800 Hz

#define BUZZER_INIT				SIU.PCR[0].R
#define SHUTDOWN_CIRCUIT_INIT	SIU.PCR[2].R
#define PUMP_INIT				SIU.PCR[4].R
#define PWM_INIT				SIU.PCR[8].R

#define BUZZER				SIU.GPDO[0].R // a0
#define SHUTDOWN_CIRCUIT	SIU.GPDO[2].R //a2
#define PUMP				SIU.GPDO[4].R //a4
#define PWM					SIU.GPDO[6].R //a6

#define TORQUE0_INIT	SIU.PCR[80].R
#define TORQUE1_INIT	SIU.PCR[82].R
#define BRAKE0_INIT		SIU.PCR[84].R
#define BRAKE1_INIT		SIU.PCR[86].R

#define TORQUE0		ADC.CDR[40].B.CDATA //f0
#define TORQUE1		ADC.CDR[42].B.CDATA //f2
#define BRAKE0		ADC.CDR[44].B.CDATA //f4
#define BRAKE1		ADC.CDR[46].B.CDATA //f6

#endif /* DEFINITIONS_H_ */
