// SPDX-License-Identifier: GPL-2.0
/*
 * Samsung Exynos SoC series Pablo driver
 *
 * BYRP HW control APIs
 *
 * Copyright (C) 2022 Samsung Electronics Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/delay.h>
#include "is-hw-api-byrp-v2_0.h"
#include "is-hw-common-dma.h"
#include "is-hw.h"
#include "is-hw-control.h"
#if IS_ENABLED(BYRP_USE_MMIO)
#if IS_ENABLED(CONFIG_PABLO_V12_0_0)
#include "sfr/is-sfr-byrp-mmio-v3_0.h"
#else
#include "sfr/is-sfr-byrp-mmio-v3_1.h"
#endif
#else
#if IS_ENABLED(CONFIG_PABLO_V12_0_0)
#include "sfr/is-sfr-byrp-v3_0.h"
#else
#include "sfr/is-sfr-byrp-v3_1.h"
#define CONFIG_FORCE_WDMA_USE_CGRAS 1
#endif
#endif
#include "pmio.h"

#if IS_ENABLED(BYRP_USE_MMIO)
#define BYRP_SET_F(base, R, F, val) \
	is_hw_set_field(base, &byrp_regs[R], &byrp_fields[F], val)
#define BYRP_SET_F_COREX(base, R, F, val) \
	is_hw_set_field(base, &byrp_regs[R], &byrp_fields[F], val)
#define BYRP_SET_R(base, R, val) \
	is_hw_set_reg(base, &byrp_regs[R], val)
#define BYRP_SET_V(base, reg_val, F, val) \
	is_hw_set_field_value(reg_val, &byrp_fields[F], val)

#define BYRP_GET_F(base, R, F) \
	is_hw_get_field(base, &byrp_regs[R], &byrp_fields[F])
#define BYRP_GET_R(base, R) \
	is_hw_get_reg(base, &byrp_regs[R])
#else
#define BYRP_SET_F(base, R, F, val)		PMIO_SET_F(base, R, F, val)
#define BYRP_SET_F_COREX(base, R, F, val)	PMIO_SET_F_COREX(base, R, F, val)
#define BYRP_SET_R(base, R, val)		PMIO_SET_R(base, R, val)
#define BYRP_SET_V(base, reg_val, F, val)	PMIO_SET_V(base, reg_val, F, val)
#define BYRP_GET_F(base, R, F)			PMIO_GET_F(base, R, F)
#define BYRP_GET_R(base, R)			PMIO_GET_R(base, R)
#endif

unsigned int byrp_hw_is_occurred(unsigned int status, enum byrp_event_type type)
{
	u32 mask;

	switch (type) {
	case INTR_FRAME_START:
		mask = 1 << INTR0_BYRP_FRAME_START_INT;
		break;
	case INTR_FRAME_CINROW:
		mask = 1 << INTR0_BYRP_ROW_COL_INT;
		break;
	case INTR_FRAME_END:
		mask = 1 << INTR0_BYRP_FRAME_END_INT;
		break;
	case INTR_COREX_END_0:
		mask = 1 << INTR0_BYRP_COREX_END_INT_0;
		break;
	case INTR_COREX_END_1:
		mask = 1 << INTR0_BYRP_COREX_END_INT_1;
		break;
	case INTR_SETTING_DONE:
		mask = 1 << INTR0_BYRP_SETTING_DONE_INT;
		break;
	case INTR_ERR0:
		mask = BYRP_INT0_ERR_MASK;
		break;
	case INTR_ERR1:
		mask = BYRP_INT1_ERR_MASK;
		break;
	default:
		return 0;
	}

	return status & mask;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_is_occurred);

int byrp_hw_s_reset(struct pablo_mmio *base)
{
	u32 reset_count = 0;

	BYRP_SET_R(base, BYRP_R_SW_RESET, 0x1);

	/* Changed from 1 to 0 when its operation finished */
	while (BYRP_GET_R(base, BYRP_R_SW_RESET)) {
		if (reset_count > BYRP_TRY_COUNT)
			return -ENODEV;
		reset_count++;
	}

	return 0;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_reset);

void byrp_hw_s_init(struct pablo_mmio *base, u32 set_id)
{
	BYRP_SET_F(base, BYRP_R_CMDQ_VHD_CONTROL, BYRP_F_CMDQ_VHD_VBLANK_QRUN_ENABLE, 1);
	BYRP_SET_F(base, BYRP_R_CMDQ_VHD_CONTROL, BYRP_F_CMDQ_VHD_STALL_ON_QSTOP_ENABLE, 1);
	BYRP_SET_F(base, BYRP_R_DEBUG_CLOCK_ENABLE, BYRP_F_DEBUG_CLOCK_ENABLE, 0);

	if (!IS_ENABLED(BYRP_USE_MMIO)) {
		BYRP_SET_R(base, BYRP_R_C_LOADER_ENABLE, 1);
		BYRP_SET_R(base, BYRP_R_BYR_RDMACLOAD_EN, 1);
	}

	/* Interrupt group enable for one frame */
	BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_L,
		BYRP_F_CMDQ_QUE_CMD_INT_GROUP_ENABLE, BYRP_INT_GRP_EN_MASK);
	/* 1: DMA preloading, 2: COREX, 3: APB Direct */
	BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_M, BYRP_F_CMDQ_QUE_CMD_SETTING_MODE, 3);
	BYRP_SET_R(base, BYRP_R_CMDQ_ENABLE, 1);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_init);

void byrp_hw_s_clock(struct pablo_mmio *base, bool on)
{
	dbg_hw(5, "[BYRP] clock %s", on ? "on" : "off");
	BYRP_SET_F(base, BYRP_R_IP_PROCESSING, BYRP_F_IP_PROCESSING, on);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_clock);

void byrp_hw_s_dtp(struct pablo_mmio *base, u32 set_id, bool enable, u32 width, u32 height)
{
	u32 val;

	if (enable) {
		dbg_hw(1, "[API][%s] dtp color bar pattern is enabled!\n", __func__);

		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_BYPASS,
			BYRP_F_BYR_DTPNONBYR_BYPASS, !enable);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_MODE,
			BYRP_F_BYR_DTPNONBYR_MODE, 0x8); /* color bar pattern */

		/* guide value */
		BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_HIGHER_LIMIT, 16383);
		BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_PATTERN_SIZE_X, width);
		BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_PATTERN_SIZE_Y, height);

		val = 0;
		val = BYRP_SET_V(base, val, BYRP_F_BYR_DTPNONBYR_LAYER_WEIGHTS_0_0, 0x0);
		val = BYRP_SET_V(base, val, BYRP_F_BYR_DTPNONBYR_LAYER_WEIGHTS_0_1, 0x0);
		val = BYRP_SET_V(base, val, BYRP_F_BYR_DTPNONBYR_LAYER_WEIGHTS_0_2, 0x0);
		val = BYRP_SET_V(base, val, BYRP_F_BYR_DTPNONBYR_LAYER_WEIGHTS_0_3, 0x0);
		BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_LAYER_WEIGHTS, val);

		val = 0;
		val = BYRP_SET_V(base, val, BYRP_F_BYR_DTPNONBYR_LAYER_WEIGHTS_0_4, 0x20);
		BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_LAYER_WEIGHTS_1, val);

		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BITMASK0_BITTAGEOUT,
			BYRP_F_BYR_BITMASK0_BITTAGEOUT, 0xE); /* dtp 14bit out */
	} else {
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_BYPASS,
			BYRP_F_BYR_DTPNONBYR_BYPASS, 0x1);
	}
}

static void byrp_hw_s_cinfifo(struct pablo_mmio *base, u32 set_id, bool enable)
{
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) +
		BYRP_R_BYR_CINFIFO_INTERVALS,
		BYRP_F_BYR_CINFIFO_INTERVAL_HBLANK, HBLANK_CYCLE);

	/* Do not support cinfifo in BYRP with no using strgen */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CINFIFO_ENABLE, enable);

	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) +
		BYRP_R_BYR_CINFIFO_CONFIG,
		BYRP_F_BYR_CINFIFO_STALL_BEFORE_FRAME_START_EN, 0);

	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CINFIFO_INT_ENABLE, 0xF);
}

void byrp_hw_s_strgen(struct pablo_mmio *base, u32 set_id)
{
	/* RDMA input off*/
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_RDMABYRIN_EN, 0);
	/* OTF input select */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_IP_USE_OTF_PATH_01,
		BYRP_F_IP_USE_OTF_IN_FOR_PATH_0, 1);
	/* DTP path select */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_INPUT_0_SELECT, 1);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_INPUT_1_SELECT, 1);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_INPUT_2_SELECT, 1);

	/* STRGEN setting */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CINFIFO_CONFIG,
		BYRP_F_BYR_CINFIFO_STRGEN_MODE_EN, 1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CINFIFO_CONFIG,
		BYRP_F_BYR_CINFIFO_STRGEN_MODE_DATA_TYPE, 1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CINFIFO_CONFIG,
		BYRP_F_BYR_CINFIFO_STRGEN_MODE_DATA, 255);

	/* cinfifo enable */
	byrp_hw_s_cinfifo(base, set_id, 1);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_strgen);

void byrp_hw_s_path(struct pablo_mmio *base, u32 set_id,
	struct byrp_param_set *param_set, struct is_byrp_config *config)
{
	u32 val = 0;
	u32 input_0, input_1, input_2, output_0;
	bool mpc_en, hdr_en, dng_en;

	/* TODO: MPC on/off is checked from cis */
	mpc_en = 0; /* TBD */
	hdr_en = param_set->dma_input_hdr.cmd; /* According to rdma cmd */
	dng_en = param_set->dma_output_byr.cmd;

	val = BYRP_SET_V(base, val, BYRP_F_IP_USE_OTF_IN_FOR_PATH_0, 0x0); /* RDMA input */
	val = BYRP_SET_V(base, val, BYRP_F_IP_USE_OTF_OUT_FOR_PATH_0, 0x1); /* OTF output */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_IP_USE_OTF_PATH_01, val);

	/* Belows decied the data path between SDC / MPC / HDR
	 * chain input0 select
	 * 0: Disconnect path
	 * 1: DTP
	 * 2: RDMA (Formatter)
	 * 3: RDMA (MPC)
	 *
	 * chain input1 & input2 select
	 * 0: Disconnect path
	 * 1: DTP
	 * 2: RDMA(HDR1, HDR2)
	 * 3: Reserved
	 */
	if (mpc_en) {
		input_0 = 0x3;
		input_1 = input_2 = 0x2;
	} else {
		input_0 = input_1 = input_2 = 0x2;
	}

	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_INPUT_0_SELECT, input_0);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_INPUT_1_SELECT, input_1);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_INPUT_2_SELECT, input_2);

	/* SDC ON/OFF : No scenario to use */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_SDC_ON,
		BYRP_F_CHAIN_SDC_ON, 0x0);

	/* chain output_0 select
	 * 0: Reserved
	 * 1: PREGAMMA to WDMA
	 * 2: CGRAS to WDMA
	 * 3: Reserved
	 */

	if (IS_ENABLED(CONFIG_FORCE_WDMA_USE_CGRAS))
		output_0 = BYRP_CGRAS_TO_WDMA;
	else
		output_0 = dng_en ? BYRP_CGRAS_TO_WDMA : BYRP_PREGAMMA_TO_WDMA;
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_CHAIN_OUTPUT_0_SELECT, output_0);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_path);

int byrp_hw_wait_idle(struct pablo_mmio *base)
{
	int ret = SET_SUCCESS;
	u32 idle;
	u32 int0_all;
	u32 int1_all;
	u32 try_cnt = 0;

	idle = BYRP_GET_F(base, BYRP_R_IDLENESS_STATUS, BYRP_F_IDLENESS_STATUS);
	int0_all = BYRP_GET_R(base, BYRP_R_INT_REQ_INT0_STATUS);
	int1_all = BYRP_GET_R(base, BYRP_R_INT_REQ_INT1_STATUS);

	info_hw("[BYRP] idle status before disable (idle: %d, int0: 0x%X, int1: 0x%X)\n",
			idle, int0_all, int1_all);

	while (!idle) {
		idle = BYRP_GET_F(base, BYRP_R_IDLENESS_STATUS, BYRP_F_IDLENESS_STATUS);

		try_cnt++;
		if (try_cnt >= BYRP_TRY_COUNT) {
			err_hw("[BYRP] timeout waiting idle - disable fail");
			byrp_hw_dump(base, HW_DUMP_CR);
			ret = -ETIME;
			break;
		}

		usleep_range(3, 4);
	};

	int0_all = BYRP_GET_R(base, BYRP_R_INT_REQ_INT0_STATUS);
	int1_all = BYRP_GET_R(base, BYRP_R_INT_REQ_INT1_STATUS);

	info_hw("[BYRP] idle status after disable (idle: %d, int0: 0x%X, int1: 0x%X)\n",
			idle, int0_all, int1_all);

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_wait_idle);

static const struct is_reg byrp_dbg_cr[] = {
	/* The order of DBG_CR should match with the DBG_CR parser. */
	/* Interrupt History */
	{0x0900,"INT_HIST_CURINT0"},
	{0x090c,"INT_HIST_CURINT1"},
	/* Core Status */
	{0x0f08,"QCH_STATUS"},
	{0x0f0c,"IDLENESS_STATUS"},
	{0x0f40,"IP_BUSY_MONITOR_0"},
	{0x0f44,"IP_BUSY_MONITOR_1"},
	{0x0f48,"IP_BUSY_MONITOR_2"},
	{0x0f4c,"IP_BUSY_MONITOR_3"},
	{0x0f60,"IP_STALL_OUT_STATUS_0"},
	{0x0f64,"IP_STALL_OUT_STATUS_1"},
	{0x0f68,"IP_STALL_OUT_STATUS_2"},
	{0x0f6c,"IP_STALL_OUT_STATUS_3"},
	/* Chain Size */
	{0x0200,"GLOBAL_IMAGE_RESOLUTION"},
	/* Chain Path */
	{0x0080,"IP_USE_OTF_PATH_01"},
	{0x007c,"IP_USE_OTF_PATH_23"},
	{0x0078,"IP_USE_OTF_PATH_45"},
	{0x0074,"IP_USE_OTF_PATH_67"},
	{0x0208,"CHAIN_INPUT_0_SELECT"},
	{0x020c,"CHAIN_INPUT_1_SELECT"},
	{0x0210,"CHAIN_INPUT_2_SELECT"},
	{0x0220,"CHAIN_OUTPUT_0_SELECT"},
	/* CMDQ Frame Counter */
	{0x04a8,"CMDQ_FRAME_COUNTER"},
	/* CINFIFO 0 Status */
	{0x1000,"BYR_CINFIFO_ENABLE"},
	{0x1014,"BYR_CINFIFO_STATUS"},
	{0x1018,"BYR_CINFIFO_INPUT_CNT"},
	{0x101c,"BYR_CINFIFO_STALL_CNT"},
	{0x1020,"BYR_CINFIFO_FIFO_FULLNESS"},
	{0x1040,"BYR_CINFIFO_INT"},
	/* COUTFIFO 0 Status */
	{0x1200,"BYR_COUTFIFO_ENABLE"},
	{0x1214,"BYR_COUTFIFO_STATUS"},
	{0x1218,"BYR_COUTFIFO_INPUT_CNT"},
	{0x121c,"BYR_COUTFIFO_STALL_CNT"},
	{0x1220,"BYR_COUTFIFO_FIFO_FULLNESS"},
	{0x1240,"BYR_COUTFIFO_INT"},
};

static void byrp_hw_dump_dbg_state(struct pablo_mmio *pmio)
{
	void *ctx;
	const struct is_reg *cr;
	u32 i, val;

	ctx = pmio->ctx ? pmio->ctx : (void *)pmio;
	pmio->reg_read(ctx, BYRP_R_IP_VERSION, &val);

	is_dbg("[HW:%s] v%02u.%02u.%02u ======================================\n", pmio->name,
		(val >> 24) & 0xff, (val >> 16) & 0xff, val & 0xffff);
	for (i = 0; i < ARRAY_SIZE(byrp_dbg_cr); i++) {
		cr = &byrp_dbg_cr[i];

		pmio->reg_read(ctx, cr->sfr_offset, &val);
		is_dbg("[HW:%s]%40s %08x\n", pmio->name, cr->reg_name, val);
	}
	is_dbg("[HW:%s]=================================================\n", pmio->name);
}

void byrp_hw_dump(struct pablo_mmio *pmio, u32 mode)
{
	switch (mode) {
	case HW_DUMP_CR:
		info_hw("[BYRP]%s:DUMP CR\n", __FILENAME__);
		is_hw_dump_regs(pmio_get_base(pmio), byrp_regs, BYRP_REG_CNT);
		break;
	case HW_DUMP_DBG_STATE:
		info_hw("[BYRP]%s:DUMP DBG_STATE\n", __FILENAME__);
		byrp_hw_dump_dbg_state(pmio);
		break;
	default:
		err_hw("[BYRP]%s:Not supported dump_mode %u", __FILENAME__, mode);
		break;
	}
}
KUNIT_EXPORT_SYMBOL(byrp_hw_dump);

static void byrp_hw_s_byrhdr(struct pablo_mmio *base, u32 set_id, u32 hdr_en)
{
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BYRHDR_RATE_CONTROL_ENABLE, hdr_en);

	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN1_BYPASS, !hdr_en);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN2_BYPASS, !hdr_en);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BITMASK1_BYPASS, !hdr_en);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_GAMMASENSOR1_BYPASS, !hdr_en);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_PREDNS1_BYPASS, !hdr_en);

	/* TBD if (hdr_en) */
}

static void byrp_hw_s_coutfifo(struct pablo_mmio *base, u32 set_id, bool enable)
{
	u32 val = 0;

	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) +
		BYRP_R_BYR_COUTFIFO_INTERVALS,
		BYRP_F_BYR_COUTFIFO_INTERVAL_HBLANK, HBLANK_CYCLE);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) +
		BYRP_R_BYR_COUTFIFO_INTERVAL_VBLANK,
		BYRP_F_BYR_COUTFIFO_INTERVAL_VBLANK, VBLANK_CYCLE);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_COUTFIFO_ENABLE, enable);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_COUTFIFO_INT_ENABLE, 0xF);

	/* DEBUG */
	val = BYRP_SET_V(base, val, BYRP_F_BYR_COUTFIFO_VVALID_RISE_AT_FIRST_DATA_EN, 1);
	val = BYRP_SET_V(base, val, BYRP_F_BYR_COUTFIFO_DEBUG_EN, 1); /* stall cnt */
	val = BYRP_SET_V(base, val, BYRP_F_BYR_COUTFIFO_BACK_STALL_EN, 1); /* RGBP is ready */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_COUTFIFO_CONFIG, val);
}

static void byrp_hw_g_rdma_fmt_map(int dma_id, ulong *byr_fmt_map)
{
	switch (dma_id) {
	case BYRP_RDMA_IMG: /* 0,1,2,4,5,6,7,8,9,10,11,12,13,14 */
		*byr_fmt_map = (0
				| BIT_MASK(DMA_FMT_U8BIT_PACK)
				| BIT_MASK(DMA_FMT_U8BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U8BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_U10BIT_PACK)
				| BIT_MASK(DMA_FMT_U10BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U10BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_ANDROID10)
				| BIT_MASK(DMA_FMT_U12BIT_PACK)
				| BIT_MASK(DMA_FMT_U12BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U12BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_ANDROID12)
				| BIT_MASK(DMA_FMT_U14BIT_PACK)
				| BIT_MASK(DMA_FMT_U14BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U14BIT_UNPACK_MSB_ZERO)
				) & IS_BAYER_FORMAT_MASK;
		break;
	case BYRP_RDMA_HDR0: /* 0,1,2,4,5,6,7,8,9,10,11 */
	case BYRP_RDMA_HDR1:
		*byr_fmt_map = (0
				| BIT_MASK(DMA_FMT_U8BIT_PACK)
				| BIT_MASK(DMA_FMT_U8BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U8BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_U10BIT_PACK)
				| BIT_MASK(DMA_FMT_U10BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U10BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_ANDROID10)
				| BIT_MASK(DMA_FMT_U12BIT_PACK)
				| BIT_MASK(DMA_FMT_U12BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U12BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_ANDROID12)
				| BIT_MASK(DMA_FMT_U14BIT_PACK)
				| BIT_MASK(DMA_FMT_U14BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U14BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_S12BIT_PACK)
				| BIT_MASK(DMA_FMT_S12BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_S12BIT_UNPACK_MSB_ZERO)
				) & IS_BAYER_FORMAT_MASK;
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma_id);
		break;
	}
}

static void byrp_hw_g_wdma_fmt_map(int dma_id, ulong *byr_fmt_map)
{
	switch (dma_id) {
	case BYRP_WDMA_BYR: /* 0,1,2,4,5,6,8,9,10,12,13,14 */
		*byr_fmt_map = (0
				| BIT_MASK(DMA_FMT_U8BIT_PACK)
				| BIT_MASK(DMA_FMT_U8BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U8BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_U10BIT_PACK)
				| BIT_MASK(DMA_FMT_U10BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U10BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_U12BIT_PACK)
				| BIT_MASK(DMA_FMT_U12BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U12BIT_UNPACK_MSB_ZERO)
				| BIT_MASK(DMA_FMT_U14BIT_PACK)
				| BIT_MASK(DMA_FMT_U14BIT_UNPACK_LSB_ZERO)
				| BIT_MASK(DMA_FMT_U14BIT_UNPACK_MSB_ZERO)
				) & IS_BAYER_FORMAT_MASK;
		break;
	case BYRP_WDMA_RGBYHIST:
	case BYRP_WDMA_THSTAT_AWB:
		*byr_fmt_map = 0;
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma_id);
		break;
	}
}

static void byrp_hw_s_common(struct pablo_mmio *base, u32 set_id,
	struct byrp_param_set *param_set, u32 bit_in)
{
	u32 val;
	u32 img_fmt;

	/* 0: start frame asap, 1; start frame upon cinfifo vvalid rise */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) +
		BYRP_R_IP_USE_CINFIFO_NEW_FRAME_IN,
		BYRP_F_IP_USE_CINFIFO_NEW_FRAME_IN, 0x0);

	switch (bit_in) {
	case 8:
		img_fmt = BYRP_IMG_FMT_8BIT;
		break;
	case 10:
		img_fmt = BYRP_IMG_FMT_10BIT;
		break;
	case 12:
		img_fmt = BYRP_IMG_FMT_12BIT;
		break;
	case 14:
		img_fmt = BYRP_IMG_FMT_14BIT;
		break;
	case 9:
		img_fmt = BYRP_IMG_FMT_9BIT;
		break;
	case 11:
		img_fmt = BYRP_IMG_FMT_11BIT;
		break;
	case 13:
		img_fmt = BYRP_IMG_FMT_13BIT;
		break;
	default:
		err_hw("[BYRP] invalid image_fmt: %d -> 10b (default)", bit_in);
		img_fmt = BYRP_IMG_FMT_10BIT; /* default: 10b */
	}

	val = 0;
	/* 0: 8b, 1: 10b, 2: 12b, 3: 14b, 4: 9b, 5: 11b, 6: 13b */
	val = BYRP_SET_V(base, val, BYRP_F_BYR_FMT_IMG_FORMAT, img_fmt);
	val = BYRP_SET_V(base, val, BYRP_F_BYR_FMT_IMG_ALIGN, 0); /* 0: LSB, 1: MSB */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_FMT_IMG, val);

	/* TODO: Need to check value */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_FMT_LINEGAP, 0x0);
}

static void byrp_hw_s_int_mask(struct pablo_mmio *base, u32 set_id)
{
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_INT_REQ_INT0_ENABLE,
		BYRP_F_INT_REQ_INT0_ENABLE, BYRP_INT0_EN_MASK);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_INT_REQ_INT1_ENABLE,
		BYRP_F_INT_REQ_INT1_ENABLE, BYRP_INT1_EN_MASK);
}

static void byrp_hw_s_secure_id(struct pablo_mmio *base, u32 set_id)
{
	/*
	 * Set Paramer Value
	 * scenario
	 * 0: Non-secure,  1: Secure
	 */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_SECU_CTRL_SEQID, BYRP_F_SECU_CTRL_SEQID, 0x0);
}

void byrp_hw_g_input_param(struct byrp_param_set *param_set, u32 instance, u32 id,
	struct param_dma_input **dma_input, dma_addr_t **input_dva,
	struct is_byrp_config *config)
{
	switch (id) {
	case BYRP_RDMA_IMG:
		*input_dva = param_set->input_dva;
		*dma_input = &param_set->dma_input;
		break;
	case BYRP_RDMA_HDR0:
		*input_dva = param_set->input_dva_hdr;
		*dma_input = &param_set->dma_input_hdr;
		break;
	case BYRP_RDMA_HDR1:
		*input_dva = param_set->input_dva_hdr1;
		*dma_input = &param_set->dma_input_hdr1;
		break;
	default:
		merr_hw("invalid ID (%d)", instance, id);
		break;
	}
}

void byrp_hw_g_output_param(struct byrp_param_set *param_set, u32 instance, u32 id,
	struct param_dma_output **dma_output, dma_addr_t **output_dva)
{
	switch (id) {
	case BYRP_WDMA_BYR:
		if (param_set->dma_output_byr.cmd && param_set->dma_output_byr_processed.cmd) {
			merr_hw("wrong control about byrp wdma mux (both enable)", instance);
		} else if (param_set->dma_output_byr_processed.cmd) {
			*output_dva = param_set->output_dva_byr_processed;
			*dma_output = &param_set->dma_output_byr_processed;
		} else {
			*output_dva = param_set->output_dva_byr;
			*dma_output = &param_set->dma_output_byr;
		}
		break;
	case BYRP_WDMA_RGBYHIST:
		*output_dva = param_set->output_dva_byrrgbyhist;
		*dma_output = &param_set->dma_output_rgbyhist;
		break;
	case BYRP_WDMA_THSTAT_AWB:
		*output_dva = param_set->output_dva_thstat_awb;
		*dma_output = &param_set->dma_output_thstat_awb;
		break;
	default:
		merr_hw("invalid ID (%d)", instance, id);
		break;
	}
}

int byrp_hw_s_rdma_init(struct is_common_dma *dma,
	struct param_dma_input *dma_input, struct param_stripe_input *stripe_input,
	u32 enable, struct is_crop *dma_crop_cfg,
	u32 *sbwc_en, u32 *payload_size, struct is_byrp_config *config)
{
	u32 comp_sbwc_en, comp_64b_align = 1, quality_control = 0;
	u32 dma_stride_1p, dma_header_stride_1p = 0, stride_align = 1;
	u32 hwformat, memory_bitwidth, pixelsize, sbwc_type;
	u32 dma_width, dma_height;
	u32 format, en_votf, bus_info;
	int ret;
	u32 strip_enable;
	u32 full_width, full_height;
	u32 cache_hint = 0;

	ret = CALL_DMA_OPS(dma, dma_enable, enable);
	if (enable == 0)
		return 0;

	strip_enable = (stripe_input->total_count == 0) ? 0 : 1;

	switch (dma->id) {
	case BYRP_RDMA_IMG:
		dma_width = dma_crop_cfg->w;
		dma_height = dma_crop_cfg->h;
		stride_align = 32;
		cache_hint = IS_LLC_CACHE_HINT_LAST_ACCESS;
		break;
	case BYRP_RDMA_HDR0:
		dma_width = dma_input->width;
		dma_height = dma_input->height;
		stride_align = 32;
		cache_hint = IS_LLC_CACHE_HINT_LAST_ACCESS;
		break;
	case BYRP_RDMA_HDR1:
		dma_width = dma_input->width;
		dma_height = dma_input->height;
		stride_align = 32;
		cache_hint = IS_LLC_CACHE_HINT_LAST_ACCESS;
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma->id);
		return SET_ERROR;
	}

	full_width = (strip_enable) ? stripe_input->full_width :
			dma_input->width;
	full_height = dma_input->height;
	en_votf = dma_input->v_otf_enable;
	hwformat = dma_input->format;
	sbwc_type = dma_input->sbwc_type;
	memory_bitwidth = dma_input->bitwidth;
	pixelsize = dma_input->msb + 1;
	bus_info = en_votf ? (cache_hint << 4) : 0x00000000UL; /* cache hint [6:4] */

	dbg_hw(2, "[API][%s]%s %dx%d, format: %d, bitwidth: %d\n",
		__func__, dma->name,
		dma_width, dma_height, hwformat, memory_bitwidth);

	*sbwc_en = comp_sbwc_en = is_hw_dma_get_comp_sbwc_en(sbwc_type, &comp_64b_align);
	if (!is_hw_dma_get_bayer_format(memory_bitwidth, pixelsize, hwformat, comp_sbwc_en,
						true, &format))
		ret |= CALL_DMA_OPS(dma, dma_set_format, format, DMA_FMT_BAYER);
	else
		ret |= DMA_OPS_ERROR;

	if (comp_sbwc_en == 0) {
		dma_stride_1p =	is_hw_dma_get_img_stride(memory_bitwidth, pixelsize, hwformat,
								full_width, stride_align, true);
	} else if (comp_sbwc_en == 1 || comp_sbwc_en == 2) {
		dma_stride_1p = is_hw_dma_get_payload_stride(comp_sbwc_en, pixelsize, full_width,
								comp_64b_align, quality_control,
								BYRP_COMP_BLOCK_WIDTH,
								BYRP_COMP_BLOCK_HEIGHT);
		dma_header_stride_1p =
			is_hw_dma_get_header_stride(full_width, BYRP_COMP_BLOCK_WIDTH, stride_align);
	} else {
		return SET_ERROR;
	}

	ret |= CALL_DMA_OPS(dma, dma_set_size, dma_width, dma_height);
	ret |= CALL_DMA_OPS(dma, dma_set_img_stride, dma_stride_1p, 0, 0);
	ret |= CALL_DMA_OPS(dma, dma_set_comp_sbwc_en, comp_sbwc_en);
	ret |= CALL_DMA_OPS(dma, dma_votf_enable, en_votf, 0);
	ret |= CALL_DMA_OPS(dma, dma_set_bus_info, bus_info);

	switch (comp_sbwc_en) {
	case 1:
	case 2:
		ret |= CALL_DMA_OPS(dma, dma_set_comp_64b_align, comp_64b_align);
		ret |= CALL_DMA_OPS(dma, dma_set_header_stride, dma_header_stride_1p, 0);
		*payload_size = DIV_ROUND_UP(full_height, BYRP_COMP_BLOCK_HEIGHT) * dma_stride_1p;
		break;
	default:
		break;
	}

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_rdma_init);

int byrp_hw_s_wdma_init(struct is_common_dma *dma, struct byrp_param_set *param_set,
	struct pablo_mmio *base, u32 set_id,
	u32 enable, u32 out_crop_size_x,
	u32 *sbwc_en, u32 *payload_size)
{
	struct param_dma_input *dma_input;
	struct param_dma_output *dma_output;
	u32 comp_sbwc_en, comp_64b_align = 1, quality_control = 0;
	u32 stride_1p, header_stride_1p = 0;
	u32 hwformat, memory_bitwidth, pixelsize, sbwc_type;
	u32 width, height;
	u32 format, en_votf, bus_info;
	u32 strip_enable, strip_margin;
	int ret;

	ret = CALL_DMA_OPS(dma, dma_enable, enable);
	if (enable == 0)
		return 0;

	strip_enable = (param_set->stripe_input.total_count == 0) ? 0 : 1;

	switch (dma->id) {
	case BYRP_WDMA_BYR:
		if (param_set->dma_output_byr_processed.cmd)
			dma_output = &param_set->dma_output_byr_processed;
		else
			dma_output = &param_set->dma_output_byr;
		break;
	case BYRP_WDMA_RGBYHIST:
		dma_output = &param_set->dma_output_rgbyhist;
		break;
	case BYRP_WDMA_THSTAT_AWB:
		dma_output = &param_set->dma_output_thstat_awb;
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma->id);
		return SET_ERROR;
	}

	dma_input = &param_set->dma_input;
	if (strip_enable) {
		strip_margin = param_set->stripe_input.left_margin
				+ param_set->stripe_input.right_margin;
		width = dma_input->width > strip_margin ?
			dma_input->width - strip_margin : 0;
		if (!width) {
			err_hw("[BYRP] Invalid width, input width(%d) <= strip margin(%d)",
				dma_input->width, strip_margin);
			return SET_ERROR;
		}
	} else {
		width = dma_output->width;
	}

	height = dma_output->height;

	en_votf = dma_output->v_otf_enable;
	hwformat = dma_output->format;
	sbwc_type = dma_output->sbwc_type;
	memory_bitwidth = dma_output->bitwidth;
	pixelsize = dma_output->msb + 1;
	bus_info = 0x00000000UL; /* cache hint [6:4] */

	dbg_hw(2, "[API][%s]%s %dx%d, format: %d, bitwidth: %d\n",
		__func__, dma->name,
		width, height, hwformat, memory_bitwidth);

	*sbwc_en = comp_sbwc_en = is_hw_dma_get_comp_sbwc_en(sbwc_type, &comp_64b_align);
	if (!is_hw_dma_get_bayer_format(memory_bitwidth, pixelsize, hwformat, comp_sbwc_en,
						true, &format))
		ret |= CALL_DMA_OPS(dma, dma_set_format, format, DMA_FMT_BAYER);
	else
		ret |= DMA_OPS_ERROR;

	if (comp_sbwc_en == 0) {
		if (strip_enable)
			stride_1p = is_hw_dma_get_img_stride(memory_bitwidth, pixelsize, hwformat,
				param_set->stripe_input.full_width, 1, true);
		else
			stride_1p = is_hw_dma_get_img_stride(memory_bitwidth, pixelsize, hwformat,
					width, 1, true);
	} else if (comp_sbwc_en == 1 || comp_sbwc_en == 2) {
		stride_1p = is_hw_dma_get_payload_stride(comp_sbwc_en, pixelsize, width,
								comp_64b_align, quality_control,
								BYRP_COMP_BLOCK_WIDTH,
								BYRP_COMP_BLOCK_HEIGHT);
		header_stride_1p =
			is_hw_dma_get_header_stride(width, BYRP_COMP_BLOCK_WIDTH, 16);
	} else {
		return SET_ERROR;
	}

	ret |= CALL_DMA_OPS(dma, dma_set_comp_sbwc_en, comp_sbwc_en);
	ret |= CALL_DMA_OPS(dma, dma_set_size, width, height);
	ret |= CALL_DMA_OPS(dma, dma_set_img_stride, stride_1p, 0, 0);
	ret |= CALL_DMA_OPS(dma, dma_votf_enable, en_votf, 0);
	ret |= CALL_DMA_OPS(dma, dma_set_bus_info, bus_info);

	*payload_size = 0;
	switch (comp_sbwc_en) {
	case 1:
	case 2:
		ret |= CALL_DMA_OPS(dma, dma_set_comp_64b_align, comp_64b_align);
		ret |= CALL_DMA_OPS(dma, dma_set_header_stride, header_stride_1p, 0);
		*payload_size = ((height + BYRP_COMP_BLOCK_HEIGHT - 1) / BYRP_COMP_BLOCK_HEIGHT) * stride_1p;
		break;
	default:
		break;
	}

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_wdma_init);

#if IS_ENABLED(BYRP_USE_MMIO)
static int byrp_hw_rdma_create_mmio(struct is_common_dma *dma, void *base, u32 dma_id)
{
	void __iomem *base_reg;
	ulong available_bayer_format_map;
	int ret = SET_SUCCESS;
	char *name;

	name = __getname();
	if (!name) {
		err_hw("[BYRP] Failed to get name buffer");
		return -ENOMEM;
	}

	switch (dma_id) {
	case BYRP_RDMA_IMG:
		base_reg = base + byrp_regs[BYRP_R_BYR_RDMABYRIN_EN].sfr_offset;
		byrp_hw_g_rdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_RDMA_BYR");
		break;
	case BYRP_RDMA_HDR0:
		base_reg = base + byrp_regs[BYRP_R_BYR_RDMAHDRIN0_EN].sfr_offset;
		byrp_hw_g_rdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_RDMA_HDR0");
		break;
	case BYRP_RDMA_HDR1:
		base_reg = base + byrp_regs[BYRP_R_BYR_RDMAHDRIN1_EN].sfr_offset;
		byrp_hw_g_rdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_RDMA_HDR1");
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma_id);
		ret = SET_ERROR;
		goto err_dma_create;
	}
	ret = is_hw_dma_set_ops(dma);
	ret |= is_hw_dma_create(dma, base_reg, dma_id, name, available_bayer_format_map, 0, 0);

err_dma_create:
	__putname(name);

	return ret;
}
#else
static int byrp_hw_rdma_create_pmio(struct is_common_dma *dma, void *base, u32 dma_id)
{
	ulong available_bayer_format_map;
	int ret = SET_SUCCESS;
	char *name;

	name = __getname();
	if (!name) {
		err_hw("[BYRP] Failed to get name buffer");
		return -ENOMEM;
	}

	switch (dma_id) {
	case BYRP_RDMA_IMG:
		dma->reg_ofs = BYRP_R_BYR_RDMABYRIN_EN;
		dma->field_ofs = BYRP_F_BYR_RDMABYRIN_EN;

		byrp_hw_g_rdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_RDMA_BYR");
		break;
	case BYRP_RDMA_HDR0:
		dma->reg_ofs = BYRP_R_BYR_RDMAHDRIN0_EN;
		dma->field_ofs = BYRP_F_BYR_RDMAHDRIN0_EN;

		byrp_hw_g_rdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_RDMA_HDR0");
		break;
	case BYRP_RDMA_HDR1:
		dma->reg_ofs = BYRP_R_BYR_RDMAHDRIN1_EN;
		dma->field_ofs = BYRP_F_BYR_RDMAHDRIN1_EN;

		byrp_hw_g_rdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_RDMA_HDR1");
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma_id);
		ret = SET_ERROR;
		goto err_dma_create;
	}

	ret = pmio_dma_set_ops(dma);
	ret |= pmio_dma_create(dma, base, dma_id, name, available_bayer_format_map, 0, 0);

err_dma_create:
	__putname(name);

	return ret;
}
#endif

int byrp_hw_rdma_create(struct is_common_dma *dma, void *base, u32 dma_id)
{
#if IS_ENABLED(BYRP_USE_MMIO)
	return byrp_hw_rdma_create_mmio(dma, base, dma_id);
#else
	return byrp_hw_rdma_create_pmio(dma, base, dma_id);
#endif
}
KUNIT_EXPORT_SYMBOL(byrp_hw_rdma_create);

void byrp_hw_s_rdma_corex_id(struct is_common_dma *dma, u32 set_id)
{
	CALL_DMA_OPS(dma, dma_set_corex_id, set_id);
}

int byrp_hw_s_rdma_addr(struct is_common_dma *dma, dma_addr_t *addr, u32 plane,
	u32 num_buffers, int buf_idx, u32 comp_sbwc_en, u32 payload_size,
	u32 image_addr_offset, u32 header_addr_offset)
{
	int ret;
	u32 i;
	dma_addr_t address[IS_MAX_FRO];
	dma_addr_t header_addr[IS_MAX_FRO];

	switch (dma->id) {
	case BYRP_RDMA_IMG:
	case BYRP_RDMA_HDR0:
	case BYRP_RDMA_HDR1:
		for (i = 0; i < num_buffers; i++)
			address[i] = (dma_addr_t)(addr[i] + image_addr_offset);

		ret = CALL_DMA_OPS(dma, dma_set_img_addr, address, plane, buf_idx, num_buffers);
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma->id);
		return SET_ERROR;
	}

	if (comp_sbwc_en == 1 || comp_sbwc_en == 2) {
		/* Lossless, Lossy need to set header base address */
		switch (dma->id) {
		case BYRP_RDMA_IMG:
		case BYRP_RDMA_HDR0:
		case BYRP_RDMA_HDR1:
			for (i = 0; i < num_buffers; i++)
				header_addr[i] = addr[i] + payload_size + header_addr_offset;
			break;
		default:
			break;
		}
		ret = CALL_DMA_OPS(dma, dma_set_header_addr, header_addr,
			plane, buf_idx, num_buffers);
	}

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_rdma_addr);

#if IS_ENABLED(BYRP_USE_MMIO)
static int byrp_hw_wdma_create_mmio(struct is_common_dma *dma, void *base, u32 dma_id)
{
	void __iomem *base_reg;
	ulong available_bayer_format_map;
	int ret;
	char *name;

	name = __getname();
	if (!name) {
		err_hw("[BYRP] Failed to get name buffer");
		return -ENOMEM;
	}

	switch (dma_id) {
	case BYRP_WDMA_BYR:
		base_reg = base + byrp_regs[BYRP_R_BYR_WDMAZSL_EN].sfr_offset;
		byrp_hw_g_wdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_WDMA_BYR");
		break;
	case BYRP_WDMA_RGBYHIST:
		base_reg = base + byrp_regs[BYRP_R_STAT_WDMARGBYHIST_EN].sfr_offset;
		byrp_hw_g_wdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_WDMA_RGBYHIST");
		break;
	case BYRP_WDMA_THSTAT_AWB:
		base_reg = base + byrp_regs[BYRP_R_STAT_WDMATHSTATAWB_EN].sfr_offset;
		byrp_hw_g_wdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_WDMA_THSTAT_AWB");
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma_id);
		ret = SET_ERROR;
		goto err_dma_create;
	}
	ret = is_hw_dma_set_ops(dma);
	ret |= is_hw_dma_create(dma, base_reg, dma_id, name, available_bayer_format_map, 0, 0);

err_dma_create:
	__putname(name);

	return ret;
}
#else
static int byrp_hw_wdma_create_pmio(struct is_common_dma *dma, void *base, u32 dma_id)
{
	ulong available_bayer_format_map;
	int ret;
	char *name;

	name = __getname();
	if (!name) {
		err_hw("[BYRP] Failed to get name buffer");
		return -ENOMEM;
	}

	switch (dma_id) {
	case BYRP_WDMA_BYR:
		dma->reg_ofs = BYRP_R_BYR_WDMAZSL_EN;
		dma->field_ofs = BYRP_F_BYR_WDMAZSL_EN;

		byrp_hw_g_wdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_WDMA_BYR");
		break;
	case BYRP_WDMA_RGBYHIST:
		dma->reg_ofs = BYRP_R_STAT_WDMARGBYHIST_EN;
		dma->field_ofs = BYRP_F_STAT_WDMARGBYHIST_EN;

		byrp_hw_g_wdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_WDMA_RGBYHIST");
		break;
	case BYRP_WDMA_THSTAT_AWB:
		dma->reg_ofs = BYRP_R_STAT_WDMATHSTATAWB_EN;
		dma->field_ofs = BYRP_F_STAT_WDMATHSTATAWB_EN;

		byrp_hw_g_wdma_fmt_map(dma_id, &available_bayer_format_map);
		snprintf(name, PATH_MAX, "BYR_WDMA_THSTATAWB");
		break;

	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma_id);
		ret = SET_ERROR;
		goto err_dma_create;
	}
	ret = pmio_dma_set_ops(dma);
	ret |= pmio_dma_create(dma, base, dma_id, name, available_bayer_format_map, 0, 0);

err_dma_create:
	__putname(name);

	return ret;
}
#endif

int byrp_hw_wdma_create(struct is_common_dma *dma, void *base, u32 dma_id)
{
#if IS_ENABLED(BYRP_USE_MMIO)
	return byrp_hw_wdma_create_mmio(dma, base, dma_id);
#else
	return byrp_hw_wdma_create_pmio(dma, base, dma_id);
#endif
}
KUNIT_EXPORT_SYMBOL(byrp_hw_wdma_create);

void byrp_hw_s_wdma_corex_id(struct is_common_dma *dma, u32 set_id)
{
	CALL_DMA_OPS(dma, dma_set_corex_id, set_id);
}

int byrp_hw_s_wdma_addr(struct is_common_dma *dma, dma_addr_t *addr, u32 plane, u32 num_buffers,
		int buf_idx, u32 comp_sbwc_en, u32 payload_size,
		u32 image_addr_offset, u32 header_addr_offset)
{
	int ret;
	u32 i;
	dma_addr_t address[IS_MAX_FRO];
	dma_addr_t header_addr[IS_MAX_FRO];

	switch (dma->id) {
	case BYRP_WDMA_BYR:
	case BYRP_WDMA_RGBYHIST:
	case BYRP_WDMA_THSTAT_AWB:
		for (i = 0; i < num_buffers; i++)
			address[i] = (dma_addr_t)(addr[i] + image_addr_offset);

		ret = CALL_DMA_OPS(dma, dma_set_img_addr, address, plane, buf_idx, num_buffers);
		break;
	default:
		err_hw("[BYRP] NOT support DMA[%d]", dma->id);
		return SET_ERROR;
	}

	if (comp_sbwc_en == 1 || comp_sbwc_en == 2) {
		/* Lossless and Lossy, need to set header base address */
		switch (dma->id) {
		case BYRP_WDMA_BYR:
		case BYRP_WDMA_RGBYHIST:
		case BYRP_WDMA_THSTAT_AWB:
			for (i = 0; i < num_buffers; i++)
				header_addr[i] = (dma_addr_t)(addr[i] + payload_size + header_addr_offset);
			break;
		default:
			break;
		}

		ret = CALL_DMA_OPS(dma, dma_set_header_addr, header_addr,
			plane, buf_idx, num_buffers);
	}

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_wdma_addr);

int byrp_hw_s_corex_update_type(struct pablo_mmio *base, u32 set_id, u32 type)
{
	int ret = 0;

	switch (set_id) {
	case COREX_SET_A:
	case COREX_SET_B:
		BYRP_SET_F(base, BYRP_R_COREX_UPDATE_TYPE_0, BYRP_F_COREX_UPDATE_TYPE_0, type);
		break;
	case COREX_DIRECT:
		BYRP_SET_F(base, BYRP_R_COREX_UPDATE_TYPE_0, BYRP_F_COREX_UPDATE_TYPE_0, COREX_IGNORE);
		break;
	default:
		err_hw("[BYRP] invalid corex set_id");
		ret = -EINVAL;
		break;
	}

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_corex_update_type);

static int byrp_hw_wait_corex_idle(struct pablo_mmio *base)
{
	u32 busy;
	u32 try_cnt = 0;
	int ret = 0;

	do {
		udelay(1);

		try_cnt++;
		if (try_cnt >= BYRP_TRY_COUNT) {
			err_hw("[BYRP] fail to wait corex idle");
			ret = -try_cnt;
			break;
		}

		busy = BYRP_GET_F(base, BYRP_R_COREX_STATUS_0, BYRP_F_COREX_BUSY_0);
		dbg_hw(1, "[BYRP] %s busy(%d)\n", __func__, busy);

	} while (busy);

	return ret;
}

void byrp_hw_s_cmdq(struct pablo_mmio *base, u32 set_id, u32 num_buffers,
	dma_addr_t clh, u32 noh)
{
	int i;
	u32 fro_en = num_buffers > 1 ? 1 : 0;

	if (fro_en)
		BYRP_SET_R(base, BYRP_R_CMDQ_ENABLE, 0);

	for (i = 0; i < num_buffers; ++i) {
		if (i == 0)
			BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_L, BYRP_F_CMDQ_QUE_CMD_INT_GROUP_ENABLE,
				fro_en ? BYRP_INT_GRP_EN_MASK_FRO_FIRST : BYRP_INT_GRP_EN_MASK);
		else if (i < num_buffers - 1)
			BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_L, BYRP_F_CMDQ_QUE_CMD_INT_GROUP_ENABLE,
				BYRP_INT_GRP_EN_MASK_FRO_MIDDLE);
		else
			BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_L, BYRP_F_CMDQ_QUE_CMD_INT_GROUP_ENABLE,
				BYRP_INT_GRP_EN_MASK_FRO_LAST);

		if (clh && noh) {
			BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_H,
				BYRP_F_CMDQ_QUE_CMD_BASE_ADDR, DVA_36BIT_HIGH(clh));
			BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_M, BYRP_F_CMDQ_QUE_CMD_HEADER_NUM, noh);
			BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_M, BYRP_F_CMDQ_QUE_CMD_SETTING_MODE, 1);
		} else {
			BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_M, BYRP_F_CMDQ_QUE_CMD_SETTING_MODE, 3);
		}

		BYRP_SET_F(base, BYRP_R_CMDQ_QUE_CMD_L, BYRP_F_CMDQ_QUE_CMD_FRO_INDEX, i);
		BYRP_SET_R(base, BYRP_R_CMDQ_ADD_TO_QUEUE_0, 1);
	}
	BYRP_SET_R(base, BYRP_R_CMDQ_ENABLE, 1);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_cmdq);

int byrp_hw_s_corex_init(struct pablo_mmio *base, bool enable)
{
	u32 i;
	u32 reset_count = 0;
	int ret = 0;

	/*
	 * Check COREX idleness
	 */
	if (!enable) {
		BYRP_SET_F(base, BYRP_R_COREX_UPDATE_MODE_0, BYRP_F_COREX_UPDATE_MODE_0, SW_TRIGGER);

		byrp_hw_wait_corex_idle(base);

		BYRP_SET_F(base, BYRP_R_COREX_ENABLE, BYRP_F_COREX_ENABLE, 0x0);

		info_hw("[BYRP] %s disable done\n", __func__);
		return ret;
	}

	/*
	 * Set Fixed Value
	 */
	BYRP_SET_F(base, BYRP_R_COREX_ENABLE, BYRP_F_COREX_ENABLE, 0x1);
	BYRP_SET_F(base, BYRP_R_COREX_RESET, BYRP_F_COREX_RESET, 0x1);

	/* Changed from 1 to 0 when its operation finished */
	while (BYRP_GET_R(base, BYRP_R_COREX_RESET)) {
		if (reset_count > BYRP_TRY_COUNT) {
			err_hw("[BYRP] fail to wait corex reset");
			ret = -reset_count;
			break;
		}
		reset_count++;
	}

	/*
	 * Type selection
	 * Only type0 will be used.
	 */
	BYRP_SET_F(base, BYRP_R_COREX_TYPE_WRITE_TRIGGER, BYRP_F_COREX_TYPE_WRITE_TRIGGER, 0x1);

	/*
	 * write COREX_TYPE_WRITE to 1 means set type size in 0x80(128) range.
	 */
	for (i = 0; i < (23 * 2); i++)
		BYRP_SET_F(base, BYRP_R_COREX_TYPE_WRITE, BYRP_F_COREX_TYPE_WRITE, 0x0);

	/*
	 * config type0
	 * @BYRP_R_COREX_UPDATE_TYPE_0: 0: ignore, 1: copy from SRAM, 2: swap
	 * @BYRP_R_COREX_UPDATE_MODE_0: 0: HW trigger, 1: SW trigger
	 */
	BYRP_SET_F(base, BYRP_R_COREX_UPDATE_TYPE_0,
		BYRP_F_COREX_UPDATE_TYPE_0, COREX_COPY); /* Use Copy mode */
	BYRP_SET_F(base, BYRP_R_COREX_UPDATE_TYPE_1,
		BYRP_F_COREX_UPDATE_TYPE_1, COREX_IGNORE); /* Do not use TYPE1 */
	BYRP_SET_F(base, BYRP_R_COREX_UPDATE_MODE_0,
		BYRP_F_COREX_UPDATE_MODE_0, SW_TRIGGER); /* 1st frame uses SW Trigger, others use H/W Trigger */
	BYRP_SET_F(base, BYRP_R_COREX_UPDATE_MODE_1,
		BYRP_F_COREX_UPDATE_MODE_1, SW_TRIGGER); /* 1st frame uses SW Trigger, others use H/W Trigger */

	/* initialize type0 */
	BYRP_SET_F(base, BYRP_R_COREX_COPY_FROM_IP_0, BYRP_F_COREX_COPY_FROM_IP_0, 0x1);

	/*
	 * Check COREX idleness, again.
	 */
	byrp_hw_wait_corex_idle(base);

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_corex_init);

unsigned int byrp_hw_g_int0_state(struct pablo_mmio *base, bool clear,
	u32 num_buffers, u32 *irq_state)
{
	u32 src_all;

	/*
	 * src_all: per-frame based byrp IRQ status
	 * src_fro: FRO based byrp IRQ status
	 *
	 * final normal status: src_fro (start, line, end)
	 * final error status(src_err): src_all & ERR_MASK
	 */
	src_all = BYRP_GET_R(base, BYRP_R_INT_REQ_INT0);

	if (clear)
		BYRP_SET_R(base, BYRP_R_INT_REQ_INT0_CLEAR, src_all);

	*irq_state = src_all;

	return src_all;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_int0_state);

void byrp_hw_int0_error_handle(struct pablo_mmio *base)
{
	u32 cinfifo, coutfifo;

	cinfifo = BYRP_GET_R(base, BYRP_R_BYR_CINFIFO_INT);
	BYRP_SET_R(base, BYRP_R_BYR_CINFIFO_INT_CLEAR, cinfifo);

	coutfifo = BYRP_GET_R(base, BYRP_R_BYR_COUTFIFO_INT);
	BYRP_SET_R(base, BYRP_R_BYR_COUTFIFO_INT_CLEAR, coutfifo);

	info_hw("[BYRP] %s cinfifo(0x%x) coutfifo(0x%x)\n", __func__, cinfifo, coutfifo);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_int0_error_handle);

unsigned int byrp_hw_g_int0_mask(struct pablo_mmio *base)
{
	return BYRP_GET_R(base, BYRP_R_INT_REQ_INT0_ENABLE);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_int0_mask);

unsigned int byrp_hw_g_int1_state(struct pablo_mmio *base, bool clear,
	u32 num_buffers, u32 *irq_state)
{
	u32 src_all;

	/*
	 * src_all: per-frame based byrp IRQ status
	 * src_fro: FRO based byrp IRQ status
	 *
	 * final normal status: src_fro (start, line, end)
	 * final error status(src_err): src_all & ERR_MASK
	 */
	src_all = BYRP_GET_R(base, BYRP_R_INT_REQ_INT1);

	if (clear)
		BYRP_SET_R(base, BYRP_R_INT_REQ_INT1_CLEAR, src_all);

	*irq_state = src_all;

	return src_all;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_int1_state);

unsigned int byrp_hw_g_int1_mask(struct pablo_mmio *base)
{
	return BYRP_GET_R(base, BYRP_R_INT_REQ_INT1_ENABLE);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_int1_mask);

void byrp_hw_s_block_bypass(struct pablo_mmio *base, u32 set_id)
{
	/* DEBUG */
	/* Should not be controlled */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BITMASK0_BYPASS,
		BYRP_F_BYR_BITMASK0_BYPASS, 0x0);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN0_BYPASS,
		BYRP_F_BYR_CROPIN0_BYPASS, 0x0);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPZSL_BYPASS,
		BYRP_F_BYR_CROPZSL_BYPASS, 0x0);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPRGB_BYPASS,
		BYRP_F_BYR_CROPRGB_BYPASS, 0x0);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_BYPASS,
		BYRP_F_BYR_DISPARITY_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCDIRDETECTOR_BYPASS,
		BYRP_F_BYR_BPCDIRDETECTOR_BYPASS_DD, 0x0);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BYRHDR_BYPASS,
		BYRP_F_BYR_BYRHDR_BYPASS, 0x1);

	/* belows are controlled by nonbayer flag */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BLCNONBYRPED_BYPASS,
		BYRP_F_BYR_BLCNONBYRPED_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BLCNONBYRRGB_BYPASS,
		BYRP_F_BYR_BLCNONBYRRGB_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BLCNONBYRZSL_BYPASS,
		BYRP_F_BYR_BLCNONBYRZSL_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_WBGNONBYR_BYPASS,
		BYRP_F_BYR_WBGNONBYR_BYPASS, 0x1);

	/* Can be controlled bypass on/off */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_MPCBYRP0_BYPASS,
		BYRP_F_BYR_MPCBYRP0_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_AFIDENTBPC_BYPASS,
		BYRP_F_BYR_AFIDENTBPC_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_GAMMASENSOR0_BYPASS,
		BYRP_F_BYR_GAMMASENSOR0_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CGRAS_BYPASS_REG,
		BYRP_F_BYR_CGRAS_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCSUSPMAP_BYPASS,
		BYRP_F_BYR_BPCSUSPMAP_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCGGC_BYPASS,
		BYRP_F_BYR_BPCGGC_PHASE_SHIFT_ENABLE, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCFLATDETECTOR_BYPASS,
		BYRP_F_BYR_BPCFLATDETECTOR_BYPASS, 0x1);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCDIRDETECTOR_BYPASS,
		BYRP_F_BYR_BPCDIRDETECTOR_BYPASS, 0x1);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_block_bypass);

static void byrp_hw_s_block_crc(struct pablo_mmio *base, u32 set_id, u32 seed)
{
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CINFIFO_STREAM_CRC,
		BYRP_F_BYR_CINFIFO_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_COUTFIFO_STREAM_CRC,
		BYRP_F_BYR_COUTFIFO_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BLCNONBYRPED_STREAM_CRC,
		BYRP_F_BYR_BLCNONBYRPED_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BLCNONBYRRGB_STREAM_CRC,
		BYRP_F_BYR_BLCNONBYRRGB_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BLCNONBYRZSL_STREAM_CRC,
		BYRP_F_BYR_BLCNONBYRZSL_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN0_STREAM_CRC,
		BYRP_F_BYR_CROPIN0_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN1_STREAM_CRC,
		BYRP_F_BYR_CROPIN1_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BITMASK0_CRC,
		BYRP_F_BYR_BITMASK0_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BITMASK1_CRC,
		BYRP_F_BYR_BITMASK1_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_STREAM_CRC,
		BYRP_F_BYR_DTPNONBYR_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_AFIDENTBPC_STREAM_CRC,
		BYRP_F_BYR_AFIDENTBPC_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_GAMMASENSOR0_STREAM_CRC,
		BYRP_F_BYR_GAMMASENSOR0_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CGRAS_CRC,
		BYRP_F_BYR_CGRAS_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_WBGNONBYR_STREAM_CRC,
		BYRP_F_BYR_WBGNONBYR_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPRGB_STREAM_CRC,
		BYRP_F_BYR_CROPRGB_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BYRHDR_STREAM_CRC,
		BYRP_F_BYR_BYRHDR_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPZSL_STREAM_CRC,
		BYRP_F_BYR_CROPZSL_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_MPCBYRP0_STREAM_CRC,
		BYRP_F_BYR_MPCBYRP0_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCSUSPMAP_CRC_SEED,
		BYRP_F_BYR_BPCSUSPMAP_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCDIRDETECTOR_CRC_SEED,
		BYRP_F_BYR_BPCDIRDETECTOR_CRC_SEED, seed);

	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_SDC_CRC_0, seed);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_SDC_CRC_1, seed);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_SDC_CRC_2, seed);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_SDC_CRC_3, seed);

	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_C_LOADER_HEADER_CRC_SEED,
		BYRP_F_C_LOADER_HEADER_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_C_LOADER_PAYLOAD_CRC_SEED,
		BYRP_F_C_LOADER_PAYLOAD_CRC_SEED, seed);

