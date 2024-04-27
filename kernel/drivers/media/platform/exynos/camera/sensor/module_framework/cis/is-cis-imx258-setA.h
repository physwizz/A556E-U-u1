/*
 * Samsung Exynos5 SoC series Sensor driver
 *
 *
 * Copyright (c) 2023 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/* IMX258ES1(0ATH5)_SEC_19.2M_RegisterSetting_ver4.00-0.23_230710.xlsx */

#ifndef IS_CIS_IMX258_SET_A_H
#define IS_CIS_IMX258_SET_A_H

#include "is-cis.h"
#include "is-cis-imx258.h"
#ifdef USE_CAMERA_ADAPTIVE_MIPI
#include "is-cis-imx258-setA-adaptive-mipi.h"
#endif

const u16 sensor_imx258_setfile_A_global[] = {
	/* External Clock Setting */
	0x0136, 0x13, 0x01,
	0x0137, 0x33, 0x01,

	/* Global Setting */
	0x3051, 0x00, 0x01,
	0x3052, 0x00, 0x01,
	0x4E21, 0x14, 0x01,
	0x6B11, 0xCF, 0x01,
	0x7FF0, 0x08, 0x01,
	0x7FF1, 0x0F, 0x01,
	0x7FF2, 0x08, 0x01,
	0x7FF3, 0x1B, 0x01,
	0x7FF4, 0x23, 0x01,
	0x7FF5, 0x60, 0x01,
	0x7FF6, 0x00, 0x01,
	0x7FF7, 0x01, 0x01,
	0x7FF8, 0x00, 0x01,
	0x7FF9, 0x78, 0x01,
	0x7FFA, 0x00, 0x01,
	0x7FFB, 0x00, 0x01,
	0x7FFC, 0x00, 0x01,
	0x7FFD, 0x00, 0x01,
	0x7FFE, 0x00, 0x01,
	0x7FFF, 0x03, 0x01,
	0x7F76, 0x03, 0x01,
	0x7F77, 0xFE, 0x01,
	0x7FA8, 0x03, 0x01,
	0x7FA9, 0xFE, 0x01,
	0x7B24, 0x81, 0x01,
	0x7B25, 0x00, 0x01,
	0x6564, 0x07, 0x01,
	0x6B0D, 0x41, 0x01,
	0x653D, 0x04, 0x01,
	0x6B05, 0x8C, 0x01,
	0x6B06, 0xF9, 0x01,
	0x6B08, 0x65, 0x01,
	0x6B09, 0xFC, 0x01,
	0x6B0A, 0xCF, 0x01,
	0x6B0B, 0xD2, 0x01,
	0x6700, 0x0E, 0x01,
	0x6707, 0x0E, 0x01,
	0x5F04, 0x00, 0x01,
	0x5F05, 0xED, 0x01,
	0x7937, 0x01, 0x01,
	0x793C, 0x01, 0x01,
	0x792F, 0x01, 0x01,
	0x7930, 0x01, 0x01,

	/* Image Quality*/
	0x94C7, 0xFF, 0x01,
	0x94C8, 0xFF, 0x01,
	0x94C9, 0xFF, 0x01,
	0x95C7, 0xFF, 0x01,
	0x95C8, 0xFF, 0x01,
	0x95C9, 0xFF, 0x01,
	0x94C4, 0x3F, 0x01,
	0x94C5, 0x3F, 0x01,
	0x94C6, 0x3F, 0x01,
	0x95C4, 0x3F, 0x01,
	0x95C5, 0x3F, 0x01,
	0x95C6, 0x3F, 0x01,
	0x94C1, 0x02, 0x01,
	0x94C2, 0x02, 0x01,
	0x94C3, 0x02, 0x01,
	0x95C1, 0x02, 0x01,
	0x95C2, 0x02, 0x01,
	0x95C3, 0x02, 0x01,
	0x94BE, 0x0C, 0x01,
	0x94BF, 0x0C, 0x01,
	0x94C0, 0x0C, 0x01,
	0x95BE, 0x0C, 0x01,
	0x95BF, 0x0C, 0x01,
	0x95C0, 0x0C, 0x01,
	0x94D0, 0x74, 0x01,
	0x94D1, 0x74, 0x01,
	0x94D2, 0x74, 0x01,
	0x95D0, 0x74, 0x01,
	0x95D1, 0x74, 0x01,
	0x95D2, 0x74, 0x01,
	0x94CD, 0x2E, 0x01,
	0x94CE, 0x2E, 0x01,
	0x94CF, 0x2E, 0x01,
	0x95CD, 0x2E, 0x01,
	0x95CE, 0x2E, 0x01,
	0x95CF, 0x2E, 0x01,
	0x94CA, 0x4C, 0x01,
	0x94CB, 0x4C, 0x01,
	0x94CC, 0x4C, 0x01,
	0x95CA, 0x4C, 0x01,
	0x95CB, 0x4C, 0x01,
	0x95CC, 0x4C, 0x01,
	0x900E, 0x32, 0x01,
	0x94E2, 0xFF, 0x01,
	0x94E3, 0xFF, 0x01,
	0x94E4, 0xFF, 0x01,
	0x95E2, 0xFF, 0x01,
	0x95E3, 0xFF, 0x01,
	0x95E4, 0xFF, 0x01,
	0x94DF, 0x6E, 0x01,
	0x94E0, 0x6E, 0x01,
	0x94E1, 0x6E, 0x01,
	0x95DF, 0x6E, 0x01,
	0x95E0, 0x6E, 0x01,
	0x95E1, 0x6E, 0x01,
	0x7FCC, 0x01, 0x01,
	0x7B78, 0x00, 0x01,
	0x9401, 0x35, 0x01,
	0x9403, 0x23, 0x01,
	0x9405, 0x23, 0x01,
	0x9406, 0x00, 0x01,
	0x9407, 0x31, 0x01,
	0x9408, 0x00, 0x01,
	0x9409, 0x1B, 0x01,
	0x940A, 0x00, 0x01,
	0x940B, 0x15, 0x01,
	0x940D, 0x3F, 0x01,
	0x940F, 0x3F, 0x01,
	0x9411, 0x3F, 0x01,
	0x9413, 0x64, 0x01,
	0x9415, 0x64, 0x01,
	0x9417, 0x64, 0x01,
	0x941D, 0x34, 0x01,
	0x941F, 0x01, 0x01,
	0x9421, 0x01, 0x01,
	0x9423, 0x01, 0x01,
	0x9425, 0x23, 0x01,
	0x9427, 0x23, 0x01,
	0x9429, 0x23, 0x01,
	0x942B, 0x2F, 0x01,
	0x942D, 0x1A, 0x01,
	0x942F, 0x14, 0x01,
	0x9431, 0x3F, 0x01,
	0x9433, 0x3F, 0x01,
	0x9435, 0x3F, 0x01,
	0x9437, 0x6B, 0x01,
	0x9439, 0x7C, 0x01,
	0x943B, 0x81, 0x01,
	0x9443, 0x0F, 0x01,
	0x9445, 0x0F, 0x01,
	0x9447, 0x0F, 0x01,
	0x9449, 0x0F, 0x01,
	0x944B, 0x0F, 0x01,
	0x944D, 0x0F, 0x01,
	0x944F, 0x1E, 0x01,
	0x9451, 0x0F, 0x01,
	0x9453, 0x0B, 0x01,
	0x9455, 0x28, 0x01,
	0x9457, 0x13, 0x01,
	0x9459, 0x0C, 0x01,
	0x945D, 0x00, 0x01,
	0x945E, 0x00, 0x01,
	0x945F, 0x00, 0x01,
	0x946D, 0x00, 0x01,
	0x946F, 0x10, 0x01,
	0x9471, 0x10, 0x01,
	0x9473, 0x40, 0x01,
	0x9475, 0x2E, 0x01,
	0x9477, 0x10, 0x01,
	0x9478, 0x0A, 0x01,
	0x947B, 0xE0, 0x01,
	0x947C, 0xE0, 0x01,
	0x947D, 0xE0, 0x01,
	0x947E, 0xE0, 0x01,
	0x947F, 0xE0, 0x01,
	0x9480, 0xE0, 0x01,
	0x9483, 0x14, 0x01,
	0x9485, 0x14, 0x01,
	0x9487, 0x14, 0x01,
	0x9501, 0x35, 0x01,
	0x9503, 0x14, 0x01,
	0x9505, 0x14, 0x01,
	0x9507, 0x31, 0x01,
	0x9509, 0x1B, 0x01,
	0x950B, 0x15, 0x01,
	0x950D, 0x1E, 0x01,
	0x950F, 0x1E, 0x01,
	0x9511, 0x1E, 0x01,
	0x9513, 0x64, 0x01,
	0x9515, 0x64, 0x01,
	0x9517, 0x64, 0x01,
	0x951D, 0x34, 0x01,
	0x951F, 0x01, 0x01,
	0x9521, 0x01, 0x01,
	0x9523, 0x01, 0x01,
	0x9525, 0x14, 0x01,
	0x9527, 0x14, 0x01,
	0x9529, 0x14, 0x01,
	0x952B, 0x2F, 0x01,
	0x952D, 0x1A, 0x01,
	0x952F, 0x14, 0x01,
	0x9531, 0x1E, 0x01,
	0x9533, 0x1E, 0x01,
	0x9535, 0x1E, 0x01,
	0x9537, 0x6B, 0x01,
	0x9539, 0x7C, 0x01,
	0x953B, 0x81, 0x01,
	0x9543, 0x0F, 0x01,
	0x9545, 0x0F, 0x01,
	0x9547, 0x0F, 0x01,
	0x9549, 0x0F, 0x01,
	0x954B, 0x0F, 0x01,
	0x954D, 0x0F, 0x01,
	0x954F, 0x15, 0x01,
	0x9551, 0x0B, 0x01,
	0x9553, 0x08, 0x01,
	0x9555, 0x1C, 0x01,
	0x9557, 0x0D, 0x01,
	0x9559, 0x08, 0x01,
	0x955D, 0x00, 0x01,
	0x955E, 0x00, 0x01,
	0x955F, 0x00, 0x01,
	0x956D, 0x00, 0x01,
	0x956F, 0x10, 0x01,
	0x9571, 0x10, 0x01,
	0x9573, 0x40, 0x01,
	0x9575, 0x2E, 0x01,
	0x9577, 0x10, 0x01,
	0x9578, 0x0A, 0x01,
	0x957B, 0xE0, 0x01,
	0x957C, 0xE0, 0x01,
	0x957D, 0xE0, 0x01,
	0x957E, 0xE0, 0x01,
	0x957F, 0xE0, 0x01,
	0x9580, 0xE0, 0x01,
	0x9583, 0x14, 0x01,
	0x9585, 0x14, 0x01,
	0x9587, 0x14, 0x01,
	0x7F78, 0x00, 0x01,
	0x7F89, 0x00, 0x01,
	0x7F93, 0x00, 0x01,
	0x924B, 0x1B, 0x01,
	0x924C, 0x0A, 0x01,
	0x9304, 0x04, 0x01,
	0x9315, 0x04, 0x01,
	0x9250, 0x50, 0x01,
	0x9251, 0x3C, 0x01,
	0x9252, 0x14, 0x01,
};

/* A-1 */
const u16 sensor_imx258_setfile_A_4000x3000_30fps[] = {
	/* Output format Setting */
	0x0112, 0x0A, 0x01,
	0x0113, 0x0A, 0x01,
	0x0114, 0x03, 0x01,
	/* Clock Setting */
	0x0301, 0x05, 0x01,
	0x0303, 0x02, 0x01,
	0x0305, 0x03, 0x01,
	0x0306, 0x00, 0x01,
	0x0307, 0xC4, 0x01,
	0x0309, 0x0A, 0x01,
	0x030B, 0x01, 0x01,
	0x030D, 0x03, 0x01,
	0x030E, 0x00, 0x01,
	0x030F, 0x9E, 0x01,
	0x0310, 0x01, 0x01,
	0x0808, 0x00, 0x01,
	/* Clock Adjustment Setting */
	0x4648, 0x7F, 0x01,
	0x7420, 0x00, 0x01,
	0x7421, 0x5C, 0x01,
	0x7422, 0x00, 0x01,
	0x7423, 0xD7, 0x01,
	0x9104, 0x04, 0x01,
	/* Line Length Setting */
	0x0342, 0x14, 0x01,
	0x0343, 0xE8, 0x01,
	/* Frame Length Setting */
	0x0340, 0x0C, 0x01,
	0x0341, 0x34, 0x01,
	/* ROI Setting */
	0x0344, 0x00, 0x01,
	0x0345, 0x00, 0x01,
	0x0346, 0x00, 0x01,
	0x0347, 0x3C, 0x01,
	0x0348, 0x10, 0x01,
	0x0349, 0x6F, 0x01,
	0x034A, 0x0B, 0x01,
	0x034B, 0xF3, 0x01,
	/* Analog Image Size Setting */
	0x0381, 0x01, 0x01,
	0x0383, 0x01, 0x01,
	0x0385, 0x01, 0x01,
	0x0387, 0x01, 0x01,
	0x0900, 0x00, 0x01,
	0x0901, 0x11, 0x01,
	/* Digital Image Size Setting */
	0x0401, 0x00, 0x01,
	0x0404, 0x00, 0x01,
	0x0405, 0x10, 0x01,
	0x0408, 0x00, 0x01,
	0x0409, 0x68, 0x01,
	0x040A, 0x00, 0x01,
	0x040B, 0x00, 0x01,
	0x040C, 0x0F, 0x01,
	0x040D, 0xA0, 0x01,
	0x040E, 0x0B, 0x01,
	0x040F, 0xB8, 0x01,
	0x3038, 0x00, 0x01,
	0x303A, 0x00, 0x01,
	0x303B, 0x10, 0x01,
	0x300D, 0x00, 0x01,
	/* Output Size Setting */
	0x034C, 0x0F, 0x01,
	0x034D, 0xA0, 0x01,
	0x034E, 0x0B, 0x01,
	0x034F, 0xB8, 0x01,
	/* Integration Time Setting */
	0x0202, 0x0C, 0x01,
	0x0203, 0x2A, 0x01,
	/* Gain Setting */
	0x0204, 0x00, 0x01,
	0x0205, 0x00, 0x01,
	0x020E, 0x01, 0x01,
	0x020F, 0x00, 0x01,
	0x0210, 0x01, 0x01,
	0x0211, 0x00, 0x01,
	0x0212, 0x01, 0x01,
	0x0213, 0x00, 0x01,
	0x0214, 0x01, 0x01,
	0x0215, 0x00, 0x01,
	/* Added Setting(AF) */
	0x7BCD, 0x00, 0x01,
	/* Added Setting(IQ) */
	0x94DC, 0x20, 0x01,
	0x94DD, 0x20, 0x01,
	0x94DE, 0x20, 0x01,
	0x95DC, 0x20, 0x01,
	0x95DD, 0x20, 0x01,
	0x95DE, 0x20, 0x01,
	0x7FB0, 0x00, 0x01,
	0x9010, 0x3E, 0x01,
	0x9419, 0x50, 0x01,
	0x941B, 0x50, 0x01,
	0x9519, 0x50, 0x01,
	0x951B, 0x50, 0x01,
	/* Added Setting(mode) */
	0x3030, 0x00, 0x01,
	0x3032, 0x00, 0x01,
	0x0220, 0x00, 0x01,
	0x0B06, 0x00, 0x01,
};

/* B-1 */
const u16 sensor_imx258_setfile_A_4000x2256_30fps[] = {
	/* Output format Setting */
	0x0112, 0x0A, 0x01,
	0x0113, 0x0A, 0x01,
	0x0114, 0x03, 0x01,
	/* Clock Setting */
	0x0301, 0x05, 0x01,
	0x0303, 0x02, 0x01,
	0x0305, 0x03, 0x01,
	0x0306, 0x00, 0x01,
	0x0307, 0xC4, 0x01,
	0x0309, 0x0A, 0x01,
	0x030B, 0x01, 0x01,
	0x030D, 0x03, 0x01,
	0x030E, 0x00, 0x01,
	0x030F, 0x9E, 0x01,
	0x0310, 0x01, 0x01,
	0x0808, 0x00, 0x01,
	/* Clock Adjustment Setting */
	0x4648, 0x7F, 0x01,
	0x7420, 0x00, 0x01,
	0x7421, 0x5C, 0x01,
	0x7422, 0x00, 0x01,
	0x7423, 0xD7, 0x01,
	0x9104, 0x04, 0x01,
	/* Line Length Setting */
	0x0342, 0x14, 0x01,
	0x0343, 0xE8, 0x01,
	/* Frame Length Setting */
	0x0340, 0x0C, 0x01,
	0x0341, 0x34, 0x01,
	/* ROI Setting */
	0x0344, 0x00, 0x01,
	0x0345, 0x00, 0x01,
	0x0346, 0x01, 0x01,
	0x0347, 0xB0, 0x01,
	0x0348, 0x10, 0x01,
	0x0349, 0x6F, 0x01,
	0x034A, 0x0A, 0x01,
	0x034B, 0x7F, 0x01,
	/* Analog Image Size Setting */
	0x0381, 0x01, 0x01,
	0x0383, 0x01, 0x01,
	0x0385, 0x01, 0x01,
	0x0387, 0x01, 0x01,
	0x0900, 0x00, 0x01,
	0x0901, 0x11, 0x01,
	/* Digital Image Size Setting */
	0x0401, 0x00, 0x01,
	0x0404, 0x00, 0x01,
	0x0405, 0x10, 0x01,
	0x0408, 0x00, 0x01,
	0x0409, 0x68, 0x01,
	0x040A, 0x00, 0x01,
	0x040B, 0x00, 0x01,
	0x040C, 0x0F, 0x01,
	0x040D, 0xA0, 0x01,
	0x040E, 0x08, 0x01,
	0x040F, 0xD0, 0x01,
	0x3038, 0x00, 0x01,
	0x303A, 0x00, 0x01,
	0x303B, 0x10, 0x01,
	0x300D, 0x00, 0x01,
	/*Output Size Setting */
	0x034C, 0x0F, 0x01,
	0x034D, 0xA0, 0x01,
	0x034E, 0x08, 0x01,
	0x034F, 0xD0, 0x01,
	/* Integration Time Setting */
	0x0202, 0x0C, 0x01,
	0x0203, 0x2A, 0x01,
	/*Gain Setting */
	0x0204, 0x00, 0x01,
	0x0205, 0x00, 0x01,
	0x020E, 0x01, 0x01,
	0x020F, 0x00, 0x01,
	0x0210, 0x01, 0x01,
	0x0211, 0x00, 0x01,
	0x0212, 0x01, 0x01,
	0x0213, 0x00, 0x01,
	0x0214, 0x01, 0x01,
	0x0215, 0x00, 0x01,
	/* Added Setting(AF) */
	0x7BCD, 0x00, 0x01,
	/* Added Setting(IQ) */
	0x94DC, 0x20, 0x01,
	0x94DD, 0x20, 0x01,
	0x94DE, 0x20, 0x01,
	0x95DC, 0x20, 0x01,
	0x95DD, 0x20, 0x01,
	0x95DE, 0x20, 0x01,
	0x7FB0, 0x00, 0x01,
	0x9010, 0x3E, 0x01,
	0x9419, 0x50, 0x01,
	0x941B, 0x50, 0x01,
	0x9519, 0x50, 0x01,
	0x951B, 0x50, 0x01,
	/* Added Setting(mode) */
	0x3030, 0x00, 0x01,
	0x3032, 0x00, 0x01,
	0x0220, 0x00, 0x01,
	0x0B06, 0x00, 0x01,
};

/* M-1 */
const u16 sensor_imx258_setfile_A_1000x750_120fps[] = {
	/* Output format Setting */
	0x0112, 0x0A, 0x01,
	0x0113, 0x0A, 0x01,
	0x0114, 0x03, 0x01,
	/* Clock Setting */
	0x0301, 0x05, 0x01,
	0x0303, 0x02, 0x01,
	0x0305, 0x03, 0x01,
	0x0306, 0x00, 0x01,
	0x0307, 0xCB, 0x01,
	0x0309, 0x0A, 0x01,
	0x030B, 0x01, 0x01,
	0x030D, 0x03, 0x01,
	0x030E, 0x00, 0x01,
	0x030F, 0x9E, 0x01,
	0x0310, 0x01, 0x01,
	0x0808, 0x00, 0x01,
	/* Clock Adjustment Setting */
	0x4648, 0x7F, 0x01,
	0x7420, 0x00, 0x01,
	0x7421, 0x5C, 0x01,
	0x7422, 0x00, 0x01,
	0x7423, 0xD7, 0x01,
	0x9104, 0x04, 0x01,
	/* Line Length Setting */
	0x0342, 0x14, 0x01,
	0x0343, 0xE8, 0x01,
	/* Frame Length Setting */
	0x0340, 0x03, 0x01,
	0x0341, 0x28, 0x01,
	/* ROI Setting */
	0x0344, 0x00, 0x01,
	0x0345, 0x00, 0x01,
	0x0346, 0x00, 0x01,
	0x0347, 0x38, 0x01,
	0x0348, 0x10, 0x01,
	0x0349, 0x6F, 0x01,
	0x034A, 0x0B, 0x01,
	0x034B, 0xEF, 0x01,
	/* Analog Image Size Setting */
	0x0381, 0x01, 0x01,
	0x0383, 0x01, 0x01,
	0x0385, 0x01, 0x01,
	0x0387, 0x01, 0x01,
	0x0900, 0x01, 0x01,
	0x0901, 0x14, 0x01,
	/* Digital Image Size Setting */
	0x0401, 0x01, 0x01,
	0x0404, 0x00, 0x01,
	0x0405, 0x40, 0x01,
	0x0408, 0x00, 0x01,
	0x0409, 0x66, 0x01,
	0x040A, 0x00, 0x01,
	0x040B, 0x00, 0x01,
	0x040C, 0x0F, 0x01,
	0x040D, 0xA4, 0x01,
	0x040E, 0x02, 0x01,
	0x040F, 0xEE, 0x01,
	0x3038, 0x00, 0x01,
	0x303A, 0x00, 0x01,
	0x303B, 0x10, 0x01,
	0x300D, 0x00, 0x01,
	/* Output Size Setting */
	0x034C, 0x03, 0x01,
	0x034D, 0xE8, 0x01,
	0x034E, 0x02, 0x01,
	0x034F, 0xEE, 0x01,
	/* Integration Time Setting */
	0x0202, 0x03, 0x01,
	0x0203, 0x1E, 0x01,
	/* Gain Setting */
	0x0204, 0x00, 0x01,
	0x0205, 0x00, 0x01,
	0x020E, 0x01, 0x01,
	0x020F, 0x00, 0x01,
	0x0210, 0x01, 0x01,
	0x0211, 0x00, 0x01,
	0x0212, 0x01, 0x01,
	0x0213, 0x00, 0x01,
	0x0214, 0x01, 0x01,
	0x0215, 0x00, 0x01,
	/* Added Setting(AF) */
	0x7BCD, 0x00, 0x01,
	/* Added Setting(IQ) */
	0x94DC, 0x20, 0x01,
	0x94DD, 0x20, 0x01,
	0x94DE, 0x20, 0x01,
	0x95DC, 0x20, 0x01,
	0x95DD, 0x20, 0x01,
	0x95DE, 0x20, 0x01,
	0x7FB0, 0x00, 0x01,
	0x9010, 0x3E, 0x01,
	0x9419, 0x50, 0x01,
	0x941B, 0x50, 0x01,
	0x9519, 0x50, 0x01,
	0x951B, 0x50, 0x01,
	/* Added Setting(mode) */
	0x3030, 0x00, 0x01,
	0x3032, 0x00, 0x01,
	0x0220, 0x00, 0x01,
	0x0B06, 0x00, 0x01,
};

