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
 * file                   : intc_init.h
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
 * Brief Description      : This file contains the function prototype for intc source file.
 *
 *
 *######################################################################
*/

#ifndef  _INTC_INIT_H
#define  _INTC_INIT_H
/********************  Dependent Include files here **********************/

#include "jdp.h"



/**********************  Function Prototype here *************************/

extern void intc_init_fnc (void);
extern void en_int_fnc (vuint32_t priority);


#endif  /*_INTC_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

