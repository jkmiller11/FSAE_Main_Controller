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
 * file                   : mpu_init.c
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
 * Brief Description      : This File Contains Entry configuration for MPU
 *
 ******************************************************************************** 
 *
 * Detail Description     : This File contains function containing entries
 *                         which defines the regions and master access to the
 *                         regions in supervisor and user mode. It also handles
 *                         enabling of MPU.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "mpu_init.h"




/*********************  Initialization Function(s) ************************/

void mpu_init_fnc(void)
{

    MPU.CESR.B.VLD = 0;
        /* MPU Entries : Invalid*/

}
 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

