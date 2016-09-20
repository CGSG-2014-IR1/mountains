/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : render.cpp
 * PURPOSE     : Computational geometry project.
 *               Rendering class implementation module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <stdlib.h>

#include "render.h"

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")

/* Class constructor.
 * ARGUMENTS:
 *   - window handle reference:
 *       HWND &hWndUsed;
 *   - reference to window size store places:
 *       INT &W, &H;
 */
tcg::render::render( HWND &hWndUsed, INT &W, INT &H ) :
  hWnd(hWndUsed), Width(W), Height(H), Camera(vec(0, 40, 40), vec(0, 0, 0), vec(0, 1, 0), 1, 1, 1, 1.5, 10000.0, W, H)
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  hDC = GetDC(hWnd);

  /*** OpenGL initialization ***/

  /* describe pixel format */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  /* create OpenGL rendering context  */
  hRC = wglCreateContext(hDC);
  /* set active contexts */
  wglMakeCurrent(hDC, hRC);

  /* OpenGL extensions initialization */
  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    exit(0);
  }

  /* Setup default settings */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.3, 0.5, 0.7, 1);
} /* End of 'tcg::render::render' function */

/* Class destructor */
tcg::render::~render( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hRC);
  ReleaseDC(hWnd, hDC);
} /* End of 'tcg::render::~render' function */

/* Resize window handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::render::Resize( VOID )
{
  glViewport(0, 0, Width, Height);

  Camera.ScreenWidth = Width;
  Camera.ScreenHeight = Height;
  Camera.UpdateProjData();
} /* End of 'tcg::render::Resize' function */

/* Render starting function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::render::StartFrame( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'tcg::render::StartFrame' function */

/* Render finishing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::render::EndFrame( VOID )
{
  glFinish();
} /* End of 'tcg::render::EndFrame' function */

/* Render copying frame to window function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::render::CopyFrame( VOID )
{
  SwapBuffers(hDC);
} /* End of 'tcg::render::CopyFrame' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive to draw:
 *       prim &P;
 * RETURNS: None.
 */
VOID tcg::render::Draw( prim &P )
{
} /* End of 'tcg::render::Draw' function */

/* END OF 'render.cpp' FILE */
