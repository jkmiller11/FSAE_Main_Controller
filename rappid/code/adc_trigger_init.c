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
 * file                   : adc_trigger_init.c
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
 * Brief Description      : This File contains the utility function used to
 *                          trigger ADC Sampling.
 *
 ******************************************************************************** 
 *
 * Detail Description     : This File contains utility function which can trigger
 *                         Normal & Injected Sampling and Abort Normal and chain
 *                         conversion and power down mode These functions are never
 *                         called by RAppID.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "adc_trigger_init.h"







/*********************  Normal Software Trigger Function ************************/

void adc_normal_start_fnc(void)
{
    ADC.MCR.B.NSTART = 1; 
        /* Starts The Normal ADC Conversion */

}

/*********************  Injected Software Trigger Function ************************/

void adc_injected_start_fnc(void)
{
    ADC.MCR.B.JSTART = 1;
        /* Starts The Injected ADC Conversion */

}

/*********************  Normal Software Conversion  Stop Function ************************/

void adc_normal_stop_fnc(void)
{
    ADC.MCR.B.ABORT = 1; 
        /*  Stops The Normal ADC Conversion */

}

/*********************  Stop ADC Chain Conversion Function ************************/

void adc_chain_stop_fnc(void)
{
    ADC.MCR.B.ABORTCHAIN = 1; 
        /*  Stops The ADC chain Conversion */

}

/*********************  Power Down Mode Control Function ************************/

void adc_enter_powerdown_mode(void)
{
    ADC.MCR.B.PWDN = 1; 
        /* Power Down Mode enabled */

}

void adc_exit_powerdown_mode(void)
{
    ADC.MCR.B.PWDN = 0; 
        /* Power Down Mode disabled */

}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

