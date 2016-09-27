/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : primitive.h
 * PURPOSE     : Computational geometry project.
 *               Primitive support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 14.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __primitive_h_
#define __primitive_h_

#include <cstdarg>

#include "../../def.h"

#include "render.h"
#include "resource/shader.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Texture coordinates structure */
  struct uv
  {
    FLOAT s, t;

    /* Class constructor.
     * ARGUMENTS: None.
     */
    uv( VOID )
    {
    } /* End of 'uv' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - texture coordinates:
     *       const FLOAT &s, &t;
     */
    uv( const FLOAT &s, const FLOAT &t ) : s(s), t(t)
    {
    } /* End of 'uv' function */
  }; /* End of 'uv' struct */

  /* Vertex structure */
  struct vertex
  {
    vecf Pos;
    vecf Norm;
    color Col;
    uv UV;
    uv Height;
    INT ID;
    uv P0, P1, H0, H1;

    /* Default constructor.
     * ARGUMENTS: None.
     */
    vertex( VOID )
    {
    } /* End of 'vertex' constructor */

    /* Position-filling constructor.
     * ARGUMENTS:
     *   - const vecf &Pos:
     *       vertex postion.
     */
    vertex( const vecf &Pos ) : Pos(Pos)
    {
    } /* End of 'vertex' constructor */
  }; /* End of 'vertex' struct */

  /* Primitive class */
  class prim
  {
  protected:
    UINT
      VABuf, VBuf, IBuf,
      NoofV, NoofI;
    anim *Ani;

  public:
    material *Material;

    /* Class constructor.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     */
    prim( anim *Ani );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~prim( VOID );

    /* Draw primitive function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Render( VOID );

    /* Update shader context function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID UpdateShaderContext( VOID );

    /* Set buffers function.
     * ARGUMENTS:
     *   - vertices array:
     *       vertex *V;
     *   - indices array:
     *       INT *I;
     *   - number of vertices and indices:
     *       INT NoofV, NoofI;
     * RETURNS: None.
     */
    virtual VOID SetBuffers( vertex *V, INT *I, INT NoofV, INT NoofI );

    /* Delete buffers function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID DeleteBuffers( VOID )
    {
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      if (VABuf != -1)
        glDeleteVertexArrays(1, (GLuint *)&VABuf);
      if (VBuf != -1)
        glDeleteBuffers(1, (GLuint *)&VBuf);
      if (IBuf != -1)
        glDeleteBuffers(1, (GLuint *)&IBuf);
    } /* End of 'DeleteBuffers' function */

  private:
    /* Class constructor.
     * ARGUMENTS:
     *   - primitive to copy:
     *       const prim &P;
     */
    prim( const prim &P );

    /* Copy primitive function.
     * ARGUMENTS:
     *   - primitive to copy:
     *       const prim &P;
     * RETURNS:
     *   (prim &) self reference.
     */
    prim & operator=( const prim &P );
  }; /* End of 'prim' class */
} /* end of 'tcg' namespace */

#endif /* __primitive_h_ */

/* END OF 'primitive.h' FILE */
