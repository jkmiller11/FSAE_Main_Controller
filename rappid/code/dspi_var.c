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
 * file                   : dspi_var.c
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
 * Brief Description      : This File contains variable definition for Transmit
 *                          and Receive queues
 *
 ******************************************************************************** 
 *
 * Detail Description     : This File contains variables which contain Transmission
 *                         and reception data for respective DSPI module.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "typedefs.h"



vuint32_t DSPI0_TxQUE[1]= {0U};    /* Transmit Queue DSPI_0 Variable */
vuint32_t DSPI1_TxQUE[1]= {0U};    /* Transmit Queue DSPI_1 Variable */
vuint32_t DSPI2_TxQUE[1]= {0U};    /* Transmit Queue DSPI_2 Variable */

vuint16_t DSPI0_RxQUE[1]= {0U };    /* Receive Queue DSPI_0 Variable */
vuint16_t DSPI1_RxQUE[1]= {0U };    /* Receive Queue DSPI_1 Variable */
vuint16_t DSPI2_RxQUE[1]= {0U };    /* Receive Queue DSPI_2 Variable */



 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

