/* Reshetnyak Ivan */

#ifndef __texture_h_
#define __texture_h_

#include <cstdio>

#define GLEW_STATIC
#pragma comment(lib, "glew32s")

#include <glew.h>
#include <glut.h>

#include "../../../def.h"

/* Texture sampler get by id macro definition */
#define TEXTURE_SAMPLER(N) \
  (GL_TEXTURE0 + N)

/* Texture representation class */
class texture
{
private:
  static unsigned LastAppliedTexture;  /* Last applied texture OpenGL id */
  int
    W, H,                              /* Texture sizes */
    Sampler;                           /* Texture sampler number */
  unsigned ID;                         /* Texture OpenGL id */

  /* Texture apply function
   * ARGUMENTS:
   *   - .g24 file path:
   *       const char *FileName;
   * RETURNS: None.
   */
  bool LoadG24( const char *FileName )
  {
    if (FileName == nullptr)
    {
      /* Set 'default' checker texture */
      W = H = 2;
      BYTE bits[4] = {0, 1, 0, 1};
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);              /* Set unpack alignment to 1 to support any image size */
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, W, H,
                        GL_BGR, GL_LUMINANCE, bits);      /* Building texture mipmaps */
      return true;
    }
    if (strstr(FileName, "g24") == nullptr)
      return false;

    glActiveTexture(TEXTURE_SAMPLER(Sampler));
    glBindTexture(GL_TEXTURE_2D, ID);
    FILE *F = fopen(FileName, "rb");                      /* Open file */
    if (F != nullptr)
    {
      /*** File opened succesfully ***/
      /* Scanning sizes */
      fread(&W, 2, 1, F);
      fread(&H, 2, 1, F);
      BYTE *bits = new BYTE[W * H * 3];                   /* Loaded image */

      fread(bits, 3, W * H, F);                           /* Read image */
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);              /* Set unpack alignment to 1 to support any image size */

      //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, W, H,
      //                  GL_BGR, GL_UNSIGNED_BYTE, bits);  /* Building texture mipmaps */

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
      glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

      delete[] bits;
      fclose(F);
    }
    return true;
  } /* End of 'LoadG24' function */

  bool LoadShort( const char *FileName )
  {
    if (strstr(FileName, "short") == nullptr)
      return false;
    glActiveTexture(TEXTURE_SAMPLER(Sampler));
    glBindTexture(GL_TEXTURE_2D, ID);
    FILE *F = fopen(FileName, "rb");                      /* Open file */
    if (F != nullptr)
    {
      /*** File opened succesfully ***/
      /* Scanning sizes */
      fread(&W, sizeof(int), 1, F);
      fread(&H, sizeof(int), 1, F);
      short *bits = new short[W * H * 3];                   /* Loaded image */

      fread(bits, sizeof(short) * 3, W * H, F);                           /* Read image */
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);              /* Set unpack alignment to 1 to support any image size */

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_SHORT, bits);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
      glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

      delete[] bits;
      fclose(F);
    }
    return true;
  }

public:
  /* Class constructor.
   * ARGUMENTS:
   *   - texture sampler number:
   *       int SamplerNumber;
   *   - image path:
   *       const char *FileName;
   */
  texture( int SamplerNumber, const char *FileName ) : Sampler(SamplerNumber), W(0), H(0)
  {
    glGenTextures(1, &ID);
    if (!(LoadG24(FileName) || LoadShort(FileName)))
      throw "OHSH";
  } /* End of 'texture' constructor */

  texture( int SamplerNumber, int W, int H, const float *Pixels ) : Sampler(SamplerNumber), W(W), H(H)
  {
    glGenTextures(1, &ID);

    glActiveTexture(TEXTURE_SAMPLER(Sampler));
    glBindTexture(GL_TEXTURE_2D, ID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);              /* Set unpack alignment to 1 to support any image size */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA_FLOAT32_ATI, W, H, 0, GL_ALPHA, GL_FLOAT, Pixels);

    glTextureParameteri(ID, GL_TEXTURE_MAX_LEVEL, 0);
    glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP);
  }

  /* Texture apply function
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Apply( VOID ) const
  {
    if (LastAppliedTexture != ID)
    {
      glActiveTexture(TEXTURE_SAMPLER(Sampler));
      glBindTexture(GL_TEXTURE_2D, ID);
      LastAppliedTexture = ID;
    }
  } /* End of 'Apply' function */

  /* Class destructor
   */
  ~texture( VOID )
  {
  } /* End of '~texture' destructor */
}; /* End of 'texture' class */

#endif /* __texture_h_ */

/* END OF 'texture.h' FILE */
