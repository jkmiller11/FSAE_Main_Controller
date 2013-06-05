/*
 * sys_init.h
 *
 *  Created on: Jun 4, 2013
 *      Author: Jake Miller
 */

#ifndef MPC5604B_H_
#define MPC5604B_H_

#include "MPC5604B.h" /* Use proper header file */

#endif

#ifndef SYS_INIT_H_
#define SYS_INIT_H_

void initModesAndClock(); /* Initialize mode entries and system clock */
void disableWatchdog(); /* Disable watchdog */
void initPeriClkGen(); /* Initialize peripheral clock generation for DSPIs */

#endif /* SYS_INIT_H_ */
