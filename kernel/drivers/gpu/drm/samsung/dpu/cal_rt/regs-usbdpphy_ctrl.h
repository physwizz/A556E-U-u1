/* SPDX-License-Identifier: GPL-2.0-only
 *
 * regs-usbdpphy_ctrl.h
 *
 * Copyright (c) 2021 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Register definition file for Samsung DisplayPort driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _USBDPPHY_CTRL_REGS_H_
#define _USBDPPHY_CTRL_REGS_H_

/* USBDPPHY_CTRL base address : 0x178D0000 */

#define PHY_RST_CTRL 				(0x0)
#define PIPE_LANE0_RESET_N_OVRD_EN 		(0x1 << 5)
#define PIPE_LANE0_RESET_N 			(0x1 << 4)
#define PHY_RESET_OVRD_EN 			(0x1 << 1)
#define PHY_RESET 				(0x1 << 0)

#define PHY_CR_PARA_CON0 			(0x4)
#define PHY0_CR_PARA_ADDR 			(0xFFFF << 16)
#define PHY0_CR_PARA_CLK 			(0x1 << 8)
#define PHY0_CR_PARA_ACK 			(0x1 << 4)
#define PHY0_CR_PARA_SEL 			(0x1 << 0)

#define PHY_CR_PARA_CON1 			(0x8)
#define PHY0_CR_PARA_RD_DATA 			(0xFFFF << 16)
#define PHY0_CR_PARA_RD_EN 			(0x1 << 0)

#define PHY_CR_PARA_CON2 			(0xC)
#define PHY0_CR_PARA_WR_DATA 			(0xFFFF << 16)
#define PHY0_CR_PARA_WR_EN 			(0x1 << 0)

#define PHY_CONFIG0 				(0x100)
#define PHY_SS_TX0_BYPASS_EQ_CALC 		(0x1 << 28)
#define PHY_SS_TX0_VREGDRV_BYP 			(0x1 << 27)
#define PHY_SS_RX0_TERM_ACDC 			(0x1 << 26)
#define PHY_SS_LANE0_RX2TX_PAR_LB_EN 		(0x1 << 25)
#define PHY_RTUNE_ACK 				(0x1 << 24)
#define PHY_RTUNE_REQ 				(0x1 << 23)
#define PHY0_SUP_PRE_HP 			(0x1 << 22)
#define PHY0_SS_MPLLA_SSC_EN 			(0x1 << 21)
#define PHY0_SS_MPLLA_FORCE_EN 			(0x1 << 20)
#define PHY0_REF_USE_PAD 			(0x1 << 19)
#define PHY0_REF_REPEAT_CLK_EN 			(0x1 << 18)
#define PHY0_REF_ALT_CLK_LP_SEL 		(0x1 << 17)
#define PHY0_PMA_PWR_STABLE 			(0x1 << 15)
#define PHY0_PCS_PWR_STABLE 			(0x1 << 14)
#define PHY0_HDMIMODE_ENABLE 			(0x1 << 13)
#define PHY0_CMN_OUT_GENERIC_BUS 		(0x1F << 8)
#define PHY0_CMN_IN_GENERIC_BUS 		(0x1F << 3)
#define PHY0_ANA_PWR_STABLE 			(0x1 << 2)
#define PHY0_ANA_PWR_EN 			(0x1 << 1)
#define PG_MODE_EN 				(0x1 << 0)

#define PHY_CONFIG1 				(0x104)
#define HDMI_MPLLB_HDMI_PIXEL_CLK_DIV 		(0x3 << 29)
#define HDMI_MPLLB_HDMI_PIXEL_CLK 		(0x1 << 28)
#define HDMI_MPLLB_HDMI_DIV 			(0x7 << 25)
#define EXT_PCLK_REQ 				(0x1 << 24)
#define PIPE_RX0_EBUFF_LOCATION 		(0x1FF << 15)
#define PIPE_RX0_IDLE_LOS_CNT 			(0x3F << 9)
#define PIPE_RX_RECAL_CONT_EN 			(0x1 << 8)
#define PIPE_RX_CDR_LEGACY_EN 			(0x1 << 7)
#define PIPE_LANE0_TX2RX_LOOPBK 		(0x1 << 6)
#define PIPE_LANE0_PHY_SRC_SEL 			(0x3 << 4)
#define PIPE_LANE0_LINK_NUM 			(0xF << 0)

#define PHY_CONFIG2 				(0x108)
#define SS_LANE1_ACTIVE 			(0x1 << 26)
#define SS_LANE0_ACTIVE 			(0x1 << 25)
#define PHY_TEST_POWERDOWN 			(0x1 << 24)
#define PHY_TEST_BURNIN 			(0x1 << 23)
#define PHY0_TEST_TX_REF_CLK_EN 		(0x1 << 22)
#define PHY0_TEST_STOP_CLK_EN 			(0x1 << 21)
#define PHY0_TEST_FLYOVER_EN 			(0x1 << 20)
#define PHY0_PMA_PWR_EN 			(0x1 << 19)
#define PHY0_PCS_PWR_EN 			(0x1 << 18)
#define UPCS_PWR_EN 				(0x1 << 17)
#define UPCS_PWR_STABLE 			(0x1 << 16)
#define UPCS_PIPE_CONFIG 			(0xFFFF << 0)

#define PHY_CONFIG3 				(0x10C)
#define PHY0_REXT_EN 				(0x1 << 8)
#define PHY0_REXT_CTRL 				(0x3F << 0)

#define PHY_SRAM_CON 				(0x110)
#define PHY0_SRAM_INIT_DONE 			(0x1 << 2)
#define PHY0_SRAM_EXT_LD_DONE 			(0x1 << 1)
#define PHY0_SRAM_BYPASS 			(0x1 << 0)

#define PHY_EXT_CONFIG0 			(0x114)
#define PHY_EXT_DCO_RANGE 			(0x3 << 15)
#define PHY_EXT_DCO_FINETUNE 			(0x3F << 9)
#define PHY_EXT_BS_TX_LOWSWING 			(0x1 << 8)
#define PHY_EXT_BS_RX_LEVEL 			(0x7 << 5)
#define PHY_EXT_BS_RX_BIGSWING 			(0x1 << 4)
#define PHY_EXT_CTRL_SEL 			(0x1 << 0)

#define PHY_EXT_CONFIG1 			(0x118)
#define PHY_EXT_MPLLA_CP_PROP_GS 		(0x7F << 24)
#define PHY_EXT_MPLLA_CP_PROP 			(0x7F << 16)
#define PHY_EXT_MPLLA_CP_INT_GS 		(0x7F << 8)
#define PHY_EXT_MPLLA_CP_INT 			(0x7F << 0)

#define PHY_EXT_CONFIG2 			(0x11C)
#define PHY_EXT_MPLLA_DIV_MULTIPLIER 		(0xFF << 4)
#define PHY_EXT_MPLLA_DIV_CLK_EN 		(0x1 << 1)
#define PHY_EXT_MPLLA_DIV5_CLK_EN 		(0x1 << 0)

#define PHY_EXT_CONFIG3 			(0x120)
#define PHY_EXT_MPLLA_FRACN_EN 			(0x1 << 16)
#define PHY_EXT_MPLLA_FRACN_DEN 		(0xFFFF << 0)

#define PHY_EXT_CONFIG4 			(0x124)
#define PHY_EXT_MPLLA_FRACN_REM 		(0xFFFF << 16)
#define PHY_EXT_MPLLA_FRACN_QUOT 		(0xFFFF << 0)

#define PHY_EXT_CONFIG5 			(0x128)
#define PHY_EXT_MPLLA_MULTIPLIER 		(0xFFF << 4)
#define PHY_EXT_MPLLA_FREQ_VCO 			(0x3 << 0)

#define PHY_EXT_CONFIG6 			(0x12C)
#define PHY_EXT_MPLLA_SSC_PEAK 			(0xFFFFF << 0)

#define PHY_EXT_CONFIG7 			(0x130)
#define PHY_EXT_MPLLA_SSC_STEPSIZE 		(0x1FFFFF << 0)