#if IS_ENABLED(CONFIG_PABLO_V12_1_0)
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_GAMMASENSOR1_STREAM_CRC,
		BYRP_F_BYR_GAMMASENSOR1_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_GAMMASENSOR2_STREAM_CRC,
		BYRP_F_BYR_GAMMASENSOR2_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_PREDNS0_STREAM_CRC,
		BYRP_F_BYR_PREDNS0_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_PREDNS1_STREAM_CRC,
		BYRP_F_BYR_PREDNS1_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_PREDNS2_STREAM_CRC,
		BYRP_F_BYR_PREDNS2_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_PREGAMMA_STREAM_CRC,
		BYRP_F_BYR_PREGAMMA_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_WBGGAMMA_STREAM_CRC,
		BYRP_F_BYR_WBGGAMMA_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_POSTGAMMA_STREAM_CRC,
		BYRP_F_BYR_POSTGAMMA_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_LUMALSC_CRC,
		BYRP_F_BYR_LUMALSC_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_THSTATAWB_CRC,
		BYRP_F_BYR_THSTATAWB_CRC_SEED, seed);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_LUMALSC_CRC,
		BYRP_F_BYR_LUMALSC_CRC_SEED, seed);
#endif
}

void byrp_hw_s_bitmask(struct pablo_mmio *base, u32 set_id, u32 bit_in, u32 bit_out)
{
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BITMASK0_BITTAGEIN,
		BYRP_F_BYR_BITMASK0_BITTAGEIN, bit_in);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BITMASK0_BITTAGEOUT,
		BYRP_F_BYR_BITMASK0_BITTAGEOUT, bit_out);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_bitmask);

static void byrp_hw_s_pixel_order(struct pablo_mmio *base, u32 set_id, u32 pixel_order)
{
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_PIXEL_ORDER,
		 BYRP_F_BYR_DTPNONBYR_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_PREDNS0_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_PREDNS1_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CGRAS_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_WBGNONBYR_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BYRHDR_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_MPCBYRP0_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCSUSPMAP_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCGGC_PIXEL_ORDER, pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCFLATDETECTOR_PIXEL_ORDER,
		pixel_order);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCDIRDETECTOR_PIXEL_ORDER,
		pixel_order);
}

static void byrp_hw_s_non_byr_pattern(struct pablo_mmio *base, u32 set_id, u32 non_byr_pattern)
{
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DTPNONBYR_PIXEL_ORDER,
		 BYRP_F_BYR_DTPNONBYR_NON_BYR_PATTERN, non_byr_pattern);

	/* 0: Bayer, 1: Tetra(only) */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_BYPASS,
		non_byr_pattern == 1 ? 1 : 0);

/*
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CGRAS_CONFIG,
		 BYRP_F_BYR_CGRAS_NON_BYR_MODE_EN, non_byr_pattern ? 1 : 0);

	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CGRAS_CONFIG,
		 BYRP_F_BYR_CGRAS_NON_BYR_PATTERN, non_byr_pattern);
*/

	/* 0: Normal Bayer, 1: 2x2(Tetra), 2: 3x3(Nona), 3: 4x4 pattern */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_WBGNONBYR_PIXEL_ORDER,
		 BYRP_F_BYR_WBGNONBYR_NON_BYR_PATTERN, non_byr_pattern);

	/* 0: Bayer, 1: Tetra(only) */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_MPCBYRP0_OP_MODE,
		non_byr_pattern == 1 ? 1 : 0);

	/* 0: Bayer, 1: Tetra(only) */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCSUSPMAP_CFA_TYPE,
		non_byr_pattern == 1 ? 1 : 0);

	/* Caution! 1: Bayer, 2: Tetra(only) */
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCGGC_PHASE_SHIFT_ENABLE,
		 BYRP_F_BYR_BPCGGC_PHASE_SHIFT_MODE, non_byr_pattern == 1 ? 2 : 1);

	/* 0: Bayer, 1: Tetra(only) */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCFLATDETECTOR_CFA_TYPE,
		non_byr_pattern == 1 ? 1 : 0);

	/* 0: Bayer, 1: Tetra(only) */
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCDIRDETECTOR_CFA_TYPE,
		non_byr_pattern == 1 ? 1 : 0);
}

static void byrp_hw_s_mono_mode(struct pablo_mmio *base, u32 set_id, bool enable)
{
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BPCDIRDETECTOR_MONO_MODE_EN, enable);
}

void byrp_hw_s_bcrop_size(struct pablo_mmio *base, u32 set_id, u32 bcrop_num,
	u32 x, u32 y, u32 width, u32 height)
{
	switch (bcrop_num) {
	case BYRP_BCROP_BYR:
		dbg_hw(1, "[API][%s] BYRP_BCROP_BYR -> x(%d), y(%d), w(%d), h(%d)\n",
			__func__, x, y, width, height);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN0_BYPASS,
			BYRP_F_BYR_CROPIN0_BYPASS, 0x0);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN0_START_X,
			BYRP_F_BYR_CROPIN0_START_X, x);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN0_START_Y,
			BYRP_F_BYR_CROPIN0_START_Y, y);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN0_SIZE_X,
			BYRP_F_BYR_CROPIN0_SIZE_X, width);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPIN0_SIZE_Y,
			BYRP_F_BYR_CROPIN0_SIZE_Y, height);
		break;
	case BYRP_BCROP_ZSL:
		dbg_hw(1, "[API][%s] BYRP_BCROP_ZSL -> x(%d), y(%d), w(%d), h(%d)\n",
			__func__, x, y, width, height);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPZSL_BYPASS,
			BYRP_F_BYR_CROPZSL_BYPASS, 0x0);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPZSL_START_X,
			BYRP_F_BYR_CROPZSL_START_X, x);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPZSL_START_Y,
			BYRP_F_BYR_CROPZSL_START_Y, y);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPZSL_SIZE_X,
			BYRP_F_BYR_CROPZSL_SIZE_X, width);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPZSL_SIZE_Y,
			BYRP_F_BYR_CROPZSL_SIZE_Y, height);
		break;
	case BYRP_BCROP_RGB:
		dbg_hw(1, "[API][%s] BYRP_BCROP_RGB -> x(%d), y(%d), w(%d), h(%d)\n",
			__func__, x, y, width, height);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPRGB_BYPASS,
			BYRP_F_BYR_CROPRGB_BYPASS, 0x0);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPRGB_START_X,
			BYRP_F_BYR_CROPRGB_START_X, x);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPRGB_START_Y,
			BYRP_F_BYR_CROPRGB_START_Y, y);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPRGB_SIZE_X,
			BYRP_F_BYR_CROPRGB_SIZE_X, width);
		BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_CROPRGB_SIZE_Y,
			BYRP_F_BYR_CROPRGB_SIZE_Y, height);
		break;
	default:
		err_hw("[BYRP] invalid bcrop number[%d]", bcrop_num);
		break;
	}
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_bcrop_size);

void byrp_hw_s_grid_cfg(struct pablo_mmio *base, struct byrp_grid_cfg *cfg)
{
	u32 val;

	val = 0;
	val = BYRP_SET_V(base, val, BYRP_F_BYR_CGRAS_BINNING_X, cfg->binning_x);
	val = BYRP_SET_V(base, val, BYRP_F_BYR_CGRAS_BINNING_Y, cfg->binning_y);
	BYRP_SET_R(base, BYRP_R_BYR_CGRAS_BINNING_X, val);

	BYRP_SET_F(base, BYRP_R_BYR_CGRAS_CROP_START_X,
			BYRP_F_BYR_CGRAS_CROP_START_X, cfg->crop_x);
	BYRP_SET_F(base, BYRP_R_BYR_CGRAS_CROP_START_Y,
			BYRP_F_BYR_CGRAS_CROP_START_Y, cfg->crop_y);

	val = 0;
	val = BYRP_SET_V(base, val, BYRP_F_BYR_CGRAS_CROP_RADIAL_X, cfg->crop_radial_x);
	val = BYRP_SET_V(base, val, BYRP_F_BYR_CGRAS_CROP_RADIAL_Y, cfg->crop_radial_y);
	BYRP_SET_R(base, BYRP_R_BYR_CGRAS_CROP_START_REAL, val);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_grid_cfg);

void byrp_hw_s_disparity_size(struct pablo_mmio *base, u32 set_id,
	struct is_hw_size_config *size_config)
{
	u32 binning_x, binning_y;

	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_SENSOR_WIDTH,
		BYRP_F_BYR_DISPARITY_SENSOR_WIDTH, size_config->sensor_calibrated_width);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_SENSOR_HEIGHT,
		BYRP_F_BYR_DISPARITY_SENSOR_HEIGHT, size_config->sensor_calibrated_height);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_CROP_X,
		BYRP_F_BYR_DISPARITY_CROP_X, size_config->sensor_crop_x);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_CROP_Y,
		BYRP_F_BYR_DISPARITY_CROP_Y, size_config->sensor_crop_y);

	if (size_config->sensor_binning_x < 2000)
		binning_x = 0;
	else if (size_config->sensor_binning_x < 4000)
		binning_x = 1;
	else if (size_config->sensor_binning_x < 8000)
		binning_x = 2;
	else
		binning_x = 3;

	if (size_config->sensor_binning_y < 2000)
		binning_y = 0;
	else if (size_config->sensor_binning_y < 4000)
		binning_y = 1;
	else if (size_config->sensor_binning_y < 8000)
		binning_y = 2;
	else
		binning_y = 3;

	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_BINNING,
		BYRP_F_BYR_DISPARITY_BINNING_X, binning_x);
	BYRP_SET_F(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_DISPARITY_BINNING,
		BYRP_F_BYR_DISPARITY_BINNING_Y, binning_y);
}

