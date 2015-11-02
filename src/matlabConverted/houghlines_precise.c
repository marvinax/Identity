/*
 * houghlines_precise.c
 *
 * Code generation for function 'houghlines_precise'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "houghlines_precise.h"
#include "findPointOnTheLine.h"
#include "getPowderAndQr_emxutil.h"
#include "sum.h"
#include "power.h"
#include "rand.h"
#include "abs.h"
#include "mean.h"
#include "diff.h"
#include "sortrows.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static void b_eml_sort_idx(const emxArray_real_T *x, const double col[2],
  emxArray_int32_T *idx);
static boolean_T eml_sort_le(const emxArray_real_T *v, const double col[2], int
  irow1, int irow2);
static void houghpixels(const emxArray_real_T *nonzeropix, const emxArray_real_T
  *rho, const double peak_data[], emxArray_real_T *r, emxArray_real_T *c);
static void parseInputs(const emxArray_boolean_T *varargin_1, double varargin_6,
  double varargin_8, emxArray_real_T *nonzeropix, double *fillgap, double
  *minlength);

/* Function Definitions */
static void b_eml_sort_idx(const emxArray_real_T *x, const double col[2],
  emxArray_int32_T *idx)
{
  int n;
  int k;
  emxArray_int32_T *idx0;
  int i;
  int i2;
  int j;
  int pEnd;
  int p;
  int q;
  int qEnd;
  int kEnd;
  n = x->size[0];
  k = idx->size[0];
  idx->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)idx, k, (int)sizeof(int));
  for (k = 1; k <= n; k++) {
    idx->data[k - 1] = k;
  }

  for (k = 1; k <= n - 1; k += 2) {
    if (eml_sort_le(x, col, k, k + 1)) {
    } else {
      idx->data[k - 1] = k + 1;
      idx->data[k] = k;
    }
  }

  emxInit_int32_T(&idx0, 1);
  k = idx0->size[0];
  idx0->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)idx0, k, (int)sizeof(int));
  i = x->size[0];
  for (k = 0; k < i; k++) {
    idx0->data[k] = 1;
  }

  i = 2;
  while (i < n) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < n + 1; pEnd = qEnd + i) {
      p = j;
      q = pEnd;
      qEnd = j + i2;
      if (qEnd > n + 1) {
        qEnd = n + 1;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if (eml_sort_le(x, col, idx->data[p - 1], idx->data[q - 1])) {
          idx0->data[k] = idx->data[p - 1];
          p++;
          if (p == pEnd) {
            while (q < qEnd) {
              k++;
              idx0->data[k] = idx->data[q - 1];
              q++;
            }
          }
        } else {
          idx0->data[k] = idx->data[q - 1];
          q++;
          if (q == qEnd) {
            while (p < pEnd) {
              k++;
              idx0->data[k] = idx->data[p - 1];
              p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx->data[(j + k) - 1] = idx0->data[k];
      }

      j = qEnd;
    }

    i = i2;
  }

  emxFree_int32_T(&idx0);
}

static boolean_T eml_sort_le(const emxArray_real_T *v, const double col[2], int
  irow1, int irow2)
{
  boolean_T p;
  int k;
  boolean_T exitg1;
  int coloffset;
  boolean_T b0;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    coloffset = ((int)fabs(col[k]) - 1) * v->size[0] - 1;
    if ((v->data[coloffset + irow1] == v->data[coloffset + irow2]) || (rtIsNaN
         (v->data[coloffset + irow1]) && rtIsNaN(v->data[coloffset + irow2]))) {
      b0 = true;
    } else {
      b0 = false;
    }

    if (!b0) {
      if ((v->data[coloffset + irow1] <= v->data[coloffset + irow2]) || rtIsNaN
          (v->data[coloffset + irow2])) {
        p = true;
      } else {
        p = false;
      }

      exitg1 = true;
    } else {
      k++;
    }
  }

  return p;
}

static void houghpixels(const emxArray_real_T *nonzeropix, const emxArray_real_T
  *rho, const double peak_data[], emxArray_real_T *r, emxArray_real_T *c)
{
  emxArray_real_T *x;
  int ixstart;
  int i13;
  emxArray_real_T *y;
  double peak_2_low;
  double peak_2_high;
  emxArray_real_T *rho_xy;
  emxArray_real_T *slope;
  emxArray_boolean_T *b_x;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  boolean_T exitg5;
  boolean_T guard1 = false;
  boolean_T exitg4;
  boolean_T exitg3;
  double mtmp;
  boolean_T exitg2;
  double b_mtmp;
  boolean_T exitg1;
  double sorting_order[2];
  emxArray_real_T *b_y;
  emxArray_real_T *rc_new;
  b_emxInit_real_T(&x, 1);

  /* ----------------------------------------------------------------------------- */
  /* HOUGHPIXELS Compute image pixels belonging to Hough transform bin. */
  /*    [R, C] = HOUGHPIXELS(NONZEROPIX, THETA, RHO, PEAK) computes the */
  /*    row-column indices (R, C) for nonzero pixels NONZEROPIX that map */
  /*    to a particular Hough transform bin, PEAK which is a two element */
  /*    vector [RBIN CBIN].  RBIN and CBIN are scalars indicating the  */
  /*    row-column bin location in the Hough transform matrix returned by */
  /*    function HOUGH.  THETA and RHO are the second and third output  */
  /*    arguments from the HOUGH function. */
  ixstart = nonzeropix->size[0];
  i13 = x->size[0];
  x->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)x, i13, (int)sizeof(double));
  for (i13 = 0; i13 < ixstart; i13++) {
    x->data[i13] = nonzeropix->data[i13];
  }

  b_emxInit_real_T(&y, 1);
  ixstart = nonzeropix->size[0];
  i13 = y->size[0];
  y->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)y, i13, (int)sizeof(double));
  for (i13 = 0; i13 < ixstart; i13++) {
    y->data[i13] = nonzeropix->data[i13 + nonzeropix->size[0]];
  }

  peak_2_low = floor(peak_data[1]);
  peak_2_high = peak_2_low + 1.0;
  if (peak_2_low + 1.0 > 180.0) {
    peak_2_high = 180.0;
  }

  b_emxInit_real_T(&rho_xy, 1);
  peak_2_low = ((-90.0 + (peak_2_low - 1.0)) + ((-90.0 + (peak_2_high - 1.0)) -
                 (-90.0 + (peak_2_low - 1.0))) * (peak_data[1] - peak_2_low)) *
    3.1415926535897931 / 180.0;
  peak_2_high = cos(peak_2_low);
  peak_2_low = sin(peak_2_low);
  i13 = rho_xy->size[0];
  rho_xy->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)rho_xy, i13, (int)sizeof(double));
  ixstart = x->size[0];
  for (i13 = 0; i13 < ixstart; i13++) {
    rho_xy->data[i13] = x->data[i13] * peak_2_high + y->data[i13] * peak_2_low;
  }

  b_emxInit_real_T(&slope, 1);
  peak_2_low = ((double)rho->size[1] - 1.0) / (rho->data[rho->size[1] - 1] -
    rho->data[0]);

  /*  Note that "<=" should be used instead of "<", if not for those cases that  */
  /*  rho_bin_index_frac = ###.5, the following line will fail. The equal sign */
  /*  will double the number of points obtain, which is okay because curve */
  /*  fitting module in the later stage will not be affected. (Chau-Wai Wong, */
  /*  Nov. 2014) */
  peak_2_high = rho->data[0];
  i13 = slope->size[0];
  slope->size[0] = rho_xy->size[0];
  emxEnsureCapacity((emxArray__common *)slope, i13, (int)sizeof(double));
  ixstart = rho_xy->size[0];
  for (i13 = 0; i13 < ixstart; i13++) {
    slope->data[i13] = (peak_2_low * (rho_xy->data[i13] - peak_2_high) + 1.0) -
      peak_data[0];
  }

  b_emxInit_boolean_T(&b_x, 1);
  b_abs(slope, rho_xy);
  i13 = b_x->size[0];
  b_x->size[0] = rho_xy->size[0];
  emxEnsureCapacity((emxArray__common *)b_x, i13, (int)sizeof(boolean_T));
  ixstart = rho_xy->size[0];
  emxFree_real_T(&slope);
  for (i13 = 0; i13 < ixstart; i13++) {
    b_x->data[i13] = (rho_xy->data[i13] <= 0.5);
  }

  emxInit_int32_T(&ii, 1);
  nx = b_x->size[0];
  idx = 0;
  i13 = ii->size[0];
  ii->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i13, (int)sizeof(int));
  ixstart = 1;
  exitg5 = false;
  while ((!exitg5) && (ixstart <= nx)) {
    guard1 = false;
    if (b_x->data[ixstart - 1]) {
      idx++;
      ii->data[idx - 1] = ixstart;
      if (idx >= nx) {
        exitg5 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ixstart++;
    }
  }

  if (b_x->size[0] == 1) {
    if (idx == 0) {
      i13 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i13, (int)sizeof(int));
    }
  } else {
    i13 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i13, (int)sizeof(int));
  }

  emxFree_boolean_T(&b_x);
  i13 = rho_xy->size[0];
  rho_xy->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)rho_xy, i13, (int)sizeof(double));
  ixstart = ii->size[0];
  for (i13 = 0; i13 < ixstart; i13++) {
    rho_xy->data[i13] = ii->data[i13];
  }

  i13 = r->size[0];
  r->size[0] = rho_xy->size[0];
  emxEnsureCapacity((emxArray__common *)r, i13, (int)sizeof(double));
  ixstart = rho_xy->size[0];
  for (i13 = 0; i13 < ixstart; i13++) {
    r->data[i13] = y->data[(int)rho_xy->data[i13] - 1] + 1.0;
  }

  emxFree_real_T(&y);
  i13 = c->size[0];
  c->size[0] = rho_xy->size[0];
  emxEnsureCapacity((emxArray__common *)c, i13, (int)sizeof(double));
  ixstart = rho_xy->size[0];
  for (i13 = 0; i13 < ixstart; i13++) {
    c->data[i13] = x->data[(int)rho_xy->data[i13] - 1] + 1.0;
  }

  emxFree_real_T(&rho_xy);
  emxFree_real_T(&x);

  /* -------------------------------------------------------------------------- */
  /*  make sure that r an c are in the order along the line segment */
  if (r->size[0] == 0) {
  } else {
    ixstart = 1;
    nx = r->size[0];
    peak_2_low = r->data[0];
    if (r->size[0] > 1) {
      if (rtIsNaN(r->data[0])) {
        idx = 2;
        exitg4 = false;
        while ((!exitg4) && (idx <= nx)) {
          ixstart = idx;
          if (!rtIsNaN(r->data[idx - 1])) {
            peak_2_low = r->data[idx - 1];
            exitg4 = true;
          } else {
            idx++;
          }
        }
      }

      if (ixstart < r->size[0]) {
        while (ixstart + 1 <= nx) {
          if (r->data[ixstart] > peak_2_low) {
            peak_2_low = r->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    ixstart = 1;
    nx = r->size[0];
    peak_2_high = r->data[0];
    if (r->size[0] > 1) {
      if (rtIsNaN(r->data[0])) {
        idx = 2;
        exitg3 = false;
        while ((!exitg3) && (idx <= nx)) {
          ixstart = idx;
          if (!rtIsNaN(r->data[idx - 1])) {
            peak_2_high = r->data[idx - 1];
            exitg3 = true;
          } else {
            idx++;
          }
        }
      }

      if (ixstart < r->size[0]) {
        while (ixstart + 1 <= nx) {
          if (r->data[ixstart] < peak_2_high) {
            peak_2_high = r->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    ixstart = 1;
    nx = c->size[0];
    mtmp = c->data[0];
    if (c->size[0] > 1) {
      if (rtIsNaN(c->data[0])) {
        idx = 2;
        exitg2 = false;
        while ((!exitg2) && (idx <= nx)) {
          ixstart = idx;
          if (!rtIsNaN(c->data[idx - 1])) {
            mtmp = c->data[idx - 1];
            exitg2 = true;
          } else {
            idx++;
          }
        }
      }

      if (ixstart < c->size[0]) {
        while (ixstart + 1 <= nx) {
          if (c->data[ixstart] > mtmp) {
            mtmp = c->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    ixstart = 1;
    nx = c->size[0];
    b_mtmp = c->data[0];
    if (c->size[0] > 1) {
      if (rtIsNaN(c->data[0])) {
        idx = 2;
        exitg1 = false;
        while ((!exitg1) && (idx <= nx)) {
          ixstart = idx;
          if (!rtIsNaN(c->data[idx - 1])) {
            b_mtmp = c->data[idx - 1];
            exitg1 = true;
          } else {
            idx++;
          }
        }
      }

      if (ixstart < c->size[0]) {
        while (ixstart + 1 <= nx) {
          if (c->data[ixstart] < b_mtmp) {
            b_mtmp = c->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    if (peak_2_low - peak_2_high > mtmp - b_mtmp) {
      /*  Sort first on r, then on c */
      for (i13 = 0; i13 < 2; i13++) {
        sorting_order[i13] = 1.0 + (double)i13;
      }
    } else {
      /*  Sort first on c, then on r */
      for (i13 = 0; i13 < 2; i13++) {
        sorting_order[i13] = 2.0 - (double)i13;
      }
    }

    emxInit_real_T(&b_y, 2);
    ixstart = r->size[0];
    nx = c->size[0];
    i13 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = ixstart;
    b_y->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)b_y, i13, (int)sizeof(double));
    for (i13 = 0; i13 < ixstart; i13++) {
      b_y->data[i13] = r->data[i13];
    }

    for (i13 = 0; i13 < nx; i13++) {
      b_y->data[i13 + b_y->size[0]] = c->data[i13];
    }

    emxInit_real_T(&rc_new, 2);
    b_eml_sort_idx(b_y, sorting_order, ii);
    i13 = rc_new->size[0] * rc_new->size[1];
    rc_new->size[0] = b_y->size[0];
    rc_new->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)rc_new, i13, (int)sizeof(double));
    ixstart = b_y->size[0] * b_y->size[1];
    for (i13 = 0; i13 < ixstart; i13++) {
      rc_new->data[i13] = b_y->data[i13];
    }

    emxFree_real_T(&b_y);
    apply_row_permutation(rc_new, ii);
    ixstart = rc_new->size[0];
    i13 = r->size[0];
    r->size[0] = ixstart;
    emxEnsureCapacity((emxArray__common *)r, i13, (int)sizeof(double));
    for (i13 = 0; i13 < ixstart; i13++) {
      r->data[i13] = rc_new->data[i13];
    }

    ixstart = rc_new->size[0];
    i13 = c->size[0];
    c->size[0] = ixstart;
    emxEnsureCapacity((emxArray__common *)c, i13, (int)sizeof(double));
    for (i13 = 0; i13 < ixstart; i13++) {
      c->data[i13] = rc_new->data[i13 + rc_new->size[0]];
    }

    emxFree_real_T(&rc_new);
  }

  emxFree_int32_T(&ii);
}

static void parseInputs(const emxArray_boolean_T *varargin_1, double varargin_6,
  double varargin_8, emxArray_real_T *nonzeropix, double *fillgap, double
  *minlength)
{
  emxArray_int32_T *ii;
  emxArray_int32_T *jj;
  int nx;
  int idx;
  int i49;
  int b_ii;
  int b_jj;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *y;
  emxArray_real_T *x;
  emxArray_real_T *b_x;
  emxInit_int32_T(&ii, 1);
  emxInit_int32_T(&jj, 1);

  /* ----------------------------------------------------------------------------- */
  /*  % % validateattributes(bw, {'numeric','logical'},... */
  /*  % %               {'real', '2d', 'nonsparse', 'nonempty'}, ... */
  /*  % %               mfilename, 'BW', idx); */
  /*  % % validateattributes(theta, {'double'}, {'real','vector','finite',... */
  /*  % %                     'nonsparse','nonempty'}, ... */
  /*  % %               mfilename, 'THETA', idx); */
  /*  % % validateattributes(rho, {'double'}, {'real','vector','finite',... */
  /*  % %                     'nonsparse','nonempty'}, ... */
  /*  % %               mfilename, 'RHO', idx); */
  /*  % % validateattributes(peaks, {'double'}, {'real','2d','nonsparse', ... */
  /*  % %                     'positive'}, ... */
  /*  % %               mfilename, 'PEAKS', idx); */
  /*  Set the defaults */
  *fillgap = varargin_6;
  *minlength = varargin_8;

  /*  % % % Process parameter-value pairs */
  /*  % % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  % % validStrings = {'FillGap','MinLength'}; */
  /*  % % idx = idx+1; */
  /*  % %  */
  /*  % % if nargin > idx-1 % we have parameter/value pairs */
  /*  % %   done = false; */
  /*  % %  */
  /*  % %   while ~done */
  /*  % %     input = varargin{idx}; */
  /*  % %     inputStr = validatestring(input, validStrings,mfilename,'PARAM',idx); */
  /*  % %      */
  /*  % %     idx = idx+1; %advance index to point to the VAL portion of the input  */
  /*  % %      */
  /*  % %     if idx > nargin */
  /*  % %       error(message('images:houghlines:valForhoughlinesMissing', inputStr)) */
  /*  % %     end */
  /*  % %      */
  /*  % %     switch inputStr */
  /*  % %        */
  /*  % %      case 'FillGap' */
  /*  % %       fillgap = varargin{idx}; */
  /*  % %       validateattributes(fillgap, {'double'}, {'finite','real', 'scalar', ... */
  /*  % %                           'positive'}, mfilename, inputStr, idx); */
  /*  % %       */
  /*  % %      case 'MinLength' */
  /*  % %       minlength = varargin{idx}; */
  /*  % %       validateattributes(minlength, {'double'}, {'finite','real', 'scalar', ... */
  /*  % %                           'positive'}, mfilename, inputStr, idx); */
  /*  % %        */
  /*  % %      otherwise */
  /*  % %       %should never get here */
  /*  % %       error(message('images:houghlines:internalError')) */
  /*  % %     end */
  /*  % %      */
  /*  % %     if idx >= nargin */
  /*  % %       done = true; */
  /*  % %     end */
  /*  % %      */
  /*  % %     idx=idx+1; */
  /*  % %   end */
  /*  % % end */
  /*  Compute the required parameters */
  nx = varargin_1->size[0] * varargin_1->size[1];
  idx = 0;
  i49 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i49, (int)sizeof(int));
  i49 = jj->size[0];
  jj->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)jj, i49, (int)sizeof(int));
  if (nx == 0) {
    i49 = ii->size[0];
    ii->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)ii, i49, (int)sizeof(int));
    i49 = jj->size[0];
    jj->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)jj, i49, (int)sizeof(int));
  } else {
    b_ii = 1;
    b_jj = 1;
    exitg1 = false;
    while ((!exitg1) && (b_jj <= varargin_1->size[1])) {
      guard1 = false;
      if (varargin_1->data[(b_ii + varargin_1->size[0] * (b_jj - 1)) - 1]) {
        idx++;
        ii->data[idx - 1] = b_ii;
        jj->data[idx - 1] = b_jj;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        b_ii++;
        if (b_ii > varargin_1->size[0]) {
          b_ii = 1;
          b_jj++;
        }
      }
    }

    if (nx == 1) {
      if (idx == 0) {
        i49 = ii->size[0];
        ii->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)ii, i49, (int)sizeof(int));
        i49 = jj->size[0];
        jj->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)jj, i49, (int)sizeof(int));
      }
    } else {
      i49 = ii->size[0];
      if (1 > idx) {
        ii->size[0] = 0;
      } else {
        ii->size[0] = idx;
      }

      emxEnsureCapacity((emxArray__common *)ii, i49, (int)sizeof(int));
      i49 = jj->size[0];
      if (1 > idx) {
        jj->size[0] = 0;
      } else {
        jj->size[0] = idx;
      }

      emxEnsureCapacity((emxArray__common *)jj, i49, (int)sizeof(int));
    }
  }

  b_emxInit_real_T(&y, 1);
  i49 = y->size[0];
  y->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)y, i49, (int)sizeof(double));
  b_ii = ii->size[0];
  for (i49 = 0; i49 < b_ii; i49++) {
    y->data[i49] = ii->data[i49];
  }

  emxFree_int32_T(&ii);
  b_emxInit_real_T(&x, 1);
  i49 = x->size[0];
  x->size[0] = jj->size[0];
  emxEnsureCapacity((emxArray__common *)x, i49, (int)sizeof(double));
  b_ii = jj->size[0];
  for (i49 = 0; i49 < b_ii; i49++) {
    x->data[i49] = jj->data[i49];
  }

  emxFree_int32_T(&jj);
  emxInit_real_T(&b_x, 2);
  b_ii = x->size[0];
  b_jj = y->size[0];
  i49 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = b_ii;
  b_x->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_x, i49, (int)sizeof(double));
  for (i49 = 0; i49 < b_ii; i49++) {
    b_x->data[i49] = x->data[i49];
  }

  emxFree_real_T(&x);
  for (i49 = 0; i49 < b_jj; i49++) {
    b_x->data[i49 + b_x->size[0]] = y->data[i49];
  }

  emxFree_real_T(&y);
  i49 = nonzeropix->size[0] * nonzeropix->size[1];
  nonzeropix->size[0] = b_x->size[0];
  nonzeropix->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)nonzeropix, i49, (int)sizeof(double));
  for (i49 = 0; i49 < 2; i49++) {
    b_ii = b_x->size[0];
    for (b_jj = 0; b_jj < b_ii; b_jj++) {
      nonzeropix->data[b_jj + nonzeropix->size[0] * i49] = b_x->data[b_jj +
        b_x->size[0] * i49] - 1.0;
    }
  }

  emxFree_real_T(&b_x);
}

