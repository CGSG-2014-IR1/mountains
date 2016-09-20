/* Reshetnyak Ivan */

#ifndef __math_h_
#define __math_h_

#include <cmath>

#include "../def.h"

#include <array>
#include <initializer_list>

namespace math
{
  const double Threshold = 0.0000000001;
  const double ThresholdFloat = 0.00001;
  const double Pi = 3.14159265358979323846;
  const double Pi2 = 6.28318530717958647692;

  typedef std::array<vec2, 2> segment;
  typedef std::array<vec2, 3> triangle;

  inline double DegreesToRadians( double Angle )
  {
    return Angle * 0.01745329251994329576922222222222;
  }

  template <class type>
    int sign( const type &a )
    {
      return (a > 0) ? 1 : ((a < 0) ? -1 : 0);
    }

  template <class type>
    type lerp( const type &a, const type &b, double t )
    {
      return (type)((b * t) + (a * (1.0 - t)));
    }

  inline double fract( double x )
  {
    return x - (long)x;
  }

  template<class type>
    type minimal( std::initializer_list<type> Vals )
    {
      type min = *Vals.begin();
      for (auto & i : Vals)
        if (i < min)
          min = i;

      return min;
    }

  template<class type>
    type maximal( std::initializer_list<type> Vals )
    {
      type max = *Vals.begin();
      for (auto & i : Vals)
        if (i > max)
          max = i;

      return max;
    }
}; /* end of 'math' namespace */

#endif /* __math_h_ */

/* END OF 'math.h' FILE */
