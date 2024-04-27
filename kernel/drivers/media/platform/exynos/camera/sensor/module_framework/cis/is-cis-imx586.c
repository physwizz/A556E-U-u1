/*
 * Samsung Exynos5 SoC series Sensor driver
 *
 *
 * Copyright (c) 2018 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/gpio.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/videodev2.h>
#include <videodev2_exynos_camera.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/syscalls.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-subdev.h>

#include <exynos-is-sensor.h>
#include "is-hw.h"
#include "is-core.h"
#include "is-param.h"
#include "is-device-sensor.h"
#include "is-device-sensor-peri.h"
#include "is-resourcemgr.h"
#include "is-dt.h"
#include "is-cis-imx586.h"
#include "is-cis-imx586-setA.h"

#include "is-helper-ixc.h"

#include "is-vendor.h"

#include "interface/is-interface-library.h"

#define SENSOR_NAME "IMX586"

static u8 coarse_integ_step_value;

static const u32 *sensor_imx586_global;
static u32 sensor_imx586_global_size;
static const u32 **sensor_imx586_setfiles;
static const u32 *sensor_imx586_setfile_sizes;
static u32 sensor_imx586_max_setfile_num;
static const struct sensor_pll_info_compact **sensor_imx586_pllinfos;

static bool sensor_imx586_cal_write_flag;

static void sensor_imx586_set_integration_max_margin(u32 mode, cis_shared_data *cis_data)
{
	FIMC_BUG_VOID(!cis_data);

	cis_data->max_margin_coarse_integration_time = SENSOR_IMX586_COARSE_INTEGRATION_TIME_MAX_MARGIN;
	dbg_sensor(1, "max_margin_coarse_integration_time(%d)\n",
		cis_data->max_margin_coarse_integration_time);
}

static void sensor_imx586_set_integration_min(u32 mode, cis_shared_data *cis_data)
{
	FIMC_BUG_VOID(!cis_data);

	err("[%s] Unsupport imx586 sensor mode\n", __func__);
	cis_data->min_coarse_integration_time = SENSOR_IMX586_COARSE_INTEGRATION_TIME_MIN;
	dbg_sensor(1, "min_coarse_integration_time(%d)\n",
			cis_data->min_coarse_integration_time);
}

static void sensor_imx586_set_integration_step_value(u32 mode)
{
	switch (mode) {
	case SENSOR_IMX586_2X2BIN_FULL_4000X3000_30FPS:
		coarse_integ_step_value = 1;
		dbg_sensor(1, "coarse_integration step value(%d)\n",
			coarse_integ_step_value);
		break;
	default:
		err("[%s] Unsupport imx586 sensor mode\n", __func__);
		coarse_integ_step_value = 1;
		dbg_sensor(1, "coarse_integration step value(%d)\n",
			coarse_integ_step_value);
		break;
	}
}

static void sensor_imx586_cis_data_calculation(const struct sensor_pll_info_compact *pll_info, cis_shared_data *cis_data)
{
	u64 vt_pix_clk_hz;
	u32 frame_rate, max_fps, frame_valid_us;

	FIMC_BUG_VOID(!pll_info);

	/* 1. get pclk value from pll info */
	/* Pixel rate [pixels/s] = IVTPXCK [MHz] * 8 (Total number of IVTPX channel) */
	vt_pix_clk_hz = pll_info->pclk * TOTAL_NUM_OF_IVTPX_CHANNEL;

	/* 2. the time of processing one frame calculation (us) */
	cis_data->min_frame_us_time = (((u64)pll_info->frame_length_lines) * pll_info->line_length_pck * 1000
	                / (vt_pix_clk_hz / 1000));
	cis_data->cur_frame_us_time = cis_data->min_frame_us_time;
	cis_data->base_min_frame_us_time = cis_data->min_frame_us_time;

	/* 3. FPS calculation */
	frame_rate = vt_pix_clk_hz / (pll_info->frame_length_lines * pll_info->line_length_pck);
	dbg_sensor(1, "frame_rate (%d) = vt_pix_clk_hz(%llu) / "
		KERN_CONT "(pll_info->frame_length_lines(%d) * pll_info->line_length_pck(%d))\n",
		frame_rate, vt_pix_clk_hz, pll_info->frame_length_lines, pll_info->line_length_pck);

	/* calculate max fps */
	max_fps = (vt_pix_clk_hz * 10) / (pll_info->frame_length_lines * pll_info->line_length_pck);
	max_fps = (max_fps % 10 >= 5 ? frame_rate + 1 : frame_rate);

	cis_data->pclk = vt_pix_clk_hz;
	cis_data->max_fps = max_fps;
	cis_data->frame_length_lines = pll_info->frame_length_lines;
	cis_data->line_length_pck = pll_info->line_length_pck;
	cis_data->line_readOut_time = (u64)cis_data->line_length_pck * 1000
					* 1000 * 1000 / cis_data->pclk;
	cis_data->rolling_shutter_skew = (cis_data->cur_height - 1) * cis_data->line_readOut_time;
	cis_data->stream_on = false;

	/* Frame valid time calculation */
	frame_valid_us = (u64)cis_data->cur_height * cis_data->line_length_pck
				* 1000 * 1000 / cis_data->pclk;
	cis_data->frame_valid_us_time = (int)frame_valid_us;

	dbg_sensor(1, "%s\n", __func__);
	dbg_sensor(1, "Sensor size(%d x %d) setting: SUCCESS!\n",
	                cis_data->cur_width, cis_data->cur_height);
	dbg_sensor(1, "Frame Valid(us): %d\n", frame_valid_us);
	dbg_sensor(1, "rolling_shutter_skew: %lld\n", cis_data->rolling_shutter_skew);

	dbg_sensor(1, "Fps: %d, max fps(%d)\n", frame_rate, cis_data->max_fps);
	dbg_sensor(1, "min_frame_time(%d us)\n", cis_data->min_frame_us_time);
	dbg_sensor(1, "Pixel rate(Kbps): %d\n", cis_data->pclk / 1000);

	/* Frame period calculation */
	cis_data->frame_time = (cis_data->line_readOut_time * cis_data->cur_height / 1000);
	cis_data->rolling_shutter_skew = (cis_data->cur_height - 1) * cis_data->line_readOut_time;

	dbg_sensor(1, "[%s] frame_time(%d), rolling_shutter_skew(%lld)\n", __func__,
		cis_data->frame_time, cis_data->rolling_shutter_skew);

	/* Constant values */
	cis_data->min_fine_integration_time = SENSOR_IMX586_FINE_INTEGRATION_TIME;
	cis_data->max_fine_integration_time = SENSOR_IMX586_FINE_INTEGRATION_TIME;
	cis_data->min_coarse_integration_time = SENSOR_IMX586_COARSE_INTEGRATION_TIME_MIN;
	cis_data->max_margin_coarse_integration_time= SENSOR_IMX586_COARSE_INTEGRATION_TIME_MAX_MARGIN;
	info("%s: done", __func__);
}

