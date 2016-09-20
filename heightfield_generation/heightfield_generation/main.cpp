/* Reshetnyak Ivan */

#include <cstdlib>
#include <ctime>

#include "def.h"
#include "anim/anim.h"

#include "anim/units/unit_hf_gen.h"
#include "anim/units/unit_hm_view.h"
#include "anim/units/unit_tess_demo.h"
#include "math/hm_gen.h"

#include <vector>
#include <array>

/* Main program function.
 * ARGUMENTS:
 *   - number of command line arguments:
 *       int argc;
 *   - command line arguments:
 *       char *argv[];
 * RETURNS: None.
 */
void main( int argc, char *argv[] )
{
  //hm_gen();  /* Generate height/normal map - very long procedure */
  anim::Anim.Init(argc, argv, "Mountain range");
  srand(time(nullptr));
  anim::Anim << new unit_hm_view(anim::Anim);
  anim::Anim.Run();
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */
