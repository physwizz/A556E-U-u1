// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Authors: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#include <drm/drm_atomic.h>
#include <drm/drm_atomic_helper.h>
#include <drm/drm_plane_helper.h>
#include <drm/drm_fourcc.h>
#include <drm/drm_blend.h>

#include <exynos_drm_drv.h>
#include <exynos_drm_crtc.h>
#include <exynos_drm_fb.h>
#include <exynos_drm_plane.h>
#include <exynos_drm_format.h>
#include <exynos_drm_modifier.h>
#include <exynos_drm_partial.h>

static const struct drm_prop_enum_list standard_list[] = {
	{ EXYNOS_STANDARD_UNSPECIFIED, "Unspecified" },
	{ EXYNOS_STANDARD_BT709, "BT709" },
	{ EXYNOS_STANDARD_BT601_625, "BT601_625" },
	{ EXYNOS_STANDARD_BT601_625_UNADJUSTED, "BT601_625_UNADJUSTED"},
	{ EXYNOS_STANDARD_BT601_525, "BT601_525" },
	{ EXYNOS_STANDARD_BT601_525_UNADJUSTED, "BT601_525_UNADJUSTED"},
	{ EXYNOS_STANDARD_BT2020, "BT2020" },
	{ EXYNOS_STANDARD_BT2020_CONSTANT_LUMINANCE,
		"BT2020_CONSTANT_LUMINANCE"},
	{ EXYNOS_STANDARD_BT470M, "BT470M" },
	{ EXYNOS_STANDARD_FILM, "FILM" },
	{ EXYNOS_STANDARD_DCI_P3, "DCI-P3" },
	{ EXYNOS_STANDARD_ADOBE_RGB, "Adobe RGB" },
};

static const struct drm_prop_enum_list transfer_list[] = {
	{ EXYNOS_TRANSFER_UNSPECIFIED, "Unspecified" },
	{ EXYNOS_TRANSFER_LINEAR, "Linear" },
	{ EXYNOS_TRANSFER_SRGB, "sRGB" },
	{ EXYNOS_TRANSFER_SMPTE_170M, "SMPTE 170M" },
	{ EXYNOS_TRANSFER_GAMMA2_2, "Gamma 2.2" },
	{ EXYNOS_TRANSFER_GAMMA2_6, "Gamma 2.6" },
	{ EXYNOS_TRANSFER_GAMMA2_8, "Gamma 2.8" },
	{ EXYNOS_TRANSFER_ST2084, "ST2084" },
	{ EXYNOS_TRANSFER_HLG, "HLG" },
};

static const struct drm_prop_enum_list range_list[] = {
	{ EXYNOS_RANGE_UNSPECIFIED, "Unspecified" },
	{ EXYNOS_RANGE_FULL, "Full" },
	{ EXYNOS_RANGE_LIMITED, "Limited" },
	{ EXYNOS_RANGE_EXTENDED, "Extended" },
};

static struct drm_plane_state *
exynos_drm_plane_duplicate_state(struct drm_plane *plane)
{
	struct exynos_drm_plane_state *exynos_state;
	struct exynos_drm_plane_state *copy;

	exynos_state = to_exynos_plane_state(plane->state);
	copy = kzalloc(sizeof(*exynos_state), GFP_KERNEL);
	if (!copy)
		return NULL;

	memcpy(copy, exynos_state, sizeof(*exynos_state));
	copy->hdr_en = false;

	if (copy->block)
		drm_property_blob_get(copy->block);

	if (copy->split)
		drm_property_blob_get(copy->split);
	copy->need_scaler_pos = false;

	__drm_atomic_helper_plane_duplicate_state(plane, &copy->base);
	return &copy->base;
}

static void exynos_drm_plane_destroy_state(struct drm_plane *plane,
					   struct drm_plane_state *old_state)
{
	struct exynos_drm_plane_state *old_exynos_state =
					to_exynos_plane_state(old_state);

	drm_property_blob_put(old_exynos_state->block);
	drm_property_blob_put(old_exynos_state->split);

	__drm_atomic_helper_plane_destroy_state(old_state);
	kfree(old_exynos_state);
}

static void exynos_drm_plane_reset(struct drm_plane *plane)
{
	struct exynos_drm_plane *exynos_plane = to_exynos_plane(plane);
	struct exynos_drm_plane_state *exynos_state;

	if (plane->state) {
		exynos_drm_plane_destroy_state(plane, plane->state);
		plane->state = NULL;
	}

	exynos_state = kzalloc(sizeof(*exynos_state), GFP_KERNEL);
	if (exynos_state) {
		plane->state = &exynos_state->base;
		plane->state->plane = plane;
		plane->state->zpos = exynos_plane->index;
		plane->state->normalized_zpos = exynos_plane->index;
		plane->state->alpha = DRM_BLEND_ALPHA_OPAQUE;
		plane->state->pixel_blend_mode = DRM_MODE_BLEND_PREMULTI;
	}
}

static int exynos_drm_plane_set_property(struct drm_plane *plane,
				   struct drm_plane_state *state,
				   struct drm_property *property,
				   uint64_t val)
{
	const struct exynos_drm_properties *p = dev_get_exynos_props(plane->dev);
	struct exynos_drm_plane_state *exynos_state = to_exynos_plane_state(state);

	if (property == p->standard) {
		exynos_state->standard = val;
	} else if (property == p->transfer) {
		exynos_state->transfer = val;
	} else if (property == p->range) {
		exynos_state->range = val;
	} else if (property == p->colormap) {
		exynos_state->colormap = val;
	} else if (property == p->split) {
		exynos_drm_replace_property_blob_from_id(
			state->plane->dev, &exynos_state->split, val,
			sizeof(struct exynos_split));
	} else if (property == p->hdr_fd) {
		exynos_state->hdr_fd = U642I64(val);
	} else if (property == p->block) {
		exynos_drm_replace_property_blob_from_id(
			state->plane->dev, &exynos_state->block, val,
			sizeof(struct exynos_block_rect));
	} else {
		return -EINVAL;
	}

	return 0;
}

static int exynos_drm_plane_get_property(struct drm_plane *plane,
				   const struct drm_plane_state *state,
				   struct drm_property *property,
				   uint64_t *val)
{
	const struct exynos_drm_properties *p = dev_get_exynos_props(plane->dev);
	const struct exynos_drm_plane_state *exynos_state = to_exynos_plane_state(state);

	if (property == p->standard)
		*val = exynos_state->standard;
	else if (property == p->transfer)
		*val = exynos_state->transfer;
	else if (property == p->range)
		*val = exynos_state->range;
	else if (property == p->colormap)
		*val = exynos_state->colormap;
	else if (property == p->split)
		*val = (exynos_state->split) ? exynos_state->split->base.id : 0;
	else if (property == p->hdr_fd)
		*val = I642U64(exynos_state->hdr_fd);
	else if (property == p->block)
		*val = (exynos_state->block) ? exynos_state->block->base.id : 0;
	else
		return -EINVAL;

	return 0;
}

static void exynos_drm_plane_print_state(struct drm_printer *p,
					 const struct drm_plane_state *state)
{
	const struct exynos_drm_plane_state *exynos_state =
		to_exynos_plane_state(state);
	const struct exynos_drm_plane *exynos_plane =
		to_exynos_plane(state->plane);

	drm_printf(p, "\talpha: 0x%x\n", state->alpha);
	drm_printf(p, "\tblend_mode: 0x%x\n", state->pixel_blend_mode);
	if (exynos_state->split) {
		struct exynos_split *split = (struct exynos_split *)exynos_state->split->data;
		struct exynos_original_size *orig_size = &split->orig_size;
		drm_printf(p, "\tsplit: 0x%x\n", split->position);
		drm_printf(p, "\toriginal_size: %u %u %u %u\n", orig_size->src_w,
				orig_size->src_h, orig_size->dst_w, orig_size->dst_h);
	}
	drm_printf(p, "\tstandard: %d\n", exynos_state->standard);
	drm_printf(p, "\ttransfer: %d\n", exynos_state->transfer);
	drm_printf(p, "\trange: %d\n", exynos_state->range);
	drm_printf(p, "\thdr_fd: %lld\n", exynos_state->hdr_fd);
	if (exynos_plane->is_win_connected)
		drm_printf(p, "\t\twin_id=%d\n", exynos_plane->win_id);

	if (exynos_plane->ops->atomic_print_state)
		exynos_plane->ops->atomic_print_state(p, exynos_plane);

	if (exynos_state->block) {
		struct exynos_block_rect *block =
			(struct exynos_block_rect *)exynos_state->block->data;
		drm_printf(p, "\tblock: %d %d %d %d\n", block->x, block->y,
			   block->w, block->h);
	}

	if (exynos_plane->is_rcd)
		drm_printf(p, "\tdedicated for decoration layer\n");
}

static bool
exynos_drm_plane_format_mode_supported(struct drm_plane *plane, uint32_t format,
				     uint64_t modifier)
{
	int i;
	const struct dpu_fmt *fmt = dpu_find_fmt_info(format);

	if (!fmt)
		return false;

	if (!plane->modifier_count || !modifier)
		return true;

	for (i = 0; i < plane->modifier_count; i++)
		if (has_all_bits(plane->modifiers[i], modifier)) break;

	if (i == plane->modifier_count) {
		DRM_ERROR("no modifiers supported(0x%llx)\n", modifier);
		return false;
	}

	if (has_all_bits(DRM_FORMAT_MOD_SAMSUNG_COLORMAP, modifier) &&
			format == DRM_FORMAT_BGRA8888)
		return true;

	/* allow rest of the modifiers to support content protection */
	modifier &= ~DRM_FORMAT_MOD_PROTECTION;
	if (!modifier)
		return true;

	if (has_all_bits(DRM_FORMAT_MOD_ARM_AFBC(0), modifier))
		if (BIT(FMT_COMP_AFBC) & fmt->comp_mask)
				return true;

	if (has_all_bits(DRM_FORMAT_MOD_SAMSUNG_SAJC(0, 0), modifier))
		if (BIT(FMT_COMP_SAJC) & fmt->comp_mask)
				return true;

	if (has_all_bits(DRM_FORMAT_MOD_SAMSUNG_SBWC(0, 0, 0), modifier))
		if (BIT(FMT_COMP_SBWC) & fmt->comp_mask)
				return true;

	if (has_all_bits(DRM_FORMAT_MOD_SAMSUNG_VOTF(0), modifier))
		return true;

	/* If need, check whether to valid the combination of modifier & format */

	return false;
}

static struct drm_plane_funcs exynos_plane_funcs = {
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.reset		= exynos_drm_plane_reset,
	.atomic_duplicate_state = exynos_drm_plane_duplicate_state,
	.atomic_destroy_state = exynos_drm_plane_destroy_state,
	.atomic_set_property = exynos_drm_plane_set_property,
	.atomic_get_property = exynos_drm_plane_get_property,
	.atomic_print_state = exynos_drm_plane_print_state,
	.format_mod_supported = exynos_drm_plane_format_mode_supported,
};

static void exynos_dual_blender_reconfig_coords(struct drm_plane_state *plane_state,
						int half_width)
{
	struct exynos_drm_plane_state *exynos_plane_state =
					to_exynos_plane_state(plane_state);

	if (plane_state->dst.x1 < half_width)
		return;

	drm_rect_translate(&plane_state->dst, -half_width, 0);
	exynos_plane_state->need_scaler_pos = true;
}

static int exynos_plane_atomic_check(struct drm_plane *plane,
				     struct drm_atomic_state *state)
{
	struct drm_plane_state *new_plane_state =
				drm_atomic_get_new_plane_state(state, plane);
	struct exynos_drm_plane *exynos_plane = to_exynos_plane(plane);
	struct drm_crtc_state *new_crtc_state;
	struct exynos_drm_crtc_state *new_exynos_crtc_state;
	struct exynos_drm_crtc *exynos_crtc;
	int ret = 0;

