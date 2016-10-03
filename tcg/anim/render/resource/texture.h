/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : texture.h
 * PURPOSE     : Computational geometry project.
 *               Texture support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 28.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __texture_h_
#define __texture_h_

#include <cstdio>

#include "../../../def.h"

#include "../../../support/soil/soil.h"
#include "../render.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Texture class */
  class texture
  {
    friend class texture_manager;
  private:
    /* Texture number */
    UINT TexNo;

    /* Load texture function.
     * ARGUMENTS:
     *   - file name:
     *       const CHAR *FileName;
     * RETURNS:
     *   (INT) texture number.
     */
    static INT Load( const CHAR *FileName )
    {
      UINT TexNo;
      glGenTextures(1, &TexNo);

      glBindTexture(GL_TEXTURE_2D, TexNo);

      CHAR Path[MAX_STR] = "bin/textures/";
      strcat(Path, FileName);

      if (!LoadG24(Path, TexNo) && !LoadPFF(Path, TexNo) && !LoadFloat(Path, TexNo) && !LoadShort(Path, TexNo))
      {
        glDeleteTextures(1, &TexNo);
        return 0;
      }
      glBindTexture(GL_TEXTURE_2D, 0);
      return TexNo;
    } /* End of 'Load' function */

    /* Load texture from *.G24 file function.
     * ARGUMENTS:
     *   - file name:
     *       const CHAR *FileName;
     * RETURNS:
     *   (BOOL) TRUE if successfull, FALSE otherwise.
     */
    static BOOL LoadG24( const CHAR *FileName, int TexNo )
    {
      BOOL isok = FALSE;

      FILE *F = fopen(FileName, "rb");
      if (F != NULL)
      {
        INT w = 0, h = 0;

        fread(&w, 2, 1, F);
        fread(&h, 2, 1, F);

        fseek(F, 0, SEEK_END);
        INT len;
        if ((len = ftell(F)) == (w * h * 3 + 4))
        {
          BYTE *image = new BYTE[w * h * 3];
          fseek(F, 4, SEEK_SET);
          fread(image, 3, w * h, F);
          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
          gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_BGR_EXT, GL_UNSIGNED_BYTE, image);
          glTextureParameteri(TexNo, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glTextureParameteri(TexNo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTextureParameteri(TexNo, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
          glTextureParameteri(TexNo, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
          delete[] image;
          isok = TRUE;
        }
        fclose(F);
      }
      return isok;
    } /* End of 'LoadG24' function */

    /* Load texture from *.float file function.
     * ARGUMENTS:
     *   - file name:
     *       const CHAR *FileName;
     * RETURNS:
     *   (BOOL) TRUE if successfull, FALSE otherwise.
     */
    static BOOL LoadFloat( const CHAR *FileName, int TexNo )
    {
      BOOL isok = FALSE;

      FILE *F = fopen(FileName, "rb");
      if (F != NULL)
      {
        INT w = 0, h = 0;

        fread(&w, sizeof(INT), 1, F);
        fread(&h, sizeof(INT), 1, F);

        fseek(F, 0, SEEK_END);
        INT len;
        if ((len = ftell(F)) == (w * h * sizeof(FLOAT) + sizeof(INT) * 2))
        {
          FLOAT *pix = new FLOAT[w * h];
          fseek(F, sizeof(INT) * 2, SEEK_SET);
          fread(pix, sizeof(float), w * h, F);

          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
          glTextureParameteri(TexNo, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glTextureParameteri(TexNo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTextureParameteri(TexNo, GL_TEXTURE_WRAP_S, GL_CLAMP);
          glTextureParameteri(TexNo, GL_TEXTURE_WRAP_T, GL_CLAMP);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA_FLOAT32_ATI, w, h, 0, GL_ALPHA, GL_FLOAT, pix);
          glGenerateMipmap(GL_TEXTURE_2D);

          delete[] pix;
          isok = TRUE;
        }
        fclose(F);
      }
      return isok;
    } /* End of 'LoadFloat' function */

    /* Load texture from *.short file function.
     * ARGUMENTS:
     *   - file name:
     *       const CHAR *FileName;
     * RETURNS:
     *   (BOOL) TRUE if successfull, FALSE otherwise.
     */
    static BOOL LoadShort( const CHAR *FileName, int TexNo )
    {
      BOOL isok = FALSE;

      FILE *F = fopen(FileName, "rb");
      if (F != NULL)
      {
        INT w = 0, h = 0;

        fread(&w, sizeof(INT), 1, F);
        fread(&h, sizeof(INT), 1, F);

        fseek(F, 0, SEEK_END);
        INT len;
        if ((len = ftell(F)) == (w * h * sizeof(SHORT) * 3))
        {
          SHORT *pix = new SHORT[w * h * 3];
          fseek(F, sizeof(INT) * 2, SEEK_SET);
          fread(pix, sizeof(SHORT) * 3, w * h, F);

          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
          glTextureParameteri(TexNo, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glTextureParameteri(TexNo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTextureParameteri(TexNo, GL_TEXTURE_WRAP_S, GL_CLAMP);
          glTextureParameteri(TexNo, GL_TEXTURE_WRAP_T, GL_CLAMP);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_SHORT, pix);
          glGenerateMipmap(GL_TEXTURE_2D);

          delete[] pix;
          isok = TRUE;
        }
        fclose(F);
      }
      return isok;
    } /* End of 'LoadShort' function */

    /* Load texture from *.BMP, *.PNG, *.JPG, *.TGA, *.DDS, *.PSD, or *.HDR file function.
     * ARGUMENTS:
     *   - file name:
     *       const CHAR *FileName;
     * RETURNS:
     *   (BOOL) TRUE if successfull, FALSE otherwise.
     */
    static BOOL LoadPFF( const CHAR *FileName, int TexNo )
    {
      INT w = 0, h = 0;
      BYTE *image = SOIL_load_image(FileName, &w, &h, 0, SOIL_LOAD_RGB);
      if (image == nullptr)
        return FALSE;
      glTexParameteri(TexNo, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(TexNo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(TexNo, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(TexNo, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
      glGenerateMipmap(GL_TEXTURE_2D);
      SOIL_free_image_data(image);
      return TRUE;
    } /* End of 'LoadPFF' function */
  public:
    /* Texture name */
    CHAR Name[MAX_STR];

    /* Texture constructor.
     * ARGUMENTS:
     *   - texture name:
     *       CHAR *Name;
     */
    texture( CHAR *Name, CHAR *FileName ) : TexNo(Load(FileName))
    {
      strcpy(this->Name, Name);
    } /* End of 'texture' function */

    /* Texture constructor.
     * ARGUMENTS:
     *   - texture name:
     *       CHAR *Name;
     *   - texture dimensions:
     *       INT W, H;
     *   - texture pixels:
     *       FLOAT *Data.
     */
    texture( CHAR *Name, INT W, INT H, FLOAT *Data )
    {
      glGenTextures(1, &TexNo);
      glBindTexture(GL_TEXTURE_2D, TexNo);

      strcpy(this->Name, Name);

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTextureParameteri(TexNo, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTextureParameteri(TexNo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTextureParameteri(TexNo, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTextureParameteri(TexNo, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA_FLOAT32_ATI,
                   W, H, 0, GL_ALPHA, GL_FLOAT, Data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glBindTexture(GL_TEXTURE_2D, 0);
    } /* End of 'texture' function */

    /* Texture data update function.
     * ARGUMENTS:
     *   - new dimensions:
     *       INT W, H;
     *   - new pixels:
     *       FLOAT *Data.
     */
    void Update( INT W, INT H, FLOAT *Data )
    {
      glBindTexture(GL_TEXTURE_2D, TexNo);

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTextureParameteri(TexNo, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTextureParameteri(TexNo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTextureParameteri(TexNo, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTextureParameteri(TexNo, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA_FLOAT32_ATI,
                   W, H, 0, GL_ALPHA, GL_FLOAT, Data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glBindTexture(GL_TEXTURE_2D, 0);
    } /* End of 'Update' function */

    /* Texture destructor.
     * ARGUMENTS: None.
     */
    ~texture( VOID )
    {
      glDeleteTextures(1, &TexNo);
    } /* End of '~texture' function */

    /* Texture no get function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) texture number.
     */
    INT GetNo( VOID )
    {
      return TexNo;
    } /* End of 'GetNo' function */

    /* Apply texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID )
    {
    } /* End of 'Apply' function */
  }; /* End of 'texture' class */

  /* Texture manager class */
  class texture_manager
  {
  private:
    std::vector<texture *> Textures;

  public:
    /* Class constructor.
     * ARGUMENTS: None.
     */
    texture_manager( VOID );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~texture_manager( VOID );

    /* Add texture function.
     * ARGUMENTS:
     *   - texture name:
     *       CHAR *Name;
     * RETURNS:
     *   (texture *) pointer to added texture.
     */
    texture * AddTexture( CHAR *Name, CHAR *FileName );

    /* Add texture function.
	 * ARGUMENTS:
	 *   - texture name:
	 *       CHAR *Name;
	 *   - texture dimensions:
	 *       INT W, H;
	 *   - texture pixels:
     *       FLOAT *Data.
     */
    texture * AddTexture( CHAR *Name, INT W, INT H, FLOAT *Data );

    /* Get texture function.
     * ARGUMENTS:
     *   - texture name:
     *       CHAR *Name;
     * RETURNS:
     *   (texture *) pointer to material.
     */
    texture * GetTexture( CHAR *Name );
  }; /* End of 'texture_manager' class */
} /* end of 'tcg' namespace */

#endif /* __texture_h_ */

/* END OF 'texture.h' FILE */
