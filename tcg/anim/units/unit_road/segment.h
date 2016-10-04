#include "intersection.h"

/* Segment struct */
struct segment
{
  INT P0, P1;                              // Segment points.
  std::vector<intersection> Intersections; // Segment intersections.

  /* Struct constructor.
    * ARGUMENTS:
    *   - segment points:
    *       INT P0, P1;
    */
  segment( INT P0, INT P1 ) : P0(P0), P1(P1)
  {
  } /* End of 'segment' function */
}; /* End of 'segment' struct */

/* Pointer to segment struct */
struct segment_ptr
{
  segment *Segment; // Pointer to segment.
  CHAR IsActive;    // Segment activity flag.

  /* Struct constructor.
    * ARGUMENTS: None.
    */
  segment_ptr( VOID )
  {
  } /* End of 'segment_ptr' function */

  /* Struct constructor.
    * ARGUMENTS:
    *   - pointer to segment:
    *       segment *Segment;
    */
  segment_ptr( segment *Segment ) : Segment(Segment), IsActive(TRUE)
  {
  } /* End of 'segment_ptr' function */

  /* Copy segment pointer function.
    * ARGUMENTS:
    *   - pointer to segment:
    *       const segment_ptr &SegmentPtr;
    * RETURNS: None.
    */
  VOID operator=( const segment_ptr &SegmentPtr )
  {
    Segment = SegmentPtr.Segment;
    IsActive = SegmentPtr.IsActive;
  } /* End of 'operator=' function */
}; /* End of 'segment_ptr' struct */

/* Segment point struct */
struct segment_point
{
  segment *Segment; // Pointer to segment.
  INT Index, No;    // Point index and number (0 / 1).

  /* Struct constructor.
    * ARGUMENTS: None.
    */
  segment_point( VOID )
  {
  } /* End of 'segment_point' function */

  /* Struct constructor.
    * ARGUMENTS:
    *   - point index and number:
    *       INT Index, No;
    *   - pointer to segment:
    *       segment *Segment
    */
  segment_point( INT Index, INT No, segment *Segment ) : Index(Index), No(No), Segment(Segment)
  {
  } /* End of 'segment_point' function */

  /* Copy segment point function.
    * ARGUMENTS:
    *   - segment point:
    *       const segment_point &SegmentPoint;
    * RETURNS: None.
    */
  VOID operator=( const segment_point &SegmentPoint )
  {
    Index = SegmentPoint.Index;
    No = SegmentPoint.No;
    Segment = SegmentPoint.Segment;
  } /* End of 'segment_point' function */
}; /* End of 'segment_point' struct */

/* Road segment struct */
struct road_segment
{
  INT P[2], Border[2][2], Shoulder[2][2], Neighbour[2][2], C, Rotation[2]; // Road segment coordinates.
  std::vector<intersection> Intersections[4];                              // Intersections with triangles.
  BOOL IsTexCoord[2], IsRounded[2];
  DOUBLE TexCoord[2], HalfLen;

  /* Struct constructor.
    * ARGUMENTS:
    *   - road segment points indices:
    *       INT P0, P1;
    */
  road_segment( INT P0 = -1, INT P1 = -1 )
  {
    if (P0 != -1 && P1 != -1 && P0 > P1)
      std::swap(P0, P1);
    P[0] = P0, P[1] = P1;
    for (INT side = 0; side < 2; side++)
      for (INT no = 0; no < 2; no++)
      {
        Border[side][no] = -1;
        Neighbour[side][no] = -1;
        IsTexCoord[no] = FALSE;
      }
  } /* End of 'road_segment' function */
}; /* End of 'road_segment' struct */