	DRM_DEBUG("%s +\n", __func__);

	if (!new_plane_state->crtc || !new_plane_state->fb)
		return 0;

	new_crtc_state = drm_atomic_get_new_crtc_state(state, new_plane_state->crtc);

	new_exynos_crtc_state = to_exynos_crtc_state(new_crtc_state);
	if (!new_crtc_state->planes_changed || !new_crtc_state->active ||
			new_exynos_crtc_state->modeset_only)
		return 0;

	ret = drm_atomic_helper_check_plane_state(new_plane_state, new_crtc_state, 0,
			INT_MAX, true, false);
	if (ret)
		return ret;

	new_exynos_crtc_state = to_exynos_crtc_state(new_crtc_state);
	exynos_crtc = to_exynos_crtc(new_plane_state->crtc);
	if (exynos_crtc->partial && new_exynos_crtc_state->needs_reconfigure)
		exynos_partial_reconfig_coords(exynos_crtc->partial, new_plane_state,
				&new_exynos_crtc_state->partial_region);

	if (is_dual_blender_by_mode(&new_crtc_state->adjusted_mode))
		exynos_dual_blender_reconfig_coords(new_plane_state,
				new_crtc_state->adjusted_mode.hdisplay / 2);

	if (exynos_plane->ops->atomic_check && new_plane_state->visible) {
		ret = exynos_plane->ops->atomic_check(exynos_plane, state);
		if (ret)
			return ret;
	}

	DRM_DEBUG("%s -\n", __func__);

	return ret;
}

static void exynos_plane_disable(struct drm_plane *plane, struct drm_crtc *crtc)
{
	struct exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);
	struct exynos_drm_plane *exynos_plane = to_exynos_plane(plane);

	if (exynos_crtc->ops->disable_plane)
		exynos_crtc->ops->disable_plane(exynos_crtc, exynos_plane);
}

static void exynos_plane_atomic_update(struct drm_plane *plane,
				       struct drm_atomic_state *old_state)
{
	struct drm_plane_state *new_plane_state =
			drm_atomic_get_new_plane_state(old_state, plane);
	struct drm_crtc_state *crtc_state;
	struct exynos_drm_crtc_state *new_exynos_crtc_state;
	struct exynos_drm_crtc *exynos_crtc;
	struct exynos_drm_plane *exynos_plane = to_exynos_plane(plane);

	if (!new_plane_state->crtc)
		return;

	exynos_crtc = to_exynos_crtc(new_plane_state->crtc);
	crtc_state = drm_atomic_get_new_crtc_state(old_state, &exynos_crtc->base);
	new_exynos_crtc_state = to_exynos_crtc_state(crtc_state);
	if (new_exynos_crtc_state->skip_update)
		return;

	if (!new_plane_state->visible)
		exynos_plane_disable(plane, new_plane_state->crtc);
	else if (exynos_crtc->ops->update_plane)
		exynos_crtc->ops->update_plane(exynos_crtc, exynos_plane, old_state);
}

static void exynos_plane_atomic_disable(struct drm_plane *plane,
					struct drm_atomic_state *old_state)
{
	struct drm_crtc *crtc;
	struct drm_plane_state *old_plane_state =
			drm_atomic_get_old_plane_state(old_state, plane);
	struct drm_plane_state *new_plane_state =
			drm_atomic_get_new_plane_state(old_state, plane);

	crtc = old_plane_state ? old_plane_state->crtc : new_plane_state->crtc;
	if (!crtc)
		return;

	exynos_plane_disable(plane, crtc);
}

static const struct drm_plane_helper_funcs plane_helper_funcs = {
	.atomic_check = exynos_plane_atomic_check,
	.atomic_update = exynos_plane_atomic_update,
	.atomic_disable = exynos_plane_atomic_disable,
};

