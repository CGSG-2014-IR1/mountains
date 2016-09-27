/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : unit_hm_preview.cpp
 * PURPOSE     : Computational geometry project.
 *               Heightfield preview unit.
 * PROGRAMMER  : IR1.
 * LAST UPDATE : 27.09.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "unit_hm_preview.h"
#include "../../math/noise.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Class constructor.
   * ARGUMENTS:
   *   - animation:
   *       anim *Ani;
   */
  unit_hm_preview::unit_hm_preview( anim *Ani ) : unit(Ani), Quad(Ani),
    Interface("Fractal parameters", [this]{Update();})
  {
    Quad.CreateQuad(vec(1, 1, 0), vec(-1, 1, 0), vec(-1, -1, 0), vec(1, -1, 0));
    Quad.Material = Ani->AddMaterial("hm_preview", "fbm");

    H = 0.4f;
    lacunarity = 6.01f;
    octaves = 8;
    offset = 1.0f;
    gain = 2.0f;

    Update();

    Interface.Push("H", &H);
    Interface.Push("Lacunarity", &lacunarity);
    Interface.Push("Offset", &offset);
    Interface.Push("Octaves", &octaves);
    Interface.Push("Gain", &gain);

    math::noise Noise;
    float *pix = new float[Noise.GetSize() * 2];
    for (int i = 0; i < Noise.GetSize(); i++)
    {
      pix[i] = Noise.GetTable(i);
      pix[i + Noise.GetSize()] = Noise.GetPerm(i);
    }
    Quad.Material->AddTexture(Ani->AddTexture("NoiseTex", Noise.GetSize(), 2, pix));
    delete[] pix;

    Interface.PopUp();
  } /* End of 'unit_hm_preview::unit_hm_preview' constructor */
} /* end of 'tcg' namespace */

/* END OF 'unit_hm_preview.cpp' FILE */
