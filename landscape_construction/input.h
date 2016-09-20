/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : input.h
 * PURPOSE     : Computational geometry project.
 *               Input support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 14.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __input_h_
#define __input_h_

#include "def.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Input class */
  class input
  {
  public:
    HWND hWnd; // window handle reference

    /* Keyboard system */
    BYTE
      Keys[256],              // the main keys array
      KeysOld[256],           // temporary array for clicked keys
      KeysClick[256];         // clicked keys array

    /* Mouse system */
    INT
      MsDeltaX, MsDeltaY,     // delta mouse coordinats
      MsX, MsY;               // mouse coordinats
    INT
      MouseOldX, MouseOldY;   // old mouse coordinats
    INT
      WheelDelta,             // mouse wheel delta move
      Wheel,                  // mouse wheel
      OldWheel;               // old mouse wheel

    /* Default constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    input( VOID ) :
      MsDeltaX(0), MsDeltaY(0), MsX(0), MsY(0), MouseOldX(0), MouseOldY(0), WheelDelta(0), Wheel(0), OldWheel(0)
    {
    } /* End of 'input::input' function */

    /* Default constructor.
     * ARGUMENTS:
     *   - window descriptor reference:
     *       HWND NewhWnd;
     *   - window size reference:
     *       INT W, H;
     * RETURNS: None.
     */
    input( HWND &NewhWnd, INT &W, INT &H ) : MsDeltaX(0), MsDeltaY(0), MsX(0), MsY(0),
      MouseOldX(0), MouseOldY(0), hWnd(NewhWnd), WheelDelta(0), Wheel(0), OldWheel(0)
    {
      POINT pt;
    
      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);
      MouseOldX = pt.x;
      MouseOldY = pt.y;
      GetKeyboardState(KeysOld);
    } /* End of 'input::input' function */

    /* Responsing inputing system function
     * ARGUMENTS:
     *   - activity state
     *     BOOL IsActive;
     * RETURNS: None.
     */
    VOID Response( BOOL IsActive );

    /* Checking the mouse wheel.
     * ARGUMENTS:
     *   - the mouse delta move:
     *       INT NewWheel;
     * RETURNS: None.
     */
    VOID Scroll( INT NewWheel )
    {
      WheelDelta = NewWheel - Wheel;
      OldWheel = Wheel;
      Wheel = NewWheel;
    } /* End of 'Scroll' function */
  }; /* End of 'input' class */
} /* end of 'tcg' namespace */

#endif /* __input_h_ */

/* END OF 'input.h' FILE */
