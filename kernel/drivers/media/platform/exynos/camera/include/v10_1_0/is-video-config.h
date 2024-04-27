// SPDX-License-Identifier: GPL-2.0
/*
 * Samsung Exynos SoC series Pablo driver
 *
 * Copyright (c) 2021 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef IS_VIDEO_CONFIG_H
#define IS_VIDEO_CONFIG_H

#define IS_VIDEO_BYRP_NAME		IS_VIDEO_NAME("byrp")
#define IS_VIDEO_RGBP_NAME		IS_VIDEO_NAME("rgbp")
#define IS_VIDEO_MCFP_NAME		IS_VIDEO_NAME("mcfp")
#define IS_VIDEO_YUVP_NAME		IS_VIDEO_NAME("yuvp")

#define IS_SENSOR_VID(vid)                                                                         \
	((vid >= IS_VIDEO_SS0_NUM && vid <= IS_VIDEO_SS8_NUM) ||                                   \
		(vid >= IS_VIDEO_SS0VC0_NUM && vid < IS_VIDEO_SS6VC3_NUM))

#define LVN_SS_OFFSET (IS_LVN_SS1_VC0 - IS_LVN_SS0_VC0)
#define LVN_VC_NUM (IS_LVN_SS0_VC9 - IS_LVN_SS0_VC0 + 1)
#define GET_LVN_VC_OFFSET(vid) ((((vid)-IS_LVN_SS0_VC0) % LVN_SS_OFFSET) % LVN_VC_NUM)
#define IS_SENSOR_LVN_VID(vid)		(((vid >= IS_LVN_SS0_VC0) && (vid <= IS_LVN_SS8_BNS)) ? 1 : 0)
#define IS_MULTI_CH_LVN_VID(vid)	(((vid >= IS_LVN_CSTAT0_LME_DS0) && (vid <= IS_LVN_CSTAT3_CDS)) ? 1 : 0)

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
	IS_VIDEO_BNS_NUM = 7,
	IS_VIDEO_PRE_NUM = 9,
	IS_VIDEO_CSTAT0 = 10,
	IS_VIDEO_30S_NUM = IS_VIDEO_CSTAT0,
	IS_VIDEO_CSTAT1 = 11,
	IS_VIDEO_31S_NUM = IS_VIDEO_CSTAT1,
	IS_VIDEO_CSTAT2 = 12,
	IS_VIDEO_32S_NUM = IS_VIDEO_CSTAT2,
	IS_VIDEO_CSTAT3 = 13,
	IS_VIDEO_33S_NUM = IS_VIDEO_CSTAT3,
	IS_VIDEO_30C_NUM,
	IS_VIDEO_30P_NUM,
	IS_VIDEO_30F_NUM,
	IS_VIDEO_30G_NUM,
	IS_VIDEO_30O_NUM,	/* ORB DS WDMA */
	IS_VIDEO_30L_NUM,	/* LME DS WDMA */
	IS_VIDEO_BYRP = 20,
	IS_VIDEO_31C_NUM,
	IS_VIDEO_31P_NUM,
	IS_VIDEO_31F_NUM,
	IS_VIDEO_31G_NUM,
	IS_VIDEO_31O_NUM,	/* ORB DS WDMA */
	IS_VIDEO_31L_NUM,	/* LME DS WDMA */
	IS_VIDEO_33O_NUM,	/* ORB DS WDMA */
	IS_VIDEO_33L_NUM,	/* LME DS WDMA */
	IS_VIDEO_RGBP = 30,
	IS_VIDEO_I0S_NUM = 30,
	IS_VIDEO_I0C_NUM,
	IS_VIDEO_I0P_NUM,
	IS_VIDEO_I0V_NUM,	/* MCFP/TNR PREV BAYER WDMA */
	IS_VIDEO_I0W_NUM,	/* MCFP/TNR PREV WEIGHT WDMA */
	IS_VIDEO_I0T_NUM,	/* MCFP/TNR PREV BAYER RDMA */
	IS_VIDEO_I0G_NUM,	/* MCFP/TNR PREV WEIGHT RDMA */
	IS_VIDEO_MCFP = 40,
	IS_VIDEO_I1S_NUM = 40,
	IS_VIDEO_I1C_NUM,
	IS_VIDEO_I1P_NUM,
	IS_VIDEO_I1T_NUM,
	IS_VIDEO_ME0C_NUM = 48,
	IS_VIDEO_ME1C_NUM = 49,
	IS_VIDEO_YUVP = 50,
	/* GDC: 55 */
	IS_VIDEO_MCSC0 = 60,
	IS_VIDEO_MCSC1,
	IS_VIDEO_M0S_NUM = 60,
	IS_VIDEO_M1S_NUM,
	IS_VIDEO_LME = 70,
	IS_VIDEO_LME0_NUM = IS_VIDEO_LME,
	IS_VIDEO_VRA_NUM = 80,
	IS_VIDEO_YPP_NUM = 81,
	IS_VIDEO_LME1_NUM = 88,
	IS_VIDEO_LME1S_NUM,
	IS_VIDEO_LME1C_NUM,	/* LME MOTION HW OUT(pure motion) */
	IS_VIDEO_CLH0S_NUM = 94,
	IS_VIDEO_CLH0C_NUM,
	IS_VIDEO_ORB0C_NUM,
	IS_VIDEO_ORB1C_NUM,
	IS_VIDEO_ORB0_NUM,
	IS_VIDEO_ORB1_NUM,
	/* JPEG: 100 ~ 109 */
	IS_VIDEO_SS0VC0_NUM = 110,
	IS_VIDEO_SS0VC1_NUM,
	IS_VIDEO_SS0VC2_NUM,
	IS_VIDEO_SS0VC3_NUM,
	IS_VIDEO_SS1VC0_NUM,
	IS_VIDEO_SS1VC1_NUM,
	IS_VIDEO_SS1VC2_NUM,
	IS_VIDEO_SS1VC3_NUM,
	IS_VIDEO_SS2VC0_NUM,
	IS_VIDEO_SS2VC1_NUM,
	IS_VIDEO_SS2VC2_NUM = 120,
	IS_VIDEO_SS2VC3_NUM,
	IS_VIDEO_SS3VC0_NUM,
	IS_VIDEO_SS3VC1_NUM,
	IS_VIDEO_SS3VC2_NUM,
	IS_VIDEO_SS3VC3_NUM,
	IS_VIDEO_SS4VC0_NUM,
	IS_VIDEO_SS4VC1_NUM,
	IS_VIDEO_SS4VC2_NUM,
	IS_VIDEO_SS4VC3_NUM,
	IS_VIDEO_SS5VC0_NUM = 130,
	IS_VIDEO_SS5VC1_NUM,
	IS_VIDEO_SS5VC2_NUM,
	IS_VIDEO_SS5VC3_NUM,
	IS_VIDEO_SS6VC0_NUM,
	IS_VIDEO_SS6VC1_NUM,
	IS_VIDEO_SS6VC2_NUM,
	IS_VIDEO_SS6VC3_NUM,
	IS_VIDEO_32O_NUM = 138,	/* ORB DS WDMA */
	IS_VIDEO_32L_NUM,	/* LME DS WDMA */
	IS_VIDEO_PAF0S_NUM = 140,
	IS_VIDEO_PAF1S_NUM,
	IS_VIDEO_PAF2S_NUM,
	IS_VIDEO_PAF3S_NUM,
	IS_VIDEO_32C_NUM = 145,
	IS_VIDEO_32P_NUM,
	IS_VIDEO_32F_NUM,
	IS_VIDEO_32G_NUM,
	IS_VIDEO_33C_NUM = 150,
	IS_VIDEO_33P_NUM,
	IS_VIDEO_33F_NUM,
	IS_VIDEO_33G_NUM = 154,

	/* Logical video node - legacy (~ IS v9.10) */
	IS_VIDEO_LVN_BASE = 155,
	IS_VIDEO_30D_NUM = IS_VIDEO_LVN_BASE,
	IS_VIDEO_31D_NUM,
	IS_VIDEO_32D_NUM,
	IS_VIDEO_33D_NUM,
	IS_VIDEO_30H_NUM,
	IS_VIDEO_31H_NUM = 160,
	IS_VIDEO_32H_NUM,
	IS_VIDEO_33H_NUM,
	IS_VIDEO_IMM_NUM,
	IS_VIDEO_IRG_NUM,
	IS_VIDEO_ISC_NUM,
	IS_VIDEO_IDR_NUM,
	IS_VIDEO_INR_NUM,
	IS_VIDEO_IND_NUM,
	IS_VIDEO_IDG_NUM,
	IS_VIDEO_ISH_NUM = 170,
	IS_VIDEO_IHF_NUM,
	IS_VIDEO_INW_NUM,
	IS_VIDEO_INRW_NUM,
	IS_VIDEO_IRGW_NUM,
	IS_VIDEO_INB_NUM = 175,
	IS_VIDEO_YND_NUM,
	IS_VIDEO_YDG_NUM,
	IS_VIDEO_YSH_NUM,
	IS_VIDEO_YNS_NUM,
	IS_VIDEO_LME1M_NUM = 181,

	/* Logical video node (IS v10.0 ~) */
	IS_LVN_BASE = 200,
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
	IS_LVN_CSTAT0_LME_DS0 = 400,
	IS_LVN_CSTAT0_LME_DS1,
	IS_LVN_CSTAT0_FDPIG,
	IS_LVN_CSTAT0_RGBHIST,
	IS_LVN_CSTAT0_SVHIST,
	IS_LVN_CSTAT0_DRC,
	IS_LVN_CSTAT0_CDS,
	IS_LVN_CSTAT1_LME_DS0 = 410,
	IS_LVN_CSTAT1_LME_DS1,
	IS_LVN_CSTAT1_FDPIG,
	IS_LVN_CSTAT1_RGBHIST,
	IS_LVN_CSTAT1_SVHIST,
	IS_LVN_CSTAT1_DRC,
	IS_LVN_CSTAT1_CDS,
	IS_LVN_CSTAT2_LME_DS0 = 420,
	IS_LVN_CSTAT2_LME_DS1,
	IS_LVN_CSTAT2_FDPIG,
	IS_LVN_CSTAT2_RGBHIST,
	IS_LVN_CSTAT2_SVHIST,
	IS_LVN_CSTAT2_DRC,
	IS_LVN_CSTAT2_CDS,
	IS_LVN_CSTAT3_LME_DS0 = 430,
	IS_LVN_CSTAT3_LME_DS1,
	IS_LVN_CSTAT3_FDPIG,
	IS_LVN_CSTAT3_RGBHIST,
	IS_LVN_CSTAT3_SVHIST,
	IS_LVN_CSTAT3_DRC,
	IS_LVN_CSTAT3_CDS,
	IS_LVN_BYRP_HDR = 440,
	IS_LVN_BYRP_BYR,
	IS_LVN_BYRP_RTA_INFO,
	IS_LVN_RGBP_HF = 450,
	IS_LVN_RGBP_SF,
	IS_LVN_RGBP_YUV,
	IS_LVN_RGBP_RGB,
	IS_LVN_RGBP_RTA_INFO,
	IS_LVN_MCFP_PREV_YUV = 460,
	IS_LVN_MCFP_PREV_W,
	IS_LVN_MCFP_DRC,
	IS_LVN_MCFP_DP,
	IS_LVN_MCFP_MV,
	IS_LVN_MCFP_SF,
	IS_LVN_MCFP_W,
	IS_LVN_MCFP_YUV,
	IS_LVN_MCFP_RTA_INFO,
	IS_LVN_YUVP_SEG = 470,
	IS_LVN_YUVP_DRC,
	IS_LVN_YUVP_CLAHE,
	IS_LVN_YUVP_YUV,
	IS_LVN_YUVP_RTA_INFO,
	IS_LVN_MCSC_P0 = 480,
	IS_VIDEO_M0P_NUM = IS_LVN_MCSC_P0,
	IS_LVN_MCSC_P1,
	IS_VIDEO_M1P_NUM = IS_LVN_MCSC_P1,
	IS_LVN_MCSC_P2,
	IS_VIDEO_M2P_NUM = IS_LVN_MCSC_P2,
	IS_LVN_MCSC_P3,
	IS_VIDEO_M3P_NUM = IS_LVN_MCSC_P3,
	IS_LVN_MCSC_P4,
	IS_VIDEO_M4P_NUM = IS_LVN_MCSC_P4,
	IS_LVN_MCSC_P5,
	IS_VIDEO_M5P_NUM = IS_LVN_MCSC_P5,
	IS_LVN_LME_PREV = 490,
	IS_VIDEO_LME0S_NUM = IS_LVN_LME_PREV,
	IS_LVN_LME_PURE,
	IS_VIDEO_LME0C_NUM = IS_LVN_LME_PURE,
	IS_LVN_LME_PROCESSED,
	IS_VIDEO_LME0M_NUM = IS_LVN_LME_PROCESSED,
	/* 493: Reserved */
	/* 494: Reserved */
	IS_LVN_LME_SAD = 495,
	IS_LVN_LME_PROCESSED_HDR,
	IS_LVN_LME_RTA_INFO,
	IS_VIDEO_MAX_NUM
};

