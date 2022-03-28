/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_scrPowerMeter(lv_ui *ui){

	//Write codes scrPowerMeter
	ui->scrPowerMeter = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_main_main_default
	static lv_style_t style_scrpowermeter_main_main_default;
	lv_style_reset(&style_scrpowermeter_main_main_default);
	lv_style_set_bg_color(&style_scrpowermeter_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_scrpowermeter_main_main_default, 255);
	lv_obj_add_style(ui->scrPowerMeter, &style_scrpowermeter_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelVolVal
	ui->scrPowerMeter_labelVolVal = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelVolVal, 75, 150);
	lv_obj_set_size(ui->scrPowerMeter_labelVolVal, 120, 40);
	lv_label_set_text(ui->scrPowerMeter_labelVolVal, "0.000");
	lv_label_set_long_mode(ui->scrPowerMeter_labelVolVal, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelVolVal, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelvolval_main_main_default
	static lv_style_t style_scrpowermeter_labelvolval_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelvolval_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelvolval_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelvolval_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelvolval_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelvolval_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelvolval_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelvolval_main_main_default, lv_color_make(0x00, 0x7f, 0xff));
	lv_style_set_text_font(&style_scrpowermeter_labelvolval_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelvolval_main_main_default, 0);
	lv_style_set_pad_left(&style_scrpowermeter_labelvolval_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelvolval_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelvolval_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelvolval_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelVolVal, &style_scrpowermeter_labelvolval_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelCurVal
	ui->scrPowerMeter_labelCurVal = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelCurVal, 75, 200);
	lv_obj_set_size(ui->scrPowerMeter_labelCurVal, 120, 40);
	lv_label_set_text(ui->scrPowerMeter_labelCurVal, "0.000");
	lv_label_set_long_mode(ui->scrPowerMeter_labelCurVal, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelCurVal, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelcurval_main_main_default
	static lv_style_t style_scrpowermeter_labelcurval_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelcurval_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelcurval_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelcurval_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelcurval_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelcurval_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelcurval_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelcurval_main_main_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_scrpowermeter_labelcurval_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelcurval_main_main_default, 0);
	lv_style_set_pad_left(&style_scrpowermeter_labelcurval_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelcurval_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelcurval_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelcurval_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelCurVal, &style_scrpowermeter_labelcurval_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelPwrVal
	ui->scrPowerMeter_labelPwrVal = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelPwrVal, 75, 250);
	lv_obj_set_size(ui->scrPowerMeter_labelPwrVal, 120, 40);
	lv_label_set_text(ui->scrPowerMeter_labelPwrVal, "0.000");
	lv_label_set_long_mode(ui->scrPowerMeter_labelPwrVal, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelPwrVal, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelpwrval_main_main_default
	static lv_style_t style_scrpowermeter_labelpwrval_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelpwrval_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelpwrval_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelpwrval_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelpwrval_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelpwrval_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelpwrval_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelpwrval_main_main_default, lv_color_make(0xff, 0x7f, 0x00));
	lv_style_set_text_font(&style_scrpowermeter_labelpwrval_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelpwrval_main_main_default, 0);
	lv_style_set_pad_left(&style_scrpowermeter_labelpwrval_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelpwrval_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelpwrval_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelpwrval_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelPwrVal, &style_scrpowermeter_labelpwrval_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelVolLab
	ui->scrPowerMeter_labelVolLab = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelVolLab, 15, 150);
	lv_obj_set_size(ui->scrPowerMeter_labelVolLab, 60, 40);
	lv_label_set_text(ui->scrPowerMeter_labelVolLab, "U:");
	lv_label_set_long_mode(ui->scrPowerMeter_labelVolLab, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelVolLab, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelvollab_main_main_default
	static lv_style_t style_scrpowermeter_labelvollab_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelvollab_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelvollab_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelvollab_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelvollab_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelvollab_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelvollab_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelvollab_main_main_default, lv_color_make(0x00, 0x7f, 0xff));
	lv_style_set_text_font(&style_scrpowermeter_labelvollab_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelvollab_main_main_default, 0);
	lv_style_set_pad_left(&style_scrpowermeter_labelvollab_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelvollab_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelvollab_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelvollab_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelVolLab, &style_scrpowermeter_labelvollab_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelCurLab
	ui->scrPowerMeter_labelCurLab = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelCurLab, 15, 200);
	lv_obj_set_size(ui->scrPowerMeter_labelCurLab, 60, 40);
	lv_label_set_text(ui->scrPowerMeter_labelCurLab, "I:");
	lv_label_set_long_mode(ui->scrPowerMeter_labelCurLab, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelCurLab, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelcurlab_main_main_default
	static lv_style_t style_scrpowermeter_labelcurlab_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelcurlab_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelcurlab_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelcurlab_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelcurlab_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelcurlab_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelcurlab_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelcurlab_main_main_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_scrpowermeter_labelcurlab_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelcurlab_main_main_default, 0);
	lv_style_set_pad_left(&style_scrpowermeter_labelcurlab_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelcurlab_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelcurlab_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelcurlab_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelCurLab, &style_scrpowermeter_labelcurlab_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelPwrLab
	ui->scrPowerMeter_labelPwrLab = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelPwrLab, 15, 250);
	lv_obj_set_size(ui->scrPowerMeter_labelPwrLab, 60, 40);
	lv_label_set_text(ui->scrPowerMeter_labelPwrLab, "P:");
	lv_label_set_long_mode(ui->scrPowerMeter_labelPwrLab, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelPwrLab, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelpwrlab_main_main_default
	static lv_style_t style_scrpowermeter_labelpwrlab_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelpwrlab_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelpwrlab_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelpwrlab_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelpwrlab_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelpwrlab_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelpwrlab_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelpwrlab_main_main_default, lv_color_make(0xff, 0x7f, 0x00));
	lv_style_set_text_font(&style_scrpowermeter_labelpwrlab_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelpwrlab_main_main_default, 0);
	lv_style_set_pad_left(&style_scrpowermeter_labelpwrlab_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelpwrlab_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelpwrlab_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelpwrlab_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelPwrLab, &style_scrpowermeter_labelpwrlab_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelVolUnit
	ui->scrPowerMeter_labelVolUnit = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelVolUnit, 195, 150);
	lv_obj_set_size(ui->scrPowerMeter_labelVolUnit, 30, 40);
	lv_label_set_text(ui->scrPowerMeter_labelVolUnit, "V");
	lv_label_set_long_mode(ui->scrPowerMeter_labelVolUnit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelVolUnit, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelvolunit_main_main_default
	static lv_style_t style_scrpowermeter_labelvolunit_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelvolunit_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelvolunit_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelvolunit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelvolunit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelvolunit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelvolunit_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelvolunit_main_main_default, lv_color_make(0x00, 0x7f, 0xff));
	lv_style_set_text_font(&style_scrpowermeter_labelvolunit_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelvolunit_main_main_default, 0);
	lv_style_set_pad_left(&style_scrpowermeter_labelvolunit_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelvolunit_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelvolunit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelvolunit_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelVolUnit, &style_scrpowermeter_labelvolunit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelCurUnit
	ui->scrPowerMeter_labelCurUnit = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelCurUnit, 195, 200);
	lv_obj_set_size(ui->scrPowerMeter_labelCurUnit, 30, 40);
	lv_label_set_text(ui->scrPowerMeter_labelCurUnit, "A");
	lv_label_set_long_mode(ui->scrPowerMeter_labelCurUnit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelCurUnit, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelcurunit_main_main_default
	static lv_style_t style_scrpowermeter_labelcurunit_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelcurunit_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelcurunit_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelcurunit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelcurunit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelcurunit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelcurunit_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelcurunit_main_main_default, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&style_scrpowermeter_labelcurunit_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelcurunit_main_main_default, 1);
	lv_style_set_pad_left(&style_scrpowermeter_labelcurunit_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelcurunit_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelcurunit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelcurunit_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelCurUnit, &style_scrpowermeter_labelcurunit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_labelPwrUnit
	ui->scrPowerMeter_labelPwrUnit = lv_label_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_labelPwrUnit, 195, 250);
	lv_obj_set_size(ui->scrPowerMeter_labelPwrUnit, 30, 40);
	lv_label_set_text(ui->scrPowerMeter_labelPwrUnit, "W");
	lv_label_set_long_mode(ui->scrPowerMeter_labelPwrUnit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->scrPowerMeter_labelPwrUnit, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_labelpwrunit_main_main_default
	static lv_style_t style_scrpowermeter_labelpwrunit_main_main_default;
	lv_style_reset(&style_scrpowermeter_labelpwrunit_main_main_default);
	lv_style_set_radius(&style_scrpowermeter_labelpwrunit_main_main_default, 0);
	lv_style_set_bg_color(&style_scrpowermeter_labelpwrunit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_scrpowermeter_labelpwrunit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_scrpowermeter_labelpwrunit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_scrpowermeter_labelpwrunit_main_main_default, 0);
	lv_style_set_text_color(&style_scrpowermeter_labelpwrunit_main_main_default, lv_color_make(0xff, 0x7f, 0x00));
	lv_style_set_text_font(&style_scrpowermeter_labelpwrunit_main_main_default, &lv_font_MONACO_40);
	lv_style_set_text_letter_space(&style_scrpowermeter_labelpwrunit_main_main_default, 2);
	lv_style_set_pad_left(&style_scrpowermeter_labelpwrunit_main_main_default, 0);
	lv_style_set_pad_right(&style_scrpowermeter_labelpwrunit_main_main_default, 0);
	lv_style_set_pad_top(&style_scrpowermeter_labelpwrunit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_scrpowermeter_labelpwrunit_main_main_default, 0);
	lv_obj_add_style(ui->scrPowerMeter_labelPwrUnit, &style_scrpowermeter_labelpwrunit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes scrPowerMeter_img_1
	ui->scrPowerMeter_img_1 = lv_img_create(ui->scrPowerMeter);
	lv_obj_set_pos(ui->scrPowerMeter_img_1, 0, 20);
	lv_obj_set_size(ui->scrPowerMeter_img_1, 240, 112);

	//Write style state: LV_STATE_DEFAULT for style_scrpowermeter_img_1_main_main_default
	static lv_style_t style_scrpowermeter_img_1_main_main_default;
	lv_style_reset(&style_scrpowermeter_img_1_main_main_default);
	lv_style_set_img_recolor(&style_scrpowermeter_img_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_scrpowermeter_img_1_main_main_default, 0);
	lv_style_set_img_opa(&style_scrpowermeter_img_1_main_main_default, 255);
	lv_obj_add_style(ui->scrPowerMeter_img_1, &style_scrpowermeter_img_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->scrPowerMeter_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->scrPowerMeter_img_1,&_nvt_240x112);
	lv_img_set_pivot(ui->scrPowerMeter_img_1, 0,0);
	lv_img_set_angle(ui->scrPowerMeter_img_1, 0);
}