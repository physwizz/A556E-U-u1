// SPDX-License-Identifier: GPL-2.0
/*
 * Samsung Exynos SoC series Pablo driver
 *
 * Copyright (c) 2023 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef IS_VIDEO_CONFIG_H
#define IS_VIDEO_CONFIG_H

#define IS_SENSOR_VID(vid) (vid >= IS_VIDEO_SS0_NUM && vid <= IS_VIDEO_SS8_NUM)

#define LVN_SS_OFFSET (IS_LVN_SS1_VC0 - IS_LVN_SS0_VC0)
#define LVN_VC_NUM (IS_LVN_SS_VC9 - IS_LVN_SS_VC0 + 1)
#define GET_LVN_VC_OFFSET(vid) ((((vid)-IS_LVN_SS0_VC0) % LVN_SS_OFFSET) % LVN_VC_NUM)
#define IS_SENSOR_LVN_VID(vid)		(((vid >= IS_LVN_SS0_VC0) && (vid <= IS_LVN_SS8_BNS)) ? 1 : 0)
#define IS_MULTI_CH_LVN_VID(vid) 0

/* Definitions for backward compitiblity */
#define IS_VIDEO_BYRP IS_VIDEO_BYRP0

enum is_video_dev_num {
	IS_VIDEO_COMMON,
	IS_VIDEO_SS0_NUM = 1,
	IS_VIDEO_SS1_NUM,
	IS_VIDEO_SS2_NUM,
	IS_VIDEO_SS3_NUM,
	IS_VIDEO_SS4_NUM,
	IS_VIDEO_SS5_NUM,
	IS_VIDEO_SS6_NUM,
	IS_VIDEO_SS7_NUM,
	IS_VIDEO_SS8_NUM,
	IS_VIDEO_PAF0S = 10,
	IS_VIDEO_PAF1S,
	IS_VIDEO_PAF2S,
	IS_VIDEO_PAF3S,
	IS_VIDEO_BYRP0 = 20,
	IS_VIDEO_BYRP1,
	IS_VIDEO_BYRP2,
	IS_VIDEO_BYRP3,
	IS_VIDEO_BYRP4,
	IS_VIDEO_RGBP0 = 30,
	IS_VIDEO_RGBP1,
	IS_VIDEO_RGBP2,
	IS_VIDEO_RGBP3,
	IS_VIDEO_YUVSC0 = 40,
	IS_VIDEO_YUVSC1,
	IS_VIDEO_YUVSC2,
	IS_VIDEO_YUVSC3,
	IS_VIDEO_MLSC0 = 50,
	IS_VIDEO_MLSC1,
	IS_VIDEO_MLSC2,
	IS_VIDEO_MLSC3,
	/* GDC_O = GDC = 55 */
	/* GDC_M = 56 */
	/* LME = 58 */
	/* DOF = 59 */
	IS_VIDEO_MTNR = 60,
	IS_VIDEO_MSNR = 70,
	IS_VIDEO_YUVP = 80,
	IS_VIDEO_MCSC = 90,
	/* JPEG: 100 ~ 109 */

