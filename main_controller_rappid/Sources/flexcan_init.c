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
 * file                   : flexcan_init.c
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
 * Brief Description      : This file contains FlexCAN register configuration
 *                          in freeze mode
 *
 ******************************************************************************** 
 *
 * Detail Description     : File contains functions where each FlexCAN configuration
 *                         for maximum number of MBs, CAN speed, different
 *                         operating modes, Receive Mask and Interrupt Mask
 *                         can be done in freeze mode.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "flexcan_init.h"


/*********************  Initialization Function(s) ************************/

uint8_t flexcan_init_fnc(void)
{
   uint8_t init_status = 0;

   init_status += flexcan_0_init_fnc();
   init_status += 2*flexcan_1_init_fnc();
   init_status += 4*flexcan_2_init_fnc();

   return init_status;
}
/*********************  CAN_0 Initialization Function(s) ************************/

uint8_t flexcan_0_init_fnc(void)
{

    uint16_t i, x;
    uint8_t status;
    volatile uint16_t j;

    /*Enable the CAN module */
    CAN_0.MCR.B.MDIS    = 0;

    /* Reset FlexCAN Module */
    CAN_0.MCR.B.SOFTRST = 1;
    while( CAN_0.MCR.B.SOFTRST ==1){}

    /*Disable the CAN module */
    CAN_0.MCR.B.MDIS    = 1;

    /* Set CAN clock source 1: bus , 0: oscillator */
    CAN_0.CR.B.CLKSRC   = 0;

    /*Enable the CAN module */
    CAN_0.MCR.B.MDIS    = 1;

    /* Set FRZ bit */
    CAN_0.MCR.B.FRZ   = 1;
    /* Set HALT bit */
    CAN_0.MCR.B.HALT  = 1;

/* ----------------------------------------------------------- */
/*                   CAN_0.MCR Control Register                          */
/* ----------------------------------------------------------- */
    CAN_0.MCR.R = 0xD080000F;
    /* Disable the FlexCAN module: 1*/
    /* Freeze Enable :1*/
    /* FIFO Enable :0*/
    /* Halt : 1*/
    /* Self Reception : 0*/
    /* Supervisor Mode : 0*/
    /* Warning Interrupt Enable : 0*/
    /* Backwards Compatibility Configuration : 0*/
    /* Local Priority Enable : 0*/
    /* Abort Enable : 0*/
    /* ID Acceptance Mode : 0*/
    /* Maximum Number of Message Buffers : 15*/

/* ----------------------------------------------------------- */
/*    CAN_0.CR Control register                                */
/* ----------------------------------------------------------- */
    CAN_0.CR.R  = 0x041B0006;
    /* Bus -Off Interrupt Mask: Disabled         */
    /* CAN bit Sampling Mode: 1 Sample           */
    /* CAN Error Interrupt Mask: Disabled        */
    /* CLOCK Source: Oscillator                  */
    /* Listen Only Mode: Disabled                */
    /* Loop Back Mode: Disabled                  */
    /* Bus off Recovery: Enabled                 */
    /* Lowest Buffer Transfer First: Disabled    */
    /* Phase Segment1: 4                         */
    /* Phase Segment2: 4                         */
    /* Prescalar Division Factor: 5              */
    /* Propagation Segment: 7                    */
    /* Resynchronization Jump Width: 1           */
    /* Timer Synch Mode: Disabled                */



    /* Set the FlexCAN Maximum Buffer Number */
    CAN_0.MCR.B.MAXMB  = 15;


    /* clear memory from message buffer 0 to 15 */
    for(x=0; x < 16; x++)
    {
        CAN_0.BUF[x].CS.R = 0;
        CAN_0.BUF[x].ID.R = 0;
        for(i=0; i < 2; i++) 
        {
            CAN_0.BUF[x].DATA.W[i] = 0;
        }
    }

/* ----------------------------------------------------------- */
/*    CAN_0.RXGMASK global mask                                */
/* ----------------------------------------------------------- */
    CAN_0.RXGMASK.R  = 0xFFFFFFFF;

/* ----------------------------------------------------------- */
/*    CAN_0.RX14MASK buffer 14 mask                             */
/* ----------------------------------------------------------- */
    CAN_0.RX14MASK.R  = 0xFFFFFFFF;

/* ----------------------------------------------------------- */
/*    CAN_0.RX15MASK  buffer 15 mask                            */
/* ----------------------------------------------------------- */
    CAN_0.RX15MASK.R  = 0xFFFFFFFF;


/* ----------------------------------------------------------- */
/*    CAN_0.IMRH Interrupt masks high register                  */
/* ----------------------------------------------------------- */
    CAN_0.IMRH.R  = 0x00000000;

/* ----------------------------------------------------------- */
/*    CAN_0.IMRL Interrupt masks low register                  */
/* ----------------------------------------------------------- */
    CAN_0.IMRL.R  = 0x00000000;

    /* Negate the HALT and the FREEZE bit to let the FlexCAN synchronize. */
    /* Exit and Disable freeze mode */
    CAN_0.MCR.B.HALT  =  1;
    CAN_0.MCR.B.FRZ   =  1;
    

    /* await synchronization (delay) */
    for(j=1; j < 255; j++){}

    if(CAN_0.MCR.B.NOTRDY == 1)
    {
       status = 1;
    }
    else
    {
       status = 0;
    }


    return status;

}
/*********************  CAN_1 Initialization Function(s) ************************/

uint8_t flexcan_1_init_fnc(void)
{

    uint16_t i, x;
    uint8_t status;
    volatile uint16_t j;

    /*Enable the CAN module */
    CAN_1.MCR.B.MDIS    = 0;

    /* Reset FlexCAN Module */
    CAN_1.MCR.B.SOFTRST = 1;
    while( CAN_1.MCR.B.SOFTRST ==1){}

    /*Disable the CAN module */
    CAN_1.MCR.B.MDIS    = 1;

    /* Set CAN clock source 1: bus , 0: oscillator */
    CAN_1.CR.B.CLKSRC   = 0;

    /*Enable the CAN module */
    CAN_1.MCR.B.MDIS    = 0;

    /* Set FRZ bit */
    CAN_1.MCR.B.FRZ   = 1;
    /* Set HALT bit */
    CAN_1.MCR.B.HALT  = 1;

/* ----------------------------------------------------------- */
/*                   CAN_1.MCR Control Register                          */
/* ----------------------------------------------------------- */
    CAN_1.MCR.R = 0x5080000F;
    /* Enable the FlexCAN module: 0*/
    /* Freeze Enable :1*/
    /* FIFO Enable :0*/
    /* Halt : 1*/
    /* Self Reception : 0*/
    /* Supervisor Mode : 0*/
    /* Warning Interrupt Enable : 0*/
    /* Backwards Compatibility Configuration : 0*/
    /* Local Priority Enable : 0*/
    /* Abort Enable : 0*/
    /* ID Acceptance Mode : 0*/
    /* Maximum Number of Message Buffers : 15*/

/* ----------------------------------------------------------- */
/*    CAN_1.CR Control register                                */
/* ----------------------------------------------------------- */
    CAN_1.CR.R  = 0x001B0006;
    /* Bus -Off Interrupt Mask: Disabled         */
    /* CAN bit Sampling Mode: 1 Sample           */
    /* CAN Error Interrupt Mask: Disabled        */
    /* CLOCK Source: Oscillator                  */
    /* Listen Only Mode: Disabled                */
    /* Loop Back Mode: Disabled                  */
    /* Bus off Recovery: Enabled                 */
    /* Lowest Buffer Transfer First: Disabled    */
    /* Phase Segment1: 4                         */
    /* Phase Segment2: 4                         */
    /* Prescalar Division Factor: 1              */
    /* Propagation Segment: 7                    */
    /* Resynchronization Jump Width: 1           */
    /* Timer Synch Mode: Disabled                */



    /* Set the FlexCAN Maximum Buffer Number */
    CAN_1.MCR.B.MAXMB  = 15;


    /* clear memory from message buffer 0 to 15 */
    for(x=0; x < 16; x++)
    {
        CAN_1.BUF[x].CS.R = 0;
        CAN_1.BUF[x].ID.R = 0;
        for(i=0; i < 2; i++) 
        {
            CAN_1.BUF[x].DATA.W[i] = 0;
        }
    }

/* ----------------------------------------------------------- */
/*    CAN_1.RXGMASK global mask                                */
/* ----------------------------------------------------------- */
    CAN_1.RXGMASK.R  = 0xFFFFFFFF;

/* ----------------------------------------------------------- */
/*    CAN_1.RX14MASK buffer 14 mask                             */
/* ----------------------------------------------------------- */
    CAN_1.RX14MASK.R  = 0xFFFFFFFF;

/* ----------------------------------------------------------- */
/*    CAN_1.RX15MASK  buffer 15 mask                            */
/* ----------------------------------------------------------- */
    CAN_1.RX15MASK.R  = 0xFFFFFFFF;


/* ----------------------------------------------------------- */
/*    CAN_1.IMRH Interrupt masks high register                  */
/* ----------------------------------------------------------- */
    CAN_1.IMRH.R  = 0x00000000;

/* ----------------------------------------------------------- */
/*    CAN_1.IMRL Interrupt masks low register                  */
/* ----------------------------------------------------------- */
    CAN_1.IMRL.R  = 0x00000000;

    /* Negate the HALT and the FREEZE bit to let the FlexCAN synchronize. */
    /* Exit and Disable freeze mode */
    CAN_1.MCR.B.HALT  =  1;
    CAN_1.MCR.B.FRZ   =  1;
    

    /* await synchronization (delay) */
    for(j=1; j < 255; j++){}

    if(CAN_1.MCR.B.NOTRDY == 1)
    {
       status = 1;
    }
    else
    {
       status = 0;
    }


    return status;

}
/*********************  CAN_2 Initialization Function(s) ************************/

