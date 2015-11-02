/*
 * rcond.c
 *
 * Code generation for function 'rcond'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "rcond.h"
#include "norm.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
double b_rcond(const double A[9])
{
  double result;
  double normA;
  double b_A[9];
  int j;
  int c;
  int jlast;
  int ix;
  double smax;
  int kase;
  double temp;
  int iter;
  int i;
  int b_j;
  int jump;
  int32_T exitg2;
  double ainvnm;
  double x[3];
  int32_T exitg1;
  result = 0.0;
  normA = d_norm(A);
  if (normA == 0.0) {
  } else {
    memcpy(&b_A[0], &A[0], 9U * sizeof(double));
    for (j = 0; j < 2; j++) {
      c = j << 2;
      jlast = 0;
      ix = c;
      smax = fabs(b_A[c]);
      for (kase = 1; kase + 1 <= 3 - j; kase++) {
        ix++;
        temp = fabs(b_A[ix]);
        if (temp > smax) {
          jlast = kase;
          smax = temp;
        }
      }

      if (b_A[c + jlast] != 0.0) {
        if (jlast != 0) {
          ix = j;
          jlast += j;
          for (kase = 0; kase < 3; kase++) {
            temp = b_A[ix];
            b_A[ix] = b_A[jlast];
            b_A[jlast] = temp;
            ix += 3;
            jlast += 3;
          }
        }

        iter = (c - j) + 3;
        for (i = c + 1; i + 1 <= iter; i++) {
          b_A[i] /= b_A[c];
        }
      }

      jlast = c;
      kase = c + 3;
      for (b_j = 1; b_j <= 2 - j; b_j++) {
        temp = b_A[kase];
        if (b_A[kase] != 0.0) {
          ix = c + 1;
          iter = (jlast - j) + 6;
          for (jump = 4 + jlast; jump + 1 <= iter; jump++) {
            b_A[jump] += b_A[ix] * -temp;
            ix++;
          }
        }

        kase += 3;
        jlast += 3;
      }
    }

    kase = 2;
    do {
      exitg2 = 0;
      if (kase + 1 > 0) {
        if (b_A[kase + 3 * kase] == 0.0) {
          exitg2 = 1;
        } else {
          kase--;
        }
      } else {
        ainvnm = 0.0;
        iter = 2;
        kase = 1;
        jump = 1;
        j = 0;
        for (i = 0; i < 3; i++) {
          x[i] = 0.33333333333333331;
        }

        exitg2 = 2;
      }
    } while (exitg2 == 0);

    if (exitg2 == 1) {
    } else {
      do {
        exitg1 = 0;
        if (kase != 0) {
          if (kase == 1) {
            for (b_j = 0; b_j < 3; b_j++) {
              jlast = b_j + b_j * 3;
              for (i = 1; i <= 2 - b_j; i++) {
                ix = b_j + i;
                x[ix] -= x[b_j] * b_A[jlast + i];
              }
            }

            for (b_j = 2; b_j > -1; b_j += -1) {
              jlast = b_j + b_j * 3;
              x[b_j] /= b_A[jlast];
              for (i = 1; i <= b_j; i++) {
                ix = b_j - i;
                x[ix] -= x[b_j] * b_A[jlast - i];
              }
            }
          } else {
            for (b_j = 0; b_j < 3; b_j++) {
              c = b_j * 3;
              temp = x[b_j];
              for (i = 0; i + 1 <= b_j; i++) {
                temp -= b_A[c + i] * x[i];
              }

              temp /= b_A[c + b_j];
              x[b_j] = temp;
            }

            for (b_j = 2; b_j > -1; b_j += -1) {
              c = b_j * 3;
              temp = x[b_j];
              for (i = 2; i + 1 >= b_j + 2; i--) {
                temp -= b_A[c + i] * x[i];
              }

              x[b_j] = temp;
            }
          }

          if (jump == 1) {
            ainvnm = 0.0;
            for (kase = 0; kase < 3; kase++) {
              ainvnm += fabs(x[kase]);
            }

            if (!((!rtIsInf(ainvnm)) && (!rtIsNaN(ainvnm)))) {
              result = ainvnm;
              exitg1 = 1;
            } else {
              for (kase = 0; kase < 3; kase++) {
                temp = fabs(x[kase]);
                if (temp > 2.2250738585072014E-308) {
                  temp = x[kase] / temp;
                } else {
                  temp = 1.0;
                }

                x[kase] = temp;
              }

              kase = 2;
              jump = 2;
            }
          } else if (jump == 2) {
            j = 0;
            smax = fabs(x[0]);
            for (kase = 0; kase < 2; kase++) {
              temp = fabs(x[kase + 1]);
              if (temp <= smax) {
              } else {
                j = 1 + kase;
                smax = temp;
              }
            }

            iter = 2;
            for (i = 0; i < 3; i++) {
              x[i] = 0.0;
            }

            x[j] = 1.0;
            kase = 1;
            jump = 3;
          } else if (jump == 3) {
            ainvnm = 0.0;
            for (kase = 0; kase < 3; kase++) {
              ainvnm += fabs(x[kase]);
            }

            if (ainvnm <= x[0]) {
              temp = 1.0;
              for (kase = 0; kase < 3; kase++) {
                x[kase] = temp * (1.0 + ((1.0 + (double)kase) - 1.0) / 2.0);
                temp = -temp;
              }

              kase = 1;
              jump = 5;
            } else {
              for (kase = 0; kase < 3; kase++) {
                temp = fabs(x[kase]);
                if (temp > 2.2250738585072014E-308) {
                  temp = x[kase] / temp;
                } else {
                  temp = 1.0;
                }

                x[kase] = temp;
              }

              kase = 2;
              jump = 4;
            }
          } else if (jump == 4) {
            jlast = j;
            j = 0;
            smax = fabs(x[0]);
            for (kase = 0; kase < 2; kase++) {
              temp = fabs(x[kase + 1]);
              if (temp <= smax) {
              } else {
                j = 1 + kase;
                smax = temp;
              }
            }

            if ((fabs(x[jlast]) != fabs(x[j])) && (iter <= 5)) {
              iter++;
              for (i = 0; i < 3; i++) {
                x[i] = 0.0;
              }

              x[j] = 1.0;
              kase = 1;
              jump = 3;
            } else {
              temp = 1.0;
              for (kase = 0; kase < 3; kase++) {
                x[kase] = temp * (1.0 + ((1.0 + (double)kase) - 1.0) / 2.0);
                temp = -temp;
              }

              kase = 1;
              jump = 5;
            }
          } else {
            if (jump == 5) {
              temp = 0.0;
              for (kase = 0; kase < 3; kase++) {
                temp += fabs(x[kase]);
              }

              temp = 2.0 * temp / 3.0 / 3.0;
              if (temp > ainvnm) {
                ainvnm = temp;
              }

              kase = 0;
            }
          }
        } else {
          if (ainvnm != 0.0) {
            result = 1.0 / ainvnm / normA;
          }

          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }

  return result;
}

double rcond(const double A[36])
{
  double result;
  double normA;
  double b_A[36];
  int j;
  int c;
  int jlast;
  int ix;
  double smax;
  int kase;
  double temp;
  int iter;
  int i;
  int b_j;
  int jump;
  int32_T exitg2;
  double ainvnm;
  double x[6];
  int32_T exitg1;
  result = 0.0;
  normA = norm(A);
  if (normA == 0.0) {
  } else {
    memcpy(&b_A[0], &A[0], 36U * sizeof(double));
    for (j = 0; j < 5; j++) {
      c = j * 7;
      jlast = 0;
      ix = c;
      smax = fabs(b_A[c]);
      for (kase = 1; kase + 1 <= 6 - j; kase++) {
        ix++;
        temp = fabs(b_A[ix]);
        if (temp > smax) {
          jlast = kase;
          smax = temp;
        }
      }

      if (b_A[c + jlast] != 0.0) {
        if (jlast != 0) {
          ix = j;
          jlast += j;
          for (kase = 0; kase < 6; kase++) {
            temp = b_A[ix];
            b_A[ix] = b_A[jlast];
            b_A[jlast] = temp;
            ix += 6;
            jlast += 6;
          }
        }

        iter = (c - j) + 6;
        for (i = c + 1; i + 1 <= iter; i++) {
          b_A[i] /= b_A[c];
        }
      }

      jlast = c;
      kase = c + 6;
      for (b_j = 1; b_j <= 5 - j; b_j++) {
        temp = b_A[kase];
        if (b_A[kase] != 0.0) {
          ix = c + 1;
          iter = (jlast - j) + 12;
          for (jump = 7 + jlast; jump + 1 <= iter; jump++) {
            b_A[jump] += b_A[ix] * -temp;
            ix++;
          }
        }

        kase += 6;
        jlast += 6;
      }
    }

    kase = 5;
    do {
      exitg2 = 0;
      if (kase + 1 > 0) {
        if (b_A[kase + 6 * kase] == 0.0) {
          exitg2 = 1;
        } else {
          kase--;
        }
      } else {
        ainvnm = 0.0;
        iter = 2;
        kase = 1;
        jump = 1;
        j = 0;
        for (i = 0; i < 6; i++) {
          x[i] = 0.16666666666666666;
        }

        exitg2 = 2;
      }
    } while (exitg2 == 0);

    if (exitg2 == 1) {
    } else {
      do {
        exitg1 = 0;
        if (kase != 0) {
          if (kase == 1) {
            for (b_j = 0; b_j < 6; b_j++) {
              jlast = b_j + b_j * 6;
              for (i = 1; i <= 5 - b_j; i++) {
                ix = b_j + i;
                x[ix] -= x[b_j] * b_A[jlast + i];
              }
            }

            for (b_j = 5; b_j > -1; b_j += -1) {
              jlast = b_j + b_j * 6;
              x[b_j] /= b_A[jlast];
              for (i = 1; i <= b_j; i++) {
                ix = b_j - i;
                x[ix] -= x[b_j] * b_A[jlast - i];
              }
            }
          } else {
            for (b_j = 0; b_j < 6; b_j++) {
              c = b_j * 6;
              temp = x[b_j];
              for (i = 0; i + 1 <= b_j; i++) {
                temp -= b_A[c + i] * x[i];
              }

              temp /= b_A[c + b_j];
              x[b_j] = temp;
            }

            for (b_j = 5; b_j > -1; b_j += -1) {
              c = b_j * 6;
              temp = x[b_j];
              for (i = 5; i + 1 >= b_j + 2; i--) {
                temp -= b_A[c + i] * x[i];
              }

              x[b_j] = temp;
            }
          }

          if (jump == 1) {
            ainvnm = 0.0;
            for (kase = 0; kase < 6; kase++) {
              ainvnm += fabs(x[kase]);
            }

            if (!((!rtIsInf(ainvnm)) && (!rtIsNaN(ainvnm)))) {
              result = ainvnm;
              exitg1 = 1;
            } else {
              for (kase = 0; kase < 6; kase++) {
                temp = fabs(x[kase]);
                if (temp > 2.2250738585072014E-308) {
                  temp = x[kase] / temp;
                } else {
                  temp = 1.0;
                }

                x[kase] = temp;
              }

              kase = 2;
              jump = 2;
            }
          } else if (jump == 2) {
            j = 0;
            smax = fabs(x[0]);
            for (kase = 0; kase < 5; kase++) {
              temp = fabs(x[kase + 1]);
              if (temp <= smax) {
              } else {
                j = 1 + kase;
                smax = temp;
              }
            }

            iter = 2;
            for (i = 0; i < 6; i++) {
              x[i] = 0.0;
            }

            x[j] = 1.0;
            kase = 1;
            jump = 3;
          } else if (jump == 3) {
            ainvnm = 0.0;
            for (kase = 0; kase < 6; kase++) {
              ainvnm += fabs(x[kase]);
            }

            if (ainvnm <= x[0]) {
              temp = 1.0;
              for (kase = 0; kase < 6; kase++) {
                x[kase] = temp * (1.0 + ((1.0 + (double)kase) - 1.0) / 5.0);
                temp = -temp;
              }

              kase = 1;
              jump = 5;
            } else {
              for (kase = 0; kase < 6; kase++) {
                temp = fabs(x[kase]);
                if (temp > 2.2250738585072014E-308) {
                  temp = x[kase] / temp;
                } else {
                  temp = 1.0;
                }

                x[kase] = temp;
              }

              kase = 2;
              jump = 4;
            }
          } else if (jump == 4) {
            jlast = j;
            j = 0;
            smax = fabs(x[0]);
            for (kase = 0; kase < 5; kase++) {
              temp = fabs(x[kase + 1]);
              if (temp <= smax) {
              } else {
                j = 1 + kase;
                smax = temp;
              }
            }

            if ((fabs(x[jlast]) != fabs(x[j])) && (iter <= 5)) {
              iter++;
              for (i = 0; i < 6; i++) {
                x[i] = 0.0;
              }

              x[j] = 1.0;
              kase = 1;
              jump = 3;
            } else {
              temp = 1.0;
              for (kase = 0; kase < 6; kase++) {
                x[kase] = temp * (1.0 + ((1.0 + (double)kase) - 1.0) / 5.0);
                temp = -temp;
              }

              kase = 1;
              jump = 5;
            }
          } else {
            if (jump == 5) {
              temp = 0.0;
              for (kase = 0; kase < 6; kase++) {
                temp += fabs(x[kase]);
              }

              temp = 2.0 * temp / 3.0 / 6.0;
              if (temp > ainvnm) {
                ainvnm = temp;
              }

              kase = 0;
            }
          }
        } else {
          if (ainvnm != 0.0) {
            result = 1.0 / ainvnm / normA;
          }

          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }

  return result;
}

/* End of code generation (rcond.c) */
