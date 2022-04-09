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
	lv_style_set_bg_color(&style_scrmodeselect_main_main_default, lv_color_make(0x80, 0x80, 0x80));
	lv_style_set_bg_opa(&style_scrmodeselect_main_main_default, 255);
	lv_obj_add_style(ui->scrModeSelect, &style_scrmodeselect_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrModeSelect_listMode
	ui->scrModeSelect_listMode = lv_list_create(ui->scrModeSelect);
	lv_obj_set_pos(ui->scrModeSelect_listMode, 20, 20);
	lv_obj_set_size(ui->scrModeSelect_listMode, 200, 280);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_listmode_main_main_default
	static lv_style_t style_scrmodeselect_listmode_main_main_default;
	lv_style_reset(&style_scrmodeselect_listmode_main_main_default);
	lv_style_set_radius(&style_scrmodeselect_listmode_main_main_default, 5);
	lv_style_set_bg_color(&style_scrmodeselect_listmode_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrmodeselect_listmode_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrmodeselect_listmode_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrmodeselect_listmode_main_main_default, 255);
	lv_style_set_border_color(&style_scrmodeselect_listmode_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_scrmodeselect_listmode_main_main_default, 1);
	lv_style_set_pad_left(&style_scrmodeselect_listmode_main_main_default, 5);
	lv_style_set_pad_right(&style_scrmodeselect_listmode_main_main_default, 5);
	lv_style_set_pad_top(&style_scrmodeselect_listmode_main_main_default, 5);
	lv_obj_add_style(ui->scrModeSelect_listMode, &style_scrmodeselect_listmode_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_listmode_main_scrollbar_default
	static lv_style_t style_scrmodeselect_listmode_main_scrollbar_default;
	lv_style_reset(&style_scrmodeselect_listmode_main_scrollbar_default);
	lv_style_set_radius(&style_scrmodeselect_listmode_main_scrollbar_default, 5);
	lv_style_set_bg_color(&style_scrmodeselect_listmode_main_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrmodeselect_listmode_main_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrmodeselect_listmode_main_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrmodeselect_listmode_main_scrollbar_default, 255);
	lv_obj_add_style(ui->scrModeSelect_listMode, &style_scrmodeselect_listmode_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_scrmodeselect_listmode_extra_btns_main_default
	static lv_style_t style_scrmodeselect_listmode_extra_btns_main_default;
	lv_style_reset(&style_scrmodeselect_listmode_extra_btns_main_default);
	lv_style_set_radius(&style_scrmodeselect_listmode_extra_btns_main_default, 5);
	lv_style_set_bg_color(&style_scrmodeselect_listmode_extra_btns_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_scrmodeselect_listmode_extra_btns_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_scrmodeselect_listmode_extra_btns_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrmodeselect_listmode_extra_btns_main_default, 255);
	lv_style_set_text_color(&style_scrmodeselect_listmode_extra_btns_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_scrmodeselect_listmode_extra_btns_main_default, &lv_font_FiraCode_Retina_18);
	lv_obj_t *scrModeSelect_listMode_btn;
	scrModeSelect_listMode_btn = lv_list_add_btn(ui->scrModeSelect_listMode, LV_SYMBOL_SETTINGS, "WIFI");
	ui->scrModeSelect_listMode_item0 = scrModeSelect_listMode_btn;
	lv_obj_add_style(scrModeSelect_listMode_btn, &style_scrmodeselect_listmode_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	scrModeSelect_listMode_btn = lv_list_add_btn(ui->scrModeSelect_listMode, LV_SYMBOL_DOWNLOAD, "PROGRAMMER");
	ui->scrModeSelect_listMode_item1 = scrModeSelect_listMode_btn;
	lv_obj_add_style(scrModeSelect_listMode_btn, &style_scrmodeselect_listmode_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	scrModeSelect_listMode_btn = lv_list_add_btn(ui->scrModeSelect_listMode, LV_SYMBOL_CHARGE, "POWER METER");
	ui->scrModeSelect_listMode_item2 = scrModeSelect_listMode_btn;
	lv_obj_add_style(scrModeSelect_listMode_btn, &style_scrmodeselect_listmode_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}