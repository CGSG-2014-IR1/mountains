/* Reshetnyak Ivan */

#ifndef __hm_gen_h_
#define __hm_gen_h_

#include <ctime>

#include "../def.h"
#include "../math/noise.h"

namespace tcg
{
  using namespace math;
  /* Animation hm_gen class */
  class hm_gen
  {
  public:
    /* Class constructor.
     * ARGUMENTS: None.
     */
    hm_gen( double H, double Lacunarity, double Gain, double Offset, double Octaves, int Seed )
    {
      math::fBm_multi_ridged fBm(H, Lacunarity, Gain, Offset, Octaves, Seed);
      int w = 1024, size = w * w;
      double b = 10;
      float *pix = new float[size];
      for (int i = 0; i < w; i++)
        for (int j = 0; j < w; j++)
          pix[i * w + j] = fBm(vec(j / (double)w * b, i / (double)w * b, 0));

      FILE *f;

      if ((f = fopen("bin/textures/heightmap1.float", "wb")) == nullptr)
        throw "Too bad - file won't open!";
      fwrite(&w, sizeof(int), 1, f);
      fwrite(&w, sizeof(int), 1, f);
      fwrite(pix, sizeof(float), size, f);
      fclose(f);
  
      w = 4096;
      size = w * w;
      float step = 1.0 / w;
      tsg::TVec<short> *npix = new tsg::TVec<short>[size];
      for (int i = 0; i < w; i++)
        for (int j = 0; j < w; j++)
        {
          tsg::TVec<double>
            v0 = tsg::TVec<double>(j / (double)w * b, fBm(vec(j / (double)w * b, i / (double)w * b, 0)), i / (double)w * b),
            v1 = tsg::TVec<double>((j + 1) / (double)w * b, fBm(vec((j + 1) / (double)w * b, i / (double)w * b, 0)), i / (double)w * b),
            v2 = tsg::TVec<double>(j / (double)w * b, fBm(vec(j / (double)w * b, (i + 1) / (double)w * b, 0)), (i + 1) / (double)w * b);
          tsg::TVec<double> r = ((v1 - v0) % (v2 - v0)).Normalizing();
          r *= Sign(r.Y);
          npix[i * w + j] = tsg::TVec<short>(r.X * 32767, r.Y * 32767, r.Z * 32767);
        }
      if ((f = fopen("bin/textures/normalmap1.short", "wb")) == nullptr)
        throw "Too bad - file won't open!";
      fwrite(&w, sizeof(int), 1, f);
      fwrite(&w, sizeof(int), 1, f);
      fwrite(npix, sizeof(tsg::TVec<short>), size, f);
      fclose(f);
  
      delete[] npix;
      delete[] pix;
    } /* End of 'hm_gen' constructor */
  }; /* End of 'hm_gen' class */
} /* End of 'tcg' namespace */

#endif /* __hm_gen_h_ */
