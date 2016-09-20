/* Reshetnyak Ivan */

#ifndef __trimesh_h_
#define __trimesh_h_

#include "../../../def.h"
#include "../geometry.h"

/* Draw primitive representation class */
class trimesh : public geometry
{
public:
  /* Class constructor.
   * ARGUMENTS:
   *   - number of vertexes:
   *       int NoofV;
   *   - number of indexes:
   *       int NoofI;
   *   - vertexes array:
   *       vertex *Vertx;
   *   - indexes array:
   *       int *Indx;
   */
  trimesh( int NoofV, int NoofI, vertex *Vertx, int *Indx )
  {
    Type = type::TRIMESH;
    NumOfV = NoofV;
    NumOfI = NoofI;
    Vert = new vertex[NumOfV];
    for (int i = 0; i < NumOfV; i++)
      Vert[i] = Vertx[i];
    Ind = new int[NumOfI];
    for (int i = 0; i < NumOfI; i++)
      Ind[i] = Indx[i];
  } /* End of 'trimesh' constructor */

  /* Class constructor.
   * ARGUMENTS: None.
   */
  trimesh( void )
  {
    Type = type::TRIMESH;
    NumOfV = 0;
    NumOfI = 0;
    Vert = nullptr;
    Ind = nullptr;
  } /* End of 'trimesh' constructor */

  /* Geometry set function.
   * ARGUMENTS:
   *   - number of vertexes:
   *       int NoofV;
   *   - number of indexes:
   *       int NoofI;
   *   - vertexes array:
   *       vertex *Vertx;
   *   - indexes array:
   *       int *Indx;
   */
  void Set( int NoofV, int NoofI, vertex *Vertx, int *Indx )
  {
    NumOfV = NoofV;
    NumOfI = NoofI;
    if (Vert != nullptr)
      delete[] Vert;
    Vert = new vertex[NumOfV];
    for (int i = 0; i < NumOfV; i++)
      Vert[i] = Vertx[i];

    if (Ind != nullptr)
      delete[] Ind;
    Ind = new int[NumOfI];
    for (int i = 0; i < NumOfI; i++)
      Ind[i] = Indx[i];
  } /* End of 'trimesh' constructor */

  /* Class destructor */
  ~trimesh( VOID )
  {
    delete[] Ind;
    delete[] Vert;
  } /* End of '~trimesh' destructor */
}; /* End of 'trimesh' class */

#endif /* __trimesh_h_ */

/* END OF 'trimesh.h' FILE */