#define PHY_EXT_CONFIG8 			(0x134)
#define PHY_EXT_RX_CDR_VCO_LOWFREQ_G2 		(0x3 << 30)
#define PHY_EXT_RX_CDR_VCO_LOWFREQ_G1 		(0x3 << 28)
#define PHY_EXT_RX_ADAPT_DFE_EN_G2 		(0x3 << 26)
#define PHY_EXT_RX_ADAPT_DFE_EN_G1 		(0x3 << 24)
#define PHY_EXT_RX_ADAPT_AFE_EN_G2 		(0x3 << 22)
#define PHY_EXT_RX_ADAPT_AFE_EN_G1 		(0x3 << 20)
#define PHY_EXT_REF_RANGE 			(0x7 << 12)
#define PHY_EXT_REF_CLK_MPLLA_DIV 		(0x7 << 8)
#define PHY_EXT_MPLLA_WORD_DIV2_EN 		(0x1 << 6)
#define PHY_EXT_MPLLA_V2I 			(0x3 << 4)
#define PHY_EXT_MPLLA_TX_CLK_DIV 		(0x7 << 1)
#define PHY_EXT_MPLLA_SSC_UP_SPREAD 		(0x1 << 0)

#define PHY_EXT_CONFIG9 			(0x138)
#define PHY_EXT_RX_EQ_ATT_LVL_G2 		(0x3F << 24)
#define PHY_EXT_RX_EQ_ATT_LVL_G1 		(0x3F << 16)
#define PHY_EXT_RX_EQ_AFE_GAIN_G2 		(0xFF << 8)
#define PHY_EXT_RX_EQ_AFE_GAIN_G1 		(0xFF << 0)

#define PHY_EXT_CONFIG10 			(0x13C)
#define PHY_EXT_RX_EQ_CTLE_BOOST_G2 		(0x3FF << 12)
#define PHY_EXT_RX_EQ_CTLE_BOOST_G1 		(0x3FF << 0)

#define PHY_EXT_CONFIG11 			(0x140)
#define PHY_EXT_RX_EQ_DELTA_IQ_G2 		(0xFF << 8)
#define PHY_EXT_RX_EQ_DELTA_IQ_G1 		(0xFF << 0)

#define PHY_EXT_CONFIG12 			(0x144)
#define PHY_EXT_RX_EQ_DFE_TAP1_G2 		(0xFFFF << 16)
#define PHY_EXT_RX_EQ_DFE_TAP1_G1 		(0xFFFF << 0)

#define PHY_EXT_CONFIG13 			(0x148)
#define PHY_EXT_RX_REF_LD_VAL_G2 		(0x7F << 12)
#define PHY_EXT_RX_REF_LD_VAL_G1 		(0x7F << 4)
#define PHY_EXT_RX_DCC_BYP_AC_CAP 		(0x3 << 0)

#define PHY_EXT_CONFIG14 			(0x14C)
#define PHY_EXT_RX_SIGDET_HF_THRESHOLD_G2 	(0x3F << 12)
#define PHY_EXT_RX_SIGDET_HF_THRESHOLD_G1 	(0x3F << 4)
#define PHY_EXT_RX_SIGDET_HF_FILT_DIS 		(0x1 << 1)
#define PHY_EXT_RX_SIGDET_HF_EN 		(0x1 << 0)

#define PHY_EXT_CONFIG15 			(0x150)
#define PHY_EXT_RX_TERM_CTRL 			(0x7 << 20)
#define PHY_EXT_RX_SIGDET_LF_THRESHOLD_G2 	(0x3F << 12)
#define PHY_EXT_RX_SIGDET_LF_THRESHOLD_G1 	(0x3F << 4)
#define PHY_EXT_RX_SIGDET_LF_FILTER_EN 		(0x1 << 1)
#define PHY_EXT_RX_SIGDET_LF_EN 		(0x1 << 0)

#define PHY_EXT_CONFIG16 			(0x154)
#define PHY_EXT_RX_VCO_LD_VAL_G2 		(0x1FFF << 16)
#define PHY_EXT_RX_VCO_LD_VAL_G1 		(0x1FFF << 0)

#define PHY_EXT_CONFIG17 			(0x158)
#define PHY_EXT_TX_DCC_BYP_AC_CAP 		(0x3 << 16)
#define PHY_EXT_TX_ANA_RBOOST_EN 		(0xF << 12)
#define PHY_EXT_TX_ANA_IBOOST_EN 		(0x3 << 8)
#define PHY_EXT_SUP_RX_VCO_VREF_SEL 		(0x7 << 4)
#define PHY_EXT_RX_VREF_CTRL 			(0x7 << 0)

