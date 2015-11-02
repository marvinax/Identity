/*
 * AlignWorker_v2.c
 *
 * Code generation for function 'AlignWorker_v2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "AlignWorker_v2.h"
#include "mean.h"
#include "abs.h"
#include "projective2d.h"
#include "correlationSearch.h"
#include "imwarp.h"
#include "imref2d.h"
#include "fitgeotrans.h"
#include "getPowderAndQr_emxutil.h"
#include "round.h"
#include "sortLinesInOrder.h"
#include "calcIntersectionUsingTwoLines.h"
#include "patchCorr.h"
#include "patchOrientationCorection.h"
#include "pickOutAPossiblePairOfGroups.h"
#include "groupParallelLines.h"
#include "eliminateDuplicatedLines_new.h"
#include "findFourLines_v2.h"
#include "SystemCore.h"
#include "imgDetrend_v2.h"
#include "getRefMarkersAntiAlias.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static boolean_T AlignWorker_v2_matchingWhole(AlignWorker_v2 *obj, double
  edgeLength);
static void cast(const c_struct_T x[2], b_struct_T y[2]);
static int compute_nones(const emxArray_boolean_T *x, int n);
static void eml_li_find(const emxArray_boolean_T *x, emxArray_int32_T *y);

/* Function Definitions */
static boolean_T AlignWorker_v2_matchingWhole(AlignWorker_v2 *obj, double
  edgeLength)
{
  boolean_T successFlag;
  boolean_T b1;
  visioncodegen_Autothresholder hautoth;
  visioncodegen_Autothresholder *b_obj;
  int i46;
  boolean_T flag;
  emxArray_int32_T *r32;
  emxArray_uint8_T *c_obj;
  int loop_ub;
  emxArray_boolean_T *unusedU4;
  unsigned char tmpThres;
  double b_diff;
  int lines_size[2];
  e_struct_T lines_data[30];
  int b_lines_size[2];
  e_struct_T b_lines_data[30];
  int groupOrientation_size[1];
  double groupOrientation_data[10];
  emxArray_struct_T_10 group;
  emxArray_struct_T_10 b_group;
  int i;
  int groupPair_groupA_size[1];
  int groupPair_groupB_size[1];
  int nm1d2;
  e_struct_T group2ln_data[30];
  int group4ln_size_idx_0;
  e_struct_T group4ln_data[30];
  double intersectedPointsSet[16];
  int ixstart;
  int cnt_while;
  emxArray_uint8_T *warped;
  emxArray_real_T *winRange;
  emxArray_uint8_T *testCircle;
  emxArray_uint8_T *r33;
  emxArray_real_T *expl_temp;
  emxArray_real_T *b_expl_temp;
  emxArray_real_T *c_expl_temp;
  double b_intersectedPointsSet[16];
  double tform_loop_T[9];
  double dv18[2];
  double d_expl_temp;
  double t7_ImageSize[2];
  double e_expl_temp[2];
  double corrVal_diffCircleSize[2];
  double extend;
  double circleSizeNum[8];
  double pNew[16];
  static const double pTheory[16] = { 61.0, 61.0, 61.0, 260.0, 61.0, 459.0, 61.0,
    658.0, 260.0, 61.0, 260.0, 260.0, 260.0, 459.0, 260.0, 658.0 };

  int extraCnt;
  int32_T exitg1;
  int idxPt;
  double delta[4];
  int rc_data_size[2];
  unsigned char rc_data_data[2401];
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  double bestMatchedPoint_intPel_y;
  double bestMatchedPoint_intPel_x;
  double b_bestMatchedPoint_intPel_x[2];
  boolean_T exitg2;
  double b_pNew[16];
  double pFinal_lastLoop[16];
  double tmp_data[18];
  double bufferForCompiler_data[18];
  double dv19[16];
  b1 = false;

  /*  AlignWorker aligns a digitally captured patch to a imaginary square */
  /*  box */
  /*    ... */
  /*    First version Chau-Wai Wong, Dec. 2014 */
  /*    Improved version Feb.- ?, 2015 */
  /* dispVec_arr */
  /* matchingMode = -999; */
  /*  help to recover the true normalized image */
  /*  these variables won't be saved when objects are saved */
  /*              if nargin>0 */
  /*                  ; */
  /*              end */
  /*  prepare reference circle objects */
  /* load refMarkers_antiAlias */
  /*  half circle patch size */
  /*  half circle patch size */
  /* obj.refCircle = refCircle; */
  /*  % %         %% ---------------------------------------------------------------- */
  /*  % %         function [obj, successFlag] = carryOutMatching_GUI_2015_05_16(obj, ... */
  /*  % %                 rawImgPathAndName, designParams, refMarkers, figPos, cameraPosParams) */
  /*  % %  */
  /*  % %             obj.downsampleRatio = 1; */
  /*  % %             obj.figureSilentMode = 1; */
  /*  % %             obj.merelyShowFinalImage = 0; */
  /*  % %             obj.morePreciseMatchingFlag = 1; */
  /*  % %             obj.figPos = figPos; */
  /*  % %  */
  /*  % %             %obj.figureSilentMode = 0; % debug */
  /*  % %              */
  /*  % %             %obj = obj.loadRawImg(rawImgPathAndName); */
  /*  % %             obj = obj.loadRawImg_2015_05_16(rawImgPathAndName); % for test purpose */
  /*  % %              */
  /*  % %             % [CWW] Gaussian filtering to remove the powder which affects the */
  /*  % %             % morphological operations. Parameters need tuning. 4/15/2015 */
  /*  % %             sigma = 3; % even 1 works, but no filtering does not work */
  /*  % %             H = fspecial('Gaussian', 6*sigma+1, sigma); */
  /*  % %             obj.rawImgBlurred = imfilter(obj.rawImg, H, 'replicate'); */
  /*  % %              */
  /*  % %             [obj, successFlag] = obj.matchingWhole(designParams, refMarkers, 'getCameraPos', cameraPosParams); */
  /*  % %         end */
  /*  % %         function [obj] = initModule_calcCameraPos(obj, cameraPosParams, rangeTriPatch, cameraParamFn, flashOffset) */
  /*  % %             obj.calcCameraPosFlag = true; */
  /*  % %             obj.cameraPosParams = cameraPosParams; */
  /*  % %             obj.cameraParamFn = cameraParamFn; */
  /*  % %             obj.flashOffset = flashOffset; */
  /*  % %  */
  /*  % %             obj.triPatchOffset.x = rangeTriPatch.x(1) - 1; */
  /*  % %             obj.triPatchOffset.y = rangeTriPatch.y(1) - 1; */
  /*  % %         end */
  /*  debug */
  /*  note that as the development goes on, "rawImg" may not mean */
  /*  it is the raw image any more - it's just a name. */
  /*  in this case, "rawImgTrulyRaw" is image with its */
  /*  intensity normalized against the flash image, and */
  /*  "rawImg" is the normalized and detrended version. */
  /*  help to recover the true normalized image */
  /*  in this case, "rawImgTrulyRaw" is cropped raw image, and */
  /*  "rawImg" is the detrended version. */
  /*  carry out detrend */
  /*  Do not try to saturate the brightest 10% pixels. May lead to  */
  /*  very bad performance. 6/14/2015, CWW. */
  /*  1-254: to leave some room for floor and ceiling */
  /*  % %             [CWW] Gaussian filtering to remove the powder which affects the */
  /*  % %             morphological operations. Parameters need tuning. 4/15/2015 */
  /*  % %             sigma = 1; % even 1 works, but no filtering does not work */
  /*  % %             H = fspecial('Gaussian', 6*sigma+1, sigma); */
  /*  % %             obj.rawImgBlurred = imfilter(obj.rawImg, H, 'replicate'); */
  /*  it seems that Gaussian filtering reducing the noise due to powder is not needed any more, 6/13/2015, CWW. */
  /*  % %         function obj = carryOutMatching(obj, deviceName, pageNum, dbId, imgIdx, ... */
  /*  % %                 dbPathBase, inPath, outPath, ... */
  /*  % %                 designParams, refMarkers, ... */
  /*  % %                 downsampleRatio, figPos, figureSilentMode, merelyShowFinalImage, morePreciseMatchingFlag) */
  /*  % %              */
  /*  % %             obj.deviceName = deviceName; */
  /*  % %             obj.pageNum = pageNum; */
  /*  % %             obj.dbId = dbId; */
  /*  % %             obj.imgIdx = imgIdx; */
  /*  % %              */
  /*  % %             obj.dbPathBase = dbPathBase; */
  /*  % %             obj.inPath = inPath; */
  /*  % %             obj.outPath = outPath; */
  /*  % %              */
  /*  % %             obj.downsampleRatio = downsampleRatio; */
  /*  % %             obj.figureSilentMode = figureSilentMode; */
  /*  % %             obj.merelyShowFinalImage = merelyShowFinalImage; */
  /*  % %             obj.morePreciseMatchingFlag = morePreciseMatchingFlag; */
  /*  % %             obj.figPos = figPos; */
  /*  % %              */
  /*  % %             tifName = sprintf('%02d.tif', obj.imgIdx); */
  /*  % %             obj.rawImgPath    = [obj.inPath  tifName]; */
  /*  % %             obj.warpedImgPath = [obj.outPath tifName]; */
  /*  % %              */
  /*  % %             %obj.matchingMode = 0; */
  /*  % %              */
  /*  % %             disp(sprintf('\nImg#%d, db#%d, %s, page%d (real time matching)', obj.imgIdx, obj.dbId, obj.deviceName, obj.pageNum)); */
  /*  % %             obj = obj.loadRawImg(); */
  /*  % %             obj = obj.matchingWhole(designParams, refMarkers); */
  /*  % %         end */
  /*         %% ---------------------------------------------------------------- */
  /*  % %         function showRawImg(obj) */
  /*  % %             obj = obj.loadRawImg(); */
  /*  % %             figure; imshow(obj.rawImg); */
  /*  % %             title(sprintf('Img#%d, db#%d, %s, page%d', obj.imgIdx, obj.dbId, obj.deviceName, obj.pageNum)); */
  /*  % %         end */
  /*  % %         function showWarpedImg(obj) */
  /*  % %             if isempty(obj.warpedImg) */
  /*  % %                 disp('No warpedImg is available.') */
  /*  % %             else */
  /*  % %                 figure; imshow(obj.warpedImg); */
  /*  % %                 title(sprintf('Img#%d, db#%d, %s, page%d', obj.imgIdx, obj.dbId, obj.deviceName, obj.pageNum)); */
  /*  % %                 if obj.turbuVec(1)==0 && obj.turbuVec(2)==0 */
  /*  % %                     xlabel('Perturbation mode off. Faithful matching.'); */
  /*  % %                 else */
  /*  % %                     xlabel(sprintf('Perturbation vector = (%.1f, %.1f)', obj.turbuVec(1), obj.turbuVec(2))); */
  /*  % %                 end */
  /*  % %             end */
  /*  % %         end */
  /*  % %         function obj = loadRawImg(obj, varargin) */
  /*  % %             if isempty(obj.rawImg) */
  /*  % %                 if nargin==2 */
  /*  % %                     img_tmp = imread_exif(varargin{1}); */
  /*  % %                 else */
  /*  % %                     img_tmp = imread_exif([obj.dbPathBase obj.rawImgPath]); */
  /*  % %                 end */
  /*  % %                 if size(img_tmp, 3)>1 */
  /*  % %                     im_raw = rgb2gray(img_tmp); */
  /*  % %                 else */
  /*  % %                     im_raw = img_tmp; */
  /*  % %                 end */
  /*  % %                 obj.rawImgTrulyRaw = myImresize(im_raw, obj.downsampleRatio, 'bicubic'); */
  /*  % %                 obj.rawImgTrulyRawNormalizer = 1; */
  /*  % %                 % estimate the big trend first */
  /*  % %                 [~, scalerPlane, ~, ~, interestedMask] = imgDetrend_v2(obj.rawImgTrulyRaw, 64); */
  /*  % %                  */
  /*  % %                 % carry out detrend */
  /*  % %                 detrendedImg = double(obj.rawImgTrulyRaw) .* scalerPlane; */
  /*  % %                 tmp = detrendedImg(interestedMask); */
  /*  % %                  */
  /*  % %                 % this block obtains the two ends of the dynamic range the */
  /*  % %                 % lower end is the min, and the higher end at the 90% of */
  /*  % %                 % all data points to avoid some very bright outliers. An */
  /*  % %                 % O(N) implementation can be done using histogram, but sort */
  /*  % %                 % is used here for quick implementation. */
  /*  % %                 [tmp_sorted, ind] = sort(tmp, 'ascend'); % complexity N*log(N) */
  /*  % %                 minVal = tmp_sorted(1); */
  /*  % %                 maxVal = tmp_sorted(ind(round(length(tmp)*0.9))); */
  /*  % %  */
  /*  % %                 rescaled =  (detrendedImg-minVal) / (maxVal-minVal); */
  /*  % %                 obj.rawImg = uint8 ( rescaled*252 + 1 ) ; % 1-254: to leave some room for floor and ceiling */
  /*  % %                 %imshow(obj.rawImg) */
  /*  % %                  */
  /*  % %                 obj.rawImgDim = size(obj.rawImg); */
  /*  % %             end */
  /*  % %         end */
  /*  % %  */
  /*  % %         function obj = loadRawImg_2015_05_16(obj, varargin) */
  /*  % %             if isempty(obj.rawImg) */
  /*  % %                 if nargin==2 */
  /*  % %                     img_tmp = imread_exif(varargin{1}); */
  /*  % %                 else */
  /*  % %                     img_tmp = double(imread_exif([obj.dbPathBase obj.rawImgPath]))/255; */
  /*  % %                 end */
  /*  % %                 if size(img_tmp, 3)>1 */
  /*  % %                     im_raw = rgb2gray(double(img_tmp)/255); */
  /*  % %                 else */
  /*  % %                     im_raw = img_tmp; */
  /*  % %                 end */
  /*  % %                  */
  /*  % %                 fullFn = varargin{1}; */
  /*  % %                 % get the flash image for normalization */
  /*  % %                 pos = strfind(fullFn, '\'); */
  /*  % %                 if isempty(pos), pos = strfind(fullFn, '/'); end */
  /*  % %                 load([fullFn(1:pos(end)) 'flashImg.mat'], 'flashImg'); */
  /*  % %                 im_raw_normalized = im_raw ./ flashImg; */
  /*  % %                  */
  /*  % %                 obj.rawImgTrulyRawNormalizer = max(im_raw_normalized(:)) / 0.95; % help to recover the true normalized image  */
  /*  % %                 im_raw_normalized = im_raw_normalized / obj.rawImgTrulyRawNormalizer; */
  /*  % %                  */
  /*  % %                 obj.rawImgTrulyRaw = myImresize(im_raw_normalized, obj.downsampleRatio, 'bicubic'); */
  /*  % %                 %imshow(obj.rawImgTrulyRaw, []); */
  /*  % %                 % estimate the big trend first */
  /*  % %                 [~, scalerPlane, ~, ~, interestedMask] = imgDetrend_v2_thres(im_raw*255, 64); */
  /*  % %                  */
  /*  % %                 % carry out detrend */
  /*  % %                 detrendedImg = im_raw*255 .* scalerPlane; */
  /*  % %                 tmp = detrendedImg(interestedMask); */
  /*  % %                  */
  /*  % %                 % this block obtains the two ends of the dynamic range the */
  /*  % %                 % lower end is the min, and the higher end at the 90% of */
  /*  % %                 % all data points to avoid some very bright outliers. An */
  /*  % %                 % O(N) implementation can be done using histogram, but sort */
  /*  % %                 % is used here for quick implementation. */
  /*  % %                 [tmp_sorted, ind] = sort(tmp, 'ascend'); % complexity N*log(N) */
  /*  % %                 minVal = tmp_sorted(1); */
  /*  % %                 maxVal = tmp_sorted(ind(round(length(tmp)*0.9))); */
  /*  % %  */
  /*  % %                 rescaled =  (detrendedImg-minVal) / (maxVal-minVal); */
  /*  % %                 obj.rawImg = uint8 ( rescaled*252 + 1 ) ; % 1-254: to leave some room for floor and ceiling */
  /*  % %                 %imshow(obj.rawImg,[]) */
  /*  % %                  */
  /*  % %                 obj.rawImgDim = size(obj.rawImg); */
  /*  % %             end */
  /*  % %         end         */
  /*  % %         function obj = saveWarpedImg(obj, varargin) */
  /*  % %             if nargin==2 */
  /*  % %                 overwrite = varargin{1}; */
  /*  % %             else */
  /*  % %                 overwrite = []; */
  /*  % %             end */
  /*  % %              */
  /*  % %             fullFn = [obj.dbPathBase obj.warpedImgPath]; */
  /*  % %             if exist(fullFn, 'file')==2 */
  /*  % %                 if strcmpi(overwrite, 'overwrite') */
  /*  % %                     imwrite(obj.warpedImg, fullFn, 'Compression', 'lzw'); */
  /*  % %                     disp(fullFn); */
  /*  % %                     disp('overwrote!') */
  /*  % %                 else */
  /*  % %                     disp(fullFn); */
  /*  % %                     disp('exists. Skipped.'); */
  /*  % %                 end */
  /*  % %             else */
  /*  % %                 path = [obj.dbPathBase obj.outPath]; */
  /*  % %                 if exist(path, 'dir')~=7, mkdir(path); end */
  /*  % %                 imwrite(obj.warpedImg, fullFn, 'Compression', 'lzw'); */
  /*  % %             end */
  /*  % %         end */
  /*         %%  */
  /*  Perturbation mode off. faithful matching */
  /*  warped = imtransform(obj.rawImg, maketform('projective', tform.T), 'bicubic', 'XYScale', 1, ... */
  /*      'UData', [1 obj.rawImgDim(2)], 'VData', [1 obj.rawImgDim(1)],... */
  /*      'XData', [1 obj.warpedImgDim(2)], 'YData', [1 obj.warpedImgDim(1)],... */
  /*      'FillValues', 220); */
  /* pFinal_loop_verify = transformPointsInverse(tform_loop, pTheory')'; */
  /* obj.figIdx = obj.figIdx+1; hFig = figure(obj.figIdx); */
  /* if obj.figureSilentMode, set(hFig, 'visible','off'); end */
  /*      figure(1000+regionId); */
  /*      imshow(warped);  */
  /*      drawnow */
  /* set(hFig, 'Position', obj.figPos{obj.figIdx}); */
  /*  in pixel scale */
  /*  in pixel scale */
  /* obj.dispVec_arr(1:2,cnt_while) = dispVec(:); */
  /* obj = obj.loadRawImg(); */
  /*  warped = imtransform(obj.rawImg, maketform('projective', tform.T), 'bicubic', 'XYScale', 1, ... */
  /*      'UData', [1 obj.rawImgDim(2)], 'VData', [1 obj.rawImgDim(1)],... */
  /*      'XData', [1 obj.warpedImgDim(2)], 'YData', [1 obj.warpedImgDim(1)],... */
  /*      'FillValues', 220); */
  /* regionId == 3 */
  /*  obj.tform     = tform; */
  /*  obj.warpedImg = warped; */
  /*         %% coarse matching using hough transform, and precise refinement using correlation mask on corner markers */
  /*  % %         % calcCameraPosFlag = false; */
  /*  % %         % if nargin>=5 */
  /*  % %         %     if strcmpi('getCameraPos', varargin{1}) */
  /*  % %         if obj.calcCameraPosFlag */
  /*  % %             cameraPos_m  = obj.cameraPosParams.xy_pel; % in pixel */
  /*  % %             cameraHeight = obj.cameraPosParams.z_mm; % in mm */
  /*  % %             cameraParamFn = obj.cameraParamFn; */
  /*  % %             flashOffset = obj.flashOffset; */
  /*  % %         end */
  /*  % %         % end */
  /* isInList = @(x,list) sum(x==list)>0; */
  /*  fixed threshold works for reflective tape */
  /*  binarizationInitThres = 200; */
  /*  but now use adaptive threshold */
  /* binarizationInitThres = round ( 255 * (1-0.7*graythresh(obj.rawImg(obj.imgMask))) ) ; */
  /*  codegen */
  b_obj = &hautoth;
  hautoth.matlabCodegenIsDeleted = false;
  hautoth.isInitialized = false;
  hautoth.isReleased = false;
  hautoth.matlabCodegenIsDeleted = false;
  hautoth.matlabCodegenIsDeleted = false;
  hautoth.c_NoTuningBeforeLockingCodeGenE = true;

  /* System object Constructor function: vision.Autothresholder */
  b_obj->cSFunObject.S0_isInitialized = false;
  b_obj->cSFunObject.S1_isReleased = false;
  for (i46 = 0; i46 < 256; i46++) {
    b_obj->cSFunObject.P0_BIN_BOUNDARY_FIXPT_RTP[i46] = (unsigned char)i46;
  }

  b_obj->cSFunObject.P1_SCALE_FIXPT_RTP = 4210752;
  b_obj->cSFunObject.P2_UMIN_FIXPT_RTP = 0;
  b_obj->cSFunObject.P3_UMAX_FIXPT_RTP = MAX_uint8_T;
  if (hautoth.isInitialized && (!hautoth.isReleased)) {
    flag = true;
  } else {
    flag = false;
  }

  if (flag) {
    hautoth.TunablePropsChanged = true;
  }

  emxInit_int32_T(&r32, 1);
  b_emxInit_uint8_T(&c_obj, 1);
  hautoth.c_NoTuningBeforeLockingCodeGenE = false;
  eml_li_find(obj->imgMask, r32);
  i46 = c_obj->size[0];
  c_obj->size[0] = r32->size[0];
  emxEnsureCapacity((emxArray__common *)c_obj, i46, (int)sizeof(unsigned char));
  loop_ub = r32->size[0];
  for (i46 = 0; i46 < loop_ub; i46++) {
    c_obj->data[i46] = obj->rawImg->data[r32->data[i46] - 1];
  }

  emxFree_int32_T(&r32);
  emxInit_boolean_T(&unusedU4, 2);
  SystemCore_step(&hautoth, c_obj, unusedU4, &tmpThres);

  /* disp(['binarizationInitThres = ' int2str(binarizationInitThres)]); */
  successFlag = true;

  /*  it will be set to false when error occurs */
  b_diff = 0.0;
  findFourLines_v2(obj->rawImgBlurred, obj->imgMask, edgeLength, rt_roundd_snf
                   (255.0 * (1.0 - 0.7 * (double)tmpThres / 255.0)), &b_diff,
                   lines_data, lines_size);
  eliminateDuplicatedLines_new(lines_data, lines_size, b_lines_data,
    b_lines_size, &b_diff);

  /* disp(['lineCnt = ' int2str(lineCnt)]); */
  /*  obj.figIdx = figIdxOut; */
  /*  obj.figIdx = obj.figIdx+1; hFig = figure(obj.figIdx); */
  /*  if obj.figureSilentMode, set(hFig, 'visible','off'); end */
  /*  % %         if obj.debugMode == 1 */
  /*  % %             hFig = figure(20); */
  /*  % %             imshow(obj.rawImg), hold on */
  /*  % %             max_len = 0; */
  /*  % %             for k = 1:length(lines) */
  /*  % %                 xy = [lines(k).point1; lines(k).point2]; */
  /*  % %                 plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green'); */
  /*  % %  */
  /*  % %                 % Plot beginnings and ends of lines */
  /*  % %                 plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow'); */
  /*  % %                 plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red'); */
  /*  % %  */
  /*  % %                 % Determine the endpoints of the longest line segment */
  /*  % %                 len = norm(lines(k).point1 - lines(k).point2); */
  /*  % %                 if ( len > max_len) */
  /*  % %                     max_len = len; */
  /*  % %                     xy_long = xy; */
  /*  % %                 end */
  /*  % %             end */
  /*  % %             hold off; */
  /*  % %             set(hFig, 'position', [300 50 300 300]); */
  /*  % %             %set(hFig, 'Position', obj.figPos{obj.figIdx}); */
  /*  % %             title(sprintf('detected line groups overlaid on \ndetrended and contrast stretched image')); */
  /*  % %             drawnow */
  /*  % %         end */
  groupParallelLines(b_lines_data, b_lines_size, group.data, group.size,
                     groupOrientation_data, groupOrientation_size);
  loop_ub = group.size[0];
  emxFree_uint8_T(&c_obj);
  emxFree_boolean_T(&unusedU4);
  for (i46 = 0; i46 < loop_ub; i46++) {
    b_group.data[i46] = group.data[i46];
  }

  /* % This functions sorts the lines in ascending order in x-y space */
  /*   Chau-Wai Wong, 2/6/2015. */
  for (i = 0; i < group.size[0]; i++) {
    groupPair_groupA_size[0] = b_group.data[i].data.size[0];
    loop_ub = b_group.data[i].data.size[0];
    for (i46 = 0; i46 < loop_ub; i46++) {
      lines_data[i46] = b_group.data[i].data.data[i46];
    }

    c_sortLinesAccordingToIntersect(lines_data, groupPair_groupA_size,
      b_group.data[i].data.data, b_group.data[i].data.size);
  }

  pickOutAPossiblePairOfGroups(b_group.data, groupOrientation_data,
    groupOrientation_size, lines_data, groupPair_groupA_size, b_lines_data,
    groupPair_groupB_size, &flag);
  if (!flag) {
    /* obj = []; */
    successFlag = false;
  } else {
    /* % Get 8 points using a 2-line group and a 4-line group */
    /*   Chau-Wai Wong, Feb. 2015 */
    /*   Chau-Wai Wong, 6/13/2015 */
    if (groupPair_groupA_size[0] == 2) {
      nm1d2 = 2;
      for (i46 = 0; i46 < 2; i46++) {
        group2ln_data[i46] = lines_data[i46];
      }

      group4ln_size_idx_0 = groupPair_groupB_size[0];
      loop_ub = groupPair_groupB_size[0];
      for (i46 = 0; i46 < loop_ub; i46++) {
        group4ln_data[i46] = b_lines_data[i46];
      }
    } else {
      if (groupPair_groupA_size[0] == 4) {
        group4ln_size_idx_0 = 4;
        for (i46 = 0; i46 < 4; i46++) {
          group4ln_data[i46] = lines_data[i46];
        }

        nm1d2 = groupPair_groupB_size[0];
        loop_ub = groupPair_groupB_size[0];
        for (i46 = 0; i46 < loop_ub; i46++) {
          group2ln_data[i46] = b_lines_data[i46];
        }
      }
    }

    /*  (1)--(5) */
    /*   |    | */
    /*  (2)--(6) */
    /*   |    | */
    /*  (3)--(7) */
    /*   |    | */
    /*  (4)--(8) */
    memset(&intersectedPointsSet[0], 0, sizeof(double) << 4);
    for (i = 0; i < nm1d2; i++) {
      for (ixstart = 0; ixstart < group4ln_size_idx_0; ixstart++) {
        calcIntersectionUsingTwoLines(group2ln_data[i].point1, group2ln_data[i].
          point2, group4ln_data[ixstart].point1, group4ln_data[ixstart].point2, *
                                      (double (*)[2])&intersectedPointsSet
          [(ixstart + i * group4ln_size_idx_0) << 1]);
      }
    }

    for (i46 = 0; i46 < 16; i46++) {
      obj->pCoarse[i46] = intersectedPointsSet[i46];
    }

    /*  points in 1-indexed coordinate */
    /*         %% iterative fine tune with the help of corner markers */
    /*  this is the ground truth patch size, we will map the test patch to the ground truth patch grid */
    /*  Note that we use 1-index coordinates in this version, because the affine */
    /*  transform components in MATLAB seems use 1-indexed coordinates all the */
    /*  time. In the last version, 0-indexed coordinates was used (but only for */
    /*  this array, highly likely wrong). */
    /*  add the offset of the top-left corner point */
    for (i46 = 0; i46 < 2; i46++) {
      obj->warpedImgDim[i46] = 718.0 + -398.0 * (double)i46;
    }

    /* pCoarse */
    b_diff = 1.0E+10;
    cnt_while = 0;
    emxInit_uint8_T(&warped, 2);
    emxInit_real_T(&winRange, 2);
    emxInit_uint8_T(&testCircle, 2);
    emxInit_uint8_T(&r33, 2);
    emxInit_real_T(&expl_temp, 2);
    emxInit_real_T(&b_expl_temp, 2);
    emxInit_real_T(&c_expl_temp, 2);
    while ((b_diff > 0.0001) && (cnt_while < 2)) {
      cnt_while++;
      obj->figIdx = 0.0;
      for (i46 = 0; i46 < 2; i46++) {
        for (group4ln_size_idx_0 = 0; group4ln_size_idx_0 < 8;
             group4ln_size_idx_0++) {
          b_intersectedPointsSet[group4ln_size_idx_0 + (i46 << 3)] =
            intersectedPointsSet[i46 + (group4ln_size_idx_0 << 1)];
        }
      }

      fitgeotrans(b_intersectedPointsSet, tform_loop_T);

      /* pFinal_loop_verify = transformPointsInverse(tform_loop, pTheory')'; */
      /*      warped_old = imtransform(obj.rawImg, maketform('projective', tform_loop.T), 'bicubic', 'XYScale', 1, ... */
      /*          'UData', [1 obj.rawImgDim(2)   ], 'VData', [1 obj.rawImgDim(1)   ],... */
      /*          'XData', [1 obj.warpedImgDim(2)], 'YData', [1 obj.warpedImgDim(1)],... */
      /*          'FillValues', 220); % Fill with gray */
      if (!b1) {
        for (i46 = 0; i46 < 2; i46++) {
          dv18[i46] = 718.0 + -398.0 * (double)i46;
        }

        b1 = true;
      }

      imref2d_imref2d(dv18, corrVal_diffCircleSize, e_expl_temp, t7_ImageSize,
                      &b_diff, &d_expl_temp);
      imwarp(obj->rawImg, tform_loop_T, t7_ImageSize, r33);
      i46 = warped->size[0] * warped->size[1];
      warped->size[0] = r33->size[0];
      warped->size[1] = r33->size[1];
      emxEnsureCapacity((emxArray__common *)warped, i46, (int)sizeof(unsigned
        char));
      loop_ub = r33->size[0] * r33->size[1];
      for (i46 = 0; i46 < loop_ub; i46++) {
        warped->data[i46] = r33->data[i46];
      }

      /*  % %             %obj.figIdx = obj.figIdx+1; hFig = figure(obj.figIdx); */
      /*  % %             %if obj.figureSilentMode, set(hFig, 'visible','off'); end */
      /*  % %             figure(1000); */
      /*  % %             imshow(warped); */
      /*  % %             drawnow */
      /* set(hFig, 'Position', obj.figPos{obj.figIdx}); */
      extend = 10.0;

      /*  in pixel scale */
      /*  in pixel scale */
      correlationSearch(warped, pTheory, obj->refCircle_small.data.data,
                        obj->refCircle_small.data.size,
                        obj->refCircle_small.halfCirclePatchSize,
                        obj->refCircle_large.data.data,
                        obj->refCircle_large.data.size,
                        obj->refCircle_large.halfCirclePatchSize, pNew,
                        circleSizeNum, corrVal_diffCircleSize);
      extraCnt = 0;
      do {
        exitg1 = 0;
        b_diff = circleSizeNum[0];
        for (group4ln_size_idx_0 = 0; group4ln_size_idx_0 < 7;
             group4ln_size_idx_0++) {
          b_diff += circleSizeNum[group4ln_size_idx_0 + 1];
        }

        if ((b_diff != 10.0) && (extraCnt < 2)) {
          extraCnt++;
          extend += 10.0;

          /* % This subroutine carries out cross-correlation search at  */
          /*   integer pixel level and then sub-pixel level. */
          /*   Chau-Wai Wong, Mar. 2015 */
          for (idxPt = 0; idxPt < 8; idxPt++) {
            /*  stage 1 - integer pixel search */
            for (i = 0; i < 2; i++) {
              corrVal_diffCircleSize[i] = 0.0;
            }

            for (i = 0; i < 2; i++) {
              if (1 + i == 1) {
                rc_data_size[0] = obj->refCircle_small.data.size[0];
                rc_data_size[1] = obj->refCircle_small.data.size[1];
                loop_ub = obj->refCircle_small.data.size[0] *
                  obj->refCircle_small.data.size[1];
                for (i46 = 0; i46 < loop_ub; i46++) {
                  rc_data_data[i46] = obj->refCircle_small.data.data[i46];
                }

                b_diff = obj->refCircle_small.halfCirclePatchSize;
              } else {
                rc_data_size[0] = obj->refCircle_large.data.size[0];
                rc_data_size[1] = obj->refCircle_large.data.size[1];
                loop_ub = obj->refCircle_large.data.size[0] *
                  obj->refCircle_large.data.size[1];
                for (i46 = 0; i46 < loop_ub; i46++) {
                  rc_data_data[i46] = obj->refCircle_large.data.data[i46];
                }

                b_diff = obj->refCircle_large.halfCirclePatchSize;
              }

              b_diff += extend;
              if (rtIsNaN(-b_diff) || rtIsNaN(b_diff)) {
                ixstart = 0;
                d_expl_temp = rtNaN;
                apnd = b_diff;
              } else if (b_diff < -b_diff) {
                ixstart = -1;
                d_expl_temp = -b_diff;
                apnd = b_diff;
              } else if (rtIsInf(-b_diff) || rtIsInf(b_diff)) {
                ixstart = 0;
                d_expl_temp = rtNaN;
                apnd = b_diff;
              } else {
                d_expl_temp = -b_diff;
                ndbl = floor((b_diff - (-b_diff)) + 0.5);
                apnd = -b_diff + ndbl;
                cdiff = apnd - b_diff;
                absa = fabs(-b_diff);
                absb = fabs(b_diff);
                if ((absa >= absb) || rtIsNaN(absb)) {
                  absb = absa;
                }

                if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                  ndbl++;
                  apnd = b_diff;
                } else if (cdiff > 0.0) {
                  apnd = -b_diff + (ndbl - 1.0);
                } else {
                  ndbl++;
                }

                if (ndbl >= 0.0) {
                  ixstart = (int)ndbl - 1;
                } else {
                  ixstart = -1;
                }
              }

              i46 = winRange->size[0] * winRange->size[1];
              winRange->size[0] = 1;
              winRange->size[1] = ixstart + 1;
              emxEnsureCapacity((emxArray__common *)winRange, i46, (int)sizeof
                                (double));
              if (ixstart + 1 > 0) {
                winRange->data[0] = d_expl_temp;
                if (ixstart + 1 > 1) {
                  winRange->data[ixstart] = apnd;
                  nm1d2 = ixstart / 2;
                  for (group4ln_size_idx_0 = 1; group4ln_size_idx_0 < nm1d2;
                       group4ln_size_idx_0++) {
                    winRange->data[group4ln_size_idx_0] = d_expl_temp + (double)
                      group4ln_size_idx_0;
                    winRange->data[ixstart - group4ln_size_idx_0] = apnd -
                      (double)group4ln_size_idx_0;
                  }

                  if (nm1d2 << 1 == ixstart) {
                    winRange->data[nm1d2] = (d_expl_temp + apnd) / 2.0;
                  } else {
                    winRange->data[nm1d2] = d_expl_temp + (double)nm1d2;
                    winRange->data[nm1d2 + 1] = apnd - (double)nm1d2;
                  }
                }
              }

              i46 = testCircle->size[0] * testCircle->size[1];
              testCircle->size[0] = winRange->size[1];
              testCircle->size[1] = winRange->size[1];
              emxEnsureCapacity((emxArray__common *)testCircle, i46, (int)sizeof
                                (unsigned char));
              loop_ub = winRange->size[1];
              for (i46 = 0; i46 < loop_ub; i46++) {
                ixstart = winRange->size[1];
                for (group4ln_size_idx_0 = 0; group4ln_size_idx_0 < ixstart;
                     group4ln_size_idx_0++) {
                  testCircle->data[group4ln_size_idx_0 + testCircle->size[0] *
                    i46] = warped->data[((int)(pTheory[1 + (idxPt << 1)] +
                    winRange->data[winRange->size[0] * group4ln_size_idx_0]) +
                    warped->size[0] * ((int)(pTheory[idxPt << 1] +
                    winRange->data[winRange->size[0] * i46]) - 1)) - 1];
                }
              }

              /*  integer search due to imprecise boundary positions obtained */
              /*  figure(689); imshow(imgBg); drawnow */
              b_patchCorr(testCircle, rc_data_data, rc_data_size, extend,
                          &corrVal_diffCircleSize[i], &bestMatchedPoint_intPel_x,
                          &bestMatchedPoint_intPel_y, expl_temp, b_expl_temp,
                          c_expl_temp);
              b_bestMatchedPoint_intPel_x[0] = bestMatchedPoint_intPel_x;
              b_bestMatchedPoint_intPel_x[1] = bestMatchedPoint_intPel_y;
              for (i46 = 0; i46 < 2; i46++) {
                delta[i46 + (i << 1)] = b_bestMatchedPoint_intPel_x[i46];
              }
            }

            /* circleSizeIdx = []; */
            ixstart = 1;
            b_diff = corrVal_diffCircleSize[0];
            nm1d2 = 1;
            if (rtIsNaN(corrVal_diffCircleSize[0])) {
              group4ln_size_idx_0 = 2;
              exitg2 = false;
              while ((!exitg2) && (group4ln_size_idx_0 < 3)) {
                ixstart = 2;
                if (!rtIsNaN(corrVal_diffCircleSize[1])) {
                  b_diff = corrVal_diffCircleSize[1];
                  nm1d2 = 2;
                  exitg2 = true;
                } else {
                  group4ln_size_idx_0 = 3;
                }
              }
            }

            if ((ixstart < 2) && (corrVal_diffCircleSize[1] > b_diff)) {
              nm1d2 = 2;
            }

            /*  stage 2 - sub-pixel search */
            for (i46 = 0; i46 < 2; i46++) {
              pNew[i46 + (idxPt << 1)] = pTheory[i46 + (idxPt << 1)] + delta[i46
                + ((nm1d2 - 1) << 1)];
            }

            circleSizeNum[idxPt] = nm1d2;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      memcpy(&b_pNew[0], &pNew[0], sizeof(double) << 4);
      patchOrientationCorection(circleSizeNum, b_pNew, pNew);
      memcpy(&pFinal_lastLoop[0], &intersectedPointsSet[0], sizeof(double) << 4);
      for (i46 = 0; i46 < 2; i46++) {
        for (group4ln_size_idx_0 = 0; group4ln_size_idx_0 < 8;
             group4ln_size_idx_0++) {
          b_intersectedPointsSet[group4ln_size_idx_0 + (i46 << 3)] = pNew[i46 +
            (group4ln_size_idx_0 << 1)];
        }
      }

      d_projective2d_transformPointsI(tform_loop_T, b_intersectedPointsSet,
        tmp_data, lines_size);
      loop_ub = lines_size[0];
      for (i46 = 0; i46 < loop_ub; i46++) {
        for (group4ln_size_idx_0 = 0; group4ln_size_idx_0 < 2;
             group4ln_size_idx_0++) {
          bufferForCompiler_data[group4ln_size_idx_0 + (i46 << 1)] =
            tmp_data[i46 + lines_size[0] * group4ln_size_idx_0];
        }
      }

      for (i46 = 0; i46 < 8; i46++) {
        for (group4ln_size_idx_0 = 0; group4ln_size_idx_0 < 2;
             group4ln_size_idx_0++) {
          intersectedPointsSet[group4ln_size_idx_0 + (i46 << 1)] =
            bufferForCompiler_data[group4ln_size_idx_0 + (i46 << 1)];
        }
      }

      for (i46 = 0; i46 < 16; i46++) {
        b_intersectedPointsSet[i46] = intersectedPointsSet[i46] -
          pFinal_lastLoop[i46];
      }

      d_abs(b_intersectedPointsSet, dv19);
      b_diff = c_mean(dv19);

      /* obj.dispVec_arr(1:2,cnt_while) = dispVec(:); */
    }

    emxFree_real_T(&c_expl_temp);
    emxFree_real_T(&b_expl_temp);
    emxFree_real_T(&expl_temp);
    emxFree_uint8_T(&r33);
    emxFree_uint8_T(&testCircle);
    emxFree_real_T(&winRange);
    emxFree_uint8_T(&warped);
    for (i46 = 0; i46 < 16; i46++) {
      obj->pPrecise[i46] = intersectedPointsSet[i46];
      obj->pTheory[i46] = pTheory[i46];
    }

    /*         %% Estimate 3D transform and camera position */
    /*  Test code, May 2015 */
    /*  % %         if ~obj.calcCameraPosFlag,  return; end */
    /*  % %  */
    /*  % %         load(cameraParamFn); */
    /*  % %         offset = [obj.triPatchOffset.x obj.triPatchOffset.y]; */
    /*  % %         imagePoints = pFinal_loop' + ones(8,1)*offset; */
    /*  % %         worldPoints = pTheory' / 300 * 25.4; % in millimeter */
    /*  % %         [R, t] = extrinsics(imagePoints, worldPoints, cameraParams); */
    /*  % %         %disp('camera location in world:') */
    /*  % %         %disp(round(-t,2)) */
    /*  % %  */
    /*  % %         % manually obtained camera position */
    /*  % %         % cameraPos_m = [1285 1595]; % in pixel */
    /*  % %         % cameraHeight = 215.9; % in mm */
    /*  % %         wp_cameraPos_m = pointsToWorld(cameraParams, R, t, cameraPos_m); */
    /*  % %         cameraPos_hybrid = [wp_cameraPos_m cameraHeight]; */
    /*  % %         lightPos_hybrid = cameraPos_hybrid + [flashOffset(:); 0]';  % offset from the camera to lens for iPhone 6, in mm */
    /*  % %         obj.ltPos = lightPos_hybrid; */
    /*  % %  */
    /*  % %         PAPER_PATCH = 1; */
    /*  % %         paperPatch_wpts = worldPoints(obj.REGION_IDX{PAPER_PATCH},:); */
    /*  % %         paperPatch_start = paperPatch_wpts(1,1); */
    /*  % %         paperPatch_end   = paperPatch_wpts(3,1); */
    /*  % %         paperPatch_range = linspace(paperPatch_start, paperPatch_end, 200); */
    /*  % %         [x_ticks, y_ticks] = meshgrid(paperPatch_range, paperPatch_range); */
    /*  % %         paperPatch_allPts = [x_ticks(:) y_ticks(:) zeros(200*200,1)]'; */
    /*  % %         ltVector = lightPos_hybrid' * ones(1,200*200) - paperPatch_allPts; */
    /*  % %         obj.ltVector   = ltVector; */
    /*  % %  */
    /*  % %         % for information */
    /*  % %         ltAngle = atan2(sqrt(ltVector(1,:).^2+ltVector(2,:).^2), ltVector(3,:)) / pi * 90; */
    /*  % %         ltAngle = reshape(ltAngle, size(x_ticks)); */
    /*  % %         obj.ltAngle    = ltAngle; */
  }

  if (!hautoth.matlabCodegenIsDeleted) {
    hautoth.matlabCodegenIsDeleted = true;
  }

  return successFlag;
}

static void cast(const c_struct_T x[2], b_struct_T y[2])
{
  int j;
  int n;
  int b_j;
  for (j = 0; j < 2; j++) {
    y[j].data.size[0] = x[j].data->size[0];
    y[j].data.size[1] = x[j].data->size[1];
    n = x[j].data->size[0] * x[j].data->size[1];
    for (b_j = 0; b_j < n; b_j++) {
      y[j].data.data[b_j] = x[j].data->data[b_j];
    }
  }
}

static int compute_nones(const emxArray_boolean_T *x, int n)
{
  int k;
  int i;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x->data[i - 1]) {
      k++;
    }
  }

  return k;
}

