/*
 * ransacFit_plane.c
 *
 * Code generation for function 'ransacFit_plane'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "ransacFit_plane.h"
#include "mean.h"
#include "abs.h"
#include "mldivide.h"
#include "rcond.h"
#include "round.h"
#include "rand.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void ransacFit_plane(const double gx[169], const double gy[169], const double
                     val[169], double val_fitted[169], double
                     best_beta_hat_data[], int best_beta_hat_size[2], double
                     *minErr)
{
  double X_all[507];
  int ib;
  double idxSet_arr[3000];
  int i;
  double X[9];
  double b_X[9];
  double c_X[3];
  double beta_hat[3];
  int ia;
  int ar;
  double b_X_all[169];
  double err;
  double dv17[169];
  double y_data[169];

  /*  Find the best fitted plane using RANSEC */
  /*  Chau-Wai Wong, Nov. 2014 */
  *minErr = 1.0E+10;
  best_beta_hat_size[0] = 0;
  best_beta_hat_size[1] = 0;
  for (ib = 0; ib < 169; ib++) {
    X_all[ib] = 1.0;
    X_all[169 + ib] = gx[ib];
    X_all[338 + ib] = gy[ib];
  }

  d_rand(idxSet_arr);
  for (ib = 0; ib < 3000; ib++) {
    idxSet_arr[ib] *= 168.0;
  }

  d_round(idxSet_arr);
  for (ib = 0; ib < 3000; ib++) {
    idxSet_arr[ib]++;
  }

  for (i = 0; i < 1000; i++) {
    for (ib = 0; ib < 3; ib++) {
      X[ib] = 1.0;
      X[3 + ib] = gx[(int)idxSet_arr[ib + 3 * i] - 1];
      X[6 + ib] = gy[(int)idxSet_arr[ib + 3 * i] - 1];
    }

    if (b_rcond(X) < 1.0E-10) {
      /* disp(['skipped ' int2str(i)]) */
    } else {
      for (ib = 0; ib < 3; ib++) {
        for (ia = 0; ia < 3; ia++) {
          b_X[ib + 3 * ia] = 0.0;
          for (ar = 0; ar < 3; ar++) {
            b_X[ib + 3 * ia] += X[ar + 3 * ib] * X[ar + 3 * ia];
          }
        }

        beta_hat[ib] = val[(int)idxSet_arr[ib + 3 * i] - 1];
      }

      for (ib = 0; ib < 3; ib++) {
        c_X[ib] = 0.0;
        for (ia = 0; ia < 3; ia++) {
          c_X[ib] += X[ia + 3 * ib] * beta_hat[ia];
        }
      }

      c_mldivide(b_X, c_X, beta_hat);
      for (ib = 0; ib < 169; ib++) {
        err = 0.0;
        for (ia = 0; ia < 3; ia++) {
          err += X_all[ib + 169 * ia] * beta_hat[ia];
        }

        b_X_all[ib] = err - val[ib];
      }

      e_abs(b_X_all, dv17);
      err = e_mean(dv17);
      if (err < *minErr) {
        best_beta_hat_size[0] = 3;
        best_beta_hat_size[1] = 1;
        for (ib = 0; ib < 3; ib++) {
          best_beta_hat_data[ib] = beta_hat[ib];
        }

        *minErr = err;
      }
    }
  }

  if (best_beta_hat_size[0] == 1) {
    for (ib = 0; ib < 169; ib++) {
      i = best_beta_hat_size[1];
      ia = 0;
      while (ia <= i - 1) {
        y_data[ib] = 0.0;
        for (ia = 0; ia < 3; ia++) {
          y_data[ib] += X_all[ib + 169 * ia] * best_beta_hat_data[ia];
        }

        ia = 1;
      }
    }
  } else {
    i = 169 * best_beta_hat_size[1];
    for (ib = 0; ib < i; ib++) {
      y_data[ib] = 0.0;
    }

    if (best_beta_hat_size[1] == 0) {
    } else {
      for (i = 1; i < 170; i++) {
        y_data[i - 1] = 0.0;
      }

      ar = 0;
      for (ib = 0; ib + 1 < 4; ib++) {
        if (best_beta_hat_data[ib] != 0.0) {
          ia = ar;
          for (i = 0; i + 1 < 170; i++) {
            ia++;
            y_data[i] += best_beta_hat_data[ib] * X_all[ia - 1];
          }
        }

        ar += 169;
      }
    }
  }

  memcpy(&val_fitted[0], &y_data[0], 169U * sizeof(double));
}

/* End of code generation (ransacFit_plane.c) */
