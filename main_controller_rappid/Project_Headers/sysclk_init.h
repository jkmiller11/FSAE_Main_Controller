/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : fsae_main_controller
 *
 * Project File           : fsae_main_controller.rsp
 *
 * Revision Number        : 1.0
 *
 * Tool Version           : 1.3.1.6
 *
 * file                   : sysclk_init.h
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5604B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 06-Jun-2013 01:34:08
 *
 * Created on Date        : 06-Jun-2013 01:34:09
 *
 * Brief Description      : The file contains declaration for Mode Entry, System Clock,
 *                          CMU initialization functions.
 *
 *
 *######################################################################
*/

#ifndef  _SYSCLK_INIT_H
#define  _SYSCLK_INIT_H

/********************  Dependent Include files here **********************/

#include "jdp.h"

/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Types
******************************************************************************/


/******************************************************************************
* Global variables
******************************************************************************/


/******************************************************************************
* Global functions
******************************************************************************/

void sysclk_module_init_fnc(void);
void mode_entry_init_fnc(void);
void mode_entry_post_config_fnc(void);
void sysclk_init_fnc(void);
void cmu_init_fnc (void);


#endif  /*_SYSCLK_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

