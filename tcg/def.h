/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Computational geometry project.
 *               Common definitions.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 14.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __def_h_
#define __def_h_

#include "math/tsg/tsgcam.h"
#include "math/tsg/tsgcolor.h"
#include "math/tsg/tsgdef.h"
#include "math/tsg/tsgmatrx.h"
#include "math/tsg/tsgray.h"
#include "math/tsg/tsgtrans.h"
#include "math/tsg/tsgvect.h"
#include "math/math.h"

/* Debug memory allocation support */ 
#ifdef _DEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __oops;

#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
# define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

/* Common useful types */
typedef DOUBLE DBL;
typedef FLOAT FLT;
typedef __int64 INT64;
typedef unsigned __int64 UINT64;

/* Forward declaration */
namespace tcg
{
  /* Maximum string size */
  const int MAX_STR = 300;

  /* Base math types */
  typedef tsg::TVec<DOUBLE> vec;
  typedef tsg::TVec<FLOAT> vecf;
  typedef tsg::TColor<FLOAT> color;

  typedef tsg::TRay<DOUBLE> ray;

  typedef tsg::TMatr<FLOAT> matr;
  typedef tsg::TTrans<FLOAT> trans;
  typedef tsg::TCam<FLOAT> camera;

  /* Forward declaration */
  class win;
  class anim;
  class unit;
  class render;
  class prim;

  /* Value range remap function.
   * ARGUMENTS:
   *   - value:
   *       double x;
   *   - source range:
   *       double a0, double a1;
   *   - destination range:
   *       double b0, b1;
   * RETURNS:
   *   (double) remapped value.
   */
  inline double Map( double x, double a0, double a1, double b0, double b1 )
  {
    x -= a0;
    x /= (a1 - a0);
    x *= (b1 - b0);
    x += b0;
    return x;
  } /* End of 'Map' function */
  
  /* Random value from 0..1 range gen function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (double) 0..1 range random value.
   */
  inline double rand0( void )
  {
    return (double)rand() / RAND_MAX;
  } /* End of 'rand0' function */
  
  /* Random value from chosen range gen function.
   * ARGUMENTS:
   *   - range bounds:
   *       double start, end.
   * RETURNS:
   *   (double) start..end range random value.
   */
  inline double rand( double start, double end )
  {
    return Map(rand0(), 0, 1, start, end);
  } /* End of 'rand' function */
  
  /* Runtime error function.
   * ARGUMENTS:
   *   - error message:
   *       char *ErrMsg;
   * RETURNS: None.
   */
  inline void RuntimeError( char *ErrMsg )
  {
    MessageBox(nullptr, ErrMsg, "Fatal error", MB_OK);
    exit(0);
  } /* End of 'RuntimeError' function */
} /* end of 'tcg' namespace */

#define OFFSET(Type, Field) \
  ((VOID *)(&((Type *)0)->Field))

#endif /* __def_h_ */

/* END OF 'def.h' FILE */
