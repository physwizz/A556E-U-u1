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

#ifndef PABLO_DEVICE_H
#define PABLO_DEVICE_H

#include <linux/types.h>

struct pablo_device {
	char	*stm;
	u32	instance;
};

#endif /* PABLO_DEVICE_H */