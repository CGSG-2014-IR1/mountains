/* Reshetnyak Ivan */

#ifndef __hm_gen_h_
#define __hm_gen_h_

#include <glut.h>

#include "../def.h"
#include "noise.h"

/* Animation hm_gen class */
class hm_gen
{
public:
  /* Class constructor.
  * ARGUMENTS: None.
  */
  hm_gen( void )
  {
    math::fBm_multi_ridged fBm(0.7, 5.5, 2.0, 0, 9, time(nullptr));
    int w = 1024, size = w * w;
    double b = 7;
    float *pix = new float[size];
    for (int i = 0; i < w; i++)
      for (int j = 0; j < w; j++)
        pix[i * w + j] = fBm(vec(j / (double)w * b, i / (double)w * b, 0));

    FILE *f;

    if ((f = fopen("heightmap1.float", "wb")) == nullptr)
      throw "Too bad - file won't open!";
    fwrite(&w, sizeof(int), 1, f);
    fwrite(&w, sizeof(int), 1, f);
    fwrite(pix, sizeof(float), size, f);
    fclose(f);

    w = 4096;
    size = w * w;
    float step = 1.0 / w;
    vec3D<short> *npix = new vec3D<short>[size];
    for (int i = 0; i < w; i++)
      for (int j = 0; j < w; j++)
      {
        vec3D<double>
          v0 = vec3D<double>(j * step, fBm(vec(j / (double)w * b, i / (double)w * b, 0)), i * step),
          v1 = vec3D<double>(v0.X + step, fBm(vec((j + 1) / (double)w * b, i / (double)w * b, 0)), v0.Z),
          v2 = vec3D<double>(v0.X, fBm(vec(j / (double)w * b, (i + 1) / (double)w * b, 0)), v0.Z + step);
        vec3D<double> r = ((v1 - v0) % (v2 - v0)).Normalized();
        r *= math::sign(r.Y);
        npix[i * w + j] = vec3D<short>(r.X * 32767, r.Y * 32767, r.Z * 32767);
      }
    if ((f = fopen("normalmap1.short", "wb")) == nullptr)
      throw "Too bad - file won't open!";
    fwrite(&w, sizeof(int), 1, f);
    fwrite(&w, sizeof(int), 1, f);
    fwrite(npix, sizeof(vec3D<short>), size, f);

    delete[] npix;
    delete[] pix;
  } /* End of 'hm_gen' constructor */
}; /* End of 'hm_gen' class */

#endif /* __hm_gen_h_ */
