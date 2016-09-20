/* Reshetnyak Ivan */

#ifndef __color_h_
#define __color_h_

/* Color class template */
template <class type>
  class color4
  {
  public:
    type R, G, B, A;  /* Vector coordinates */

    /* Class constructor.
     * ARGUMENTS:
     *   - components:
     *       type R = 0, G = 0, B = 0, A = 1;
     */
    color4( type R = 0, type G = 0, type B = 0, type A = 1 ) : R(R), G(G), B(B), A(A)
    {
    } /* End of 'color4' constructor */
  }; /* End of 'color4' class */

#endif /* __color_h_ */