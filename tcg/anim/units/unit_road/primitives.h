/* Create mountain function.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     *   - points:
     *       const std::vector<vec> &Points;
     *   - triangles:
     *       const std::vector<math::triangle> &Triangles;
     *   - IDs:
     *       const std::vector<math::triangle> &IDs;
     * RETURNS: None.
     */
    VOID CreateMountain( tcg::primitive::patch3 &Tri, anim *Ani, const std::vector<vec> &Points,
      const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs );

    /* Create mountain function.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     *   - points:
     *       const std::vector<vec> &Points;
     *   - triangles:
     *       const std::vector<math::triangle> &Triangles;
     *   - IDs:
     *       const std::vector<math::triangle> &IDs;
     *   - height identifiers:
     *       const std::vector<math::triangle> &P0, &P1, &H0, &H1;
     * RETURNS: None.
     */
    VOID CreateMountain( tcg::primitive::patch3 &Tri, anim *Ani, const std::vector<vec> &Points,
      const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs,
      const std::vector<INT> &P0, const std::vector<INT> &P1, const std::vector<INT> &H0, const std::vector<INT> &H1 );

    /* Create road function.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     *   - points:
     *       const std::vector<vec> &Points;
     *   - triangles:
     *       const std::vector<math::triangle> &Triangles;
     *   - texture coordinates:
     *       const std::vector<tsg::TVec<uv>> &TextureCoords;
     *   - heights:
     *       const std::vector<INT> &Heights;
     *   - height identifiers:
     *       const std::vector<math::triangle> &P0, &P1, &H0, &H1;
     * RETURNS: None.
     */
    VOID CreateRoad( tcg::primitive::trimesh &Tri, anim *Ani, const std::vector<vec> &Points, const std::vector<math::triangle> &Triangles,
      const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<math::triangle> &Heights,
      const std::vector<math::triangle> &P0, const std::vector<math::triangle> &P1,
      const std::vector<math::triangle> &H0, const std::vector<math::triangle> &H1 );

    /* Create village function.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     *   - points:
     *       const std::vector<vec> &Points;
     *   - triangles:
     *       const std::vector<math::triangle> &Triangles;
     *   - IDs:
     *       const std::vector<math::triangle> &IDs;
     *   - texture coordinates:
     *       const std::vector<tsg::TVec<uv>> &TextureCoords;
     *   - heights:
     *       const std::vector<INT> &Heights;
     * RETURNS: None.
     */
    VOID CreateVillage( tcg::primitive::patch3 &Tri, anim *Ani, const std::vector<vec> &Points,
      const std::vector<math::triangle> &Triangles, const std::vector<math::triangle> &IDs,
      const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<INT> &Heights );