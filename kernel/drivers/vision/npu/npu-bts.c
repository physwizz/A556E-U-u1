/*
 * Samsung Exynos SoC series NPU driver
 *
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/version.h>
#include <linux/delay.h>
#include <linux/random.h>
#include <linux/printk.h>
#include <linux/cpuidle.h>
#include <soc/samsung/bts.h>
#if IS_ENABLED(CONFIG_EXYNOS_PM_QOS)
#include <soc/samsung/exynos-devfreq.h>
#endif

#include "npu-config.h"
#include "npu-scheduler-governor.h"
#include "npu-device.h"
#include "npu-llc.h"
#include "npu-util-regs.h"
#include "npu-hw-device.h"

#if IS_ENABLED(CONFIG_EXYNOS_BTS) || IS_ENABLED(CONFIG_EXYNOS_BTS_MODULE)
unsigned int npu_bts_get_scenindex(const char *name)
{
	return bts_get_scenindex(name);
}

int npu_bts_add_scenario(unsigned int index)
{
	return bts_add_scenario(index);
}

int npu_bts_del_scenario(unsigned int index)
{
	return bts_del_scenario(index);
}
#else
unsigned int npu_bts_get_scenindex(
		__attribute__((unused))const char *name)
{
	return 0;
}

int npu_bts_add_scenario(
		__attribute__((unused))unsigned int index)
{
	return 0;
}

int npu_bts_del_scenario(
		__attribute__((unused))unsigned int index)
{
	return 0;
}
#endif
