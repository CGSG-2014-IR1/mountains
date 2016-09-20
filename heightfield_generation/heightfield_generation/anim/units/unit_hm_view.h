/* Reshetnyak Ivan */

#ifndef __unit_hm_view_h_
#define __unit_hm_view_h_

#include <glut.h>

#include "../../def.h"
#include "../../math/noise.h"
#include "../render/resource/material.h"
#include "../render/geometry/patch3.h"
#include "../render/primitive.h"

/* Animation unit_hm_view class */
class unit_hm_view : public unit
{
private:
  primitive Rect;
  int SceneSize;
  material Mtl;
  float H, lacunarity, octaves, offset, gain;

  float * LoadFloat( const char *FileName, int &w, int &h )
  {
    FILE *f = fopen(FileName, "rb");
    if (f == nullptr)
      throw "OHSH";

    fread(&w, sizeof(int), 1, f);
    fread(&h, sizeof(int), 1, f);

    float *pix = new float[w * h];
    fread(pix, sizeof(float), w * h, f);
    fclose(f);

    return pix;
  }

public:
  /* Class constructor.
  * ARGUMENTS: None.
  */
  unit_hm_view( anim &Ani ) : Mtl("hmview")
  {
    Ani.Camera.Set(vec(0, 1.3, -1.3), vec(0, 0, 0), vec(0, 1, 0));
    geometry::vertex vx[32 * 32];
    int w = 32;
    float s = 1.0 / w;
    for (int i = 0; i < w; i++)
      for (int j = 0; j < w; j++)
        vx[i * w + j] = geometry::vertex(vec(s * i, 0, s * j));

    int ix[31 * 31 * 6];
    for (int i = 0; i < w - 1; i++)
      for (int j = 0; j < w - 1; j++)
      {
        ix[i * (w - 1) * 6 + j * 6 + 0] = i * w + j;
        ix[i * (w - 1) * 6 + j * 6 + 1] = i * w + j + 1;
        ix[i * (w - 1) * 6 + j * 6 + 2] = (i + 1) * w + j;
        ix[i * (w - 1) * 6 + j * 6 + 3] = i * w + j + 1;
        ix[i * (w - 1) * 6 + j * 6 + 4] = (i + 1) * w + j;
        ix[i * (w - 1) * 6 + j * 6 + 5] = (i + 1) * w + j + 1;
      }
    patch3 geom(w * w, (w - 1) * (w - 1) * 6, vx, ix);
    Rect.Set(&geom, Mtl.ID);

    float *pix = LoadFloat("heightmap1.float", w, w);
    material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(0, w, w, pix));
    delete[] pix;

    math::noise Noise;
    pix = new float[Noise.GetSize() * 2];
    for (int i = 0; i < Noise.GetSize(); i++)
    {
      pix[i] = Noise.GetTable(i);
      pix[i + Noise.GetSize()] = Noise.GetPerm(i);
    }
    material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(1, Noise.GetSize(), 2, pix));
    material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(2, "bin/textures/ec2.g24"));
    delete[] pix;

    material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(3, "normalmap1.short"));

    float
      octaves = 4,
      lacunarity = 4.5,
      H = 2.2;
    material::MaterialLibrary[Mtl.ID].AddUniform(         "H", H);
    material::MaterialLibrary[Mtl.ID].AddUniform(      "gain", 2.0f);
    material::MaterialLibrary[Mtl.ID].AddUniform("lacunarity", lacunarity);
    material::MaterialLibrary[Mtl.ID].AddUniform(   "octaves", octaves);
    material::MaterialLibrary[Mtl.ID].AddUniform(    "offset", 0.0f);
    float *exponent_array = new float[(int)octaves];
    float frequency = 1.0f;
    for (int i = 0; i < (int)octaves; i++)
    {
      exponent_array[i] = pow(frequency, -H);
      frequency *= lacunarity;
    }
    material::MaterialLibrary[Mtl.ID].Textures.push_back(texture(4, (int)octaves, 1, exponent_array));
    delete[] exponent_array;
  } /* End of 'unit_hm_view' constructor */

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
    if (Ani.Keys[32])
      Ani.Camera.Move(-Ani.Camera.Dir * Ani.Timer.GlobalDeltaTime * 0.4);
    if (Ani.Keys['x'])
      Ani.Camera.Move(Ani.Camera.Dir * Ani.Timer.GlobalDeltaTime * 0.4);

    if (Ani.Keys['w'])
      Ani.Camera.Rotate(Ani.Camera.Right, 90 * Ani.Timer.GlobalDeltaTime);
    else if (Ani.Keys['s'])
      Ani.Camera.Rotate(Ani.Camera.Right, -90 * Ani.Timer.GlobalDeltaTime);

    if (Ani.Keys['a'])
      Ani.Camera.Rotate(Ani.Camera.Up, 90 * Ani.Timer.GlobalDeltaTime);
    else if (Ani.Keys['d'])
      Ani.Camera.Rotate(Ani.Camera.Up, -90 * Ani.Timer.GlobalDeltaTime);
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
  } /* End of 'Keyboard' function */
}; /* End of 'unit_hm_view' class */

#endif /* __unit_hm_view_h_ */