#define PHY_EXT_CONFIG18 			(0x15C)
#define PHY_EXT_TX_EQ_OVRD_G2 			(0x3 << 26)
#define PHY_EXT_TX_EQ_OVRD_G1 			(0x3 << 24)
#define PHY_EXT_TX_EQ_MAIN_G2 			(0xFFF << 12)
#define PHY_EXT_TX_EQ_MAIN_G1 			(0xFFF << 0)

#define PHY_EXT_CONFIG19 			(0x160)
#define PHY_EXT_TX_EQ_POST_G2 			(0xFFF << 12)
#define PHY_EXT_TX_EQ_POST_G1 			(0xFFF << 0)

#define PHY_EXT_CONFIG20 			(0x164)
#define PHY_EXT_TX_EQ_PRE_G2 			(0xFFF << 12)
#define PHY_EXT_TX_EQ_PRE_G1 			(0xFFF << 0)

#define PHY_EXT_CONFIG21 			(0x168)
#define PHY_EXT_TX_VSWING_LVL 			(0x7 << 4)
#define PHY_EXT_TX_TERM_CTRL 			(0x7 << 0)

#define TCA_CONFIG 				(0x16C)
#define TCA_MISC_CTRL 				(0x3F << 8)
#define TCA_VBUSVALID 				(0x1 << 7)
#define TCA_POWERPRESENT 			(0x1 << 6)
#define TCA_IDDIG 				(0x1 << 5)
#define TCA_DRV_HOST_VBUS 			(0x1 << 4)
#define TCA_USB_DEV_POR 			(0x1 << 3)
#define TYPEC_FLIP_INVERT 			(0x1 << 2)

#define PHY_POWER_DOWN 				(0x170)
#define RX2_DISABLE_PD 				(0x1 << 29)
#define RX1_DISABLE_PD 				(0x1 << 28)
#define TX3_DISABLE_PD 				(0x1 << 27)
#define TX2_DISABLE_PD 				(0x1 << 26)
#define TX1_DISABLE_PD 				(0x1 << 25)
#define TX0_DISABLE_PD 				(0x1 << 24)
#define RX2_RESET_PD 				(0x1 << 21)
#define RX1_RESET_PD 				(0x1 << 20)
#define TX3_RESET_PD 				(0x1 << 19)
#define TX2_RESET_PD 				(0x1 << 18)
#define TX1_RESET_PD 				(0x1 << 17)
#define TX0_RESET_PD 				(0x1 << 16)
#define RX2_PSTATE_PD 				(0x3 << 14)
#define RX1_PSTATE_PD 				(0x3 << 12)
#define TX3_PSTATE_PD 				(0x3 << 10)
#define TX2_PSTATE_PD 				(0x3 << 8)
#define TX1_PSTATE_PD 				(0x3 << 6)
#define TX0_PSTATE_PD 				(0x3 << 4)
#define REF_CLK_EN_PD 				(0x1 << 1)
#define POWER_DOWN_MODE_EN 			(0x1 << 0)

#define TCA_STATE_CTRL 				(0x174)
#define PIPE_LANE0_PHYSTATUS 			(0x1 << 17)
#define SS_RXDET_DISABLE 			(0x1 << 16)
#define PIPE_LANE0_POWERDOWN_OVRD_EN 		(0x1 << 8)
#define PIPE_LANE0_POWERDOWN 			(0xF << 4)
#define SS_RXDET_DISABLE_ACK_OVRD_EN 		(0x1 << 1)
#define SS_RXDET_DISABLE_ACK 			(0x1 << 0)

#define PHY_LANE1_CTRL 				(0x178)
#define SS_RXDET_DISABLE_ACK_1 			(0x1 << 17)
#define SS_RXDET_DISABLE_1 			(0x1 << 16)
#define PIPE_TX1_ELECIDLE 			(0x1 << 14)
#define PIPE_LANE1_RATE 			(0x3 << 12)
#define PIPE_LANE1_POWERDOWN 			(0xF << 8)
#define PIPE_LANE1_LINK_NUM 			(0xF << 4)
#define PHY_SS_TX1_VREGDRV_BYP 			(0x1 << 3)
#define PHY_SS_TX1_BYPASS_EQ_CALC 		(0x1 << 2)
#define PHY_SS_RX1_TERM_ACDC 			(0x1 << 1)
#define PHY_LANE1_POWER_PRESENT 		(0x1 << 0)