void houghlines_precise(const emxArray_boolean_T *varargin_1, const
  emxArray_real_T *varargin_3, const double varargin_4_data[], const int
  varargin_4_size[2], double varargin_6, double varargin_8, e_struct_T
  lines_data[], int lines_size[2])
{
  emxArray_real_T *rho;
  int i12;
  int loop_ub;
  int peaks_size_idx_0;
  double peaks_data[20];
  emxArray_real_T *nonzeropix;
  double scale_x;
  double Syy;
  double minlength_sq;
  double fillgap_sq;
  int numlines;
  static const e_struct_T rv1[30] = { { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0,
        0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0,
      0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { {
        0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0,
        0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, {
        0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 },
      { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 },
      0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, {
      { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0,
        0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, {
        0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 },
      { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 },
      0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, {
      { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0,
        0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, {
        0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 },
      { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 },
      0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, {
      { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0,
        0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, {
        0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 },
      { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 },
      0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, {
      { 0.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0,
        0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 }, { { 0.0, 0.0, 0.0 }, {
        0.0, 0.0 }, { 0.0, 0.0 }, 0.0, 0.0 } };

  int k;
  emxArray_real_T *xy;
  emxArray_real_T *diff_xy_sq;
  emxArray_real_T *dist_sq;
  emxArray_real_T *idx;
  emxArray_real_T *pointForThisLine;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  emxArray_real_T *x_notCentered;
  emxArray_real_T *y_notCentered;
  emxArray_real_T *b_x;
  emxArray_real_T *y;
  emxArray_real_T *a;
  emxArray_real_T *r14;
  emxArray_real_T *r15;
  emxArray_real_T *b_y_notCentered;
  emxArray_real_T *b_x_notCentered;
  double b_peaks_data[2];
  int k0;
  int nx;
  int b_idx;
  boolean_T exitg1;
  boolean_T guard1 = false;
  int p;
  double b_y[2];
  double x_mean;
  double y_mean;
  double Sxx;
  double c_y;
  double Sxy;
  d_struct_T expl_temp;
  double idx_data[30];
  e_struct_T b_lines_data[30];
  boolean_T b_data[30];
  emxInit_real_T(&rho, 2);

  /* HOUGHLINES Extract line segments based on Hough transform. */
  /*    LINES = HOUGHLINES(BW, THETA, RHO, PEAKS) extracts line segments */
  /*    in the image BW associated with particular bins in a Hough  */
  /*    transform.  THETA and RHO are vectors returned by function HOUGH. */
  /*    Matrix PEAKS, which is returned by function HOUGHPEAKS, */
  /*    contains the row and column coordinates of the Hough transform  */
  /*    bins to use in searching for line segments. HOUGHLINES returns */
  /*    LINES structure array whose length equals the number of merged */
  /*    line segments found. Each element of the structure array has */
  /*    these fields:  */
  /*  */
  /*       point1  End-point of the line segment; two-element vector */
  /*       point2  End-point of the line segment; two-element vector */
  /*       theta   Angle (in degrees) of the Hough transform bin */
  /*       rho     Rho-axis position of the Hough transform bin */
  /*  */
  /*    The end-point vectors contain [X, Y] coordinates. */
  /*  */
  /*    LINES = HOUGHLINES(...,PARAM1,VAL1,PARAM2,VAL2) sets various */
  /*    parameters. Parameter names can be abbreviated, and case  */
  /*    does not matter. Each string parameter is followed by a value  */
  /*    as indicated below: */
  /*  */
  /*    'FillGap'   Positive real scalar. */
  /*                When HOUGHLINES finds two line segments associated */
  /*                with the same Hough transform bin that are separated */
  /*                by less than 'FillGap' distance, HOUGHLINES merges */
  /*                them into a single line segment. */
  /*  */
  /*                Default: 20 */
  /*  */
  /*    'MinLength' Positive real scalar. */
  /*                Merged line segments shorter than 'MinLength' */
  /*                are discarded. */
  /*  */
  /*                Default: 40 */
  /*  */
  /*    Class Support */
  /*    ------------- */
  /*    BW can be logical or numeric and it must be real, 2-D, and nonsparse. */
  /*  */
  /*    Example */
  /*    ------- */
  /*    Search for line segments corresponding to five peaks in the Hough  */
  /*    transform of the rotated circuit.tif image. Additionally, highlight */
  /*    the longest segment. */
  /*  */
  /*       I  = imread('circuit.tif'); */
  /*       rotI = imrotate(I,33,'crop'); */
  /*       BW = edge(rotI,'canny'); */
  /*       [H,T,R] = hough(BW); */
  /*       imshow(H,[],'XData',T,'YData',R,'InitialMagnification','fit'); */
  /*       xlabel('\theta'), ylabel('\rho'); */
  /*       axis on, axis normal, hold on; */
  /*       P  = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:)))); */
  /*       x = T(P(:,2));  */
  /*       y = R(P(:,1)); */
  /*       plot(x,y,'s','color','white'); */
  /*  */
  /*       % Find lines and plot them */
  /*       lines = houghlines(BW,T,R,P,'FillGap',5,'MinLength',7); */
  /*       figure, imshow(rotI), hold on */
  /*       max_len = 0; */
  /*       for k = 1:length(lines) */
  /*         xy = [lines(k).point1; lines(k).point2]; */
  /*         plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green'); */
  /*  */
  /*         % plot beginnings and ends of lines */
  /*         plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow'); */
  /*         plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red'); */
  /*  */
  /*         % determine the endpoints of the longest line segment  */
  /*         len = norm(lines(k).point1 - lines(k).point2); */
  /*         if ( len > max_len) */
  /*           max_len = len; */
  /*           xy_long = xy; */
  /*         end */
  /*       end */
  /*  */
  /*       % highlight the longest line segment */
  /*       plot(xy_long(:,1),xy_long(:,2),'LineWidth',2,'Color','cyan'); */
  /*  */
  /*    See also HOUGH and HOUGHPEAKS. */
  /*    Copyright 1993-2011 The MathWorks, Inc. */
  /*    References: */
  /*    Rafael C. Gonzalez, Richard E. Woods, Steven L. Eddins, "Digital */
  /*    Image Processing Using MATLAB", Prentice Hall, 2003 */
  i12 = rho->size[0] * rho->size[1];
  rho->size[0] = 1;
  rho->size[1] = varargin_3->size[1];
  emxEnsureCapacity((emxArray__common *)rho, i12, (int)sizeof(double));
  loop_ub = varargin_3->size[0] * varargin_3->size[1];
  for (i12 = 0; i12 < loop_ub; i12++) {
    rho->data[i12] = varargin_3->data[i12];
  }

  peaks_size_idx_0 = varargin_4_size[0];
  loop_ub = varargin_4_size[0] * varargin_4_size[1];
  for (i12 = 0; i12 < loop_ub; i12++) {
    peaks_data[i12] = varargin_4_data[i12];
  }

  emxInit_real_T(&nonzeropix, 2);
  parseInputs(varargin_1, varargin_6, varargin_8, nonzeropix, &Syy, &scale_x);
  minlength_sq = scale_x * scale_x;
  fillgap_sq = Syy * Syy;
  numlines = -1;

  /*  % % lines = struct([]); */
  /*  % var size */
  /*  % fixed size */
  /*  % fixed size */
  /*  % fixed size */
  /*  fixed size */
  lines_size[0] = 1;
  for (i12 = 0; i12 < 30; i12++) {
    lines_data[i12] = rv1[i12];
  }

  k = 0;
  emxInit_real_T(&xy, 2);
  emxInit_real_T(&diff_xy_sq, 2);
  b_emxInit_real_T(&dist_sq, 1);
  b_emxInit_real_T(&idx, 1);
  emxInit_real_T(&pointForThisLine, 2);
  b_emxInit_boolean_T(&x, 1);
  emxInit_int32_T(&ii, 1);
  b_emxInit_real_T(&x_notCentered, 1);
  b_emxInit_real_T(&y_notCentered, 1);
  b_emxInit_real_T(&b_x, 1);
  b_emxInit_real_T(&y, 1);
  emxInit_real_T(&a, 2);
  b_emxInit_real_T(&r14, 1);
  b_emxInit_real_T(&r15, 1);
  b_emxInit_real_T(&b_y_notCentered, 1);
  b_emxInit_real_T(&b_x_notCentered, 1);
  while (k <= peaks_size_idx_0 - 1) {
    /*  Get all pixels associated with Hough transform cell. */
    for (i12 = 0; i12 < 2; i12++) {
      b_peaks_data[i12] = peaks_data[k + peaks_size_idx_0 * i12];
    }

    houghpixels(nonzeropix, rho, b_peaks_data, x_notCentered, y_notCentered);
    if (x_notCentered->size[0] == 0) {
    } else {
      /*  Compute distance^2 between the point pairs */
      k0 = y_notCentered->size[0];
      nx = x_notCentered->size[0];
      i12 = xy->size[0] * xy->size[1];
      xy->size[0] = k0;
      xy->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)xy, i12, (int)sizeof(double));
      for (i12 = 0; i12 < k0; i12++) {
        xy->data[i12] = y_notCentered->data[i12];
      }

      for (i12 = 0; i12 < nx; i12++) {
        xy->data[i12 + xy->size[0]] = x_notCentered->data[i12];
      }

      /*  x,y pairs in coordinate system with the origin at (1,1) */
      diff(xy, pointForThisLine);
      c_power(pointForThisLine, diff_xy_sq);
      sum(diff_xy_sq, dist_sq);

      /*  Find the gaps larger than the threshold. */
      i12 = x->size[0];
      x->size[0] = dist_sq->size[0];
      emxEnsureCapacity((emxArray__common *)x, i12, (int)sizeof(boolean_T));
      loop_ub = dist_sq->size[0];
      for (i12 = 0; i12 < loop_ub; i12++) {
        x->data[i12] = (dist_sq->data[i12] > fillgap_sq);
      }

      nx = x->size[0];
      b_idx = 0;
      i12 = ii->size[0];
      ii->size[0] = x->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i12, (int)sizeof(int));
      k0 = 1;
      exitg1 = false;
      while ((!exitg1) && (k0 <= nx)) {
        guard1 = false;
        if (x->data[k0 - 1]) {
          b_idx++;
          ii->data[b_idx - 1] = k0;
          if (b_idx >= nx) {
            exitg1 = true;
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          k0++;
        }
      }

      if (x->size[0] == 1) {
        if (b_idx == 0) {
          i12 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)ii, i12, (int)sizeof(int));
        }
      } else {
        i12 = ii->size[0];
        if (1 > b_idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = b_idx;
        }

        emxEnsureCapacity((emxArray__common *)ii, i12, (int)sizeof(int));
      }

      i12 = idx->size[0];
      idx->size[0] = 2 + ii->size[0];
      emxEnsureCapacity((emxArray__common *)idx, i12, (int)sizeof(double));
      idx->data[0] = 0.0;
      loop_ub = ii->size[0];
      for (i12 = 0; i12 < loop_ub; i12++) {
        idx->data[i12 + 1] = ii->data[i12];
      }

      idx->data[1 + ii->size[0]] = xy->size[0];
      for (p = 0; p <= idx->size[0] - 2; p++) {
        /*  offset by 1 to convert to 1 based index */
        /*  set the end (don't offset by one this time) */
        b_idx = (int)idx->data[1 + p];
        k0 = (int)(idx->data[p] + 1.0);
        for (i12 = 0; i12 < 2; i12++) {
          b_peaks_data[i12] = xy->data[(b_idx + xy->size[0] * i12) - 1] -
            xy->data[(k0 + xy->size[0] * i12) - 1];
        }

        for (k0 = 0; k0 < 2; k0++) {
          b_y[k0] = b_peaks_data[k0] * b_peaks_data[k0];
        }

        if (b_y[0] + b_y[1] >= minlength_sq) {
          numlines++;
          if (idx->data[p] + 1.0 > idx->data[1 + p]) {
            i12 = 0;
            nx = 0;
          } else {
            i12 = (int)(idx->data[p] + 1.0) - 1;
            nx = (int)idx->data[1 + p];
          }

          b_idx = pointForThisLine->size[0] * pointForThisLine->size[1];
          pointForThisLine->size[0] = nx - i12;
          pointForThisLine->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)pointForThisLine, b_idx, (int)
                            sizeof(double));
          for (b_idx = 0; b_idx < 2; b_idx++) {
            loop_ub = nx - i12;
            for (k0 = 0; k0 < loop_ub; k0++) {
              pointForThisLine->data[k0 + pointForThisLine->size[0] * b_idx] =
                xy->data[(i12 + k0) + xy->size[0] * b_idx];
            }
          }

          /*  Estimate a line using Deming regression. To avoid estimated slope to be */
          /*  +/- infinity for nearly vertical lines, we use the following three- */
          /*  parameter form: */
          /*  */
          /*             alpha * E[x] + beta * E[y] + gamma = 0 */
          /*  */
          /*  Chau-Wai Wong, Oct. 2014 */
          loop_ub = nx - i12;
          b_idx = x_notCentered->size[0];
          x_notCentered->size[0] = nx - i12;
          emxEnsureCapacity((emxArray__common *)x_notCentered, b_idx, (int)
                            sizeof(double));
          for (b_idx = 0; b_idx < loop_ub; b_idx++) {
            x_notCentered->data[b_idx] = pointForThisLine->data[b_idx];
          }

          loop_ub = nx - i12;
          b_idx = y_notCentered->size[0];
          y_notCentered->size[0] = nx - i12;
          emxEnsureCapacity((emxArray__common *)y_notCentered, b_idx, (int)
                            sizeof(double));
          for (b_idx = 0; b_idx < loop_ub; b_idx++) {
            y_notCentered->data[b_idx] = pointForThisLine->data[b_idx +
              pointForThisLine->size[0]];
          }

          x_mean = mean(x_notCentered);
          y_mean = mean(y_notCentered);
          b_idx = b_x->size[0];
          b_x->size[0] = x_notCentered->size[0];
          emxEnsureCapacity((emxArray__common *)b_x, b_idx, (int)sizeof(double));
          loop_ub = x_notCentered->size[0];
          for (b_idx = 0; b_idx < loop_ub; b_idx++) {
            b_x->data[b_idx] = x_notCentered->data[b_idx] - x_mean;
          }

          b_idx = y->size[0];
          y->size[0] = y_notCentered->size[0];
          emxEnsureCapacity((emxArray__common *)y, b_idx, (int)sizeof(double));
          loop_ub = y_notCentered->size[0];
          for (b_idx = 0; b_idx < loop_ub; b_idx++) {
            y->data[b_idx] = y_notCentered->data[b_idx] - y_mean;
          }

          b_abs(b_x, r14);
          if (mean(r14) == 0.0) {
            /*  vertical line */
            Syy = 1.0;
            Sxx = 0.0;
            scale_x = -x_mean;
          } else {
            b_abs(y, r14);
            if (mean(r14) == 0.0) {
              /*  horizontal line */
              Syy = 0.0;
              Sxx = 1.0;
              scale_x = -y_mean;
            } else {
              /*  general case: use Deming regression */
              k0 = b_x->size[0];
              power(b_x, r15);
              scale_x = b_sum(r15);
              Sxx = scale_x / ((double)b_x->size[0] - 1.0);
              power(y, r15);
              scale_x = b_sum(r15);
              Syy = scale_x / ((double)b_x->size[0] - 1.0);
              b_idx = a->size[0] * a->size[1];
              a->size[0] = 1;
              a->size[1] = b_x->size[0];
              emxEnsureCapacity((emxArray__common *)a, b_idx, (int)sizeof(double));
              loop_ub = b_x->size[0];
              for (b_idx = 0; b_idx < loop_ub; b_idx++) {
                a->data[a->size[0] * b_idx] = b_x->data[b_idx];
              }

              if ((a->size[1] == 1) || (y->size[0] == 1)) {
                c_y = 0.0;
                for (b_idx = 0; b_idx < a->size[1]; b_idx++) {
                  c_y += a->data[a->size[0] * b_idx] * y->data[b_idx];
                }
              } else {
                c_y = 0.0;
                for (b_idx = 0; b_idx < a->size[1]; b_idx++) {
                  c_y += a->data[a->size[0] * b_idx] * y->data[b_idx];
                }
              }

              Sxy = c_y / ((double)b_x->size[0] - 1.0);
              scale_x = Syy - Sxx;
              scale_x = (Syy - Sxx) + sqrt(scale_x * scale_x + 4.0 * (Sxy * Sxy));
              c_y = scale_x / 2.0;
              Syy = scale_x / 2.0;
              Sxx = -Sxy;
              scale_x = -(-Sxy) * y_mean - c_y * x_mean;

              /*  In very rare cases for purely horizontal or vertical lines, the Deming regression estimator fails by producing 0's   */
              /*  for both alpha and beta. For an estimated line to */
              /*  be meaningful, either alpha or beta can be zero, but they cannot be */
              /*  zero simultaneously. And the failure of the Deming estimator does not */
              /*  mean the true values of alpha and beta cannot be estimated. */
              /*  In case of this, we give some small perturbation to the points so */
              /*  that the line is not likely to be purely horizontal or vertical. */
              if ((c_y == 0.0) && (-Sxy == 0.0)) {
                b_idx = b_x_notCentered->size[0];
                b_x_notCentered->size[0] = x_notCentered->size[0];
                emxEnsureCapacity((emxArray__common *)b_x_notCentered, b_idx,
                                  (int)sizeof(double));
                loop_ub = x_notCentered->size[0];
                for (b_idx = 0; b_idx < loop_ub; b_idx++) {
                  b_x_notCentered->data[b_idx] = x_notCentered->data[b_idx] -
                    x_mean;
                }

                b_abs(b_x_notCentered, r14);
                scale_x = b_sum(r14);
                scale_x *= 0.01;
                c_rand(nx - i12, b_x);
                b_idx = b_x->size[0];
                b_x->size[0] = x_notCentered->size[0];
                emxEnsureCapacity((emxArray__common *)b_x, b_idx, (int)sizeof
                                  (double));
                loop_ub = x_notCentered->size[0];
                for (b_idx = 0; b_idx < loop_ub; b_idx++) {
                  b_x->data[b_idx] = (x_notCentered->data[b_idx] - x_mean) +
                    scale_x * b_x->data[b_idx];
                }

                b_idx = b_y_notCentered->size[0];
                b_y_notCentered->size[0] = y_notCentered->size[0];
                emxEnsureCapacity((emxArray__common *)b_y_notCentered, b_idx,
                                  (int)sizeof(double));
                loop_ub = y_notCentered->size[0];
                for (b_idx = 0; b_idx < loop_ub; b_idx++) {
                  b_y_notCentered->data[b_idx] = y_notCentered->data[b_idx] -
                    y_mean;
                }

                b_abs(b_y_notCentered, r14);
                Syy = b_sum(r14);
                scale_x = Syy * 0.01;
                c_rand(nx - i12, y);
                i12 = y->size[0];
                y->size[0] = y_notCentered->size[0];
                emxEnsureCapacity((emxArray__common *)y, i12, (int)sizeof(double));
                loop_ub = y_notCentered->size[0];
                for (i12 = 0; i12 < loop_ub; i12++) {
                  y->data[i12] = (y_notCentered->data[i12] - y_mean) + scale_x *
                    y->data[i12];
                }

                power(b_x, r15);
                scale_x = b_sum(r15);
                Sxx = scale_x / ((double)k0 - 1.0);
                power(y, r15);
                scale_x = b_sum(r15);
                Syy = scale_x / ((double)k0 - 1.0);
                i12 = a->size[0] * a->size[1];
                a->size[0] = 1;
                a->size[1] = b_x->size[0];
                emxEnsureCapacity((emxArray__common *)a, i12, (int)sizeof(double));
                loop_ub = b_x->size[0];
                for (i12 = 0; i12 < loop_ub; i12++) {
                  a->data[a->size[0] * i12] = b_x->data[i12];
                }

                if ((a->size[1] == 1) || (y->size[0] == 1)) {
                  c_y = 0.0;
                  for (i12 = 0; i12 < a->size[1]; i12++) {
                    c_y += a->data[a->size[0] * i12] * y->data[i12];
                  }
                } else {
                  c_y = 0.0;
                  for (i12 = 0; i12 < a->size[1]; i12++) {
                    c_y += a->data[a->size[0] * i12] * y->data[i12];
                  }
                }

                Sxy = c_y / ((double)k0 - 1.0);
                scale_x = Syy - Sxx;
                scale_x = (Syy - Sxx) + sqrt(scale_x * scale_x + 4.0 * (Sxy *
                  Sxy));
                Syy = scale_x / 2.0;
                Sxx = -Sxy;
                scale_x = -(-Sxy) * y_mean - scale_x / 2.0 * x_mean;
              }
            }
          }

          expl_temp.alpha_hat = Syy;
          expl_temp.beta_hat = Sxx;
          expl_temp.gamma_hat = scale_x;
          lines_data[numlines].param = expl_temp;
          b_idx = (int)(idx->data[p] + 1.0);
          for (i12 = 0; i12 < 2; i12++) {
            b_peaks_data[i12] = xy->data[(b_idx + xy->size[0] * i12) - 1];
          }

          findPointOnTheLine(b_peaks_data, Syy, Sxx, scale_x,
                             lines_data[numlines].point1);
          b_idx = (int)idx->data[1 + p];
          for (i12 = 0; i12 < 2; i12++) {
            b_peaks_data[i12] = xy->data[(b_idx + xy->size[0] * i12) - 1];
          }

          findPointOnTheLine(b_peaks_data, Syy, Sxx, scale_x,
                             lines_data[numlines].point2);
          scale_x = floor(peaks_data[k + peaks_size_idx_0]);
          Syy = scale_x + 1.0;
          if (scale_x + 1.0 > 180.0) {
            Syy = 180.0;
          }

          lines_data[numlines].theta = (-90.0 + (scale_x - 1.0)) + ((-90.0 +
            (Syy - 1.0)) - (-90.0 + (scale_x - 1.0))) * (peaks_data[k +
            peaks_size_idx_0] - scale_x);
          scale_x = floor(peaks_data[k]);
          Syy = scale_x + 1.0;
          if (scale_x + 1.0 > 180.0) {
            Syy = 180.0;
          }

          lines_data[numlines].rho = rho->data[(int)scale_x - 1] + (rho->data
            [(int)Syy - 1] - rho->data[(int)scale_x - 1]) * (peaks_data[k] -
            scale_x);
        }
      }
    }

    k++;
  }

  emxFree_real_T(&b_x_notCentered);
  emxFree_real_T(&b_y_notCentered);
  emxFree_real_T(&r15);
  emxFree_real_T(&r14);
  emxFree_real_T(&a);
  emxFree_real_T(&y);
  emxFree_real_T(&b_x);
  emxFree_real_T(&y_notCentered);
  emxFree_real_T(&x_notCentered);
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&rho);
  emxFree_real_T(&nonzeropix);
  emxFree_real_T(&pointForThisLine);
  emxFree_real_T(&idx);
  emxFree_real_T(&dist_sq);
  emxFree_real_T(&diff_xy_sq);
  emxFree_real_T(&xy);
  nx = (int)(30.0 - ((double)(numlines + 1) + 1.0)) + 1;
  loop_ub = (int)(30.0 - ((double)(numlines + 1) + 1.0));
  for (i12 = 0; i12 <= loop_ub; i12++) {
    idx_data[i12] = ((double)(numlines + 1) + 1.0) + (double)i12;
  }

  if (nx == 1) {
    for (k = (int)idx_data[0]; k < 30; k++) {
      lines_data[k - 1] = lines_data[k];
    }

    for (i12 = 0; i12 < 29; i12++) {
      b_lines_data[i12] = lines_data[i12];
    }

    lines_size[0] = 1;
    lines_size[1] = 29;
    for (i12 = 0; i12 < 29; i12++) {
      lines_data[i12] = b_lines_data[i12];
    }
  } else {
    for (i12 = 0; i12 < 30; i12++) {
      b_data[i12] = false;
    }

    for (k = 1; k <= nx; k++) {
      b_data[(int)idx_data[k - 1] - 1] = true;
    }

    nx = 0;
    for (k = 1; k < 31; k++) {
      nx += b_data[k - 1];
    }

    k0 = -1;
    for (k = 0; k < 30; k++) {
      if (!b_data[k]) {
        k0++;
        lines_data[k0] = lines_data[k];
      }
    }

    if (1 > 30 - nx) {
      lines_size[1] = 0;
    } else {
      lines_size[1] = 30 - nx;
    }
  }
}

/* End of code generation (houghlines_precise.c) */
