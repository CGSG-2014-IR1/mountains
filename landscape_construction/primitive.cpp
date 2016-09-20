/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : primitive.cpp
 * PURPOSE     : Computational geometry project.
 *               Primitive support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstdarg>

#include "primitive.h"

/* Class constructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::prim::prim( anim *Ani ) : Ani(Ani), VBuf(-1), IBuf(-1), VABuf(-1)
{
} /* End of 'tcg::prim::prim' function */

/* Class constructor.
 * ARGUMENTS:
 *   - primitive to copy:
 *       const prim &P;
 */
tcg::prim::prim( const prim &P )
{
} /* End of 'tcg::prim::prim' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::prim::~prim( VOID )
{
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteVertexArrays(1, (GLuint *)&VABuf);
  glDeleteBuffers(1, (GLuint *)&VBuf);
  glDeleteBuffers(1, (GLuint *)&IBuf);
} /* End of 'tcg::prim::~prim' function */

/* Draw primitive function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::prim::Render( VOID )
{
  Material->Apply(Ani);
  glBindVertexArray(VABuf);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);

  glDrawElements(GL_TRIANGLES, NoofI, GL_UNSIGNED_INT, NULL);
  glUseProgram(0);
} /* End of 'Render' function */

/* Update shader context function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::prim::UpdateShaderContext( VOID )
{
} /* End of 'tcg::prim::UpdateShaderContext' function */

/* Set buffers function.
 * ARGUMENTS:
 *   - vertices array:
 *       vertex *V;
 *   - indices array:
 *       INT *I;
 *   - number of vertices and indices:
 *       INT NoofV, NoofI;
 * RETURNS:
 *   (prim &) self reference.
 */
VOID tcg::prim::SetBuffers( vertex *V, INT *I, INT NoofV, INT NoofI )
{
  if (VABuf == 0)
    return;

  this->NoofI = NoofI;

  glGenBuffers(1, &VBuf);
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * NoofV, V, GL_STATIC_DRAW);

  glGenBuffers(1, &IBuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);

  glGenVertexArrays(1, &VABuf);
  glBindVertexArray(VABuf);

  glVertexAttribPointer( 0, 3, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, Pos));
  glVertexAttribPointer( 1, 3, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, Norm));
  glVertexAttribPointer( 2, 4, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, Col));
  glVertexAttribPointer( 3, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, UV));
  glVertexAttribPointer( 4, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, Height));
  glVertexAttribIPointer(5, 1, GL_INT,          sizeof(vertex), OFFSET(vertex, ID));
  glVertexAttribPointer( 6, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, P0));
  glVertexAttribPointer( 7, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, P1));
  glVertexAttribPointer( 8, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, H0));
  glVertexAttribPointer( 9, 2, GL_FLOAT, FALSE, sizeof(vertex), OFFSET(vertex, H1));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);
  glEnableVertexAttribArray(5);
  glEnableVertexAttribArray(6);
  glEnableVertexAttribArray(7);
  glEnableVertexAttribArray(8);
  glEnableVertexAttribArray(9);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
} /* End of 'tcg::prim::SetBuffers' function */

tcg::prim & tcg::prim::operator=( const prim &P )
{
  return *this;
} /* End of 'tcg::prim::operator=' function */

/* END OF 'primitive.cpp' FILE */