static void eml_li_find(const emxArray_boolean_T *x, emxArray_int32_T *y)
{
  int n;
  int k;
  int i;
  n = x->size[0] * x->size[1];
  k = compute_nones(x, n);
  i = y->size[0];
  y->size[0] = k;
  emxEnsureCapacity((emxArray__common *)y, i, (int)sizeof(int));
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x->data[i - 1]) {
      y->data[k] = i;
      k++;
    }
  }
}

void AlignWorker_v2_AlignWorker_v2(AlignWorker_v2 *obj)
{
  int i1;
  static const signed char iv0[12] = { 1, 2, 6, 5, 2, 3, 7, 6, 3, 4, 8, 7 };

  c_struct_T rv0[2];
  b_struct_T refMarkers[2];
  int loop_ub;
  unsigned char t9_data_data[2401];
  unsigned char t8_data_data[2401];
  i1 = obj->rawImgTrulyRaw->size[0] * obj->rawImgTrulyRaw->size[1];
  obj->rawImgTrulyRaw->size[0] = 0;
  obj->rawImgTrulyRaw->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)obj->rawImgTrulyRaw, i1, (int)sizeof
                    (double));
  i1 = obj->rawImg->size[0] * obj->rawImg->size[1];
  obj->rawImg->size[0] = 0;
  obj->rawImg->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)obj->rawImg, i1, (int)sizeof(unsigned
    char));
  i1 = obj->imgMask->size[0] * obj->imgMask->size[1];
  obj->imgMask->size[0] = 0;
  obj->imgMask->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)obj->imgMask, i1, (int)sizeof(boolean_T));
  i1 = obj->rawImgBlurred->size[0] * obj->rawImgBlurred->size[1];
  obj->rawImgBlurred->size[0] = 0;
  obj->rawImgBlurred->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)obj->rawImgBlurred, i1, (int)sizeof
                    (unsigned char));
  i1 = obj->warpedRegion2->size[0] * obj->warpedRegion2->size[1];
  obj->warpedRegion2->size[0] = 0;
  obj->warpedRegion2->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)obj->warpedRegion2, i1, (int)sizeof
                    (double));
  i1 = obj->warpedRegion3->size[0] * obj->warpedRegion3->size[1];
  obj->warpedRegion3->size[0] = 0;
  obj->warpedRegion3->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)obj->warpedRegion3, i1, (int)sizeof
                    (double));
  for (i1 = 0; i1 < 2; i1++) {
    obj->warpedImgDim[i1] = 0.0;
  }

  for (i1 = 0; i1 < 16; i1++) {
    obj->pTheory[i1] = 0.0;
  }

  for (i1 = 0; i1 < 16; i1++) {
    obj->pPrecise[i1] = 0.0;
  }

  obj->calcCameraPosFlag = false;
  obj->figIdx = 0.0;
  obj->regionCnt = 3.0;
  for (i1 = 0; i1 < 12; i1++) {
    obj->REGION_IDX[i1] = iv0[i1];
  }

  emxInitMatrix_struct_T(rv0);
  getRefMarkersAntiAlias(rv0);
  cast(rv0, refMarkers);
  loop_ub = refMarkers[0].data.size[0] * refMarkers[0].data.size[1];
  emxFreeMatrix_struct_T(rv0);
  for (i1 = 0; i1 < loop_ub; i1++) {
    t9_data_data[i1] = refMarkers[0].data.data[i1];
  }

  obj->refCircle_small.data.size[0] = refMarkers[0].data.size[0];
  obj->refCircle_small.data.size[1] = refMarkers[0].data.size[1];
  loop_ub = refMarkers[0].data.size[0] * refMarkers[0].data.size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    obj->refCircle_small.data.data[i1] = t9_data_data[i1];
  }

  obj->refCircle_small.halfCirclePatchSize = ((double)refMarkers[0].data.size[0]
    - 1.0) / 2.0;
  loop_ub = refMarkers[1].data.size[0] * refMarkers[1].data.size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    t8_data_data[i1] = refMarkers[1].data.data[i1];
  }

  obj->refCircle_large.data.size[0] = refMarkers[1].data.size[0];
  obj->refCircle_large.data.size[1] = refMarkers[1].data.size[1];
  loop_ub = refMarkers[1].data.size[0] * refMarkers[1].data.size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    obj->refCircle_large.data.data[i1] = t8_data_data[i1];
  }

  obj->refCircle_large.halfCirclePatchSize = ((double)refMarkers[1].data.size[0]
    - 1.0) / 2.0;
}

