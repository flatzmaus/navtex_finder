/*************************************************************************/
/*                                                                       */
/* FILE NAME VERSION                                                     */
/*                                                                       */
/*  appl.h                                                               */
/*                                                                       */
/* COMPONENT                                                             */
/*                                                                       */
/*      application                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      application                                                      */
/*                                                                       */
/*                                                                       */
/* AUTHOR                                                                */
/*                                                                       */
/*                                                                       */
/* Target                                                                */
/*      Philips LPC2114 with 24LC32A via I2C                             */
/*                                                                       */
/* Compiler                                                              */
/*                                                                       */
/*      ARM/Thumb Macro Assembler, RVCT2.1 [Build 498]                   */
/*      ARM/Thumb C/C++ Compiler, RVCT2.1 [Build 498]                    */
/*      ARM Linker, RVCT2.1 [Build 498]                                  */
/*      ARM FromELF, RVCT2.1 [Build 498]                                 */
/*                                                                       */
/* HISTORY                                                               */
/*                                                                       */
/*        DATE          REMARKS                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
#ifndef _APPL_H_
#define _APPL_H_


/****************************************************************************/
/*
**  ------
**  
*/
/****************************************************************************/

#define MAXDEV 4

typedef union
{
  struct
  {
    U8 i;     // 0: valid      not 0: invalid data
    U8 h;     // hours 0..23
    U8 m;     // minutes 0..59
    U8 s;     // seconds 0..59
  } e;
  U32 all;
} HMS;

typedef union 
{
  U8 all;
  struct
  {
    U8 autoup : 1;  // enable auto-up
    U8 autodn : 1;  // enable auto-down
    U8 solup  : 1;  // enable solar-up
    U8 soldn  : 1;  // enable solar-down
  } aut;
} AUT;

typedef struct 
{
  HMS tupmin;       // earliest up-time 
  HMS tupmax;       // latest up-time 
  HMS tdnmin;       // earliest down-time 
  HMS tdnmax;       // latest down-time 
  AUT aut;          // enable/disable automatic functions
  U16 pulsdur;      // duration of up/down travel
} tDEVCFG;

typedef struct 
{
  tDEVCFG   APPL_Para[MAXDEV];
  U8        sun_param;
  U8        auto_param;
} tAPPLCFG;

extern tAPPLCFG tAPPLCfg;

void APPL_Init ( void );
void APPL_Start( void );
void APPL_Main ( void );
void APPL_1ms  ( void );
void APPL_100ms ( void );
void APPL_1s   ( void );


#endif  /* _APPL_H_ */