/*************************************************
 *  [imx586 Analog gain formular]
 *
 *  m0: [0x008c:0x008d] fixed to 0
 *  m1: [0x0090:0x0091] fixed to -1
 *  c0: [0x008e:0x008f] fixed to 1024
 *  c1: [0x0092:0x0093] fixed to 1024
 *  X : [0x0204:0x0205] Analog gain setting value
 *
 *  Analog Gain = (m0 * X + c0) / (m1 * X + c1)
 *              = 1024 / (1024 - X)
 *
 *  Analog Gain Range = 112 to 1008 (1dB to 26dB)
 *
 *************************************************/

u32 sensor_imx586_cis_calc_again_code(u32 permille)
{
	return 1024 - (1024000 / permille);
}

u32 sensor_imx586_cis_calc_again_permile(u32 code)
{
	return 1024000 / (1024 - code);
}

u32 sensor_imx586_cis_calc_dgain_code(u32 permile)
{
	u8 buf[2] = {0, 0};
	buf[0] = (permile / 1000) & 0x0F;
	buf[1] = (((permile - (buf[0] * 1000)) * 256) / 1000);

	return (buf[0] << 8 | buf[1]);
}

u32 sensor_imx586_cis_calc_dgain_permile(u32 code)
{
	return (((code & 0x0F00) >> 8) * 1000) + ((code & 0x00FF) * 1000 / 256);
}

u32 sensor_imx586_cis_get_fineIntegTime(struct is_cis *cis)
{
	u32 ret = 0;
	u16 fine_integ_time = 0;

	FIMC_BUG(!cis);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
	}

	IXC_MUTEX_LOCK(cis->ixc_lock);
	/* FINE_INTEG_TIME ADDR [0x0200:0x0201] */
	ret = cis->ixc_ops->read16(cis->client, SENSOR_IMX586_FINE_INTEG_TIME_ADDR, &fine_integ_time);
	if (ret < 0) {
		err("is_sensor_read16 fail (ret %d)", ret);
		IXC_MUTEX_UNLOCK(cis->ixc_lock);
		return ret;
	}
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

	info("%s: read fine_integ_time = %#x\n", __func__, fine_integ_time);

	return ret;
}

/* CIS OPS */
int sensor_imx586_cis_init(struct v4l2_subdev *subdev)
{
	int ret = 0;
	struct is_cis *cis;
	u32 setfile_index = 0;
	cis_setting_info setinfo;
	ktime_t st = ktime_get();

	setinfo.param = NULL;
	setinfo.return_value = 0;

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);
	if (!cis) {
		err("cis is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	FIMC_BUG(!cis->cis_data);
	memset(cis->cis_data, 0, sizeof(cis_shared_data));

	probe_info("%s imx586 init\n", __func__);
	cis->rev_flag = false;

/***********************************************************************
***** Check that QSC Cal is written for Remosaic Capture.
***** false : Not yet write the QSC
***** true  : Written the QSC Or Skip
***********************************************************************/
	sensor_imx586_cal_write_flag = false;

#if !defined(CONFIG_CAMERA_VENDOR_MCD)
	memset(cis->cis_data, 0, sizeof(cis_shared_data));

	ret = sensor_cis_check_rev(cis);
	if (ret < 0) {
		warn("sensor_imx586_check_rev is fail when cis init");
		cis->rev_flag = true;
		ret = -EINVAL;
		goto p_err;
	}
#endif

	cis->cis_data->cur_width = SENSOR_IMX586_MAX_WIDTH;
	cis->cis_data->cur_height = SENSOR_IMX586_MAX_HEIGHT;
	cis->cis_data->low_expo_start = 33000;
	cis->need_mode_change = false;
	cis->long_term_mode.sen_strm_off_on_step = 0;
	cis->mipi_clock_index_cur = CAM_MIPI_NOT_INITIALIZED;
	cis->mipi_clock_index_new = CAM_MIPI_NOT_INITIALIZED;

	sensor_imx586_cis_data_calculation(sensor_imx586_pllinfos[setfile_index], cis->cis_data);
	sensor_imx586_set_integration_max_margin(setfile_index, cis->cis_data);
	sensor_imx586_set_integration_min(setfile_index, cis->cis_data);
	sensor_imx586_set_integration_step_value(setfile_index);

#if SENSOR_IMX586_DEBUG_INFO
	ret = sensor_imx586_cis_get_fineIntegTime(cis);
	if (ret < 0) {
		err("sensor_imx586_cis_get_fineIntegTime fail!! (%d)", ret);
		goto p_err;
	}

	setinfo.return_value = 0;
	CALL_CISOPS(cis, cis_get_min_exposure_time, subdev, &setinfo.return_value);
	dbg_sensor(1, "[%s] min exposure time : %d\n", __func__, setinfo.return_value);
	setinfo.return_value = 0;
	CALL_CISOPS(cis, cis_get_max_exposure_time, subdev, &setinfo.return_value);
	dbg_sensor(1, "[%s] max exposure time : %d\n", __func__, setinfo.return_value);
	setinfo.return_value = 0;
	CALL_CISOPS(cis, cis_get_min_analog_gain, subdev, &setinfo.return_value);
	dbg_sensor(1, "[%s] min again : %d\n", __func__, setinfo.return_value);
	setinfo.return_value = 0;
	CALL_CISOPS(cis, cis_get_max_analog_gain, subdev, &setinfo.return_value);
	dbg_sensor(1, "[%s] max again : %d\n", __func__, setinfo.return_value);
	setinfo.return_value = 0;
	CALL_CISOPS(cis, cis_get_min_digital_gain, subdev, &setinfo.return_value);
	dbg_sensor(1, "[%s] min dgain : %d\n", __func__, setinfo.return_value);
	setinfo.return_value = 0;
	CALL_CISOPS(cis, cis_get_max_digital_gain, subdev, &setinfo.return_value);
	dbg_sensor(1, "[%s] max dgain : %d\n", __func__, setinfo.return_value);
	setinfo.return_value = 0;
#endif

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_err:
	return ret;
}

int sensor_imx586_cis_log_status(struct v4l2_subdev *subdev)
{
	int ret = 0;
	struct is_cis *cis;
	u8 data8 = 0;
	u16 data16 = 0;

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);
	if (!cis) {
		err("cis is NULL");
		ret = -ENODEV;
		goto p_err;
	}

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -ENODEV;
		goto p_err;
	}

	IXC_MUTEX_LOCK(cis->ixc_lock);
	pr_err("[SEN:DUMP] *******************************\n");
	cis->ixc_ops->read16(cis->client, 0x0000, &data16);
	pr_err("[SEN:DUMP] model_id(%x)\n", data16);
	cis->ixc_ops->read8(cis->client, 0x0002, &data8);
	pr_err("[SEN:DUMP] revision_number(%x)\n", data8);
	cis->ixc_ops->read8(cis->client, 0x0005, &data8);
	pr_err("[SEN:DUMP] frame_count(%x)\n", data8);
	cis->ixc_ops->read8(cis->client, 0x0100, &data8);
	pr_err("[SEN:DUMP] mode_select(%x)\n", data8);

	sensor_cis_dump_registers(subdev, sensor_imx586_setfiles[0], sensor_imx586_setfile_sizes[0]);
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

	pr_err("[SEN:DUMP] *******************************\n");

