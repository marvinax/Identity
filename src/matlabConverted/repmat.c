/*
 * repmat.c
 *
 * Code generation for function 'repmat'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "repmat.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void repmat(const double a_data[], const int a_size[1], double b_data[], int
            b_size[2])
{
  int nrows;
  int jtilecol;
  int ibtile;
  int k;
  b_size[0] = a_size[0];
  b_size[1] = 2;
  nrows = a_size[0];
  for (jtilecol = 0; jtilecol < 2; jtilecol++) {
    ibtile = jtilecol * nrows;
    for (k = 0; k + 1 <= nrows; k++) {
      b_data[ibtile + k] = a_data[k];
    }
  }
}

/* End of code generation (repmat.c) */
