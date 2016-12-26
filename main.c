/*************************************************************************/
/*                                                                       */
/* FILE NAME VERSION                                                     */
/*                                                                       */
/*      main.c                                                           */
/*                                                                       */
/* COMPONENT                                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/* AUTHOR                                                                */
/*                                                                       */
/*                                                                       */
/* Target                                                                */
/*                                                                       */
/* Compiler                                                              */
/*                                                                       */
/*                                                                       */
/* FUNCTIONS                                                             */
/*                                                                       */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/*        DATE          REMARKS                                          */
/*                                                                       */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

/*-----------------------------------------------------------------------*/
/* include files                                                         */
/*-----------------------------------------------------------------------*/

#include <avr/io.h>
#include "defines.h"
#include "system.h"
#include "appl.h"
#include "main.h"


/*-----------------------------------------------------------------------*/
/* local defines                                                         */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* local typedefs                                                        */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* local enums                                                           */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* local enums                                                           */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* local macros                                                          */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* external variables                                                    */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* global variables                                                      */
/*-----------------------------------------------------------------------*/
FUSES  =
{
  .low = 0xFF
    // & FUSE_CKSEL0  
    // & FUSE_CKSEL1  
    // & FUSE_CKSEL2  
    // & FUSE_CKSEL3  
       & FUSE_SUT0    
    // & FUSE_SUT1    
       & FUSE_BODEN   
       & FUSE_BODLEVEL
     ,

  .high = 0xFF
    // & FUSE_BOOTRST
       & FUSE_BOOTSZ0
       & FUSE_BOOTSZ1
       & FUSE_EESAVE 
       & FUSE_CKOPT  
       & FUSE_SPIEN  
    // & FUSE_JTAGEN 
    // & FUSE_OCDEN  
     ,
};

/*-----------------------------------------------------------------------*/
/* local variables                                                       */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* local functions                                                       */
/*-----------------------------------------------------------------------*/


/*************************************************************************/
/* Fuses:                                                                */
/*                                                                       */
/* FH : 0xC1 : 1100 0001                                                 */
/*             |||| ||||                                                 */
/*             |||| |||+-- BOOTRST   Select reset vector (1: application)*/
/*             |||| ||+--- BOOTSZ0   Select Boot Size                    */
/*             |||| |+---- BOOTSZ1   Select Boot Size                    */
/*             |||| +----- EESAVE    EEPROM memory is preserved through  */
/*             ||||                     the Chip Erase                   */
/*             |||+------- CKOPT     Oscillator options  (0 for > 8MHz)  */
/*             ||+-------- SPIEN     Enable SPI Serial Program and       */
/*             ||                       Data Downloading                 */
/*             |+--------- JTAGEN    Enable JTAG                         */
/*             +---------- OCDEN     Enable OCD                          */
/*                                                                       */
/* FL : 0x2F : 0010 1111                                                 */
/*             |||| ||||                                                 */
/*             |||| |||+-- CKSEL0    Select Clock source                 */
/*             |||| ||+--- CKSEL1    Select Clock source                 */
/*             |||| |+---- CKSEL2    Select Clock source                 */
/*             |||| +----- CKSEL3    Select Clock source                 */
/*             |||+------- SUT0      Select start-up time                */
/*             ||+-------- SUT1      Select start-up time                */
/*             |+--------- BODEN     Brown-out Detector enable           */
/*             +---------- BODLEVEL  Brown-out Detector trigger level    */
/*************************************************************************/

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      main                                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*                                                                       */
/* INPUT                                                                 */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* OUTPUT                                                                */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* RETURNS                                                               */
/*                                                                       */
/*      status  description                                              */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/*        DATE          REMARKS                                          */
/*      mm-dd-yyyy                                                       */
/*                                                                       */
/*************************************************************************/
long ttt;
int main(void)
{
  /**** SYS_init should be the first action in main ****/
  SYS_init();
 
  APPL_Init();
  
  // /**** Sys_start should be called immediately before main loop ****/
  SYS_start();
  
  APPL_Start();

  /**** main loop ****/
  while(1)
  {
    APPL_Main();
  }
  
  return(0);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      MAIN_1s                                                          */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*       Second main loop                                                */
/*                                                                       */
/*       run time must be shorter than 1s                                */
/*                                                                       */
/* INPUT                                                                 */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* OUTPUT                                                                */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* RETURNS                                                               */
/*                                                                       */
/*      status  description                                              */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/*        DATE          REMARKS                                          */
/*      mm-dd-yyyy                                                       */
/*                                                                       */
/*************************************************************************/
void MAIN_1s(void)
{
  APPL_1s();
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      MAIN_100ms                                                       */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*       Second main loop                                                */
/*                                                                       */
/*       run time must be shorter than 100ms                             */
/*                                                                       */
/* INPUT                                                                 */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* OUTPUT                                                                */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* RETURNS                                                               */
/*                                                                       */
/*      status  description                                              */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/*        DATE          REMARKS                                          */
/*      mm-dd-yyyy                                                       */
/*                                                                       */
/*************************************************************************/
void MAIN_100ms(void)
{
  APPL_100ms();
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      MAIN_1ms                                                         */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*       Millisecond main loop                                           */
/*                                                                       */
/*       run time must be shorter than 1ms                               */
/*                                                                       */
/* INPUT                                                                 */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* OUTPUT                                                                */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* RETURNS                                                               */
/*                                                                       */
/*      status  description                                              */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/*        DATE          REMARKS                                          */
/*      mm-dd-yyyy                                                       */
/*                                                                       */
/*************************************************************************/
void MAIN_1ms(void)
{
  APPL_1ms();
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      MAIN_fast                                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*       Fast main loop                                                  */
/*                                                                       */
/*       run time must be shorter than fast interrupt (100us)            */
/*                                                                       */
/* INPUT                                                                 */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* OUTPUT                                                                */
/*                                                                       */
/*      name    description                                              */
/*                                                                       */
/* RETURNS                                                               */
/*                                                                       */
/*      status  description                                              */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/*        DATE          REMARKS                                          */
/*      mm-dd-yyyy                                                       */
/*                                                                       */
/*************************************************************************/
void MAIN_fast(void)
{
}


/*-----------------------------------------------------------------------*/
/* end of source file                                                    */
/*-----------------------------------------------------------------------*/