p_err:
	return ret;
}

static int sensor_imx586_cis_group_param_hold_func(struct v4l2_subdev *subdev, unsigned int hold)
{
#if USE_GROUP_PARAM_HOLD
	int ret = 0;
	struct is_cis *cis = NULL;

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	if (hold == cis->cis_data->group_param_hold) {
		pr_debug("already group_param_hold (%d)\n", cis->cis_data->group_param_hold);
		goto p_err;
	}

	ret = cis->ixc_ops->write8(cis->client, 0x0104, hold);
	if (ret < 0)
		goto p_err;

	cis->cis_data->group_param_hold = hold;
	ret = 1;

p_err:
	return ret;
#else

	return 0;
#endif
}

/* Input
 *	hold : true - hold, flase - no hold
 * Output
 *      return: 0 - no effect(already hold or no hold)
 *		positive - setted by request
 *		negative - ERROR value
 */
int sensor_imx586_cis_group_param_hold(struct v4l2_subdev *subdev, bool hold)
{
	int ret = 0;
	struct is_cis *cis = NULL;

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	IXC_MUTEX_LOCK(cis->ixc_lock);
	ret = sensor_imx586_cis_group_param_hold_func(subdev, hold);
	if (ret < 0)
		goto p_err;

p_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);
	return ret;
}

#define CIS_CALIBRATION 0
#if IS_ENABLED(CIS_CALIBRATION)
int sensor_imx586_calibration_setting(struct is_cis *cis)
{
	int ret = 0, i;
	char *cal_buf;
	struct is_rom_info *finfo = NULL;
	u8 spdc_cal[SENSOR_IMX586_SPDC_CAL_SIZE];
	u8 pdxtc_cal[SENSOR_IMX586_PDXTC_CAL_SIZE];
	int spdc_size, pdxtc_size[2];

	is_sec_get_cal_buf(&cal_buf, ROM_ID_REAR4);
	is_sec_get_sysfs_finfo(&finfo, ROM_ID_REAR4);

#ifdef CAMERA_IMX586_CAL_MODULE_VERSION
	if(finfo->header_ver[10] < CAMERA_IMX586_CAL_MODULE_VERSION) {
		info("%s - skip calibration, cal value not valid(cur_header : %s)", __func__, finfo->header_ver);
		return 0;
	}
#endif

	spdc_size = finfo->rom_spdc_cal_data_size;
	pdxtc_size[0] = finfo->rom_pdxtc_cal_data_0_size;
	pdxtc_size[1] = finfo->rom_pdxtc_cal_data_1_size;

	memcpy(spdc_cal, &cal_buf[finfo->rom_spdc_cal_data_start_addr], SENSOR_IMX586_SPDC_CAL_SIZE);
	memcpy(pdxtc_cal, &cal_buf[finfo->rom_pdxtc_cal_data_start_addr], SENSOR_IMX586_PDXTC_CAL_SIZE);

/* SPDC Calibraition */
	for (i=0; i<spdc_size; i++) {
		ret = cis->ixc_ops->write8(cis->client, 0x7F00+i, spdc_cal[i]);
		if (ret < 0)
			goto err;
	}


/* PDXTC Calibration */
	for (i=0;i<pdxtc_size[0];i++) {
		cis->ixc_ops->write8(cis->client, 0x7510+i, pdxtc_cal[i]);
		if (ret < 0)
			goto err;
	}
	for (i=0;i<pdxtc_size[1];i++) {
		cis->ixc_ops->write8(cis->client, 0x7600+i, pdxtc_cal[pdxtc_size[0] + i]);
		if (ret < 0)
			goto err;
	}

	info("%s - calibration applied",__func__);

	return ret;
err:
	err("%s - calibration failed",__func__);
	return -1;
}
#endif

int sensor_imx586_cis_set_global_setting(struct v4l2_subdev *subdev)
{
	int ret = 0;
	struct is_cis *cis = NULL;

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);
	FIMC_BUG(!cis);

	IXC_MUTEX_LOCK(cis->ixc_lock);

	/* setfile global setting is at camera entrance */
	info("[%s] global setting start\n", __func__);
	ret = sensor_cis_set_registers(subdev, sensor_imx586_global, sensor_imx586_global_size);
	if (ret < 0) {
		err("sensor_imx586_set_registers fail!!");
		goto p_err;
	}

#if IS_ENABLED(CIS_CALIBRATION)
	ret = sensor_imx586_calibration_setting(cis);
	if (ret < 0) {
		err("sensor_imx586_set_calibration fail!!");
		goto p_err;
	}
#endif

	dbg_sensor(1, "[%s] global setting done\n", __func__);

p_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

	// Check that QSC and DPC Cal is written for Remosaic Capture.
	// false : Not yet write the QSC and DPC
	// true  : Written the QSC and DPC
	sensor_imx586_cal_write_flag = false;
	return ret;
}

int sensor_imx586_cis_mode_change(struct v4l2_subdev *subdev, u32 mode)
{
	int ret = 0;
	struct is_cis *cis = NULL;

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);
	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	if (mode > sensor_imx586_max_setfile_num) {
		err("invalid mode(%d)!!", mode);
		ret = -EINVAL;
		goto p_err;
	}

	/* If check_rev(Sensor ID in OTP) of imx586 fail when cis_init, one more check_rev in mode_change */
	if (cis->rev_flag == true) {
		cis->rev_flag = false;
		ret = sensor_cis_check_rev(cis);
		if (ret < 0) {
			err("sensor_imx586_check_rev is fail");
			goto p_err;
		}
		info("[%s] cis_rev=%#x\n", __func__, cis->cis_data->cis_rev);
	}

	switch(mode) {
		case SENSOR_IMX586_REMOSAIC_FULL_8000X6000_15FPS:
		case SENSOR_IMX586_REMOSAIC_CROP_4000X3000_30FPS:
			cis->cis_data->max_analog_gain[0] = 960; /* x16 */
			cis->cis_data->max_analog_gain[1] = sensor_imx586_cis_calc_again_permile(cis->cis_data->max_analog_gain[0]);
			break;
		default:
			cis->cis_data->max_analog_gain[0] = SENSOR_IMX586_MAX_ANALOG_GAIN_SET_VALUE; /* x64 */
			cis->cis_data->max_analog_gain[1] = sensor_imx586_cis_calc_again_permile(cis->cis_data->max_analog_gain[0]);
			break;
	}

	sensor_imx586_set_integration_max_margin(mode, cis->cis_data);
	sensor_imx586_set_integration_min(mode, cis->cis_data);
	sensor_imx586_set_integration_step_value(mode);

	cis->mipi_clock_index_cur = CAM_MIPI_NOT_INITIALIZED;

	IXC_MUTEX_LOCK(cis->ixc_lock);

	info("[%s] mode=%d, mode change setting start\n", __func__, mode);
	ret = sensor_cis_set_registers(subdev, sensor_imx586_setfiles[mode], sensor_imx586_setfile_sizes[mode]);
	if (ret < 0) {
		err("sensor_imx586_set_registers fail!!");
		goto p_i2c_err;
	}
	dbg_sensor(1, "[%s] mode changed(%d)\n", __func__, mode);

	/* EMB Header off */
	ret = cis->ixc_ops->write8(cis->client, 0xbcf1, 0x00);
	if (ret < 0){
		err("EMB header off fail");
	}

