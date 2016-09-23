/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : patch3.cpp
 * PURPOSE     : Computational geometry project.
 *               Primitive patch3 module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 16.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../../animation.h"

#include "patch3.h"

/* Class constructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::primitive::patch3::patch3( anim *Ani ) : prim(Ani)
{
} /* End of 'tcg::primitive::patch3::patch3' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::primitive::patch3::~patch3( VOID )
{
} /* End of 'tcg::primitive::patch3::~patch3' function */

/* Draw primitive function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::primitive::patch3::Render( VOID )
{
  Material->Apply(Ani);

  glBindVertexArray(VABuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
  glPatchParameteri(GL_PATCH_VERTICES, 3);
  glDrawElements(GL_PATCHES, this->NoofI, GL_UNSIGNED_INT, NULL);

  glUseProgram(0);
} /* End of 'tcg::primitive::patch3::Render' render */

/* END OF 'patch3' FILE */