#define DP_AUX_CONFIG0 				(0x200)
#define AUX_CTRL 				(0xF << 12)
#define AUX_PWDNB 				(0x1 << 9)
#define AUX_VOD_TUNE 				(0x1 << 8)
#define AUX_HYS_TUNE 				(0x3 << 4)
#define AUX_DP_DN_SWAP 				(0x1 << 0)

#define DP_CONFIG0 				(0x204)
#define DP_LANE3_TX2RX_SER_LB_EN 		(0x1 << 7)
#define DP_LANE2_TX2RX_SER_LB_EN 		(0x1 << 6)
#define DP_LANE1_TX2RX_SER_LB_EN 		(0x1 << 5)
#define DP_LANE0_TX2RX_SER_LB_EN 		(0x1 << 4)
#define DP_LANE3_RX2TX_PAR_LB_EN 		(0x1 << 3)
#define DP_LANE2_RX2TX_PAR_LB_EN 		(0x1 << 2)
#define DP_LANE1_RX2TX_PAR_LB_EN 		(0x1 << 1)
#define DP_LANE0_RX2TX_PAR_LB_EN 		(0x1 << 0)

#define DP_CONFIG1 				(0x208)
#define DP_MPLLB_CP_PROP_GS 			(0x7F << 24)
#define DP_MPLLB_CP_PROP 			(0x7F << 16)
#define DP_MPLLB_CP_INT_GS 			(0x7F << 8)
#define DP_MPLLB_CP_INT 			(0x7F << 0)

#define DP_CONFIG2 				(0x20C)
#define DP_MPLLB_FRACN_DEN 			(0xFFFF << 16)
#define DP_MPLLB_FRACN_EN 			(0x1 << 15)
#define DP_MPLLB_FRACN_CFG_UPDATE_EN 		(0x1 << 14)
#define DP_MPLLB_FORCE_ACK 			(0x1 << 13)
#define DP_MPLLB_FORCE_EN 			(0x1 << 12)
#define DP_MPLLB_DIV_MULTIPLIER 		(0xFF << 4)
#define DP_MPLLB_DIV_CLK_EN 			(0x1 << 1)
#define DP_MPLLB_DIV5_CLK_EN 			(0x1 << 0)

#define DP_CONFIG3 				(0x210)
#define DP_MPLLB_FRACN_REM 			(0xFFFF << 16)
#define DP_MPLLB_FRACN_QUOT 			(0xFFFF << 0)

#define DP_CONFIG4 				(0x214)
#define DP_MPLLB_SSC_EN 			(0x1 << 17)
#define DP_MPLLB_PMIX_EN 			(0x1 << 16)
#define DP_MPLLB_MULTIPLIER 			(0xFFF << 4)
#define DP_MPLLB_INIT_CAL_DISABLE 		(0x1 << 2)
#define DP_MPLLB_FREQ_VCO 			(0x3 << 0)

#define DP_CONFIG5 				(0x218)
#define DP_MPLLB_SSC_PEAK 			(0xFFFFF << 0)

#define DP_CONFIG6 				(0x21C)
#define DP_MPLLB_SSC_STEPSIZE 			(0x1FFFFF << 0)

#define DP_CONFIG7 				(0x220)
#define DP_REF_CLK_REQ 				(0x1 << 12)
#define DP_REF_CLK_MPLLB_DIV 			(0x7 << 9)
#define DP_REF_CLK_EN 				(0x1 << 8)
#define DP_PG_RESET 				(0x1 << 7)
#define DP_MPLLB_WORD_DIV2_EN 			(0x1 << 6)
#define DP_MPLLB_V2I 				(0x3 << 4)
#define DP_MPLLB_TX_CLK_DIV 			(0x7 << 1)
#define DP_MPLLB_SSC_UP_SPREAD 			(0x1 << 0)

#define DP_CONFIG8 				(0x224)
#define DP_TX3_EQ_MAIN 				(0x3F << 24)
#define DP_TX2_EQ_MAIN 				(0x3F << 16)
#define DP_TX1_EQ_MAIN 				(0x3F << 8)
#define DP_TX0_EQ_MAIN 				(0x3F << 0)

#define DP_CONFIG9 				(0x228)
#define DP_TX3_EQ_POST 				(0x3F << 24)
#define DP_TX2_EQ_POST 				(0x3F << 16)
#define DP_TX1_EQ_POST 				(0x3F << 8)
#define DP_TX0_EQ_POST 				(0x3F << 0)

