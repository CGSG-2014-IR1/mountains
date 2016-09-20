/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : input.h
 * PURPOSE     : Computational geometry project.
 *               Input support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 14.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../def.h"

#include "input.h"

/* Responsing inputing system function
 * ARGUMENTS:
 *   - activity state
 *       BOOL IsActive;
 * RETURNS: None.
 */
VOID tcg::input::Response( BOOL IsActive )
{
  POINT pt;

  if (!IsActive)
  {
    for (INT i = 0; i < 256; i++)
      Keys[i] = 0;
    for (INT i = 0; i < 256; i++)
      KeysClick[i] = 0;
    memcpy(KeysOld, Keys, sizeof(KeysOld));
    MsX = 0;
    MsY = 0;
    MsDeltaX = 0;
    MsDeltaY = 0;
    MouseOldX = 0;
    MouseOldY = 0;
    OldWheel = 0;
    WheelDelta = 0;

    return;
  }

  GetKeyboardState(Keys);
  for (INT i = 0; i < 256; i++)
    Keys[i] >>= 7;
  for (INT i = 0; i < 256; i++)
    KeysClick[i] = Keys[i] && !KeysOld[i];
  memcpy(KeysOld, Keys, sizeof(KeysOld));

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  MsX = pt.x;
  MsY = pt.y;
  MsDeltaX = pt.x - MouseOldX;
  MsDeltaY = pt.y - MouseOldY;
  MouseOldX = pt.x;
  MouseOldY = pt.y;
  OldWheel = WheelDelta;
  WheelDelta = 0;
} /* End of 'tcg::input::Response' function */

/* END OF 'input.cpp' FILE */
