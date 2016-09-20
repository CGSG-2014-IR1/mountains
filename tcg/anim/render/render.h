/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : render.h
 * PURPOSE     : Computational geometry project.
 *               Rendering class declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __render_h_
#define __render_h_

#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "../../def.h"

#include "resource/material.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Forward declaration */
  class prim;

  /* Render system through OpenGL class declaration */
  class render : public material_manager
  {
  private:
    /* Window handle */
    HWND &hWnd;
    /* Window device context */
    HDC hDC;
    /* OpenGL rendering context */
    HGLRC hRC;
    /* Window size */
    INT &Width, &Height;

  public:
    camera Camera; /* Camera */
    matr World;    /* World matrix */

    /* Class constructor.
     * ARGUMENTS:
     *   - window handle reference:
     *       HWND &hWndUsed;
     *   - reference to window size store places:
     *       INT &W, &H;
     */
    render( HWND &hWndUsed, INT &W, INT &H );

    /* Class destructor */
    ~render( VOID );

    /* Resize window handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID );

    /* Render starting function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID StartFrame( VOID );

    /* Render finishing function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EndFrame( VOID );

    /* Render copying frame to window function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CopyFrame( VOID );

    /* Draw primitive function.
     * ARGUMENTS:
     *   - primitive to draw:
     *       prim &P;
     * RETURNS: None.
     */
    VOID Draw( prim &P );
  }; /* End of 'render' class */

} /* end of 'tcg' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */
