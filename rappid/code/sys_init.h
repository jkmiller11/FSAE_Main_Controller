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
 * file                   : sys_init.h
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5604B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 06-Jun-2013 02:49:54
 *
 * Created on Date        : 06-Jun-2013 02:49:57
 *
 * Brief Description      : This file contains system initialization code
 *
 *
 *######################################################################
*/

#ifndef  _SYS_INIT_H
#define  _SYS_INIT_H
/********************  Dependent Include files here **********************/

#include "sysclk_init.h"
#include "adc_init.h"
#include "msr_init.h"
#include "flexcan_init.h"
#include "dspi_init.h"
#include "siu_init.h"
#include "rgm_init.h"
#include "flash_init.h"

/**********************  Function Prototype here *************************/

void sys_init_fnc (void);


#endif  /*_SYS_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