/* J-5 */
const u16 sensor_imx258_setfile_A_2000x1500_30fps[] = {
	0x0112, 0x0A, 0x01,
	0x0113, 0x0A, 0x01,
	0x0114, 0x03, 0x01,
	0x0301, 0x05, 0x01,
	0x0303, 0x02, 0x01,
	0x0305, 0x03, 0x01,
	0x0306, 0x00, 0x01,
	0x0307, 0xCB, 0x01,
	0x0309, 0x0A, 0x01,
	0x030B, 0x01, 0x01,
	0x030D, 0x03, 0x01,
	0x030E, 0x00, 0x01,
	0x030F, 0x9E, 0x01,
	0x0310, 0x01, 0x01,
	0x0808, 0x00, 0x01,
	0x4648, 0x7F, 0x01,
	0x7420, 0x00, 0x01,
	0x7421, 0x5C, 0x01,
	0x7422, 0x00, 0x01,
	0x7423, 0xD7, 0x01,
	0x9104, 0x04, 0x01,
	0x0342, 0x14, 0x01,
	0x0343, 0xE8, 0x01,
	0x0340, 0x0C, 0x01,
	0x0341, 0xA4, 0x01,
	0x0344, 0x00, 0x01,
	0x0345, 0x00, 0x01,
	0x0346, 0x00, 0x01,
	0x0347, 0x3C, 0x01,
	0x0348, 0x10, 0x01,
	0x0349, 0x6F, 0x01,
	0x034A, 0x0B, 0x01,
	0x034B, 0xF3, 0x01,
	0x0381, 0x01, 0x01,
	0x0383, 0x01, 0x01,
	0x0385, 0x01, 0x01,
	0x0387, 0x01, 0x01,
	0x0900, 0x01, 0x01,
	0x0901, 0x12, 0x01,
	0x0401, 0x01, 0x01,
	0x0404, 0x00, 0x01,
	0x0405, 0x20, 0x01,
	0x0408, 0x00, 0x01,
	0x0409, 0x66, 0x01,
	0x040A, 0x00, 0x01,
	0x040B, 0x00, 0x01,
	0x040C, 0x0F, 0x01,
	0x040D, 0xA2, 0x01,
	0x040E, 0x05, 0x01,
	0x040F, 0xDC, 0x01,
	0x3038, 0x00, 0x01,
	0x303A, 0x00, 0x01,
	0x303B, 0x10, 0x01,
	0x300D, 0x00, 0x01,
	0x034C, 0x07, 0x01,
	0x034D, 0xD0, 0x01,
	0x034E, 0x05, 0x01,
	0x034F, 0xDC, 0x01,
	0x0202, 0x0C, 0x01,
	0x0203, 0x9A, 0x01,
	0x0204, 0x00, 0x01,
	0x0205, 0x00, 0x01,
	0x020E, 0x01, 0x01,
	0x020F, 0x00, 0x01,
	0x0210, 0x01, 0x01,
	0x0211, 0x00, 0x01,
	0x0212, 0x01, 0x01,
	0x0213, 0x00, 0x01,
	0x0214, 0x01, 0x01,
	0x0215, 0x00, 0x01,
	0x7BCD, 0x01, 0x01,
	0x94DC, 0x20, 0x01,
	0x94DD, 0x20, 0x01,
	0x94DE, 0x20, 0x01,
	0x95DC, 0x20, 0x01,
	0x95DD, 0x20, 0x01,
	0x95DE, 0x20, 0x01,
	0x7FB0, 0x00, 0x01,
	0x9010, 0x3E, 0x01,
	0x9419, 0x50, 0x01,
	0x941B, 0x50, 0x01,
	0x9519, 0x50, 0x01,
	0x951B, 0x50, 0x01,
	0x3030, 0x00, 0x01,
	0x3032, 0x00, 0x01,
	0x0220, 0x00, 0x01,
	0x0B06, 0x00, 0x01,
};

