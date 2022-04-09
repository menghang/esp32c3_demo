/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"

static void _scrProg_ddlistCfgFile_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistcfgfile_extra_list_selected_default
	static lv_style_t style_scrprog_ddlistcfgfile_extra_list_selected_default;
	lv_style_reset(&style_scrprog_ddlistcfgfile_extra_list_selected_default);
	lv_style_set_radius(&style_scrprog_ddlistcfgfile_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistcfgfile_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistcfgfile_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistcfgfile_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistcfgfile_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_scrprog_ddlistcfgfile_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrprog_ddlistcfgfile_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_scrprog_ddlistcfgfile_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrprog_ddlistcfgfile_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrprog_ddlistcfgfile_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistcfgfile_extra_list_main_default
	static lv_style_t style_scrprog_ddlistcfgfile_extra_list_main_default;
	lv_style_reset(&style_scrprog_ddlistcfgfile_extra_list_main_default);
	lv_style_set_radius(&style_scrprog_ddlistcfgfile_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistcfgfile_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistcfgfile_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistcfgfile_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistcfgfile_extra_list_main_default, 255);
	lv_style_set_border_color(&style_scrprog_ddlistcfgfile_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrprog_ddlistcfgfile_extra_list_main_default, 1);
	lv_style_set_text_color(&style_scrprog_ddlistcfgfile_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_scrprog_ddlistcfgfile_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_scrprog_ddlistcfgfile_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrprog_ddlistcfgfile_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistcfgfile_extra_list_scrollbar_default
	static lv_style_t style_scrprog_ddlistcfgfile_extra_list_scrollbar_default;
	lv_style_reset(&style_scrprog_ddlistcfgfile_extra_list_scrollbar_default);
	lv_style_set_radius(&style_scrprog_ddlistcfgfile_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistcfgfile_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistcfgfile_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistcfgfile_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistcfgfile_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrprog_ddlistcfgfile_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}
static void _scrProg_ddlistMtpFile_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistmtpfile_extra_list_selected_default
	static lv_style_t style_scrprog_ddlistmtpfile_extra_list_selected_default;
	lv_style_reset(&style_scrprog_ddlistmtpfile_extra_list_selected_default);
	lv_style_set_radius(&style_scrprog_ddlistmtpfile_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistmtpfile_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistmtpfile_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistmtpfile_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistmtpfile_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_scrprog_ddlistmtpfile_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrprog_ddlistmtpfile_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_scrprog_ddlistmtpfile_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrprog_ddlistmtpfile_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrprog_ddlistmtpfile_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistmtpfile_extra_list_main_default
	static lv_style_t style_scrprog_ddlistmtpfile_extra_list_main_default;
	lv_style_reset(&style_scrprog_ddlistmtpfile_extra_list_main_default);
	lv_style_set_radius(&style_scrprog_ddlistmtpfile_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistmtpfile_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistmtpfile_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistmtpfile_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistmtpfile_extra_list_main_default, 255);
	lv_style_set_border_color(&style_scrprog_ddlistmtpfile_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrprog_ddlistmtpfile_extra_list_main_default, 1);
	lv_style_set_text_color(&style_scrprog_ddlistmtpfile_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_scrprog_ddlistmtpfile_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_scrprog_ddlistmtpfile_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrprog_ddlistmtpfile_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistmtpfile_extra_list_scrollbar_default
	static lv_style_t style_scrprog_ddlistmtpfile_extra_list_scrollbar_default;
	lv_style_reset(&style_scrprog_ddlistmtpfile_extra_list_scrollbar_default);
	lv_style_set_radius(&style_scrprog_ddlistmtpfile_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistmtpfile_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistmtpfile_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistmtpfile_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistmtpfile_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrprog_ddlistmtpfile_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}

void setup_scr_scrProg(lv_ui *ui){

	//Write codes scrProg
	ui->scrProg = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_main_main_default
	static lv_style_t style_scrprog_main_main_default;
	lv_style_reset(&style_scrprog_main_main_default);
	lv_style_set_bg_color(&style_scrprog_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_scrprog_main_main_default, 255);
	lv_obj_add_style(ui->scrProg, &style_scrprog_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrProg_labelMtp
	ui->scrProg_labelMtp = lv_label_create(ui->scrProg);
	lv_obj_set_pos(ui->scrProg_labelMtp, 10, 18);
	lv_obj_set_size(ui->scrProg_labelMtp, 45, 14);
	lv_label_set_text(ui->scrProg_labelMtp, "MTP:");
	lv_label_set_long_mode(ui->scrProg_labelMtp, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->scrProg_labelMtp, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_labelmtp_main_main_default
	static lv_style_t style_scrprog_labelmtp_main_main_default;
	lv_style_reset(&style_scrprog_labelmtp_main_main_default);
	lv_style_set_radius(&style_scrprog_labelmtp_main_main_default, 0);
	lv_style_set_bg_color(&style_scrprog_labelmtp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrprog_labelmtp_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrprog_labelmtp_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_labelmtp_main_main_default, 0);
	lv_style_set_text_color(&style_scrprog_labelmtp_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrprog_labelmtp_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrprog_labelmtp_main_main_default, 2);
	lv_style_set_pad_left(&style_scrprog_labelmtp_main_main_default, 0);
	lv_style_set_pad_right(&style_scrprog_labelmtp_main_main_default, 0);
	lv_style_set_pad_top(&style_scrprog_labelmtp_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrprog_labelmtp_main_main_default, 0);
	lv_obj_add_style(ui->scrProg_labelMtp, &style_scrprog_labelmtp_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrProg_labelCfg
	ui->scrProg_labelCfg = lv_label_create(ui->scrProg);
	lv_obj_set_pos(ui->scrProg_labelCfg, 10, 58);
	lv_obj_set_size(ui->scrProg_labelCfg, 45, 14);
	lv_label_set_text(ui->scrProg_labelCfg, "CFG:");
	lv_label_set_long_mode(ui->scrProg_labelCfg, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->scrProg_labelCfg, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_labelcfg_main_main_default
	static lv_style_t style_scrprog_labelcfg_main_main_default;
	lv_style_reset(&style_scrprog_labelcfg_main_main_default);
	lv_style_set_radius(&style_scrprog_labelcfg_main_main_default, 0);
	lv_style_set_bg_color(&style_scrprog_labelcfg_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrprog_labelcfg_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrprog_labelcfg_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_labelcfg_main_main_default, 0);
	lv_style_set_text_color(&style_scrprog_labelcfg_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrprog_labelcfg_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrprog_labelcfg_main_main_default, 2);
	lv_style_set_pad_left(&style_scrprog_labelcfg_main_main_default, 0);
	lv_style_set_pad_right(&style_scrprog_labelcfg_main_main_default, 0);
	lv_style_set_pad_top(&style_scrprog_labelcfg_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrprog_labelcfg_main_main_default, 0);
	lv_obj_add_style(ui->scrProg_labelCfg, &style_scrprog_labelcfg_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrProg_btnStart
	ui->scrProg_btnStart = lv_btn_create(ui->scrProg);
	lv_obj_set_pos(ui->scrProg_btnStart, 10, 90);
	lv_obj_set_size(ui->scrProg_btnStart, 220, 30);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_btnstart_main_main_default
	static lv_style_t style_scrprog_btnstart_main_main_default;
	lv_style_reset(&style_scrprog_btnstart_main_main_default);
	lv_style_set_radius(&style_scrprog_btnstart_main_main_default, 15);
	lv_style_set_bg_color(&style_scrprog_btnstart_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_scrprog_btnstart_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_scrprog_btnstart_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_btnstart_main_main_default, 255);
	lv_style_set_shadow_color(&style_scrprog_btnstart_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_scrprog_btnstart_main_main_default, 0);
	lv_style_set_border_color(&style_scrprog_btnstart_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_scrprog_btnstart_main_main_default, 1);
	lv_style_set_border_opa(&style_scrprog_btnstart_main_main_default, 255);
	lv_obj_add_style(ui->scrProg_btnStart, &style_scrprog_btnstart_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->scrProg_btnStart_label = lv_label_create(ui->scrProg_btnStart);
	lv_label_set_text(ui->scrProg_btnStart_label, "START");
	lv_obj_set_style_text_color(ui->scrProg_btnStart_label, lv_color_make(0xff, 0xff, 0xff), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrProg_btnStart_label, &lv_font_FiraCode_Retina_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->scrProg_btnStart, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->scrProg_btnStart_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes scrProg_spangroupLog
	ui->scrProg_spangroupLog = lv_spangroup_create(ui->scrProg);
	lv_obj_set_pos(ui->scrProg_spangroupLog, 10, 135);
	lv_obj_set_size(ui->scrProg_spangroupLog, 220, 135);
	lv_spangroup_set_align(ui->scrProg_spangroupLog, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->scrProg_spangroupLog, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->scrProg_spangroupLog, LV_SPAN_MODE_FIXED);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_spangrouplog_main_main_default
	static lv_style_t style_scrprog_spangrouplog_main_main_default;
	lv_style_reset(&style_scrprog_spangrouplog_main_main_default);
	lv_style_set_bg_color(&style_scrprog_spangrouplog_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrprog_spangrouplog_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrprog_spangrouplog_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_spangrouplog_main_main_default, 0);
	lv_style_set_border_color(&style_scrprog_spangrouplog_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_scrprog_spangrouplog_main_main_default, 1);
	lv_style_set_pad_left(&style_scrprog_spangrouplog_main_main_default, 2);
	lv_style_set_pad_right(&style_scrprog_spangrouplog_main_main_default, 2);
	lv_style_set_pad_top(&style_scrprog_spangrouplog_main_main_default, 2);
	lv_style_set_pad_bottom(&style_scrprog_spangrouplog_main_main_default, 2);
	lv_obj_add_style(ui->scrProg_spangroupLog, &style_scrprog_spangrouplog_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//create spans
	lv_span_t *scrProg_spangroupLog_span;

	//create a new span
	scrProg_spangroupLog_span = lv_spangroup_new_span(ui->scrProg_spangroupLog);
	lv_span_set_text(scrProg_spangroupLog_span, "LOG");
	lv_style_set_text_color(&scrProg_spangroupLog_span->style, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_decor(&scrProg_spangroupLog_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&scrProg_spangroupLog_span->style, &lv_font_FiraCode_Retina_14);

	//Write codes scrProg_barProgress
	ui->scrProg_barProgress = lv_bar_create(ui->scrProg);
	lv_obj_set_pos(ui->scrProg_barProgress, 10, 280);
	lv_obj_set_size(ui->scrProg_barProgress, 220, 30);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_barprogress_main_main_default
	static lv_style_t style_scrprog_barprogress_main_main_default;
	lv_style_reset(&style_scrprog_barprogress_main_main_default);
	lv_style_set_radius(&style_scrprog_barprogress_main_main_default, 15);
	lv_style_set_bg_color(&style_scrprog_barprogress_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrprog_barprogress_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrprog_barprogress_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_barprogress_main_main_default, 82);
	lv_style_set_pad_left(&style_scrprog_barprogress_main_main_default, 0);
	lv_style_set_pad_right(&style_scrprog_barprogress_main_main_default, 0);
	lv_style_set_pad_top(&style_scrprog_barprogress_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrprog_barprogress_main_main_default, 0);
	lv_obj_add_style(ui->scrProg_barProgress, &style_scrprog_barprogress_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_barprogress_main_indicator_default
	static lv_style_t style_scrprog_barprogress_main_indicator_default;
	lv_style_reset(&style_scrprog_barprogress_main_indicator_default);
	lv_style_set_radius(&style_scrprog_barprogress_main_indicator_default, 10);
	lv_style_set_bg_color(&style_scrprog_barprogress_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrprog_barprogress_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrprog_barprogress_main_indicator_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_barprogress_main_indicator_default, 255);
	lv_obj_add_style(ui->scrProg_barProgress, &style_scrprog_barprogress_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->scrProg_barProgress, 1000, 0);
	lv_bar_set_mode(ui->scrProg_barProgress, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->scrProg_barProgress, 50, LV_ANIM_OFF);

	//Write codes scrProg_ddlistCfgFile
	ui->scrProg_ddlistCfgFile = lv_dropdown_create(ui->scrProg);
	lv_obj_set_pos(ui->scrProg_ddlistCfgFile, 55, 50);
	lv_obj_set_width(ui->scrProg_ddlistCfgFile, 175);
	lv_dropdown_set_options(ui->scrProg_ddlistCfgFile, "NULL");
	lv_obj_add_event_cb(ui->scrProg_ddlistCfgFile, _scrProg_ddlistCfgFile_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistcfgfile_main_main_default
	static lv_style_t style_scrprog_ddlistcfgfile_main_main_default;
	lv_style_reset(&style_scrprog_ddlistcfgfile_main_main_default);
	lv_style_set_radius(&style_scrprog_ddlistcfgfile_main_main_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistcfgfile_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistcfgfile_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistcfgfile_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistcfgfile_main_main_default, 255);
	lv_style_set_border_color(&style_scrprog_ddlistcfgfile_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_scrprog_ddlistcfgfile_main_main_default, 2);
	lv_style_set_text_color(&style_scrprog_ddlistcfgfile_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_scrprog_ddlistcfgfile_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_line_space(&style_scrprog_ddlistcfgfile_main_main_default, 20);
	lv_obj_add_style(ui->scrProg_ddlistCfgFile, &style_scrprog_ddlistcfgfile_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrProg_ddlistMtpFile
	ui->scrProg_ddlistMtpFile = lv_dropdown_create(ui->scrProg);
	lv_obj_set_pos(ui->scrProg_ddlistMtpFile, 55, 10);
	lv_obj_set_width(ui->scrProg_ddlistMtpFile, 175);
	lv_dropdown_set_options(ui->scrProg_ddlistMtpFile, "NULL");
	lv_obj_add_event_cb(ui->scrProg_ddlistMtpFile, _scrProg_ddlistMtpFile_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrprog_ddlistmtpfile_main_main_default
	static lv_style_t style_scrprog_ddlistmtpfile_main_main_default;
	lv_style_reset(&style_scrprog_ddlistmtpfile_main_main_default);
	lv_style_set_radius(&style_scrprog_ddlistmtpfile_main_main_default, 3);
	lv_style_set_bg_color(&style_scrprog_ddlistmtpfile_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrprog_ddlistmtpfile_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrprog_ddlistmtpfile_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrprog_ddlistmtpfile_main_main_default, 255);
	lv_style_set_border_color(&style_scrprog_ddlistmtpfile_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_scrprog_ddlistmtpfile_main_main_default, 2);
	lv_style_set_text_color(&style_scrprog_ddlistmtpfile_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_scrprog_ddlistmtpfile_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_line_space(&style_scrprog_ddlistmtpfile_main_main_default, 20);
	lv_obj_add_style(ui->scrProg_ddlistMtpFile, &style_scrprog_ddlistmtpfile_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}