	/* Logical video node */
	IS_LVN_BASE = 200,
	IS_LVN_SS_VC0 = IS_LVN_BASE,
	IS_LVN_SS_VC1,
	IS_LVN_SS_VC2,
	IS_LVN_SS_VC3,
	IS_LVN_SS_VC4,
	IS_LVN_SS_VC5,
	IS_LVN_SS_VC6,
	IS_LVN_SS_VC7,
	IS_LVN_SS_VC8,
	IS_LVN_SS_VC9,
	IS_LVN_SS_MCB0 = 210,
	IS_LVN_SS_MCB1,
	IS_LVN_SS_BNS = 215,
	IS_LVN_SS0_VC0 = IS_LVN_BASE,
	IS_LVN_SS0_VC1,
	IS_LVN_SS0_VC2,
	IS_LVN_SS0_VC3,
	IS_LVN_SS0_VC4,
	IS_LVN_SS0_VC5,
	IS_LVN_SS0_VC6,
	IS_LVN_SS0_VC7,
	IS_LVN_SS0_VC8,
	IS_LVN_SS0_VC9,
	IS_LVN_SS0_MCB0 = 210,
	IS_LVN_SS0_MCB1,
	IS_LVN_SS0_BNS = 215,
	IS_LVN_SS1_VC0 = 220,
	IS_LVN_SS1_VC1,
	IS_LVN_SS1_VC2,
	IS_LVN_SS1_VC3,
	IS_LVN_SS1_VC4,
	IS_LVN_SS1_VC5,
	IS_LVN_SS1_VC6,
	IS_LVN_SS1_VC7,
	IS_LVN_SS1_VC8,
	IS_LVN_SS1_VC9,
	IS_LVN_SS1_MCB0 = 230,
	IS_LVN_SS1_MCB1,
	IS_LVN_SS1_BNS = 235,
	IS_LVN_SS2_VC0 = 240,
	IS_LVN_SS2_VC1,
	IS_LVN_SS2_VC2,
	IS_LVN_SS2_VC3,
	IS_LVN_SS2_VC4,
	IS_LVN_SS2_VC5,
	IS_LVN_SS2_VC6,
	IS_LVN_SS2_VC7,
	IS_LVN_SS2_VC8,
	IS_LVN_SS2_VC9,
	IS_LVN_SS2_MCB0 = 250,
	IS_LVN_SS2_MCB1,
	IS_LVN_SS2_BNS = 255,
	IS_LVN_SS3_VC0 = 260,
	IS_LVN_SS3_VC1,
	IS_LVN_SS3_VC2,
	IS_LVN_SS3_VC3,
	IS_LVN_SS3_VC4,
	IS_LVN_SS3_VC5,
	IS_LVN_SS3_VC6,
	IS_LVN_SS3_VC7,
	IS_LVN_SS3_VC8,
	IS_LVN_SS3_VC9,
	IS_LVN_SS3_MCB0 = 270,
	IS_LVN_SS3_MCB1,
	IS_LVN_SS3_BNS = 275,
	IS_LVN_SS4_VC0 = 280,
	IS_LVN_SS4_VC1,
	IS_LVN_SS4_VC2,
	IS_LVN_SS4_VC3,
	IS_LVN_SS4_VC4,
	IS_LVN_SS4_VC5,
	IS_LVN_SS4_VC6,
	IS_LVN_SS4_VC7,
	IS_LVN_SS4_VC8,
	IS_LVN_SS4_VC9,
	IS_LVN_SS4_MCB0 = 290,
	IS_LVN_SS4_MCB1,
	IS_LVN_SS4_BNS = 295,
	IS_LVN_SS5_VC0 = 300,
	IS_LVN_SS5_VC1,
	IS_LVN_SS5_VC2,
	IS_LVN_SS5_VC3,
	IS_LVN_SS5_VC4,
	IS_LVN_SS5_VC5,
	IS_LVN_SS5_VC6,
	IS_LVN_SS5_VC7,
	IS_LVN_SS5_VC8,
	IS_LVN_SS5_VC9,
	IS_LVN_SS5_MCB0 = 310,
	IS_LVN_SS5_MCB1,
	IS_LVN_SS5_BNS = 315,
	IS_LVN_SS6_VC0 = 320,
	IS_LVN_SS6_VC1,
	IS_LVN_SS6_VC2,
	IS_LVN_SS6_VC3,
	IS_LVN_SS6_VC4,
	IS_LVN_SS6_VC5,
	IS_LVN_SS6_VC6,
	IS_LVN_SS6_VC7,
	IS_LVN_SS6_VC8,
	IS_LVN_SS6_VC9,
	IS_LVN_SS6_MCB0 = 330,
	IS_LVN_SS6_MCB1,
	IS_LVN_SS6_BNS = 335,
	IS_LVN_SS7_VC0 = 340,
	IS_LVN_SS7_VC1,
	IS_LVN_SS7_VC2,
	IS_LVN_SS7_VC3,
	IS_LVN_SS7_VC4,
	IS_LVN_SS7_VC5,
	IS_LVN_SS7_VC6,
	IS_LVN_SS7_VC7,
	IS_LVN_SS7_VC8,
	IS_LVN_SS7_VC9,
	IS_LVN_SS7_MCB0 = 350,
	IS_LVN_SS7_MCB1,
	IS_LVN_SS7_BNS = 355,
	IS_LVN_SS8_VC0 = 360,
	IS_LVN_SS8_VC1,
	IS_LVN_SS8_VC2,
	IS_LVN_SS8_VC3,
	IS_LVN_SS8_VC4,
	IS_LVN_SS8_VC5,
	IS_LVN_SS8_VC6,
	IS_LVN_SS8_VC7,
	IS_LVN_SS8_VC8,
	IS_LVN_SS8_VC9,
	IS_LVN_SS8_MCB0 = 370,
	IS_LVN_SS8_MCB1,
	IS_LVN_SS8_BNS = 375,
	IS_LVN_BYRP_BYR = 400,
	IS_LVN_BYRP_HDR,
	IS_LVN_BYRP0_BYR = IS_LVN_BYRP_BYR,
	IS_LVN_BYRP0_HDR,
	IS_LVN_BYRP1_BYR = 410,
	IS_LVN_BYRP1_HDR,
	IS_LVN_BYRP2_BYR = 420,
	IS_LVN_BYRP2_HDR,
	IS_LVN_BYRP3_BYR = 430,
	IS_LVN_BYRP3_HDR,
	IS_LVN_BYRP4_BYR = 440,
	IS_LVN_BYRP4_HDR,
	IS_LVN_RGBP_DRC = 450,
	IS_LVN_RGBP_SAT,
	IS_LVN_RGBP_HIST,
	IS_LVN_RGBP0_DRC = IS_LVN_RGBP_DRC,
	IS_LVN_RGBP0_SAT,
	IS_LVN_RGBP0_HIST,
	IS_LVN_RGBP1_DRC = 460,
	IS_LVN_RGBP1_SAT,
	IS_LVN_RGBP1_HIST,
	IS_LVN_RGBP2_DRC = 470,
	IS_LVN_RGBP2_SAT,
	IS_LVN_RGBP2_HIST,
	IS_LVN_RGBP3_DRC = 480,
	IS_LVN_RGBP3_SAT,
	IS_LVN_RGBP3_HIST,
	IS_LVN_MLSC_SVHIST = 490,
	IS_LVN_MLSC_FDPIG,
	IS_LVN_MLSC_LMEDS,
	IS_LVN_MLSC_CAV,
	IS_LVN_MLSC_GLPG_L0,
	IS_LVN_MLSC_GLPG_L1,
	IS_LVN_MLSC_GLPG_L2,
	IS_LVN_MLSC_GLPG_L3,
	IS_LVN_MLSC_GLPG_G4,
	IS_LVN_MLSC_YUV444,
	IS_LVN_MLSC0_SVHIST = IS_LVN_MLSC_SVHIST,
	IS_LVN_MLSC0_FDPIG,
	IS_LVN_MLSC0_LMEDS,
	IS_LVN_MLSC0_CAV,
	IS_LVN_MLSC0_GLPG_L0,
	IS_LVN_MLSC0_GLPG_L1,
	IS_LVN_MLSC0_GLPG_L2,
	IS_LVN_MLSC0_GLPG_L3,
	IS_LVN_MLSC0_GLPG_G4,
	IS_LVN_MLSC0_YUV444,
	IS_LVN_MLSC1_SVHIST = 500,
	IS_LVN_MLSC1_FDPIG,
	IS_LVN_MLSC1_LMEDS,
	IS_LVN_MLSC1_CAV,
	IS_LVN_MLSC1_GLPG_L0,
	IS_LVN_MLSC1_GLPG_L1,
	IS_LVN_MLSC1_GLPG_L2,
	IS_LVN_MLSC1_GLPG_L3,
	IS_LVN_MLSC1_GLPG_G4,
	IS_LVN_MLSC1_YUV444,
	IS_LVN_MLSC2_SVHIST = 510,
	IS_LVN_MLSC2_FDPIG,
	IS_LVN_MLSC2_LMEDS,
	IS_LVN_MLSC2_CAV,
	IS_LVN_MLSC2_GLPG_L0,
	IS_LVN_MLSC2_GLPG_L1,
	IS_LVN_MLSC2_GLPG_L2,
	IS_LVN_MLSC2_GLPG_L3,
	IS_LVN_MLSC2_GLPG_G4,
	IS_LVN_MLSC2_YUV444,
	IS_LVN_MLSC3_SVHIST = 520,
	IS_LVN_MLSC3_FDPIG,
	IS_LVN_MLSC3_LMEDS,
	IS_LVN_MLSC3_CAV,
	IS_LVN_MLSC3_GLPG_L0,
	IS_LVN_MLSC3_GLPG_L1,
	IS_LVN_MLSC3_GLPG_L2,
	IS_LVN_MLSC3_GLPG_L3,
	IS_LVN_MLSC3_GLPG_G4,
	IS_LVN_MLSC3_YUV444,
	IS_LVN_MTNR_OUTPUT_CUR_L1 = 530,
	IS_LVN_MTNR_OUTPUT_CUR_L2,
	IS_LVN_MTNR_OUTPUT_CUR_L3,
	IS_LVN_MTNR_OUTPUT_CUR_L4,
	IS_LVN_MTNR_OUTPUT_PREV_L0,
	IS_LVN_MTNR_OUTPUT_PREV_L1,
	IS_LVN_MTNR_OUTPUT_PREV_L2,
	IS_LVN_MTNR_OUTPUT_PREV_L3,
	IS_LVN_MTNR_OUTPUT_PREV_L4,
	IS_LVN_MTNR_OUTPUT_MV_GEOMATCH,
	IS_LVN_MTNR_OUTPUT_PREV_L0_WGT = 540,
	IS_LVN_MTNR_OUTPUT_PREV_L1_WGT,
	IS_LVN_MTNR_OUTPUT_SEG_L0,
	IS_LVN_MTNR_OUTPUT_SEG_L1,
	IS_LVN_MTNR_OUTPUT_SEG_L2,
	IS_LVN_MTNR_OUTPUT_SEG_L3,
	IS_LVN_MTNR_OUTPUT_SEG_L4,
	IS_LVN_MTNR_CAPTURE_PREV_L0,
	IS_LVN_MTNR_CAPTURE_PREV_L1,
	IS_LVN_MTNR_CAPTURE_PREV_L2,
	IS_LVN_MTNR_CAPTURE_PREV_L3 = 550,
	IS_LVN_MTNR_CAPTURE_PREV_L4,
	IS_LVN_MTNR_CAPTURE_PREV_L0_WGT,
	IS_LVN_MTNR_CAPTURE_PREV_L1_WGT,
	IS_LVN_MTNR0_CR,
	IS_LVN_MTNR1_CR,
	IS_LVN_MSNR_LMEDS = 560,
	IS_LVN_MSNR_CR,
	IS_LVN_YUVP_SEG = 570,
	IS_LVN_YUVP_DRC,
	IS_LVN_YUVP_CLAHE,
	IS_LVN_YUVP_PCC_R,
	IS_LVN_YUVP_PCC_W,
	IS_LVN_YUVP_CR,
	IS_LVN_MCSC_P0 = 580,
	IS_LVN_MCSC_P1,
	IS_LVN_MCSC_P2,
	IS_LVN_MCSC_P3,
	IS_LVN_MCSC_P4,
	IS_LVN_MCSC_P5,
	IS_LVN_MCSC_CR,
	IS_VIDEO_MAX_NUM
};

