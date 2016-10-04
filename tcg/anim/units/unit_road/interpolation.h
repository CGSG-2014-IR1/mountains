/* Interpolation class */
class interpolation
{
public:
  vec p0, p1, p2, p3; // Interpolation points.
  DOUBLE t0, t1, t2, t3; // Interpolation distances.

  /* Class constructor.
    * ARGUMENTS:
    *   - interpolation points:
    *       const vec &P0, &P1, &P2, &P3;
    */
  interpolation( const vec &P0, const vec &P1, const vec &P2, const vec &P3 ) :
    p0(P0), p1(P1), p2(P2), p3(P3)
  {
    t0 = 0;
    t1 = sqrt(sqrt((p1.X - p0.X) * (p1.X - p0.X) +
                    (p1.Z - p0.Z) * (p1.Z - p0.Z))) + t0;
    t2 = sqrt(sqrt((p2.X - p1.X) * (p2.X - p1.X) +
                    (p2.Z - p1.Z) * (p2.Z - p1.Z))) + t1;
    t3 = sqrt(sqrt((p3.X - p2.X) * (p3.X - p2.X) +
                    (p3.Z - p2.Z) * (p3.Z - p2.Z))) + t2;
  } /* End of 'interpolation' class */

  /* Convert interpolation distance to point function.
    * ARGUMENTS:
    *   - interpolation distance:
    *       DOUBLE t;
    * RETURNS:
    *   (vec) result point.
    */
  vec operator()( DOUBLE t )
  {
    vec
      a1 = p0 * (t1 - t) / (t1 - t0) + p1 * (t - t0) / (t1 - t0),
      a2 = p1 * (t2 - t) / (t2 - t1) + p2 * (t - t1) / (t2 - t1),
      a3 = p2 * (t3 - t) / (t3 - t2) + p3 * (t - t2) / (t3 - t2),

      b1 = a1 * (t2 - t) / (t2 - t0) + a2 * (t - t0) / (t2 - t0),
      b2 = a2 * (t3 - t) / (t3 - t1) + a3 * (t - t1) / (t3 - t1);

    return b1 * (t2 - t) / (t2 - t1) + b2 * (t - t1) / (t2 - t1);
  } /* End of 'operator()' function */

  /* Convert interpolation distance to point function.
    * ARGUMENTS:
    *   - interpolation distance:
    *       DOUBLE t;
    * RETURNS:
    *   (vec) result point.
    */
  vec Interpolate( DOUBLE t )
  {
    vec
      a1 = p0 * (t1 - t) / (t1 - t0) + p1 * (t - t0) / (t1 - t0),
      a2 = p1 * (t2 - t) / (t2 - t1) + p2 * (t - t1) / (t2 - t1),
      a3 = p2 * (t3 - t) / (t3 - t2) + p3 * (t - t2) / (t3 - t2),

      b1 = a1 * (t2 - t) / (t2 - t0) + a2 * (t - t0) / (t2 - t0),
      b2 = a2 * (t3 - t) / (t3 - t1) + a3 * (t - t1) / (t3 - t1);

    return b1 * (t2 - t) / (t2 - t1) + b2 * (t - t1) / (t2 - t1);
  } /* End of 'Interpolate' function */

  /* Compute normal in point function.
    * ARGUMENTS:
    *   - interpolation distance:
    *       DOUBLE t;
    * RETURNS:
    *   (vec) result normal.
    */
  vec Normal( DOUBLE t )
  {
    vec
      dir0 = Interpolate(t + 0.0001) - Interpolate(t),
      dir1 = Interpolate(t) - Interpolate(t - 0.0001);

    return (vec(dir0.Z, 0, -dir0.X).Normalize() + vec(dir1.Z, 0, -dir1.X).Normalize()).Normalize();
  } /* End of 'Normal' function */

  /* Compute normal function.
    * ARGUMENTS: None.
    * RETURNS:
    *   (vec) result normal.
    */
  vec Normal( VOID )
  {
    for (DOUBLE t = t1 + 0.01; t < t2 - 0.01; t += 0.001)
      if (Rotation(p2 - p1, Interpolate(t) - p1) != Rotation(p2 - p1, Interpolate(t + 0.01) - p1))
        return Normal(t);
      
    return vec(p2.Z - p1.Z, 0, p1.X - p2.X).Normalize();
  } /* End of 'Normal' function */
}; /* End of 'interpolation' class */