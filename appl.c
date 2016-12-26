/*************************************************************************/
/*************************************************************************/
/*                                                                       */
/* FILE NAME VERSION                                                     */
/*                                                                       */
/*      appl.c                                                           */
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

/*-------------------------------------------------------------------------
This application generates frequencies of DWD (147.3khz) and NAVTEX (490khz/518khz).
The oscillator works 100ms at one of these frequencies and changes then to the next 
frequency. So each frequency is 100ms active with 200ms break.

This pulsed frequencies are good detectable with a SSB radio so the target frequency 
can be tuned.

As the navtex frequencies are too high for the choosen algorithm, 1/3 of the target
frequency is used and the receiver is tuned to the third harmonics. Because we work 
with a square wave, the third harmonic has enough power.

-------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* include files                                                         */
/*-----------------------------------------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>


#include "defines.h"
#include "system.h"

#include "appl.h"

/*-----------------------------------------------------------------------*/
/* local defines                                                         */
/*-----------------------------------------------------------------------*/
#define FREQ1  (147300)			  // DWD frequency
#define FREQ2  (490000/3)		  // NAVTEX national  1/3
#define FREQ3  (518000/3)		  // NAVTEX international  1/3

/*-------------------------------------------------------------------------------*/
/* here some constants are calculated offline as macros to optimize runtime      */
/*                                                                               */
/*   x is a placeholder for the index of the frequency                           */
/*                                                                               */
/*   CYCx is the calculated value for the ICR1L register, this is 1 less as the  */ 
/*   ratio of SYS_CPU_CLK/FREQ1. So the real period is (CYCx+1)*SYS_CPU_CLK,     */
/*   which is a fraction of a CPU_CLK shorter than the target period.            */
/*                                                                               */
/*   The constant DIFFxS is the calculated error between actual (always shorter  */
/*   period) and target period times 128.                                        */
/*                                                                               */
/*   If the register ICR1L is written with CYCx + 1, the real period is          */
/*   (CYCx+2)*SYS_CPU_CLK, which is a fraction of a CPU_CLK longer than the      */
/*   target period.                                                              */
/*                                                                               */
/*   The constant DIFFxL is the calculated error between actual                  */
/*   (always longer) period and target period times 128.                         */ 
/*-------------------------------------------------------------------------------*/
#define CYC1 (SYS_CPU_CLK/FREQ1-1)
#define DIFF1S (((S16) (((double)SYS_CPU_CLK/ FREQ1) * 128) - ((S16)(CYC1+1) * 128)))
#define DIFF1L (((S16) (((double)SYS_CPU_CLK/ FREQ1) * 128) - ((S16)(CYC1+2) * 128)))

#define CYC2 (SYS_CPU_CLK/FREQ2-1)                                   
#define DIFF2S (((S16) (((double)SYS_CPU_CLK/ FREQ2) * 128) - ((S16)(CYC2+1) * 128)))
#define DIFF2L (((S16) (((double)SYS_CPU_CLK/ FREQ2) * 128) - ((S16)(CYC2+2) * 128)))

#define CYC3 (SYS_CPU_CLK/FREQ3-1)                                  
#define DIFF3S (((S16) (((double)SYS_CPU_CLK/ FREQ3) * 128) - ((S16)(CYC3+1) * 128)))
#define DIFF3L (((S16) (((double)SYS_CPU_CLK/ FREQ3) * 128) - ((S16)(CYC3+2) * 128)))


#define PORTLED PORTD
#define PINLED  0x08

/*-----------------------------------------------------------------------*/
/* local variables                                                       */
/*-----------------------------------------------------------------------*/

S8 interr;
U8 cycs;
U8 cycl;
U8 diffs;
U8 diffl;

U8 fstate;

/****************************************************************************
*
*  appl
*  ------
*  
*
****************************************************************************/


void APPL_Init( void )
{
}


void APPL_Start(void)
{
  interr = 0;
  // configure  Timer1 for Fast PWM, period set to ICR1 
  // do PWM with OC1A
  TCCR1A = 0xf2;            // 0010 0000;
  TCCR1B = 0x19;            // 0001 1001;
  ICR1   = CYC1;            // period
  OCR1A  = ICR1 / 2;
  OCR1B  = ICR1 / 2;
  TCNT1  = 0;
  TIMSK |= 0x04;
  cycs = CYC1;
  cycl = cycs + 1;
  diffs = DIFF1S;
  diffl = DIFF1L;
}


void APPL_Main(void)
{
}

void APPL_1ms(void)
{
  U8 t8;
  U16 t16;

  // calculate 50% duty cycle 
  //
  // as the generated frequencies dont vary so much, this is not really necessary, 
  // but its nice do do it correct
  //
  t16 = ICR1;
  t16 = t16 + 1;
  t16 = t16 / 2;
  t8  = t16-1;
  
  OCR1A  = t8;
  OCR1B  = t8;
}

void APPL_100ms(void)
{
  // change each 100ms the target frequency
  switch (fstate)
  {
    case 1: 
      {
        fstate = 2;
          ICR1 = CYC1;
          TCNT1  = 0;
          cycs = CYC1;
          cycl = CYC1 + 1;
          diffs = DIFF1S;
          diffl = DIFF1L;
	  PORTLED |= PINLED;
      }
      break;

    case 2: 
      {
        fstate = 3;
          ICR1 = CYC2;
          TCNT1  = 0;
          cycs = CYC2;
          cycl = CYC2 + 1;
          diffs = DIFF2S;
          diffl = DIFF2L;
	  PORTLED &= ~PINLED;
      }
      break;

    case 3: 
      {
        fstate = 1;
          ICR1 = CYC3;
          TCNT1  = 0;
          cycs = CYC3;
          cycl = CYC3 + 1;
          diffs = DIFF3S;
          diffl = DIFF3L;
      }
      break;

    default: 
      {
        fstate = 1;
      }
      break;
  }
  
}

void APPL_1s(void)
{
}

// interrupt routine should be optimized for max. speed
// max. 190kHz may be achieved
#pragma GCC optimize ("O3")
ISR(TIMER1_OVF_vect)
{
  if(interr < 0)        // if error is negative
  {
    ICR1L = cycs;       // use short period
    interr += diffs;
  }
  else
  {
    ICR1L = cycl;       // else use long period
    interr += diffl;
  }
}
