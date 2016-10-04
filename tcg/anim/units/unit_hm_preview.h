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
#include "../../math/noise.h"
#include "../../support/hm_gen.h"
#include "unit_road/unit_road.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* heightmap preview unit class */
  class unit_hm_preview : public unit
  {
  private:
    primitive::trimesh Quad;
    float H, Lacunarity, Octaves, Offset, Gain, FSeed;
    window_list Interface;
    bool Rend, N;

    int Load( void )
    {
      FILE *F = fopen("bin/input/fractal.data", "rb");

      if (F == nullptr)
        return 0;

      char c;
      int cnt = 0;
      float pars[8];
      while ((c = fgetc(F)) != EOF)
      {
        if (c == ';')
        {
          char Buf[400];
          fgets(Buf, 399, F);
          continue;
        }
        ungetc(c, F);
        fscanf(F, "%f", &pars[cnt]);
        if (cnt == 0)
          if (pars[0] == 0)
          {
            fclose(F);
            return 0;
          }
        if (cnt == 1)
          if (pars[1] == 0)
          {
            fclose(F);
            return 2;
          }
        cnt++;
      }
      H = pars[2];
      Octaves = pars[3];
      Lacunarity = pars[4];
      Gain = pars[5];
      Offset = pars[6];
      FSeed = pars[7];
      fclose(F);
      return 1;
    }

    void Gen( void )
    {
      hm_gen(H, Lacunarity, Gain, Offset, Octaves, (INT)(FSeed * 100));
      *Ani << new unit_road(this->Ani);
      Rend = false;
    }

    void Update( void )
    {
      Quad.Material->SetUniform("H", H);
      Quad.Material->SetUniform("gain", Gain);
      Quad.Material->SetUniform("lacunarity", Lacunarity);
      Quad.Material->SetUniform("octaves", Octaves);
      Quad.Material->SetUniform("offset", Offset);

      float *exponent_array = new float[(int)Octaves];
      float frequency = 1.0f;
      for (int i = 0; i < (int)Octaves; i++)
      {
        exponent_array[i] = pow(frequency, -H);
        frequency *= Lacunarity;
      }
      Quad.Material->AddTexture(Ani->AddTexture("ExponentArray", (int)Octaves, 1, exponent_array));
      delete[] exponent_array;

      math::noise Noise((INT)(FSeed * 100));
      float *pix = new float[Noise.GetSize() * 2];
      for (int i = 0; i < Noise.GetSize(); i++)
      {
        pix[i] = Noise.GetTable(i);
        pix[i + Noise.GetSize()] = Noise.GetPerm(i);
      }
      Quad.Material->AddTexture(Ani->AddTexture("NoiseTex", Noise.GetSize(), 2, pix));
      Quad.Material->SetUniform("ISN", 0);
      delete[] pix;

      Interface.PopUp();
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
      if (!Rend)
        return;
      Quad.Render();
    } /* End of 'Render' function */

    VOID Response( VOID )
    {
      if (Ani->KeysClick['N'])
      {
        N = !N;
        Quad.Material->SetUniform("ISN", N ? 1 : 0);
      }
    }
  }; /* End of 'unit_hm_preview' class */
} /* end of 'tcg' namespace */

#endif /* __unit_hf_preview_h_ */

/* END OF 'unit_hm_preview.h' FILE */
