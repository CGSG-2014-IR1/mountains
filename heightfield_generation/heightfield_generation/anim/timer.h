/* Reshetnyak Ivan */

#ifndef __TIMER_H_
#define __TIMER_H_

#include "../def.h"

/* Timer handle class */
class timer
{
public:
  bool IsPause;        // flag if animation is paused
  double
    GlobalTime,        // global time
    GlobalDeltaTime,   // global delta time
    Time,              // local time
    DeltaTime,         // local delta time
    FPS;               // Frames-Per-Second
  long FrameCounter;   // frame counter

  /* Timer update function
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Update( VOID )
  {
    LARGE_INTEGER li;                                                     // temporary L_I variable

    QueryPerformanceCounter(&li);                                         // get current time
    GlobalTime = (double)(li.QuadPart - TimeStart) / TimeFreq;            // set global time
    GlobalDeltaTime = (double)(li.QuadPart - TimeOld) / TimeFreq;         // set global delta time

    if (!IsPause)
      DeltaTime = GlobalDeltaTime;                                        // no pause - local time passes
    else
    {
      TimePause += li.QuadPart - TimeOld;                                 // count pause time
      DeltaTime = 0;                                                      // pause - local time stands
    }

    Time = (double)(li.QuadPart - TimePause - TimeStart) / TimeFreq;      // set time

    /* Count FPS */
    if (li.QuadPart - TimeFPS > TimeFreq)
    {
      FPS = FrameCounter / ((double)(li.QuadPart - TimeFPS) / TimeFreq);  // count FPS
      TimeFPS = li.QuadPart;                                              // set FPS time
      FrameCounter = 0;                                                   // nullify frame counter
    }
    FrameCounter++;

    TimeOld = li.QuadPart;                                                // set old frame time
  } // End of 'Update' function

private:
  __int64
    TimeFreq,          // timer frequency
    TimeStart,         // animation start time
    TimeOld,           // previous frame time
    TimePause,         // pause elapsed time
    TimeFPS;           // time for FPS

public:
  /* Default timer constructor
   * ARGUMENTS: None.
   */
  timer( VOID ) : IsPause(FALSE), FrameCounter(0)
  {
    LARGE_INTEGER li;  // temporary L_I variable

    QueryPerformanceFrequency(&li);               // get timer frequency
    TimeFreq = li.QuadPart;                       // set timer frequency
    QueryPerformanceCounter(&li);                 // get current time
    TimeStart = TimeOld = TimeFPS = li.QuadPart;  // set all to beginning time
    TimePause = 0;
  } // End of 'timer' constructor

  /* Timer destructor
   * ARGUMENTS: None.
   */
  ~timer( VOID )
  {
  } // End of 'timer' destructor
}; // End of 'timer' class

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */
