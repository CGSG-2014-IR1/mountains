/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : WINMSG.CPP
 * PURPOSE     : Simple animation system.
 *               Window class massage handle implementation module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "window.h"

#include <windowsx.h>

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL tcg::window::OnCreate( CREATESTRUCT *CS )
{
  return TRUE;
} /* End of 'tcg::window::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::window::OnDestroy( VOID )
{
  /* Call user level deinitialization */
  if (IsInit)
  {
    IsInit = FALSE;
    Close();
    KillTimer(hWnd, 30);
  }
} /* End of 'tcg::window::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID tcg::window::OnSize( UINT State, INT W, INT H )
{
  Width = W;
  Height = H;
  /* Call user level change size notifivcation */
  if (IsInit)
    Resize();
} /* End of 'tcg::window::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL tcg::window::OnEraseBkgnd( HDC hDC )
{
  /* Call user level erase background function */
  if (IsInit)
    Erase(hDC);
  return FALSE;
} /* End of 'tcg::window::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::window::OnPaint( VOID )
{
  HDC hDC;
  PAINTSTRUCT ps;

  hDC = BeginPaint(hWnd, &ps);
  /* Call user level paint window content function */
  if (IsInit)
    Paint(hDC);
  EndPaint(hWnd, &ps); 
} /* End of 'tcg::window::OnPaint' function */

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID tcg::window::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;

  /* Call user level activate handle function */
  if (IsInit)
    Activate(IsActive);
} /* End of 'tcg::window::OnActivate' function */

/* WM_KEYDOWN window message handle function.
 * ARGUMENTS:
 *   - pressed key:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID tcg::window::OnKeyDown( UINT Keys )
{
} /* End of 'tcg::window::OnKeyDown' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID tcg::window::OnTimer( INT Id )
{
  /* Call user level timer handle function */
  if (IsInit)
    if (Id != InitializationTimer)
      Timer();
    else
      InvalidateRect(hWnd, NULL, TRUE);
  else
  {
    IsInit = TRUE;
    Init();
    Resize();
    InvalidateRect(hWnd, NULL, TRUE);
    if (IsActive)
      Activate(TRUE);
  }
} /* End of 'tcg::window::OnTimer' function */

/* WM_*BUTTONDOWN window message handle function.
 * ARGUMENTS:
 *   - double click flag:
 *       BOOL IsDoubleClick;
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID tcg::window::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
  SetCapture(hWnd);
} /* End of 'tcg::window::OnButtonDown' function */

/* WM_*BUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID tcg::window::OnButtonUp( INT X, INT Y, UINT Keys )
{
  ReleaseCapture();
} /* End of 'tcg::window::OnButtonUp' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel delta value (120 points per rotate):
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID tcg::window::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'tcg::window::OnButtonUp' function */

/* END OF 'WINMSG.CPP' FILE */
