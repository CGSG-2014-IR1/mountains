/* Reshetnyak Ivan */

#ifndef __def_h_
#define __def_h_

/* Common includes */
#include <windows.h>
#include <cstdlib>

typedef float float_type;

#include "math/vec2.h"
typedef vec2D<double> vec2;
#include "math/vec3.h"
typedef vec3D<float_type> vec;
#include "math/ray2.h"
typedef ray2D<double> ray2;
#include "math/matrix.h"
typedef matrix4<float_type> matrix;
#include "math/color.h"
typedef color4<float_type> color;

#include <vector>

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
  __Dummy( void )
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

/* Forward reference */
class anim;
class unit;

/***
 * Cool functions.
 ***/

/* Get structure field offset macro definition - should be like FieldOffset(foo, foo_field) */
#define FieldOffset(Type, Field)  \
  ((VOID *)(&((Type *)0)->Field))

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
} /* End of 'map' function */

/* Sign check function.
 * ARGUMENTS:
 *   - value:
 *       double a;
 * RETURNS:
 *   (int) value sign - -1, 0, or 1.
 */
inline int Sign( double a )
{
  return a > 0 ? 1 :
    a < 0 ? -1 :
    0;
} /* End of 'Sign' function */

/* Polygon square count function.
 * ARGUMENTS:
 *   - polygon:
 *       const std::vector<vec2> &Polygon;
 * RETURNS:
 *   (double) polygon square.
 */
inline double PolygonSquare( const std::vector<vec2> &Polygon )
{
  auto cut =
    [Polygon](int i) -> int
    {
      return (i + Polygon.size()) % Polygon.size();
    };
  double sq = 0;
  for (unsigned i = 0; i < Polygon.size(); i++)
    sq += 0.5 * (Polygon[cut(i + 1)].X - Polygon[cut(i)].X) * 
      (Polygon[cut(i + 1)].Y + Polygon[cut(i)].Y);
  return sq;
} /* End of 'PolygonSquare' function  */

template<class type>
  /* Two values swap function.
   * ARGUMENTS:
   *   - values to swap (output):
   *       type &a, &b;
   * RETURNS: None.
   */
  void Swap( type &a, type &b )
  {
    type t = a;
    a = b;
    b = t;
  } /* End of 'Swap' function */

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

template<class type>
  /* Average value find function.
   * ARGUMENTS:
   *   - values:
   *       const std::initializer_list<const type> &Input;
   * RETURNS:
   *   (type) average.
   */
  type Center( const std::initializer_list<const type> &Input )
  {
    type out(0);
    for (auto &i : Input)
      out += i;
    out /= Input.size();
    return out;
  } /* End of 'Center' function */

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

#endif /* __def_h_ */

/* END OF 'def.h' FILE */