static int exynos_drm_plane_attach_restrictions_property(struct drm_device *drm_dev,
							 struct drm_mode_object *obj,
							 const struct dpp_restrict *res)
{
	struct drm_property_blob *blob;
	struct exynos_drm_properties *p = dev_get_exynos_props(drm_dev);
	size_t size = SZ_2K;
	char *blob_data, *ptr;

	blob_data = kzalloc(size, GFP_KERNEL);
	if (!blob_data)
		return -ENOMEM;

	ptr = blob_data;
	dpu_res_add_u32(&ptr, &size, DPU_RES_ID, &res->id);
	dpu_res_add_u32(&ptr, &size, DPU_RES_PORT, &res->port);
	dpu_res_add_u32(&ptr, &size, DPU_RES_DPUF_ID, &res->dpuf_id);
	dpu_res_add_u64(&ptr, &size, DPU_RES_ATTR, &res->attr);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_F_W, &res->src_f_w);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_F_H, &res->src_f_h);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_W, &res->src_w);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_H, &res->src_h);
	dpu_res_add_u32(&ptr, &size, DPU_RES_SRC_X_ALIGN, &res->src_x_align);
	dpu_res_add_u32(&ptr, &size, DPU_RES_SRC_Y_ALIGN, &res->src_y_align);

	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_RGB_COMP_F_W, &res->src_rgb_comp_f_w);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_RGB_COMP_W, &res->src_rgb_comp_w);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_RGB_COMP_F_H, &res->src_rgb_comp_f_h);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_SRC_RGB_COMP_H, &res->src_rgb_comp_h);

	dpu_res_add_u32_range(&ptr, &size, DPU_RES_DST_F_W, &res->dst_f_w);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_DST_F_H, &res->dst_f_h);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_DST_W, &res->dst_w);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_DST_H, &res->dst_h);
	dpu_res_add_u32(&ptr, &size, DPU_RES_DST_X_ALIGN, &res->dst_x_align);
	dpu_res_add_u32(&ptr, &size, DPU_RES_DST_Y_ALIGN, &res->dst_y_align);

	dpu_res_add_u32_range(&ptr, &size, DPU_RES_BLK_W, &res->blk_w);
	dpu_res_add_u32_range(&ptr, &size, DPU_RES_BLK_H, &res->blk_h);
	dpu_res_add_u32(&ptr, &size, DPU_RES_BLK_X_ALIGN, &res->blk_x_align);
	dpu_res_add_u32(&ptr, &size, DPU_RES_BLK_Y_ALIGN, &res->blk_y_align);

	dpu_res_add_u32(&ptr, &size, DPU_RES_SRC_W_ROT_MAX, &res->src_w_rot_max);
	dpu_res_add_u32(&ptr, &size, DPU_RES_SRC_H_ROT_MAX, &res->src_h_rot_max);

	dpu_res_add_u32(&ptr, &size, DPU_RES_SCALE_DOWN, &res->scale_down);
	dpu_res_add_u32(&ptr, &size, DPU_RES_SCALE_UP, &res->scale_up);

	blob = drm_property_create_blob(drm_dev, SZ_2K - size, blob_data);
	if (IS_ERR(blob))
		return PTR_ERR(blob);

	drm_object_attach_property(obj, p->restrictions, blob->base.id);

	kfree(blob_data);

	return 0;
}

