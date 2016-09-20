/* Reshetnyak Ivan */

#ifndef __buffer_h_
#define __buffer_h_

#include <glew.h>
#include <glut.h>

#include "../../def.h"
#include "geometry.h"

#include <vector>

/* Shader data buffer representation class */
class buffer
{
private:
  static std::vector<buffer> BufferLibrary;  /* Buffers library */

public:
  int NumOfI;
  geometry::type Type;

  /* Buffers initialization function
    * ARGUMENTS: None.
    * RETURNS: None.
    */
  void Gen( void )
  {
    if (VertAr != 0)
      return;

    /* Vertex buffer */
    glGenBuffers(1, &Vert);                                         // generating free buffer name
    glBindBuffer(GL_ARRAY_BUFFER, Vert);                            // binding buffer
    glBufferData(GL_ARRAY_BUFFER,
                  sizeof(geometry::vertex) * Geom->NumOfV,
                  Geom->Vert, GL_STATIC_DRAW);                       // setting data

    /* Index buffer */
    glGenBuffers(1, &Ind);                                          // generating free buffer name
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ind);                     // binding buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                  sizeof(INT) * Geom->NumOfI,
                  Geom->Ind, GL_STATIC_DRAW);                        // setting data

    /* Vertex array buffer */
    glGenVertexArrays(1, &VertAr);                                  // generating free buffer name
    glBindVertexArray(VertAr);

    /* Setting shader layout */
    void *i;
    glVertexAttribPointer(0 /* Pos */, 3 /* XYZ */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), i = FieldOffset(geometry::vertex, Pos));    // position
    glVertexAttribPointer(1 /* Norm */, 3 /* XYZ */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), i = FieldOffset(geometry::vertex, Norm));   // normal
    glVertexAttribPointer(2 /* Color */, 4 /* RGBA */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), i = FieldOffset(geometry::vertex, Color));  // color
    glVertexAttribPointer(3 /* Tex */, 2 /* UV */, GL_FLOAT,
                          FALSE /* Need normalize */,
                          sizeof(geometry::vertex), i = FieldOffset(geometry::vertex, Tex));    // texture coordinates

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  } /* End of 'Gen' function */

  unsigned
    Ind,                                   // index buffer
    Vert,                                  // vertex buffer
    VertAr;                                // vertex array buffer
  const geometry *Geom;                    // linked geometry
  INT ID;                                  // library id

  /* Class constructor
   * ARGUMENTS:
   *   - buffer geometry:
   *       constgeometry *Geometry;
   */
  buffer( const geometry *Geometry = nullptr ) : Geom(Geometry), Ind(0), Vert(0), VertAr(0)
  {
    if (Geom != nullptr)
    {
      Gen();
      Type = Geom->Type;
      NumOfI = Geom->NumOfI;
      ID = BufferLibrary.size();
      BufferLibrary.push_back(*this);
    }
  } /* End of 'buffer' constructor */

  /* Class destructor
   * ARGUMENTS: None.
   */
  ~buffer( VOID )
  {
  } /* End of 'buffer' destructor */

  static buffer * Get( int Id )
  {
    return &BufferLibrary[Id];
  }
}; /* End of 'buffer' class */

#endif /* __buffer_h_ */

/* END OF 'buffer.h' FILE */