p_i2c_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

p_err:
	return ret;
}

int sensor_imx586_cis_set_size(struct v4l2_subdev *subdev, cis_shared_data *cis_data)
{
	int ret = 0;
	struct is_cis *cis = NULL;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);
	FIMC_BUG(!cis);

	dbg_sensor(1, "[MOD:D:%d] %s\n", cis->id, __func__);

	if (unlikely(!cis_data)) {
		err("cis data is NULL");
		if (unlikely(!cis->cis_data)) {
			ret = -EINVAL;
			goto p_err;
		} else {
			cis_data = cis->cis_data;
		}
	}

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_err:

	return ret;
}

int sensor_imx586_cis_stream_on(struct v4l2_subdev *subdev)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	struct is_device_sensor_peri *sensor_peri = NULL;
	struct is_device_sensor *device;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);

	device = (struct is_device_sensor *)v4l2_get_subdev_hostdata(subdev);
	WARN_ON(!device);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	sensor_peri = container_of(cis, struct is_device_sensor_peri, cis);
	FIMC_BUG(!sensor_peri);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	cis_data = cis->cis_data;

	dbg_sensor(1, "[MOD:D:%d] %s\n", cis->id, __func__);

	is_vendor_set_mipi_clock(device);

	sensor_imx586_cis_group_param_hold(subdev, 0x01);

