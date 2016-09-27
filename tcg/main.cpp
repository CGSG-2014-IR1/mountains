/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Computational geometry project.
 *               WinAPI startup module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "anim/animation.h"

#include "anim/units/unit_hm_preview.h"

using namespace tcg;

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow )
{
  anim Ani(hInstance);
  Ani << new unit_hm_preview(&Ani);
  //Ani << new unit_road(&Ani);
  Ani.Run();

  return 0;
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */
