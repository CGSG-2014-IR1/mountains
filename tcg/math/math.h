/* Reshetnyak Ivan */

#ifndef __math_h_
#define __math_h_

#include <cmath>

#include "../def.h"

#include <array>
#include <initializer_list>

namespace tcg
{
  namespace math
  {
    const double Threshold = 0.0000000001;
    const double ThresholdFloat = 0.00001;
    const double Pi = 3.14159265358979323846;  /* Pi */
    const double Pi2 = 6.28318530717958647692; /* Pi * 2 */

    template <class type>
      /* Value sign find function.
       * ARGUMENTS:
       *   - values:
       *       const type &a.
       * RETURNS:
       *   (type) value sign (-1, 0, 1).
       */
      int Sign( const type &a )
      {
        return (a > 0) ? 1 : ((a < 0) ? -1 : 0);
      } /* End of 'Sign' function */

    template<class type>
      /* Minimal value find function.
       * ARGUMENTS:
       *   - values:
       *       const std::initializer_list<type> &Vals.
       * RETURNS:
       *   (type) minimal value.
       */
      type Minimal( const std::initializer_list<type> &Vals )
      {
        type min = *Vals.begin();
        for (auto & i : Vals)
          if (i < min)
            min = i;

        return min;
      } /* End of 'Minimal' function */

    template<class type>
      /* Maximal value find function.
       * ARGUMENTS:
       *   - values:
       *       const std::initializer_list<type> &Vals.
       * RETURNS:
       *   (type) maximal value.
       */
      type Maximal( const std::initializer_list<type> &Vals )
      {
        type max = *Vals.begin();
        for (auto & i : Vals)
          if (i > max)
            max = i;

        return max;
      } /* End of 'Maximal' function */
  } /* end of 'math' namespace */
} /* end of 'tcg' namespace */

#endif /* __math_h_ */

/* END OF 'math.h' FILE */
