/*
 * findFourLines_v2.c
 *
 * Code generation for function 'findFourLines_v2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "findFourLines_v2.h"
#include "getPowderAndQr_emxutil.h"
#include "houghlines_precise.h"
#include "round.h"
#include "getMorePreciseMaxPoints.h"
#include "fliplr.h"
#include "SystemCore.h"
#include "LocalMaximaFinder.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void findFourLines_v2(const emxArray_uint8_T *im, const emxArray_boolean_T *mask,
                      double edgeLength, double thres, double *figIdx,
                      e_struct_T lines_data[], int lines_size[2])
{
  visioncodegen_HoughTransform_6 hhoughtrans;
  emxArray_boolean_T *BW;
  emxArray_boolean_T *U0;
  int i47;
  int i;
  visioncodegen_HoughTransform_6 *obj;
  static const double dv20[91] = { -1.0, -0.99984769515639127,
    -0.99939082701909565, -0.99862953475457383, -0.9975640502598242,
    -0.99619469809174555, -0.9945218953682734, -0.992546151641322,
    -0.99026806874157036, -0.98768834059513766, -0.98480775301220791,
    -0.98162718344766386, -0.97814760073380558, -0.97437006478523525,
    -0.97029572627599658, -0.96592582628906831, -0.96126169593831889,
    -0.95630475596303555, -0.95105651629515353, -0.94551857559931674,
    -0.93969262078590832, -0.93358042649720174, -0.92718385456678754,
    -0.92050485345244026, -0.913545457642601, -0.90630778703664994,
    -0.898794046299167, -0.89100652418836779, -0.88294759285892688,
    -0.87461970713939574, -0.8660254037844386, -0.85716730070211233,
    -0.848048096156426, -0.838670567945424, -0.82903757255504162,
    -0.8191520442889918, -0.80901699437494745, -0.79863551004729283,
    -0.788010753606722, -0.7771459614569709, -0.766044443118978,
    -0.7547095802227719, -0.74314482547739424, -0.73135370161917046,
    -0.71933980033865119, -0.70710678118654746, -0.69465837045899725,
    -0.68199836006249859, -0.66913060635885824, -0.65605902899050728,
    -0.64278760968653936, -0.62932039104983739, -0.61566147532565829,
    -0.60181502315204827, -0.587785252292473, -0.573576436351046,
    -0.55919290347074679, -0.54463903501502708, -0.529919264233205,
    -0.51503807491005416, -0.49999999999999994, -0.48480962024633706,
    -0.46947156278589081, -0.45399049973954675, -0.4383711467890774,
    -0.42261826174069939, -0.40673664307580026, -0.39073112848927377,
    -0.37460659341591196, -0.35836794954530027, -0.34202014332566871,
    -0.3255681544571567, -0.30901699437494745, -0.29237170472273677,
    -0.27563735581699916, -0.25881904510252074, -0.24192189559966773,
    -0.224951054343865, -0.20791169081775934, -0.1908089953765448,
    -0.17364817766693033, -0.15643446504023087, -0.13917310096006544,
    -0.12186934340514748, -0.10452846326765347, -0.087155742747658166,
    -0.0697564737441253, -0.052335956242943835, -0.034899496702500969,
    -0.017452406437283512, 0.0 };

  int mRowsIn;
  int mColsIn;
  double accTmp;
  int q;
  emxArray_real_T *b_obj;
  int loop_ub;
  int i48;
  emxArray_real_T *c_obj;
  emxArray_real_T *H;
  double anew;
  double apnd;
  double cdiff;
  double absa;
  double absb;
  emxArray_real_T *y;
  static visioncodegen_LocalMaximaFinder hLocalMax;
  int P_size[2];
  unsigned int P_data[20];
  int P_olderVersion_size[2];
  double P_olderVersion_data[20];
  double P_prec_data[20];
  c_emxInitStruct_visioncodegen_H(&hhoughtrans);
  emxInit_boolean_T(&BW, 2);
  emxInit_boolean_T(&U0, 2);
  *figIdx = 0.0;

  /* % This function finds all lines (not only 4 lines) using Hough transform */
  /*   for the binary map "im". */
  /*   Chau-Wai Wong, Oct. 2014. */
  /*   Chau-Wai Wong, Mar. 2015. */
  /*  QR code removed by the known mask */
  i47 = BW->size[0] * BW->size[1];
  BW->size[0] = im->size[0];
  BW->size[1] = im->size[1];
  emxEnsureCapacity((emxArray__common *)BW, i47, (int)sizeof(boolean_T));
  i = im->size[0] * im->size[1];
  for (i47 = 0; i47 < i; i47++) {
    BW->data[i47] = ((255.0 - (double)im->data[i47] > thres) * mask->data[i47]
                     != 0);
  }

  /*  % %     if debugMode >= 1 */
  /*  % %         %figure(586); imshow(BW_raw); */
  /*  % %         hFig = figure(587); imshow(BW_needed) */
  /*  % %         set(hFig, 'position', [0 50 300 300]); */
  /*  % %         title('QR region removed and thresholded image') */
  /*  % %     end */
  /*  Similarly, the following 2 parameters should also be adaptive */
  /*  good value 80. Range: 80/[604, 1100] = [0.133, 0.073]. Mean = 0.1 */
  /*  good value 50. Range: 50/[604, 1100] = [0.083, 0.046]. Mean = 0.065 */
  /*  % % coder.extrinsic('hough') */
  /*  % % % Hough() is not supported for codegen */
  /*  % % [H,theta,rho] = hough(BW_needed); */
  /*  The implementation below isn't supported by the Matlab to C conversion, */
  /*  as the size of output variable theta_rad is dependent on the size of */
  /*  input image BW_needed. */
  /* hhoughtrans = vision.HoughTransform(pi/180, 'ThetaRhoOutputPort', true); */
  /* [H,theta_rad,rho] = step(hhoughtrans, BW_needed); */
  /* theta = theta_rad / pi * 180; */
  /*  The following code works ... */
  obj = &hhoughtrans;
  hhoughtrans.matlabCodegenIsDeleted = false;
  hhoughtrans.isInitialized = false;
  hhoughtrans.isReleased = false;
  hhoughtrans.matlabCodegenIsDeleted = false;
  hhoughtrans.matlabCodegenIsDeleted = false;

  /* System object Constructor function: vision.HoughTransform */
  obj->cSFunObject.S0_isInitialized = false;
  obj->cSFunObject.S1_isReleased = false;
  for (i = 0; i < 91; i++) {
    obj->cSFunObject.P0_SINE_TABLE_RTP[i] = dv20[i];
  }

  obj->cSFunObject.P1_RHO_RESOL_RTP = 1.0;
  obj = &hhoughtrans;
  if (!hhoughtrans.isInitialized) {
    hhoughtrans.isInitialized = true;
  }

  i47 = U0->size[0] * U0->size[1];
  U0->size[0] = BW->size[0];
  U0->size[1] = BW->size[1];
  emxEnsureCapacity((emxArray__common *)U0, i47, (int)sizeof(boolean_T));
  i = BW->size[0] * BW->size[1];
  for (i47 = 0; i47 < i; i47++) {
    U0->data[i47] = BW->data[i47];
  }

  /* System object Outputs function: vision.HoughTransform */
  mRowsIn = U0->size[0];
  mColsIn = U0->size[1];
  accTmp = ceil(sqrt((mRowsIn - 1) * (mRowsIn - 1) + (mColsIn - 1) * (mColsIn -
    1)) / obj->cSFunObject.P1_RHO_RESOL_RTP);
  obj->cSFunObject.W0_FIRSTRHO_DW = (int)accTmp;
  obj->cSFunObject.W0_FIRSTRHO_DW = -(obj->cSFunObject.W0_FIRSTRHO_DW *
    obj->cSFunObject.P1_RHO_RESOL_RTP);
  q = ((int)accTmp << 1) + 1;
  if (q < 1) {
    q = 1;
  }

  emxInit_real_T(&b_obj, 2);
  i47 = obj->cSFunObject.O0_Y0->size[0] * obj->cSFunObject.O0_Y0->size[1];
  obj->cSFunObject.O0_Y0->size[0] = q;
  obj->cSFunObject.O0_Y0->size[1] = 180;
  emxEnsureCapacity((emxArray__common *)obj->cSFunObject.O0_Y0, i47, (int)sizeof
                    (double));
  i47 = b_obj->size[0] * b_obj->size[1];
  b_obj->size[0] = obj->cSFunObject.O0_Y0->size[0];
  b_obj->size[1] = obj->cSFunObject.O0_Y0->size[1];
  emxEnsureCapacity((emxArray__common *)b_obj, i47, (int)sizeof(double));
  i = obj->cSFunObject.O0_Y0->size[1];
  for (i47 = 0; i47 < i; i47++) {
    loop_ub = obj->cSFunObject.O0_Y0->size[0];
    for (i48 = 0; i48 < loop_ub; i48++) {
      b_obj->data[i48 + b_obj->size[0] * i47] = obj->cSFunObject.O0_Y0->data[i48
        + obj->cSFunObject.O0_Y0->size[0] * i47];
    }
  }

  emxFree_real_T(&b_obj);
  emxInit_real_T(&c_obj, 2);
  i47 = c_obj->size[0] * c_obj->size[1];
  c_obj->size[0] = obj->cSFunObject.O0_Y0->size[0];
  c_obj->size[1] = obj->cSFunObject.O0_Y0->size[1];
  emxEnsureCapacity((emxArray__common *)c_obj, i47, (int)sizeof(double));
  i = obj->cSFunObject.O0_Y0->size[1];
  for (i47 = 0; i47 < i; i47++) {
    loop_ub = obj->cSFunObject.O0_Y0->size[0];
    for (i48 = 0; i48 < loop_ub; i48++) {
      c_obj->data[i48 + c_obj->size[0] * i47] = obj->cSFunObject.O0_Y0->data[i48
        + obj->cSFunObject.O0_Y0->size[0] * i47];
    }
  }

  emxFree_real_T(&c_obj);
  emxInit_real_T(&H, 2);
  MWVIP_Hough_D(&U0->data[0], &obj->cSFunObject.O0_Y0->data[0],
                &obj->cSFunObject.P0_SINE_TABLE_RTP[0],
                &obj->cSFunObject.W0_FIRSTRHO_DW, mRowsIn, mColsIn, q, 91);
  i47 = H->size[0] * H->size[1];
  H->size[0] = obj->cSFunObject.O0_Y0->size[0];
  H->size[1] = obj->cSFunObject.O0_Y0->size[1];
  emxEnsureCapacity((emxArray__common *)H, i47, (int)sizeof(double));
  i = obj->cSFunObject.O0_Y0->size[0] * obj->cSFunObject.O0_Y0->size[1];
  for (i47 = 0; i47 < i; i47++) {
    H->data[i47] = obj->cSFunObject.O0_Y0->data[i47];
  }

  accTmp = ((double)H->size[0] - 1.0) / 2.0;
  if (accTmp < -accTmp) {
    mColsIn = -1;
    anew = -accTmp;
    apnd = accTmp;
  } else {
    anew = -accTmp;
    i = (int)floor((accTmp - (-accTmp)) + 0.5);
    apnd = -accTmp + (double)i;
    cdiff = apnd - accTmp;
    absa = fabs(-accTmp);
    absb = fabs(accTmp);
    if (absa >= absb) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      i++;
      apnd = accTmp;
    } else if (cdiff > 0.0) {
      apnd = -accTmp + ((double)i - 1.0);
    } else {
      i++;
    }

    if (i >= 0) {
      mColsIn = i - 1;
    } else {
      mColsIn = -1;
    }
  }

  emxInit_real_T(&y, 2);
  i47 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = mColsIn + 1;
  emxEnsureCapacity((emxArray__common *)y, i47, (int)sizeof(double));
  if (mColsIn + 1 > 0) {
    y->data[0] = anew;
    if (mColsIn + 1 > 1) {
      y->data[mColsIn] = apnd;
      i = mColsIn / 2;
      for (mRowsIn = 1; mRowsIn < i; mRowsIn++) {
        y->data[mRowsIn] = anew + (double)mRowsIn;
        y->data[mColsIn - mRowsIn] = apnd - (double)mRowsIn;
      }

      if (i << 1 == mColsIn) {
        y->data[i] = (anew + apnd) / 2.0;
      } else {
        y->data[i] = anew + (double)i;
        y->data[i + 1] = apnd - (double)i;
      }
    }
  }

  /*  % % %if ~merelyShowFinalImage */
  /*  % % if debugMode >= 2 */
  /*  % %     figIdx = figIdx+1; hFig = figure(figIdx); */
  /*  % %     if figureSilentMode, set(hFig, 'visible','off'); end */
  /*  % %     imshow(imadjust(mat2gray(H)),[],'XData',theta,'YData',rho,... */
  /*  % %         'InitialMagnification','fit'); */
  /*  % %     xlabel('\theta (degrees)'), ylabel('\rho'); */
  /*  % %     axis on, axis normal, hold on; */
  /*  % %     colormap(hot); */
  /*  % %     title('Hough transform of binarized tri-patch box') */
  /*  % % end */
  /* neighhoodSize = [501, 101]; % 1st parameter for rho is absolute, whereas 2nd parameter for theta is relative */
  /*  1st parameter for rho is absolute, whereas 2nd parameter for theta is relative */
  /* largestVal = max(H(:)); % Matlab Coder compiler does not like this ... */
  /*  % % coder.extrinsic('houghpeaks') */
  /*  % % P = houghpeaks(H, peakCnt, 'threshold', houghThres, 'NHoodSize', neighhoodSize); */
  c_LocalMaximaFinder_LocalMaxima(&hLocalMax);

  /*  The object will assume a Hough matrix input when "HoughMatrixInput" is */
  /*  set to true. The block applies additional processing, specific to Hough */
  /*  transform on the right and left boundaries of the input matrix. */
  b_SystemCore_step(&hLocalMax, H, P_data, P_size);
  fliplr(P_data, P_size);
  P_olderVersion_size[0] = P_size[0];
  P_olderVersion_size[1] = P_size[1];
  i = P_size[0] * P_size[1];
  for (i47 = 0; i47 < i; i47++) {
    P_olderVersion_data[i47] = P_data[i47];
  }

  /*  hhoughlines = vision.HoughLines('SineComputation', 'Trigonometric function'); */
  /*  linepts = step(hhoughlines, theta(P(:,1))/180*pi, rho(P(:,2)), BW); */
  /* if morePreciseMatchingFlag */
  /*  improve the precision of maximal points */
  getMorePreciseMaxPoints(H, P_olderVersion_data, P_olderVersion_size,
    P_prec_data, P_size);

  /* end */
  /*  % % x = theta(P(:,2)); */
  /*  % % y = rho(P(:,1)); */
  /*  % % %if ~merelyShowFinalImage */
  /*  % % if debugMode >= 2 */
  /*  % %     plot(x,y,'s','color','black'); */
  /*  % %     set(hFig, 'Position', figPos{figIdx}); hold off */
  /*  % %     set(hFig, 'position', [400 600 500 300]); */
  /*  % % end */
  /* coder.extrinsic('houghlines_precise') */
  /* if morePreciseMatchingFlag */
  houghlines_precise(BW, y, P_prec_data, P_size, rt_roundd_snf(0.065 * (2.0 *
    edgeLength)), rt_roundd_snf(0.1 * (2.0 * edgeLength)), lines_data,
                     lines_size);

  /* else */
  /*     lines = houghlines(BW, theta, rho, P, 'FillGap', gapToFillSize, 'MinLength', minLength); */
  /* end */
  /* pause(0.1) */
  emxFree_real_T(&y);
  emxFree_real_T(&H);
  emxFree_boolean_T(&BW);
  if (!hLocalMax.matlabCodegenIsDeleted) {
    hLocalMax.matlabCodegenIsDeleted = true;
  }

  if (!hhoughtrans.matlabCodegenIsDeleted) {
    hhoughtrans.matlabCodegenIsDeleted = true;
  }

  emxFree_boolean_T(&U0);
  c_emxFreeStruct_visioncodegen_H(&hhoughtrans);
}

/* End of code generation (findFourLines_v2.c) */
