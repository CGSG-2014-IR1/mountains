/* Reshetnyak Ivan */

#ifndef __vec2d_h_
#define __vec2d_h_

#include "vec2.h"

template<class type>
  /* 2D ray representation type */
  class ray2D
  {
  public:
    vec2D<type>
      Org,  /* Origin */
      Dir;  /* Direction */

    /* Class constructor.
     * ARGUMENTS:
     *   - ray origin and direction.
     *       const vec2D<type> &Org, &Dir.
     */
    ray2D( const vec2D<type> &Org, const vec2D<type> &Dir ) : Org(Org), Dir(Dir)
    {
    } /* End of 'ray2D' constructor */

    /* 2 rays intersection check function.
     * ARGUMENTS:
     *   - right-hand ray:
     *       const ray2D &rhs;
     *   - intersection point (OUTPUT)
     *       vec2D &Intr;
     *   - flag if rays should be intersected as lines:
     *       bool Line = false.
     * RETURNS:
     *   (bool) if rays intersect.
     */
    bool Intersect( const ray2D &rhs, vec2D<type> &Intr, bool Line = false, bool Approx = false )
    {
      type t1, t2;

      if (Approx)
        if (vec2::NearEqual(this->Dir, rhs.Dir) ||
            vec2::NearEqual(this->Dir, -rhs.Dir))
          return false;

      if (Dir.X != 0)
      {
        double tt = (rhs.Dir.X * Dir.Y / Dir.X - rhs.Dir.Y);
        if (tt == 0)
          return false;
        t2 = ((rhs.Org.Y - Org.Y) - ((rhs.Org.X - Org.X) * (Dir.Y / Dir.X))) / (type)tt;
        if (!Line && (t2 < 0 || t2 > 1))
          return false;
        t1 = (rhs.Org.X - Org.X + t2 * rhs.Dir.X) / Dir.X;
        if (Line || (t1 >= 0 && t1 <= 1))
        {
          Intr = Org + (Dir * t1);
          return true;
        }
      }
      else if (rhs.Dir.X != 0)
      {
        double tt = (Dir.X * rhs.Dir.Y / rhs.Dir.X - Dir.Y);
        if (tt == 0)
          return false;
        t1 = ((Org.Y - rhs.Org.Y) - ((Org.X - rhs.Org.X) * (rhs.Dir.Y / rhs.Dir.X))) / (type)tt;
        if (!Line && (t1 < 0 || t1 > 1))
          return false;
        t2 = (Org.X - rhs.Org.X + t1 * Dir.X) / rhs.Dir.X;
        if (Line || (t2 >= 0 && t2 <= 1))
        {
          Intr = Org + (Dir * t1);
          return true;
        }
      }
      return false;
    } /* End of 'Intersect' function */
  }; /* End of 'ray2D' class */

#endif /* __vec2d_h_ */

/* END OF 'ray2.h' FILE */