#ifdef SENSOR_imx586_DEBUG_INFO
	{
	u16 pll;
	cis->ixc_ops->read16(cis->client, 0x0300, &pll);
	dbg_sensor(1, "______ vt_pix_clk_div(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x0302, &pll);
	dbg_sensor(1, "______ vt_sys_clk_div(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x0304, &pll);
	dbg_sensor(1, "______ pre_pll_clk_div(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x0306, &pll);
	dbg_sensor(1, "______ pll_multiplier(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x030a, &pll);
	dbg_sensor(1, "______ op_sys_clk_div(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x030c, &pll);
	dbg_sensor(1, "______ op_prepllck_div(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x030e, &pll);
	dbg_sensor(1, "______ op_pll_multiplier(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x0310, &pll);
	dbg_sensor(1, "______ pll_mult_driv(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x0340, &pll);
	dbg_sensor(1, "______ frame_length_lines(%x)\n", pll);
	cis->ixc_ops->read16(cis->client, 0x0342, &pll);
	dbg_sensor(1, "______ line_length_pck(%x)\n", pll);
	}
#endif

	IXC_MUTEX_LOCK(cis->ixc_lock);

	info("[%s] start\n", __func__);
	/* Here Add for Master mode in dual */
	cis->ixc_ops->write8(cis->client, 0x3040, 0x01);
	cis->ixc_ops->write8(cis->client, 0x3F71, 0x01);

	cis->ixc_ops->write8(cis->client, 0x0101, 0x02);//TEMP_2020 flip setting(Only z3 project)

	/* Sensor stream on */
	cis->ixc_ops->write8(cis->client, 0x0100, 0x01);
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

	sensor_imx586_cis_group_param_hold(subdev, 0x00);

	cis_data->stream_on = true;

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_err:
	return ret;
}

int sensor_imx586_cis_stream_off(struct v4l2_subdev *subdev)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	cis_data = cis->cis_data;

	dbg_sensor(1, "[MOD:D:%d] %s\n", cis->id, __func__);

	sensor_imx586_cis_group_param_hold(subdev, 0x00);

	IXC_MUTEX_LOCK(cis->ixc_lock);
	cis->ixc_ops->write8(cis->client, 0x0100, 0x00);
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

	cis_data->stream_on = false;

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_err:
	return ret;
}

int sensor_imx586_cis_adjust_frame_duration(struct v4l2_subdev *subdev,
						u32 input_exposure_time,
						u32 *target_duration)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;

	u32 pix_rate_freq_mhz = 0;
	u32 line_length_pck = 0;
	u32 coarse_integ_time = 0;
	u32 frame_length_lines = 0;
	u32 frame_duration = 0;
	u32 max_frame_us_time = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!target_duration);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	pix_rate_freq_mhz = cis_data->pclk / (1000 * 1000);
	line_length_pck = cis_data->line_length_pck;
	coarse_integ_time = ((pix_rate_freq_mhz * input_exposure_time) / line_length_pck);
	frame_length_lines = coarse_integ_time + cis_data->max_margin_coarse_integration_time;

	frame_duration = (frame_length_lines * line_length_pck) / pix_rate_freq_mhz;
	max_frame_us_time = 1000000/cis->min_fps;

	dbg_sensor(1, "[%s](vsync cnt = %d) input exp(%d), adj duration, frame duraion(%d), min_frame_us(%d)\n",
			__func__, cis_data->sen_vsync_count, input_exposure_time, frame_duration, cis_data->min_frame_us_time);
	dbg_sensor(1, "[%s](vsync cnt = %d) adj duration, frame duraion(%d), min_frame_us(%d), max_frame_us_time(%d)\n",
			__func__, cis_data->sen_vsync_count, frame_duration, cis_data->min_frame_us_time, max_frame_us_time);

	dbg_sensor(1, "[%s] requested min_fps(%d), max_fps(%d) from HAL\n", __func__, cis->min_fps, cis->max_fps);

	*target_duration = MAX(frame_duration, cis_data->min_frame_us_time);
	if(cis->min_fps == cis->max_fps) {
		*target_duration = MIN(frame_duration, max_frame_us_time);
	}

	dbg_sensor(1, "[%s] calcurated frame_duration(%d), adjusted frame_duration(%d)\n", __func__, frame_duration, *target_duration);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_set_frame_duration(struct v4l2_subdev *subdev, u32 frame_duration)
{
	int ret = 0;
	int hold = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;

	u64 vt_pic_clk_freq_khz = 0;
	u32 line_length_pck = 0;
	u16 frame_length_lines = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	cis_data = cis->cis_data;

	if (frame_duration < cis_data->min_frame_us_time) {
		dbg_sensor(1, "frame duration is less than min(%d)\n", frame_duration);
		frame_duration = cis_data->min_frame_us_time;
	}

	vt_pic_clk_freq_khz = cis_data->pclk / 1000;
	line_length_pck = cis_data->line_length_pck;

	frame_length_lines = (u16)((vt_pic_clk_freq_khz * frame_duration) / (line_length_pck * 1000));

	dbg_sensor(1, "[MOD:D:%d] %s, vt_pic_clk_freq_khz(%#x) frame_duration = %d us,"
		KERN_CONT "(line_length_pck%#x), frame_length_lines(%#x)\n",
		cis->id, __func__, vt_pic_clk_freq_khz, frame_duration, line_length_pck, frame_length_lines);

	IXC_MUTEX_LOCK(cis->ixc_lock);

	hold = sensor_imx586_cis_group_param_hold_func(subdev, 0x01);
	if (hold < 0) {
		ret = hold;
		goto p_err;
	}

	ret = cis->ixc_ops->write16(cis->client, 0x0340, frame_length_lines);
	if (ret < 0)
		goto p_err;

	cis_data->cur_frame_us_time = frame_duration;
	cis_data->frame_length_lines = frame_length_lines;
	cis_data->max_coarse_integration_time = cis_data->frame_length_lines - cis_data->max_margin_coarse_integration_time;

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_err:
	if (hold > 0) {
		hold = sensor_imx586_cis_group_param_hold_func(subdev, 0x00);
		if (hold < 0)
			ret = hold;
	}

	IXC_MUTEX_UNLOCK(cis->ixc_lock);

	return ret;
}

int sensor_imx586_cis_set_frame_rate(struct v4l2_subdev *subdev, u32 min_fps)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;

	u32 frame_duration = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	if (min_fps > cis_data->max_fps) {
		err("[MOD:D:%d] %s, request FPS is too high(%d), set to max(%d)\n",
			cis->id, __func__, min_fps, cis_data->max_fps);
		min_fps = cis_data->max_fps;
	}

	if (min_fps == 0) {
		err("[MOD:D:%d] %s, request FPS is 0, set to min FPS(1)\n",
			cis->id, __func__);
		min_fps = 1;
	}

	frame_duration = (1 * 1000 * 1000) / min_fps;

	dbg_sensor(1, "[MOD:D:%d] %s, set FPS(%d), frame duration(%d)\n",
			cis->id, __func__, min_fps, frame_duration);

	ret = sensor_imx586_cis_set_frame_duration(subdev, frame_duration);
	if (ret < 0) {
		err("[MOD:D:%d] %s, set frame duration is fail(%d)\n",
			cis->id, __func__, ret);
		goto p_err;
	}

	cis_data->min_frame_us_time = MAX(frame_duration, cis_data->base_min_frame_us_time);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_err:
	return ret;
}

int sensor_imx586_cis_set_exposure_time(struct v4l2_subdev *subdev, struct ae_param *target_exposure)
{
	int ret = 0;
	int hold = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	u32 pix_rate_freq_mhz = 0;
	u16 coarse_int = 0;
	u32 line_length_pck = 0;
	u32 min_fine_int = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!target_exposure);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	if ((target_exposure->long_val <= 0) || (target_exposure->short_val <= 0)) {
		err("[%s] invalid target exposure(%d, %d)\n", __func__,
				target_exposure->long_val, target_exposure->short_val);
		ret = -EINVAL;
		goto p_err;
	}

	cis_data = cis->cis_data;

	dbg_sensor(1, "[MOD:D:%d] %s, vsync_cnt(%d), target long(%d), short(%d)\n", cis->id, __func__,
			cis_data->sen_vsync_count, target_exposure->long_val, target_exposure->short_val);

	pix_rate_freq_mhz = cis_data->pclk / (1000 * 1000);
	line_length_pck = cis_data->line_length_pck;
	min_fine_int = cis_data->min_fine_integration_time;

	coarse_int = ((target_exposure->val * pix_rate_freq_mhz) - min_fine_int) / line_length_pck;

	if (coarse_int%coarse_integ_step_value)
		coarse_int -= 1;

	if (coarse_int > cis_data->max_coarse_integration_time) {
		dbg_sensor(1, "[MOD:D:%d] %s, vsync_cnt(%d), coarse(%d) max(%d)\n", cis->id, __func__,
			cis_data->sen_vsync_count, coarse_int, cis_data->max_coarse_integration_time);
		coarse_int = cis_data->max_coarse_integration_time;
	}

	if (coarse_int < cis_data->min_coarse_integration_time) {
		dbg_sensor(1, "[MOD:D:%d] %s, vsync_cnt(%d), coarse(%d) min(%d)\n", cis->id, __func__,
			cis_data->sen_vsync_count, coarse_int, cis_data->min_coarse_integration_time);
		coarse_int = cis_data->min_coarse_integration_time;
	}

	if (cis_data->min_coarse_integration_time == SENSOR_IMX586_COARSE_INTEGRATION_TIME_MIN
		&& coarse_int < 16
		&& coarse_int%2 == 0) {
		coarse_int -= 1;
	}

	cis_data->cur_exposure_coarse = coarse_int;
	cis_data->cur_long_exposure_coarse = coarse_int;
	cis_data->cur_short_exposure_coarse = coarse_int;

	hold = sensor_imx586_cis_group_param_hold(subdev, 0x01);
	if (hold < 0) {
		ret = hold;
		goto p_err;
	}

	IXC_MUTEX_LOCK(cis->ixc_lock);
	ret = cis->ixc_ops->write16(cis->client, SENSOR_IMX586_COARSE_INTEG_TIME_ADDR, coarse_int);
		if (ret < 0)
			goto p_i2c_err;

	dbg_sensor(1, "[MOD:D:%d] %s, vsync_cnt(%d): pix_rate_freq_mhz (%d),"
		KERN_CONT "line_length_pck(%d), frame_length_lines(%#x)\n", cis->id, __func__,
		cis_data->sen_vsync_count, pix_rate_freq_mhz, line_length_pck, cis_data->frame_length_lines);
	dbg_sensor(1, "[MOD:D:%d] %s, vsync_cnt(%d): coarse_integration_time (%#x)\n",
		cis->id, __func__, cis_data->sen_vsync_count, coarse_int);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_i2c_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

p_err:
	if (hold > 0) {
		hold = sensor_imx586_cis_group_param_hold_func(subdev, 0x00);
		if (hold < 0)
			ret = hold;
	}

	return ret;
}

int sensor_imx586_cis_get_min_exposure_time(struct v4l2_subdev *subdev, u32 *min_expo)
{
	int ret = 0;
	struct is_cis *cis = NULL;
	cis_shared_data *cis_data = NULL;
	u32 min_integration_time = 0;
	u32 min_coarse = 0;
	u32 min_fine = 0;
	u32 pix_rate_freq_mhz = 0;
	u32 line_length_pck = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!min_expo);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	pix_rate_freq_mhz = cis_data->pclk / (1000 * 1000);
	line_length_pck = cis_data->line_length_pck;
	min_coarse = cis_data->min_coarse_integration_time;
	min_fine = cis_data->min_fine_integration_time;

	min_integration_time = ((line_length_pck * min_coarse) + min_fine) / pix_rate_freq_mhz;
	*min_expo = min_integration_time;

	dbg_sensor(1, "[%s] min integration time %d\n", __func__, min_integration_time);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_get_max_exposure_time(struct v4l2_subdev *subdev, u32 *max_expo)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	u32 max_integration_time = 0;
	u32 max_coarse_margin = 0;
	u32 max_coarse = 0;
	u32 max_fine = 0;
	u32 pix_rate_freq_mhz = 0;
	u32 line_length_pck = 0;
	u32 frame_length_lines = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!max_expo);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	pix_rate_freq_mhz = cis_data->pclk / (1000 * 1000);
	line_length_pck = cis_data->line_length_pck;
	frame_length_lines = cis_data->frame_length_lines;
	max_coarse_margin = cis_data->max_margin_coarse_integration_time;
	max_coarse = frame_length_lines - max_coarse_margin;
	max_fine = cis_data->max_fine_integration_time;

	max_integration_time = ((line_length_pck * max_coarse) + max_fine) / pix_rate_freq_mhz;

	*max_expo = max_integration_time;

	/* To Do: is udating this value right hear? */
	cis_data->max_coarse_integration_time = max_coarse;

	dbg_sensor(1, "[%s] max integration time %d, max coarse integration %d\n",
			__func__, max_integration_time, cis_data->max_coarse_integration_time);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_adjust_analog_gain(struct v4l2_subdev *subdev, u32 input_again, u32 *target_permile)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;

	u32 again_code = 0;
	u32 again_permile = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!target_permile);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	again_code = sensor_imx586_cis_calc_again_code(input_again);

	if (again_code > cis_data->max_analog_gain[0]) {
		again_code = cis_data->max_analog_gain[0];
	} else if (again_code < cis_data->min_analog_gain[0]) {
		again_code = cis_data->min_analog_gain[0];
	}

	again_permile = sensor_imx586_cis_calc_again_permile(again_code);

	dbg_sensor(1, "[%s] min again(%d), max(%d), input_again(%d), code(%d), permile(%d)\n", __func__,
			cis_data->max_analog_gain[0],
			cis_data->min_analog_gain[0],
			input_again,
			again_code,
			again_permile);

	*target_permile = again_permile;

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_set_analog_gain(struct v4l2_subdev *subdev, struct ae_param *again)
{
	int ret = 0;
	int hold = 0;
	struct is_cis *cis;
	u16 analog_gain = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!again);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	analog_gain = (u16)sensor_imx586_cis_calc_again_code(again->val);

	if (analog_gain < cis->cis_data->min_analog_gain[0]) {
		analog_gain = cis->cis_data->min_analog_gain[0];
	}

	if (analog_gain > cis->cis_data->max_analog_gain[0]) {
		analog_gain = cis->cis_data->max_analog_gain[0];
	}

	dbg_sensor(1, "[MOD:D:%d] %s(vsync cnt = %d), input_again = %d us, analog_gain(%#x)\n",
		cis->id, __func__, cis->cis_data->sen_vsync_count, again->val, analog_gain);

	hold = sensor_imx586_cis_group_param_hold(subdev, 0x01);
	if (hold < 0) {
		ret = hold;
		goto p_err;
	}

	// the address of analog_gain is [9:0] from 0x0204 to 0x0205
	analog_gain &= 0x03FF;

	// Analog gain
	IXC_MUTEX_LOCK(cis->ixc_lock);
	ret = cis->ixc_ops->write16(cis->client, SENSOR_IMX586_ANALOG_GAIN_ADDR, analog_gain);
	if (ret < 0)
		goto p_i2c_err;

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_i2c_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

p_err:
	if (hold > 0) {
		hold = sensor_imx586_cis_group_param_hold_func(subdev, 0x00);
		if (hold < 0)
			ret = hold;
	}

	return ret;
}

