/*
 * histc.c
 *
 * Code generation for function 'histc'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "histc.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static int findbin(double x, const double bin_edges[257]);

/* Function Definitions */
static int findbin(double x, const double bin_edges[257])
{
  int k;
  int low_ip1;
  int high_i;
  int mid_i;
  k = 0;
  if (!rtIsNaN(x)) {
    if ((x >= bin_edges[0]) && (x < bin_edges[256])) {
      k = 1;
      low_ip1 = 2;
      high_i = 257;
      while (high_i > low_ip1) {
        mid_i = (k + high_i) >> 1;
        if (x >= bin_edges[mid_i - 1]) {
          k = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
    }

    if (x == bin_edges[256]) {
      k = 257;
    }
  }

  return k;
}

void histc(const emxArray_real_T *X, const double edges[257], double N[257])
{
  int xind;
  int k;
  int bin;
  memset(&N[0], 0, 257U * sizeof(double));
  xind = 0;
  for (k = 0; k < X->size[0]; k++) {
    bin = findbin(X->data[xind], edges);
    if (bin > 0) {
      N[bin - 1]++;
    }

    xind++;
  }
}

/* End of code generation (histc.c) */