uint8_t flexcan_2_init_fnc(void)
{

    uint16_t i, x;
    uint8_t status;
    volatile uint16_t j;

    /*Enable the CAN module */
    CAN_2.MCR.B.MDIS    = 0;

    /* Reset FlexCAN Module */
    CAN_2.MCR.B.SOFTRST = 1;
    while( CAN_2.MCR.B.SOFTRST ==1){}

    /*Disable the CAN module */
    CAN_2.MCR.B.MDIS    = 1;

    /* Set CAN clock source 1: bus , 0: oscillator */
    CAN_2.CR.B.CLKSRC   = 0;

    /*Enable the CAN module */
    CAN_2.MCR.B.MDIS    = 1;

    /* Set FRZ bit */
    CAN_2.MCR.B.FRZ   = 1;
    /* Set HALT bit */
    CAN_2.MCR.B.HALT  = 1;

/* ----------------------------------------------------------- */
/*                   CAN_2.MCR Control Register                          */
/* ----------------------------------------------------------- */
    CAN_2.MCR.R = 0xD080000F;
    /* Disable the FlexCAN module: 1*/
    /* Freeze Enable :1*/
    /* FIFO Enable :0*/
    /* Halt : 1*/
    /* Self Reception : 0*/
    /* Supervisor Mode : 0*/
    /* Warning Interrupt Enable : 0*/
    /* Backwards Compatibility Configuration : 0*/
    /* Local Priority Enable : 0*/
    /* Abort Enable : 0*/
    /* ID Acceptance Mode : 0*/
    /* Maximum Number of Message Buffers : 15*/

/* ----------------------------------------------------------- */
/*    CAN_2.CR Control register                                */
/* ----------------------------------------------------------- */
    CAN_2.CR.R  = 0x041B0006;
    /* Bus -Off Interrupt Mask: Disabled         */
    /* CAN bit Sampling Mode: 1 Sample           */
    /* CAN Error Interrupt Mask: Disabled        */
    /* CLOCK Source: Oscillator                  */
    /* Listen Only Mode: Disabled                */
    /* Loop Back Mode: Disabled                  */
    /* Bus off Recovery: Enabled                 */
    /* Lowest Buffer Transfer First: Disabled    */
    /* Phase Segment1: 4                         */
    /* Phase Segment2: 4                         */
    /* Prescalar Division Factor: 5              */
    /* Propagation Segment: 7                    */
    /* Resynchronization Jump Width: 1           */
    /* Timer Synch Mode: Disabled                */



    /* Set the FlexCAN Maximum Buffer Number */
    CAN_2.MCR.B.MAXMB  = 15;


    /* clear memory from message buffer 0 to 15 */
    for(x=0; x < 16; x++)
    {
        CAN_2.BUF[x].CS.R = 0;
        CAN_2.BUF[x].ID.R = 0;
        for(i=0; i < 2; i++) 
        {
            CAN_2.BUF[x].DATA.W[i] = 0;
        }
    }

/* ----------------------------------------------------------- */
/*    CAN_2.RXGMASK global mask                                */
/* ----------------------------------------------------------- */
    CAN_2.RXGMASK.R  = 0xFFFFFFFF;

/* ----------------------------------------------------------- */
/*    CAN_2.RX14MASK buffer 14 mask                             */
/* ----------------------------------------------------------- */
    CAN_2.RX14MASK.R  = 0xFFFFFFFF;

/* ----------------------------------------------------------- */
/*    CAN_2.RX15MASK  buffer 15 mask                            */
/* ----------------------------------------------------------- */
    CAN_2.RX15MASK.R  = 0xFFFFFFFF;


/* ----------------------------------------------------------- */
/*    CAN_2.IMRH Interrupt masks high register                  */
/* ----------------------------------------------------------- */
    CAN_2.IMRH.R  = 0x00000000;

/* ----------------------------------------------------------- */
/*    CAN_2.IMRL Interrupt masks low register                  */
/* ----------------------------------------------------------- */
    CAN_2.IMRL.R  = 0x00000000;

    /* Negate the HALT and the FREEZE bit to let the FlexCAN synchronize. */
    /* Exit and Disable freeze mode */
    CAN_2.MCR.B.HALT  =  1;
    CAN_2.MCR.B.FRZ   =  1;
    

    /* await synchronization (delay) */
    for(j=1; j < 255; j++){}

    if(CAN_2.MCR.B.NOTRDY == 1)
    {
       status = 1;
    }
    else
    {
       status = 0;
    }


    return status;

}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