int sensor_imx586_cis_get_analog_gain(struct v4l2_subdev *subdev, u32 *again)
{
	int ret = 0;
	int hold = 0;
	struct is_cis *cis;
	u16 analog_gain = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!again);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	hold = sensor_imx586_cis_group_param_hold(subdev, 0x01);
	if (hold < 0) {
		ret = hold;
		goto p_err;
	}

	IXC_MUTEX_LOCK(cis->ixc_lock);
	ret = cis->ixc_ops->read16(cis->client, SENSOR_IMX586_ANALOG_GAIN_ADDR, &analog_gain);
	if (ret < 0)
		goto p_i2c_err;

	analog_gain &= 0x03FF;
	*again = sensor_imx586_cis_calc_again_permile(analog_gain);

	dbg_sensor(1, "[MOD:D:%d] %s, cur_again = %d us, analog_gain(%#x)\n",
			cis->id, __func__, *again, analog_gain);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_i2c_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

p_err:
	if (hold > 0) {
		hold = sensor_imx586_cis_group_param_hold_func(subdev, 0x00);
		if (hold < 0)
			ret = hold;
	}

	return ret;
}

int sensor_imx586_cis_get_min_analog_gain(struct v4l2_subdev *subdev, u32 *min_again)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	u16 min_again_code = SENSOR_IMX586_MIN_ANALOG_GAIN_SET_VALUE;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!min_again);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	cis_data->min_analog_gain[0] = min_again_code;
	cis_data->min_analog_gain[1] = sensor_imx586_cis_calc_again_permile(min_again_code);
	*min_again = cis_data->min_analog_gain[1];

	dbg_sensor(1, "[%s] min_again_code %d, main_again_permile %d\n", __func__,
		cis_data->min_analog_gain[0], cis_data->min_analog_gain[1]);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_get_max_analog_gain(struct v4l2_subdev *subdev, u32 *max_again)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	u16 max_again_code = SENSOR_IMX586_MAX_ANALOG_GAIN_SET_VALUE;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!max_again);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	cis_data->max_analog_gain[0] = max_again_code;
	cis_data->max_analog_gain[1] = sensor_imx586_cis_calc_again_permile(max_again_code);
	*max_again = cis_data->max_analog_gain[1];

	dbg_sensor(1, "[%s] max_again_code %d, max_again_permile %d\n", __func__,
		cis_data->max_analog_gain[0], cis_data->max_analog_gain[1]);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_set_digital_gain(struct v4l2_subdev *subdev, struct ae_param *dgain)
{
	int ret = 0;
	int hold = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;

	u16 dgain_code = 0;
	u8 dgains[2] = {0};
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!dgain);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	cis_data = cis->cis_data;

	dgain_code = (u16)sensor_cis_calc_dgain_code(dgain->val);

	if (dgain_code < cis->cis_data->min_digital_gain[0]) {
		dgain_code = cis->cis_data->min_digital_gain[0];
	}
	if (dgain_code > cis->cis_data->max_digital_gain[0]) {
		dgain_code = cis->cis_data->max_digital_gain[0];
	}

	dbg_sensor(1, "[MOD:D:%d] %s(vsync cnt = %d), input_dgain = %d, dgain_code(%#x)\n",
			cis->id, __func__, cis->cis_data->sen_vsync_count, dgain->val, dgain_code);

	hold = sensor_imx586_cis_group_param_hold(subdev, 0x01);
	if (hold < 0) {
		ret = hold;
		goto p_err;
	}

	dgains[0] = (u8)((dgain_code & 0x0F00) >> 8);
	dgains[1] = (u8)(dgain_code & 0xFF);

	IXC_MUTEX_LOCK(cis->ixc_lock);
	ret = cis->ixc_ops->write8_array(client, SENSOR_IMX586_DIG_GAIN_ADDR, dgains, 2);
	if (ret < 0) {
		goto p_i2c_err;
	}

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_i2c_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

