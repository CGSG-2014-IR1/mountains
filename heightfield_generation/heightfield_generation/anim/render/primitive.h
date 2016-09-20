/* Reshetnyak Ivan  */

#ifndef __primitive_h_
#define __primitive_h_

#include <cstdlib>

#include "../../def.h"
#include "buffer.h"
#include "resource/material.h"

/* Draw primitive representation class */
class primitive
{
protected:
  int Material;  /* Primitive material id */
  int Buffer;    /* geometry buffer id */

public:
  /* Class constructor
   * ARGUMENTS:
   *   - primitive geometry:
   *       geometry *Geom = nullptr;
   *   - primitive material id:
   *       int Mtl = 0;
   */
  primitive( geometry *Geom = nullptr, int Mtl = 0 ) : Material(Mtl)
  {
    if (Geom != nullptr)
    {
      buffer PrimBuffer(Geom);
      Buffer = PrimBuffer.ID;
    }
  } /* End of 'primitive' constructor */

  /* Data set function.
   * ARGUMENTS:
   *   - primitive geometry:
   *       geometry *Geom = nullptr;
   *   - primitive material id:
   *       int Mtl = 0;
   * RETURNS: None.
   */
  void Set( geometry *Geom = nullptr, int Mtl = -1 )
  {
    if (Geom != nullptr)
    {
      buffer PrimBuffer(Geom);
      Buffer = PrimBuffer.ID;
    }
    if (Mtl != -1)
      Material = Mtl;
  } /* End of 'Set' function */

  /* Class destructor
   */
  ~primitive( void )
  {
  } /* End of '~primitive' destructor */

  /* Primitive draw function.
   * ARGUMENTS:
   *   - override material id (-1 for no override):
   *       INT Mtl = -1;
   *   - override shader id (-1 for no override):
   *       INT Shd = -1;
   * RETURNS: None.
   */
  virtual void Draw( INT Mtl = -1, INT Shd = -1 )
  {
    /* Setting shader layout */
    glVertexAttribPointer(0 /* Pos */, 3 /* XYZ */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), FieldOffset(geometry::vertex, Pos));    /* Position */
    glVertexAttribPointer(1 /* Norm */, 3 /* XYZ */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), FieldOffset(geometry::vertex, Norm));   /* Normal */
    glVertexAttribPointer(2 /* Color */, 4 /* RGBA */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), FieldOffset(geometry::vertex, Color));  /* Color */
    glVertexAttribPointer(3 /* Tex */, 2 /* UV */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), FieldOffset(geometry::vertex, Tex));    /* Texture coordinates */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    material *CurMtl = material::GetMaterial(Mtl == -1 ? Material : Mtl);
    CurMtl->Apply(Shd);                    // applying material

    /* Drawing */
    buffer *CurBuf = buffer::Get(Buffer);

    CurBuf->Gen();
    switch (CurBuf->Type)
    {
    case geometry::type::TRIMESH:
      glBindVertexArray(CurBuf->VertAr);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurBuf->Ind);
      glDrawElements(GL_TRIANGLES, CurBuf->NumOfI, GL_UNSIGNED_INT, NULL);
      break;
    case geometry::type::GRID:
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurBuf->Ind);
      for (int i = 0; i < CurBuf->Geom->GridH - 1; i++)
        glDrawElementsBaseVertex(GL_TRIANGLE_STRIP, CurBuf->Geom->NumOfI,
                                 GL_UNSIGNED_INT, (VOID *)0,
                                 i * CurBuf->Geom->GridW);
      break;
    case geometry::type::TRIANGLE:
      glBindVertexArray(CurBuf->VertAr);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      break;
    case geometry::type::PATCH_TRIANGLE:
      glBindVertexArray(CurBuf->VertAr);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurBuf->Ind);
      glPatchParameteri(GL_PATCH_VERTICES, 3);
      glDrawElements(GL_PATCHES, CurBuf->NumOfI, GL_UNSIGNED_INT, NULL);
      break;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    shader::Disable();
  } /* End of 'Draw' function */

  /* Primitive material set function.
   * ARGUMENTS:
   *   - new material id:
   *       INT Mtl;
   * RETURNS: None.
   */
  VOID SetMtl( INT Mtl )
  {
    Material = Mtl;
  } /* End of 'SetMtl' function */
}; /* End of 'primitive' class */

#endif /* __primitive_h_ */

/* END OF 'primitive.h' FILE */
