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

#include "tsg/tsgcam.h"
#include "tsg/tsgcolor.h"
#include "tsg/tsgdef.h"
#include "tsg/tsgmatrx.h"
#include "tsg/tsgray.h"
#include "tsg/tsgtrans.h"
#include "tsg/tsgvect.h"

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
} /* end of 'tcg' namespace */

#define OFFSET(Type, Field) \
  ((VOID *)(&((Type *)0)->Field))

#endif /* __def_h_ */

/* END OF 'def.h' FILE */
