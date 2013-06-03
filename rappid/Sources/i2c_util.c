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
 * file                   : i2c_util.c
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
 * Brief Description      : This File contains I2C start function.
 *
 ******************************************************************************** 
 *
 * Detail Description     : This function generates I2C start condition by making
 *                          Master Transmit mode. It also configures data register
 *                          with calling address.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "i2c_init.h"
#include "rappid_ref.h"




void i2c_start_fnc(void)
{
    while (I2C.IBSR.B.IBB == 1 ) {;} //wait in loop for IBB flag to clear
    I2C.IBCR.R = 0x38;//Master,Transmit, Noack selected
    //Generate start condition
    I2C.IBDR.R = I2C.IBAD.R;// send the calling address to the data register
}
 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