#define DP_CONFIG10 				(0x22C)
#define DP_TX3_EQ_PRE 				(0x3F << 24)
#define DP_TX2_EQ_PRE 				(0x3F << 16)
#define DP_TX1_EQ_PRE 				(0x3F << 8)
#define DP_TX0_EQ_PRE 				(0x3F << 0)

#define DP_CONFIG11 				(0x230)
#define DP_TX3_RATE 				(0x7 << 28)
#define DP_TX2_RATE 				(0x7 << 24)
#define DP_TX1_RATE 				(0x7 << 20)
#define DP_TX0_RATE 				(0x7 << 16)
#define DP_TX3_LPD 				(0x1 << 15)
#define DP_TX2_LPD 				(0x1 << 14)
#define DP_TX1_LPD 				(0x1 << 13)
#define DP_TX0_LPD 				(0x1 << 12)
#define DP_TX3_PSTATE 				(0x3 << 10)
#define DP_TX2_PSTATE 				(0x3 << 8)
#define DP_TX1_PSTATE 				(0x3 << 6)
#define DP_TX0_PSTATE 				(0x3 << 4)
#define DP_TX3_BYPASS_EQ_CALC 			(0x1 << 3)
#define DP_TX2_BYPASS_EQ_CALC 			(0x1 << 2)
#define DP_TX1_BYPASS_EQ_CALC 			(0x1 << 1)
#define DP_TX0_BYPASS_EQ_CALC 			(0x1 << 0)

#define DP_CONFIG12 				(0x234)
#define DP_TX3_ACK 				(0x1 << 19)
#define DP_TX2_ACK 				(0x1 << 18)
#define DP_TX1_ACK 				(0x1 << 17)
#define DP_TX0_ACK 				(0x1 << 16)
#define DP_TX3_REQ_STATUS 			(0x1 << 15)
#define DP_TX2_REQ_STATUS 			(0x1 << 14)
#define DP_TX1_REQ_STATUS 			(0x1 << 13)
#define DP_TX0_REQ_STATUS 			(0x1 << 12)
#define DP_TX3_MPLL_EN 				(0x1 << 11)
#define DP_TX2_MPLL_EN 				(0x1 << 10)
#define DP_TX1_MPLL_EN 				(0x1 << 9)
#define DP_TX0_MPLL_EN 				(0x1 << 8)
#define DP_TX3_WIDTH 				(0x3 << 6)
#define DP_TX2_WIDTH 				(0x3 << 4)
#define DP_TX1_WIDTH 				(0x3 << 2)
#define DP_TX0_WIDTH 				(0x3 << 0)

#define DP_CONFIG13 				(0x238)
#define DP_TX3_HP_PROT_EN 			(0x1 << 27)
#define DP_TX2_HP_PROT_EN 			(0x1 << 26)
#define DP_TX1_HP_PROT_EN 			(0x1 << 25)
#define DP_TX0_HP_PROT_EN 			(0x1 << 24)
#define DP_TX3_FLYOVER_DATA_P 			(0x1 << 23)
#define DP_TX2_FLYOVER_DATA_P 			(0x1 << 22)
#define DP_TX1_FLYOVER_DATA_P 			(0x1 << 21)
#define DP_TX0_FLYOVER_DATA_P 			(0x1 << 20)
#define DP_TX3_FLYOVER_DATA_M 			(0x1 << 19)
#define DP_TX2_FLYOVER_DATA_M 			(0x1 << 18)
#define DP_TX1_FLYOVER_DATA_M 			(0x1 << 17)
#define DP_TX0_FLYOVER_DATA_M 			(0x1 << 16)
#define DP_TX3_DETRX_RESULT 			(0x1 << 15)
#define DP_TX2_DETRX_RESULT 			(0x1 << 14)
#define DP_TX1_DETRX_RESULT 			(0x1 << 13)
#define DP_TX0_DETRX_RESULT 			(0x1 << 12)
#define DP_TX3_DETRX_REQ_STATUS 		(0x1 << 11)
#define DP_TX2_DETRX_REQ_STATUS 		(0x1 << 10)
#define DP_TX1_DETRX_REQ_STATUS 		(0x1 << 9)
#define DP_TX0_DETRX_REQ_STATUS 		(0x1 << 8)
#define DP_TX3_RESET 				(0x1 << 7)
#define DP_TX2_RESET 				(0x1 << 6)
#define DP_TX1_RESET 				(0x1 << 5)
#define DP_TX0_RESET 				(0x1 << 4)
#define DP_TX3_DISABLE 				(0x1 << 3)
#define DP_TX2_DISABLE 				(0x1 << 2)
#define DP_TX1_DISABLE 				(0x1 << 1)
#define DP_TX0_DISABLE 				(0x1 << 0)