/* K-5 */
const u16 sensor_imx258_setfile_A_2000x1128_30fps[] = {
	0x0112, 0x0A, 0x01,
	0x0113, 0x0A, 0x01,
	0x0114, 0x03, 0x01,
	0x0301, 0x05, 0x01,
	0x0303, 0x02, 0x01,
	0x0305, 0x03, 0x01,
	0x0306, 0x00, 0x01,
	0x0307, 0xCB, 0x01,
	0x0309, 0x0A, 0x01,
	0x030B, 0x01, 0x01,
	0x030D, 0x03, 0x01,
	0x030E, 0x00, 0x01,
	0x030F, 0x9E, 0x01,
	0x0310, 0x01, 0x01,
	0x0808, 0x00, 0x01,
	0x4648, 0x7F, 0x01,
	0x7420, 0x00, 0x01,
	0x7421, 0x5C, 0x01,
	0x7422, 0x00, 0x01,
	0x7423, 0xD7, 0x01,
	0x9104, 0x04, 0x01,
	0x0342, 0x14, 0x01,
	0x0343, 0xE8, 0x01,
	0x0340, 0x0C, 0x01,
	0x0341, 0xA4, 0x01,
	0x0344, 0x00, 0x01,
	0x0345, 0x00, 0x01,
	0x0346, 0x01, 0x01,
	0x0347, 0xB0, 0x01,
	0x0348, 0x10, 0x01,
	0x0349, 0x6F, 0x01,
	0x034A, 0x0A, 0x01,
	0x034B, 0x7F, 0x01,
	0x0381, 0x01, 0x01,
	0x0383, 0x01, 0x01,
	0x0385, 0x01, 0x01,
	0x0387, 0x01, 0x01,
	0x0900, 0x01, 0x01,
	0x0901, 0x12, 0x01,
	0x0401, 0x01, 0x01,
	0x0404, 0x00, 0x01,
	0x0405, 0x20, 0x01,
	0x0408, 0x00, 0x01,
	0x0409, 0x66, 0x01,
	0x040A, 0x00, 0x01,
	0x040B, 0x00, 0x01,
	0x040C, 0x0F, 0x01,
	0x040D, 0xA2, 0x01,
	0x040E, 0x04, 0x01,
	0x040F, 0x68, 0x01,
	0x3038, 0x00, 0x01,
	0x303A, 0x00, 0x01,
	0x303B, 0x10, 0x01,
	0x300D, 0x00, 0x01,
	0x034C, 0x07, 0x01,
	0x034D, 0xD0, 0x01,
	0x034E, 0x04, 0x01,
	0x034F, 0x68, 0x01,
	0x0202, 0x0C, 0x01,
	0x0203, 0x9A, 0x01,
	0x0204, 0x00, 0x01,
	0x0205, 0x00, 0x01,
	0x020E, 0x01, 0x01,
	0x020F, 0x00, 0x01,
	0x0210, 0x01, 0x01,
	0x0211, 0x00, 0x01,
	0x0212, 0x01, 0x01,
	0x0213, 0x00, 0x01,
	0x0214, 0x01, 0x01,
	0x0215, 0x00, 0x01,
	0x7BCD, 0x01, 0x01,
	0x94DC, 0x20, 0x01,
	0x94DD, 0x20, 0x01,
	0x94DE, 0x20, 0x01,
	0x95DC, 0x20, 0x01,
	0x95DD, 0x20, 0x01,
	0x95DE, 0x20, 0x01,
	0x7FB0, 0x00, 0x01,
	0x9010, 0x3E, 0x01,
	0x9419, 0x50, 0x01,
	0x941B, 0x50, 0x01,
	0x9519, 0x50, 0x01,
	0x3030, 0x00, 0x01,
	0x3032, 0x00, 0x01,
	0x0220, 0x00, 0x01,
	0x0B06, 0x00, 0x01,
};

