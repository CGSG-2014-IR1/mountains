/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : trimesh.h
 * PURPOSE     : Computational geometry project.
 *               Primitive samples declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __trimesh_h_
#define __trimesh_h_

#include "../../../def.h"

#include <vector>
#include <array>

#include "../primitive.h"
#include "../../../math/computational_geometry.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Primitive namespace */
  namespace primitive
  {
    /* Primitive trimesh class */
    class trimesh : public prim
    {
    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       */
      trimesh( anim *Ani );

      /* Class destructor.
       * ARGUMENTS: None.
       */
      ~trimesh( VOID );

      /* Quad create function.
       * ARGUMENTS:
       *   - quad vertexes:
       *       const vec &P0, &P1, &P2, &P3.
       * RETURNS: None.
       */
      VOID CreateQuad( const vec &P0, const vec &P1, const vec &P2, const vec &P3 )
      {
        DeleteBuffers();
        vertex v[4] = { P0, P1, P2, P3 };
        INT i[6] = { 0, 1, 2, 0, 2, 3 };
        SetBuffers(v, i, 4, 6);
      } /* End of 'CreateQuad' function */
    }; /* End of 'trimesh' class */
  } /* end of 'primitive' namespace */
} /* end of 'tcg' namespace */

#endif /* __trimesh_h_ */

/* END OF 'trimesh.h' FILE */