void byrp_hw_s_chain_size(struct pablo_mmio *base, u32 set_id, u32 dma_width, u32 dma_height)
{
	u32 val = 0;

	val = BYRP_SET_V(base, val, BYRP_F_GLOBAL_IMG_WIDTH, dma_width);
	val = BYRP_SET_V(base, val, BYRP_F_GLOBAL_IMG_HEIGHT, dma_height);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_GLOBAL_IMAGE_RESOLUTION, val);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_chain_size);

void byrp_hw_s_mpc_size(struct pablo_mmio *base, u32 set_id, u32 width, u32 height)
{
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_MPCBYRP0_IMAGE_WIDTH, width);
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_MPCBYRP0_IMAGE_HEIGHT, height);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_mpc_size);

void byrp_hw_s_otf_hdr_size(struct pablo_mmio *base, bool enable, u32 set_id, u32 height)
{
	BYRP_SET_R(base, GET_COREX_OFFSET(set_id) + BYRP_R_BYR_BYRHDR_BYPASS, !enable);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_otf_hdr_size);

void byrp_hw_s_core(struct pablo_mmio *base, u32 num_buffers, u32 set_id,
	struct byrp_param_set *param_set)
{
	bool cinfifo_en, coutfifo_en, mono_mode_en, hdr_en, dtp_en;
	u32 bit_in;
	u32 width, height;
	u32 pixel_order;
	u32 non_byr_pattern;
	u32 seed;

	cinfifo_en = 0; /* Use only RDMA input */
	coutfifo_en = 1; /* OTF to RGBP */
	non_byr_pattern = 0;
	mono_mode_en = 0;
	dtp_en = 0;
	hdr_en = param_set->dma_input_hdr.cmd; /* According to rdma cmd */
	bit_in = param_set->dma_input.msb + 1; /* valid bittage */
	width = param_set->dma_input.dma_crop_width;
	height = param_set->dma_input.dma_crop_height;
	pixel_order = param_set->dma_input.order;

	byrp_hw_s_cinfifo(base, set_id, cinfifo_en);
	byrp_hw_s_coutfifo(base, set_id, coutfifo_en);
	byrp_hw_s_common(base, set_id, param_set, bit_in);
	byrp_hw_s_int_mask(base, set_id);
	byrp_hw_s_pixel_order(base, set_id, pixel_order);
	byrp_hw_s_non_byr_pattern(base, set_id, non_byr_pattern);
	byrp_hw_s_mono_mode(base, set_id, mono_mode_en);
	byrp_hw_s_secure_id(base, set_id);
	byrp_hw_s_byrhdr(base, set_id, hdr_en);

	seed = is_get_debug_param(IS_DEBUG_PARAM_CRC_SEED);
	if (unlikely(seed))
		byrp_hw_s_block_crc(base, set_id, seed);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_s_core);

u32 byrp_hw_g_rdma_max_cnt(void)
{
	return BYRP_RDMA_MAX;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_rdma_max_cnt);

u32 byrp_hw_g_wdma_max_cnt(void)
{
	return BYRP_WDMA_MAX;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_wdma_max_cnt);

u32 byrp_hw_g_reg_cnt(void)
{
	return BYRP_REG_CNT + BYRP_LUT_REG_CNT;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_reg_cnt);

u32 byrp_hw_g_rdma_cfg_max_cnt(void)
{
	return BYRP_RDMA_CFG_MAX;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_rdma_cfg_max_cnt);

u32 byrp_hw_g_wdma_cfg_max_cnt(void)
{
	return BYRP_WDMA_CFG_MAX;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_wdma_cfg_max_cnt);

void byrp_hw_update_param(struct byrp_param *src, IS_DECLARE_PMAP(pmap),
	struct byrp_param_set *dst)
{
	/* check input */
	if (test_bit(PARAM_BYRP_DMA_INPUT, pmap))
		memcpy(&dst->dma_input, &src->dma_input,
				sizeof(struct param_dma_input));

	if (test_bit(PARAM_BYRP_HDR, pmap))
		memcpy(&dst->dma_input_hdr, &src->hdr,
				sizeof(struct param_dma_input));

	if (test_bit(PARAM_BYRP_HDR1, pmap))
		memcpy(&dst->dma_input_hdr1, &src->hdr1,
				sizeof(struct param_dma_input));

	if (test_bit(PARAM_BYRP_STRIPE_INPUT, pmap))
		memcpy(&dst->stripe_input, &src->stripe_input,
				sizeof(struct param_stripe_input));

	/* check output */
	if (test_bit(PARAM_BYRP_BYR, pmap))
		memcpy(&dst->dma_output_byr, &src->byr,
				sizeof(struct param_dma_output));

	if (test_bit(PARAM_BYRP_BYR_PROCESSED, pmap))
		memcpy(&dst->dma_output_byr_processed, &src->byr_processed,
				sizeof(struct param_dma_output));

	if (test_bit(PARAM_BYRP_RGBY_HIST, pmap))
		memcpy(&dst->dma_output_rgbyhist, &src->rgbyhist,
				sizeof(struct param_dma_output));

	if (test_bit(PARAM_BYRP_THSTAT_AWB, pmap))
		memcpy(&dst->dma_output_thstat_awb, &src->thstat_awb,
				sizeof(struct param_dma_output));

}
KUNIT_EXPORT_SYMBOL(byrp_hw_update_param);

int byrp_hw_g_rdma_param_ptr(u32 id, struct is_frame *dma_frame, struct byrp_param_set *param_set,
	char *name, dma_addr_t **dma_frame_dva, struct param_dma_input **pdi,
	pdma_addr_t **param_set_dva)
{
	int ret = 0;

	switch (id) {
	case BYRP_RDMA_CFG_IMG:
		*dma_frame_dva = dma_frame->dvaddr_buffer;
		*pdi = &param_set->dma_input;
		*param_set_dva = param_set->input_dva;
		sprintf(name, "byrp_img");
		break;
	case BYRP_RDMA_CFG_HDR0:
		*dma_frame_dva = dma_frame->dva_byrp_hdr;
		*pdi = &param_set->dma_input_hdr;
		*param_set_dva = param_set->input_dva_hdr;
		sprintf(name, "byrp_hdr0");
		break;
	case BYRP_RDMA_CFG_HDR1:
		*dma_frame_dva = dma_frame->dva_byrp_hdr1;
		*pdi = &param_set->dma_input_hdr1;
		*param_set_dva = param_set->input_dva_hdr1;
		sprintf(name, "byrp_hdr1");
		break;
	default:
		ret = -EINVAL;
		err_hw("[BYRP] invalid rdma param id[%d]", id);
		break;
	}

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_rdma_param_ptr);

int byrp_hw_g_wdma_param_ptr(u32 id, struct is_frame *dma_frame, struct byrp_param_set *param_set,
	char *name, dma_addr_t **dma_frame_dva, struct param_dma_output **pdo,
	pdma_addr_t **param_set_dva)
{
	int ret = 0;

	switch (id) {
	case BYRP_WDMA_CFG_BYR:
		*dma_frame_dva = dma_frame->dva_byrp_byr;
		*pdo = &param_set->dma_output_byr;
		*param_set_dva = param_set->output_dva_byr;
		sprintf(name, "byrp_wdma_befor_wbg");
		break;
	case BYRP_WDMA_CFG_BYR_PROCESSED:
		*dma_frame_dva = dma_frame->dva_byrp_byr_processed;
		*pdo = &param_set->dma_output_byr_processed;
		*param_set_dva = param_set->output_dva_byr_processed;
		sprintf(name, "byrp_wdma_after_wbg");
		break;
	case BYRP_WDMA_CFG_RGBYHIST:
		*dma_frame_dva = dma_frame->dva_byrp_rgby_hist;
		*pdo = &param_set->dma_output_rgbyhist;
		*param_set_dva = param_set->output_dva_byrrgbyhist;
		sprintf(name, "byrp_wdma_rgbyhist");
		break;
	case BYRP_WDMA_CFG_THSTAT_AWB:
		*dma_frame_dva = dma_frame->dva_byrp_thstat_awb;
		*pdo = &param_set->dma_output_thstat_awb;
		*param_set_dva = param_set->output_dva_thstat_awb;
		sprintf(name, "byrp_wdma_thstat_awb");
		break;
	default:
		ret = -EINVAL;
		err_hw("[BYRP] invalid wdma param id[%d]", id);
		break;
	}

	return ret;
}
KUNIT_EXPORT_SYMBOL(byrp_hw_g_wdma_param_ptr);

void byrp_hw_init_pmio_config(struct pmio_config *cfg)
{
	cfg->num_corexs = 2;
	cfg->corex_stride = 0x8000;

	cfg->volatile_table = &byrp_volatile_table;
	cfg->wr_noinc_table = &byrp_wr_noinc_table;

	cfg->max_register = BYRP_R_BYR_THSTATAWB_CRC;
	cfg->num_reg_defaults_raw = (BYRP_R_BYR_THSTATAWB_CRC >> 2) + 1;
	cfg->dma_addr_shift = 4;

	cfg->ranges = byrp_range_cfgs;
	cfg->num_ranges = ARRAY_SIZE(byrp_range_cfgs);

	cfg->fields = byrp_field_descs;
	cfg->num_fields = ARRAY_SIZE(byrp_field_descs);
}
KUNIT_EXPORT_SYMBOL(byrp_hw_init_pmio_config);
