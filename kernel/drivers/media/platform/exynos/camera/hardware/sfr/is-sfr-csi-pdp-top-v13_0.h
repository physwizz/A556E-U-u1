/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Samsung Exynos SoC series Pablo IS driver
 *
 * Copyright (c) 2023 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef IS_SFR_CSIS_PDP_TOP_V13_0_H
#define IS_SFR_CSIS_PDP_TOP_V13_0_H

enum csis_top_interrupt_map {
	INTR_CSIS_TOP_MPC_DECODING_DONE_INT = 0,
	INTR_CSIS_TOP_MPC_DECODING_ERR_INT = 1,
	INTR_CSIS_TOP_IBUF_CH0_ERR_INT = 2,
	INTR_CSIS_TOP_IBUF_CH1_ERR_INT = 3,
	INTR_CSIS_TOP_IBUF_CH2_ERR_INT = 4,
	INTR_CSIS_TOP_IBUF_CH3_ERR_INT = 5,
};

#define CSIS_TOP_IBUF_INTR_EN_MASK                                                                 \
	((0) | (1 << INTR_CSIS_TOP_IBUF_CH0_ERR_INT) | (1 << INTR_CSIS_TOP_IBUF_CH1_ERR_INT) |     \
		(1 << INTR_CSIS_TOP_IBUF_CH2_ERR_INT) | (1 << INTR_CSIS_TOP_IBUF_CH3_ERR_INT))

/* CSIS_PDP_TOP */
enum is_csis_pdp_top_reg_id {
	CSIS_PDP_TOP_R_VERSION_ID,
	CSIS_PDP_TOP_R_CSIS_CTRL,
	CSIS_PDP_TOP_R_SW_RESET_APB,
	CSIS_PDP_TOP_R_SW_RESET_CORE,
	CSIS_PDP_TOP_R_MISC,
	CSIS_PDP_TOP_R_MCB_INPUT_MUX_0,
	CSIS_PDP_TOP_R_MCB_OUTPUT_MUX_0,
	CSIS_PDP_TOP_R_MPC_MUX,
	CSIS_PDP_TOP_R_BNS_MUX,
	CSIS_PDP_TOP_R_OTF_IMG_SEL,
	CSIS_PDP_TOP_R_FRO_NORMAL_OUTPUT_CTRL,
	CSIS_PDP_TOP_R_FRO_VOTF_VVALID_N_NORMAL_FLAG_CTRL,
	CSIS_PDP_TOP_R_DMA_MUX0,
	CSIS_PDP_TOP_R_DMA_MUX1,
	CSIS_PDP_TOP_R_DMA_MUX2,
	CSIS_PDP_TOP_R_DMA_MUX3,
	CSIS_PDP_TOP_R_DMA_MUX4,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_PDP0,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_PDP1,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_PDP2,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_PDP3,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_BYRP0,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_BYRP1,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_BYRP2,
	CSIS_PDP_TOP_R_DBG_STALL_CNT_BYRP3,
	CSIS_PDP_TOP_R_HDR_TYPE,
	CSIS_PDP_TOP_R_AEB_NFI,
	CSIS_PDP_TOP_R_VC_CTRL_0,
	CSIS_PDP_TOP_R_MPC_SHIFT,
	CSIS_PDP_TOP_R_MPC_HBLANK,
	CSIS_PDP_TOP_R_CSIS0_EMB_LC_CTRL,
	CSIS_PDP_TOP_R_CSIS1_EMB_LC_CTRL,
	CSIS_PDP_TOP_R_CSIS2_EMB_LC_CTRL,
	CSIS_PDP_TOP_R_CSIS3_EMB_LC_CTRL,
	CSIS_PDP_TOP_R_CSIS4_EMB_LC_CTRL,
	CSIS_PDP_TOP_R_CSIS5_EMB_LC_CTRL,
	CSIS_PDP_TOP_R_CSIS6_EMB_LC_CTRL,
	CSIS_PDP_TOP_R_CSIS0_FRAME_ID_EN,
	CSIS_PDP_TOP_R_CSIS1_FRAME_ID_EN,
	CSIS_PDP_TOP_R_CSIS2_FRAME_ID_EN,
	CSIS_PDP_TOP_R_CSIS3_FRAME_ID_EN,
	CSIS_PDP_TOP_R_CSIS4_FRAME_ID_EN,
	CSIS_PDP_TOP_R_CSIS5_FRAME_ID_EN,
	CSIS_PDP_TOP_R_CSIS6_FRAME_ID_EN,
	CSIS_PDP_TOP_R_CSIS0_NFI_EN,
	CSIS_PDP_TOP_R_CSIS1_NFI_EN,
	CSIS_PDP_TOP_R_CSIS2_NFI_EN,
	CSIS_PDP_TOP_R_CSIS3_NFI_EN,
	CSIS_PDP_TOP_R_CSIS4_NFI_EN,
	CSIS_PDP_TOP_R_CSIS5_NFI_EN,
	CSIS_PDP_TOP_R_CSIS6_NFI_EN,
	CSIS_PDP_TOP_R_CSIS_TOP_INTR_SOURCE,
	CSIS_PDP_TOP_R_CSIS_TOP_INT_ENABLE,
	CSIS_PDP_TOP_R_CSIS_TOP_STATUS,
	CSIS_PDP_TOP_R_NFI_INT_SOURCE_0,
	CSIS_PDP_TOP_R_NFI_INT_ENABLE_0,
	CSIS_PDP_TOP_R_NFI_ACTIVE_SET_CSIS_LINK,
	CSIS_PDP_TOP_R_NFI_ACTIVE_SET_OTF,
	CSIS_PDP_TOP_R_NFI_CTRL_0,
	CSIS_PDP_TOP_R_NFI_SET_OTF_CLR,
	CSIS_PDP_TOP_R_NFI_SET_CSIS_LINK_CLR,
	CSIS_PDP_TOP_R_NFI_INT_SOURCE_1,
	CSIS_PDP_TOP_R_NFI_INT_ENABLE_1,
	CSIS_PDP_TOP_R_NFI_OVERR_CNT,
	CSIS_PDP_TOP_R_VOTF_APB_TOKEN_CTRL,
	CSIS_PDP_TOP_R_VOTF0_TOKEN_INDEX,
	CSIS_PDP_TOP_R_VOTF0_IN_TOKEN_0_TO_3,
	CSIS_PDP_TOP_R_VOTF0_IN_TOKEN_4_TO_7,
	CSIS_PDP_TOP_R_VOTF0_IN_TOKEN_8_TO_11,
	CSIS_PDP_TOP_R_VOTF0_OUT_TOKEN_0_TO_3,
	CSIS_PDP_TOP_R_VOTF0_OUT_TOKEN_4_TO_7,
	CSIS_PDP_TOP_R_VOTF0_OUT_TOKEN_8_TO_11,
	CSIS_PDP_TOP_R_VOTF1_TOKEN_INDEX,
	CSIS_PDP_TOP_R_VOTF1_IN_TOKEN_0_TO_3,
	CSIS_PDP_TOP_R_VOTF1_IN_TOKEN_4_TO_7,
	CSIS_PDP_TOP_R_VOTF1_IN_TOKEN_8_TO_11,
	CSIS_PDP_TOP_R_VOTF1_OUT_TOKEN_0_TO_3,
	CSIS_PDP_TOP_R_VOTF1_OUT_TOKEN_4_TO_7,
	CSIS_PDP_TOP_R_VOTF1_OUT_TOKEN_8_TO_11,
	CSIS_PDP_TOP_REG_CNT,
};

