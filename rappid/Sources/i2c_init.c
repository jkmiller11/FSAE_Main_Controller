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
 * file                   : i2c_init.c
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
 * Brief Description      : File contains I2C initialization. 
 *
 ******************************************************************************** 
 *
 * Detail Description     : File contains function which configures I2C Master/Slave
 *                          mode,Transmit/Receive mode, baud rate, slave address and
 *                          interrupt.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "i2c_init.h"




/********************* Initialization Function(s) *********************** */




void i2c_init_fnc(void)
{

    I2C.IBCR.B.MDIS = 1;
        /* Module Disable : Disabled */


/*-----------------------------------------------------------*/
/*    I2C Frequency Divider Register (I2C_IBFD)            */
/*-----------------------------------------------------------*/
    I2C.IBFD.R = 0x00;
        /* Bus Clock Multiplier : 1*/

/*-----------------------------------------------------------*/
/*    I2C Slave Address (I2C_IBAD)                         */
/*-----------------------------------------------------------*/
    I2C.IBAD.R = 0x00;
            /* Slave Address  : 0*/



/*-----------------------------------------------------------*/
/*    I2C Control Register (I2C_IBCR)                      */
/*-----------------------------------------------------------*/
    I2C.IBCR.R = 0x80;
            /* Module Disable  : Disabled*/
            /* I-Bus Interrupt Enabled  : Disabled*/
            /* Master/Slave Mode  : Slave*/
            /* Transmit/Receive Mode  : Receieve*/
            /* Data acknowledge disable  :  Acknowledge*/
            /* Repeat Start  : Disabled*/

/*-----------------------------------------------------------*/
/*    I2C Bus Interrupt Config Register (I2C_IBIC)         */
/*-----------------------------------------------------------*/
    
    I2C.IBIC.R = 0x00;
        /* Bus idle interrupt : Disabled*/
}
 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