/* 4000x3000_30fps */
const struct sensor_cis_mode_info sensor_imx258_mode_info_A_4000x3000_30fps = {
	.setfile_index = SENSOR_IMX258_MODE_4000x3000_30FPS,
	.setfile = SENSOR_REGS(sensor_imx258_setfile_A_4000x3000_30fps),
	.pclk = 501760000ULL,
	.line_length_pck = 5352,
	.frame_length_lines = 3124,
	.max_analog_gain = 0x1E0,
	.max_digital_gain = 0x0FD9,
	.min_cit = 1,
	.max_cit_margin = 10,
	.align_cit = 1,
};

/* 4000x2256_30fps */
const struct sensor_cis_mode_info sensor_imx258_mode_info_A_4000x2256_30fps = {
	.setfile_index = SENSOR_IMX258_MODE_4000x2256_30FPS,
	.setfile = SENSOR_REGS(sensor_imx258_setfile_A_4000x2256_30fps),
	.pclk = 501760000ULL,
	.line_length_pck = 5352,
	.frame_length_lines = 3124,
	.max_analog_gain = 0x1E0,
	.max_digital_gain = 0x0FD9,
	.min_cit = 1,
	.max_cit_margin = 10,
	.align_cit = 1,
};

/* 1000x750_120fps */
const struct sensor_cis_mode_info sensor_imx258_mode_info_A_1000x750_120fps = {
	.setfile_index = SENSOR_IMX258_MODE_1000x750_120FPS,
	.setfile = SENSOR_REGS(sensor_imx258_setfile_A_1000x750_120fps),
	.pclk = 519680000ULL,
	.line_length_pck = 5352,
	.frame_length_lines = 808,
	.max_analog_gain = 0x1E0,
	.max_digital_gain = 0x0FD9,
	.min_cit = 1,
	.max_cit_margin = 10,
	.align_cit = 1,
};

