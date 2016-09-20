/* Reshetnyak Ivan */

#ifndef __unit_hf_gen_h_
#define __unit_hf_gen_h_

#include <glut.h>

#include "../../def.h"
#include "../../math/noise.h"
#include "../render/resource/material.h"
#include "../render/geometry/trimesh.h"
#include "../render/primitive.h"

/* Animation unit_hf_gen class */
class unit_hf_gen : public unit
{
private:
  primitive Rect;
  int SceneSize;
  material Mtl;
  float H, lacunarity, octaves, offset, gain;

public:
  /* Class constructor.
  * ARGUMENTS: None.
  */
  unit_hf_gen( void ) : Mtl("hfgen")
  {
    geometry::vertex vx[4] =
      {
        geometry::vertex(vec(-1, -1, 1)),
        geometry::vertex(vec( 1, -1, 1)),
        geometry::vertex(vec( 1,  1, 1)),
        geometry::vertex(vec(-1,  1, 1))
      };

    int ix[6] = {0, 1, 3, 2, 3, 1}; 
    trimesh geom(4, 6, vx, ix);
    Rect.Set(&geom, Mtl.ID);

    H = 0.4f;
    lacunarity = 6.01f;
    octaves = 8;
    offset = 1.0f;
    gain = 2.0f;

    material::MaterialLibrary[Mtl.ID].AddUniform("H", H);
    material::MaterialLibrary[Mtl.ID].AddUniform("gain", gain);
    material::MaterialLibrary[Mtl.ID].AddUniform("lacunarity", lacunarity);
    material::MaterialLibrary[Mtl.ID].AddUniform("octaves", octaves);
    material::MaterialLibrary[Mtl.ID].AddUniform("offset", offset);

    float *exponent_array = new float[(int)octaves];
    float frequency = 1.0f;
    for (int i = 0; i < (int)octaves; i++)
    {
      exponent_array[i] = pow(frequency, -H);
      frequency *= lacunarity;
    }
    material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(0, (int)octaves, 1, exponent_array));
    delete[] exponent_array;

    math::noise Noise;
    float *pix = new float[Noise.GetSize() * 2];
    for (int i = 0; i < Noise.GetSize(); i++)
    {
      pix[i] = Noise.GetTable(i);
      pix[i + Noise.GetSize()] = Noise.GetPerm(i);
    }
    material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(1, Noise.GetSize(), 2, pix));
    delete[] pix;
  } /* End of 'unit_hf_gen' constructor */

    /* Unit render function.
    * ARGUMENTS:
    *   - animation structure reference.
    *       anim &Ani;
    * RETURNS: None.
    */
  void Render( anim &Ani )
  {
    Rect.Draw();
  } /* End of 'Render' function */

    /* Unit render function.
    * ARGUMENTS:
    *   - animation structure reference.
    *       anim &Ani;
    * RETURNS: None.
    */
  void Response( anim &Ani )
  {
  } /* End of 'Response' function' */

    /* Unit keyboard callback function.
    * ARGUMENTS:
    *   - animation structure reference.
    *       anim &Ani;
    *   - pressed key code:
    *       unsigned char Key;
    *   - mouse coordinates:
    *       int X, Y;
    * RETURNS: None.
    */
  void Keyboard( anim &Ani, unsigned char Key, int X, int Y )
  {
    float *exponent_array;
    float frequency = 1.0f;
    switch (Key)
    {
    case 'w':
      lacunarity += 0.01;
      material::MaterialLibrary[Mtl.ID].SetUniform("lacunarity", lacunarity);
      break;
    case 's':
      lacunarity -= 0.01;
      material::MaterialLibrary[Mtl.ID].SetUniform("lacunarity", lacunarity);
      break;
    case 'q':
      gain += 0.01;
      material::MaterialLibrary[Mtl.ID].SetUniform("gain", gain);
      break;
    case 'a':
      gain -= 0.01;
      material::MaterialLibrary[Mtl.ID].SetUniform("gain", gain);
      break;
    case '+':
      octaves += 1;
      material::MaterialLibrary[Mtl.ID].SetUniform("octaves", octaves);
      exponent_array = new float[(int)octaves];
      for (int i = 0; i < (int)octaves; i++)
      {
        exponent_array[i] = pow(frequency, -H);
        frequency *= lacunarity;
      }
      material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(0, (int)octaves, 1, exponent_array));
      delete[] exponent_array;
      break;
    case '-':
      octaves -= 1;
      if (octaves <= 0)
        octaves++;
      material::MaterialLibrary[Mtl.ID].SetUniform("octaves", octaves);
      exponent_array = new float[(int)octaves];
      for (int i = 0; i < (int)octaves; i++)
      {
        exponent_array[i] = pow(frequency, -H);
        frequency *= lacunarity;
      }
      material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(0, (int)octaves, 1, exponent_array));
      delete[] exponent_array;
      break;
    }
  } /* End of 'Keyboard' function */
}; /* End of 'unit_hf_gen' class */

#endif /* __unit_hf_gen_h_ */
