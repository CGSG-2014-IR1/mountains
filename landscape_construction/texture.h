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

#include "def.h"

#include "soil/soil.h"
#include "render.h"

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

      CHAR Path[MAX_STR] = "Textures/";
      strcat(Path, FileName);

      if (!LoadG24(Path) && !LoadPFF(Path) && !LoadFloat(Path))
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
    static BOOL LoadG24( const CHAR *FileName )
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
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
    static BOOL LoadFloat( const CHAR *FileName )
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
          FLOAT *pix = new FLOAT[w * h * sizeof(FLOAT)];
          fseek(F, sizeof(INT) * 2, SEEK_SET);
          fread(pix, sizeof(float), w * h, F);
          BYTE *image = new BYTE[w * h * 3];
          for (INT i = 0; i < w * h; i++)
          {
            BYTE c = pix[i] * 255;
            image[i * 3] = c;
            image[i * 3 + 1] = c;
            image[i * 3 + 2] = c;
          }

          //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
          //glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA_FLOAT32_ATI, w, h, 0, GL_ALPHA, GL_FLOAT, image);

          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
          //glGenerateMipmap(GL_TEXTURE_2D);
          delete[] image;
          isok = TRUE;
        }
        fclose(F);
      }
      return isok;
    } /* End of 'LoadFloat' function */

    /* Load texture from *.BMP, *.PNG, *.JPG, *.TGA, *.DDS, *.PSD, or *.HDR file function.
     * ARGUMENTS:
     *   - file name:
     *       const CHAR *FileName;
     * RETURNS:
     *   (BOOL) TRUE if successfull, FALSE otherwise.
     */
    static BOOL LoadPFF( const CHAR *FileName )
    {
      INT w = 0, h = 0;
      BYTE *image = SOIL_load_image(FileName, &w, &h, 0, SOIL_LOAD_RGB);
      if (image == nullptr)
        return FALSE;
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