static const char *const vn_name[IS_VIDEO_MAX_NUM + 1] = { [IS_VIDEO_COMMON] = "V:CMN",

	[IS_VIDEO_SS0_NUM] = "V:SS0",
	[IS_VIDEO_SS1_NUM] = "V:SS1",
	[IS_VIDEO_SS2_NUM] = "V:SS2",
	[IS_VIDEO_SS3_NUM] = "V:SS3",
	[IS_VIDEO_SS4_NUM] = "V:SS4",
	[IS_VIDEO_SS5_NUM] = "V:SS5",
	[IS_VIDEO_SS6_NUM] = "V:SS6",
	[IS_VIDEO_SS7_NUM] = "V:SS7",
	[IS_VIDEO_SS8_NUM] = "V:SS8",

	[IS_VIDEO_PAF0S] = "V:PDP0",
	[IS_VIDEO_PAF1S] = "V:PDP1",
	[IS_VIDEO_PAF2S] = "V:PDP2",
	[IS_VIDEO_PAF3S] = "V:PDP3",

	[IS_VIDEO_BYRP0] = "V:BYRP0",
	[IS_VIDEO_BYRP1] = "V:BYRP1",
	[IS_VIDEO_BYRP2] = "V:BYRP2",
	[IS_VIDEO_BYRP3] = "V:BYRP3",
	[IS_VIDEO_BYRP4] = "V:BYRP4",

	[IS_VIDEO_RGBP0] = "V:RGBP0",
	[IS_VIDEO_RGBP1] = "V:RGBP1",
	[IS_VIDEO_RGBP2] = "V:RGBP2",
	[IS_VIDEO_RGBP3] = "V:RGBP3",

	[IS_VIDEO_YUVSC0] = "V:YUVSC0",
	[IS_VIDEO_YUVSC1] = "V:YUVSC1",
	[IS_VIDEO_YUVSC2] = "V:YUVSC2",
	[IS_VIDEO_YUVSC3] = "V:YUVSC3",

	[IS_VIDEO_MLSC0] = "V:MLSC0",
	[IS_VIDEO_MLSC1] = "V:MLSC1",
	[IS_VIDEO_MLSC2] = "V:MLSC2",
	[IS_VIDEO_MLSC3] = "V:MLSC3",

	[IS_VIDEO_MTNR] = "V:MTNR",

	[IS_VIDEO_MSNR] = "V:MSNR",

	[IS_VIDEO_YUVP] = "V:YUVP",

	[IS_VIDEO_MCSC] = "V:MCSC",

	[IS_LVN_SS0_VC0] = "V:S0V0",
	[IS_LVN_SS0_VC1] = "V:S0V1",
	[IS_LVN_SS0_VC2] = "V:S0V2",
	[IS_LVN_SS0_VC3] = "V:S0V3",
	[IS_LVN_SS0_VC4] = "V:S0V4",
	[IS_LVN_SS0_VC5] = "V:S0V5",
	[IS_LVN_SS0_VC6] = "V:S0V6",
	[IS_LVN_SS0_VC7] = "V:S0V7",
	[IS_LVN_SS0_VC8] = "V:S0V8",
	[IS_LVN_SS0_VC9] = "V:S0V9",
	[IS_LVN_SS0_MCB0] = "V:S0M0",
	[IS_LVN_SS0_MCB1] = "V:S0M1",
	[IS_LVN_SS0_BNS] = "V:S0B",

	[IS_LVN_SS1_VC0] = "V:S1V0",
	[IS_LVN_SS1_VC1] = "V:S1V1",
	[IS_LVN_SS1_VC2] = "V:S1V2",
	[IS_LVN_SS1_VC3] = "V:S1V3",
	[IS_LVN_SS1_VC4] = "V:S1V4",
	[IS_LVN_SS1_VC5] = "V:S1V5",
	[IS_LVN_SS1_VC6] = "V:S1V6",
	[IS_LVN_SS1_VC7] = "V:S1V7",
	[IS_LVN_SS1_VC8] = "V:S1V8",
	[IS_LVN_SS1_VC9] = "V:S1V9",
	[IS_LVN_SS1_MCB0] = "V:S1M0",
	[IS_LVN_SS1_MCB1] = "V:S1M1",
	[IS_LVN_SS1_BNS] = "V:S1B",

	[IS_LVN_SS2_VC0] = "V:S2V0",
	[IS_LVN_SS2_VC1] = "V:S2V1",
	[IS_LVN_SS2_VC2] = "V:S2V2",
	[IS_LVN_SS2_VC3] = "V:S2V3",
	[IS_LVN_SS2_VC4] = "V:S2V4",
	[IS_LVN_SS2_VC5] = "V:S2V5",
	[IS_LVN_SS2_VC6] = "V:S2V6",
	[IS_LVN_SS2_VC7] = "V:S2V7",
	[IS_LVN_SS2_VC8] = "V:S2V8",
	[IS_LVN_SS2_VC9] = "V:S2V9",
	[IS_LVN_SS2_MCB0] = "V:S2M0",
	[IS_LVN_SS2_MCB1] = "V:S2M1",
	[IS_LVN_SS2_BNS] = "V:S2B",

	[IS_LVN_SS3_VC0] = "V:S3V0",
	[IS_LVN_SS3_VC1] = "V:S3V1",
	[IS_LVN_SS3_VC2] = "V:S3V2",
	[IS_LVN_SS3_VC3] = "V:S3V3",
	[IS_LVN_SS3_VC4] = "V:S3V4",
	[IS_LVN_SS3_VC5] = "V:S3V5",
	[IS_LVN_SS3_VC6] = "V:S3V6",
	[IS_LVN_SS3_VC7] = "V:S3V7",
	[IS_LVN_SS3_VC8] = "V:S3V8",
	[IS_LVN_SS3_VC9] = "V:S3V9",
	[IS_LVN_SS3_MCB0] = "V:S3M0",
	[IS_LVN_SS3_MCB1] = "V:S3M1",
	[IS_LVN_SS3_BNS] = "V:S3B",

	[IS_LVN_SS4_VC0] = "V:S4V0",
	[IS_LVN_SS4_VC1] = "V:S4V1",
	[IS_LVN_SS4_VC2] = "V:S4V2",
	[IS_LVN_SS4_VC3] = "V:S4V3",
	[IS_LVN_SS4_VC4] = "V:S4V4",
	[IS_LVN_SS4_VC5] = "V:S4V5",
	[IS_LVN_SS4_VC6] = "V:S4V6",
	[IS_LVN_SS4_VC7] = "V:S4V7",
	[IS_LVN_SS4_VC8] = "V:S4V8",
	[IS_LVN_SS4_VC9] = "V:S4V9",
	[IS_LVN_SS4_MCB0] = "V:S4M0",
	[IS_LVN_SS4_MCB1] = "V:S4M1",
	[IS_LVN_SS4_BNS] = "V:S4B",

	[IS_LVN_SS5_VC0] = "V:S5V0",
	[IS_LVN_SS5_VC1] = "V:S5V1",
	[IS_LVN_SS5_VC2] = "V:S5V2",
	[IS_LVN_SS5_VC3] = "V:S5V3",
	[IS_LVN_SS5_VC4] = "V:S5V4",
	[IS_LVN_SS5_VC5] = "V:S5V5",
	[IS_LVN_SS5_VC6] = "V:S5V6",
	[IS_LVN_SS5_VC7] = "V:S5V7",
	[IS_LVN_SS5_VC8] = "V:S5V8",
	[IS_LVN_SS5_VC9] = "V:S5V9",
	[IS_LVN_SS5_MCB0] = "V:S5M0",
	[IS_LVN_SS5_MCB1] = "V:S5M1",
	[IS_LVN_SS5_BNS] = "V:S5B",

	[IS_LVN_SS6_VC0] = "V:S6V0",
	[IS_LVN_SS6_VC1] = "V:S6V1",
	[IS_LVN_SS6_VC2] = "V:S6V2",
	[IS_LVN_SS6_VC3] = "V:S6V3",
	[IS_LVN_SS6_VC4] = "V:S6V4",
	[IS_LVN_SS6_VC5] = "V:S6V5",
	[IS_LVN_SS6_VC6] = "V:S6V6",
	[IS_LVN_SS6_VC7] = "V:S6V7",
	[IS_LVN_SS6_VC8] = "V:S6V8",
	[IS_LVN_SS6_VC9] = "V:S6V9",
	[IS_LVN_SS6_MCB0] = "V:S6M0",
	[IS_LVN_SS6_MCB1] = "V:S6M1",
	[IS_LVN_SS6_BNS] = "V:S6B",

	[IS_LVN_SS7_VC0] = "V:S7V0",
	[IS_LVN_SS7_VC1] = "V:S7V1",
	[IS_LVN_SS7_VC2] = "V:S7V2",
	[IS_LVN_SS7_VC3] = "V:S7V3",
	[IS_LVN_SS7_VC4] = "V:S7V4",
	[IS_LVN_SS7_VC5] = "V:S7V5",
	[IS_LVN_SS7_VC6] = "V:S7V6",
	[IS_LVN_SS7_VC7] = "V:S7V7",
	[IS_LVN_SS7_VC8] = "V:S7V8",
	[IS_LVN_SS7_VC9] = "V:S7V9",
	[IS_LVN_SS7_MCB0] = "V:S7M0",
	[IS_LVN_SS7_MCB1] = "V:S7M1",
	[IS_LVN_SS7_BNS] = "V:S7B",

	[IS_LVN_SS8_VC0] = "V:S8V0",
	[IS_LVN_SS8_VC1] = "V:S8V1",
	[IS_LVN_SS8_VC2] = "V:S8V2",
	[IS_LVN_SS8_VC3] = "V:S8V3",
	[IS_LVN_SS8_VC4] = "V:S8V4",
	[IS_LVN_SS8_VC5] = "V:S8V5",
	[IS_LVN_SS8_VC6] = "V:S8V6",
	[IS_LVN_SS8_VC7] = "V:S8V7",
	[IS_LVN_SS8_VC8] = "V:S8V8",
	[IS_LVN_SS8_VC9] = "V:S8V9",
	[IS_LVN_SS8_MCB0] = "V:S8M0",
	[IS_LVN_SS8_MCB1] = "V:S8M1",
	[IS_LVN_SS8_BNS] = "V:S8B",

	[IS_LVN_BYRP0_BYR] = "V:BYRP0_BYR",
	[IS_LVN_BYRP0_HDR] = "V:BYRP0_HDR",

	[IS_LVN_BYRP1_BYR] = "V:BYRP1_BYR",
	[IS_LVN_BYRP1_HDR] = "V:BYRP1_HDR",

	[IS_LVN_BYRP2_BYR] = "V:BYRP2_BYR",
	[IS_LVN_BYRP2_HDR] = "V:BYRP2_HDR",

	[IS_LVN_BYRP3_BYR] = "V:BYRP3_BYR",
	[IS_LVN_BYRP3_HDR] = "V:BYRP3_HDR",

	[IS_LVN_BYRP4_BYR] = "V:BYRP4_BYR",
	[IS_LVN_BYRP4_HDR] = "V:BYRP4_HDR",

	[IS_LVN_RGBP0_DRC] = "V:RGBP0_DRC",
	[IS_LVN_RGBP0_SAT] = "V:RGBP0_SAT",
	[IS_LVN_RGBP0_HIST] = "V:RGBP0_HIST",

	[IS_LVN_RGBP1_DRC] = "V:RGBP1_DRC",
	[IS_LVN_RGBP1_SAT] = "V:RGBP1_SAT",
	[IS_LVN_RGBP1_HIST] = "V:RGBP1_HIST",

	[IS_LVN_RGBP2_DRC] = "V:RGBP2_DRC",
	[IS_LVN_RGBP2_SAT] = "V:RGBP2_SAT",
	[IS_LVN_RGBP2_HIST] = "V:RGBP2_HIST",

	[IS_LVN_RGBP3_DRC] = "V:RGBP3_DRC",
	[IS_LVN_RGBP3_SAT] = "V:RGBP3_SAT",
	[IS_LVN_RGBP3_HIST] = "V:RGBP3_HIST",

	[IS_LVN_MLSC0_SVHIST] = "V:MLSC0_SVHIST",
	[IS_LVN_MLSC0_FDPIG] = "V:MLSC0_FDPIG",
	[IS_LVN_MLSC0_LMEDS] = "V:MLSC0_LMEDS",
	[IS_LVN_MLSC0_CAV] = "V:MLSC0_CAV",
	[IS_LVN_MLSC0_GLPG_L0] = "V:MLSC0_GLPG_L0",
	[IS_LVN_MLSC0_GLPG_L1] = "V:MLSC0_GLPG_L1",
	[IS_LVN_MLSC0_GLPG_L2] = "V:MLSC0_GLPG_L2",
	[IS_LVN_MLSC0_GLPG_L3] = "V:MLSC0_GLPG_L3",
	[IS_LVN_MLSC0_GLPG_G4] = "V:MLSC0_GLPG_G4",
	[IS_LVN_MLSC0_YUV444] = "V:MLSC0_YUV444",

	[IS_LVN_MLSC1_SVHIST] = "V:MLSC1_SVHIST",
	[IS_LVN_MLSC1_FDPIG] = "V:MLSC1_FDPIG",
	[IS_LVN_MLSC1_LMEDS] = "V:MLSC1_LMEDS",
	[IS_LVN_MLSC1_CAV] = "V:MLSC1_CAV",
	[IS_LVN_MLSC1_GLPG_L0] = "V:MLSC1_GLPG_L0",
	[IS_LVN_MLSC1_GLPG_L1] = "V:MLSC1_GLPG_L1",
	[IS_LVN_MLSC1_GLPG_L2] = "V:MLSC1_GLPG_L2",
	[IS_LVN_MLSC1_GLPG_L3] = "V:MLSC1_GLPG_L3",
	[IS_LVN_MLSC1_GLPG_G4] = "V:MLSC1_GLPG_G4",
	[IS_LVN_MLSC1_YUV444] = "V:MLSC1_YUV444",

	[IS_LVN_MLSC2_SVHIST] = "V:MLSC2_SVHIST",
	[IS_LVN_MLSC2_FDPIG] = "V:MLSC2_FDPIG",
	[IS_LVN_MLSC2_LMEDS] = "V:MLSC2_LMEDS",
	[IS_LVN_MLSC2_CAV] = "V:MLSC2_CAV",
	[IS_LVN_MLSC2_GLPG_L0] = "V:MLSC2_GLPG_L0",
	[IS_LVN_MLSC2_GLPG_L1] = "V:MLSC2_GLPG_L1",
	[IS_LVN_MLSC2_GLPG_L2] = "V:MLSC2_GLPG_L2",
	[IS_LVN_MLSC2_GLPG_L3] = "V:MLSC2_GLPG_L3",
	[IS_LVN_MLSC2_GLPG_G4] = "V:MLSC2_GLPG_G4",
	[IS_LVN_MLSC2_YUV444] = "V:MLSC2_YUV444",

	[IS_LVN_MLSC3_SVHIST] = "V:MLSC3_SVHIST",
	[IS_LVN_MLSC3_FDPIG] = "V:MLSC3_FDPIG",
	[IS_LVN_MLSC3_LMEDS] = "V:MLSC3_LMEDS",
	[IS_LVN_MLSC3_CAV] = "V:MLSC3_CAV",
	[IS_LVN_MLSC3_GLPG_L0] = "V:MLSC3_GLPG_L0",
	[IS_LVN_MLSC3_GLPG_L1] = "V:MLSC3_GLPG_L1",
	[IS_LVN_MLSC3_GLPG_L2] = "V:MLSC3_GLPG_L2",
	[IS_LVN_MLSC3_GLPG_L3] = "V:MLSC3_GLPG_L3",
	[IS_LVN_MLSC3_GLPG_G4] = "V:MLSC3_GLPG_G4",
	[IS_LVN_MLSC3_YUV444] = "V:MLSC3_YUV444",

	[IS_LVN_MTNR_OUTPUT_CUR_L1] = "V:MTNR_OUT_CUR_L1",
	[IS_LVN_MTNR_OUTPUT_CUR_L2] = "V:MTNR_OUT_CUR_L2",
	[IS_LVN_MTNR_OUTPUT_CUR_L3] = "V:MTNR_OUT_CUR_L3",
	[IS_LVN_MTNR_OUTPUT_CUR_L4] = "V:MTNR_OUT_CUR_L4",
	[IS_LVN_MTNR_OUTPUT_PREV_L0] = "V:MTNR_OUT_PREV_L0",
	[IS_LVN_MTNR_OUTPUT_PREV_L1] = "V:MTNR_OUT_PREV_L1",
	[IS_LVN_MTNR_OUTPUT_PREV_L2] = "V:MTNR_OUT_PREV_L2",
	[IS_LVN_MTNR_OUTPUT_PREV_L3] = "V:MTNR_OUT_PREV_L3",
	[IS_LVN_MTNR_OUTPUT_PREV_L4] = "V:MTNR_OUT_PREV_L4",
	[IS_LVN_MTNR_OUTPUT_MV_GEOMATCH] = "V:MTNR_OUT_MV_GEOMATCH",
	[IS_LVN_MTNR_OUTPUT_PREV_L0_WGT] = "V:MTNR_OUT_PREV_L0_WGT",
	[IS_LVN_MTNR_OUTPUT_PREV_L1_WGT] = "V:MTNR_OUT_PREV_L1_WGT",
	[IS_LVN_MTNR_OUTPUT_SEG_L0] = "V:MTNR_OUT_SEG_L0",
	[IS_LVN_MTNR_OUTPUT_SEG_L1] = "V:MTNR_OUT_SEG_L1",
	[IS_LVN_MTNR_OUTPUT_SEG_L2] = "V:MTNR_OUT_SEG_L2",
	[IS_LVN_MTNR_OUTPUT_SEG_L3] = "V:MTNR_OUT_SEG_L3",
	[IS_LVN_MTNR_OUTPUT_SEG_L4] = "V:MTNR_OUT_SEG_L4",
	[IS_LVN_MTNR_CAPTURE_PREV_L0] = "V:MTNR_CAP_PREV_L0",
	[IS_LVN_MTNR_CAPTURE_PREV_L1] = "V:MTNR_CAP_PREV_L1",
	[IS_LVN_MTNR_CAPTURE_PREV_L2] = "V:MTNR_CAP_PREV_L2",
	[IS_LVN_MTNR_CAPTURE_PREV_L3] = "V:MTNR_CAP_PREV_L3",
	[IS_LVN_MTNR_CAPTURE_PREV_L4] = "V:MTNR_CAP_PREV_L4",
	[IS_LVN_MTNR_CAPTURE_PREV_L0_WGT] = "V:MTNR_CAP_PREV_L0_WGT",
	[IS_LVN_MTNR_CAPTURE_PREV_L1_WGT] = "V:MTNR_CAP_PREV_L1_WGT",
	[IS_LVN_MTNR0_CR] = "V:MTNR0_CR",
	[IS_LVN_MTNR1_CR] = "V:MTNR1_CR",

	[IS_LVN_MSNR_LMEDS] = "V:MSNR_LMEDS",
	[IS_LVN_MSNR_CR] = "V:MSNR_CR",

	[IS_LVN_YUVP_SEG] = "V:YUVP_SEG",
	[IS_LVN_YUVP_DRC] = "V:YUVP_DRC",
	[IS_LVN_YUVP_CLAHE] = "V:YUVP_CLAHE",
	[IS_LVN_YUVP_PCC_R] = "V:YUVP_PCC_R",
	[IS_LVN_YUVP_PCC_W] = "V:YUVP_PCC_W",
	[IS_LVN_YUVP_CR] = "V:YUVP_CR",

	[IS_LVN_MCSC_P0] = "V:MCSC_P0",
	[IS_LVN_MCSC_P1] = "V:MCSC_P1",
	[IS_LVN_MCSC_P2] = "V:MCSC_P2",
	[IS_LVN_MCSC_P3] = "V:MCSC_P3",
	[IS_LVN_MCSC_P4] = "V:MCSC_P4",
	[IS_LVN_MCSC_P5] = "V:MCSC_P5",
	[IS_LVN_MCSC_CR] = "V:MCSC_CR",

	[IS_VIDEO_MAX_NUM] = "V:MAX" };

static const char *blob_lvn_name[] = {
	"V:S0V0",    "V:S0V1",	  "V:S0V2",    "V:S0V3",    "V:S0V4",
	"V:S0V5",    "V:S0V6",	  "V:S0V7",

	"V:S1V0",    "V:S1V1",	  "V:S1V2",    "V:S1V3",    "V:S1V4",
	"V:S1V5",    "V:S1V6",	  "V:S1V7",

	"V:S2V0",    "V:S2V1",	  "V:S2V2",    "V:S2V3",    "V:S2V4",
	"V:S2V5",    "V:S2V6",	  "V:S2V7",

	"V:S3V0",    "V:S3V1",	  "V:S3V2",    "V:S3V3",    "V:S3V4",
	"V:S3V5",    "V:S3V6",	  "V:S3V7",

	"V:S4V0",    "V:S4V1",	  "V:S4V2",    "V:S4V3",    "V:S4V4",
	"V:S4V5",    "V:S4V6",	  "V:S4V7",

	"V:MCSC_P0", "V:MCSC_P1", "V:MCSC_P2", "V:MCSC_P3", "V:MCSC_P4",
};

#endif /* IS_VIDEO_CONFIG_H */
