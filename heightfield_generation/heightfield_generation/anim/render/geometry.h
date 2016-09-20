/* Reshetnyak Ivan  */

#ifndef __geometry_h_
#define __geometry_h_

#include "../../def.h"

class geometry
{
protected:
  /* Class constructor
   * ARGUMENTS: None.
   */
  geometry( void )
  {
  } /* End of 'geometry' constructor */

  /* Class destructor
   * ARGUMENTS: None.
   */
  ~geometry( void )
  {
  } /* End of 'geometry' destructor */

public:
  /* All vertexes paint function
   * ARGUMENTS:
   *   - paint color:
   *       const color Col;
   * RETURNS: None.
   */
  VOID Paint( const color &Col )
  {
    for (INT i = 0; i < NumOfV; i++)
      Vert[i].Color = Col;
  } /* End of 'Paint' function */

  /* Primitive type representation enumeration type */
  enum class type
  {
    TRIMESH, GRID, TRIANGLE, PATCH_TRIANGLE
  }; /* End of 'type' class */

  /* Primitive vertex representation class */
  class vertex
  {
  public:
    vec Pos;                                // vertex coordinates
    vec2D<float_type> Tex;                  // vertex texture coordinates
    vec Norm;                               // vertex normal coordinates
    color Color;                            // vertex color

    /* Class copying constructor
     * ARGUMENTS:
     *   - right-hand vertex.
     *       const vertex &NV;
     */
    vertex( const vertex &NV )
    {
      Pos = NV.Pos;
      Norm = NV.Norm;
      Color = NV.Color;
      Tex = NV.Tex;
    } /* End of 'vertex' constructor */

    /* Class filling constructor
     * ARGUMENTS:
     *   - position:
     *       const vec &P = vec(0, 0, 0);
     *   - normal:
     *       const vec &N = vec(0, 1, 0);
     *   - color:
     *       const color &C = color(0.6, 0.1, 0.1);
     *   - texture coordinates:
     *       const vec2 &T = vec2(0, 0);
     */
    vertex( const vec &P = vec(0, 0, 0),
            const vec &N = vec(0, 1, 0),
            const color &C = color(0.6, 0.1, 0.1),
            const vec2D<float_type> &T = vec2D<float_type>(0, 0) ) : Pos(P), Norm(N), Color(C), Tex(T)
    {
    } /* End of 'vertex' constructor */

    /* Vertex copy function.
     * ARGUMENTS:
     *   - right-rand vertex:
     *       vertex &RightV;
     * RETURNS: None.
     */
    vertex & operator=( vertex &RightV )
    {
      Pos = RightV.Pos;
      Norm = RightV.Norm;
      Color = RightV.Color;
      Tex = RightV.Tex;
      return *this;
    } /* End of 'operator=' function */

    /* Class destructor
     */
    ~vertex( VOID )
    {
    } /* End of '~vertex' destructor */
  }; /* End of 'vertex' class */

  type Type;                       /* Geometry type */
  int
    NumOfV,                                 /* Number of vertexes */
    NumOfI,                                 /* Number of indexes  */
    GridW, GridH,                           /* Grid sizes         */
    *Ind;                                   /* Indexes array      */
  vertex *Vert;                             /* Vertexes array     */
}; /* End of 'geometry' class */

#endif /* __geometry_h_ */

/* END OF 'geometry.h' FILE */
