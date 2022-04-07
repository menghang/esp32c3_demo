/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_scrModeSelect(lv_ui *ui){

	//Write codes scrModeSelect
	ui->scrModeSelect = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_main_main_default
	static lv_style_t style_scrmodeselect_main_main_default;
	lv_style_reset(&style_scrmodeselect_main_main_default);
	lv_style_set_bg_color(&style_scrmodeselect_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_scrmodeselect_main_main_default, 255);
	lv_obj_add_style(ui->scrModeSelect, &style_scrmodeselect_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrModeSelect_labelTitle
	ui->scrModeSelect_labelTitle = lv_label_create(ui->scrModeSelect);
	lv_obj_set_pos(ui->scrModeSelect_labelTitle, 0, 52);
	lv_obj_set_size(ui->scrModeSelect_labelTitle, 240, 24);
	lv_label_set_text(ui->scrModeSelect_labelTitle, "Mode List");
	lv_label_set_long_mode(ui->scrModeSelect_labelTitle, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->scrModeSelect_labelTitle, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_labeltitle_main_main_default
	static lv_style_t style_scrmodeselect_labeltitle_main_main_default;
	lv_style_reset(&style_scrmodeselect_labeltitle_main_main_default);
	lv_style_set_radius(&style_scrmodeselect_labeltitle_main_main_default, 0);
	lv_style_set_bg_color(&style_scrmodeselect_labeltitle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrmodeselect_labeltitle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrmodeselect_labeltitle_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrmodeselect_labeltitle_main_main_default, 0);
	lv_style_set_text_color(&style_scrmodeselect_labeltitle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrmodeselect_labeltitle_main_main_default, &lv_font_FiraCode_Retina_24);
	lv_style_set_text_letter_space(&style_scrmodeselect_labeltitle_main_main_default, 2);
	lv_style_set_pad_left(&style_scrmodeselect_labeltitle_main_main_default, 0);
	lv_style_set_pad_right(&style_scrmodeselect_labeltitle_main_main_default, 0);
	lv_style_set_pad_top(&style_scrmodeselect_labeltitle_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrmodeselect_labeltitle_main_main_default, 0);
	lv_obj_add_style(ui->scrModeSelect_labelTitle, &style_scrmodeselect_labeltitle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrModeSelect_labelProgMode
	ui->scrModeSelect_labelProgMode = lv_label_create(ui->scrModeSelect);
	lv_obj_set_pos(ui->scrModeSelect_labelProgMode, 0, 97);
	lv_obj_set_size(ui->scrModeSelect_labelProgMode, 240, 14);
	lv_label_set_text(ui->scrModeSelect_labelProgMode, "NU1708 Programmer");
	lv_label_set_long_mode(ui->scrModeSelect_labelProgMode, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->scrModeSelect_labelProgMode, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_labelprogmode_main_main_default
	static lv_style_t style_scrmodeselect_labelprogmode_main_main_default;
	lv_style_reset(&style_scrmodeselect_labelprogmode_main_main_default);
	lv_style_set_radius(&style_scrmodeselect_labelprogmode_main_main_default, 0);
	lv_style_set_bg_color(&style_scrmodeselect_labelprogmode_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrmodeselect_labelprogmode_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrmodeselect_labelprogmode_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrmodeselect_labelprogmode_main_main_default, 0);
	lv_style_set_text_color(&style_scrmodeselect_labelprogmode_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrmodeselect_labelprogmode_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrmodeselect_labelprogmode_main_main_default, 2);
	lv_style_set_pad_left(&style_scrmodeselect_labelprogmode_main_main_default, 0);
	lv_style_set_pad_right(&style_scrmodeselect_labelprogmode_main_main_default, 0);
	lv_style_set_pad_top(&style_scrmodeselect_labelprogmode_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrmodeselect_labelprogmode_main_main_default, 0);
	lv_obj_add_style(ui->scrModeSelect_labelProgMode, &style_scrmodeselect_labelprogmode_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrModeSelect_labelWifiConnect
	ui->scrModeSelect_labelWifiConnect = lv_label_create(ui->scrModeSelect);
	lv_obj_set_pos(ui->scrModeSelect_labelWifiConnect, 0, 129);
	lv_obj_set_size(ui->scrModeSelect_labelWifiConnect, 240, 14);
	lv_label_set_text(ui->scrModeSelect_labelWifiConnect, "WiFi Connection");
	lv_label_set_long_mode(ui->scrModeSelect_labelWifiConnect, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->scrModeSelect_labelWifiConnect, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_labelwificonnect_main_main_default
	static lv_style_t style_scrmodeselect_labelwificonnect_main_main_default;
	lv_style_reset(&style_scrmodeselect_labelwificonnect_main_main_default);
	lv_style_set_radius(&style_scrmodeselect_labelwificonnect_main_main_default, 0);
	lv_style_set_bg_color(&style_scrmodeselect_labelwificonnect_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrmodeselect_labelwificonnect_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrmodeselect_labelwificonnect_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrmodeselect_labelwificonnect_main_main_default, 0);
	lv_style_set_text_color(&style_scrmodeselect_labelwificonnect_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrmodeselect_labelwificonnect_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrmodeselect_labelwificonnect_main_main_default, 2);
	lv_style_set_pad_left(&style_scrmodeselect_labelwificonnect_main_main_default, 0);
	lv_style_set_pad_right(&style_scrmodeselect_labelwificonnect_main_main_default, 0);
	lv_style_set_pad_top(&style_scrmodeselect_labelwificonnect_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrmodeselect_labelwificonnect_main_main_default, 0);
	lv_obj_add_style(ui->scrModeSelect_labelWifiConnect, &style_scrmodeselect_labelwificonnect_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrModeSelect_labelPowerMeter
	ui->scrModeSelect_labelPowerMeter = lv_label_create(ui->scrModeSelect);
	lv_obj_set_pos(ui->scrModeSelect_labelPowerMeter, 0, 161);
	lv_obj_set_size(ui->scrModeSelect_labelPowerMeter, 240, 14);
	lv_label_set_text(ui->scrModeSelect_labelPowerMeter, "Power Meter");
	lv_label_set_long_mode(ui->scrModeSelect_labelPowerMeter, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->scrModeSelect_labelPowerMeter, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_labelpowermeter_main_main_default
	static lv_style_t style_scrmodeselect_labelpowermeter_main_main_default;
	lv_style_reset(&style_scrmodeselect_labelpowermeter_main_main_default);
	lv_style_set_radius(&style_scrmodeselect_labelpowermeter_main_main_default, 0);
	lv_style_set_bg_color(&style_scrmodeselect_labelpowermeter_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrmodeselect_labelpowermeter_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrmodeselect_labelpowermeter_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrmodeselect_labelpowermeter_main_main_default, 0);
	lv_style_set_text_color(&style_scrmodeselect_labelpowermeter_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_scrmodeselect_labelpowermeter_main_main_default, &lv_font_FiraCode_Retina_14);
	lv_style_set_text_letter_space(&style_scrmodeselect_labelpowermeter_main_main_default, 2);
	lv_style_set_pad_left(&style_scrmodeselect_labelpowermeter_main_main_default, 0);
	lv_style_set_pad_right(&style_scrmodeselect_labelpowermeter_main_main_default, 0);
	lv_style_set_pad_top(&style_scrmodeselect_labelpowermeter_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrmodeselect_labelpowermeter_main_main_default, 0);
	lv_obj_add_style(ui->scrModeSelect_labelPowerMeter, &style_scrmodeselect_labelpowermeter_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}