p_err:
	if (hold > 0) {
		hold = sensor_imx586_cis_group_param_hold_func(subdev, 0x00);
		if (hold < 0)
			ret = hold;
	}

	return ret;
}

int sensor_imx586_cis_get_digital_gain(struct v4l2_subdev *subdev, u32 *dgain)
{
	int ret = 0;
	int hold = 0;
	struct is_cis *cis;
	u16 digital_gain = 0;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!dgain);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	hold = sensor_imx586_cis_group_param_hold(subdev, 0x01);
	if (hold < 0) {
		ret = hold;
		goto p_err;
	}

	IXC_MUTEX_LOCK(cis->ixc_lock);
	ret = cis->ixc_ops->read16(cis->client, SENSOR_IMX586_DIG_GAIN_ADDR, &digital_gain);
	if (ret < 0)
		goto p_i2c_err;

	*dgain = sensor_cis_calc_dgain_permile(digital_gain);

	dbg_sensor(1, "[MOD:D:%d] %s, dgain_permile = %d, dgain_code(%#x)\n",
			cis->id, __func__, *dgain, digital_gain);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_i2c_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

p_err:
	if (hold > 0) {
		hold = sensor_imx586_cis_group_param_hold_func(subdev, 0x00);
		if (hold < 0)
			ret = hold;
	}

	return ret;
}

int sensor_imx586_cis_get_min_digital_gain(struct v4l2_subdev *subdev, u32 *min_dgain)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	u16 min_dgain_code = SENSOR_IMX586_MIN_DIGITAL_GAIN_SET_VALUE;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!min_dgain);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	cis_data->min_digital_gain[0] = min_dgain_code;
	cis_data->min_digital_gain[1] = sensor_imx586_cis_calc_dgain_permile(min_dgain_code);

	*min_dgain = cis_data->min_digital_gain[1];

	dbg_sensor(1, "[%s] min_dgain_code %d, min_dgain_permile %d\n", __func__,
		cis_data->min_digital_gain[0], cis_data->min_digital_gain[1]);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_get_max_digital_gain(struct v4l2_subdev *subdev, u32 *max_dgain)
{
	int ret = 0;
	struct is_cis *cis;
	cis_shared_data *cis_data;
	u16 max_dgain_code = SENSOR_IMX586_MAX_DIGITAL_GAIN_SET_VALUE;
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);
	FIMC_BUG(!max_dgain);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	cis_data = cis->cis_data;

	cis_data->max_digital_gain[0] = max_dgain_code;
	cis_data->max_digital_gain[1] = sensor_imx586_cis_calc_dgain_permile(max_dgain_code);

	*max_dgain = cis_data->max_digital_gain[1];

	dbg_sensor(1, "[%s] max_dgain_code %d, max_dgain_permile %d\n", __func__,
		cis_data->max_digital_gain[0], cis_data->max_digital_gain[1]);

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

	return ret;
}

