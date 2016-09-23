/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : patch3.h
 * PURPOSE     : Computational geometry project.
 *               Primitive samples declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __patch3_h_
#define __patch3_h_

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
    /* Primitive patch3 class */
    class patch3 : public prim
    {
    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       */
      patch3( anim *Ani );

      /* Class destructor.
       * ARGUMENTS: None.
       */
      ~patch3( VOID );

      /* Draw primitive function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Render( VOID );
    }; /* End of 'patch3' class */
  } /* end of 'primitive' namespace */
} /* end of 'tcg' namespace */

#endif /* __patch3_h_ */

/* END OF 'patch3.h' FILE */
