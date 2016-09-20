/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : animation.cpp
 * PURPOSE     : Computational geometry project.
 *               Animation class implementation module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "animation.h"

/* Class constructor.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 */
tcg::anim::anim( HINSTANCE hInstance ) :
  win(hInstance), render(win::hWnd, win::Width, win::Height), input(win::hWnd, win::Width, win::Height)
{
} /* End of 'tcg::anim::anim' function */

/* Class destructor */
tcg::anim::~anim( VOID )
{
} /* End of 'tcg::anim::Close' function */

/* Render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::anim::Render( VOID )
{
  /* Update timer data */
  timer::Response();
  timer::IncrFrameCount();

  /* Update input system */
  input::Response(IsActive);
  input::Scroll(win::MouseWheel);

  /* Responce all units */
  unit_manager::Response();

  /* Render one frame */
  render::StartFrame();

  /* Render all units */
  unit_manager::Render();

  render::EndFrame();
  render::CopyFrame();
} /* End of 'tcg::anim::Render' function */

/***
 * Virtual functions for window customization
 ***/

/* Initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::anim::Init( VOID )
{
} /* End of 'tcg::anim::Init' function */

/* Deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::anim::Close( VOID )
{
} /* End of 'tcg::anim::Close' function */

/* Change window size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::anim::Resize( VOID )
{
  render::Resize();
} /* End of 'tcg::anim::Resize' function */

/* Erase background handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID tcg::anim::Erase( HDC hDC )
{
} /* End of 'tcg::anim::Erase' function */

/* Paint window content function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID tcg::anim::Paint( HDC hDC )
{
  Render();
} /* End of 'tcg::anim::Paint' function */

/* Activate handle function.
 * ARGUMENTS:
 *   - activation window flag:
 *       BOOL IsActive;
 * RETURNS: None.
 */
VOID tcg::anim::Activate( BOOL IsActive )
{
} /* End of 'tcg::anim::Activate' function */

/* Timer handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::anim::Timer( VOID )
{
  Render();
} /* End of 'tcg::anim::Timer' function */

/* Free CPU time handling function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::anim::Idle( VOID )
{
  Render();
} /* End of 'tcg::anim::Idle' function */

/* END OF 'animation.cpp' FILE */
