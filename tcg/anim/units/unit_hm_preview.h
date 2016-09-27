/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : unit_hm_preview.h
 * PURPOSE     : Computational geometry project.
 *               Heightfield preview unit.
 * PROGRAMMER  : IR1.
 * LAST UPDATE : 27.09.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __unit_hf_preview_h_
#define __unit_hf_preview_h_

#include "../../def.h"

#include "../unit.h"
#include "../animation.h"
#include "../render/prim/trimesh.h"
#include "../../win/window_list.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* heightmap preview unit class */
  class unit_hm_preview : public unit
  {
  private:
    primitive::trimesh Quad;
    float H, lacunarity, octaves, offset, gain;
    window_list Interface;

    void Update( void )
    {
      Quad.Material->SetUniform("H", H);
      Quad.Material->SetUniform("gain", gain);
      Quad.Material->SetUniform("lacunarity", lacunarity);
      Quad.Material->SetUniform("octaves", octaves);
      Quad.Material->SetUniform("offset", offset);

      float *exponent_array = new float[(int)octaves];
      float frequency = 1.0f;
      for (int i = 0; i < (int)octaves; i++)
      {
        exponent_array[i] = pow(frequency, -H);
        frequency *= lacunarity;
      }
      Quad.Material->AddTexture(Ani->AddTexture("ExponentArray", (int)octaves, 1, exponent_array));
      delete[] exponent_array;
    }

  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     */
    unit_hm_preview( anim *Ani );

    /* Render unit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      Quad.Render();
    } /* End of 'Render' function */
  }; /* End of 'unit_hm_preview' class */
} /* end of 'tcg' namespace */

#endif /* __unit_hf_preview_h_ */

/* END OF 'unit_hm_preview.h' FILE */
