/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"

static void _scrWifi_ddlistApList_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_ddlistaplist_extra_list_selected_default
	static lv_style_t style_scrwifi_ddlistaplist_extra_list_selected_default;
	lv_style_reset(&style_scrwifi_ddlistaplist_extra_list_selected_default);
	lv_style_set_radius(&style_scrwifi_ddlistaplist_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_scrwifi_ddlistaplist_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_scrwifi_ddlistaplist_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_scrwifi_ddlistaplist_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_ddlistaplist_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_scrwifi_ddlistaplist_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrwifi_ddlistaplist_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_scrwifi_ddlistaplist_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrwifi_ddlistaplist_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_ddlistaplist_extra_list_main_default
	static lv_style_t style_scrwifi_ddlistaplist_extra_list_main_default;
	lv_style_reset(&style_scrwifi_ddlistaplist_extra_list_main_default);
	lv_style_set_radius(&style_scrwifi_ddlistaplist_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_scrwifi_ddlistaplist_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrwifi_ddlistaplist_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrwifi_ddlistaplist_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_ddlistaplist_extra_list_main_default, 255);
	lv_style_set_border_color(&style_scrwifi_ddlistaplist_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrwifi_ddlistaplist_extra_list_main_default, 1);
	lv_style_set_text_color(&style_scrwifi_ddlistaplist_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_max_height(&style_scrwifi_ddlistaplist_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrwifi_ddlistaplist_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_ddlistaplist_extra_list_scrollbar_default
	static lv_style_t style_scrwifi_ddlistaplist_extra_list_scrollbar_default;
	lv_style_reset(&style_scrwifi_ddlistaplist_extra_list_scrollbar_default);
	lv_style_set_radius(&style_scrwifi_ddlistaplist_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_scrwifi_ddlistaplist_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_scrwifi_ddlistaplist_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrwifi_ddlistaplist_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_ddlistaplist_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_scrwifi_ddlistaplist_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}

void setup_scr_scrWifi(lv_ui *ui){

	//Write codes scrWifi
	ui->scrWifi = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_main_main_default
	static lv_style_t style_scrwifi_main_main_default;
	lv_style_reset(&style_scrwifi_main_main_default);
	lv_style_set_bg_color(&style_scrwifi_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_scrwifi_main_main_default, 255);
	lv_obj_add_style(ui->scrWifi, &style_scrwifi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrWifi_spangroupLog
	ui->scrWifi_spangroupLog = lv_spangroup_create(ui->scrWifi);
	lv_obj_set_pos(ui->scrWifi_spangroupLog, 10, 120);
	lv_obj_set_size(ui->scrWifi_spangroupLog, 220, 190);
	lv_spangroup_set_align(ui->scrWifi_spangroupLog, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->scrWifi_spangroupLog, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->scrWifi_spangroupLog, LV_SPAN_MODE_BREAK);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_spangrouplog_main_main_default
	static lv_style_t style_scrwifi_spangrouplog_main_main_default;
	lv_style_reset(&style_scrwifi_spangrouplog_main_main_default);
	lv_style_set_bg_color(&style_scrwifi_spangrouplog_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrwifi_spangrouplog_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrwifi_spangrouplog_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_spangrouplog_main_main_default, 0);
	lv_style_set_border_color(&style_scrwifi_spangrouplog_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_scrwifi_spangrouplog_main_main_default, 1);
	lv_style_set_pad_left(&style_scrwifi_spangrouplog_main_main_default, 2);
	lv_style_set_pad_right(&style_scrwifi_spangrouplog_main_main_default, 2);
	lv_style_set_pad_top(&style_scrwifi_spangrouplog_main_main_default, 2);
	lv_style_set_pad_bottom(&style_scrwifi_spangrouplog_main_main_default, 2);
	lv_obj_add_style(ui->scrWifi_spangroupLog, &style_scrwifi_spangrouplog_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//create spans
	lv_span_t *scrWifi_spangroupLog_span;

	//create a new span
	scrWifi_spangroupLog_span = lv_spangroup_new_span(ui->scrWifi_spangroupLog);
	lv_span_set_text(scrWifi_spangroupLog_span, "LOG");
	lv_style_set_text_color(&scrWifi_spangroupLog_span->style, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_decor(&scrWifi_spangroupLog_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&scrWifi_spangroupLog_span->style, &lv_font_FiraCode_Retina_14);
	lv_spangroup_refr_mode(ui->scrWifi_spangroupLog);

	//Write codes scrWifi_labelIp
	ui->scrWifi_labelIp = lv_label_create(ui->scrWifi);
	lv_obj_set_pos(ui->scrWifi_labelIp, 10, 45);
	lv_obj_set_size(ui->scrWifi_labelIp, 35, 14);
	lv_label_set_text(ui->scrWifi_labelIp, "IP:");
	lv_label_set_long_mode(ui->scrWifi_labelIp, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrWifi_labelIp, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_labelip_main_main_default
	static lv_style_t style_scrwifi_labelip_main_main_default;
	lv_style_reset(&style_scrwifi_labelip_main_main_default);
	lv_style_set_radius(&style_scrwifi_labelip_main_main_default, 0);
	lv_style_set_bg_color(&style_scrwifi_labelip_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrwifi_labelip_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrwifi_labelip_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_labelip_main_main_default, 0);
	lv_style_set_text_color(&style_scrwifi_labelip_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrwifi_labelip_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrwifi_labelip_main_main_default, 2);
	lv_style_set_pad_left(&style_scrwifi_labelip_main_main_default, 0);
	lv_style_set_pad_right(&style_scrwifi_labelip_main_main_default, 0);
	lv_style_set_pad_top(&style_scrwifi_labelip_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrwifi_labelip_main_main_default, 0);
	lv_obj_add_style(ui->scrWifi_labelIp, &style_scrwifi_labelip_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrWifi_labelIpValue
	ui->scrWifi_labelIpValue = lv_label_create(ui->scrWifi);
	lv_obj_set_pos(ui->scrWifi_labelIpValue, 45, 45);
	lv_obj_set_size(ui->scrWifi_labelIpValue, 185, 14);
	lv_label_set_text(ui->scrWifi_labelIpValue, "NULL");
	lv_label_set_long_mode(ui->scrWifi_labelIpValue, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrWifi_labelIpValue, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_labelipvalue_main_main_default
	static lv_style_t style_scrwifi_labelipvalue_main_main_default;
	lv_style_reset(&style_scrwifi_labelipvalue_main_main_default);
	lv_style_set_radius(&style_scrwifi_labelipvalue_main_main_default, 0);
	lv_style_set_bg_color(&style_scrwifi_labelipvalue_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrwifi_labelipvalue_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrwifi_labelipvalue_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_labelipvalue_main_main_default, 0);
	lv_style_set_text_color(&style_scrwifi_labelipvalue_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrwifi_labelipvalue_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrwifi_labelipvalue_main_main_default, 2);
	lv_style_set_pad_left(&style_scrwifi_labelipvalue_main_main_default, 0);
	lv_style_set_pad_right(&style_scrwifi_labelipvalue_main_main_default, 0);
	lv_style_set_pad_top(&style_scrwifi_labelipvalue_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrwifi_labelipvalue_main_main_default, 0);
	lv_obj_add_style(ui->scrWifi_labelIpValue, &style_scrwifi_labelipvalue_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrWifi_btnScanAp
	ui->scrWifi_btnScanAp = lv_btn_create(ui->scrWifi);
	lv_obj_set_pos(ui->scrWifi_btnScanAp, 10, 75);
	lv_obj_set_size(ui->scrWifi_btnScanAp, 220, 30);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_btnscanap_main_main_default
	static lv_style_t style_scrwifi_btnscanap_main_main_default;
	lv_style_reset(&style_scrwifi_btnscanap_main_main_default);
	lv_style_set_radius(&style_scrwifi_btnscanap_main_main_default, 15);
	lv_style_set_bg_color(&style_scrwifi_btnscanap_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_scrwifi_btnscanap_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_scrwifi_btnscanap_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_btnscanap_main_main_default, 255);
	lv_style_set_shadow_color(&style_scrwifi_btnscanap_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_scrwifi_btnscanap_main_main_default, 0);
	lv_style_set_border_color(&style_scrwifi_btnscanap_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_scrwifi_btnscanap_main_main_default, 1);
	lv_style_set_border_opa(&style_scrwifi_btnscanap_main_main_default, 255);
	lv_obj_add_style(ui->scrWifi_btnScanAp, &style_scrwifi_btnscanap_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->scrWifi_btnScanAp_label = lv_label_create(ui->scrWifi_btnScanAp);
	lv_label_set_text(ui->scrWifi_btnScanAp_label, "SCAN WIFI");
	lv_obj_set_style_text_color(ui->scrWifi_btnScanAp_label, lv_color_make(0xff, 0xff, 0xff), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->scrWifi_btnScanAp_label, &lv_font_FiraCode_Retina_14, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->scrWifi_btnScanAp, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->scrWifi_btnScanAp_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes scrWifi_ddlistApList
	ui->scrWifi_ddlistApList = lv_dropdown_create(ui->scrWifi);
	lv_obj_set_pos(ui->scrWifi_ddlistApList, 10, 10);
	lv_obj_set_width(ui->scrWifi_ddlistApList, 220);
	lv_dropdown_set_options(ui->scrWifi_ddlistApList, "");
	lv_obj_add_event_cb(ui->scrWifi_ddlistApList, _scrWifi_ddlistApList_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrwifi_ddlistaplist_main_main_default
	static lv_style_t style_scrwifi_ddlistaplist_main_main_default;
	lv_style_reset(&style_scrwifi_ddlistaplist_main_main_default);
	lv_style_set_radius(&style_scrwifi_ddlistaplist_main_main_default, 3);
	lv_style_set_bg_color(&style_scrwifi_ddlistaplist_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrwifi_ddlistaplist_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrwifi_ddlistaplist_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrwifi_ddlistaplist_main_main_default, 255);
	lv_style_set_border_color(&style_scrwifi_ddlistaplist_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrwifi_ddlistaplist_main_main_default, 1);
	lv_style_set_text_color(&style_scrwifi_ddlistaplist_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_line_space(&style_scrwifi_ddlistaplist_main_main_default, 20);
	lv_obj_add_style(ui->scrWifi_ddlistApList, &style_scrwifi_ddlistaplist_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}