int exynos_drm_plane_create_properties(struct drm_device *drm_dev)
{
	struct exynos_drm_properties *p;

	p = dev_get_exynos_props(drm_dev);
	if (!p)
		return -EINVAL;

	p->standard = drm_property_create_enum(drm_dev, 0, "standard",
				standard_list, ARRAY_SIZE(standard_list));
	if (!p->standard)
		return -ENOMEM;

	p->transfer = drm_property_create_enum(drm_dev, 0, "transfer",
				transfer_list, ARRAY_SIZE(transfer_list));
	if (!p->transfer)
		return -ENOMEM;

	p->range = drm_property_create_enum(drm_dev, 0, "range", range_list,
						ARRAY_SIZE(range_list));
	if (!p->range)
		return -ENOMEM;

	p->colormap = drm_property_create_range(drm_dev, 0, "colormap", 0, UINT_MAX);
	if (!p->colormap)
		return -ENOMEM;

	p->split = drm_property_create(drm_dev, DRM_MODE_PROP_BLOB, "split", 0);
	if (!p->split)
		return -ENOMEM;

	p->hdr_fd = drm_property_create_signed_range(drm_dev, 0, "HDR_FD", -1,
			1023);
	if (!p->hdr_fd)
		return -ENOMEM;

	p->block = drm_property_create(drm_dev, DRM_MODE_PROP_BLOB, "block", 0);
	if (!p->block)
		return -ENOMEM;

	return 0;
}

struct exynos_drm_plane *
exynos_drm_plane_create(struct drm_device *dev, unsigned int index,
		       const struct exynos_drm_plane_config *config,
		       const struct exynos_drm_plane_ops *ops)
{
	struct exynos_drm_plane *exynos_plane;
	struct exynos_drm_properties *p = dev_get_exynos_props(dev);
	struct drm_plane *plane;
	int ret;

	exynos_plane = drmm_universal_plane_alloc(dev, struct exynos_drm_plane,
				base, 0, &exynos_plane_funcs,
				config->pixel_formats,
				config->num_pixel_formats,
				config->modifiers, config->type,
				"exynos-plane-%d", index);
	if (IS_ERR(exynos_plane)) {
		DRM_ERROR("failed to alloc exynos_plane(%d)\n", index);
		return exynos_plane;
	}

	plane = &exynos_plane->base;
	drm_plane_helper_add(plane, &plane_helper_funcs);

	exynos_plane->index = index;
	exynos_plane->ops = ops;
	exynos_plane->ctx = config->ctx;

	if (EXYNOS_DRM_PLANE_CAP_RCD & config->capabilities) {
		ret = drm_plane_create_zpos_immutable_property(
			plane, config->max_zpos);
		if (ret)
			return ERR_PTR(ret);

		drm_object_attach_property(&plane->base, p->block, 0);
	} else {
		ret = drm_plane_create_alpha_property(plane);
		if (ret)
			return ERR_PTR(ret);

		ret = drm_plane_create_blend_mode_property(plane,
				BIT(DRM_MODE_BLEND_PIXEL_NONE) |
				BIT(DRM_MODE_BLEND_PREMULTI) |
				BIT(DRM_MODE_BLEND_COVERAGE));
		if (ret)
			return ERR_PTR(ret);

		ret = drm_plane_create_zpos_property(plane, config->zpos, 0,
						     config->max_zpos);
		if (ret)
			return ERR_PTR(ret);

		drm_object_attach_property(&plane->base, p->standard,
					   EXYNOS_STANDARD_UNSPECIFIED);

		drm_object_attach_property(&plane->base, p->transfer,
					   EXYNOS_TRANSFER_UNSPECIFIED);

		drm_object_attach_property(&plane->base, p->range,
					   EXYNOS_RANGE_UNSPECIFIED);

		drm_object_attach_property(&plane->base, p->colormap, 0);
	}

	if (EXYNOS_DRM_PLANE_CAP_ROT & config->capabilities)
		ret = drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
				DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
				DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270 |
				DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y);
	else if (EXYNOS_DRM_PLANE_CAP_FLIP & config->capabilities)
		ret = drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
				DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
				DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y);
	if (ret)
		return ERR_PTR(ret);

	if (EXYNOS_DRM_PLANE_CAP_CSC & config->capabilities)
		drm_object_attach_property(&plane->base, p->split, 0);

	drm_object_attach_property(&plane->base, p->hdr_fd, -1);

	ret = exynos_drm_plane_attach_restrictions_property(dev, &plane->base,
			config->res);
	if (ret)
		return ERR_PTR(ret);

	return exynos_plane;
}