#define DP_CONFIG14 				(0x23C)
#define DP_TX3_IN_GENERIC_BUS 			(0x1F << 24)
#define DP_TX2_IN_GENERIC_BUS 			(0x1F << 16)
#define DP_TX1_IN_GENERIC_BUS 			(0x1F << 8)
#define DP_TX0_IN_GENERIC_BUS 			(0x1F << 0)

#define DP_CONFIG15 				(0x240)
#define DP_TX3_OUT_GENERIC_BUS 			(0x1F << 24)
#define DP_TX2_OUT_GENERIC_BUS 			(0x1F << 16)
#define DP_TX1_OUT_GENERIC_BUS 			(0x1F << 8)
#define DP_TX0_OUT_GENERIC_BUS 			(0x1F << 0)

#define DP_CONFIG16 				(0x244)
#define DP_TX3_DATA_EN 				(0x1 << 31)
#define DP_TX2_DATA_EN 				(0x1 << 30)
#define DP_TX1_DATA_EN 				(0x1 << 29)
#define DP_TX0_DATA_EN 				(0x1 << 28)
#define DP_TX3_CLK_RDY 				(0x1 << 27)
#define DP_TX2_CLK_RDY 				(0x1 << 26)
#define DP_TX1_CLK_RDY 				(0x1 << 25)
#define DP_TX0_CLK_RDY 				(0x1 << 24)
#define DP_TX3_VREGDRV_BYP 			(0x1 << 23)
#define DP_TX2_VREGDRV_BYP 			(0x1 << 22)
#define DP_TX1_VREGDRV_BYP 			(0x1 << 21)
#define DP_TX0_VREGDRV_BYP 			(0x1 << 20)
#define DP_TX3_TERM_CTRL 			(0x7 << 16)
#define DP_TX2_TERM_CTRL 			(0x7 << 12)
#define DP_TX1_TERM_CTRL 			(0x7 << 8)
#define DP_TX0_TERM_CTRL 			(0x7 << 4)
#define DP_TX3_INVERT 				(0x1 << 3)
#define DP_TX2_INVERT 				(0x1 << 2)
#define DP_TX1_INVERT 				(0x1 << 1)
#define DP_TX0_INVERT 				(0x1 << 0)

#define DP_CONFIG17 				(0x248)
#define DP_TX3_RBOOST_EN 			(0x3 << 14)
#define DP_TX2_RBOOST_EN 			(0x3 << 12)
#define DP_TX1_RBOOST_EN 			(0x3 << 10)
#define DP_TX0_RBOOST_EN 			(0x3 << 8)
#define DP_TX3_IBOOST_EN 			(0x1 << 7)
#define DP_TX2_IBOOST_EN 			(0x1 << 6)
#define DP_TX1_IBOOST_EN 			(0x1 << 5)
#define DP_TX0_IBOOST_EN 			(0x1 << 4)
#define DP_TX3_DCC_BYP_AC_CAP 			(0x1 << 3)
#define DP_TX2_DCC_BYP_AC_CAP 			(0x1 << 2)
#define DP_TX1_DCC_BYP_AC_CAP 			(0x1 << 1)
#define DP_TX0_DCC_BYP_AC_CAP 			(0x1 << 0)

#define DP_CONFIG18 				(0x24C)
#define DP_MPLLB_QWORD_CLK 			(0x1 << 2)
#define DP_MPLLB_OWORD_CLK 			(0x1 << 1)
#define DP_MPLLB_DIV_CLK 			(0x1 << 0)

#define DP_CONFIG19 				(0x250)
#define TCA_DP4_POR 				(0x1 << 3)
#define DPALT_DP4 				(0x1 << 2)
#define DPALT_DISABLE_ACK 			(0x1 << 1)
#define DPALT_DISABLE 				(0x1 << 0)


#endif  /* _USBDPPHY_CTRL_REGS_H_ */