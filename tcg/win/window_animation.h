/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : window_animation.h
 * PURPOSE     : Simple animation system.
 *               Window class declaration module.
 * PROGRAMMER  : MM5,
 *               IR1.
 * LAST UPDATE : 24.09.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __window_animation_h_
#define __window_animation_h_

#include "../def.h"
#include "../resource.h"
#include "window.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Main window class declaration */
  class window_animation : public window
  {
  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - application instance handle:
     *       HINSTANCE hInst;
     */
    window_animation( HINSTANCE hInst = GetModuleHandle(NULL) ) :
      window(hInst, "AnimationWindowClass", "Animation window", true, IDR_MENU1, true)
    {
      SetTimer(hWnd, 30, 1, NULL);
    } /* End of 'window_animation' constructor */

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID )
    {
      /* Call user level deinitialization */
      if (IsInit)
      {
        IsInit = FALSE;
        Close();
        KillTimer(hWnd, 30);
      }
      PostMessage(hWnd, WM_QUIT, 0, 0);
    } /* End of 'tcg::window_animation::OnDestroy' function */
  }; /* End of 'win' class */
} /* end of 'tcg' namespace */

#endif /* __window_h_ */

/* END OF 'window.h' FILE */
