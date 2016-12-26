/*************************************************************************/
/*                                                                       */
/* FILE NAME VERSION                                                     */
/*                                                                       */
/*      defines.h                                                        */
/*                                                                       */
/* COMPONENT                                                             */
/*                                                                       */
/*      software definitions                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      symbolic definitions for commonly used data types                */
/*                                                                       */
/* AUTHOR                                                                */
/*                                                                       */
/*                                                                       */
/* Target                                                                */
/*                                                                       */
/*      Philips LPC2114                                                  */
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
/*                                                                       */
/*************************************************************************/

#ifndef _DEFINES_H_
#define _DEFINES_H_

/*-----------------------------------------------------------------------*/
/*  constant definitions                                                 */
/*-----------------------------------------------------------------------*/
#define VERSION2

/*-----------------------------------------------------------------------*/
/*  exported macros                                                      */
/*-----------------------------------------------------------------------*/
#define DEF_U8toD2(c) (((((U8)(c))/10)*16)+((U8)(c))%10)


/*-----------------------------------------------------------------------*/
/*  type declarations                                                    */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*  exported enums                                                       */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*  exported variables                                                   */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*  exported functions                                                   */
/*-----------------------------------------------------------------------*/

/* 'exact width' integer types */
typedef unsigned char          U8;   /* unsigned  8 bit integer */
typedef unsigned short int     U16;  /* unsigned 16 bit integer */
typedef unsigned long int      U32;  /* unsigned 32 bit integer */
typedef unsigned long long int U64;  /* unsigned 64 bit integer */

typedef signed char            S8;   /*   signed  8 bit integer */
typedef signed short int       S16;  /*   signed 16 bit integer */
typedef signed long int        S32;  /*   signed 32 bit integer */
typedef signed long long int   S64;  /*   signed 64 bit integer */

typedef union
{
  U64 u64;
  S64 s64;
  U32 au32[2];
  U16 au16[4];
  U8  au8[8];
  struct
  {
    U32 l;
    U32 h;
  } u32;
  struct
  {
    S32 l;
    S32 h;
  } s32;
  struct
  {
    U16 ll;
    U16 lh;
    U16 hl;
    U16 hh;
  } u16;
  struct
  {
    S16 ll;
    S16 lh;
    S16 hl;
    S16 hh;
  } s16;
  struct
  {
    U8 lll;
    U8 llh;
    U8 lhl;
    U8 lhh;
    U8 hll;
    U8 hlh;
    U8 hhl;
    U8 hhh;
  } u8;
  struct
  {
    S8 lll;
    S8 llh;
    S8 lhl;
    S8 lhh;
    S8 hll;
    S8 hlh;
    S8 hhl;
    S8 hhh;
  } s8;
} tConvert64;

typedef union
{
  U32 u32;
  S32 s32;
  U16 au16[2];
  S16 as16[2];
  U8  au8[4];
  S8  as8[4];
  struct
  {
    U16 l;
    U16 h;
  } u16;
  struct
  {
    S16 l;
    S16 h;
  } s16;
  struct
  {
    U8 ll;
    U8 lh;
    U8 hl;
    U8 hh;
  } u8;
  struct
  {
    S8 ll;
    S8 lh;
    S8 hl;
    S8 hh;
  } s8;
} tConvert32;

typedef union
{
  U16 u16;
  S16 s16;
  struct
  {
    U8 l;
    U8 h;
  } u8;
  struct
  {
    S8 l;
    S8 h;
  } s8;
} tConvert16;



#ifndef BOOL_TYPE
  typedef unsigned char BOOL;

  #define BOOL_TYPE
#endif /* BOOL_TYPE */

#ifndef TRUE
  #define TRUE ( ( BOOL ) 1==1)
#endif /* TRUE*/

#ifndef FALSE
  #define FALSE (!TRUE)
#endif /* FALSE */

/* null pointer constant. */
#undef NULL  /* others (e.g. <stdio.h>) also define */
#define NULL 0

#define BITS_PER_BYTE  8

#define U8MIN     ( ( U8)  0 )
#define U8MAX     ( ( U8)  0xFF )
#define U16MIN    ( ( U16) 0 )
#define U16MAX    ( ( U16) 0xFFFF )
#define U32MIN    ( ( U32) 0 )
#define U32MAX    ( ( U32) 0xFFFFFFFF )
#define U64MIN    ( ( U64) 0 )
#define U64MAX    ( ( U64) 0xFFFFFFFFFFFFFFFF )

#define S8MIN      ( ( S8)  0x80 )
#define S8MAX      ( ( S8)  0x7f )
#define S16MIN     ( ( S16) 0x8000 )
#define S16MAX     ( ( S16) 0x7fff )
#define S32MIN     ( ( S32) 0x80000000 )
#define S32MAX     ( ( S32) 0x7fffffff )
#define S64MIN     ( ( S64) 0x8000000000000000 )
#define S64MAX     ( ( S64) 0x7fffffffffffffff )


#endif /* _DEFINES_H_ */

/*-----------------------------------------------------------------------*/
/* end of source file                                                    */
/*-----------------------------------------------------------------------*/

/*************************************************************************
*
* FOOTER
*
*
**************************************************************************/
