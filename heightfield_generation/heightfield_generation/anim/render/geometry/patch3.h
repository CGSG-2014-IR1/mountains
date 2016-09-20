/* Reshetnyak Ivan */

#ifndef __patch3_h_
#define __patch3_h_

#include "../../../def.h"
#include "../geometry.h"

/* Draw primitive representation class */
class patch3 : public geometry
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
  patch3( int NoofV, int NoofI, vertex *Vertx, int *Indx )
  {
    Type = type::PATCH_TRIANGLE;
    NumOfV = NoofV;
    NumOfI = NoofI;
    Vert = new vertex[NumOfV];
    for (int i = 0; i < NumOfV; i++)
      Vert[i] = Vertx[i];
    Ind = new int[NumOfI];
    for (int i = 0; i < NumOfI; i++)
      Ind[i] = Indx[i];
  } /* End of 'patch3' constructor */

  /* Class constructor.
   * ARGUMENTS: None.
   */
  patch3( void )
  {
    Type = type::TRIMESH;
    NumOfV = 0;
    NumOfI = 0;
    Vert = nullptr;
    Ind = nullptr;
  } /* End of 'patch3' constructor */

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
  } /* End of 'patch3' constructor */

  /* Class destructor */
  ~patch3( VOID )
  {
    delete[] Ind;
    delete[] Vert;
  } /* End of '~patch3' destructor */
}; /* End of 'patch3' class */

#endif /* __patch3_h_ */

/* END OF 'patch3.h' FILE */