/* 2000x1500_30fps */
const struct sensor_cis_mode_info sensor_imx258_mode_info_A_2000x1500_30fps = {
	.setfile_index = SENSOR_IMX258_MODE_2000x1500_30FPS,
	.setfile = SENSOR_REGS(sensor_imx258_setfile_A_2000x1500_30fps),
	.pclk = 519680000ULL,
	.line_length_pck = 5352,
	.frame_length_lines = 3236,
	.max_analog_gain = 0x1E0,
	.max_digital_gain = 0x0FD9,
	.min_cit = 1,
	.max_cit_margin = 10,
	.align_cit = 1,
};

/* 2000x1128_30fps */
const struct sensor_cis_mode_info sensor_imx258_mode_info_A_2000x1128_30fps = {
	.setfile_index = SENSOR_IMX258_MODE_2000x1128_30FPS,
	.setfile = SENSOR_REGS(sensor_imx258_setfile_A_2000x1128_30fps),
	.pclk = 519680000ULL,
	.line_length_pck = 5352,
	.frame_length_lines = 3236,
	.max_analog_gain = 0x1E0,
	.max_digital_gain = 0x0FD9,
	.min_cit = 1,
	.max_cit_margin = 10,
	.align_cit = 1,
};

static const struct sensor_cis_mode_info *sensor_imx258_mode_infos_A[] = {
	&sensor_imx258_mode_info_A_4000x3000_30fps,
	&sensor_imx258_mode_info_A_4000x2256_30fps,
	&sensor_imx258_mode_info_A_1000x750_120fps,
	&sensor_imx258_mode_info_A_2000x1500_30fps,
	&sensor_imx258_mode_info_A_2000x1128_30fps,
};

static const struct sensor_imx258_private_data sensor_imx258_private_data_A = {
	.global = SENSOR_REGS(sensor_imx258_setfile_A_global),
};

static const struct sensor_cis_info sensor_imx258_info_A = {
	.name = "IMX258",
	.version = "IMX258ES1(0ATH5)_SEC_19.2M_RegisterSetting_ver4.00-0.23_230710",
	.max_width = 4000,
	.max_height = 3000,
	.min_analog_gain = 0x0, /* x1.0 */
	.min_digital_gain = 0x100, /* x1.0 */
	.fine_integration_time = 0x054C,
	.cit_compensation_threshold = 15,
	.use_group_param_hold = false,
	.mode_infos = sensor_imx258_mode_infos_A,
	.mode_count = ARRAY_SIZE(sensor_imx258_mode_infos_A),
	.priv = (void *)&sensor_imx258_private_data_A,
#ifdef USE_CAMERA_ADAPTIVE_MIPI
	.mipi_mode = sensor_imx258_setfile_A_19p2_mipi_sensor_mode,
	.mipi_mode_count = ARRAY_SIZE(sensor_imx258_setfile_A_19p2_mipi_sensor_mode),
#endif
};

#endif
