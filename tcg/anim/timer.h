/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TIMER.H
 * PURPOSE     : Simple animation system.
 *               Timer class declaration and implementation module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __timer_h_
#define __timer_h_

#include "../def.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Timer class declaration */
  class timer
  {
  private:
    /* Start time (in ticks) */
    UINT64
      StartTime,      // Time from program start
      OldTime,        // Time of last frame
      LastTime,       // Time of last FPS measure
      PauseTime,      // Total pause time
      TimesPerSecond; // Timer sensitivity

    /* Frame counter */
    UINT64 FrameCount;

  public:
    /* Timer data (in seconds) */
    DBL
      GlobalTime,      // Time from program start
      GlobalDeltaTime, // Delta time from last frame
      Time,            // Time from prgram start (with pause)
      DeltaTime;       // Delta time from last frame (with pause)

    /* Pause flag */
    BOOL IsPause;

    /* Frames-per-second value */
    DBL FPS;

    /* Class constructor */
    timer( VOID ) :
      FrameCount(0), GlobalTime(0), GlobalDeltaTime(0),
      Time(0), DeltaTime(0), PauseTime(0), IsPause(FALSE), FPS(0)
    {
      LARGE_INTEGER CurrentTime;

      /* Query timer information */
      QueryPerformanceCounter(&CurrentTime);
      StartTime = OldTime = LastTime = CurrentTime.QuadPart;
      QueryPerformanceFrequency(&CurrentTime);
      TimesPerSecond = CurrentTime.QuadPart;
    } /* End of 'timer' function */

    /* Responce and update timer values function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      LARGE_INTEGER CurrentTime;

      /* Query current timer value */
      QueryPerformanceCounter(&CurrentTime);

      /* Evaluate global time values */
      GlobalTime =
        (DBL)(CurrentTime.QuadPart - StartTime) / TimesPerSecond;
      GlobalDeltaTime =
        (DBL)(CurrentTime.QuadPart - OldTime) / TimesPerSecond;

      /* Determine FPS value (one time per one second) */
      if (CurrentTime.QuadPart - LastTime > TimesPerSecond)
      {
        FPS = (DBL)FrameCount / (CurrentTime.QuadPart - LastTime) * TimesPerSecond;
        LastTime = CurrentTime.QuadPart;
        FrameCount = 0;
      }

      /* Evaluate local time (time with pause) values */
      Time = (DBL)(CurrentTime.QuadPart - StartTime - PauseTime) / TimesPerSecond;
      if (IsPause)
        DeltaTime = 0, PauseTime += CurrentTime.QuadPart - OldTime;
      else
        DeltaTime = GlobalDeltaTime;

      OldTime = CurrentTime.QuadPart;
    } /* End of 'Response' function */

    /* Increment frame count function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID IncrFrameCount( VOID )
    {
      FrameCount++;
    } /* End of 'IncrFrameCount' function */

    /* Enable/disable pause function.
     * ARGUMENTS:
     *   - new pause flag value:
     *       BOOL IsToBePause;
     * RETURNS:
     *   (BOOL) old pause state (TRUE or FALSE).
     */
    BOOL SetPause( BOOL IsToBePause )
    {
      if (IsPause == IsToBePause)
        return IsPause;
      return IsPause = IsToBePause;
    } /* End of 'SetPause' function */
  }; /* End of 'timer' class */
} /* end of 'tcg' namespace */

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */
