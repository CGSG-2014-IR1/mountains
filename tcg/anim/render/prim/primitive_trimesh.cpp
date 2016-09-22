/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : primitive_trimesh.cpp
 * PURPOSE     : Computational geometry project.
 *               Primitive trimesh module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 16.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../../animation.h"

#include "primitive_samples.h"

/* Class constructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::primitive::trimesh::trimesh( anim *Ani ) : prim(Ani)
{
} /* End of 'tcg::primitive::trimesh::trimesh' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::primitive::trimesh::~trimesh( VOID )
{
} /* End of 'tcg::primitive::trimesh::~trimesh' function */

/* END OF 'primitive_trimesh' FILE */
