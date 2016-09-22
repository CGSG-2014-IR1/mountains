/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : primitive_samples.h
 * PURPOSE     : Computational geometry project.
 *               Primitive samples declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __primitive_samples_h_
#define __primitive_samples_h_

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
    }; /* End of 'trimesh' class */
  } /* end of 'primitive' namespace */
} /* end of 'tcg' namespace */

#endif /* __primitive_samples_h_ */

/* END OF 'primitive_samples.h' FILE */
