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

      /* Create mountain function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       *   - points:
       *       const std::vector<vec> &Points;
       *   - triangles:
       *       const std::vector<math::triangle> &Triangles;
       *   - IDs:
       *       const std::vector<math::triangle> &IDs;
       * RETURNS: None.
       */
      VOID CreateMountain( anim *Ani, const std::vector<vec> &Points,
        const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs );

      /* Create mountain function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       *   - points:
       *       const std::vector<vec> &Points;
       *   - triangles:
       *       const std::vector<math::triangle> &Triangles;
       *   - IDs:
       *       const std::vector<math::triangle> &IDs;
       *   - height identifiers:
       *       const std::vector<math::triangle> &P0, &P1, &H0, &H1;
       * RETURNS: None.
       */
      VOID CreateMountain( anim *Ani, const std::vector<vec> &Points,
        const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs,
        const std::vector<INT> &P0, const std::vector<INT> &P1, const std::vector<INT> &H0, const std::vector<INT> &H1 );

      /* Create road function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       *   - points:
       *       const std::vector<vec> &Points;
       *   - triangles:
       *       const std::vector<math::triangle> &Triangles;
       *   - texture coordinates:
       *       const std::vector<tsg::TVec<uv>> &TextureCoords;
       *   - heights:
       *       const std::vector<INT> &Heights;
       *   - height identifiers:
       *       const std::vector<math::triangle> &P0, &P1, &H0, &H1;
       * RETURNS: None.
       */
      VOID CreateRoad( anim *Ani, const std::vector<vec> &Points, const std::vector<math::triangle> &Triangles,
        const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<math::triangle> &Heights,
        const std::vector<math::triangle> &P0, const std::vector<math::triangle> &P1,
        const std::vector<math::triangle> &H0, const std::vector<math::triangle> &H1 );

      /* Create village function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       *   - points:
       *       const std::vector<vec> &Points;
       *   - triangles:
       *       const std::vector<math::triangle> &Triangles;
       *   - IDs:
       *       const std::vector<math::triangle> &IDs;
       *   - texture coordinates:
       *       const std::vector<tsg::TVec<uv>> &TextureCoords;
       *   - heights:
       *       const std::vector<INT> &Heights;
       * RETURNS: None.
       */
      VOID CreateVillage( anim *Ani, const std::vector<vec> &Points,
        const std::vector<math::triangle> &Triangles, const std::vector<math::triangle> &IDs,
        const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<INT> &Heights );

      /* Class destructor.
       * ARGUMENTS: None.
       */
      ~trimesh( VOID );
    }; /* End of 'trimesh' class */
  } /* end of 'primitive' namespace */
} /* end of 'tcg' namespace */

#endif /* __primitive_samples_h_ */

/* END OF 'primitive_samples.h' FILE */