static const struct is_reg is_csis_pdp_top_regs[CSIS_PDP_TOP_REG_CNT] = {
	{ 0x0000, "VERSION_ID" },
	{ 0x0004, "CSIS_CTRL" },
	{ 0x0008, "SW_RESET_APB" },
	{ 0x000c, "SW_RESET_CORE" },
	{ 0x0018, "MISC" },
	{ 0x0200, "MCB_INPUT_MUX_0" },
	{ 0x0204, "MCB_OUTPUT_MUX_0" },
	{ 0x0208, "MPC_MUX" },
	{ 0x020c, "BNS_MUX" },
	{ 0x021c, "OTF_IMG_SEL" },
	{ 0x022c, "FRO_NORMAL_OUTPUT_CTRL" },
	{ 0x0230, "FRO_VOTF_VVALID_N_NORMAL_FLAG_CTRL" },
	{ 0x0240, "DMA_MUX0" },
	{ 0x0244, "DMA_MUX1" },
	{ 0x0248, "DMA_MUX2" },
	{ 0x024c, "DMA_MUX3" },
	{ 0x0250, "DMA_MUX4" },
	{ 0x0254, "DBG_STALL_CNT_PDP0" },
	{ 0x0258, "DBG_STALL_CNT_PDP1" },
	{ 0x025c, "DBG_STALL_CNT_PDP2" },
	{ 0x0260, "DBG_STALL_CNT_PDP3" },
	{ 0x0264, "DBG_STALL_CNT_BYRP0" },
	{ 0x0268, "DBG_STALL_CNT_BYRP1" },
	{ 0x026c, "DBG_STALL_CNT_BYRP2" },
	{ 0x0270, "DBG_STALL_CNT_BYRP3" },
	{ 0x0290, "HDR_TYPE" },
	{ 0x0294, "AEB_NFI" },
	{ 0x0298, "VC_CTRL_0" },
	{ 0x029c, "MPC_SHIFT" },
	{ 0x02a0, "MPC_HBLANK" },
	{ 0x02a4, "CSIS0_EMB_LC_CTRL" },
	{ 0x02a8, "CSIS1_EMB_LC_CTRL" },
	{ 0x02ac, "CSIS2_EMB_LC_CTRL" },
	{ 0x02b0, "CSIS3_EMB_LC_CTRL" },
	{ 0x02b4, "CSIS4_EMB_LC_CTRL" },
	{ 0x02b8, "CSIS5_EMB_LC_CTRL" },
	{ 0x02bc, "CSIS6_EMB_LC_CTRL" },
	{ 0x0400, "CSIS0_FRAME_ID_EN" },
	{ 0x0404, "CSIS1_FRAME_ID_EN" },
	{ 0x0408, "CSIS2_FRAME_ID_EN" },
	{ 0x040c, "CSIS3_FRAME_ID_EN" },
	{ 0x0410, "CSIS4_FRAME_ID_EN" },
	{ 0x0414, "CSIS5_FRAME_ID_EN" },
	{ 0x0418, "CSIS6_FRAME_ID_EN" },
	{ 0x0420, "CSIS0_NFI_EN" },
	{ 0x0424, "CSIS1_NFI_EN" },
	{ 0x0428, "CSIS2_NFI_EN" },
	{ 0x042c, "CSIS3_NFI_EN" },
	{ 0x0430, "CSIS4_NFI_EN" },
	{ 0x0434, "CSIS5_NFI_EN" },
	{ 0x0438, "CSIS6_NFI_EN" },
	{ 0x0500, "CSIS_TOP_INTR_SOURCE" },
	{ 0x0504, "CSIS_TOP_INT_ENABLE" },
	{ 0x0508, "CSIS_TOP_STATUS" },
	{ 0x0800, "NFI_INT_SOURCE_0" },
	{ 0x0804, "NFI_INT_ENABLE_0" },
	{ 0x0808, "NFI_ACTIVE_SET_CSIS_LINK" },
	{ 0x080c, "NFI_ACTIVE_SET_OTF" },
	{ 0x0810, "NFI_CTRL_0" },
	{ 0x0814, "NFI_SET_OTF_CLR" },
	{ 0x0818, "NFI_SET_CSIS_LINK_CLR" },
	{ 0x081c, "NFI_INT_SOURCE_1" },
	{ 0x0820, "NFI_INT_ENABLE_1" },
	{ 0x0824, "NFI_OVERR_CNT" },
	{ 0x0a00, "VOTF_APB_TOKEN_CTRL" },
	{ 0x0a04, "VOTF0_TOKEN_INDEX" },
	{ 0x0a08, "VOTF0_IN_TOKEN_0_TO_3" },
	{ 0x0a0c, "VOTF0_IN_TOKEN_4_TO_7" },
	{ 0x0a10, "VOTF0_IN_TOKEN_8_TO_11" },
	{ 0x0a14, "VOTF0_OUT_TOKEN_0_TO_3" },
	{ 0x0a18, "VOTF0_OUT_TOKEN_4_TO_7" },
	{ 0x0a1c, "VOTF0_OUT_TOKEN_8_TO_11" },
	{ 0x0a20, "VOTF1_TOKEN_INDEX" },
	{ 0x0a24, "VOTF1_IN_TOKEN_0_TO_3" },
	{ 0x0a28, "VOTF1_IN_TOKEN_4_TO_7" },
	{ 0x0a2c, "VOTF1_IN_TOKEN_8_TO_11" },
	{ 0x0a30, "VOTF1_OUT_TOKEN_0_TO_3" },
	{ 0x0a34, "VOTF1_OUT_TOKEN_4_TO_7" },
	{ 0x0a38, "VOTF1_OUT_TOKEN_8_TO_11" },
};

enum is_csis_pdp_top_field_id {
	CSIS_PDP_TOP_F_IP_MICRO,
	CSIS_PDP_TOP_F_IP_MINOR,
	CSIS_PDP_TOP_F_IP_MAJOR,
	CSIS_PDP_TOP_F_QACTIVE_ON,
	CSIS_PDP_TOP_F_IP_PROCESSING,
	CSIS_PDP_TOP_F_SYNC_RESET_ALWAYS_ON,
	CSIS_PDP_TOP_F_DO_NOT_USE_BYRP_FIFO,
	CSIS_PDP_TOP_F_SDW_ENABLE,
	CSIS_PDP_TOP_F_SWRESET_IBUF,
	CSIS_PDP_TOP_F_SWRESET_APB_MPC,
	CSIS_PDP_TOP_F_SWRESET_APB_MCB0,
	CSIS_PDP_TOP_F_SWRESET_APB_MCB1,
	CSIS_PDP_TOP_F_SWRESET_APB_BNS,
	CSIS_PDP_TOP_F_SWRESET_CORE_IBUF,
	CSIS_PDP_TOP_F_SWRESET_CORE_MPC,
	CSIS_PDP_TOP_F_SWRESET_CORE_MCB0,
	CSIS_PDP_TOP_F_SWRESET_CORE_MCB1,
	CSIS_PDP_TOP_F_SWRESET_CORE_BNS,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_BYRP0,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_BYRP1,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_BYRP2,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_BYRP3,
	CSIS_PDP_TOP_F_SWRESET_CORE_FRM_ID_DEC,
	CSIS_PDP_TOP_F_SWRESET_CORE_NFI_DEC0,
	CSIS_PDP_TOP_F_SWRESET_CORE_NFI_DEC1,
	CSIS_PDP_TOP_F_SWRESET_CORE_NFI_DEC2,
	CSIS_PDP_TOP_F_SWRESET_CORE_NFI_DEC3,
	CSIS_PDP_TOP_F_SWRESET_CORE_NFI_DEC4,
	CSIS_PDP_TOP_F_SWRESET_CORE_NFI_DEC5,
	CSIS_PDP_TOP_F_SWRESET_CORE_NFI_DEC6,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_DMA0,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_DMA1,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_DMA2,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_DMA3,
	CSIS_PDP_TOP_F_SWRESET_CORE_ISP2VHD_DMA4,
	CSIS_PDP_TOP_F_MPC_VHVALID_DISABLE,
	CSIS_PDP_TOP_F_EXTEND_NORMAL_FLAG,
	CSIS_PDP_TOP_F_READ_SDW_REG,
	CSIS_PDP_TOP_F_USE_INPUT_NORMAL_OTF,
	CSIS_PDP_TOP_F_IBUF_ERR_INTR_CLR_SW_CTRL_EN,
	CSIS_PDP_TOP_F_IBUF_ERR_MODULE_SWRESET_AUTO_DISABLE,
	CSIS_PDP_TOP_F_NFI_CSIS_MUX_IMMEDIATE_SWITCH,
	CSIS_PDP_TOP_F_DBG_ON,
	CSIS_PDP_TOP_F_BYRP_PATH0_EN_SEL,
	CSIS_PDP_TOP_F_BYRP_PATH1_EN_SEL,
	CSIS_PDP_TOP_F_BYRP_PATH2_EN_SEL,
	CSIS_PDP_TOP_F_BYRP_PATH3_EN_SEL,
	CSIS_PDP_TOP_F_USE_INPUT_NORMAL_DMA,
	CSIS_PDP_TOP_F_GLUEMUX_MCB_INPUT_MUX_SEL_0,
	CSIS_PDP_TOP_F_GLUEMUX_MCB_INPUT_MUX_SEL_1,
	CSIS_PDP_TOP_F_GLUEMUX_MCB_OUTPUT_MUX_SEL_0,
	CSIS_PDP_TOP_F_GLUEMUX_MCB_OUTPUT_MUX_SEL_1,
	CSIS_PDP_TOP_F_GLUEMUX_MCB_OUTPUT_MUX_SEL_2,
	CSIS_PDP_TOP_F_GLUEMUX_MCB_OUTPUT_MUX_SEL_3,
	CSIS_PDP_TOP_F_GLUEMUX_MPC_MUX_SEL,
	CSIS_PDP_TOP_F_GLUEMUX_BNS_MUX_SEL,
	CSIS_PDP_TOP_F_OTF0_IMG_VC_SELECT,
	CSIS_PDP_TOP_F_OTF1_IMG_VC_SELECT,
	CSIS_PDP_TOP_F_OTF2_IMG_VC_SELECT,
	CSIS_PDP_TOP_F_OTF3_IMG_VC_SELECT,
	CSIS_PDP_TOP_F_DMA_NORMAL_FLAG_CTRL,
	CSIS_PDP_TOP_F_PDP_PATH_NORMAL_FLAG_EN,
	CSIS_PDP_TOP_F_PDP_PATH_VOTF_VVALID_EN,
	CSIS_PDP_TOP_F_BYRP_PATH_NORMAL_FLAG_EN,
	CSIS_PDP_TOP_F_BYRP_PATH_VOTF_VVALID_EN,
	CSIS_PDP_TOP_F_GLUEMUX_DMA_MUX_SELX,
	CSIS_PDP_TOP_F_STALL_COUNTER_OTF_OUTPUT_X,
	CSIS_PDP_TOP_F_OVERLAP_HDR,
	CSIS_PDP_TOP_F_AEB_MASK_EN,
	CSIS_PDP_TOP_F_IBUF0,
	CSIS_PDP_TOP_F_IBUF1,
	CSIS_PDP_TOP_F_IBUF2,
	CSIS_PDP_TOP_F_IBUF3,
	CSIS_PDP_TOP_F_LEFT_SHIFT_2BIT,
	CSIS_PDP_TOP_F_LEFT_SHIFT_4BIT,
	CSIS_PDP_TOP_F_SET_EN,
	CSIS_PDP_TOP_F_SIZE,
	CSIS_PDP_TOP_F_CSISX_EMB_LOCH_ID,
	CSIS_PDP_TOP_F_CSISX_FRAME_ID_EN_CSIS,
	CSIS_PDP_TOP_F_CSISX_FID_LOC_LINE,
	CSIS_PDP_TOP_F_CSISX_FID_LOC_BYTE,
	CSIS_PDP_TOP_F_CSISX_NFI_EN_CSIS,
	CSIS_PDP_TOP_F_CSISX_NFI_LOC_LINE,
	CSIS_PDP_TOP_F_CSISX_NFI_LOC_BYTE,
	CSIS_PDP_TOP_F_INTR_SOURCE,
	CSIS_PDP_TOP_F_INTR_ENABLE,
	CSIS_PDP_TOP_F_TOP_STATUS,
	CSIS_PDP_TOP_F_NFI_INT_SRC_0_TO_3,
	CSIS_PDP_TOP_F_NFI_INT_EN_0_TO_3,
	CSIS_PDP_TOP_F_NFI_CSIS_LINK_SET_INFO,
	CSIS_PDP_TOP_F_NFI_OTF_SET0,
	CSIS_PDP_TOP_F_NFI_OTF_SET1,
	CSIS_PDP_TOP_F_NFI_OTF_SET2,
	CSIS_PDP_TOP_F_NFI_OTF_SET3,
	CSIS_PDP_TOP_F_SW_TRIGGER,
	CSIS_PDP_TOP_F_NFI_OTF_SET0_CLR,
	CSIS_PDP_TOP_F_NFI_OTF_SET1_CLR,
	CSIS_PDP_TOP_F_NFI_OTF_SET2_CLR,
	CSIS_PDP_TOP_F_NFI_OTF_SET3_CLR,
	CSIS_PDP_TOP_F_NFI_CSIS_LINK_SET_CLR,
	CSIS_PDP_TOP_F_NFI_INT_SRC_4_TO_6,
	CSIS_PDP_TOP_F_NFI_INT_EN_4_TO_6,
	CSIS_PDP_TOP_F_CSIS0_NFI_OVERRIDE_CNT,
	CSIS_PDP_TOP_F_CSIS1_NFI_OVERRIDE_CNT,
	CSIS_PDP_TOP_F_CSIS2_NFI_OVERRIDE_CNT,
	CSIS_PDP_TOP_F_CSIS3_NFI_OVERRIDE_CNT,
	CSIS_PDP_TOP_F_CSIS4_NFI_OVERRIDE_CNT,
	CSIS_PDP_TOP_F_CSIS5_NFI_OVERRIDE_CNT,
	CSIS_PDP_TOP_F_CSIS6_NFI_OVERRIDE_CNT,
	CSIS_PDP_TOP_F_VOTF0_AXI_EN,
	CSIS_PDP_TOP_F_VOTF0_APB_EN,
	CSIS_PDP_TOP_F_VOTF1_AXI_EN,
	CSIS_PDP_TOP_F_VOTF1_APB_EN,
	CSIS_PDP_TOP_F_TOKEN_INDEX,
	CSIS_PDP_TOP_F_IN_TOKEN_0_3,
	CSIS_PDP_TOP_F_OUT_TOKEN_0_3,
	CSIS_PDP_TOP_FIELD_CNT,
};

static const struct is_field is_csis_pdp_top_fields[CSIS_PDP_TOP_FIELD_CNT] = {
	{ "IP_MICRO", 0, 16, RO, 0x0000 },
	{ "IP_MINOR", 16, 8, RO, 0x00 },
	{ "IP_MAJOR", 24, 8, RO, 0x0D },
	{ "QACTIVE_ON", 0, 1, RW, 0x0 },
	{ "IP_PROCESSING", 1, 1, RW, 0x0 },
	{ "SYNC_RESET_ALWAYS_ON", 8, 1, RW, 0x0 },
	{ "DO_NOT_USE_BYRP_FIFO", 16, 1, RW, 0x0 },
	{ "SDW_ENABLE", 20, 1, RW, 0x0 },
	{ "SWRESET_IBUF", 0, 1, WO, 0x0 },
	{ "SWRESET_APB_MPC", 1, 1, WO, 0x0 },
	{ "SWRESET_APB_MCB0", 2, 1, WO, 0x0 },
	{ "SWRESET_APB_MCB1", 3, 1, WO, 0x0 },
	{ "SWRESET_APB_BNS", 4, 1, WO, 0x0 },
	{ "SWRESET_CORE_IBUF", 0, 1, WO, 0x0 },
	{ "SWRESET_CORE_MPC", 1, 1, WO, 0x0 },
	{ "SWRESET_CORE_MCB0", 2, 1, WO, 0x0 },
	{ "SWRESET_CORE_MCB1", 3, 1, WO, 0x0 },
	{ "SWRESET_CORE_BNS", 4, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_BYRP0", 7, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_BYRP1", 8, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_BYRP2", 9, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_BYRP3", 10, 1, WO, 0x0 },
	{ "SWRESET_CORE_FRM_ID_DEC", 12, 1, WO, 0x0 },
	{ "SWRESET_CORE_NFI_DEC0", 13, 1, WO, 0x0 },
	{ "SWRESET_CORE_NFI_DEC1", 14, 1, WO, 0x0 },
	{ "SWRESET_CORE_NFI_DEC2", 15, 1, WO, 0x0 },
	{ "SWRESET_CORE_NFI_DEC3", 16, 1, WO, 0x0 },
	{ "SWRESET_CORE_NFI_DEC4", 17, 1, WO, 0x0 },
	{ "SWRESET_CORE_NFI_DEC5", 18, 1, WO, 0x0 },
	{ "SWRESET_CORE_NFI_DEC6", 19, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_DMA0", 20, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_DMA1", 21, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_DMA2", 22, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_DMA3", 23, 1, WO, 0x0 },
	{ "SWRESET_CORE_ISP2VHD_DMA4", 24, 1, WO, 0x0 },
	{ "MPC_VHVALID_DISABLE", 0, 1, RW, 0x0 },
	{ "EXTEND_NORMAL_FLAG", 1, 1, RW, 0x0 },
	{ "READ_SDW_REG", 2, 1, RW, 0x0 },
	{ "USE_INPUT_NORMAL_OTF", 3, 1, RW, 0x0 },
	{ "IBUF_ERR_INTR_CLR_SW_CTRL_EN", 4, 1, RW, 0x0 },
	{ "IBUF_ERR_MODULE_SWRESET_AUTO_DISABLE", 5, 1, RW, 0x0 },
	{ "NFI_CSIS_MUX_IMMEDIATE_SWITCH", 6, 1, RW, 0x0 },
	{ "DBG_ON", 7, 1, RW, 0x0 },
	{ "BYRP_PATH0_EN_SEL", 8, 1, RW, 0x1 },
	{ "BYRP_PATH1_EN_SEL", 9, 1, RW, 0x1 },
	{ "BYRP_PATH2_EN_SEL", 10, 1, RW, 0x1 },
	{ "BYRP_PATH3_EN_SEL", 11, 1, RW, 0x1 },
	{ "USE_INPUT_NORMAL_DMA", 31, 1, RW, 0x1 },
	{ "GLUEMUX_MCB_INPUT_MUX_SEL_0", 0, 2, RW, 0x0 },
	{ "GLUEMUX_MCB_INPUT_MUX_SEL_1", 4, 2, RW, 0x0 },
	{ "GLUEMUX_MCB_OUTPUT_MUX_SEL_0", 0, 3, RW, 0x4 },
	{ "GLUEMUX_MCB_OUTPUT_MUX_SEL_1", 4, 3, RW, 0x5 },
	{ "GLUEMUX_MCB_OUTPUT_MUX_SEL_2", 8, 3, RW, 0x6 },
	{ "GLUEMUX_MCB_OUTPUT_MUX_SEL_3", 12, 3, RW, 0x7 },
	{ "GLUEMUX_MPC_MUX_SEL", 0, 2, RW, 0x0 },
	{ "GLUEMUX_BNS_MUX_SEL", 0, 2, RW, 0x0 },
	{ "OTF0_IMG_VC_SELECT", 0, 4, RW, 0x0 },
	{ "OTF1_IMG_VC_SELECT", 4, 4, RW, 0x0 },
	{ "OTF2_IMG_VC_SELECT", 8, 4, RW, 0x0 },
	{ "OTF3_IMG_VC_SELECT", 12, 4, RW, 0x0 },
	{ "DMA_NORMAL_FLAG_CTRL", 0, 5, RW, 0x00 },
	{ "PDP_PATH_NORMAL_FLAG_EN", 0, 4, RW, 0x0 },
	{ "PDP_PATH_VOTF_VVALID_EN", 4, 4, RW, 0x0 },
	{ "BYRP_PATH_NORMAL_FLAG_EN", 8, 4, RW, 0x0 },
	{ "BYRP_PATH_VOTF_VVALID_EN", 12, 4, RW, 0x0 },
	{ "GLUEMUX_DMA_MUX_SELX", 0, 6, RW, 0x00 },
	{ "STALL_COUNTER_OTF_OUTPUT_X", 0, 32, RO, 0x00000000 },
	{ "OVERLAP_HDR", 0, 7, RW, 0x00 },
	{ "AEB_MASK_EN", 0, 7, RW, 0x00 },
	{ "IBUF0", 0, 6, RW, 0x3F },
	{ "IBUF1", 8, 6, RW, 0x3F },
	{ "IBUF2", 16, 6, RW, 0x3F },
	{ "IBUF3", 24, 6, RW, 0x3F },
	{ "LEFT_SHIFT_2BIT", 0, 1, RW, 0x0 },
	{ "LEFT_SHIFT_4BIT", 1, 1, RW, 0x0 },
	{ "SET_EN", 0, 1, RW, 0x0 },
	{ "SIZE", 8, 14, RW, 0x0000 },
	{ "CSISX_EMB_LOCH_ID", 0, 5, RW, 0x02 },
	{ "CSISX_FRAME_ID_EN_CSIS", 0, 1, RW, 0x0 },
	{ "CSISX_FID_LOC_LINE", 8, 2, RW, 0x0 },
	{ "CSISX_FID_LOC_BYTE", 16, 16, RW, 0x0000 },
	{ "CSISX_NFI_EN_CSIS", 0, 1, RW, 0x0 },
	{ "CSISX_NFI_LOC_LINE", 8, 2, RW, 0x0 },
	{ "CSISX_NFI_LOC_BYTE", 16, 16, RW, 0x0000 },
	{ "INTR_SOURCE", 0, 32, RW, 0x00000000 },
	{ "INTR_ENABLE", 0, 32, RW, 0x00000000 },
	{ "TOP_STATUS", 0, 32, RO, 0x00000000 },
	{ "NFI_INT_SRC_0_TO_3", 0, 32, RW, 0x00000000 },
	{ "NFI_INT_EN_0_TO_3", 0, 32, RW, 0x00000000 },
	{ "NFI_CSIS_LINK_SET_INFO", 0, 7, RO, 0x00 },
	{ "NFI_OTF_SET0", 0, 1, RO, 0x0 },
	{ "NFI_OTF_SET1", 8, 1, RO, 0x0 },
	{ "NFI_OTF_SET2", 16, 1, RO, 0x0 },
	{ "NFI_OTF_SET3", 24, 1, RO, 0x0 },
	{ "SW_TRIGGER", 0, 7, RW, 0x00 },
	{ "NFI_OTF_SET0_CLR", 0, 1, RW, 0x0 },
	{ "NFI_OTF_SET1_CLR", 8, 1, RW, 0x0 },
	{ "NFI_OTF_SET2_CLR", 16, 1, RW, 0x0 },
	{ "NFI_OTF_SET3_CLR", 24, 1, RW, 0x0 },
	{ "NFI_CSIS_LINK_SET_CLR", 0, 7, RW, 0x00 },
	{ "NFI_INT_SRC_4_TO_6", 0, 17, RW, 0x00000 },
	{ "NFI_INT_EN_4_TO_6", 0, 17, RW, 0x00000 },
	{ "CSIS0_NFI_OVERRIDE_CNT", 0, 1, RW, 0x0 },
	{ "CSIS1_NFI_OVERRIDE_CNT", 1, 1, RW, 0x0 },
	{ "CSIS2_NFI_OVERRIDE_CNT", 2, 1, RW, 0x0 },
	{ "CSIS3_NFI_OVERRIDE_CNT", 3, 1, RW, 0x0 },
	{ "CSIS4_NFI_OVERRIDE_CNT", 4, 1, RW, 0x0 },
	{ "CSIS5_NFI_OVERRIDE_CNT", 5, 1, RW, 0x0 },
	{ "CSIS6_NFI_OVERRIDE_CNT", 6, 1, RW, 0x0 },
	{ "VOTF0_AXI_EN", 0, 1, RW, 0x0 },
	{ "VOTF0_APB_EN", 4, 1, RW, 0x0 },
	{ "VOTF1_AXI_EN", 8, 1, RW, 0x0 },
	{ "VOTF1_APB_EN", 12, 1, RW, 0x0 },
	{ "TOKEN_INDEX", 0, 32, RO, 0x00000000 },
	{ "IN_TOKEN_0_3", 0, 32, RO, 0x00000000 },
	{ "OUT_TOKEN_0_3", 0, 32, RO, 0x00000000 },
};

/* CSIS_IBUF */
#define CSIS_IBUF_CH_NUM 4
#define CSIS_IBUF_CR_OFFSET 0x100

enum is_csis_ibuf_reg_id {
	CSIS_IBUF_R_IBUFX_INPUT_CONFIG_CNTL_0,
	CSIS_IBUF_R_IBUFX_INPUT_CONFIG_CNTL_1,
	CSIS_IBUF_R_IBUFX_INPUT_CONFIG_CNTL_2,
	CSIS_IBUF_R_IBUFX_MEM_USAGE,
	CSIS_IBUF_R_IBUFX_PTRN_CONFIG_0,
	CSIS_IBUF_R_IBUFX_PTRN_CONFIG_1,
	CSIS_IBUF_R_IBUFX_PTRN_CONFIG_2,
	CSIS_IBUF_R_IBUFX_PTRN_CONFIG_3,
	CSIS_IBUF_R_IBUFX_PTRN_CONFIG_4,
	CSIS_IBUF_R_IBUFX_PTRN_CONFIG_5,
	CSIS_IBUF_R_IBUFX_ERR_CONFIG_0,
	CSIS_IBUF_R_IBUFX_ERR_CONFIG_1,
	CSIS_IBUF_R_IBUFX_DEBUG_STALL_CNT,
	CSIS_IBUF_R_IBUFX_DEBUG_IN_CNT_A0,
	CSIS_IBUF_R_IBUFX_DEBUG_IN_CNT_A1,
	CSIS_IBUF_R_IBUFX_DEBUG_IN_CNT_B0,
	CSIS_IBUF_R_IBUFX_DEBUG_IN_CNT_B1,
	CSIS_IBUF_R_IBUFX_DEBUG_OUT_CNT_A0,
	CSIS_IBUF_R_IBUFX_DEBUG_OUT_CNT_A1,
	CSIS_IBUF_R_IBUFX_DEBUG_OUT_CNT_B0,
	CSIS_IBUF_R_IBUFX_DEBUG_OUT_CNT_B1,
	CSIS_IBUF_R_IBUFX_INPUT_MASKING,
	CSIS_IBUF_R_IBUFX_ERR_RECORD_0,
	CSIS_IBUF_R_IBUFX_ERR_RECORD_1,
	CSIS_IBUF_REG_CNT,
};

static const struct is_reg is_csis_ibuf_regs[CSIS_IBUF_REG_CNT] = {
	{ 0x2000, "IBUFX_INPUT_CONFIG_CNTL_0" },
	{ 0x2004, "IBUFX_INPUT_CONFIG_CNTL_1" },
	{ 0x2008, "IBUFX_INPUT_CONFIG_CNTL_2" },
	{ 0x200c, "IBUFX_MEM_USAGE" },
	{ 0x2010, "IBUFX_PTRN_CONFIG_0" },
	{ 0x2014, "IBUFX_PTRN_CONFIG_1" },
	{ 0x2018, "IBUFX_PTRN_CONFIG_2" },
	{ 0x201c, "IBUFX_PTRN_CONFIG_3" },
	{ 0x2020, "IBUFX_PTRN_CONFIG_4" },
	{ 0x2024, "IBUFX_PTRN_CONFIG_5" },
	{ 0x2030, "IBUFX_ERR_CONFIG_0" },
	{ 0x2034, "IBUFX_ERR_CONFIG_1" },
	{ 0x2038, "IBUFX_DEBUG_STALL_CNT" },
	{ 0x2040, "IBUFX_DEBUG_IN_CNT_A0" },
	{ 0x2044, "IBUFX_DEBUG_IN_CNT_A1" },
	{ 0x2048, "IBUFX_DEBUG_IN_CNT_B0" },
	{ 0x204c, "IBUFX_DEBUG_IN_CNT_B1" },
	{ 0x2050, "IBUFX_DEBUG_OUT_CNT_A0" },
	{ 0x2054, "IBUFX_DEBUG_OUT_CNT_A1" },
	{ 0x2058, "IBUFX_DEBUG_OUT_CNT_B0" },
	{ 0x205c, "IBUFX_DEBUG_OUT_CNT_B1" },
	{ 0x20c0, "IBUFX_INPUT_MASKING" },
	{ 0x20c4, "IBUFX_ERR_RECORD_0" },
	{ 0x20c8, "IBUFX_ERR_RECORD_1" },
};

#define CSIS_IBUF_LC_NUM 6
#define CSIS_IBUF_LC_CR_OFFSET 0x10
enum is_csis_ibuf_lc_reg_id {
	CSIS_IBUF_R_IBUFX_INPUT_CONFIG_LCX_0,
	CSIS_IBUF_R_IBUFX_INPUT_CONFIG_LCX_1,
	CSIS_IBUF_LC_REG_CNT,
};

static const struct is_reg is_csis_ibuf_lc_regs[CSIS_IBUF_LC_REG_CNT] = {
	{ 0x2060, "IBUFX_INPUT_CONFIG_LCX_0" },
	{ 0x2064, "IBUFX_INPUT_CONFIG_LCX_1" },
};

enum is_csis_ibuf_cmn_reg_id {
	CSIS_IBUF_CMN_R_IBUF_MUX0,
	CSIS_IBUF_CMN_R_IBUF_MUX1,
	CSIS_IBUF_CMN_R_IBUF_MUX2,
	CSIS_IBUF_CMN_R_IBUF_MUX3,
	CSIS_IBUF_CMN_REG_CNT,
};

static const struct is_reg is_csis_ibuf_cmn_regs[CSIS_IBUF_CMN_REG_CNT] = {
	{ 0x4000, "IBUF_MUX0" },
	{ 0x4004, "IBUF_MUX1" },
	{ 0x4008, "IBUF_MUX2" },
	{ 0x400c, "IBUF_MUX3" },
};

enum is_csis_ibuf_field_id {
	CSIS_IBUF_F_DEBUG_ON,
	CSIS_IBUF_F_DEBUG_LOCH_A,
	CSIS_IBUF_F_DEBUG_LOCH_B,
	CSIS_IBUF_F_STUCK_DETECT,
	CSIS_IBUF_F_OUT_H2H_BLANK,
	CSIS_IBUF_F_OUT_V2V_BLANK,
	CSIS_IBUF_F_STUCK_PERIOD,
	CSIS_IBUF_F_MEM_USAGE,
	CSIS_IBUF_F_PTRN_GEN_ON,
	CSIS_IBUF_F_PTRN_FRAME_CNT,
	CSIS_IBUF_F_PTRN_SENSOR_SYNC,
	CSIS_IBUF_F_PTRN_DATA_TYPE,
	CSIS_IBUF_F_PTRN_BITMODE,
	CSIS_IBUF_F_PTRN_PD_ON,
	CSIS_IBUF_F_PTRN_PD_LOCH_ID,
	CSIS_IBUF_F_PTRN_PD_H,
	CSIS_IBUF_F_PTRN_PD_V,
	CSIS_IBUF_F_PTRN_WIDTH,
	CSIS_IBUF_F_PTRN_HEIGHT,
	CSIS_IBUF_F_PTRN_D2D_BLANK,
	CSIS_IBUF_F_PTRN_H2H_BLANK,
	CSIS_IBUF_F_PTRN_V2V_BLANK,
	CSIS_IBUF_F_ERR_OVERFLOW,
	CSIS_IBUF_F_ERR_STUCK,
	CSIS_IBUF_F_ERR_PROTOCOL,
	CSIS_IBUF_F_ERR_LOCH,
	CSIS_IBUF_F_MEM_PERCENT,
	CSIS_IBUF_F_ERR_HCNT,
	CSIS_IBUF_F_ERR_VCNT,
	CSIS_IBUF_F_STALL_CNT,
	CSIS_IBUF_F_DEBUG_HCNT,
	CSIS_IBUF_F_DEBUG_VCNT,
	CSIS_IBUF_F_DEBUG_FCNT,
	CSIS_IBUF_F_WIDTH_LCX,
	CSIS_IBUF_F_HEIGHT_LCX,
	CSIS_IBUF_F_OTF_EN_LCX,
	CSIS_IBUF_F_BITMODE_LCX,
	CSIS_IBUF_F_ERR_CHECK_ON_LCX,
	CSIS_IBUF_F_USER_EMB_LCX,
	CSIS_IBUF_F_INTR_INPUT_MASK_ON,
	CSIS_IBUF_F_INTR_INPUT_MASK_CLR,
	CSIS_IBUF_F_ERR_STATUS_RECORD_CLR,
	CSIS_IBUF_F_ERR_RCD_OVERFLOW,
	CSIS_IBUF_F_ERR_RCD_STUCK,
	CSIS_IBUF_F_ERR_RCD_PROTOCOL,
	CSIS_IBUF_F_ERR_RCD_LOCH,
	CSIS_IBUF_F_ERR_RCD_HCNT,
	CSIS_IBUF_F_ERR_RCD_VCNT,
	CSIS_IBUF_F_GLUEMUX_IBUF_MUX_SELX,
	CSIS_IBUF_FIELD_CNT,
};

static const struct is_field is_csis_ibuf_fields[CSIS_IBUF_FIELD_CNT] = {
	{ "DEBUG_ON", 0, 1, RW, 0x0 },
	{ "DEBUG_LOCH_A", 4, 3, RW, 0x0 },
	{ "DEBUG_LOCH_B", 8, 3, RW, 0x1 },
	{ "STUCK_DETECT", 12, 1, RW, 0x0 },
	{ "OUT_H2H_BLANK", 16, 16, RW, 0x0040 },
	{ "OUT_V2V_BLANK", 0, 32, RW, 0x00000200 },
	{ "STUCK_PERIOD", 0, 32, RW, 0x3FFFFFFF },
	{ "MEM_USAGE", 0, 7, RW, 0x64 },
	{ "PTRN_GEN_ON", 0, 1, RW, 0x0 },
	{ "PTRN_FRAME_CNT", 0, 6, RW, 0x01 },
	{ "PTRN_SENSOR_SYNC", 8, 1, RW, 0x0 },
	{ "PTRN_DATA_TYPE", 12, 3, RW, 0x0 },
	{ "PTRN_BITMODE", 16, 2, RW, 0x1 },
	{ "PTRN_PD_ON", 0, 1, RW, 0x0 },
	{ "PTRN_PD_LOCH_ID", 4, 3, RW, 0x1 },
	{ "PTRN_PD_H", 8, 2, RW, 0x1 },
	{ "PTRN_PD_V", 12, 2, RW, 0x1 },
	{ "PTRN_WIDTH", 0, 16, RW, 0x0100 },
	{ "PTRN_HEIGHT", 16, 16, RW, 0x0040 },
	{ "PTRN_D2D_BLANK", 0, 4, RW, 0x0 },
	{ "PTRN_H2H_BLANK", 16, 16, RW, 0x0100 },
	{ "PTRN_V2V_BLANK", 0, 32, RW, 0x00000200 },
	{ "ERR_OVERFLOW", 0, 1, RO, 0x0 },
	{ "ERR_STUCK", 4, 1, RO, 0x0 },
	{ "ERR_PROTOCOL", 8, 1, RO, 0x0 },
	{ "ERR_LOCH", 16, 3, RO, 0x0 },
	{ "MEM_PERCENT", 24, 7, RO, 0x00 },
	{ "ERR_HCNT", 0, 16, RO, 0x0000 },
	{ "ERR_VCNT", 16, 16, RO, 0x0000 },
	{ "STALL_CNT", 0, 32, RO, 0x00000000 },
	{ "DEBUG_HCNT", 0, 16, RO, 0x0000 },
	{ "DEBUG_VCNT", 16, 16, RO, 0x0000 },
	{ "DEBUG_FCNT", 0, 16, RO, 0x0000 },
	{ "WIDTH_LCX", 0, 16, RW, 0x0100 },
	{ "HEIGHT_LCX", 16, 16, RW, 0x0040 },
	{ "OTF_EN_LCX", 0, 1, RW, 0x0 },
	{ "BITMODE_LCX", 4, 2, RW, 0x1 },
	{ "ERR_CHECK_ON_LCX", 8, 1, RW, 0x1 },
	{ "USER_EMB_LCX", 12, 1, RW, 0x0 },
	{ "INTR_INPUT_MASK_ON", 0, 1, RW, 0x0 },
	{ "INTR_INPUT_MASK_CLR", 4, 1, RW, 0x0 },
	{ "ERR_STATUS_RECORD_CLR", 8, 1, RW, 0x0 },
	{ "ERR_RCD_OVERFLOW", 0, 1, RO, 0x0 },
	{ "ERR_RCD_STUCK", 4, 1, RO, 0x0 },
	{ "ERR_RCD_PROTOCOL", 8, 1, RO, 0x0 },
	{ "ERR_RCD_LOCH", 16, 3, RO, 0x0 },
	{ "ERR_RCD_HCNT", 0, 16, RO, 0x0000 },
	{ "ERR_RCD_VCNT", 16, 16, RO, 0x0000 },
	{ "GLUEMUX_IBUF_MUX_SELX", 0, 6, RW, 0x00 },
};

/* CSIS_MPC */
enum is_csis_mpc_reg_id {
	CSIS_MPC_R_BYPASS,
	CSIS_MPC_R_INTP_MASK,
	CSIS_MPC_R_INTP_PEND,
	CSIS_MPC_R_PIXEL_ORDER,
	CSIS_MPC_R_OP_MODE,
	CSIS_MPC_R_COMP_RATIO,
	CSIS_MPC_R_BIT_IND,
	CSIS_MPC_R_PREVIEW_EN,
	CSIS_MPC_R_POWER_SAVE_MODE,
	CSIS_MPC_R_SAT_MODE_EN,
	CSIS_MPC_R_SAT_REF_VALUE,
	CSIS_MPC_R_SAT_RANGE,
	CSIS_MPC_R_FIX_REF0,
	CSIS_MPC_R_FIX_REF1,
	CSIS_MPC_R_FIX_REF2,
	CSIS_MPC_R_FIX_REF3,
	CSIS_MPC_R_BP_EN,
	CSIS_MPC_R_BP_SAT_EN,
	CSIS_MPC_R_BP_THRESH,
	CSIS_MPC_R_BP_LOW_THRESH,
	CSIS_MPC_R_BP_LOW_AROUND,
	CSIS_MPC_R_BASE_VALUE0,
	CSIS_MPC_R_BASE_VALUE1,
	CSIS_MPC_R_BASE_VALUE2,
	CSIS_MPC_R_BASE_VALUE3,
	CSIS_MPC_R_IMAGE_WIDTH,
	CSIS_MPC_R_IMAGE_HEIGHT,
	CSIS_MPC_R_LFSR_SEED,
	CSIS_MPC_R_FIFO_DEPTH,
	CSIS_MPC_R_HBLANK_CNT,
	CSIS_MPC_R_EMBDD_SEL,
	CSIS_MPC_R_BLOCK_ID_CODE,
	CSIS_MPC_R_STREAM_CRC,
	CSIS_MPC_REG_CNT,
};

static const struct is_reg is_csis_mpc_regs[CSIS_MPC_REG_CNT] = {
	{ 0x8000, "MPC_BYPASS" },
	{ 0x8004, "MPC_INTP_MASK" },
	{ 0x8008, "MPC_INTP_PEND" },
	{ 0x800c, "MPC_PIXEL_ORDER" },
	{ 0x8010, "MPC_OP_MODE" },
	{ 0x8014, "MPC_COMP_RATIO" },
	{ 0x8018, "MPC_BIT_IND" },
	{ 0x801c, "MPC_PREVIEW_EN" },
	{ 0x8020, "MPC_POWER_SAVE_MODE" },
	{ 0x8024, "MPC_SAT_MODE_EN" },
	{ 0x8028, "MPC_SAT_REF_VALUE" },
	{ 0x802c, "MPC_SAT_RANGE" },
	{ 0x8030, "MPC_FIX_REF0" },
	{ 0x8034, "MPC_FIX_REF1" },
	{ 0x8038, "MPC_FIX_REF2" },
	{ 0x803c, "MPC_FIX_REF3" },
	{ 0x8040, "MPC_BP_EN" },
	{ 0x8044, "MPC_BP_SAT_EN" },
	{ 0x8048, "MPC_BP_THRESH" },
	{ 0x804c, "MPC_BP_LOW_THRESH" },
	{ 0x8050, "MPC_BP_LOW_AROUND" },
	{ 0x8054, "MPC_BASE_VALUE0" },
	{ 0x8058, "MPC_BASE_VALUE1" },
	{ 0x805c, "MPC_BASE_VALUE2" },
	{ 0x8060, "MPC_BASE_VALUE3" },
	{ 0x8064, "MPC_IMAGE_WIDTH" },
	{ 0x8068, "MPC_IMAGE_HEIGHT" },
	{ 0x806c, "MPC_LFSR_SEED" },
	{ 0x8070, "MPC_FIFO_DEPTH" },
	{ 0x8074, "MPC_HBLANK_CNT" },
	{ 0x8078, "MPC_EMBDD_SEL" },
	{ 0x80f8, "MPC_BLOCK_ID_CODE" },
	{ 0x80fc, "MPC_STREAM_CRC" },
};

enum is_csis_mpc_field_id {
	CSIS_MPC_F_BYPASS,
	CSIS_MPC_F_INTP_MASK_DEC_DONE,
	CSIS_MPC_F_INTP_MASK_HTIME_ERROR,
	CSIS_MPC_F_INTP_MASK_SIZE_MISMATCH,
	CSIS_MPC_F_INTP_PEND_DEC_DONE,
	CSIS_MPC_F_INTP_PEND_HTIME_ERROR,
	CSIS_MPC_F_INTP_PEND_SIZE_MISMATCH,
	CSIS_MPC_F_PIXEL_ORDER,
	CSIS_MPC_F_OP_MODE,
	CSIS_MPC_F_COMP_RATIO,
	CSIS_MPC_F_BIT_IND,
	CSIS_MPC_F_PREVIEW_EN,
	CSIS_MPC_F_POWER_SAVE_EN,
	CSIS_MPC_F_SAT_MODE_EN,
	CSIS_MPC_F_SAT_REF_VALUE,
	CSIS_MPC_F_SAT_RANGE,
	CSIS_MPC_F_FIX_REF0,
	CSIS_MPC_F_FIX_REF1,
	CSIS_MPC_F_FIX_REF2,
	CSIS_MPC_F_FIX_REF3,
	CSIS_MPC_F_BP_EN,
	CSIS_MPC_F_BP_SAT_EN,
	CSIS_MPC_F_BP_THRESH,
	CSIS_MPC_F_BP_LOW_THRESH,
	CSIS_MPC_F_BP_LOW_AROUND,
	CSIS_MPC_F_BASE_VALUEX,
	CSIS_MPC_F_IMAGE_WIDTH,
	CSIS_MPC_F_IMAGE_HEIGHT,
	CSIS_MPC_F_LFSR_SEED,
	CSIS_MPC_F_FIFO_DEPTH,
	CSIS_MPC_F_HBLANK_CNT,
	CSIS_MPC_F_EMBDD_SEL,
	CSIS_MPC_F_BLOCK_ID_CODE,
	CSIS_MPC_F_CRC_SEED,
	CSIS_MPC_F_CRC_RESULT,
	CSIS_MPC_FIELD_CNT,
};

static const struct is_field is_csis_mpc_fields[CSIS_MPC_FIELD_CNT] = {
	{ "BYPASS", 0, 1, RW, 0x1 },
	{ "INTP_MASK_DEC_DONE", 0, 1, RW, 0x1 },
	{ "INTP_MASK_HTIME_ERROR", 1, 1, RW, 0x1 },
	{ "INTP_MASK_SIZE_MISMATCH", 2, 1, RW, 0x1 },
	{ "INTP_PEND_DEC_DONE", 0, 1, RW, 0x0 },
	{ "INTP_PEND_HTIME_ERROR", 1, 1, RW, 0x0 },
	{ "INTP_PEND_SIZE_MISMATCH", 2, 1, RW, 0x0 },
	{ "PIXEL_ORDER", 0, 2, RW, 0x0 },
	{ "OP_MODE", 0, 1, RW, 0x0 },
	{ "COMP_RATIO", 0, 2, RW, 0x0 },
	{ "BIT_IND", 0, 2, RW, 0x0 },
	{ "PREVIEW_EN", 0, 1, RW, 0x0 },
	{ "POWER_SAVE_EN", 0, 1, RW, 0x0 },
	{ "SAT_MODE_EN", 0, 1, RW, 0x0 },
	{ "SAT_REF_VALUE", 0, 10, RW, 0x2F5 },
	{ "SAT_RANGE", 0, 5, RW, 0x00 },
	{ "FIX_REF0", 0, 10, RW, 0x384 },
	{ "FIX_REF1", 0, 10, RW, 0x12C },
	{ "FIX_REF2", 0, 10, RW, 0x258 },
	{ "FIX_REF3", 0, 10, RW, 0x14A },
	{ "BP_EN", 0, 1, RW, 0x0 },
	{ "BP_SAT_EN", 0, 1, RW, 0x0 },
	{ "BP_THRESH", 0, 10, RW, 0x12C },
	{ "BP_LOW_THRESH", 0, 10, RW, 0x0C8 },
	{ "BP_LOW_AROUND", 0, 8, RW, 0x78 },
	{ "BASE_VALUEX", 0, 10, RW, 0x080 },
	{ "IMAGE_WIDTH", 0, 14, RW, 0x1FE0 },
	{ "IMAGE_HEIGHT", 0, 13, RW, 0x1800 },
	{ "LFSR_SEED", 0, 16, RW, 0x003B },
	{ "FIFO_DEPTH", 0, 9, RW, 0x100 },
	{ "HBLANK_CNT", 0, 10, RW, 0x100 },
	{ "EMBDD_SEL", 0, 1, RW, 0x0 },
	{ "BLOCK_ID_CODE", 0, 32, RO, 0x00000000 },
	{ "CRC_SEED", 0, 8, RW, 0x00 },
	{ "CRC_RESULT", 8, 8, RO, 0x00 },
};

/* CSIS_MCB0 */
#define CSIS_MCB0_PLANE_CR_NUM 4
#define CSIS_MCB0_GROUP_CR_NUM 8
#define CSIS_MCB0_SET_NUM_CR_NUM 3
#define CSIS_MCB0_WEIGHT_CR_NUM 86
#define CSIS_MCB0_OFFSET_CR_NUM 12
#define CSIS_MCB0_SHIFT_CR_NUM 3

enum is_csis_mcb0_reg_id {
	CSIS_MCB0_R_CTRL,
	CSIS_MCB0_R_START,
	CSIS_MCB0_R_SIZE,
	CSIS_MCB0_R_OUT_WIDTH,
	CSIS_MCB0_R_STEP,
	CSIS_MCB0_R_PLANE_0, /* [PLANE_0:PLANE_3] */
	CSIS_MCB0_R_GROUP_0, /* [GROUP_0:GROUP_7] */
	CSIS_MCB0_R_SET_NUM_0, /* [SET_NUM_0:SET_NUM_2] */
	CSIS_MCB0_R_WEIGHT_0, /* [WEIGHT_0:WEIGHT_85] */
	CSIS_MCB0_R_OFFSET_0, /* [OFFSET_0:OFFSET_11] */
	CSIS_MCB0_R_OFFSET_24, /* [OFFSET_24:OFFSET_35] */
	CSIS_MCB0_R_OFFSET_48, /* [OFFSET_48:OFFSET_59] */
	CSIS_MCB0_R_SHIFT_0, /* [SHIFT_0:SHIFT_2] */
	CSIS_MCB0_R_HEIGHT,
	CSIS_MCB0_R_CRC,
	CSIS_MCB0_REG_CNT,
};

static const struct is_reg is_csis_mcb0_regs[CSIS_MCB0_REG_CNT] = {
	{ 0xa000, "MCB0_CTRL" },
	{ 0xa004, "MCB0_START" },
	{ 0xa008, "MCB0_SIZE" },
	{ 0xa00c, "MCB0_OUT_WIDTH" },
	{ 0xa010, "MCB0_STEP" },
	{ 0xa014, "MCB0_PLANE_0" }, /* [0xa014:0xa020] */
	{ 0xa024, "MCB0_GROUP_0" }, /* [0xa024:0xa040] */
	{ 0xa044, "MCB0_SET_NUM_0" }, /* [0xa044:0xa04c] */
	{ 0xa05c, "MCB0_WEIGHT_0" }, /* [0xa05c:0xa1b0] */
	{ 0xa1b4, "MCB0_OFFSET_0" }, /* [0xa1b4:0xa1e0] */
	{ 0xa214, "MCB0_OFFSET_24" }, /* [0xa214:0xa240] */
	{ 0xa274, "MCB0_OFFSET_48" }, /* [0xa274:0xa2a0] */
	{ 0xa2d4, "MCB0_SHIFT_0" }, /* [0xa2d4:0xa2dc] */
	{ 0xa2e0, "MCB0_HEIGHT" },
	{ 0xa2f0, "MCB0_CRC" },
};

enum is_csis_mcb0_field_id {
	CSIS_MCB0_F_BYPASS,
	CSIS_MCB0_F_BINNINGMODE,
	CSIS_MCB0_F_CROP_EN,
	CSIS_MCB0_F_IBITMODE,
	CSIS_MCB0_F_OBITMODE,
	CSIS_MCB0_F_INPUT_WIDTH,
	CSIS_MCB0_F_CROP_START_X,
	CSIS_MCB0_F_CROP_START_Y,
	CSIS_MCB0_F_CROP_SIZE_X,
	CSIS_MCB0_F_CROP_SIZE_Y,
	CSIS_MCB0_F_OUTPUT_WIDTH,
	CSIS_MCB0_F_ACTIVE_PLANE_NUM,
	CSIS_MCB0_F_UNIT_KERNEL_SIZE,
	CSIS_MCB0_F_FLAG_PLANE_X_15,
	CSIS_MCB0_F_FLAG_PLANE_X_14,
	CSIS_MCB0_F_FLAG_PLANE_X_13,
	CSIS_MCB0_F_FLAG_PLANE_X_12,
	CSIS_MCB0_F_FLAG_PLANE_X_11,
	CSIS_MCB0_F_FLAG_PLANE_X_10,
	CSIS_MCB0_F_FLAG_PLANE_X_9,
	CSIS_MCB0_F_FLAG_PLANE_X_8,
	CSIS_MCB0_F_FLAG_PLANE_X_7,
	CSIS_MCB0_F_FLAG_PLANE_X_6,
	CSIS_MCB0_F_FLAG_PLANE_X_5,
	CSIS_MCB0_F_FLAG_PLANE_X_4,
	CSIS_MCB0_F_FLAG_PLANE_X_3,
	CSIS_MCB0_F_FLAG_PLANE_X_2,
	CSIS_MCB0_F_FLAG_PLANE_X_1,
	CSIS_MCB0_F_FLAG_PLANE_X_0,
	CSIS_MCB0_F_FLAG_GROUP_0_7,
	CSIS_MCB0_F_FLAG_GROUP_0_6,
	CSIS_MCB0_F_FLAG_GROUP_0_5,
	CSIS_MCB0_F_FLAG_GROUP_0_4,
	CSIS_MCB0_F_FLAG_GROUP_0_3,
	CSIS_MCB0_F_FLAG_GROUP_0_2,
	CSIS_MCB0_F_FLAG_GROUP_0_1,
	CSIS_MCB0_F_FLAG_GROUP_0_0,
	CSIS_MCB0_F_FLAG_GROUP_0_15,
	CSIS_MCB0_F_FLAG_GROUP_0_14,
	CSIS_MCB0_F_FLAG_GROUP_0_13,
	CSIS_MCB0_F_FLAG_GROUP_0_12,
	CSIS_MCB0_F_FLAG_GROUP_0_11,
	CSIS_MCB0_F_FLAG_GROUP_0_10,
	CSIS_MCB0_F_FLAG_GROUP_0_9,
	CSIS_MCB0_F_FLAG_GROUP_0_8,
	CSIS_MCB0_F_FLAG_GROUP_X_7,
	CSIS_MCB0_F_FLAG_GROUP_X_6,
	CSIS_MCB0_F_FLAG_GROUP_X_5,
	CSIS_MCB0_F_FLAG_GROUP_X_4,
	CSIS_MCB0_F_FLAG_GROUP_X_3,
	CSIS_MCB0_F_FLAG_GROUP_X_2,
	CSIS_MCB0_F_FLAG_GROUP_X_1,
	CSIS_MCB0_F_FLAG_GROUP_X_0,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_7,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_6,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_5,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_4,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_3,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_2,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_1,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_0,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_15,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_14,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_13,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_12,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_11,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_10,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_9,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE00_GROUP_0_8,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE02_GROUP_0_3,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE02_GROUP_0_2,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE02_GROUP_0_1,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE02_GROUP_0_0,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE01_GROUP_0_3,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE01_GROUP_0_2,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE01_GROUP_0_1,
	CSIS_MCB0_F_WEIGHT_SET_NUM_PLANE01_GROUP_0_0,
	CSIS_MCB0_F_PIXEL_WEIGHT_SET_PIX_X_2,
	CSIS_MCB0_F_PIXEL_WEIGHT_SET_PIX_X_1,
	CSIS_MCB0_F_PIXEL_WEIGHT_SET_PIX_X_0,
	CSIS_MCB0_F_PRE_OFFSET_PLANEX_GROUP_X_1,
	CSIS_MCB0_F_PRE_OFFSET_PLANEX_GROUP_X_0,
	CSIS_MCB0_F_SHIFT_OFFSET_PLANEX_GROUP_X_1,
	CSIS_MCB0_F_SHIFT_OFFSET_PLANEX_GROUP_X_0,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_7,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_6,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_5,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_4,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_3,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_2,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_1,
	CSIS_MCB0_F_SHIFT_PLANEX_GROUP_X_0,
	CSIS_MCB0_F_INPUT_HEIGHT,
	CSIS_MCB0_F_OUTPUT_HEIGHT,
	CSIS_MCB0_F_CRC_SEED,
	CSIS_MCB0_F_CRC_RESULT,
	CSIS_MCB0_FIELD_CNT,
};

static const struct is_field is_csis_mcb0_fields[CSIS_MCB0_FIELD_CNT] = {
	{ "BYPASS", 0, 1, RW, 0x1 },
	{ "BINNINGMODE", 4, 4, RW, 0x1 },
	{ "CROP_EN", 8, 1, RW, 0x0 },
	{ "IBITMODE", 12, 2, RW, 0x1 },
	{ "OBITMODE", 14, 2, RW, 0x1 },
	{ "INPUT_WIDTH", 16, 15, RW, 0x0140 },
	{ "CROP_START_X", 0, 15, RW, 0x0000 },
	{ "CROP_START_Y", 16, 15, RW, 0x0000 },
	{ "CROP_SIZE_X", 0, 15, RW, 0x0140 },
	{ "CROP_SIZE_Y", 16, 15, RW, 0x00F0 },
	{ "OUTPUT_WIDTH", 0, 15, RW, 0x00A0 },
	{ "ACTIVE_PLANE_NUM", 8, 2, RW, 0x1 },
	{ "UNIT_KERNEL_SIZE", 16, 4, RW, 0x4 },
	{ "FLAG_PLANE_X_15", 0, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_14", 2, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_13", 4, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_12", 6, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_11", 8, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_10", 10, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_9", 12, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_8", 14, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_7", 16, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_6", 18, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_5", 20, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_4", 22, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_3", 24, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_2", 26, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_1", 28, 2, RW, 0x0 },
	{ "FLAG_PLANE_X_0", 30, 2, RW, 0x0 },
	{ "FLAG_GROUP_0_7", 0, 4, RW, 0x1 },
	{ "FLAG_GROUP_0_6", 4, 4, RW, 0x1 },
	{ "FLAG_GROUP_0_5", 8, 4, RW, 0x0 },
	{ "FLAG_GROUP_0_4", 12, 4, RW, 0x1 },
	{ "FLAG_GROUP_0_3", 16, 4, RW, 0x1 },
	{ "FLAG_GROUP_0_2", 20, 4, RW, 0x0 },
	{ "FLAG_GROUP_0_1", 24, 4, RW, 0x0 },
	{ "FLAG_GROUP_0_0", 28, 4, RW, 0x0 },
	{ "FLAG_GROUP_0_15", 0, 4, RW, 0x3 },
	{ "FLAG_GROUP_0_14", 4, 4, RW, 0x3 },
	{ "FLAG_GROUP_0_13", 8, 4, RW, 0x2 },
	{ "FLAG_GROUP_0_12", 12, 4, RW, 0x2 },
	{ "FLAG_GROUP_0_11", 16, 4, RW, 0x3 },
	{ "FLAG_GROUP_0_10", 20, 4, RW, 0x3 },
	{ "FLAG_GROUP_0_9", 24, 4, RW, 0x2 },
	{ "FLAG_GROUP_0_8", 28, 4, RW, 0x2 },
	{ "FLAG_GROUP_X_7", 0, 4, RW, 0x0 },
	{ "FLAG_GROUP_X_6", 4, 4, RW, 0x0 },
	{ "FLAG_GROUP_X_5", 8, 4, RW, 0x0 },
	{ "FLAG_GROUP_X_4", 12, 4, RW, 0x0 },
	{ "FLAG_GROUP_X_3", 16, 4, RW, 0x0 },
	{ "FLAG_GROUP_X_2", 20, 4, RW, 0x0 },
	{ "FLAG_GROUP_X_1", 24, 4, RW, 0x0 },
	{ "FLAG_GROUP_X_0", 28, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_7", 0, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_6", 4, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_5", 8, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_4", 12, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_3", 16, 4, RW, 0x3 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_2", 20, 4, RW, 0x2 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_1", 24, 4, RW, 0x1 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_0", 28, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_15", 0, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_14", 4, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_13", 8, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_12", 12, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_11", 16, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_10", 20, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_9", 24, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE00_GROUP_0_8", 28, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE02_GROUP_0_3", 0, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE02_GROUP_0_2", 4, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE02_GROUP_0_1", 8, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE02_GROUP_0_0", 12, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE01_GROUP_0_3", 16, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE01_GROUP_0_2", 20, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE01_GROUP_0_1", 24, 4, RW, 0x0 },
	{ "WEIGHT_SET_NUM_PLANE01_GROUP_0_0", 28, 4, RW, 0x0 },
	{ "PIXEL_WEIGHT_SET_PIX_X_2", 0, 10, RW, 0x080 },
	{ "PIXEL_WEIGHT_SET_PIX_X_1", 10, 10, RW, 0x080 },
	{ "PIXEL_WEIGHT_SET_PIX_X_0", 20, 10, RW, 0x080 },
	{ "PRE_OFFSET_PLANEX_GROUP_X_1", 0, 15, RW, 0x0000 },
	{ "PRE_OFFSET_PLANEX_GROUP_X_0", 16, 15, RW, 0x0000 },
	{ "SHIFT_OFFSET_PLANEX_GROUP_X_1", 0, 11, RW, 0x100 },
	{ "SHIFT_OFFSET_PLANEX_GROUP_X_0", 16, 11, RW, 0x100 },
	{ "SHIFT_PLANEX_GROUP_X_7", 0, 4, RW, 0x9 },
	{ "SHIFT_PLANEX_GROUP_X_6", 4, 4, RW, 0x9 },
	{ "SHIFT_PLANEX_GROUP_X_5", 8, 4, RW, 0x9 },
	{ "SHIFT_PLANEX_GROUP_X_4", 12, 4, RW, 0x9 },
	{ "SHIFT_PLANEX_GROUP_X_3", 16, 4, RW, 0x9 },
	{ "SHIFT_PLANEX_GROUP_X_2", 20, 4, RW, 0x9 },
	{ "SHIFT_PLANEX_GROUP_X_1", 24, 4, RW, 0x9 },
	{ "SHIFT_PLANEX_GROUP_X_0", 28, 4, RW, 0x9 },
	{ "INPUT_HEIGHT", 0, 15, RW, 0x00F0 },
	{ "OUTPUT_HEIGHT", 16, 15, RW, 0x0078 },
	{ "CRC_SEED", 0, 8, RW, 0x00 },
	{ "CRC_RESULT", 8, 8, RO, 0x00 },
};

/* CSIS_MCB1 */
enum is_csis_mcb1_reg_id {
	CSIS_MCB1_R_CTRL,
	CSIS_MCB1_R_CROP_START,
	CSIS_MCB1_R_CROP_SIZE,
	CSIS_MCB1_R_OUTPUT_WIDTH,
	CSIS_MCB1_R_HEIGHT,
	CSIS_MCB1_R_CRC,
	CSIS_MCB1_REG_CNT,
};

static const struct is_reg is_csis_mcb1_regs[CSIS_MCB1_REG_CNT] = {
	{ 0xa300, "MCB1_CTRL" },
	{ 0xa304, "MCB1_CROP_START" },
	{ 0xa308, "MCB1_CROP_SIZE" },
	{ 0xa30c, "MCB1_OUTPUT_WIDTH" },
	{ 0xa310, "MCB1_HEIGHT" },
	{ 0xa3fc, "MCB1_CRC" },
};

enum is_csis_mcb1_field_id {
	CSIS_MCB1_F_BYPASS,
	CSIS_MCB1_F_BINNINGMODE,
	CSIS_MCB1_F_CROP_EN,
	CSIS_MCB1_F_IBITMODE,
	CSIS_MCB1_F_OBITMODE,
	CSIS_MCB1_F_INPUT_WIDTH,
	CSIS_MCB1_F_CROP_START_X,
	CSIS_MCB1_F_CROP_START_Y,
	CSIS_MCB1_F_CROP_SIZE_X,
	CSIS_MCB1_F_CROP_SIZE_Y,
	CSIS_MCB1_F_OUTPUT_WIDTH,
	CSIS_MCB1_F_INPUT_HEIGHT,
	CSIS_MCB1_F_OUTPUT_HEIGHT,
	CSIS_MCB1_F_CRC_SEED,
	CSIS_MCB1_F_CRC_RESULT,
	CSIS_MCB1_FIELD_CNT,
};

static const struct is_field is_csis_mcb1_fields[CSIS_MCB1_FIELD_CNT] = {
	{ "BYPASS", 0, 1, RW, 0x1 },
	{ "BINNINGMODE", 4, 2, RW, 0x0 },
	{ "CROP_EN", 8, 1, RW, 0x0 },
	{ "IBITMODE", 12, 2, RW, 0x0 },
	{ "OBITMODE", 14, 2, RW, 0x0 },
	{ "INPUT_WIDTH", 16, 15, RW, 0x0000 },
	{ "CROP_START_X", 0, 15, RW, 0x0000 },
	{ "CROP_START_Y", 16, 15, RW, 0x0000 },
	{ "CROP_SIZE_X", 0, 15, RW, 0x0000 },
	{ "CROP_SIZE_Y", 16, 15, RW, 0x0000 },
	{ "OUTPUT_WIDTH", 0, 15, RW, 0x0000 },
	{ "INPUT_HEIGHT", 0, 15, RW, 0x00f0 },
	{ "OUTPUT_HEIGHT", 16, 15, RW, 0x0078 },
	{ "CRC_SEED", 0, 8, RW, 0x00 },
	{ "CRC_RESULT", 8, 8, RO, 0x00 },
};

/* CSIS_BNS */
enum is_csis_bns_reg_id {
	CSIS_BNS_R_BYPASS,
	CSIS_BNS_R_CONFIG,
	CSIS_BNS_R_INPUTSIZE,
	CSIS_BNS_R_OUTPUTSIZE,
	CSIS_BNS_R_WEIGHT_X_0,
	CSIS_BNS_R_WEIGHT_X_4,
	CSIS_BNS_R_WEIGHT_Y_0,
	CSIS_BNS_R_WEIGHT_Y_4,
	CSIS_BNS_R_CRC,
	CSIS_BNS_REG_CNT,
};

static const struct is_reg is_csis_bns_regs[CSIS_BNS_REG_CNT] = {
	{ 0xe000, "BNS_BYPASS" },
	{ 0xe004, "BNS_CONFIG" },
	{ 0xe010, "BNS_INPUTSIZE" },
	{ 0xe014, "BNS_OUTPUTSIZE" },
	{ 0xe020, "BNS_WEIGHT_X_0" },
	{ 0xe024, "BNS_WEIGHT_X_4" },
	{ 0xe030, "BNS_WEIGHT_Y_0" },
	{ 0xe034, "BNS_WEIGHT_Y_4" },
	{ 0xe0fc, "BNS_CRC" },
};

enum is_csis_bns_field_id {
	CSIS_BNS_F_BYPASS,
	CSIS_BNS_F_FACTOR_X,
	CSIS_BNS_F_FACTOR_Y,
	CSIS_BNS_F_BITTAGE,
	CSIS_BNS_F_NINPUTTOTALWIDTH,
	CSIS_BNS_F_NINPUTTOTALHEIGHT,
	CSIS_BNS_F_NOUTPUTTOTALWIDTH,
	CSIS_BNS_F_NOUTPUTTOTALHEIGHT,
	CSIS_BNS_F_WEIGHT_X_0_0,
	CSIS_BNS_F_WEIGHT_X_0_1,
	CSIS_BNS_F_WEIGHT_X_0_2,
	CSIS_BNS_F_WEIGHT_X_0_3,
	CSIS_BNS_F_WEIGHT_X_0_4,
	CSIS_BNS_F_CRC_SEED,
	CSIS_BNS_F_CRC_RESULT,
	CSIS_BNS_FIELD_CNT,
};

static const struct is_field is_csis_bns_fields[CSIS_BNS_FIELD_CNT] = {
	{ "BYPASS", 0, 1, RW, 0x1 },
	{ "FACTOR_X", 0, 3, RW, 0x0 },
	{ "FACTOR_Y", 8, 3, RW, 0x0 },
	{ "BITTAGE", 16, 4, RW, 0x0 },
	{ "NINPUTTOTALWIDTH", 0, 15, RW, 0x0020 },
	{ "NINPUTTOTALHEIGHT", 16, 14, RW, 0x0020 },
	{ "NOUTPUTTOTALWIDTH", 0, 15, RW, 0x0020 },
	{ "NOUTPUTTOTALHEIGHT", 16, 14, RW, 0x0020 },
	{ "WEIGHT_X_0_0", 0, 8, RW, 0x00 },
	{ "WEIGHT_X_0_1", 8, 8, RW, 0x00 },
	{ "WEIGHT_X_0_2", 16, 8, RW, 0x00 },
	{ "WEIGHT_X_0_3", 24, 8, RW, 0x00 },
	{ "WEIGHT_X_0_4", 0, 8, RW, 0x00 },
	{ "CRC_SEED", 0, 8, RW, 0x00 },
	{ "CRC_RESULT", 8, 8, RO, 0x00 },
};
#endif /* IS_SFR_CSIS_PDP_TOP_V13_0_H */
