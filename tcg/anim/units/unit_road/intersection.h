/* Segment intersection struct */
struct intersection
{
  DOUBLE t;  // Distance.
  INT Index; // Index of intersection point.

  /* Struct constructor.
    * ARGUMENTS:
    *   - distance:
    *       DOUBLE t;
    *   - index:
    *       INT Index;
    */
  intersection( DOUBLE t, INT Index ) : t(t), Index(Index)
  {
  } /* End of 'intersection' function */
}; /* End of 'intersection' struct */