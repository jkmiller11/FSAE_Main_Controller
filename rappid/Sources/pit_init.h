/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : baseconfig
 *
 * Project File           : baseconfig.rsp
 *
 * Revision Number        : 1.0
 *
 * Tool Version           : 1.3.1.6
 *
 * file                   : pit_init.h
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5602B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 18-Aug-2010 23:54:51
 *
 * Created on Date        : 02-Jun-2013 23:16:07
 *
 * Brief Description      : File contains declaration for Periodic Interrupt Timer(PIT)
 *                          initialization function.
 *
 *
 *######################################################################
*/

#ifndef  _PIT_INIT_H
#define  _PIT_INIT_H
/********************  Dependent Include files here **********************/

#include "jdp.h"

/**********************  Function Prototype here *************************/

void pit_init_fnc (void);


#endif  /*_PIT_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/