int sensor_imx586_cis_set_wb_gain(struct v4l2_subdev *subdev, struct wb_gains wb_gains)
{
	int ret = 0;
	int hold = 0;
	int mode = 0;
	struct is_cis *cis;
	u16 abs_gains[4] = {0, };	//[0]=gr, [1]=r, [2]=b, [3]=gb
	ktime_t st = ktime_get();

	FIMC_BUG(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	if (!cis->use_wb_gain)
		return ret;

	if (unlikely(!cis->client)) {
		err("client is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	mode = cis->cis_data->sens_config_index_cur;

	dbg_sensor(1, "[SEN:%d]%s:DDK vlaue: wb_gain_gr(%d), wb_gain_r(%d), wb_gain_b(%d), wb_gain_gb(%d)\n",
		cis->id, __func__, wb_gains.gr, wb_gains.r, wb_gains.b, wb_gains.gb);

	abs_gains[0] = (u16)((wb_gains.gr / 4) & 0xFFFF);
	abs_gains[1] = (u16)((wb_gains.r / 4) & 0xFFFF);
	abs_gains[2] = (u16)((wb_gains.b / 4) & 0xFFFF);
	abs_gains[3] = (u16)((wb_gains.gb / 4) & 0xFFFF);

	dbg_sensor(1, "[SEN:%d]%s, abs_gain_gr(0x%4X), abs_gain_r(0x%4X), abs_gain_b(0x%4X), abs_gain_gb(0x%4X)\n",
		cis->id, __func__, abs_gains[0], abs_gains[1], abs_gains[2], abs_gains[3]);

	hold = sensor_imx586_cis_group_param_hold(subdev, 0x01);
	if (hold < 0) {
		ret = hold;
		goto p_err;
	}

	IXC_MUTEX_LOCK(cis->ixc_lock);
	ret = cis->ixc_ops->write16_array(cis->client, SENSOR_IMX586_ABS_GAIN_GR_SET_ADDR, abs_gains, 4);
	if (ret < 0)
		goto p_i2c_err;

	if (IS_ENABLED(DEBUG_SENSOR_TIME))
		dbg_sensor(1, "[%s] time %ldus", __func__, PABLO_KTIME_US_DELTA_NOW(st));

p_i2c_err:
	IXC_MUTEX_UNLOCK(cis->ixc_lock);

p_err:
	if (hold > 0) {
		hold = sensor_imx586_cis_group_param_hold(subdev, 0x00);
		if (hold < 0)
			ret = hold;
	}
	return ret;
}

void sensor_imx586_cis_data_calc(struct v4l2_subdev *subdev, u32 mode)
{
	int ret = 0;
	struct is_cis *cis = NULL;

	FIMC_BUG_VOID(!subdev);

	cis = (struct is_cis *)v4l2_get_subdevdata(subdev);
	FIMC_BUG_VOID(!cis);
	FIMC_BUG_VOID(!cis->cis_data);

	if (mode > sensor_imx586_max_setfile_num) {
		err("invalid mode(%d)!!", mode);
		return;
	}

	/* If check_rev fail when cis_init, one more check_rev in mode_change */
	if (cis->rev_flag == true) {
		cis->rev_flag = false;
		ret = sensor_cis_check_rev(cis);
		if (ret < 0) {
			err("sensor_imx586_check_rev is fail: ret(%d)", ret);
			return;
		}
	}

	sensor_imx586_cis_data_calculation(sensor_imx586_pllinfos[mode], cis->cis_data);
}

static struct is_cis_ops cis_ops_imx586 = {
	.cis_init = sensor_imx586_cis_init,
	.cis_log_status = sensor_imx586_cis_log_status,
	.cis_group_param_hold = sensor_imx586_cis_group_param_hold,
	.cis_set_global_setting = sensor_imx586_cis_set_global_setting,
	.cis_set_size = sensor_imx586_cis_set_size,
	.cis_mode_change = sensor_imx586_cis_mode_change,
	.cis_stream_on = sensor_imx586_cis_stream_on,
	.cis_stream_off = sensor_imx586_cis_stream_off,
	.cis_wait_streamon = sensor_cis_wait_streamon,
	.cis_wait_streamoff = sensor_cis_wait_streamoff,
	.cis_adjust_frame_duration = sensor_imx586_cis_adjust_frame_duration,
	.cis_set_frame_duration = sensor_imx586_cis_set_frame_duration,
	.cis_set_frame_rate = sensor_imx586_cis_set_frame_rate,
	.cis_set_exposure_time = sensor_imx586_cis_set_exposure_time,
	.cis_get_min_exposure_time = sensor_imx586_cis_get_min_exposure_time,
	.cis_get_max_exposure_time = sensor_imx586_cis_get_max_exposure_time,
	.cis_adjust_analog_gain = sensor_imx586_cis_adjust_analog_gain,
	.cis_set_analog_gain = sensor_imx586_cis_set_analog_gain,
	.cis_get_analog_gain = sensor_imx586_cis_get_analog_gain,
	.cis_get_min_analog_gain = sensor_imx586_cis_get_min_analog_gain,
	.cis_get_max_analog_gain = sensor_imx586_cis_get_max_analog_gain,
	.cis_set_digital_gain = sensor_imx586_cis_set_digital_gain,
	.cis_get_digital_gain = sensor_imx586_cis_get_digital_gain,
	.cis_get_min_digital_gain = sensor_imx586_cis_get_min_digital_gain,
	.cis_get_max_digital_gain = sensor_imx586_cis_get_max_digital_gain,
	.cis_compensate_gain_for_extremely_br = sensor_cis_compensate_gain_for_extremely_br,
	.cis_set_wb_gains = sensor_imx586_cis_set_wb_gain,
	.cis_data_calculation = sensor_imx586_cis_data_calc,
	.cis_check_rev_on_init = sensor_cis_check_rev_on_init,
};

int cis_imx586_probe_i2c(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int ret;
	struct is_cis *cis;
	struct is_device_sensor_peri *sensor_peri;
	char const *setfile;
	struct device_node *dnode = client->dev.of_node;
	int i;
	int index;
	const int *verify_sensor_mode = NULL;
	int verify_sensor_mode_size = 0;

	ret = sensor_cis_probe(client, &(client->dev), &sensor_peri, I2C_TYPE);
	if (ret) {
		probe_info("%s: sensor_cis_probe ret(%d)\n", __func__, ret);
		return ret;
	}

	cis = &sensor_peri->cis;
	cis->ctrl_delay = N_PLUS_TWO_FRAME;
	cis->cis_ops = &cis_ops_imx586;
	/* belows are depend on sensor cis. MUST check sensor spec */
	cis->bayer_order = OTF_INPUT_ORDER_BAYER_GB_RG; //TEMP_2020
	cis->use_wb_gain = true;

	ret = of_property_read_string(dnode, "setfile", &setfile);
	if (ret) {
		err("setfile index read fail(%d), take default setfile!!", ret);
		setfile = "default";
	}

	if (strcmp(setfile, "default") == 0 || strcmp(setfile, "setA") == 0) {
		probe_info("%s setfile_A\n", __func__);
		sensor_imx586_global = sensor_imx586_setfile_A_Global;
		sensor_imx586_global_size = ARRAY_SIZE(sensor_imx586_setfile_A_Global);
		sensor_imx586_setfiles = sensor_imx586_setfiles_A;
		sensor_imx586_setfile_sizes = sensor_imx586_setfile_A_sizes;
		sensor_imx586_pllinfos = sensor_imx586_pllinfos_A;
		sensor_imx586_max_setfile_num = ARRAY_SIZE(sensor_imx586_setfiles_A);
		verify_sensor_mode = sensor_IMX586_setfile_A_verify_sensor_mode;
		verify_sensor_mode_size = ARRAY_SIZE(sensor_IMX586_setfile_A_verify_sensor_mode);
	} else {
		err("%s setfile index out of bound, take default (setfile_A)", __func__);
		sensor_imx586_global = sensor_imx586_setfile_A_Global;
		sensor_imx586_global_size = ARRAY_SIZE(sensor_imx586_setfile_A_Global);
		sensor_imx586_setfiles = sensor_imx586_setfiles_A;
		sensor_imx586_setfile_sizes = sensor_imx586_setfile_A_sizes;
		sensor_imx586_pllinfos = sensor_imx586_pllinfos_A;
		sensor_imx586_max_setfile_num = ARRAY_SIZE(sensor_imx586_setfiles_A);
		verify_sensor_mode = sensor_IMX586_setfile_A_verify_sensor_mode;
		verify_sensor_mode_size = ARRAY_SIZE(sensor_IMX586_setfile_A_verify_sensor_mode);
	}

	if (cis->vendor_use_adaptive_mipi) {
		for (i = 0; i < verify_sensor_mode_size; i++) {
			index = verify_sensor_mode[i];

			if (index >= cis->mipi_sensor_mode_size || index < 0) {
				panic("wrong mipi_sensor_mode index");
				break;
			}
		}
	}

	probe_info("%s done\n", __func__);

	return ret;
}

static const struct of_device_id sensor_cis_imx586_match[] = {
	{
		.compatible = "samsung,exynos-is-cis-imx586",
	},
	{},
};
MODULE_DEVICE_TABLE(of, sensor_cis_imx586_match);

static const struct i2c_device_id sensor_cis_imx586_idt[] = {
	{ SENSOR_NAME, 0 },
	{},
};

static struct i2c_driver sensor_cis_imx586_driver = {
	.probe	= cis_imx586_probe_i2c,
	.driver = {
		.name	= SENSOR_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = sensor_cis_imx586_match,
		.suppress_bind_attrs = true,
	},
	.id_table = sensor_cis_imx586_idt
};

static int __init sensor_cis_imx586_init(void)
{
	int ret;

	ret = i2c_add_driver(&sensor_cis_imx586_driver);
	if (ret)
		err("failed to add %s driver: %d\n",
			sensor_cis_imx586_driver.driver.name, ret);

	return ret;
}
late_initcall_sync(sensor_cis_imx586_init);

MODULE_LICENSE("GPL");