static const char * const vn_name[IS_VIDEO_MAX_NUM + 1] = {
	[IS_VIDEO_COMMON] = "V:CMN",

	[IS_VIDEO_SS0_NUM] = "V:SS0",
	[IS_VIDEO_SS1_NUM] = "V:SS1",
	[IS_VIDEO_SS2_NUM] = "V:SS2",
	[IS_VIDEO_SS3_NUM] = "V:SS3",
	[IS_VIDEO_SS4_NUM] = "V:SS4",
	[IS_VIDEO_SS5_NUM] = "V:SS5",
	[IS_VIDEO_SS6_NUM] = "V:SS6",
	[IS_VIDEO_SS7_NUM] = "V:SS7",
	[IS_VIDEO_SS8_NUM] = "V:SS8",
	[IS_VIDEO_BNS_NUM] = "V:BNS",
	[IS_VIDEO_PRE_NUM] = "V:PRE",

	[IS_VIDEO_CSTAT0] = "V:CSTAT0",
	[IS_VIDEO_CSTAT1] = "V:CSTAT1",
	[IS_VIDEO_CSTAT2] = "V:CSTAT2",
	[IS_VIDEO_CSTAT3] = "V:CSTAT3",

	[IS_VIDEO_BYRP] = "V:BYRP",

	[IS_VIDEO_RGBP] = "V:RGBP",

	[IS_VIDEO_MCFP] = "V:MCFP",

	[IS_VIDEO_YUVP] = "V:YUVP",

	[IS_VIDEO_MCSC0] = "V:MCSC",

	[IS_VIDEO_LME] = "V:LME",

	[IS_VIDEO_SS0VC0_NUM] = "V:S0VC0",
	[IS_VIDEO_SS0VC1_NUM] = "V:S0VC1",
	[IS_VIDEO_SS0VC2_NUM] = "V:S0VC2",
	[IS_VIDEO_SS0VC3_NUM] = "V:S0VC3",
	[IS_VIDEO_SS1VC0_NUM] = "V:S1VC0",
	[IS_VIDEO_SS1VC1_NUM] = "V:S1VC1",
	[IS_VIDEO_SS1VC2_NUM] = "V:S1VC2",
	[IS_VIDEO_SS1VC3_NUM] = "V:S1VC3",
	[IS_VIDEO_SS2VC0_NUM] = "V:S2VC0",
	[IS_VIDEO_SS2VC1_NUM] = "V:S2VC1",
	[IS_VIDEO_SS2VC2_NUM] = "V:S2VC2",
	[IS_VIDEO_SS2VC3_NUM] = "V:S2VC3",
	[IS_VIDEO_SS3VC0_NUM] = "V:S3VC0",
	[IS_VIDEO_SS3VC1_NUM] = "V:S3VC1",
	[IS_VIDEO_SS3VC2_NUM] = "V:S3VC2",
	[IS_VIDEO_SS3VC3_NUM] = "V:S3VC3",
	[IS_VIDEO_SS4VC0_NUM] = "V:S4VC0",
	[IS_VIDEO_SS4VC1_NUM] = "V:S4VC1",
	[IS_VIDEO_SS4VC2_NUM] = "V:S4VC2",
	[IS_VIDEO_SS4VC3_NUM] = "V:S4VC3",
	[IS_VIDEO_SS5VC0_NUM] = "V:S5VC0",
	[IS_VIDEO_SS5VC1_NUM] = "V:S5VC1",
	[IS_VIDEO_SS5VC2_NUM] = "V:S5VC2",
	[IS_VIDEO_SS5VC3_NUM] = "V:S5VC3",
	[IS_VIDEO_SS6VC0_NUM] = "V:S6VC0",
	[IS_VIDEO_SS6VC1_NUM] = "V:S6VC1",
	[IS_VIDEO_SS6VC2_NUM] = "V:S6VC2",
	[IS_VIDEO_SS6VC3_NUM] = "V:S6VC3",

	[IS_VIDEO_PAF0S_NUM] = "V:PDP0",
	[IS_VIDEO_PAF1S_NUM] = "V:PDP1",
	[IS_VIDEO_PAF2S_NUM] = "V:PDP2",
	[IS_VIDEO_PAF3S_NUM] = "V:PDP3",

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

	[IS_LVN_CSTAT0_LME_DS0] = "V:CSTAT0_LMEDS0",
	[IS_LVN_CSTAT0_LME_DS1] = "V:CSTAT0_LMEDS1",
	[IS_LVN_CSTAT0_FDPIG] = "V:CSTAT0_FDPIG",
	[IS_LVN_CSTAT0_RGBHIST] = "V:CSTAT0_RGBH",
	[IS_LVN_CSTAT0_SVHIST] = "V:CSTAT0_SVH",
	[IS_LVN_CSTAT0_DRC] = "V:CSTAT0_DRC",
	[IS_LVN_CSTAT0_CDS] = "V:CSTAT0_CDS",

	[IS_LVN_CSTAT1_LME_DS0] = "V:CSTAT1_LMEDS0",
	[IS_LVN_CSTAT1_LME_DS1] = "V:CSTAT1_LMEDS1",
	[IS_LVN_CSTAT1_FDPIG] = "V:CSTAT1_FDPIG",
	[IS_LVN_CSTAT1_RGBHIST] = "V:CSTAT1_RGBH",
	[IS_LVN_CSTAT1_SVHIST] = "V:CSTAT1_SVH",
	[IS_LVN_CSTAT1_DRC] = "V:CSTAT1_DRC",
	[IS_LVN_CSTAT1_CDS] = "V:CSTAT1_CDS",

	[IS_LVN_CSTAT2_LME_DS0] = "V:CSTAT2_LMEDS0",
	[IS_LVN_CSTAT2_LME_DS1] = "V:CSTAT2_LMEDS1",
	[IS_LVN_CSTAT2_FDPIG] = "V:CSTAT2_FDPIG",
	[IS_LVN_CSTAT2_RGBHIST] = "V:CSTAT2_RGBH",
	[IS_LVN_CSTAT2_SVHIST] = "V:CSTAT2_SVH",
	[IS_LVN_CSTAT2_DRC] = "V:CSTAT2_DRC",
	[IS_LVN_CSTAT2_CDS] = "V:CSTAT2_CDS",

	[IS_LVN_CSTAT3_LME_DS0] = "V:CSTAT3_LMEDS0",
	[IS_LVN_CSTAT3_LME_DS1] = "V:CSTAT3_LMEDS1",
	[IS_LVN_CSTAT3_FDPIG] = "V:CSTAT3_FDPIG",
	[IS_LVN_CSTAT3_RGBHIST] = "V:CSTAT3_RGBH",
	[IS_LVN_CSTAT3_SVHIST] = "V:CSTAT3_SVH",
	[IS_LVN_CSTAT3_DRC] = "V:CSTAT3_DRC",
	[IS_LVN_CSTAT3_CDS] = "V:CSTAT3_CDS",

	[IS_LVN_BYRP_HDR] = "V:BYRP_HDR",
	[IS_LVN_BYRP_BYR] = "V:BYRP_BYR",
	[IS_LVN_BYRP_RTA_INFO] = "V:BYRP_RTA_INFO",

	[IS_LVN_RGBP_HF] = "V:RGBP_HF",
	[IS_LVN_RGBP_SF] = "V:RGBP_SF",
	[IS_LVN_RGBP_YUV] = "V:RGBP_YUV",
	[IS_LVN_RGBP_RGB] = "V:RGBP_RGB",
	[IS_LVN_RGBP_RTA_INFO] = "V:RGBP_RTA_INFO",

	[IS_LVN_MCFP_PREV_YUV] = "V:MCFP_PREV_YUV",
	[IS_LVN_MCFP_PREV_W] = "V:MCFP_PREV_W",
	[IS_LVN_MCFP_DRC] = "V:MCFP_DRC",
	[IS_LVN_MCFP_DP] = "V:MCFP_DP",
	[IS_LVN_MCFP_MV] = "V:MCFP_MV",
	[IS_LVN_MCFP_SF] = "V:MCFP_SF",
	[IS_LVN_MCFP_W] = "V:MCFP_W",
	[IS_LVN_MCFP_YUV] = "V:MCFP_YUV",
	[IS_LVN_MCFP_RTA_INFO] = "V:MCFP_RTA_INFO",

	[IS_LVN_YUVP_SEG] = "V:YUVP_SEG",
	[IS_LVN_YUVP_DRC] = "V:YUVP_DRC",
	[IS_LVN_YUVP_CLAHE] = "V:YUVP_CLAHE",
	[IS_LVN_YUVP_YUV] = "V:YUVP_YUV",
	[IS_LVN_YUVP_RTA_INFO] = "V:YUVP_RTA_INFO",

	[IS_LVN_MCSC_P0] = "V:MCSC_P0",
	[IS_LVN_MCSC_P1] = "V:MCSC_P1",
	[IS_LVN_MCSC_P2] = "V:MCSC_P2",
	[IS_LVN_MCSC_P3] = "V:MCSC_P3",
	[IS_LVN_MCSC_P4] = "V:MCSC_P4",
	[IS_LVN_MCSC_P5] = "V:MCSC_P5",

	[IS_LVN_LME_PREV] = "V:LME_PREV",
	[IS_LVN_LME_PURE] = "V:LME_PURE",
	[IS_LVN_LME_PROCESSED] = "V:LME_PROC",
	[IS_LVN_LME_SAD] = "V:LME_SAD",
	[IS_LVN_LME_PROCESSED_HDR] = "V:LME_PROCESSED_HDR",
	[IS_LVN_LME_RTA_INFO] = "V:LME_RTA_INFO",

	[IS_VIDEO_MAX_NUM] = "V:MAX"
};

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
