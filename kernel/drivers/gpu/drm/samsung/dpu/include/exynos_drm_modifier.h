// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS DRM modifier header file for Samsung EXYNOS DPU driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef EXYNOS_DRM_MODIFIER_H
#define EXYNOS_DRM_MODIFIER_H

#include <uapi/drm/drm_fourcc.h>

/*
 * Set to access the secure buffer
 *
 * The secure buffer is used to store DRM(Digital Right Management) contents.
 * DMA needs special authority to access the secure buffer. This modifier can
 * be set to allow the DMA to access the secure buffer. This can be used in
 * combination with another modifier.
 */
#define DRM_FORMAT_MOD_PROTECTION	fourcc_mod_code(NONE, (1ULL << 51))
#define DRM_MODE_GET_PROT(mod)		(!!((mod) & DRM_FORMAT_MOD_PROTECTION))

/*
 * SAMSUNG DRM Modifiers
 * [63:0]	: full modifier range, [63:56] vendor name [55:0] specific modifier
 * [3:0]	: 64x32 TILE = 1, 16x16 TILE = 2, 8P2 split = X, colormap = 4
 * [8:4]	: SBWC lossless and lossy
 * [13:9]	: VOTF_IN
 * [16:14]	: SAJC
 * [17]		: SBWC align indicator
 * [18]		: SAJC align indicator
 * [55:19]	: Reserved
 */

/*
 * The colormap uses the color data generated by hardware instead of reading
 * the data from the memory.
 *
 * It supports only solid color in BGRA8888 format. When it is used as
 * a modifier, BGRA8888 format should be used and color value is passed through
 * first handles[0].
 */
#define DRM_FORMAT_MOD_SAMSUNG_COLORMAP		fourcc_mod_code(SAMSUNG, 4)

/*
 * Samsung Virtual On The Fly (VOTF) modifier
 */
#define VOTF_IDENTIFIER				(1 << 9)
#define VOTF_BUF_IDX_MASK		(0xfULL << 10)
#define VOTF_BUF_IDX_SET(buf_idx)		\
		((buf_idx << 10) & VOTF_BUF_IDX_MASK)
#define VOTF_BUF_IDX_GET(modifier)		\
		(((modifier) & VOTF_BUF_IDX_MASK) >> 10)

#define DRM_FORMAT_MOD_SAMSUNG_VOTF(buf_idx)	\
		fourcc_mod_code(SAMSUNG,	\
		(VOTF_BUF_IDX_SET(buf_idx) | VOTF_IDENTIFIER))

/*
 * Samsung Band Width Compression (SBWC) modifier
 *
 * SBWC is a specific lossless or lossy image compression protocol and format.
 * It supports video image (YUV) compression to reduce the amount of data
 * transferred between IP blocks. This modifier is used when to decode data or
 * when to encode data through writeback.
 *
 * SBWC Modifiers
 * [4]		: SBWC identifier
 * [5:6]	: SBWC lossless/lossy/non comp
 * [8:7]	: SBWC lossy compression ratio(for legacy sbwc lossy)
 *		  8bpc format(e.g. NV12)  - 50%, 75%
 *		  10bpc format(e.g. P010) - 40%, 60%, 80%
 * [17]		: SBWC align indicator(32B or 256B)
 */
#define SBWC_IDENTIFIER				(1 << 4)
#define SBWC_MOD_NONE				(0ULL)
#define SBWC_MOD_LOSSLESS			(1ULL)
#define SBWC_MOD_LOSSY				(2ULL)
#define SBWC_MOD_TYPE_MASK			(0x3ULL << 5)
#define SBWC_MOD_TYPE_SET(t)			(((t) << 5) & SBWC_MOD_TYPE_MASK)
#define SBWC_MOD_TYPE_GET(mod)			(((mod) & SBWC_MOD_TYPE_MASK) >> 5)

#define SBWCL_8B_50				(1ULL)
#define SBWCL_8B_75				(2ULL)
#define SBWCL_10B_40				(1ULL)
#define SBWCL_10B_60				(2ULL)
#define SBWCL_10B_80				(3ULL)
#define SBWCL_MOD_RATIO_MASK			(0x3ULL << 7)
#define SBWCL_MOD_RATIO_SET(r)			(((r) << 7) & SBWCL_MOD_RATIO_MASK)
#define SBWCL_MOD_RATIO_GET(mod)		(((mod) & SBWCL_MOD_RATIO_MASK) >> 7)

#define SBWC_ALIGN_32				(0ULL)
#define SBWC_ALIGN_256				(1ULL)
#define SBWC_ALIGN_MASK				(0x1ULL << 17)
#define SBWC_ALIGN_SET(a)			(((a) << 17) & SBWC_ALIGN_MASK)
#define SBWC_ALIGN_GET(mod)			(((mod) & SBWC_ALIGN_MASK) >> 17)

#define DRM_FORMAT_MOD_SAMSUNG_SBWC(type, ratio, align)		\
		fourcc_mod_code(SAMSUNG, SBWC_IDENTIFIER |	\
		SBWC_MOD_TYPE_SET((type)) | SBWCL_MOD_RATIO_SET((ratio)) |\
			SBWC_ALIGN_SET((align)))

/*
 * Samsung AMD Joint Compression (SAJC) modifier
 *
 * SAJC is a specific lossless image compression protocol and format.
 * It supports graphic image (RGB) compression to reduce the amount of data
 * transferred between IP blocks.
 */
#define SAJC_IDENTIFIER				(1 << 14)
#define SAJC_FORMAT_MOD_BLK_SIZE_MASK		(0x3ULL << 15)
#define SAJC_BLK_SIZE_SET(blk_size)		\
		((blk_size << 15) & SAJC_FORMAT_MOD_BLK_SIZE_MASK)
#define SAJC_BLK_SIZE_GET(modifier)		\
		(((modifier) & SAJC_FORMAT_MOD_BLK_SIZE_MASK) >> 15)

#define SAJC_64K_MODE				(0ULL)
#define SAJC_4K_MODE				(1ULL)
#define SAJC_MOD_SW_MODE_MASK			(0x1ULL << 18)
#define SAJC_MOD_SW_MODE_SET(sw_mode)		(((sw_mode) << 18) & SAJC_MOD_SW_MODE_MASK)
#define SAJC_MOD_SW_MODE_GET(mod)		(((mod) & SAJC_MOD_SW_MODE_MASK) >> 18)

#define DRM_FORMAT_MOD_SAMSUNG_SAJC(blk_size, sw_mode)		\
		fourcc_mod_code(SAMSUNG, (SAJC_IDENTIFIER |	\
			SAJC_BLK_SIZE_SET(blk_size) | SAJC_MOD_SW_MODE_SET(sw_mode)))

/* from 52 to 55 bit are reserved for AFBC encoder source informaton */
#define AFBC_FORMAT_MOD_SOURCE_MASK	(0xfULL << 52)
#define AFBC_FORMAT_MOD_SOURCE_GPU	(1ULL << 52)
#define AFBC_FORMAT_MOD_SOURCE_G2D	(2ULL << 52)

#endif /* EXYNOS_DRM_MODIFIER_H */