boolean_T c_AlignWorker_v2_carryOutMatchi(AlignWorker_v2 *obj, const
  emxArray_real_T *triPatch, const emxArray_boolean_T *triPatchMask, double
  edgeLength)
{
  int unnamed_idx_0;
  int loop_ub;
  emxArray_real_T *b_triPatch;
  emxArray_real_T *detrendedImg;
  emxArray_real_T *unusedU0;
  emxArray_real_T *unusedU1;
  double unusedU2;
  emxArray_real_T *tmp;
  emxArray_int32_T *r31;
  int ixstart;
  int b_unnamed_idx_0;
  double mtmp;
  boolean_T exitg2;
  boolean_T exitg1;
  double d1;
  unsigned char u2;
  unnamed_idx_0 = obj->rawImgTrulyRaw->size[0] * obj->rawImgTrulyRaw->size[1];
  obj->rawImgTrulyRaw->size[0] = triPatch->size[0];
  obj->rawImgTrulyRaw->size[1] = triPatch->size[1];
  emxEnsureCapacity((emxArray__common *)obj->rawImgTrulyRaw, unnamed_idx_0, (int)
                    sizeof(double));
  loop_ub = triPatch->size[0] * triPatch->size[1];
  for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub; unnamed_idx_0++) {
    obj->rawImgTrulyRaw->data[unnamed_idx_0] = triPatch->data[unnamed_idx_0] *
      255.0;
  }

  emxInit_real_T(&b_triPatch, 2);
  b_round(obj->rawImgTrulyRaw);
  unnamed_idx_0 = b_triPatch->size[0] * b_triPatch->size[1];
  b_triPatch->size[0] = triPatch->size[0];
  b_triPatch->size[1] = triPatch->size[1];
  emxEnsureCapacity((emxArray__common *)b_triPatch, unnamed_idx_0, (int)sizeof
                    (double));
  loop_ub = triPatch->size[0] * triPatch->size[1];
  for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub; unnamed_idx_0++) {
    b_triPatch->data[unnamed_idx_0] = triPatch->data[unnamed_idx_0] * 255.0;
  }

  emxInit_real_T(&detrendedImg, 2);
  emxInit_real_T(&unusedU0, 2);
  emxInit_real_T(&unusedU1, 2);
  imgDetrend_v2(b_triPatch, unusedU0, detrendedImg, unusedU1, &unusedU2);
  unnamed_idx_0 = detrendedImg->size[0] * detrendedImg->size[1];
  detrendedImg->size[0] = triPatch->size[0];
  detrendedImg->size[1] = triPatch->size[1];
  emxEnsureCapacity((emxArray__common *)detrendedImg, unnamed_idx_0, (int)sizeof
                    (double));
  loop_ub = triPatch->size[0] * triPatch->size[1];
  emxFree_real_T(&b_triPatch);
  emxFree_real_T(&unusedU1);
  emxFree_real_T(&unusedU0);
  for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub; unnamed_idx_0++) {
    detrendedImg->data[unnamed_idx_0] *= triPatch->data[unnamed_idx_0] * 255.0;
  }

  b_emxInit_real_T(&tmp, 1);
  emxInit_int32_T(&r31, 1);
  eml_li_find(triPatchMask, r31);
  unnamed_idx_0 = tmp->size[0];
  tmp->size[0] = r31->size[0];
  emxEnsureCapacity((emxArray__common *)tmp, unnamed_idx_0, (int)sizeof(double));
  loop_ub = r31->size[0];
  for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub; unnamed_idx_0++) {
    tmp->data[unnamed_idx_0] = detrendedImg->data[r31->data[unnamed_idx_0] - 1];
  }

  ixstart = 1;
  b_unnamed_idx_0 = r31->size[0];
  mtmp = tmp->data[0];
  unnamed_idx_0 = r31->size[0];
  if (unnamed_idx_0 > 1) {
    if (rtIsNaN(tmp->data[0])) {
      loop_ub = 2;
      exitg2 = false;
      while ((!exitg2) && (loop_ub <= b_unnamed_idx_0)) {
        ixstart = loop_ub;
        if (!rtIsNaN(tmp->data[loop_ub - 1])) {
          mtmp = tmp->data[loop_ub - 1];
          exitg2 = true;
        } else {
          loop_ub++;
        }
      }
    }

    unnamed_idx_0 = r31->size[0];
    if (ixstart < unnamed_idx_0) {
      while (ixstart + 1 <= b_unnamed_idx_0) {
        if (tmp->data[ixstart] < mtmp) {
          mtmp = tmp->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  b_unnamed_idx_0 = r31->size[0];
  unusedU2 = tmp->data[0];
  unnamed_idx_0 = r31->size[0];
  if (unnamed_idx_0 > 1) {
    if (rtIsNaN(tmp->data[0])) {
      loop_ub = 2;
      exitg1 = false;
      while ((!exitg1) && (loop_ub <= b_unnamed_idx_0)) {
        ixstart = loop_ub;
        if (!rtIsNaN(tmp->data[loop_ub - 1])) {
          unusedU2 = tmp->data[loop_ub - 1];
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }
    }

    unnamed_idx_0 = r31->size[0];
    if (ixstart < unnamed_idx_0) {
      while (ixstart + 1 <= b_unnamed_idx_0) {
        if (tmp->data[ixstart] > unusedU2) {
          unusedU2 = tmp->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  emxFree_int32_T(&r31);
  emxFree_real_T(&tmp);
  unusedU2 -= mtmp;
  unnamed_idx_0 = obj->rawImg->size[0] * obj->rawImg->size[1];
  obj->rawImg->size[0] = detrendedImg->size[0];
  obj->rawImg->size[1] = detrendedImg->size[1];
  emxEnsureCapacity((emxArray__common *)obj->rawImg, unnamed_idx_0, (int)sizeof
                    (unsigned char));
  loop_ub = detrendedImg->size[0] * detrendedImg->size[1];
  for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub; unnamed_idx_0++) {
    d1 = rt_roundd_snf((detrendedImg->data[unnamed_idx_0] - mtmp) / unusedU2 *
                       252.0 + 1.0);
    if (d1 < 256.0) {
      if (d1 >= 0.0) {
        u2 = (unsigned char)d1;
      } else {
        u2 = 0;
      }
    } else if (d1 >= 256.0) {
      u2 = MAX_uint8_T;
    } else {
      u2 = 0;
    }

    obj->rawImg->data[unnamed_idx_0] = u2;
  }

  emxFree_real_T(&detrendedImg);
  for (unnamed_idx_0 = 0; unnamed_idx_0 < 2; unnamed_idx_0++) {
    obj->rawImgDim[unnamed_idx_0] = obj->rawImg->size[unnamed_idx_0];
  }

  unnamed_idx_0 = obj->rawImgBlurred->size[0] * obj->rawImgBlurred->size[1];
  obj->rawImgBlurred->size[0] = obj->rawImg->size[0];
  obj->rawImgBlurred->size[1] = obj->rawImg->size[1];
  emxEnsureCapacity((emxArray__common *)obj->rawImgBlurred, unnamed_idx_0, (int)
                    sizeof(unsigned char));
  loop_ub = obj->rawImg->size[0] * obj->rawImg->size[1];
  for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub; unnamed_idx_0++) {
    obj->rawImgBlurred->data[unnamed_idx_0] = obj->rawImg->data[unnamed_idx_0];
  }

  unnamed_idx_0 = obj->imgMask->size[0] * obj->imgMask->size[1];
  obj->imgMask->size[0] = triPatchMask->size[0];
  obj->imgMask->size[1] = triPatchMask->size[1];
  emxEnsureCapacity((emxArray__common *)obj->imgMask, unnamed_idx_0, (int)sizeof
                    (boolean_T));
  loop_ub = triPatchMask->size[0] * triPatchMask->size[1];
  for (unnamed_idx_0 = 0; unnamed_idx_0 < loop_ub; unnamed_idx_0++) {
    obj->imgMask->data[unnamed_idx_0] = triPatchMask->data[unnamed_idx_0];
  }

  return AlignWorker_v2_matchingWhole(obj, edgeLength);
}

void c_AlignWorker_v2_matchingIndivi(AlignWorker_v2 *obj)
{
  double pTheory[8];
  double pFinal_loop[8];
  int i51;
  int i52;
  double b_diff;
  int cnt_while;
  emxArray_uint8_T *warped;
  double b_pFinal_loop[8];
  double b_pTheory[8];
  double tform_T[9];
  double expl_temp;
  double t3_ImageSize[2];
  double b_expl_temp[2];
  double c_expl_temp[2];
  double circleSizeNum[4];
  double pFinal_lastLoop[8];
  int tmp_size[2];
  double tmp_data[10];
  int loop_ub;
  double bufferForMatlabCoder_data[10];
  double dv21[8];
  emxArray_real_T *warpedRegionTmp;
  for (i51 = 0; i51 < 4; i51++) {
    for (i52 = 0; i52 < 2; i52++) {
      pTheory[i52 + (i51 << 1)] = obj->pTheory[i52 + (((int)obj->REGION_IDX[8 +
        i51] - 1) << 1)];
      pFinal_loop[i52 + (i51 << 1)] = obj->pPrecise[i52 + (((int)obj->
        REGION_IDX[8 + i51] - 1) << 1)];
    }
  }

  b_diff = 1.0E+10;
  cnt_while = 0;
  emxInit_uint8_T(&warped, 2);
  while ((b_diff > 0.0001) && (cnt_while < 4)) {
    cnt_while++;
    for (i51 = 0; i51 < 2; i51++) {
      for (i52 = 0; i52 < 4; i52++) {
        b_pFinal_loop[i52 + (i51 << 2)] = pFinal_loop[i51 + (i52 << 1)];
        b_pTheory[i52 + (i51 << 2)] = pTheory[i51 + (i52 << 1)];
      }
    }

    b_fitgeotrans(b_pFinal_loop, b_pTheory, tform_T);
    imref2d_imref2d(obj->warpedImgDim, c_expl_temp, b_expl_temp, t3_ImageSize,
                    &b_diff, &expl_temp);
    imwarp(obj->rawImg, tform_T, t3_ImageSize, warped);
    b_correlationSearch(warped, pTheory, obj->refCircle_small.data.data,
                        obj->refCircle_small.data.size,
                        obj->refCircle_small.halfCirclePatchSize,
                        obj->refCircle_large.data.data,
                        obj->refCircle_large.data.size,
                        obj->refCircle_large.halfCirclePatchSize, b_pFinal_loop,
                        circleSizeNum, c_expl_temp);
    memcpy(&pFinal_lastLoop[0], &pFinal_loop[0], sizeof(double) << 3);
    for (i51 = 0; i51 < 2; i51++) {
      for (i52 = 0; i52 < 4; i52++) {
        b_pTheory[i52 + (i51 << 2)] = b_pFinal_loop[i51 + (i52 << 1)];
      }
    }

    e_projective2d_transformPointsI(tform_T, b_pTheory, tmp_data, tmp_size);
    loop_ub = tmp_size[0];
    for (i51 = 0; i51 < loop_ub; i51++) {
      for (i52 = 0; i52 < 2; i52++) {
        bufferForMatlabCoder_data[i52 + (i51 << 1)] = tmp_data[i51 + tmp_size[0]
          * i52];
      }
    }

    for (i51 = 0; i51 < 4; i51++) {
      for (i52 = 0; i52 < 2; i52++) {
        pFinal_loop[i52 + (i51 << 1)] = bufferForMatlabCoder_data[i52 + (i51 <<
          1)];
      }
    }

    for (i51 = 0; i51 < 8; i51++) {
      b_pFinal_loop[i51] = pFinal_loop[i51] - pFinal_lastLoop[i51];
    }

    c_abs(b_pFinal_loop, dv21);
    b_diff = d_mean(dv21);
  }

  emxFree_uint8_T(&warped);
  for (i51 = 0; i51 < 2; i51++) {
    for (i52 = 0; i52 < 4; i52++) {
      b_pFinal_loop[i52 + (i51 << 2)] = pFinal_loop[i51 + (i52 << 1)];
      b_pTheory[i52 + (i51 << 2)] = pTheory[i51 + (i52 << 1)];
    }
  }

  emxInit_real_T(&warpedRegionTmp, 2);
  b_fitgeotrans(b_pFinal_loop, b_pTheory, tform_T);
  imref2d_imref2d(obj->warpedImgDim, c_expl_temp, b_expl_temp, t3_ImageSize,
                  &b_diff, &expl_temp);
  c_imwarp(obj->rawImgTrulyRaw, tform_T, t3_ImageSize, warpedRegionTmp);
  i51 = obj->warpedRegion3->size[0] * obj->warpedRegion3->size[1];
  obj->warpedRegion3->size[0] = warpedRegionTmp->size[0];
  obj->warpedRegion3->size[1] = warpedRegionTmp->size[1];
  emxEnsureCapacity((emxArray__common *)obj->warpedRegion3, i51, (int)sizeof
                    (double));
  loop_ub = warpedRegionTmp->size[0] * warpedRegionTmp->size[1];
  for (i51 = 0; i51 < loop_ub; i51++) {
    obj->warpedRegion3->data[i51] = warpedRegionTmp->data[i51];
  }

  emxFree_real_T(&warpedRegionTmp);
}

void d_AlignWorker_v2_matchingIndivi(AlignWorker_v2 *obj)
{
  double pTheory[8];
  double pFinal_loop[8];
  int i61;
  int i62;
  double b_diff;
  int cnt_while;
  emxArray_uint8_T *warped;
  double b_pFinal_loop[8];
  double b_pTheory[8];
  double tform_T[9];
  double expl_temp;
  double t2_ImageSize[2];
  double b_expl_temp[2];
  double c_expl_temp[2];
  double circleSizeNum[4];
  double pFinal_lastLoop[8];
  int tmp_size[2];
  double tmp_data[10];
  int loop_ub;
  double bufferForMatlabCoder_data[10];
  double dv26[8];
  emxArray_real_T *warpedRegionTmp;
  for (i61 = 0; i61 < 4; i61++) {
    for (i62 = 0; i62 < 2; i62++) {
      pTheory[i62 + (i61 << 1)] = obj->pTheory[i62 + (((int)obj->REGION_IDX[4 +
        i61] - 1) << 1)];
      pFinal_loop[i62 + (i61 << 1)] = obj->pPrecise[i62 + (((int)obj->
        REGION_IDX[4 + i61] - 1) << 1)];
    }
  }

  b_diff = 1.0E+10;
  cnt_while = 0;
  emxInit_uint8_T(&warped, 2);
  while ((b_diff > 0.0001) && (cnt_while < 4)) {
    cnt_while++;
    for (i61 = 0; i61 < 2; i61++) {
      for (i62 = 0; i62 < 4; i62++) {
        b_pFinal_loop[i62 + (i61 << 2)] = pFinal_loop[i61 + (i62 << 1)];
        b_pTheory[i62 + (i61 << 2)] = pTheory[i61 + (i62 << 1)];
      }
    }

    b_fitgeotrans(b_pFinal_loop, b_pTheory, tform_T);
    imref2d_imref2d(obj->warpedImgDim, c_expl_temp, b_expl_temp, t2_ImageSize,
                    &b_diff, &expl_temp);
    imwarp(obj->rawImg, tform_T, t2_ImageSize, warped);
    b_correlationSearch(warped, pTheory, obj->refCircle_small.data.data,
                        obj->refCircle_small.data.size,
                        obj->refCircle_small.halfCirclePatchSize,
                        obj->refCircle_large.data.data,
                        obj->refCircle_large.data.size,
                        obj->refCircle_large.halfCirclePatchSize, b_pFinal_loop,
                        circleSizeNum, c_expl_temp);
    memcpy(&pFinal_lastLoop[0], &pFinal_loop[0], sizeof(double) << 3);
    for (i61 = 0; i61 < 2; i61++) {
      for (i62 = 0; i62 < 4; i62++) {
        b_pTheory[i62 + (i61 << 2)] = b_pFinal_loop[i61 + (i62 << 1)];
      }
    }

    e_projective2d_transformPointsI(tform_T, b_pTheory, tmp_data, tmp_size);
    loop_ub = tmp_size[0];
    for (i61 = 0; i61 < loop_ub; i61++) {
      for (i62 = 0; i62 < 2; i62++) {
        bufferForMatlabCoder_data[i62 + (i61 << 1)] = tmp_data[i61 + tmp_size[0]
          * i62];
      }
    }

    for (i61 = 0; i61 < 4; i61++) {
      for (i62 = 0; i62 < 2; i62++) {
        pFinal_loop[i62 + (i61 << 1)] = bufferForMatlabCoder_data[i62 + (i61 <<
          1)];
      }
    }

    for (i61 = 0; i61 < 8; i61++) {
      b_pFinal_loop[i61] = pFinal_loop[i61] - pFinal_lastLoop[i61];
    }

    c_abs(b_pFinal_loop, dv26);
    b_diff = d_mean(dv26);
  }

  emxFree_uint8_T(&warped);
  for (i61 = 0; i61 < 2; i61++) {
    for (i62 = 0; i62 < 4; i62++) {
      b_pFinal_loop[i62 + (i61 << 2)] = pFinal_loop[i61 + (i62 << 1)];
      b_pTheory[i62 + (i61 << 2)] = pTheory[i61 + (i62 << 1)];
    }
  }

  emxInit_real_T(&warpedRegionTmp, 2);
  b_fitgeotrans(b_pFinal_loop, b_pTheory, tform_T);
  imref2d_imref2d(obj->warpedImgDim, c_expl_temp, b_expl_temp, t2_ImageSize,
                  &b_diff, &expl_temp);
  c_imwarp(obj->rawImgTrulyRaw, tform_T, t2_ImageSize, warpedRegionTmp);
  i61 = obj->warpedRegion2->size[0] * obj->warpedRegion2->size[1];
  obj->warpedRegion2->size[0] = warpedRegionTmp->size[0];
  obj->warpedRegion2->size[1] = warpedRegionTmp->size[1];
  emxEnsureCapacity((emxArray__common *)obj->warpedRegion2, i61, (int)sizeof
                    (double));
  loop_ub = warpedRegionTmp->size[0] * warpedRegionTmp->size[1];
  for (i61 = 0; i61 < loop_ub; i61++) {
    obj->warpedRegion2->data[i61] = warpedRegionTmp->data[i61];
  }

  emxFree_real_T(&warpedRegionTmp);
}

/* End of code generation (AlignWorker_v2.c) */
