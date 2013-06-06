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
 * file                   : sys_init.c
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
 * Brief Description      : This file contains system initialization code
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file contains function which calls respective
 *                         peripheral initialization functions
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "sys_init.h"


/*********************  Initialization Function(s) ************************/

void sys_init_fnc (void)
{

/* ----------------------------------------------------------- */
/*	               System Initialization Functions              */
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/*                  Reset Determination Goes Here             */
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/*	           FlexCAN Initialization Status Flag                 */
/* Variable is provided to contains the status of the FlexCAN     */
/* initialization. This variable can be used by user to determine */
/* if FlexCAN initialization was successfully done                */
/* ----------------------------------------------------------- */
   uint8_t fci_status;

/* ----------------------------------------------------------- */
/*	        Initialize the Reset Generation Module (RGM)             */
/* ----------------------------------------------------------- */
    rgm_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Main Status Register (MSR)             */
/* ----------------------------------------------------------- */
    msr_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the System Clock, Mode Entry (ME) & CMU             */
/* ----------------------------------------------------------- */
    sysclk_module_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Flash Bus Interface Unit (BIU)             */
/* ----------------------------------------------------------- */
    flash_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the FlexCAN             */
/* ----------------------------------------------------------- */
    fci_status = flexcan_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Analog to Digital Converter (ADC)             */
/* ----------------------------------------------------------- */
    adc_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Deserial Serial Peripheral Interface (DSPI)             */
/* ----------------------------------------------------------- */
    dspi_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Mode Entry Post Configuration             */
/* ----------------------------------------------------------- */
    mode_entry_post_config_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the System Integration Unit (SIU)             */
/* ----------------------------------------------------------- */
    siu_init_fnc();


}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

