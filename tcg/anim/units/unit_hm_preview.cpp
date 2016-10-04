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

/* Computational geometry project namespace */
namespace tcg
{
  /* Class constructor.
   * ARGUMENTS:
   *   - animation:
   *       anim *Ani;
   */
  unit_hm_preview::unit_hm_preview( anim *Ani ) : unit(Ani), Quad(Ani),
    Interface("Fractal parameters", [this]{Update();},
              [this]{Gen();})
  {
    int r;
    if (r = Load())
    {
      Interface.Begone();
      Rend = false;
      if (r == 1)
        Gen();
      else
        *Ani << new unit_road(this->Ani);
      return;
    }
    N = true;
    Quad.CreateQuad(vec(1, 1, 0), vec(-1, 1, 0), vec(-1, -1, 0), vec(1, -1, 0));
    Quad.Material = Ani->AddMaterial("hm_preview", "fbm");

    H = 0.4f;
    Lacunarity = 6.01f;
    Octaves = 8;
    Offset = 1.0f;
    Gain = 2.0f;
    FSeed = 30.59;

    Update();

    Interface.Push("H", &H);
    Interface.Push("Lacunarity", &Lacunarity);
    Interface.Push("Offset", &Offset);
    Interface.Push("Octaves", &Octaves);
    Interface.Push("Gain", &Gain);
    Interface.Push("Seed (int)", &FSeed);

    Rend = true;
  } /* End of 'unit_hm_preview::unit_hm_preview' constructor */
} /* end of 'tcg' namespace */

/* END OF 'unit_hm_preview.cpp' FILE */
